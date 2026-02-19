//Common Base Program

#include "stdafx.h"
#include "CBase4618.h"
#include "CControl.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <algorithm>
#include <cmath>


const int R_paddlemargin = 950;


//Constructor
CBase4618 ::CBase4618() {

	comm;

}

//Destructor
CBase4618::~CBase4618() {

}

//Run Loop
void CBase4618::run(int lab) {

	int key;

	cv::Point pt1;
	cv::Point pt2;
	cv::Point pos_ball;
	cv::Point vel_ball;
	float percentage_x = 0;
	float percentage_y = 0;
	int  index = 0; //an index that simply passes from update to draw if a condition is met
	float  findex = 0; //an index that simply passes from update to draw if a condition is met
	bool BIGBUTTON2_button_pressed = false;
	bool BIGBUTTON1_button_pressed = false;
	int spd = 0;

	if (lab == 4) {
		pt1 = cv::Point(500, 500);
		pt2 = cv::Point(501, 501);
		index = 5;
	}
	else if (lab == 5) {
		pt1 = cv::Point(R_paddlemargin, 500);
		pt2 = cv::Point(R_paddlemargin, 600);
		pos_ball = cv::Point(500, 400);
		vel_ball = cv::Point(100, 0);


	}

	while (true) {

		gpio(comm, percentage_x, percentage_y, BIGBUTTON1_button_pressed, BIGBUTTON2_button_pressed);

		update(percentage_x, percentage_y, BIGBUTTON1_button_pressed, pt1, pt2, index, findex,pos_ball, vel_ball);

		bool exit_pressed = draw(pt1, pt2, index, BIGBUTTON2_button_pressed, findex, pos_ball, spd); //must do imshow

		int key = cv::waitKey(1);

		if (key == 'q' || key == 'Q' || exit_pressed == 0) {

			cv::destroyAllWindows();
			break;

		}

	}

}

