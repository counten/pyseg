cmake_minimum_required(VERSION 2.5)
set(PROJECT_NAME cSeg)
set(LIB_NAME cseg)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD  11)

include_directories(src)

add_library(
        ${LIB_NAME}
        SHARED
        src/friso.c
        src/friso.h
        src/friso_API.h
        src/friso_array.c
        src/friso_ctype.c
        src/friso_ctype.h
        src/friso_GBK.c
        src/friso_hash.c
        src/friso_lexicon.c
        src/friso_link.c
        src/friso_string.c
        src/friso_UTF8.c
)

#add_test(
#        src/tst-array.c
#        src/tst-friso.c
#        src/tst-hash.c
#        src/tst-lex.c
#        src/tst-link.c
#        src/tst-split.c
#        src/tst-string.c
#)

#link_libraries(${LIB_NAME} m)
#add_executable(
#        ${PROJECT_NAME}
#)