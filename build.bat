@echo off

set RENDERHUB_PATH=C:\Development\renderhub

@REM echo building renderhub_Debug_x64.lib...
@REM cd ..\renderhub
@REM call %RENDERHUB_PATH%\build.bat
@REM cd ..\three-dimensional-cellular-automata
@REM echo finished building renderhub_Debug_x64.lib, returning to compiling tdca...

set PROJECT_NAME=tdca
set CODE_BASE_PATH=%CD%
set BUILD_PATH=%CODE_BASE_PATH%\output
set BINARIES_PATH=%BUILD_PATH%\binaries
set INTERMEDIATES_PATH=%BUILD_PATH%\intermediates
set SOURCE_PATH=%CODE_BASE_PATH%\source
set SHADER_PATH=%CODE_BASE_PATH%\shaders

set INCLUDE_DIRECTORIES=/I %CODE_BASE_PATH%\include\ /I %RENDERHUB_PATH%\include\
set PREPROCESSOR_DEFINES=/DUNICODE /D_UNICODE /D_WIN32 /D_DEBUG
set COMPILER_OPTIONS=/Fe%BINARIES_PATH%\%PROJECT_NAME%.exe /Fd%INTERMEDIATES_PATH%\ /Fo%BINARIES_PATH%\ /nologo /MT %INCLUDE_DIRECTORIES% /ZI /EHsc /W3 /std:c++17 %PREPROCESSOR_DEFINES%
set INCLUDED_LIBRARIES=User32.lib Gdi32.lib Shell32.lib msvcrt.lib %RENDERHUB_PATH%\output\binaries\renderhub_Debug_x64.lib dxguid.lib D3D11.lib DXGI.lib vcruntimed.lib ucrtd.lib
set LINKER_OPTIONS=/link /NODEFAULTLIB:libcmt.lib /NODEFAULTLIB:msvcrtd.lib /DEBUG

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

fxc /T vs_5_0 /Fd %BINARIES_PATH%\vertex_shader.pdb /Fo %BINARIES_PATH%\vertex_shader.cso /nologo /Od /Zi /Zpr %SHADER_PATH%\vertex.hlsl
fxc /T ps_5_0 /Fd %BINARIES_PATH%\pixel_shader.pdb /Fo %BINARIES_PATH%\pixel_shader.cso /nologo /Od /Zi /Zpr %SHADER_PATH%\pixel.hlsl

cl %COMPILER_OPTIONS% %SOURCE_PATH%\*.cpp %INCLUDED_LIBRARIES% %LINKER_OPTIONS%
echo finished building tdca.exe