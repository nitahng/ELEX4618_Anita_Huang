#pragma once
// CSketch.h (CHILD)
// Anita Huang Feb 2026

#include "stdafx.h"
#include "CBase4618.h"
#include "CControl.h"

/**
 * @file CSketch.h
 * @brief Etch-A-Sketch implementation for ELEX 4618.
 */

 /**
  * @class CSketch
  * @brief Etch-A-Sketch game class.
  *
  * Inherits from CBase4618 and implements an Etch-A-Sketch where the user
  * draws by moving the joystick. Includes colour changing and shake-to-clear.
  */
class CSketch : public CBase4618
{
protected:
    /**
     * @brief Previous cursor position for drawing lines.
     */
    cv::Point pt1;

    /**
     * @brief Current cursor position for drawing lines.
     */
    cv::Point pt2;

    /**
     * @brief Joystick X position as percentage (0-100).
     */
    float percentage_x;

    /**
     * @brief Joystick Y position as percentage (0-100).
     */
    float percentage_y;

    /**
     * @brief Flag for when colour button is pressed.
     */
    bool colour_button_pressed;

    /**
     * @brief Flag for when reset button is pressed.
     */
    bool reset_button_pressed;

    /**
     * @brief Current colour index (0=RED, 1=GREEN, 2=BLUE).
     */
    int colour_index;

    /**
     * @brief Accelerometer Z-axis reading for shake detection.
     */
    float shaker;

public:
    /**
     * @brief Constructor.
     *
     * Initializes the Etch-A-Sketch with given canvas size and COM port.
     * Sets up starting cursor positions and default values.
     *
     * @param canvassize Width and height of drawing canvas.
     * @param comportnumber COM port for microcontroller communication.
     */
    CSketch(cv::Size canvassize, int comportnumber);

    /**
     * @brief Destructor.
     */
    ~CSketch();

    /**
     * @brief Read joystick and button inputs from microcontroller.
     *
     * Reads:
     * - Joystick X/Y positions as percentages
     * - BIG_BUTTON_1 for colour change
     * - BIG_BUTTON_2 for reset
     */
    void gpio();

    /**
     * @brief Update cursor position and game state.
     *
     * Moves the cursor based on joystick input, handles colour button presses,
     * and reads accelerometer for shake detection.
     */
    void update();

    /**
     * @brief Draw the Etch-A-Sketch canvas and UI.
     *
     * Draws lines between pt1 and pt2 in the selected colour.
     * Handles reset button, shake-to-clear, and exit button.
     * Controls RGB LED to show current colour.
     *
     * @retval true Continue running.
     * @retval false Exit program.
     */
    bool draw();

    /**
     * @brief Move pencil based on joystick percentages.
     *
     * Uses percentage_x and percentage_y to determine direction and speed.
     * Different speed thresholds for slow/fast movement.
     */
    void move_pencil();

    /**
     * @brief Keep cursor within canvas boundaries.
     *
     * Prevents drawing outside the valid pixel range using PIXEL_BOUNDS_UL
     * and PIXEL_BOUNDS_BR constants.
     */
    void make_bounds();

};