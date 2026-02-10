cmake_minimum_required(VERSION 3.13)

set(picotool_DIR $MY_INSTALL_DIR/picotool)
set(PICO_BOARD pico2)
set(PICO_PLATFORM rp2350)

# Pull in Pico SDK (must be before project)
set(sdk_import_PATH "$ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake")
message(${sdk_import_PATH})
include(${sdk_import_PATH})

get_filename_component(DIR_NAME_NOPATH ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${DIR_NAME_NOPATH}_example C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

add_subdirectory(../src 
    ${CMAKE_CURRENT_BINARY_DIR}/src
)

add_executable(${PROJECT_NAME}
        main.c
)

# pull in common dependencies and additional pwm hardware support
target_link_libraries(${PROJECT_NAME} 
        ${DIR_NAME_NOPATH}_driver
)

pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(${PROJECT_NAME})

# add url via pico_set_program_url
# example_auto_set_url(pwm_led_fade)
