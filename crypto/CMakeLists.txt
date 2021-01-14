cmake_minimum_required(VERSION 3.0)
project(qjs-crypto)

set(DISABLE_WERROR TRUE CACHE BOOL "Disable -Werror flag" FORCE)

if(BUILD_SHARED_LIBS)
  set(LWS_WITH_SHARED TRUE)
  set(LWS_WITH_STATIC FALSE)
else(BUILD_SHARED_LIBS)
  set(LWS_WITH_SHARED FALSE)
  set(LWS_WITH_STATIC TRUE)
endif(BUILD_SHARED_LIBS)

set(DISABLE_WERROR ON)

if(NOT QUICKJS_INCLUDE_DIR)
  set(QUICKJS_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../..")
endif(NOT QUICKJS_INCLUDE_DIR)

if(QUICKJS_INCLUDE_DIR)
  include_directories(${QUICKJS_INCLUDE_DIR})
endif(QUICKJS_INCLUDE_DIR)

# Search OpenSSL
find_package(PkgConfig REQUIRED)
pkg_search_module(OPENSSL REQUIRED openssl)

function(make_shared_module FNAME)
  string(REGEX REPLACE "_" "-" NAME "${FNAME}")
  string(TOUPPER "${FNAME}" UNAME)

  message("Module: ${NAME}")
  set(TARGET_NAME quickjs-${NAME})

  add_library(${TARGET_NAME} SHARED ${FNAME}.c)

  target_link_libraries(${TARGET_NAME} ssl crypto quickjs dl)
  set_target_properties(${TARGET_NAME} PROPERTIES PREFIX "" BUILD_RPATH "${CMAKE_CURRENT_BINARY_DIR}" INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib" OUTPUT_NAME "${NAME}" # COMPILE_FLAGS "-fvisibility=hidden"
                                                  BUILD_RPATH "${CMAKE_BINARY_DIR};${CMAKE_CURRENT_BINARY_DIR};${CMAKE_BINARY_DIR}/quickjs;${CMAKE_CURRENT_BINARY_DIR}/quickjs")
  target_compile_definitions(${TARGET_NAME} PRIVATE -DJS_${UNAME}_MODULE=1)
  install(TARGETS ${TARGET_NAME} DESTINATION lib/quickjs)
endfunction()

if(NOT QUICKJS_INCLUDE_DIR)
  set(QUICKJS_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../..")
endif(NOT QUICKJS_INCLUDE_DIR)

if(QUICKJS_INCLUDE_DIR)
  include_directories(${QUICKJS_INCLUDE_DIR})
endif(QUICKJS_INCLUDE_DIR)

function(make_shared_module FNAME)
  string(REGEX REPLACE "_" "-" NAME "${FNAME}")
  string(TOUPPER "${FNAME}" UNAME)

  message("Module: ${NAME}")
  set(TARGET_NAME quickjs-${NAME})

  add_library(${TARGET_NAME} SHARED ${FNAME}.c)

  target_link_libraries(
    ${TARGET_NAME}
    ssl
    crypto
    quickjs
    dl)
  set_target_properties(
    ${TARGET_NAME}
    PROPERTIES
      PREFIX ""
      BUILD_RPATH "${CMAKE_CURRENT_BINARY_DIR}"
      INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib"
      OUTPUT_NAME "${NAME}"
      # COMPILE_FLAGS "-fvisibility=hidden"
      BUILD_RPATH
      "${CMAKE_BINARY_DIR};${CMAKE_CURRENT_BINARY_DIR};${CMAKE_BINARY_DIR}/quickjs;${CMAKE_CURRENT_BINARY_DIR}/quickjs"
  )
  target_compile_definitions(${TARGET_NAME} PRIVATE -DJS_${UNAME}_MODULE=1)
  install(TARGETS ${TARGET_NAME} DESTINATION lib/quickjs)
endfunction()

# file(GLOB JS_BINDINGS_SOURCES ${CMAKE_SOURCE_DIR}/src/js_*.cpp) foreach(MOD
# ${JS_BINDINGS_SOURCES}) string(REGEX REPLACE "\\.cpp" "" MOD "${MOD}")
# string(REGEX REPLACE ".*/js_" "" MOD "${MOD}") list(APPEND JS_BINDINGS_MODULES
# ${MOD}) endforeach(MOD ${JS_BINDINGS_SOURCES}) message("JS_BINDINGS_MODULES:
# ${JS_BINDINGS_MODULES}") foreach(JS_MODULE ${JS_BINDINGS_MODULES})
# make_shared_module(${JS_MODULE}) endforeach()

file(GLOB JS_BINDINGS_SOURCES qjs-crypto.c qjs-crypto.h)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
 
# Main
add_library(quickjs-crypto MODULE ${JS_BINDINGS_SOURCES})
set_target_properties(
  quickjs-crypto
  PROPERTIES COMPILE_FLAGS "-fvisibility=hidden"
             PREFIX ""
             OUTPUT_NAME "qjs-crypto"
             # OUTPUT_NAME_DEBUG "qjs-crypto-debug"
)
target_compile_definitions(quickjs-crypto PRIVATE -DJS_SHARED_LIBRARY=1 -DJS_BINDINGS_INIT_MODULE=1)
target_link_libraries(quickjs-crypto ssl crypto quickjs)

install(TARGETS quickjs-crypto DESTINATION lib/quickjs)

# link
