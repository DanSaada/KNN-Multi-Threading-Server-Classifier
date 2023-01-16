cmake_minimum_required(VERSION 3.20)
project(KNN-Server)

set(CMAKE_CXX_STANDARD 11)


add_executable(KNN-Server
        Distances/Canberra.h Distances/Canberra.cpp Classify/Catalog.h Classify/Catalog.cpp Distances/Chebyshev.h Distances/Chebyshev.cpp Classify/Database.cpp Classify/Database.h
        Distances/Distance.cpp Distances/Distance.h Distances/Euclidean.cpp Distances/Euclidean.h Server.cpp Distances/Manhattan.cpp Distances/Manhattan.h Distances/Minkowski.cpp
        Distances/Minkowski.h Server.h Classify/classificationLogic.cpp Classify/classificationLogic.h Commands/Command.h Commands/Command.cpp IO's/DefaultIO.h IO's/DefaultIO.cpp Commands/DisplayResultsCommand.cpp Commands/DisplayResultsCommand.h Commands/DownloadResultsCommand.cpp Commands/DownloadResultsCommand.h Commands/ExitCommand.cpp Commands/ExitCommand.h Commands/ClassifyDataCommand.h Commands/SettingsCommand.h Commands/UploadDataCommand.cpp Commands/ClassifyDataCommand.cpp Commands/SettingsCommand.cpp IO's/StandardIO.cpp IO's/StandardIO.h IO's/SocketIO.cpp IO's/SocketIO.h IO's/CLI.cpp IO's/CLI.h)