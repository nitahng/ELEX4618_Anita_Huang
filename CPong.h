#pragma once
#include "CBase4618.h"

class CPong :public CBase4618
{

protected:




public:

	/**
	 * @brief Constructor for a new CPong object.
	 *
	 * Initializes the Pong game instance, including the drawing canvas size
	 * and communication configuration.
	 *
	 * @param canvasSize Size of the drawing canvas (width/height).
	 * @param comportnumber COM port number used to communicate with the controller.
	 */
	CPong(cv::Size canvassize, int comportnumber);



	/**
	 * @brief Destroy the CSketch object.
	 *
	 * Cleans up any resources owned by the sketch instance.
	 */
	~CPong();


	/**
	 * @brief Handle hardware I/O with the microcontroller.
	 *
	 * Performs the read/write communication needed to retrieve input states
	 * (joystick position, pushbuttons) and send output states if required
	 */

	void gpio(CControl& comm, float& percentage_x, float& percentage_y, bool& BIGBUTTON1_button_pressed, bool& BIGBUTTON2_button_pressed);


	/**
	 * @brief Update the PONG state.
	 *
	 * Updates the internal game state using the most recent inputs obtained from
	 * gpio(), such as cursor movement, and joystick input
	 */
	void update(float& percentage_x, float& percentage_y, bool& colour_button_pressed, cv::Point& pt1, cv::Point& pt2, int& index, float& findex, cv::Point& pos_ball, cv::Point& vel_ball);



	/**
	 * @brief Render the current frame to the canvas and display it.
	 *
	 * Draws the UI elements and the Etch-A-Sketch output onto the OpenCV canvas,
	 * then displays the resulting image on screen.
	 */
	bool draw(cv::Point& pt1, cv::Point& pt2, int& colour_index, bool& reset_button_pressed, float& findex, cv::Point& pos_ball, int &spd);




	bool make_ui_window(int& ball_radius, bool& reset_button_pressed, float& fps, int& spd);

};

