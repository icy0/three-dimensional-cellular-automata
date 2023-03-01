@echo off

set PROJECT_NAME=tdca
set CODE_BASE_PATH=%CD%
set RENDERHUB_PATH=%CODE_BASE_PATH%\dependencies\renderhub
set BUILD_PATH=%CODE_BASE_PATH%\output
set BINARIES_PATH=%BUILD_PATH%\binaries
set INTERMEDIATES_PATH=%BUILD_PATH%\intermediates
set SOURCE_PATH=%CODE_BASE_PATH%\source
set SHADER_PATH=%CODE_BASE_PATH%\shaders

set NVCC_CL_INCLUDE_DIRECTORIES=/I%CODE_BASE_PATH%\include\,/I%RENDERHUB_PATH%\include\
set NVCC_CL_PREPROCESSOR_DEFINES=/DUNICODE,/D_UNICODE,/D_WIN32,/D_DEBUG
set NVCC_CL_COMPILER_OPTIONS=/Fd%INTERMEDIATES_PATH%\,/nologo,/MDd,%NVCC_CL_INCLUDE_DIRECTORIES%,/Zi,/EHsc,/W3,/std:c++17,%NVCC_CL_PREPROCESSOR_DEFINES%
set NVCC_CL_INCLUDED_LIBRARIES=--library=User32,Gdi32,Shell32,msvcrt,%RENDERHUB_PATH%\output\binaries\renderhub_Debug_x64,dxguid,D3D11,DXGI,vcruntimed,ucrtd
set NVCC_CL_LINKER_OPTIONS=/NODEFAULTLIB:libcmtd.lib,/NODEFAULTLIB:msvcrtd.lib,/DEBUG
set NVCC_SOURCE_FILES=%NVCC_CL_INCLUDED_LIBRARIES% %SOURCE_PATH%\tdca_gpu_device_functions.cu %SOURCE_PATH%\main.cpp %SOURCE_PATH%\tdca_lifespace_renderer.cpp %SOURCE_PATH%\tdca_simulation.cpp %SOURCE_PATH%\tdca_voxel_renderer.cpp
set NVCC_COMPILER_OPTIONS=--std=c++17 --debug --device-debug --cudart=static --keep --keep-dir=%INTERMEDIATES_PATH%\ --machine=64 --compiler-options=%NVCC_CL_COMPILER_OPTIONS% --linker-options=%NVCC_CL_LINKER_OPTIONS% --output-file=%BINARIES_PATH%\%PROJECT_NAME%.exe

IF NOT DEFINED VC_COMPILER_INITIALIZED (
	set /A VC_COMPILER_INITIALIZED=1
	call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
	echo.
)

IF NOT EXIST %BUILD_PATH% (
	mkdir %BUILD_PATH%
)

IF NOT EXIST %INTERMEDIATES_PATH% (
	mkdir %INTERMEDIATES_PATH%
)

IF NOT EXIST %BINARIES_PATH% (
	mkdir %BINARIES_PATH%
)

fxc /T vs_5_0 /Fd %BINARIES_PATH%\vertex_shader_lifespace.pdb /Fo %BINARIES_PATH%\vertex_shader_lifespace.cso /nologo /Od /Zi /Zpr %SHADER_PATH%\vertex_lifespace.hlsl
fxc /T ps_5_0 /Fd %BINARIES_PATH%\pixel_shader_lifespace.pdb /Fo %BINARIES_PATH%\pixel_shader_lifespace.cso /nologo /Od /Zi /Zpr %SHADER_PATH%\pixel_lifespace.hlsl

fxc /T vs_5_0 /Fd %BINARIES_PATH%\vertex_shader_voxel.pdb /Fo %BINARIES_PATH%\vertex_shader_voxel.cso /nologo /Od /Zi /Zpr %SHADER_PATH%\vertex_voxel.hlsl
fxc /T ps_5_0 /Fd %BINARIES_PATH%\pixel_shader_voxel.pdb /Fo %BINARIES_PATH%\pixel_shader_voxel.cso /nologo /Od /Zi /Zpr %SHADER_PATH%\pixel_voxel.hlsl

nvcc %NVCC_COMPILER_OPTIONS% %NVCC_SOURCE_FILES%

REM cl %CL_COMPILER_OPTIONS% %SOURCE_PATH%\*.cpp %CL_INCLUDED_LIBRARIES% %CL_LINKER_OPTIONS%
REM echo finished building tdca.exe