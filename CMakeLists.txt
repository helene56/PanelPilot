# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(PanelPilot C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add the lvgl submodule
add_subdirectory(lib/lvgl)

# Add the ui library
add_subdirectory(lib/ui)

# Add executable. Default name is the project name, version 0.1
add_executable(PanelPilot main.cpp )
pico_set_program_name(PanelPilot "PanelPilot")
pico_set_program_version(PanelPilot "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(PanelPilot 0)
pico_enable_stdio_usb(PanelPilot 1)

# Link libraries to PanelPilot
target_link_libraries(PanelPilot
    pico_stdlib
    hardware_spi
    hardware_dma
    lvgl
    ui
)

# Add include directories for PanelPilot
target_include_directories(PanelPilot PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_SOURCE_DIR}/lib
    ${CMAKE_CURRENT_LIST_DIR}/lib
    ${CMAKE_SOURCE_DIR}/lib/lvgl
    ${CMAKE_SOURCE_DIR}/lib/ui
)

# Add extra outputs for the Pico
pico_add_extra_outputs(PanelPilot)

