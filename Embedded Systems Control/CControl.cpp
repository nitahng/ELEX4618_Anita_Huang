//.CPP file for CControl Class

#include "CControl.h"
#include <iostream>
#include "../Serial.h"
#include <sstream> 
#include <math.h>


#define bufferlen 64
#define FULLSCALE 4096

enum Type {
	DIGITAL = 0,
	ANALOG = 1,
	SERVO = 2
};

CControl :: CControl(){

}

CControl::~CControl() {

}

void CControl::init_com(int comport){ // comport is returned as an integer, wont fit into open() unless its in correct format

	int baudrate = 115200;
	std::string comport_number = "COM" + std::to_string(comport);

	bool opened = _com.open(comport_number, baudrate);

	if (opened) {
		std::cout << "COM" + std::to_string(comport) + " Successfully Opened\n";
	}
	else {
		std::cout << "No COM PORT found!\n\n";
	}
}

bool CControl::get_data(int type, int channel, int& result){

	char header;
	int get_type;
	int get_channel;
	float get_result;

	
	std::string get_data_string =
		std::string("G") + " " + std::to_string(type) + " " + std::to_string(channel) + "\n";
	
	_com.flush();

	_com.write(get_data_string.c_str(), get_data_string.length());
	Sleep(10);

	

	char buffer [bufferlen];

	int n =	_com.read(buffer, bufferlen-1);

	buffer[n] = '\0';


	std::istringstream iss(buffer);
	iss >> header >> get_type >> get_channel >> get_result; //info flows outward

	result = get_result;

	return true;

}


bool CControl::set_data(int type, int channel, int val){

	std::string set_data_string = 
		std::string("S") + " " +  std::to_string(type) +  " " + std::to_string(channel) + " " + std::to_string(val) + "\n";
	
	_com.write(set_data_string.c_str(), set_data_string.length());//c_str() converts the string type tp const char*

	return true; 

}



float CControl::get_analog(int channel, int& result){

	int joy_result;
	get_data(ANALOG, channel,joy_result);

	float percentage = 100*joy_result/ FULLSCALE;

	result = joy_result;

	return percentage;
}

void CControl::get_button(){}
