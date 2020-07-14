cmake_minimum_required(VERSION 3.16)
project(test_allegro C)

set(CMAKE_C_STANDARD 11)

set(ALLEGRO_DIR "/usr/local/Cellar/allegro/5.2.6.0")
include_directories(${ALLEGRO_DIR}/include)
link_directories(${ALLEGRO_DIR}/lib)

add_executable(test_allegro main.c LS_allegro.c LS_allegro.h game.c game.h race/race.c race/race.h models/base.h models/car.h models/championship.h models/gps.h models/pieces.h models/player.h models/racer.h interface/interface.c interface/interface.h file/file.c file/file.h configuration/configuration.c configuration/configuration.h)

file(GLOB LIBRARIES ${ALLEGRO_DIR}/lib/*.dylib)
message("LIBRARIES = ${LIBRARIES}")

TARGET_LINK_LIBRARIES(test_allegro ${LIBRARIES})