cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 17)
project(ProtobufStudy)

find_package(Protobuf REQUIRED)
set(MY_PROTO_HEADER_DIR ${CMAKE_CURRENT_BINARY_DIR})
add_library(proto SHARED)
target_sources(proto PRIVATE proto/Person.proto proto/Localization.proto)

protobuf_generate(LANGUAGE cpp EXPORT_MACRO NAIVE_API TARGET proto APPEND_PATH PROTOC_OUT_DIR ${MY_PROTO_HEADER_DIR})

target_link_libraries(proto PUBLIC protobuf::libprotobuf)
target_compile_definitions(proto PRIVATE NAIVE_API="__declspec(dllexport)")

add_executable(Demo Demo.cpp)
target_link_libraries(Demo PRIVATE proto)
target_link_options(Demo PRIVATE LINKER:-stats)
target_include_directories(Demo PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_compile_definitions(Demo PRIVATE NAIVE_API="__declspec(dllimport)")

include(CMakePrintHelpers)
cmake_print_properties(
	TARGETS proto Demo
	PROPERTIES LINK_LIBRARIES INTERFACE_LINK_LIBRARIES
)