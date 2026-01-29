#include <iostream>
#include "CControl.h"
#include "../Serial.h"
#include <regex>

enum Type {
    DIGITAL = 0,
    ANALOG = 1,
    SERVO = 2
};

#define GREEN_LED 38
#define PUSH_BUTTON_1 41
#define SERVO_0 0
#define HIGH 1
#define LOW 0


int main()
{
    CControl comm;
    int comport_number = 3;
    comm.init_com(comport_number);
    int num;

    do {
        std::cout << "\n\nHello! Welcome to the Embedded Systems Control Menu\n";
        std::cout << "Select an operation!\n";
        std::cout << "(A) for ANALOG TEST (Joystick X and Y)\n";
        std::cout << "(B) for DIGITAL TEST (Button)\n";
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
                comm.set_data(DIGITAL, GREEN_LED, HIGH);

            }
            else if (pick == "b" || pick == "B") {

                std::cout << "DIGITAL TEST\n";

                
                comm.get_data(DIGITAL, PUSH_BUTTON_1, num);
                std::cout << num;
                

            }
            else if (pick == "c" || pick == "C") {

                std::cout << "BUTTON TEST\n";
                comm.set_data(SERVO, SERVO_0, 1);

            }
            else if (pick == "d" || pick == "D") {

                std::cout << "SERVO TEST\n";

                comm.set_data(SERVO, SERVO_0, 180);

            }
     
        }

        else if (menu == false) {
            std::cout << "\nPlease pick a valid menu option!\n";
        }

    } while (1);

}

