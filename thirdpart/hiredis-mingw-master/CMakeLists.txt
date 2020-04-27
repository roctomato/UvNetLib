cmake_minimum_required(VERSION 3.8)
project(hiredis)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES
        async.c
        dict.c
        hiredis.c
        net.c
        read.c
        sds.c
        async.c
        crossplatform.c
        net_win32.c)

set(CMAKE_C_VISIBILITY_PRESET hidden)

if (WIN32)
    add_definitions(-D_WIN32_WINNT=0x0600)
    add_definitions(-DNO_OLDNAMES)
endif()

add_library(hiredis STATIC ${SOURCE_FILES})

if (WIN32)
    target_link_libraries(hiredis ws2_32)
endif()

install(TARGETS hiredis
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

set(INSTALL_INCLUDES async.h crossplatform.h dict.h fmacros.h hiredis.h net.h read.h sds.h sdsalloc.h)
install(FILES ${INSTALL_INCLUDES} DESTINATION include)