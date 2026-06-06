
#================================
#     /src Directory Script
#================================

# TODO: Handle project source targets...

add_executable(Win32_App WIN32)

target_sources(
    Win32_App

    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/window_proc.cpp"
)

target_include_directories(
    Win32_App

    PRIVATE
    "${WIN32_GUI_SOURCE_DIR}/src"
)

# Conditionally link against compiler configuration
if(${WIN32_GUI_CXX_GCC})
    target_link_libraries(
        Win32_App
    
        PRIVATE
        WIN32_GUI_gcc_cxx_bundle
        WIN32_GUI_gcc_c_defines
    )
elseif(${WIN32_GUI_CXX_CLANG})
    target_link_libraries(
        Win32_App
    
        PRIVATE
        WIN32_GUI_clang_cxx_bundle
        WIN32_GUI_clang_c_defines
    )
elseif(${WIN32_GUI_CXX_MSVC})
    target_link_libraries(
        Win32_App
    
        PRIVATE
        WIN32_GUI_msvc_cxx_bundle
    )
endif()

# Setup installation of demo executable
install(
    TARGETS Win32_App
    COMPONENT Win32App
    EXPORT Win32_App-targets

    RUNTIME
        DESTINATION ${CMAKE_INSTALL_BINDIR}
)
