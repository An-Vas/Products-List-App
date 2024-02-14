# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\ClientTesting_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\ClientTesting_autogen.dir\\ParseCache.txt"
  "CMakeFiles\\json_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\json_autogen.dir\\ParseCache.txt"
  "ClientTesting_autogen"
  "json_autogen"
  )
endif()
