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
set(sdkVersion 2.2.0)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.2.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(Nyanithm C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()


# Add executable. Default name is the project name, version 0.1
add_executable(Nyanithm 
        src/Nyanithm.cpp
        src/mpr121.cpp
        src/pca954x.cpp
        src/usb_device.cpp
        src/usb_descriptors.c
        src/i2c_port.cpp
        src/vl53l0x.cpp
        src/controller_config.cpp
        src/hw_devices.cpp
        src/chuni_io.cpp
        src/app_link.cpp
        src/boot_mode.cpp
        src/button.cpp
        src/cy8cmbr3116.cpp
        src/hw_check.cpp
        src/error_state.cpp
        src/rainbow.cpp
        src/other_modes.cpp
        src/tca9539.cpp
        src/lamp_array.cpp
        src/production_mode.cpp
        lib/Pico_WS2812-master/WS2812.cpp
        )

pico_generate_pio_header(Nyanithm ${CMAKE_CURRENT_LIST_DIR}/lib/Pico_WS2812-master/WS2812.pio)


pico_set_program_name(Nyanithm "Nyanithm")

pico_set_program_version(Nyanithm "1.0")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(Nyanithm 0)
pico_enable_stdio_usb(Nyanithm 0)
# Add the standard library to the build
target_link_libraries(Nyanithm
        pico_stdlib
        tinyusb_device
        tinyusb_board
        hardware_pio
        )


# Add the standard include files to the build
target_include_directories(Nyanithm PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/src/
        ${CMAKE_CURRENT_LIST_DIR}/include/
        ${CMAKE_CURRENT_LIST_DIR}/include/usb/
        ${CMAKE_CURRENT_LIST_DIR}/include/device/
        ${CMAKE_CURRENT_LIST_DIR}/include/config/
        ${CMAKE_CURRENT_LIST_DIR}/include/share/
        ${CMAKE_CURRENT_LIST_DIR}/include/software/
        ${CMAKE_CURRENT_LIST_DIR}/lib/Pico_WS2812-master/
        )

# Add any user requested libraries
target_link_libraries(Nyanithm 
        hardware_i2c
        hardware_spi
        pico_multicore
        pico_flash
        )

pico_add_extra_outputs(Nyanithm)

