#include "game.h"
#include <cassert>
#include <iostream>


/*
    this is special class for testing the algorithm of this program
    it can be used by special Makefile in this way:
    make test -> ./test
*/
class GameTest {
    public:
        static void test_place_all_ships_success() {
            Game game;
            int play_zone[7][9];

            for (int i = 0; i < 7; ++i)
                for (int j = 0; j < 9; ++j)
                    play_zone[i][j] = VALID;

            int ships_placed_count = 0;
            bool success = game.place_all_ships(play_zone, game.get_ship_list(), 0, ships_placed_count);

            assert(success);
            assert(ships_placed_count == 10);
        }

        static void test_place_all_ships_fails_on_small_field() {
            Game game;
            int play_zone[7][9];

            for (int i = 0; i < 7; ++i)
                for (int j = 0; j < 9; ++j)
                    play_zone[i][j] = (i < 5 && j < 5) ? VALID : INVALID;
        
            int ships_placed_count = 0;
            bool success = game.place_all_ships(play_zone, game.get_ship_list(), 0, ships_placed_count);
        
            assert(!success);
            assert(ships_placed_count < 10);
        }

        static void test_remove_ship() {
            Game game;
            int play_zone[7][9];
            
            for (int i = 0; i < 7; ++i)
                for (int j = 0; j < 9; ++j)
                    play_zone[i][j] = VALID;

            Linked_ships* test_ship = new Linked_ships(3);
            int ships_placed_count = 0;

            bool placed = game.place_ship_if_possible(play_zone, test_ship, 0, 0, false, ships_placed_count);
            assert(placed);
            assert(ships_placed_count == 1);

            assert(play_zone[0][0] == 3);
            assert(play_zone[0][1] == 3);
            assert(play_zone[0][2] == 3);

            game.remove_ship(play_zone, test_ship, 0, 0, false, ships_placed_count);
            assert(ships_placed_count == 0);
            assert(play_zone[0][0] == VALID);
            assert(play_zone[0][1] == VALID);
            assert(play_zone[0][2] == VALID);

            delete test_ship;
        }
};

int main(void){

    GameTest::test_place_all_ships_success();
    GameTest::test_place_all_ships_fails_on_small_field();
    GameTest::test_remove_ship();
    std::cout << "Algorithm tests passed correctly!" << std::endl;

    return 0;
}