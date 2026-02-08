//Common Base Program

#include "stdafx.h"
#include "CBase4618.h"
#include "CControl.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <algorithm>
#include <cmath>


//Constructor
CBase4618 ::CBase4618() {

	CControl comm;

}

//Destructor
CBase4618::~CBase4618() {

}

//Run Loop
void CBase4618::run() {

	cv::Point pt1;
	cv::Point pt2;
	pt1 = cv::Point(500, 500);
	pt2 = cv::Point(501, 501);


	int key;
	float percentage_x = 0;
	float percentage_y = 0;
	bool reset_button_pressed = false;
	bool colour_button_pressed = false;

	int colour_index = 0;


	while (true) {

		gpio(comm, percentage_x, percentage_y, colour_button_pressed, reset_button_pressed);

		update(percentage_x, percentage_y, colour_button_pressed, pt1, pt2, colour_index);

		bool exit_pressed = draw(pt1, pt2, colour_index, reset_button_pressed); //must do imshow

		int key = cv::waitKey(1);

		if (key == 'q' || key == 'Q' || exit_pressed == 0) {

			cv::destroyAllWindows();
			break;

		}

	}

}

