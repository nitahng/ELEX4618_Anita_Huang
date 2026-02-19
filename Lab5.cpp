
#include "stdafx.h"
#include "CControl.h"
#include "Serial.h"
#include "CPong.h"
#include "CBase4618.h"

#define COM 4
#define Canvas_Width 1000
#define Canvas_Height 800
#define Lab5 5

void run_lab5() {

	CPong pong(cv::Size(Canvas_Width, Canvas_Height), COM);
	pong.run(Lab5);
}
