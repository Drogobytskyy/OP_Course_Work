#ifndef START_INSTRUCTION_H
#define START_INSTRUCTION_H

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

/* ----------------------------------------------------------------------[<]-
    Class: Start_instruction

    Synopsis: this header was created for any type of output that we have in programm, 
    it can handle every situation and grants us with some specific kind of
    box output and color specifications
    ---------------------------------------------------------------------[>]-*/
    
class Start_instruction {
    private:
        void show_message_block(const std::vector<std::string> &messages);
        void show_ships();
        void show_squares();

    public:

        void up_bottom_fill();
        void controlled_output(const std::string &s);
        void show();
        void custom_message(const std::string &message);
        void custom_only_text(const std::string &message);

        /*
            this little function checks what systeam user are in
            and in terms of that clear console for users.
        */
        void clear_screen(){
            #ifdef _WIN32
                system("cls");
            #else
                system("clear");
            #endif
        }
};



#endif

