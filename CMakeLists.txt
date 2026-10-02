cmake_minimum_required(VERSION 3.10)

# Définition du nom du projet
project(MonProjet CXX)

# Spécification de la version standard C++ (C++17 utilisé ici par défaut)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Ajout de l'exécutable avec les fichiers sources pertinents
add_executable(mon_programme main.cpp Student.cpp)