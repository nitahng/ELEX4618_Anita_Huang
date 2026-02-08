
#include "stdafx.h"
#include "CControl.h"
#include "Serial.h"
#include "CSketch.h"
#include "CBase4618.h"

#define COM 3
#define Canvas_Size 1000

void run_lab4() {
	CSketch sketch(cv::Size(Canvas_Size, Canvas_Size), COM);
	sketch.run();

}
