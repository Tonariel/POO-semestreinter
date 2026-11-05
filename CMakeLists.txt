
cmake_minimum_required(VERSION 3.10)

project(POO_Remise3 LANGUAGES CXX)

# Version du langage
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCES
    private/Books/AudioBook.cpp
    private/Books/Book.cpp
    private/Books/EBook.cpp
    private/Books/PhysicalBook.cpp
    private/Library.cpp
    private/Members/Member.cpp
    private/Members/StudentMember.cpp
    private/Members/TeacherMember.cpp
)

# Creation de l'executable
add_executable(POO
    main.cpp
    ${SOURCES}
)

# Dossier des fichiers d'en-tete
target_include_directories(POO PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/public"
)

# Avertissements de compilation
if(MSVC)
    target_compile_options(POO PRIVATE /W4)
else()
    target_compile_options(POO PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endif()
