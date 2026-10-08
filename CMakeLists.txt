cmake_minimum_required(VERSION 3.10)

# Définition du nom du projet
project(MonProjet CXX)

# Spécification de la version standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Récupère tous les fichiers .cpp présents dans le dossier "private"
file(GLOB SOURCES "private/*.cpp")

# Ajout de l'exécutable (main.cpp à la racine + tous les cpp du dossier private)
add_executable(POO main.cpp ${SOURCES})

# Indique au compilateur où chercher les fichiers d'en-tête (.hpp)
target_include_directories(POO PRIVATE public)