##################################################################
# Копирайт (C) Антон Ковалев (vertver), 2020. Все права защищены.
# TemaVKBot - Бот, который дополнит ваши беседы бесполезным трепом
# GPLv3 лицензия
##################################################################
# Данный бот создан как просто шутка, и не стремится оскорбить
# кого-либо (как самого Артемия Лебедева, так и его студию 
# дизайна). Код бота распространяется под свободной лицензией 
# GPLv3 для того, чтобы при создание порта на другие платформы
# от других людей код также был бы открыт и прозрачен для
# программиста. 
##################################################################
# Автору бота не требуется никаких пожертвований, он сам себя
# сможет обеспечить. Но чем вы точно сможете помочь автору
# проекта - так это pull request'ами и issue на гитхабе. Так
# вы и людям поможете избавиться от багов и говнокода, так и
# автору "спасибо" таким образом скажите.
##################################################################
cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
project(TemaVKBot C CXX)

include(ExternalProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(WIN32)
    if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        set(LIB_DEBUG "d")
    endif()        
endif()

##################################################################
# Задаем базовые переменные
##################################################################
set(RERUN_STUDIO 0)         # для тех, кто пользуется гуишным CMake'ом и не хочет использовать тот, что в студии
set(EXTERNAL_SOURCES_DIR ${CMAKE_BINARY_DIR}/external_sources)

set(CURL_REPOSITORY https://github.com/curl/curl.git)
set(CURL_SOURCE_DIR ${EXTERNAL_SOURCES_DIR}/curl)
set(CURL_INSTALL_DIR ${CMAKE_BINARY_DIR}/install/curl)
set(CURL_INCLUDE_DIR ${CURL_SOURCE_DIR}/include/)

message("libcurl include directory: " ${CURL_INCLUDE_DIR})

set(APP_NAME TemaVKBot)

##################################################################
# Скачиваем либы
##################################################################
ExternalProject_Add(curl
    PREFIX curl
    GIT_REPOSITORY ${CURL_REPOSITORY}
    GIT_PROGRESS TRUE
    SOURCE_DIR ${CURL_SOURCE_DIR}
    BINARY_DIR ${CMAKE_BINARY_DIR}/curl
    INSTALL_DIR ${CURL_INSTALL_DIR}
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${CURL_INSTALL_DIR} -DCURL_STATICLIB=1
    UPDATE_COMMAND ""
    INSTALL_COMMAND ${CMAKE_COMMAND} --build ${CURL_SOURCE_DIR}
)

set(CURL_LIBRARIES_DIR ${CURL_INSTALL_DIR}/lib)
set(CURL_LIBRARY ${CURL_INSTALL_DIR}/lib/libcurl${LIB_DEBUG}_imp.lib)

##################################################################
# Создаем директорию с исходниками бота
##################################################################
set(VKBOT_SOURCES_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/
)

include_directories(${CURL_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)        # Потому что я очень ленивый

file(GLOB VKBOT_SOURCES_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/vkapi/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/vkapi/*.h
)

##################################################################
# Создаем конечный таргет с нужными нами сорсами
##################################################################
add_executable(${APP_NAME} 
    ${VKBOT_SOURCES_FILES}
)

add_dependencies(${APP_NAME}
    curl
)

target_link_libraries(${APP_NAME} 
    ${CURL_LIBRARY}
)

if (WIN32)
    target_link_libraries(${APP_NAME} 
        Ws2_32.lib
        Imm32.lib
        WinMM.lib
    )
endif()

message("VKBOT source directories: " ${VKBOT_SOURCES_DIRS})