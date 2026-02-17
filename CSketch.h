#pragma once
//CSketch.h (CHILD)

#include "stdafx.h"
#include "CBase4618.h"
#include "CControl.h"


/**
 * @class CSketch
 * @brief Etch-A-Sketch game implementation.
 *
 * CSketch inherits from CBase4618 and provides concrete implementations of the
 * gpio(), update(), and draw() methods for the Etch-A-Sketch application.
 * It reads joystick/buttons via the microcontroller and renders drawing output
 * onto an OpenCV canvas.
 */
class CSketch : public CBase4618 {



protected:

	cv::Point pt1;
	cv::Point pt2;


public:

	/**
	 * @brief Constructor for a new CSketch object.
	 *
	 * Initializes the Etch-A-Sketch game instance, including the drawing canvas size
	 * and communication configuration.
	 *
	 * @param canvasSize Size of the drawing canvas (width/height).
	 * @param comportnumber COM port number used to communicate with the controller.
	 */
	CSketch(cv::Size canvassize, int comportnumber);



	/**
	 * @brief Destroy the CSketch object.
	 *
	 * Cleans up any resources owned by the sketch instance.
	 */
	~CSketch();



	/**
	 * @brief Handle hardware I/O with the microcontroller.
	 *
	 * Performs the read/write communication needed to retrieve input states
	 * (joystick position, pushbuttons) and send output states if required
	 */

	void gpio(CControl& comm, float &percentage_x, float &percentage_y, bool &BIGBUTTON1_button_pressed, bool &BIGBUTTON2_button_pressed);


	/**
	 * @brief Update the Etch-A-Sketch state.
	 *
	 * Updates the internal game state using the most recent inputs obtained from
	 * gpio(), such as cursor movement, colour selection, and reset requests.
	 */
	void update(float& percentage_x, float& percentage_y, bool& colour_button_pressed, cv::Point& pt1, cv::Point& pt2, int &index, float &findex);



	/**
	 * @brief Render the current frame to the canvas and display it.
	 *
	 * Draws the UI elements and the Etch-A-Sketch output onto the OpenCV canvas,
	 * then displays the resulting image on screen.
	 */
	bool draw(cv::Point& pt1, cv::Point& pt2, int& colour_index, bool& reset_button_pressed);


};