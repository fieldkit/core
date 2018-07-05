set(SOURCE_FILES
  main.cpp
)

set(LIBRARIES
  Wire
  SPI
)

arduino(fk-core-test "${SOURCE_FILES}" "${LIBRARIES}")
