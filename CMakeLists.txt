
cmake_minimum_required(VERSION 3.10)

project(MonProjet CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fichiers sources existants
file(GLOB SOURCES
    "private/*.cpp"
)

# Nouvelles classes Member
file(GLOB MEMBER_SOURCES
    "sources/Members/*.cpp"
)

# Construction du programme
add_executable(POO
    main.cpp
    ${SOURCES}
    ${MEMBER_SOURCES}
)

# Dossiers contenant les fichiers .hpp
target_include_directories(POO PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/public"
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
