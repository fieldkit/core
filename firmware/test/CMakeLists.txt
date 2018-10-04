include(Arduino)

enable_arduino_toolchain()

set(sources main.cpp)

add_arduino_library(fk-core-test "${sources}")

find_package(FkCore)

fk_configure_core(fk-core-test)

find_package(phylum)

target_link_libraries(fk-core-test phylum)

fk_core_apply_configuration(fk-core-test)

fk_write_profile(fk-core-test)

add_arduino_firmware(fk-core-test)
