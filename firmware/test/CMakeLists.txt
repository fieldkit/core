include(Arduino)

enable_arduino_toolchain()

file(GLOB sources *.cpp ../common/*.cpp)

add_arduino_library(fk-core-test "${sources}")

target_include_directories(fk-core-test PRIVATE "../common")

find_package(FkCore)

fk_configure_core(fk-core-test)

find_package(phylum)

target_link_libraries(fk-core-test phylum)

fk_core_apply_configuration(fk-core-test)

fk_write_profile(fk-core-test)

add_arduino_firmware(fk-core-test)
