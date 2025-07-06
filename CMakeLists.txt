cmake_minimum_required(VERSION 3.14)
project(mi_proyecto)

set(CMAKE_CXX_STANDARD 17)
enable_testing()

# Agregar raylib como subdirectorio
set(SDL2_DISABLE_INSTALL ON CACHE BOOL "" FORCE)
add_subdirectory(external/raylib)

# === Archivos fuente comunes ===
set(MODEL_SOURCES
  src/Blocks/Bloque.cpp
  src/Inventory/Inventario.cpp
  src/Player/Player.cpp
  src/Position/Position.cpp
  src/GameController/GameController.cpp
  src/GameView/GameView.cpp
)

# === Ejecutable de juego ===
add_executable(juego
  src/main.cpp
  ${MODEL_SOURCES}
)

target_include_directories(juego PRIVATE
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/external/raylib/src
)

target_link_libraries(juego PRIVATE raylib)

if(UNIX)
  target_link_libraries(juego PRIVATE m pthread dl GL X11)
endif()

# === Ejecutable de tests ===
set(TEST_SOURCES
  test/testInventario.cpp
  test/testPlayer.cpp
)

add_executable(tests
  ${TEST_SOURCES}
  ${MODEL_SOURCES}
)

target_include_directories(tests PRIVATE
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/external/raylib/src
)

target_link_libraries(tests PRIVATE raylib)

if(UNIX)
  target_link_libraries(tests PRIVATE m pthread dl GL X11)
endif()

add_test(NAME doctest_tests COMMAND tests)

