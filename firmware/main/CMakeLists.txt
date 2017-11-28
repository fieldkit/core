set(SOURCE_FILES
  main.cpp
)

set(LIBRARIES
  Wire
)

arduino(fk-core "${SOURCE_FILES}" "${LIBRARIES}")
