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

	Serial serial; // open the serial class for its functions

	std::string comport_number = std::to_string(comport);
	std::ostringstream comportname;

	comportname << "COM" << comport_number;

	bool opened = serial.open(comportname.str());


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



