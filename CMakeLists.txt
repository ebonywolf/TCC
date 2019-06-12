cmake_minimum_required ( VERSION 3.3 )
project(Tcc)

set (CMAKE_CXX_STANDARD 14)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_FLAGS_RELEASE "-O3")

file(GLOB lib_srcs "*.cpp" "IGMN/*.cpp" "GeneticAI/*.cpp")



include_directories( NeuralNetwork GeneticAI include/ )

list(REMOVE_ITEM lib_srcs ${CMAKE_CURRENT_SOURCE_DIR}/GeneticAI/main.cpp)

list(REMOVE_ITEM lib_srcs ${CMAKE_CURRENT_SOURCE_DIR}/NeuralNetwork/basicNNmain.cpp)
list(REMOVE_ITEM lib_srcs ${CMAKE_CURRENT_SOURCE_DIR}/NeuralNetwork/main.cpp)


message( ${lib_srcs} )
add_executable(TCC main.cpp ${lib_srcs} )

target_link_libraries( TCC boost_system boost_iostreams pthread jsoncpp  ) 
