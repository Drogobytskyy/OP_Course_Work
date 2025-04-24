


CXX = g++
CXXFLAGS = -Wall -Wextra -Wpedantic -std=c++17

myprog: task2.cpp start_instruction.cpp
	$(CXX) $(CXXFLAGS) -o myprog task2.cpp start_instruction.cpp

myalg: algorithm.cpp globals.cpp ship_struct.cpp game_zone.cpp
	$(CXX) $(CXXFLAGS) -o myalg algorithm.cpp globals.cpp ship_struct.cpp game_zone.cpp
