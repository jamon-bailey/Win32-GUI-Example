
#=================================================
#     Clang C COMPILER CONFIGURATION (clang)
#=================================================

# TODO: Setup clang compiler configuration (if applicable)

set(WIN32_GUI_CLANG_C_VERSION_MIN 14 CACHE STRING "Minimum clang compiler version")

# Confirm supported clang compiler version
if(CMAKE_C_COMPILER_VERSION VERSION_LESS ${WIN32_GUI_CLANG_C_VERSION_MIN})
    message(FATAL_ERROR "Incompatible version of Clang C compiler for ${CMAKE_PROJECT_NAME}.")
endif()

# Compiler feature configuration target
add_library(WIN32_GUI_clang_c_features INTERFACE)
# Compiler diagnostics configuration target
add_library(WIN32_GUI_clang_c_warnings INTERFACE)
# General compiler configuration target
add_library(WIN32_GUI_clang_c_options INTERFACE)
# Preprocessor definitions target
add_library(WIN32_GUI_clang_c_defines INTERFACE)

# Set C standard version
target_compile_features(
    WIN32_GUI_clang_c_features

    INTERFACE
        c_std_11
)

# Set compiler warning flags
target_compile_options(
    WIN32_GUI_clang_c_warnings

    INTERFACE
        # Compiler warning flags
        "-Wall"
        "-Wextra"
        "-Wpedantic"
)

# Conditionally add more aggressive warnings
if(WIN32_GUI_STRICT_C_WARNINGS)
    target_compile_options(
        WIN32_GUI_clang_c_warnings

        INTERFACE
            "-Werror"
            "-Wshadow"
            "-Wdouble-promotion"
            "-Wformat=2"
    )
endif()

# Conditionally set compiler optimization level
target_compile_options(
    WIN32_GUI_clang_c_options

    INTERFACE
        # Disable optimization on debug
        $<$<CONFIG:Debug>:
            "-O0"
        >

        # High optimization on release
        $<$<CONFIG:Release>:
            "-O2"
        >
)

# Define preprocessor definitions
target_compile_definitions(
    WIN32_GUI_clang_c_defines

    INTERFACE
        # Unconditional preprocessor definitions
        WIN32_GUI_C_LANG

        # Preprocessor definitions on debug
        $<$<CONFIG:Debug>:
            _WIN32_GUI_C_DEBUG
            WIN32_GUI_C_DEBUG
        >

        # Preprocessor definitions on release
        $<$<CONFIG:Release>:
            WIN32_GUI_C_RELEASE
        >
)

# Complete Clang C++ compiler package
add_library(WIN32_GUI_clang_c_bundle INTERFACE)

target_link_libraries(
    WIN32_GUI_clang_c_bundle
    
    INTERFACE
        WIN32_GUI_clang_c_features
        WIN32_GUI_clang_c_warnings
        WIN32_GUI_clang_c_options
        WIN32_GUI_clang_c_defines
)
