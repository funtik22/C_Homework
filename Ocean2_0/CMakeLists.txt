cmake_minimum_required(VERSION 3.5)

project(OCEAN)

set(PRINT_ACTIONS ON CACHE BOOL "Print actions")

set(SRC
      ${PROJECT_SOURCE_DIR}/Simulations.cpp
      ${PROJECT_SOURCE_DIR}/Entities/Cell.cpp
      ${PROJECT_SOURCE_DIR}/Entities/Object.cpp
      ${PROJECT_SOURCE_DIR}/Entities/Ocean.cpp
      ${PROJECT_SOURCE_DIR}/Entities/Stone.cpp
      ${PROJECT_SOURCE_DIR}/Entities/Reef.cpp
      ${PROJECT_SOURCE_DIR}/Entities/Prey.cpp
      ${PROJECT_SOURCE_DIR}/Entities/Predator.cpp
      ${PROJECT_SOURCE_DIR}/Entities/ApexPredator.cpp
      ${PROJECT_SOURCE_DIR}/Entities/Neighbourhood.cpp
      ${PROJECT_SOURCE_DIR}/Actions/Evalution.cpp
      ${PROJECT_SOURCE_DIR}/Actions/NoAction.cpp
      ${PROJECT_SOURCE_DIR}/Actions/Death.cpp
      ${PROJECT_SOURCE_DIR}/Actions/Move.cpp
      ${PROJECT_SOURCE_DIR}/Actions/Mating.cpp
      ${PROJECT_SOURCE_DIR}/Actions/Eating.cpp
      
   )

set(HEADERS
      ${PROJECT_SOURCE_DIR}/Entities/Cell.hpp
      ${PROJECT_SOURCE_DIR}/Entities/Object.hpp
      ${PROJECT_SOURCE_DIR}/Entities/Ocean.hpp
      ${PROJECT_SOURCE_DIR}/Entities/Stone.hpp
      ${PROJECT_SOURCE_DIR}/Entities/Reef.hpp
      ${PROJECT_SOURCE_DIR}/Entities/Prey.hpp
      ${PROJECT_SOURCE_DIR}/Entities/Predator.hpp
      ${PROJECT_SOURCE_DIR}/Entities/ApexPredator.cpp
      ${PROJECT_SOURCE_DIR}/Entities/Neighbourhood.hpp
      ${PROJECT_SOURCE_DIR}/Actions/Action.hpp
      ${PROJECT_SOURCE_DIR}/Actions/Evalution.hpp
      ${PROJECT_SOURCE_DIR}/Actions/NoAction.hpp
      ${PROJECT_SOURCE_DIR}/Actions/Death.hpp
      ${PROJECT_SOURCE_DIR}/Actions/Move.hpp
      ${PROJECT_SOURCE_DIR}/Actions/Mating.hpp
      ${PROJECT_SOURCE_DIR}/Actions/Eating.hpp
   )

if(PRINT_ACTIONS)
   add_compile_definitions(PRINT_ACTIONS)
endif()

add_executable(Ocean ${SRC} ${HEADERS})
