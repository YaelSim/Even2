cmake_minimum_required(VERSION 3.15)
project(EVEN2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(EVEN2 main.cpp Server.h ClientHandler.h CacheManager.h MySerialServer.cpp MySerialServer.h MyTestClientHandler.cpp MyTestClientHandler.h Solver.h FileCacheManager.h FileCacheManager.cpp StringReverser.h StringReverser.cpp Main.h Matrix.h Searchable.h Searcher.h State.h Matrix.cpp MyClientHandler.h MyClientHandler.cpp DFS.h BFS.h BestFirstSearch.h AStar.h ObjectAdapter.h MyParallelServer.h MyParallelServer.cpp)