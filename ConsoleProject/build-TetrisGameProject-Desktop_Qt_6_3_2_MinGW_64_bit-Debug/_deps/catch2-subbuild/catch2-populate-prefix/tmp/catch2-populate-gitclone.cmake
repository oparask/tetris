# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

if(EXISTS "C:/esi_2024/Q4/DEV4/60085_55996_tetris/ConsoleProject/build-TetrisGameProject-Desktop_Qt_6_3_2_MinGW_64_bit-Debug/_deps/catch2-subbuild/catch2-populate-prefix/src/catch2-populate-stamp/catch2-populate-gitclone-lastrun.txt" AND EXISTS "C:/esi_2024/Q4/DEV4/60085_55996_tetris/ConsoleProject/build-TetrisGameProject-Desktop_Qt_6_3_2_MinGW_64_bit-Debug/_deps/catch2-subbuild/catch2-populate-prefix/src/catch2-populate-stamp/catch2-populate-gitinfo.txt" AND
  "C:/esi_2024/Q4/DEV4/60085_55996_tetris/ConsoleProject/build-TetrisGameProject-Desktop_Qt_6_3_2_MinGW_64_bit-Debug/_deps/catch2-subbuild/catch2-populate-prefix/src/catch2-populate-stamp/catch2-populate-gitclone-lastrun.txt" IS_NEWER_THAN "C:/esi_2024/Q4/DEV4/60085_55996_tetris/ConsoleProject/build-TetrisGameProject-Desktop_Qt_6_3_2_MinGW_64_bit-Debug/_deps/catch2-subbuild/catch2-populate-prefix/src/catch2-populate-stamp/catch2-populate-gitinfo.txt")
  message(STATUS
    "Avoiding repeated git clone, stamp file is up to date: "
    "'C:/esi_2024/Q4/DEV4/60085_55996_tetris/ConsoleProject/build-TetrisGameProject-Desktop_Qt_6_3_2_MinGW_64_bit-Debug/_deps/catch2-subbuild/catch2-populate-prefix/src/catch2-populate-stamp/catch2-populate-gitclone-lastrun.txt'"
  )
  return()
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E rm -rf "C:/esi_2024/Q4/DEV4/60085_55996_tetris/ConsoleProject/build-TetrisGameProject-Desktop_Qt_6_3_2_MinGW_64_bit-Debug/_deps/catch2-src"
  RESULT_VARIABLE error_code
)
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: 'C:/esi_2024/Q4/DEV4/60085_55996_tetris/ConsoleProject/build-TetrisGameProject-Desktop_Qt_6_3_2_MinGW_64_bit-Debug/_deps/catch2-src'")
endif()

# try the clone 3 times in case there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
while(error_code AND number_of_tries LESS 3)
  execute_process(
    COMMAND "C:/Program Files/Git/cmd/git.exe" 
            clone --no-checkout --config "advice.detachedHead=false" "https://github.com/catchorg/Catch2.git" "catch2-src"
    WORKING_DIRECTORY "C:/esi_2024/Q4/DEV4/60085_55996_tetris/ConsoleProject/build-TetrisGameProject-Desktop_Qt_6_3_2_MinGW_64_bit-Debug/_deps"
    RESULT_VARIABLE error_code
  )
  math(EXPR number_of_tries "${number_of_tries} + 1")
endwhile()
if(number_of_tries GREATER 1)
  message(STATUS "Had to git clone more than once: ${number_of_tries} times.")
endif()
if(error_code)
  message(FATAL_ERROR "Failed to clone repository: 'https://github.com/catchorg/Catch2.git'")
endif()

execute_process(
  COMMAND "C:/Program Files/Git/cmd/git.exe" 
          checkout "v3.3.1" --
  WORKING_DIRECTORY "C:/esi_2024/Q4/DEV4/60085_55996_tetris/ConsoleProject/build-TetrisGameProject-Desktop_Qt_6_3_2_MinGW_64_bit-Debug/_deps/catch2-src"
  RESULT_VARIABLE error_code
)
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: 'v3.3.1'")
endif()

set(init_submodules TRUE)
if(init_submodules)
  execute_process(
    COMMAND "C:/Program Files/Git/cmd/git.exe" 
            submodule update --recursive --init 
    WORKING_DIRECTORY "C:/esi_2024/Q4/DEV4/60085_55996_tetris/ConsoleProject/build-TetrisGameProject-Desktop_Qt_6_3_2_MinGW_64_bit-Debug/_deps/catch2-src"
    RESULT_VARIABLE error_code
  )
endif()
if(error_code)
  message(FATAL_ERROR "Failed to update submodules in: 'C:/esi_2024/Q4/DEV4/60085_55996_tetris/ConsoleProject/build-TetrisGameProject-Desktop_Qt_6_3_2_MinGW_64_bit-Debug/_deps/catch2-src'")
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy "C:/esi_2024/Q4/DEV4/60085_55996_tetris/ConsoleProject/build-TetrisGameProject-Desktop_Qt_6_3_2_MinGW_64_bit-Debug/_deps/catch2-subbuild/catch2-populate-prefix/src/catch2-populate-stamp/catch2-populate-gitinfo.txt" "C:/esi_2024/Q4/DEV4/60085_55996_tetris/ConsoleProject/build-TetrisGameProject-Desktop_Qt_6_3_2_MinGW_64_bit-Debug/_deps/catch2-subbuild/catch2-populate-prefix/src/catch2-populate-stamp/catch2-populate-gitclone-lastrun.txt"
  RESULT_VARIABLE error_code
)
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: 'C:/esi_2024/Q4/DEV4/60085_55996_tetris/ConsoleProject/build-TetrisGameProject-Desktop_Qt_6_3_2_MinGW_64_bit-Debug/_deps/catch2-subbuild/catch2-populate-prefix/src/catch2-populate-stamp/catch2-populate-gitclone-lastrun.txt'")
endif()
