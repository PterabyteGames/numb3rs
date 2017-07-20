#
# Copyright (C) The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
cmake_minimum_required(VERSION 3.4.1)

add_subdirectory (native_app_glue)

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
	main.cpp
)

# Export ANativeActivity_onCreate(),
# Refer to: https://github.com/android-ndk/ndk/issues/381.
set(CMAKE_SHARED_LINKER_FLAGS
    "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")

# add lib dependencies
target_link_libraries (
	numb3rs

    android
    native_app_glue
    EGL
    GLESv1_CM
    log)
