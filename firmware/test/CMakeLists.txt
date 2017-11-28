set(SOURCE_FILES
  main.cpp
)

set(LIBRARIES
  Wire
  SPI
  SD
)

arduino(fk-core-test "${SOURCE_FILES}" "${LIBRARIES}")
