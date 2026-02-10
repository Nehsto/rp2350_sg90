message("Name of library is ${DIR_NAME_NOPATH}_driver")

add_library(${DIR_NAME_NOPATH}_driver
	servo.c
)

target_include_directories(${DIR_NAME_NOPATH}_driver PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../include
)

target_link_libraries(${DIR_NAME_NOPATH}_driver
	hardware_spi
	hardware_pwm
	pico_stdlib
	pico_stdio_usb
)