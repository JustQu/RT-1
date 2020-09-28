rem ===================build rt on windows using nvidia opencl lib===============
@echo off

mkdir .\build
pushd .\build
cl -FC -Zi  ..\srcs\main.c ..\srcs\*.c ^
					-I ../include ^
					-I ../Libs/libft/includes ^
					-I ../Libs ^
					-I ../Libs/libft ^
					-I ../Libs/SDL2 ^
					-I ../Libs/SDL2_image/include ^
					-I ../Libs/SDL2_ttf/include ^
					-I ../Libs/SDL2_gfx ^
					/link /SUBSYSTEM:CONSOLE ^
					../Libs/libft/libft.lib ^
					../Libs\SDL2\lib\win64\SDL2main.lib ^
					../Libs\SDL2\lib\win64\SDL2.lib ^
					"C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v10.2\lib\x64\OpenCL.lib"^
					"Shell32.lib"
rem /link /SUBSYSTEM:CONSOLE ^ ..\srcs\*.c

popd
