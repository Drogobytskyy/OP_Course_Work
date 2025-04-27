#include "game_zone.h"
using namespace std; 

Game_zone :: Game_zone(){

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 9; j++) {
            play_zone[i][j] = g_play_zone[i][j];
        }
    }
}


void Game_zone::print_start_zone(int play_zone[7][9], Start_instruction& instruction) {
    instruction.up_bottom_fill();

    vec_st_zone.clear(); 

    for (int i = 0; i < 7; i++) {
        string line1 = "";
        string line2 = "";
        string line3 = "";

        for (int j = 0; j < 9; j++) {
            if (play_zone[i][j] == 0) {
                line1 += "     ";
                line2 += "     ";
                line3 += "     ";
            } else if (play_zone[i][j] == 9) {
                line1 += "*****";
                line2 += "|   |";
                line3 += "*****";
            } else {
                line1 += "*****";
                line2 += "| \033[31m\u2248\033[0m |";
                line3 += "*****";
            }
        }
        vec_st_zone.push_back(line1);
        vec_st_zone.push_back(line2);
        vec_st_zone.push_back(line3);
    }

    for (int i = 0; i < (int)vec_st_zone.size(); i++) {
        instruction.controlled_output(vec_st_zone[i]);
    }

    instruction.up_bottom_fill();
}

void Game_zone::print_final_zone(int play_zone[7][9], Start_instruction& instruction) {
    instruction.up_bottom_fill();

    vec_st_zone.clear(); 

    for (int i = 0; i < 7; i++) {
        string line1 = "";
        string line2 = "";
        string line3 = "";

        for (int j = 0; j < 9; j++) {
            if (play_zone[i][j] == 0) {
                line1 += "     ";
                line2 += "     ";
                line3 += "     ";
            } else if (play_zone[i][j] == 7) {
                line1 += "*****";
                line2 += "| \033[31m\u2248\033[0m |";
                line3 += "*****";
            } else if (play_zone[i][j] == 9){
                line1 += "*****";
                line2 += "|   |";
                line3 += "*****";
            } else {
                line1 += "*****";
                line2 += "| ";
                line2 += '0' + play_zone[i][j];
                line2 += " |";
                line3 += "*****";
            }
        }
        vec_st_zone.push_back(line1);
        vec_st_zone.push_back(line2);
        vec_st_zone.push_back(line3);
    }

    for (int i = 0; i < (int)vec_st_zone.size(); i++) {
        instruction.controlled_output(vec_st_zone[i]);
    }

    instruction.up_bottom_fill();
}

void Game_zone :: copy_zone(int src[7][9], int dest[7][9]) {
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 9; j++) {
            dest[i][j] = src[i][j];
        }
    }
}

bool Game_zone :: is_inside_zone(int x, int y) {
    return x >= 0 && x < 7 && y >= 0 && y < 9;
}

bool Game_zone :: is_ship(int *zone) {
    return *zone != VALID && *zone != INVALID && *zone != SPECIAL;
}

bool Game_zone :: has_nearby_ship(int x, int y, int play_zone[7][9]) {
    int dx[] = {-1, -1, -1,  0, 0, 1, 1, 1};
    int dy[] = {-1,  0,  1, -1, 1,-1, 0, 1};

    for (int dir = 0; dir < 8; dir++) {
        int nx = x + dx[dir];
        int ny = y + dy[dir];

        if (is_inside_zone(nx, ny) && is_ship(&play_zone[nx][ny])) {
            return true;
        }
    }
    return false;
}

bool Game_zone :: is_valid(int *zone) {
    return *zone == VALID;
}

