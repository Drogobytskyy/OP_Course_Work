

CXX = g++
CXXFLAGS = -Wall -Wextra -Wpedantic -std=c++17

course: task2.cpp start_instruction.cpp globals.cpp ship_struct.cpp game_zone.cpp game.cpp
	$(CXX) $(CXXFLAGS) -o course task2.cpp start_instruction.cpp globals.cpp ship_struct.cpp game_zone.cpp game.cpp
