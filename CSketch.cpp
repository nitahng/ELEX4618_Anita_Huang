//Anita Huang Feb 2026
//CSketch.cpp (CHILD)

#include "stdafx.h"
#include "cvui.h"
#include "CSketch.h"

 const int IMGTYPE = CV_8UC3;

 const int JOYSTICK_X = 2;
 const int JOYSTICK_Y = 26;

 const int ACCL_Y = 23;
 const int ACCL_Z = 24;

 const int PUSH_BUTTON_2 = 42;
 const int DIGITAL = 0;
 const int BIG_BUTTON_1 = 32;
 const int BIG_BUTTON_2 = 33;

 const int PIXEL_BOUNDS_BR = 992;
 const int PIXEL_BOUNDS_UL = 5;

 const int SLOW_BOUNDS_X = 55;
 const int FAST_BOUNDS_X = 80;

 const int SLOW_BOUNDS_Y = 45;
 const int FAST_BOUNDS_Y = 20;

 const int RGB_RED = 39;
 const int RGB_GRN = 38;
 const int RGB_BLU = 37;



void make_bounds(cv::Point& pt1, cv::Point& pt2);
void move_pencil(cv::Point& pt1, cv::Point& pt2, float& percentage_x, float& percentage_y);






CSketch::CSketch(cv::Size canvassize, int comportnumber) {

	comm.init_com(comportnumber);
	cvui::init("Etch-A-Sketch");
	_canvas = cv::Mat::zeros(canvassize, IMGTYPE);

}


CSketch::~CSketch() {

}


void CSketch::gpio(CControl& comm, float &percentage_x, float &percentage_y, bool &colour_button_pressed, bool& reset_button_pressed) {

	//Reading Joystick Inputs
	int raw_x, raw_y;
	percentage_x = comm.get_analog(JOYSTICK_X, raw_x);
	percentage_y = comm.get_analog(JOYSTICK_Y, raw_y);

	//Reading Button Input for Colour
	bool button1_input = comm.get_button(BIG_BUTTON_1, comm);
	colour_button_pressed = button1_input;
	bool button2_input = comm.get_button(BIG_BUTTON_2, comm);
	reset_button_pressed = button2_input;

	//Live Input Read
	std::cout << "ANALOG TEST: " << "X_CH" << JOYSTICK_X << " = " << raw_x << " (" << percentage_x << "%" << ") "
		"    Y_CH" << JOYSTICK_Y << " = " << raw_y << " (" << percentage_y << "%" << ") " << " Button Press:" << colour_button_pressed<< "\n";

}


void CSketch::update(float& percentage_x, float& percentage_y, bool& colour_button_pressed, cv::Point &pt1, cv::Point& pt2, int &colour_index) {
		

		std::vector <int> colour_channel = { RGB_RED , RGB_GRN, RGB_BLU };
		pt2.x = pt1.x;
		pt2.y = pt1.y;

		make_bounds(pt1, pt2);
		move_pencil(pt1, pt2, percentage_x, percentage_y);

		//int shake_y, shake_z;
		//float shake_y_pctg = comm.get_analog(ACCL_Y, shake_y);
		//float shake_z_pctg = comm.get_analog(ACCL_Z, shake_z);
		//std::cout << "\n\nANALOG TEST: " << "Y_CH" << ACCL_Y << " = " << shake_y << " (" << shake_y_pctg << "%" << ") "
			//"    Z_CH" << ACCL_Z << " = " << shake_z << " (" << shake_z_pctg << "%" << ") " << "\n";

		
		if (colour_button_pressed) {

			comm.set_data(DIGITAL, colour_channel[colour_index], false);

			++colour_index;

		}
		if (colour_index > 2) colour_index = 0;

		
}


bool CSketch::draw(cv::Point &pt1, cv::Point& pt2, int& colour_index, bool& reset_button_pressed) {

	//Colour Selection
	std::vector <cv::Scalar> colours = {
	cv::Scalar(0, 0, 255),
	cv::Scalar(0, 255, 0),
	cv::Scalar(255, 0, 0),
	};
	std::vector <std::string> colour_text = { "RED", "GREEN", "BLUE" };
	std::vector <int> colour_channel = { RGB_RED , RGB_GRN, RGB_BLU };

	//Turn Coloured LED 
	comm.set_data(DIGITAL, colour_channel[colour_index], true);


	//CVUI for Buttons and Text
	cvui::window(_canvas, 10, 10, 150, 90, "Etch-A-Sketch");

	cv::Point colour_text_position(20, 60);

	cv::putText(_canvas, colour_text.at(colour_index), colour_text_position, cv::FONT_HERSHEY_SIMPLEX, 1, colours.at(colour_index), 2, cv::LINE_AA);

	if (cvui::button(_canvas, 20, 70, "Reset") || reset_button_pressed == true) {
		cv::Size canvassize = cv::Size(1000, 1000);
		_canvas = cv::Mat::zeros(canvassize, IMGTYPE);
	}
	if (cvui::button(_canvas, 100, 70, "Exit")) {
		return 0;
	}


	//Draw Game
	cv::line(_canvas, pt1, pt2,colours.at(colour_index), 8, cv::LINE_AA);


	//Update and Show
	cvui::update();
	cv::imshow("Etch-A-Sketch", _canvas);

	return 1;
	
}







//      //        !The Helper Functions!      //         //


void make_bounds(cv::Point& pt1, cv::Point& pt2) {

	if (PIXEL_BOUNDS_UL > pt1.x) {
		pt1.x = PIXEL_BOUNDS_UL;
	}
	else if (PIXEL_BOUNDS_UL > pt1.y) {
		pt1.y = PIXEL_BOUNDS_UL;
	}
	else if (PIXEL_BOUNDS_BR < pt1.x) {
		pt1.x = PIXEL_BOUNDS_BR;
	}
	else if (PIXEL_BOUNDS_BR < pt1.y) {
		pt1.y = PIXEL_BOUNDS_BR;
	}

}

void move_pencil(cv::Point& pt1, cv::Point& pt2, float& percentage_x, float& percentage_y) {


	if (SLOW_BOUNDS_X < percentage_x && FAST_BOUNDS_X > percentage_x) { //move right 

		pt1.x = pt1.x + 2;


	}
	else if (80 < percentage_x) { //move right quicker

		pt1.x = pt1.x + 8;


	}
	else if (45 > percentage_x && 20 < percentage_x) { //move left

		pt1.x = pt1.x - 2;

	}
	else if (20 > percentage_x) { //move right quicker

		pt1.x = pt1.x - 8;

	}

	if (55 < percentage_y && 80 > percentage_y) { //move up

		pt1.y = pt1.y - 2;


	}
	else if (80 < percentage_y) { //move up quicker

		pt1.y = pt1.y - 8;

	}
	else if (45 > percentage_y && 20 < percentage_y) { //move down

		pt1.y = pt1.y + 2;

	}
	else if (20 > percentage_y) { //move down quicker

		pt1.y = pt1.y + 8;

	}



}


