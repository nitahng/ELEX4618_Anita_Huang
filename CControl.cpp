//.CPP file for CControl Class
#include "stdafx.h"
#include "CControl.h"
#include <iostream>
#include "Serial.h"
#include <sstream> 
#include <math.h>
#include <Windows.h>

#define PUSH_BUTTON_2 42
#define bufferlen 64
#define FULLSCALE 4096
#define BIG_BUTTON_2 32

enum Type {
	DIGITAL = 0,
	ANALOG = 1,
	SERVO = 2
};

CControl :: CControl(){

}

CControl::~CControl() {

}

void CControl::init_com(int comport){ 

	int baudrate = 115200;
	std::string comport_number = "COM" + std::to_string(comport);

	bool opened = _com.open(comport_number, baudrate);

	if (opened) {
		std::cout << "COM" + std::to_string(comport) + " Successfully Opened\n";
	}
	else {
		std::cout << "No COM port found!\n\n";
	}
}


bool CControl::get_data(int type, int channel, int& result) {

	char header;
	int get_type;
	int get_channel;
	float get_result;
	std::string string_data;
	string_data = "";
	char buffer[2];


	std::string get_data_string =
		std::string("G") + " " + std::to_string(type) + " " + std::to_string(channel) + "\n";

	_com.flush();

	_com.write(get_data_string.c_str(), get_data_string.length());
	Sleep(10);



	double start_time = GetTickCount();

	buffer[0] = 0;

	while (buffer[0] != '\n' && GetTickCount() - start_time < 1000) {
		if (_com.read(buffer, 1) > 0) {
			string_data = string_data + buffer[0];
		}
	}

	if (string_data.empty()) {
		return false;
	}

	if (string_data.back() != '\n') {
		return false;
	}



	std::istringstream iss(string_data);
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

	int joy_result = 0;
	get_data(ANALOG, channel,joy_result);

	float percentage = 100*joy_result/ FULLSCALE;

	result = joy_result;

	return percentage;
}



bool CControl::get_button(int channel, CControl& comm){

	static int last_state = 0;
	static unsigned long last_press_time = 0;
	const unsigned long debounce_delay = 1000;
	int current_state;

	if (comm.get_data(DIGITAL, channel, current_state)) {
		
		if (current_state == 1 && last_state == 0) {
			unsigned long current_time = GetTickCount();

			
			if ((current_time - last_press_time) >= debounce_delay) {
				last_press_time = current_time;
				last_state = current_state;
				return true;  
			}
		}

		last_state = current_state;
	}

	return false; 
}
