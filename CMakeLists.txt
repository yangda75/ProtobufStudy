cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 17)
project(ProtobufStudy)

#https://stackoverflow.com/a/62886758
#https://github.com/abseil/abseil-cpp/issues/398
# This project is using a dynamic vcpkg triplet. Because I could not get Abseil to work with a static triplet.
find_package(Protobuf CONFIG REQUIRED)
find_package(Threads REQUIRED) # ShortDebugString() need this

set(MY_PROTO_HEADER_DIR ${CMAKE_CURRENT_BINARY_DIR}/proto)
add_library(proto SHARED)
target_sources(proto PRIVATE proto/Person.proto proto/Localization.proto)
set(PROTO_FILES proto/Person.proto proto/Localization.proto)
if(MSVC)
    protobuf_generate(LANGUAGE cpp TARGET proto APPEND_PATH PROTOC_OUT_DIR ${MY_PROTO_HEADER_DIR} EXPORT_MACRO NAIVE_API)
else()
    protobuf_generate(LANGUAGE cpp TARGET proto APPEND_PATH PROTOC_OUT_DIR ${MY_PROTO_HEADER_DIR})
endif()

target_include_directories(proto INTERFACE ${MY_PROTO_HEADER_DIR})
target_link_libraries(proto PUBLIC protobuf::libprotobuf Threads::Threads)

if(MSVC)
    target_compile_definitions(proto PRIVATE NAIVE_API=__declspec\(dllexport\))
endif()
add_executable(Demo Demo.cpp)
target_link_libraries(Demo PRIVATE proto)

if(MSVC)
    target_compile_definitions(Demo PRIVATE NAIVE_API=__declspec\(dllimport\))
endif()


include(CMakePrintHelpers)
cmake_print_properties(
    TARGETS proto Demo
    PROPERTIES LINK_LIBRARIES INTERFACE_LINK_LIBRARIES INCLUDE_DIRECTORIES INTERFACE_INCLUDE_DIRECTORIES
)

# install
if(MSVC)
    install(
        TARGETS Demo proto 
        RUNTIME_DEPENDENCIES 
            PRE_EXCLUDE_REGEXES [[api-ms-win-.*]] [[ext-ms-.*]] [[kernel32\.dll]]
            POST_EXCLUDE_REGEXES [[.*(\\|/)system32(\\|/).*\.dll]]
    )
else()

    include(GNUInstallDirs)
    file(RELATIVE_PATH relDir 
        ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR} 
        ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}
    )

    set_target_properties(Demo PROPERTIES INSTALL_RPATH "$ORIGIN/${relDir}")
    install(
        TARGETS Demo proto 
        RUNTIME_DEPENDENCIES 
            PRE_EXCLUDE_REGEXES [[libc\.so\..*]] [[libgcc_s\.so\..*]] [[libm\.so\..*]] [[libstdc\+\+\.so\..*]]
    )
endif()
