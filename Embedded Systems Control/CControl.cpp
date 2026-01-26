//.CPP file for CControl Class

#include "CControl.h"
#include <iostream>
#include "../Serial.h"

CControl :: CControl(){

}

CControl::~CControl() {

}

void CControl::init_com(int comport){

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



