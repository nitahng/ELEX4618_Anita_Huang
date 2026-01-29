#include <iostream>
#include "CControl.h"
#include "../Serial.h"
#include <regex>

int main()
{
    CControl comm;
    int comport_number = 3;
    comm.init_com(comport_number);


    do {
        std::cout << "Hello! Welcome to the Embedded Systems Control Menu\n";
        std::cout << "Select an operation!\n";
        std::cout << "(A) for ANALOG TEST (Joystick X and Y)\n";
        std::cout << "(B) for DIGITAL TEST (Booster Button)\n";
        std::cout << "(C) for BUTTON TEST (Button Debouncer)\n";
        std::cout << "(D) for SERVO TEST (Servo Motor)\n";

        bool menu;
        std::string pick;
        std::cin >> pick;
        std::regex printmenu("[Aa]|[Bb]|[Cc]|[Dd]");

        menu = std::regex_match(pick, printmenu);

        if (menu == true) {

            if (pick == "a" || pick == "A") {

                std::cout << "ANALOG TEST\n";
                

            }
            else if (pick == "b" || pick == "B") {

                std::cout << "DIGITAL TEST\n";

            }
            else if (pick == "c" || pick == "C") {

                std::cout << "BUTTON TEST\n";

            }
            else if (pick == "d" || pick == "D") {

                std::cout << "SERVO TEST\n";

            }
     
        }

        else if (menu == false) {
            std::cout << "\nPlease pick a valid menu option!\n";
        }

    } while (1);

    

    


}

