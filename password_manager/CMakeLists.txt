cmake_minimum_required(VERSION 3.2)
project(PasswordManager)

include_directories(include)

set(PASSWORD_MANAGER_SOURCES
    src/PasswordManager.cpp
)

set(PASSWORD_MANAGER_HEADERS
    include/PasswordManager/PasswordManager.h
)

add_executable(${PROJECT_NAME}
    main.cpp
    ${PASSWORD_MANAGER_SOURCES}
    ${PASSWORD_MANAGER_HEADERS}
)