#include "stdafx.h"
#include "cvui.h"
#include "CSketch.h"
//CSketch.cpp (CHILD)

#define IMGTYPE CV_8UC3

CSketch::CSketch(cv::Size canvassize, int comportnumber) {
	cvui::init("Etch-A-Sketch");
	_canvas = cv::Mat::zeros(canvassize, IMGTYPE);

}


CSketch::~CSketch() {

}


void CSketch::gpio() {


}


void CSketch::update() {


}


bool CSketch::draw() {

	//Clear Canvas
	cv::Size canvassize = cv::Size(600, 600);
	_canvas = cv::Mat::zeros(canvassize, IMGTYPE);

	//Draw CVUI for Button Window
	cvui::window(_canvas, 10, 10, 150, 90, "Etch-A-Sketch");

	if (cvui::button(_canvas, 20, 70, "Reset")) {

	}

	if (cvui::button(_canvas, 100, 70, "Exit")) {
		return 0;
	}


	//Draw Game

	//Update and Show
	cvui::update();
	cv::imshow("Etch-A-Sketch", _canvas);

	return 1;
	
}


