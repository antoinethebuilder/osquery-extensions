# Copyright (c) 2018 Trail of Bits, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

cmake_minimum_required(VERSION 3.10)
project(fwctl)

function(fwctlMain)
  set(project_libraries
    firewall
    hostsfile
  )

  set(project_common_source_files
    src/globals.h
    src/globals.cpp
    src/basetable.h
  )

  addOsqueryExtensionEx("HostBlacklistTable" "table" "HostBlacklist"
    SOURCES ${project_common_source_files} src/hostblacklist.h src/hostblacklist.cpp
    INCLUDEDIRS "${CMAKE_CURRENT_SOURCE_DIR}/src"
    MAININCLUDES hostblacklist.h
    LIBRARIES ${project_libraries}
  )

  addOsqueryExtensionEx("PortBlacklistTable" "table" "PortBlacklist"
    SOURCES ${project_common_source_files} src/portblacklist.h src/portblacklist.cpp
    INCLUDEDIRS "${CMAKE_CURRENT_SOURCE_DIR}/src"
    MAININCLUDES portblacklist.h
    LIBRARIES ${project_libraries}
  )

  # Only enable table tests on Linux and macOS
  if(UNIX)
    set(project_test_files

      tests/main.cpp
      tests/hostblacklist.cpp

      src/globals.h
      src/globals.cpp

      src/basetable.h

      src/hostblacklist.h
      src/hostblacklist.cpp

      src/portblacklist.h
      src/portblacklist.cpp
    )

    AddTest("tables" test_target_name ${project_test_files})

    target_include_directories("${test_target_name}" PRIVATE
      "${CMAKE_CURRENT_SOURCE_DIR}/src"
      "${TOB_EXTENSIONS_ROOT}"
    )

    target_compile_definitions("${test_target_name}" PRIVATE "${configuration_root}")

    target_compile_options("${test_target_name}" PRIVATE ${cxx_settings})

    target_link_libraries("${test_target_name}" PRIVATE
      firewall
      hostsfile
    )

    if(NOT APPLE)
      target_link_libraries("${test_target_name}" PRIVATE rt)
    endif()
  endif()
endfunction()

fwctlMain()
