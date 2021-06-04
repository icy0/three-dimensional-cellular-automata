#include <windows.h>
#include <stdio.h>
#include <intrin.h>
#include <dxgidebug.h>
#include <d3d11.h>
#include <directxmath.h>

#include "renderhub_types.h"
#include "renderhub_input.h"
#include "renderhub_logging.h"
#include "renderhub_assert.h"
#include "renderhub_resourceloader.h"

#include "win_renderhub_resourceloader.h"
#include "win_renderhub_window_settings.h"
#include "dx11win_renderhub_renderer.h"

#include "tdca_types.h"
#include "tdca_lifespace_renderer.h"
#include "tdca_voxel_renderer.h"
#include "tdca_simulation.h"

uint8* g_keyboard_key_states = new uint8[256];
mouse_state* g_mouse_state = new mouse_state{};

display_properties* g_display_properties = new display_properties();
window_properties* g_window_properties = new window_properties();

IDXGISwapChain* g_swap_chain = nullptr;
ID3D11Device* g_device = nullptr;
ID3D11DeviceContext* g_device_context = nullptr;

ID3D11RenderTargetView* g_render_target_view = nullptr;
ID3D11DepthStencilView* g_depth_stencil_view = nullptr;
ID3D11DepthStencilState* g_depth_stencil_state = nullptr;
ID3D11RasterizerState* g_rasterizer_state = nullptr;
D3D11_VIEWPORT* g_viewport = new D3D11_VIEWPORT{};

struct IDXGIInfoQueue* g_info_queue = nullptr;

camera* g_camera = new camera{};
voxel_render_data* g_dx11_voxel = new voxel_render_data{};
lifespace_render_data* g_dx11_lifespace = new lifespace_render_data{};

void init_camera()
{
    DirectX::XMVECTOR eye = DirectX::XMVectorSet(0.5f, 0.5f, 1.0f, 1.0f);
    DirectX::XMVECTOR focus_point = DirectX::XMVectorSet(0.5f, -0.5f, -0.5f, 1.0f);
    DirectX::XMVECTOR up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

    DirectX::XMStoreFloat4x4(&g_camera->look_at, DirectX::XMMatrixLookAtRH(eye, focus_point, up));
    DirectX::XMStoreFloat4x4(&g_camera->perspective, 
        DirectX::XMMatrixPerspectiveFovRH(DirectX::XMConvertToRadians(70.0f), 16.0f/9.0f, 0.1f, 1000.0f));
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    rh_assert(g_keyboard_key_states);
    rh_assert(g_mouse_state);
    rh_assert(g_display_properties);
    rh_assert(g_window_properties);

    ZeroMemory(g_keyboard_key_states, sizeof(uint8) * 256);
    ZeroMemory(g_mouse_state, sizeof(mouse_state));
    ZeroMemory(g_display_properties, sizeof(display_properties));
    ZeroMemory(g_window_properties, sizeof(window_properties));
    ZeroMemory(g_viewport, sizeof(D3D11_VIEWPORT));

    win32_get_current_display_device();
    g_window_properties->window_width = g_display_properties->horizontal_pixel_count;
    g_window_properties->window_height = g_display_properties->vertical_pixel_count;

    win32_setup_console_io();

    const wchar_t CLASS_NAME[] = L"resourceloader_windowclass";

    WNDCLASS wc = {};
    wc.lpfnWndProc = win32_callback_procedure;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    rh_assert(RegisterClass(&wc));

    HWND hwnd = CreateWindowEx(0, CLASS_NAME, L"Threedimensional Cellular Automata", WS_OVERLAPPEDWINDOW,
        0, 0, 1920, 1080, NULL, NULL, hInstance, NULL);
    rh_assert(hwnd);

    ShowWindow(hwnd, nCmdShow);

    g_window_properties->window_handle = hwnd;

    win32_init_directx11();

    tdca tdca = {};
    init_tdca(&tdca);

    init_camera();
    init_lifespace_data();
    init_voxel_data(&tdca);

    MSG msg = {};

    LARGE_INTEGER performance_frequency;
    QueryPerformanceFrequency(&performance_frequency);

    LARGE_INTEGER prev_frametime;
    QueryPerformanceCounter(&prev_frametime);

    double fps = 0.0;
    // char fps_print_buffer[256];

    LARGE_INTEGER delta_time = {};
    LARGE_INTEGER curr_frametime = {};

    uint64 prev_cycle_count = __rdtsc();
    uint64 delta_cycle_count = 0;
    uint64 curr_cycle_count = 0;

    uint64 current_time = __rdtsc();
    uint64 time_when_to_start = __rdtsc() + (3'600'000'000 * 4);

    while (msg.message != WM_QUIT)
    {
        if (PeekMessageA(&msg, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessageA(&msg);
        }
        else
        {
            float clear_color[] {0.1f, 0.1f, 0.1f, 1.0f};
            rh_dx_logging(g_device_context->ClearRenderTargetView(g_render_target_view, clear_color));
            rh_dx_logging(g_device_context->ClearDepthStencilView(g_depth_stencil_view, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0));

            current_time = __rdtsc();
            if(time_when_to_start < current_time)
            {
                update_tdca(&tdca);
                update_voxels(&tdca);
                time_when_to_start = __rdtsc() + (3'600'000'000 * 4);
            }

            render_lifespace();
            render_voxels(&tdca);

            rh_dx_logging(g_swap_chain->Present(0, 0));

            curr_cycle_count = __rdtsc();
            delta_cycle_count = curr_cycle_count - prev_cycle_count;
            prev_cycle_count = curr_cycle_count;

            QueryPerformanceCounter(&curr_frametime);
            delta_time.QuadPart = curr_frametime.QuadPart - prev_frametime.QuadPart;
            delta_time.QuadPart *= 1'000'000;
            delta_time.QuadPart /= performance_frequency.QuadPart;

            fps = 1.0 / (delta_time.QuadPart / 1'000'000.0f);
            prev_frametime.QuadPart = curr_frametime.QuadPart;
            
            char buffer[256];
            snprintf(buffer, 256, "fps: %f", fps);
            // rh_log_message(buffer);

            // after update and render
            update_keyboard_input(g_keyboard_key_states);
            update_mouse_input(g_mouse_state);
        }
    }

    return 0;
}