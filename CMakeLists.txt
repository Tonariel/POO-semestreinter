
cmake_minimum_required(VERSION 3.10)

project(MonProjet CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fichiers sources de la bibliotheque
file(GLOB SOURCES
    "private/*.cpp"
)

# Fichiers sources des membres
file(GLOB MEMBER_SOURCES
    "private/Members/*.cpp"
)

# Creation de l'executable
add_executable(POO
    main.cpp
    ${SOURCES}
    ${MEMBER_SOURCES}
)

# Dossier des fichiers d'en-tete
target_include_directories(POO PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/public"
)
