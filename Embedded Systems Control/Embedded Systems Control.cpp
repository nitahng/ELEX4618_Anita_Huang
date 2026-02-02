





/// Libraries ///
#include <iostream>
#include "CControl.h"
#include "../Serial.h"
#include <windows.h>
#include <regex>
#include <conio.h> // For _kbhit() and _getch()


/// Functions ///
void menu();

//Pass the CControl class by reference to other functions
void servo_loop(CControl& comm);
void analog_loop(CControl& comm);
void digital_loop(CControl& comm);




enum Type {
    DIGITAL = 0,
    ANALOG = 1,
    SERVO = 2
};

#define FULLSCALE 4096
#define GREEN_LED 38
#define PUSH_BUTTON_1 41
#define PUSH_BUTTON_2 42
#define SERVO_0 0
#define HIGH 1
#define LOW 0
#define SERVOMAX 180
#define SERVOMIN 0
#define JOYSTICK_X 2
#define JOYSTICK_Y 26





int main()
{
    CControl comm;
    int comport_number = 3;
    comm.init_com(comport_number);


    do {

        menu();

        bool menu;
        char quit;
        std::string pick;
        std::cin >> pick;
        std::regex printmenu("[Aa]|[Bb]|[Cc]|[Dd]");

        menu = std::regex_match(pick, printmenu);

        if (menu == true) {

                if (pick == "a" || pick == "A") {

                    analog_loop(comm);

                }


                else if (pick == "b" || pick == "B") {

                    digital_loop(comm);
                    
                }


                else if (pick == "c" || pick == "C") {

                    int button_test;
                    bool check;
                    std::cout << "BUTTON TEST\n";
                    int press = 0;

                    while (true) {

                        check = comm.get_button(comm);

                        if (check == HIGH) {
                            ++press;

                            std::cout << "BUTTON TEST:" << press << "\n";

                        }
                        if (_kbhit()) {
                            break;
                        }
                        
                    }
                }



                else if (pick == "d" || pick == "D") {

                    servo_loop(comm);

                }
     
        }

        else if (menu == false) {
            std::cout << "\nPlease pick a valid menu option!\n";
        }


    } while (1);

}







void menu() {

    std::cout << "\n\nHello! Welcome to the Embedded Systems Control Menu\n";
    std::cout << "Select an operation!\n";
    std::cout << "(A) for ANALOG TEST (Joystick X and Y)\n";
    std::cout << "(B) for DIGITAL TEST (LED)\n";
    std::cout << "(C) for BUTTON TEST (Button Debouncer)\n";
    std::cout << "(D) for SERVO TEST (Servo Motor)\n";

}



void servo_loop(CControl& comm){

    int servo_out;
    int servo_controller;

    std::cout << "SERVO TEST\n";

    comm.get_data(SERVO, SERVO_0, servo_controller);

    while (true) {
        for (servo_controller < SERVOMAX; servo_controller <= SERVOMAX; servo_controller++) {

            comm.set_data(SERVO, SERVO_0, servo_controller);
            comm.get_data(SERVO, SERVO_0, servo_out);
            std::cout << "SERVO TEST: " << "CH" << SERVO_0 << " = " << servo_out << "\n";
        }
        for (servo_controller > SERVOMIN; servo_controller > SERVOMIN; servo_controller--) {

            comm.set_data(SERVO, SERVO_0, servo_controller);
            comm.get_data(SERVO, SERVO_0, servo_out);
            std::cout << "SERVO TEST: " << "CH" << SERVO_0 << " = " << servo_out << "\n";

        }

        if (_kbhit()) {
            break;
        }

    }

}

void digital_loop(CControl& comm) {

    int digital_in;
    int digital_out;

    std::cout << "DIGITAL TEST\n";

    while (true) {
        Sleep(50);
        comm.get_data(DIGITAL, PUSH_BUTTON_1, digital_in);
        comm.set_data(DIGITAL, GREEN_LED, digital_in);

        std::cout << "DIGITAL TEST: " << "CH" << PUSH_BUTTON_1 << " = " << digital_in << "\n";

        if (_kbhit()) {
            break;
        }
    }

}

void analog_loop(CControl& comm) {

    int joy_x;
    int joy_y;
    float percentage_x;
    float percentage_y;

    std::cout << "ANALOG TEST\n";

    while (true) {
        Sleep(10);
        percentage_x = comm.get_analog(JOYSTICK_X, joy_x);
        percentage_y = comm.get_analog(JOYSTICK_Y, joy_y);

        std::cout << "ANALOG TEST: " << "X_CH" << JOYSTICK_X << " = " << joy_x << " (" << percentage_x << "%" << ") "
            "    Y_CH" << JOYSTICK_Y << " = " << joy_y << " (" << percentage_y << "%" << ") " << "\n";

        if (_kbhit()) {
            break;
        }
    }
    

}