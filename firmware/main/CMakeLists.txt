include(ArduinoMinimal)

set(SOURCE_FILES main.cpp)
set(LIBRARIES Wire)

arduino(fk-core "${SOURCE_FILES}" "${LIBRARIES}")

add_definitions(-DPHYLUM_ENABLE_SERIAL_FLASH)
target_compile_options(arduino_zero_phylum PUBLIC -DPHYLUM_ENABLE_SERIAL_FLASH)
