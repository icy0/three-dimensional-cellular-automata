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

ID3D11Buffer* g_constant_buffer = nullptr;
ID3D11Buffer* g_vertex_buffer = nullptr;
ID3D11Buffer* g_index_buffer = nullptr;
ID3D11Buffer* g_instance_buffer = nullptr;
ID3D11VertexShader* g_vertex_shader = nullptr;
ID3D11InputLayout* g_input_layout = nullptr;
ID3D11PixelShader* g_pixel_shader = nullptr;

uint32 g_instance_count = 0;

void read_shader(const char* filename, char** file_bytes, uint64* file_size_in_bytes)
{
	char* file_buffer;
    HANDLE file_handle;
    LARGE_INTEGER file_size_in_bytes_temp = {};

	ZeroMemory(&file_handle, sizeof(HANDLE));

	file_handle = CreateFileA(filename, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	rh_assert(file_handle);

	GetFileSizeEx(file_handle, &file_size_in_bytes_temp);
    *file_size_in_bytes = file_size_in_bytes_temp.QuadPart;
	rh_assert(file_size_in_bytes);

	file_buffer = new char[*file_size_in_bytes];
	rh_assert(file_buffer);

	DWORD bytes_read = {}; // note(paul): necessary for function call, won't be used afterwards.
	rh_assert(ReadFile(file_handle, (void*) file_buffer, *file_size_in_bytes, &bytes_read, NULL));

    *file_bytes = file_buffer;
}

void init_cube_data()
{
    HRESULT result = -1;
    
    DirectX::XMVECTOR eye = DirectX::XMVectorSet(0.5f, -0.5f, 3.0f, 1.0f);
    DirectX::XMVECTOR focus_point = DirectX::XMVectorSet(0.5f, -0.5f, -0.5f, 1.0f);
    DirectX::XMVECTOR up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

    constant_buffer vertex_shader_constant_buffer = {};
    DirectX::XMStoreFloat4x4(&vertex_shader_constant_buffer.model, DirectX::XMMatrixIdentity());

    DirectX::XMStoreFloat4x4(&vertex_shader_constant_buffer.view, DirectX::XMMatrixLookAtRH(eye, focus_point, up));

    DirectX::XMStoreFloat4x4(&vertex_shader_constant_buffer.projection, 
        DirectX::XMMatrixPerspectiveFovRH(DirectX::XMConvertToRadians(70.0f), 16.0f/9.0f, 0.1f, 1000.0f));

    vertex_shader_constant_buffer.scale_factor = 0.1f;

    dx_vertex vertices[]
    {
    //   {pos},      {normal}           {pos},        {normal}          {pos},        {normal}          {pos},        {normal}
        {{0, 0, 0},  {0, 0, 1}},        {{1, 0, 0},   {0, 0, 1}},       {{0, -1, 0},  {0, 0, 1}},       {{1, -1, 0},  {0, 0, 1}},   // front face
        {{1, 0, 0},  {1, 0, 0}},        {{1, 0, -1},  {1, 0, 0}},       {{1, -1, 0},  {1, 0, 0}},       {{1, -1, -1}, {1, 0, 0}},   // right face
        {{1, 0, -1}, {0, 0, -1}},       {{0, 0, -1},  {0, 0, -1}},      {{1, -1, -1}, {0, 0, -1}},      {{0, -1, -1}, {0, 0, -1}},  // back face
        {{0, 0, -1}, {-1, 0, 0}},       {{0, 0, 0},   {-1, 0, 0}},      {{0, -1, -1}, {-1, 0, 0}},      {{0, -1, 0},  {-1, 0, 0}},  // left face
        {{1, 0, -1}, {0, 1, 0}},        {{1, 0, 0},   {0, 1, 0}},       {{0, 0, -1},  {0, 1, 0}},       {{0, 0, 0},   {0, 1, 0}},   // top face
        {{1, -1, 0}, {0, -1, 0}},       {{1, -1, -1}, {0, -1, 0}},      {{0, -1, 0},  {0, -1, 0}},      {{0, -1, -1}, {0, -1, 0}}   // bottom face
    };

    struct instance_transforms
    {
        DirectX::XMVECTOR translation;
    };

    instance_transforms instances[]
    {
        {DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f)},
        {DirectX::XMVectorSet(1.01f, 0.0f, 0.0f, 1.0f)},
        {DirectX::XMVectorSet(2.02f, 0.0f, 0.0f, 1.0f)}
    };

    g_instance_count = ARRAYSIZE(instances);

    uint32 indices[]
    {
        0, 1, 2,
        1, 3, 2,
        4, 5, 6,
        5, 7, 6,
        8, 9, 10,
        9, 11, 10,
        12, 13, 14,
        13, 15, 14,
        16, 17, 18,
        17, 19, 18,
        20, 21, 22,
        21, 23, 22
    };

    D3D11_BUFFER_DESC constant_buffer_description = {};
    constant_buffer_description.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    constant_buffer_description.ByteWidth = sizeof(constant_buffer);
    // constant_buffer_description.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    constant_buffer_description.CPUAccessFlags = 0;
    // constant_buffer_description.Usage = D3D11_USAGE_DYNAMIC;
    constant_buffer_description.Usage = D3D11_USAGE_DEFAULT;
    constant_buffer_description.MiscFlags = 0;
    constant_buffer_description.StructureByteStride = 0;

    D3D11_SUBRESOURCE_DATA constant_buffer_subres_data = {};
    constant_buffer_subres_data.pSysMem = &vertex_shader_constant_buffer;
    constant_buffer_subres_data.SysMemPitch = 0;
    constant_buffer_subres_data.SysMemSlicePitch = 0;

    rh_dx_logging(result = g_device->CreateBuffer(&constant_buffer_description, &constant_buffer_subres_data, &g_constant_buffer));
    rh_assert(SUCCEEDED(result));
    rh_assert(g_constant_buffer)
    rh_dx_logging(g_device_context->VSSetConstantBuffers(0, 1, &g_constant_buffer));

    D3D11_BUFFER_DESC vertex_buffer_description = {};
    vertex_buffer_description.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertex_buffer_description.ByteWidth = sizeof(vertex) * ARRAYSIZE(vertices);
    vertex_buffer_description.CPUAccessFlags = 0;
    vertex_buffer_description.Usage = D3D11_USAGE_IMMUTABLE;
    vertex_buffer_description.MiscFlags = 0;
    vertex_buffer_description.StructureByteStride = sizeof(vertex);

    D3D11_SUBRESOURCE_DATA vertex_buffer_subres_data = {};
    vertex_buffer_subres_data.pSysMem = (void*) vertices;
    vertex_buffer_subres_data.SysMemPitch = 0;
    vertex_buffer_subres_data.SysMemSlicePitch = 0;

    result = -1;
    rh_dx_logging(result = g_device->CreateBuffer(&vertex_buffer_description, &vertex_buffer_subres_data, &g_vertex_buffer));
    rh_assert(SUCCEEDED(result));
    rh_assert(g_vertex_buffer);

    uint32 stride = sizeof(dx_vertex);
    uint32 offset = 0;
    rh_dx_logging(g_device_context->IASetVertexBuffers(0, 1, &g_vertex_buffer, &stride, &offset));

    D3D11_BUFFER_DESC instance_buffer_description = {};
    instance_buffer_description.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    instance_buffer_description.ByteWidth = sizeof(instance_transforms) * ARRAYSIZE(instances);
    instance_buffer_description.CPUAccessFlags = 0;
    instance_buffer_description.Usage = D3D11_USAGE_IMMUTABLE;
    instance_buffer_description.MiscFlags = 0;
    instance_buffer_description.StructureByteStride = sizeof(instance_transforms);

    D3D11_SUBRESOURCE_DATA instance_buffer_subres_data = {};
    instance_buffer_subres_data.pSysMem = (void*) instances;
    instance_buffer_subres_data.SysMemPitch = 0;
    instance_buffer_subres_data.SysMemSlicePitch = 0;

    result = -1;
    rh_dx_logging(result = g_device->CreateBuffer(&instance_buffer_description, &instance_buffer_subres_data, &g_instance_buffer));
    rh_assert(SUCCEEDED(result));
    rh_assert(g_instance_buffer);

    stride = sizeof(instance_transforms);
    offset = 0;
    rh_dx_logging(g_device_context->IASetVertexBuffers(1, 1, &g_instance_buffer, &stride, &offset));

    D3D11_BUFFER_DESC index_buffer_description = {};
    index_buffer_description.BindFlags = D3D11_BIND_INDEX_BUFFER;
    index_buffer_description.ByteWidth = sizeof(uint32) * ARRAYSIZE(indices);
    index_buffer_description.CPUAccessFlags = 0;
    index_buffer_description.Usage = D3D11_USAGE_IMMUTABLE;
    index_buffer_description.MiscFlags = 0;
    index_buffer_description.StructureByteStride = sizeof(uint32);

    D3D11_SUBRESOURCE_DATA index_buffer_subres_data = {};
    index_buffer_subres_data.pSysMem = (void*) indices;
    index_buffer_subres_data.SysMemPitch = 0;
    index_buffer_subres_data.SysMemSlicePitch = 0;

    result = -1;
    rh_dx_logging(result = g_device->CreateBuffer(&index_buffer_description, &index_buffer_subres_data, &g_index_buffer));
    rh_assert(SUCCEEDED(result));
    rh_assert(g_index_buffer);

    char* vertex_shader_bytes = nullptr;
    uint64 vertex_shader_size_in_bytes = 0;
    read_shader("vertex_shader.cso", &vertex_shader_bytes, &vertex_shader_size_in_bytes);

    rh_dx_logging(g_device_context->IASetIndexBuffer(g_index_buffer, DXGI_FORMAT_R32_UINT, 0));
    rh_dx_logging(g_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

    rh_dx_logging(result = g_device->CreateVertexShader((void*) vertex_shader_bytes, vertex_shader_size_in_bytes, nullptr, &g_vertex_shader));
    rh_assert(SUCCEEDED(result));
    rh_assert(g_vertex_shader);

    D3D11_INPUT_ELEMENT_DESC input_layout_position = {};
    input_layout_position.SemanticName = "POSITION";
    input_layout_position.SemanticIndex = 0;
    input_layout_position.Format = DXGI_FORMAT_R32G32B32_FLOAT;
    input_layout_position.InputSlot = 0;
    input_layout_position.AlignedByteOffset = offsetof(dx_vertex, position);
    input_layout_position.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    input_layout_position.InstanceDataStepRate = 0;
    
    D3D11_INPUT_ELEMENT_DESC input_layout_normal = {};
    input_layout_normal.SemanticName = "NORMAL";
    input_layout_normal.SemanticIndex = 0;
    input_layout_normal.Format = DXGI_FORMAT_R32G32B32_FLOAT;
    input_layout_normal.InputSlot = 0;
    input_layout_normal.AlignedByteOffset = offsetof(dx_vertex, normal);
    input_layout_normal.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    input_layout_normal.InstanceDataStepRate = 0;
    
    D3D11_INPUT_ELEMENT_DESC input_layout_instance_position = {};
    input_layout_instance_position.SemanticName = "POSITION";
    input_layout_instance_position.SemanticIndex = 1;
    input_layout_instance_position.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
    input_layout_instance_position.InputSlot = 1;
    input_layout_instance_position.AlignedByteOffset = 0;
    input_layout_instance_position.InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
    input_layout_instance_position.InstanceDataStepRate = 1;

    D3D11_INPUT_ELEMENT_DESC layouts[] {input_layout_position, input_layout_normal, input_layout_instance_position};

    rh_dx_logging(result = g_device->CreateInputLayout(layouts, ARRAYSIZE(layouts), (void*) vertex_shader_bytes, vertex_shader_size_in_bytes, &g_input_layout));
    rh_assert(SUCCEEDED(result));
    rh_assert(g_input_layout);

    char* pixel_shader_bytes = nullptr;
    uint64 pixel_shader_size_in_bytes = 0;
    read_shader("pixel_shader.cso", &pixel_shader_bytes, &pixel_shader_size_in_bytes);

    result = -1;
    rh_dx_logging(result = g_device->CreatePixelShader((void*) pixel_shader_bytes, pixel_shader_size_in_bytes, nullptr, &g_pixel_shader));
    rh_assert(SUCCEEDED(result));
    rh_assert(g_pixel_shader);

    rh_dx_logging(g_device_context->IASetInputLayout(g_input_layout));

    rh_dx_logging(g_device_context->VSSetShader(g_vertex_shader, nullptr, 0));
    rh_dx_logging(g_device_context->PSSetShader(g_pixel_shader, nullptr, 0));
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

    init_cube_data();

    // init background data structure
    // init vertex buffer and index buffer for one cube
    // build constant buffers for model, view and world matrices
    // load shaders

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

    while (msg.message != WM_QUIT)
    {
        if (PeekMessageA(&msg, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessageA(&msg);
        }
        else
        {
            float clear_color[] {0.2f, 0.2f, 0.2f, 1.0f};
            rh_dx_logging(g_device_context->ClearRenderTargetView(g_render_target_view, clear_color));
            rh_dx_logging(g_device_context->ClearDepthStencilView(g_depth_stencil_view, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0));

            constant_buffer vertex_shader_constant_buffer = {};
            DirectX::XMVECTOR eye = DirectX::XMVectorSet(0.5f, -0.5f, 3.0f, 1.0f);
            DirectX::XMVECTOR focus_point = DirectX::XMVectorSet(0.5f, -0.5f, -0.5f, 1.0f);
            DirectX::XMVECTOR up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
            DirectX::XMStoreFloat4x4(&vertex_shader_constant_buffer.model, DirectX::XMMatrixIdentity());
            DirectX::XMStoreFloat4x4(&vertex_shader_constant_buffer.view, DirectX::XMMatrixLookAtRH(eye, focus_point, up));
            DirectX::XMStoreFloat4x4(&vertex_shader_constant_buffer.projection, DirectX::XMMatrixPerspectiveFovRH(DirectX::XMConvertToRadians(90.0f), 16.0f/9.0f, 0.1f, 1000.0f));
            vertex_shader_constant_buffer.scale_factor = 0.1f;

            // static float angle = 0.0f;
            // angle += 30.0f * (delta_time.QuadPart / 1'000'000.0f);
            // DirectX::XMVECTOR rotation_axis = DirectX::XMVectorSet(1, 0, 0, 0);

            // DirectX::XMStoreFloat4x4(&vertex_shader_constant_buffer.model, DirectX::XMMatrixRotationAxis(rotation_axis, DirectX::XMConvertToRadians(angle)));

            rh_dx_logging(g_device_context->UpdateSubresource(g_constant_buffer, 0, nullptr, &vertex_shader_constant_buffer, 0, 0));

            rh_dx_logging(g_device_context->DrawIndexedInstanced(36, g_instance_count, 0, 0, 0));

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

            // after update and render
            update_keyboard_input(g_keyboard_key_states);
            update_mouse_input(g_mouse_state);
        }
    }

    return 0;
}