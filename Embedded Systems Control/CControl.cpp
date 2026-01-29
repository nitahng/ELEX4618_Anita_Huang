//.CPP file for CControl Class

#include "CControl.h"
#include <iostream>
#include "../Serial.h"
#include <sstream> 

CControl :: CControl(){

}

CControl::~CControl() {

}

void CControl::init_com(int comport){ // comport is returned as an integer, wont fit into open() unless its in correct format

	int baudrate = 115200;
	std::string comport_number = "COM" + std::to_string(comport);

	bool opened = _com.open(comport_number, baudrate);
}

bool CControl::get_data(int type, int channel, int& result){




	return true;
}


bool CControl::set_data(int type, int channel, int val){


	return true;
}

float CControl::get_analog() {
	float percent = 2;

	return percent;
}

void CControl::get_button() {

}



