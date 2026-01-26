#pragma once
#include "../Serial.h" //Use Serial Class in CControl Class

class CControl
{
private:
	Serial _com;
public: 
	CControl();
	~CControl();
	void init_com(int comport);
	bool get_data(int type, int channel, int &result);
	bool set_data(int type, int channel, int val);
	float get_analog(); // A guess on type
	void get_button(); // A guess on type
};

