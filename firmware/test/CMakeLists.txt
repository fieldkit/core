include(Arduino)

enable_arduino_toolchain()

set(sources main.cpp)

add_arduino_library(fk-core-test "${sources}")

find_package(phylum)
target_link_libraries(fk-core-test phylum)

find_package(FkCore)
fk_configure_core(fk-core-test)

find_package(Adafruit_NeoPixel)
target_link_libraries(fk-core-test Adafruit_NeoPixel)

add_arduino_firmware(fk-core-test)
