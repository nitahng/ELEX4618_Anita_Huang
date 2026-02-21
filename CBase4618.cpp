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

	comm;

}

//Destructor
CBase4618::~CBase4618() {

}

//Run Loop
void CBase4618::run(int lab) {

	int key;

	while (true) {

		gpio();

		update();

		bool exit_pressed = draw(); 
		key = cv::waitKey(1);

		if (key == 'q' || key == 'Q' || exit_pressed == 0) {

			cv::destroyAllWindows();
			break;

		}

	}

}

