option(FK_CORE_GENERATION_2 "Enable Generation 2 Core hardware profile. (see harware.h)")
if(FK_CORE_GENERATION_2)
  add_definitions(-DFK_CORE_GENERATION_2)
else()
  add_definitions(-DFK_CORE_GENERATION_1)
endif(FK_CORE_GENERATION_2)

option(FK_ENABLE_RADIO "Configure radio." ON)
if(FK_ENABLE_RADIO)
  add_definitions(-DFK_DISABLE_RADIO)
else()
  add_definitions(-DFK_ENABLE_RADIO)
endif(FK_ENABLE_RADIO)

set(SOURCE_FILES main.cpp)
set(LIBRARIES Wire SPI)

arduino(fk-core-test "${SOURCE_FILES}" "${LIBRARIES}")
