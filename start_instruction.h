#ifndef START_INSTRUCTION_H
#define START_INSTRUCTION_H

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

class Start_instruction {
    
    void up_bottom_fill();
    void controlled_output(const std::string &s);
    void show_message_block(const std::vector<std::string> &messages);
    void show_ships();
    void show_squares();

    public:
        void show();
        void custom_message(const std::string &message);
        void up_and_bot();
        void custom_only_text(const std::string &message);

        void clear_screen(){
            #ifdef _WIN32
                system("cls");
            #else
                system("clear");
            #endif
        }
};



#endif

