#include <iostream>
#include "CControl.h"
#include "../Serial.h"

int main()
{
    CControl comm;
    int comport_number = 3;

    comm.init_com(comport_number);

}

