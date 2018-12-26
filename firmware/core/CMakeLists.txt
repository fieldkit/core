include(Arduino)

enable_arduino_toolchain()

file(GLOB sources *.cpp ../common/*.cpp)

find_package(FkCore)

# Get the current working branch
execute_process(
  COMMAND git rev-parse --abbrev-ref HEAD
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_BRANCH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Get the latest abbreviated commit hash of the working branch
execute_process(
  COMMAND git log -1 --format=%H
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_COMMIT_HASH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

add_definitions("-DFIRMWARE_GIT_HASH=\"${GIT_COMMIT_HASH}\"")
add_definitions("-DFIRMWARE_GIT_BRANCH=\"${GIT_BRANCH}\"")
add_definitions("-DFIRMWARE_BUILD=\"$ENV{BUILD_TAG}\"")

option(FK_PROFILE_STANDARD "Standard Profile" ON)
if(FK_PROFILE_STANDARD)
  add_arduino_library(fk-core-standard "${sources}")

  target_include_directories(fk-core-standard PRIVATE "../common")

  fk_configure_core(fk-core-standard)

  target_compile_options(firmware-common-fk-core-standard PUBLIC -DFK_PROFILE_STANDARD)
  target_compile_options(firmware-common-fk-core-standard PUBLIC -DFK_CORE)
  target_compile_options(firmware-common-fk-core-standard PUBLIC -DFK_DEBUG_UART_FALLBACK)
  target_compile_options(firmware-common-fk-core-standard PUBLIC -DFK_ENABLE_FLASH)
  target_compile_options(firmware-common-fk-core-standard PUBLIC -DFK_DISABLE_RADIO)
  target_compile_options(firmware-common-fk-core-standard PUBLIC -DFK_RTC_PCF8523)
  target_compile_options(firmware-common-fk-core-standard PUBLIC -DFK_HARDWARE_SERIAL2_ENABLE)
  target_compile_options(firmware-common-fk-core-standard PUBLIC -DFK_GPS_FIXED_STATION)
  target_compile_options(firmware-common-fk-core-standard PUBLIC -DFK_ENABLE_LOW_POWER_SLEEP)
  target_compile_options(firmware-common-fk-core-standard PUBLIC -DFK_ENABLE_DEEP_SLEEP)

  fk_write_profile(fk-core-standard)

  target_compile_options(fk-core-standard PUBLIC -Wall -Werror)

  add_arduino_firmware(fk-core-standard)
endif(FK_PROFILE_STANDARD)

option(FK_PROFILE_AMAZON "Amazon Profile" ON)
if(FK_PROFILE_AMAZON)
  add_arduino_library(fk-core-amazon "${sources}")

  target_include_directories(fk-core-standard PRIVATE "../common")

  fk_configure_core(fk-core-amazon)

  target_compile_options(firmware-common-fk-core-amazon PUBLIC -DFK_PROFILE_AMAZON)
  target_compile_options(firmware-common-fk-core-amazon PUBLIC -DFK_CORE)
  target_compile_options(firmware-common-fk-core-amazon PUBLIC -DFK_DEBUG_UART_FALLBACK)
  target_compile_options(firmware-common-fk-core-amazon PUBLIC -DFK_ENABLE_FLASH)
  target_compile_options(firmware-common-fk-core-amazon PUBLIC -DFK_DISABLE_RADIO)
  target_compile_options(firmware-common-fk-core-amazon PUBLIC -DFK_RTC_PCF8523)
  target_compile_options(firmware-common-fk-core-amazon PUBLIC -DFK_HARDWARE_SERIAL2_ENABLE)
  target_compile_options(firmware-common-fk-core-amazon PUBLIC -DFK_GPS_FIXED_STATION)
  target_compile_options(firmware-common-fk-core-amazon PUBLIC -DFK_ENABLE_LOW_POWER_SLEEP)
  target_compile_options(firmware-common-fk-core-amazon PUBLIC -DFK_ENABLE_DEEP_SLEEP)

  fk_write_profile(fk-core-amazon)

  target_compile_options(fk-core-amazon PUBLIC -Wall -Werror)

  add_arduino_firmware(fk-core-amazon)
endif(FK_PROFILE_AMAZON)
