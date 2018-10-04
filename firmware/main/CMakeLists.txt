include(Arduino)

enable_arduino_toolchain()

set(sources main.cpp)

add_arduino_library(fk-core "${sources}")

find_package(FkCore)

fk_configure_core(fk-core)

fk_core_apply_configuration(fk-core)

add_arduino_firmware(fk-core)
