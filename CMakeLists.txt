cmake_minimum_required(VERSION 3.0)
project(icarus VERSION 0.0.0.0)

add_definitions(-DVERSION_MAJOR="${PROJECT_VERSION_MAJOR}")
add_definitions(-DVERSION_MINOR="${PROJECT_VERSION_MINOR}")
add_definitions(-DVERSION_PATCH="${PROJECT_VERSION_PATCH}")
add_definitions(-DVERSION_TWEAK="${PROJECT_VERSION_TWEAK}")

add_definitions(-DSOCI_USE_BOOST=1)

SET (CMAKE_C_COMPILER               "/usr/bin/clang")
SET (CMAKE_CXX_COMPILER             "/usr/bin/clang++")

if(NOT WIN32)
	string(ASCII 27 Esc)
	set(ColourReset "${Esc}[m")
	set(ColourBold  "${Esc}[1m")
	set(Red         "${Esc}[31m")
	set(Green       "${Esc}[32m")
	set(Yellow      "${Esc}[33m")
	set(Blue        "${Esc}[34m")
	set(Magenta     "${Esc}[35m")
	set(Cyan        "${Esc}[36m")
	set(White       "${Esc}[37m")
	set(BoldRed     "${Esc}[1;31m")
	set(BoldGreen   "${Esc}[1;32m")
	set(BoldYellow  "${Esc}[1;33m")
	set(BoldBlue    "${Esc}[1;34m")
	set(BoldMagenta "${Esc}[1;35m")
	set(BoldCyan    "${Esc}[1;36m")
	set(BoldWhite   "${Esc}[1;37m")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")

set(CMAKE_MODULE_PATH ${icarus_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

add_definitions(-DOUTPUT_DIRECTORY="${CMAKE_BINARY_DIR}")
add_definitions(-DSOURCE_DIRECTORY="${CMAKE_CURRENT_SOURCE_DIR}")

#
# SOCI
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

set(SOCI_LIBRARY_DIR "$ENV{HOME}/libs/soci3.2.3")
find_library(soci_core soci_core REQUIRED PATHS "${SOCI_LIBRARY_DIR}" PATH_SUFFIXES lib lib64)
if("${soci_core}" STREQUAL "soci_core-NOTFOUND")
	message(FATAL_ERROR "Component not found ${Red}soci_core${ColourReset}.")
endif()

find_library(soci_mysql soci_mysql REQUIRED PATHS "${SOCI_LIBRARY_DIR}" PATH_SUFFIXES lib lib64)
if("${soci_mysql}" STREQUAL "soci_mysql-NOTFOUND")
	message(FATAL_ERROR "Component not found ${Red}soci_mysql${ColourReset}.")
endif()

# find_library(soci_postgresql soci_postgresql REQUIRED PATHS "${SOCI_LIBRARY_DIR}" PATH_SUFFIXES lib lib64)
# if("${soci_postgresql}" STREQUAL "soci_postgresql-NOTFOUND")
# 	message(FATAL_ERROR "Component not found ${Red}soci_postgresql${ColourReset}.")
# endif()

message("-- SOCI")
message("--   core: ${soci_core}")
message("--   mysql: ${soci_mysql}")
# message("--   postgresql: ${soci_postgresql}")
message("")

include_directories(
	"${SOCI_LIBRARY_DIR}/include"
)

#
# BOOST
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

set(BOOST_ROOT "$ENV{HOME}/libs/libboost_1_60_0")
set(BOOST_INCLUDEDIR "${BOOST_ROOT}/include")
set(BOOST_LIBRARYDIR "${BOOST_ROOT}/lib")
find_package(Boost REQUIRED log_setup log system coroutine context filesystem program_options regex date_time unit_test_framework)
message("--   include: ${Boost_INCLUDE_DIRS}")
message("--   library: ${Boost_LIBRARY_DIRS}")
message("")
add_definitions(-DBOOST_LOG_DYN_LINK=1)

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

#
# OpenSSL
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

find_package(OpenSSL REQUIRED)
message("-- OpenSSL")
message("--   include dir: ${OPENSSL_INCLUDE_DIR}")
message("--   SSL libraries: ${OPENSSL_SSL_LIBRARIES}")
message("--   crypto libraries: ${OPENSSL_CRYPTO_LIBRARIES}")
message("")
include_directories(${OPENSSL_INCLUDE_DIR})

#
# libmemcached
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

set(LIBMEMCACHED_ROOT "$ENV{HOME}/libs/libmemcached")
set(LIBMEMCACHED_INCLUDE_DIR "${LIBMEMCACHED_ROOT}/include")
find_library(memcached memcached REQUIRED PATHS "${LIBMEMCACHED_ROOT}" PATH_SUFFIXES lib lib64 NAMES libmemcached.a libmemcached)
if("${memcached}" STREQUAL "libmemcached-NOTFOUND")
	message("libmemcached searched in ${Red}${LIBMEMCACHED_ROOT}${ColourReset}")
	message(FATAL_ERROR "Component not found ${Red}libmemcached${ColourReset}.")
endif()

find_library(memcachedutil memcachedutil REQUIRED PATHS "${LIBMEMCACHED_ROOT}" PATH_SUFFIXES lib lib64 NAMES libmemcachedutil.a libmemcachedutil)
if("${memcachedutil}" STREQUAL "memcachedutil-NOTFOUND")
	message("memcachedutil searched in ${Red}${LIBMEMCACHED_ROOT}${ColourReset}")
	message(FATAL_ERROR "Component not found ${Red}memcachedutil${ColourReset}.")
endif()

message("-- memcached")
message("--        memcached: ${memcached}")
message("--    memcachedutil: ${memcachedutil}")
message("--      include dir: ${LIBMEMCACHED_INCLUDE_DIR}")
message("")

include_directories(
	"${LIBMEMCACHED_INCLUDE_DIR}"
)

#
# JSONCPP
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

set(JSONCPP_ROOT "$ENV{HOME}/libs/jsoncpp1.7.2")

find_library(jsoncpp jsoncpp REQUIRED PATHS "${JSONCPP_ROOT}" PATH_SUFFIXES lib lib64)
if("${jsoncpp}" STREQUAL "jsoncpp-NOTFOUND")
	message(FATAL_ERROR "Component not found ${Red}jsoncpp${ColourReset}.")
endif()
message("-- JSONCPP")
message("--   include dir: ${JSONCPP_ROOT}/include")
message("--       library: ${jsoncpp}")
message("")
include_directories(${JSONCPP_ROOT}/include)

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

set(SOURCE_FILES
	include/icarus/log.h
	src/icarus/log.cpp

	# ---

	include/icarus/http/headers.h
	include/icarus/statuses.h
	include/icarus/http/cookies.h
	include/icarus/http/exceptions.h
	include/icarus/http/request.h
	include/icarus/http/response.h
	include/icarus/http/client.h
	include/icarus/http/dataconversion.h

	src/icarus/http/headers.cpp
	src/icarus/statuses.cpp
	src/icarus/http/cookies.cpp
	src/icarus/http/exceptions.cpp
	src/icarus/http/request.cpp
	src/icarus/http/response.cpp
	src/icarus/http/client.cpp
	src/icarus/http/dataconversion.cpp

	# ---

	include/icarus/http/fcgi/request.h
	include/icarus/http/fcgi/response.h
	include/icarus/http/fcgi/application.h
	include/icarus/http/fcgi/client.h

	src/icarus/http/fcgi/request.cpp
	src/icarus/http/fcgi/response.cpp
	src/icarus/http/fcgi/application.cpp
	src/icarus/http/fcgi/client.cpp

	# ---

	include/icarus/routes/data.h
	include/icarus/routes/parser.h
	include/icarus/routes/compiler.h
	include/icarus/routes/routeswriter.h
	include/icarus/routes/exceptions.h
	include/icarus/routes/fieldtypes.h

	src/icarus/routes/data.cpp
	src/icarus/routes/parser.cpp
	src/icarus/routes/compiler.cpp
	src/icarus/routes/routeswriter.cpp
	src/icarus/routes/exceptions.cpp
	src/icarus/routes/fieldtypes.cpp

	# ---

	src/icarus/memcached.cpp
	include/icarus/memcached.h

	include/icarus/session/session.h
	src/icarus/session/session.cpp

	# ---

	include/icarus/interfaces.h

	include/icarus/action.h
	include/icarus/result.h
	include/icarus/exceptions.h
	include/icarus/action.h
	include/icarus/application.h
	include/icarus/config.h
	include/icarus/multithreadedapplication.h

	src/icarus/action.cpp
	src/icarus/result.cpp
	src/icarus/exceptions.cpp
	src/icarus/action.cpp
	src/icarus/application.cpp
	src/icarus/config.cpp
	src/icarus/multithreadedapplication.cpp

	# ---

	include/icarus/db/databases.h
	src/icarus/db/databases.cpp

	# ---

	include/icarus/migrations/manager.h
	include/icarus/migrations/migration.h
	include/icarus/migrations/soci.h
	include/icarus/migrations/runner.h


	src/icarus/migrations/manager.cpp
	src/icarus/migrations/migration.cpp
	src/icarus/migrations/soci.cpp
	include/icarus/migrations/runner.cpp

	include/icarus/http/querystring.h
	src/icarus/http/querystring.cpp

	include/icarus/general.h
	src/icarus/general.cpp

	include/icarus/typeconversion.h
	src/icarus/typeconversion.cpp
	include/icarus/typeconversion-commons.h

	include/icarus/content.h
	src/icarus/content.cpp

	include/icarus/dispatcher.h
	src/icarus/dispatcher.cpp

	src/icarus/session/memcached.cpp
	include/icarus/session/memcached.h

	src/icarus/digests.cpp
	include/icarus/digests.h
)

include_directories("${CMAKE_SOURCE_DIR}/include")

set(ICARUS_LIBRARIES
	boost_log_setup
	boost_log
	boost_system
	boost_date_time
	boost_coroutine
	boost_context
	boost_filesystem
	boost_program_options
	boost_regex
	boost_locale
	boost_thread

	${soci_core}
	${soci_mysql}

	fcgi
	fcgi++

	${memcached}
	${memcachedutil}

	rt

	pthread
	minotaur

	${OPENSSL_SSL_LIBRARIES}
	${OPENSSL_CRYPTO_LIBRARIES}
	${jsoncpp}
)

include_directories(${CMAKE_SOURCE_DIR}/src)

add_library(icarus SHARED
	${SOURCE_FILES}
)

add_library(minotaur SHARED

	include/minotaur/fileinfo.h

	include/minotaur/compiler.h
	include/minotaur/parser.h
	include/minotaur/cpptemplatebuilder.h
	include/minotaur/exceptions.h
	include/minotaur/metainfo.h
	include/minotaur/templatebuilder.h

	src/minotaur/compiler.cpp
	src/minotaur/parser.cpp
	src/minotaur/cpptemplatebuilder.cpp
	src/minotaur/exceptions.cpp
	src/minotaur/metainfo.cpp
	src/minotaur/templatebuilder.cpp
)

target_link_libraries(icarus
	${ICARUS_LIBRARIES}
)

set_target_properties(icarus PROPERTIES LINKER_LANGUAGE CXX)

add_executable(mntr
	src/minotaur/mntr.cpp
)

target_link_libraries(mntr
	boost_system
	boost_filesystem
	boost_program_options
	boost_regex

	icarus
)

add_executable(icarus-routes
	src/icarus/routes/main.cpp
)

target_link_libraries(icarus-routes
	boost_system
	boost_filesystem
	boost_program_options
	boost_regex

	${jsoncpp}
	icarus
)

# Test configuration thanks to http://neyasystems.com/an-engineers-guide-to-unit-testing-cmake-and-boost-unit-tests/

enable_testing()

add_definitions(-DTEST_RESOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/test/resources")
set(TEST_OUTPUT ${CMAKE_BINARY_DIR}/tests)
message("-- Tests")

file(GLOB_RECURSE TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} test/icarus/*.cpp)
foreach (testSrc ${TEST_SRCS})
	get_filename_component(testName ${testSrc} NAME_WE)
	string(REPLACE "test/" "" testPackage "${testSrc}")
	string(REPLACE "${testName}.cpp" "" testPackage "${testPackage}")
	string(REPLACE "/" "_" testPackage "${testPackage}")
	set(testName "test_${testPackage}${testName}")
	message("--   ${testSrc} as ${testName}")

	add_executable(${testName} ${testSrc})

	target_link_libraries(${testName}
		${Boost_LIBRARIES}

		icarus
		${jsoncpp}
	)

	set_target_properties(${testName} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TEST_OUTPUT})

	add_test(NAME ${testName}
		WORKING_DIRECTORY ${TEST_OUTPUT}
		COMMAND ${TEST_OUTPUT}/${testName}
		)
endforeach (testSrc)

file(GLOB_RECURSE TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} test/minotaur/*.cpp)
foreach (testSrc ${TEST_SRCS})
	get_filename_component(testName ${testSrc} NAME_WE)
	string(REPLACE "test/" "" testPackage "${testSrc}")
	string(REPLACE "${testName}.cpp" "" testPackage "${testPackage}")
	string(REPLACE "/" "_" testPackage "${testPackage}")
	set(testName "test_${testPackage}${testName}")
	message("--   ${testSrc} as ${testName}")

	add_executable(${testName} ${testSrc})

	target_link_libraries(${testName}
		${Boost_LIBRARIES}

		icarus
		minotaur
	)

	set_target_properties(${testName} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TEST_OUTPUT})

	add_test(NAME ${testName}
		WORKING_DIRECTORY ${TEST_OUTPUT}
		COMMAND ${TEST_OUTPUT}/${testName}
		)
endforeach (testSrc)
message("")
