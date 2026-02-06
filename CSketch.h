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

private:




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
	 * (e.g., joystick position, pushbuttons) and send output states if required
	 * (e.g., LED colour).
	 */

	void gpio();


	/**
	 * @brief Update the Etch-A-Sketch state.
	 *
	 * Updates the internal game state using the most recent inputs obtained from
	 * gpio(), such as cursor movement, colour selection, and reset requests.
	 */
	void update();



	/**
	 * @brief Render the current frame to the canvas and display it.
	 *
	 * Draws the UI elements and the Etch-A-Sketch output onto the OpenCV canvas,
	 * then displays the resulting image on screen.
	 */
	bool draw();


};