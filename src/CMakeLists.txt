# CMakeList.txt : CMake project for Pong, include source and define
# project specific logic here.
#

#set(TGUI_STATIC_LIBRARIES TRUE)
#find_package(TGUI CONFIG REQUIRED)
find_package(SFML COMPONENTS system window graphics network audio)
find_package(CMakeRC CONFIG REQUIRED)

# recursivly register all game resources in order to compile them in to cpp files
file(GLOB_RECURSE GAME_RESOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/resources/*)

cmrc_add_resource_library(game-resources ALIAS game::rc NAMESPACE game_resources WHENCE ${CMAKE_SOURCE_DIR} ${GAME_RESOURCES})

# recursivly add cpp files compile list
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS *.cpp)

# Add source to this project's executable.
add_executable (ShootEmUp WIN32 ${SRC_FILES})

set(LIBS sfml-graphics sfml-audio sfml-system sfml-network sfml-window game::rc)

if (CMAKE_HOST_WIN32)
  list(APPEND LIBS sfml-main)
endif()

target_link_libraries(ShootEmUp PRIVATE ${LIBS})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ShootEmUp PROPERTY CXX_STANDARD 20)
endif()


# TODO: Add tests and install targets if needed.
