cmake_minimum_required(VERSION 3.4.1)

project (native_app_glue C)

add_library(native_app_glue STATIC "")

target_include_directories (
	native_app_glue
	PUBLIC
	${ANDROID_NDK}/sources/android/native_app_glue
)

target_sources(
	native_app_glue
	PRIVATE
	${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c
)

