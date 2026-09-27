# CMakeList.txt : CMake project for malevola, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.10)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

project ("malevola")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

set(RAYLIB_VERSION 6.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # if not raylib already installed
    set(FETCHCONTENT_QUIET NO)
    FetchContent_MakeAvailable(raylib)
  endif()
endif()

# Add source to this project's executable.
add_executable (malevola "src/game.cpp" "includes/game.h" "malevola.cpp" "includes/player.h" "src/player.cpp" "includes/sprite.h" "src/sprite.cpp" "includes/texture_manager.h" "src/texture_manager.cpp" "includes/world.h" "src/world.cpp" "includes/tile_registry.h" "src/tile_registry.cpp" "includes/constants.h" "includes/item_registry.h" "src/item_registry.cpp")

target_include_directories(malevola PRIVATE "includes")

target_link_libraries(malevola PRIVATE raylib)

# adds a custom shell command to pre or post build
add_custom_command(TARGET malevola POST_BUILD # specify target and when PRE_BUILD/POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory #  ${CMAKE_COMMAND} = C:/Program Files/CMake/bin/cmake.exe and -E tells the exe to only use one of the built-ins
    # copy_directory is the specific built-in command being invoked
    ${CMAKE_SOURCE_DIR}/resources # 1st (source folder) argument to copy_directory ${CMAKE_SOURCE_DIR} = project root
    $<TARGET_FILE_DIR:malevola>/resources # 2nd argument <destnation> is a generator expression (means it gets set at generator stage (after the initial configuration which is where {} vars get set))
    # and TARGET_FILE_DIR:malevola basically means the folder where exe is
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET malevola PROPERTY CXX_STANDARD 20)
endif()