cmake_minimum_required (VERSION 3.5)

add_subdirectory (cmake/native_app_glue)

project (Numb3rs CXX)

add_library(numb3rs SHARED "")

target_compile_options (
	numb3rs

	PUBLIC
	-std=c++1z
	-Wall
	-Wextra
	-Wpedantic
	-Werror
)

target_include_directories (
	numb3rs

	SYSTEM PUBLIC
	native_app_glue
)

target_sources (
	numb3rs

	PRIVATE
	source/main.cpp
)

# Export ANativeActivity_onCreate(),
# Refer to: https://github.com/android-ndk/ndk/issues/381.
set (
	CMAKE_SHARED_LINKER_FLAGS
	"${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate"
)

# add lib dependencies
target_link_libraries (
	numb3rs

	android
	native_app_glue
	EGL
	GLESv1_CM
	log
)
