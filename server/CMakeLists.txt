cmake_minimum_required (VERSION 3.5)
project(xalgames_server)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

message(${CMAKE_BUILD_TYPE})
if(CMAKE_BUILD_TYPE MATCHES Debug)
  add_compile_definitions(DEBUG)
endif()

#add_subdirectory(${PROJECT_SOURCE_DIR}/extlibs/rapidyaml ryml)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories("${PROJECT_SOURCE_DIR}/external_libs/websocketpp")
include_directories("${PROJECT_SOURCE_DIR}/external_libs/asio/asio/include")
include_directories("${PROJECT_SOURCE_DIR}/external_libs/sol2/include")
include_directories("${PROJECT_SOURCE_DIR}/external_libs/json/include")
include_directories(/usr/include/lua5.4/)

#link_directories(${PROJECT_SOURCE_DIR}/extlibs/cryptopp)

set(
  SOURCES
  "${PROJECT_SOURCE_DIR}/src/system/engine/LuaEngine.cpp"
  "${PROJECT_SOURCE_DIR}/src/system/game_loop/VariableTimestep.cpp"
  "${PROJECT_SOURCE_DIR}/src/system/message_queue/JSONMessagesQueue.cpp"
  "${PROJECT_SOURCE_DIR}/src/system/message_queue/LuaMessagesQueue.cpp"
  # "${PROJECT_SOURCE_DIR}/src/system/phase/Game.cpp"
  "${PROJECT_SOURCE_DIR}/src/system/phase/lobby/Lobby.cpp"
  "${PROJECT_SOURCE_DIR}/src/system/phase/lobby/LuaLobby.cpp"
  "${PROJECT_SOURCE_DIR}/src/system/session/Room.cpp"
  "${PROJECT_SOURCE_DIR}/src/system/session/RoomPool.cpp"
  "${PROJECT_SOURCE_DIR}/src/network/Server.cpp"
  "${PROJECT_SOURCE_DIR}/src/utils/CmdArguments.cpp"
  "${PROJECT_SOURCE_DIR}/src/main.cpp"
)

if(WIN32) # Check if we are on Windows
  if( ${CMAKE_SYSTEM_VERSION} EQUAL 10)
    add_compile_definitions(_WIN32_WINNT=0x0A00)
  endif()
elseif(UNIX)
  # Nothing special required
else()
  message(SEND_ERROR "You are on an unsupported platform! (Not Win32, Mac OS X or Unix)")
endif(WIN32)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(USING_GCC TRUE)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(USING_CLANG TRUE)
endif()

if(USING_GCC OR USING_CLANG)
  add_compile_options(-std=c++20 -g -pedantic -Wall -Wl,-rpath)
endif()

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_executable(
    "xalgames_server"
    ${SOURCES}
)

target_link_libraries("xalgames_server" pthread lua5.4 stdc++fs)