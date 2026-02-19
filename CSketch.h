#pragma once
// CSketch.h (CHILD)

#include "stdafx.h"
#include "CBase4618.h"
#include "CControl.h"

/**
 * @file CSketch.h
 * @brief Etch-A-Sketch child class for ELEX 4618.
 *
 * Implements the lab/game-specific behavior by inheriting from @ref CBase4618 and
 * providing concrete implementations of:
 * - @ref CSketch::gpio  (read joystick/buttons from the controller)
 * - @ref CSketch::update (update cursor/state; choose colour; interpret sensors)
 * - @ref CSketch::draw  (render the canvas + UI)
 *
 * @note `percentage_x` and `percentage_y` are joystick **analog inputs** expressed as percentages.
 * @note `index` is used as the **colour index** (selected drawing colour).
 * @note `findex` is used for an **accelerometer-derived reading** (float) that is forwarded from
 *       @ref update to @ref draw.
 */

 /**
  * @class CSketch
  * @brief Etch-A-Sketch game implementation.
  *
  * CSketch inherits from @ref CBase4618 and defines the Etch-A-Sketch behavior.
  * It reads joystick/button inputs (and sensor data where applicable) via the TM4C123G,
  * updates cursor state, and draws to an OpenCV canvas.
  */
class CSketch : public CBase4618
{
protected:
    /**
     * @brief Previous/anchor point for drawing.
     *
     * Typically represents the last cursor location used to draw a line segment
     * to @ref pt2.
     */
    cv::Point pt1;

    /**
     * @brief Current cursor point for drawing.
     *
     * Typically represents the updated cursor location computed during @ref update.
     */
    cv::Point pt2;

public:
    /**
     * @brief Construct a new CSketch object.
     *
     * Sets up the Etch-A-Sketch instance including canvas sizing and communication
     * settings required to talk to the controller.
     *
     * @param canvassize Size of the drawing canvas (width, height).
     * @param comportnumber COM port number for controller communication.
     */
    CSketch(cv::Size canvassize, int comportnumber);

    /**
     * @brief Destroy the CSketch object.
     */
    ~CSketch();

    /**
     * @brief Perform hardware I/O (joystick + buttons) for the sketch.
     *
     * Reads the joystick analog values (as percentages) and button states from the
     * microcontroller via @ref CControl.
     *
     * @param comm Communication interface to the TM4C123G board.
     * @param[out] percentage_x Joystick X position as a percentage.
     * @param[out] percentage_y Joystick Y position as a percentage.
     * @param[out] BIGBUTTON1_button_pressed True if BIGBUTTON1 is pressed.
     * @param[out] BIGBUTTON2_button_pressed True if BIGBUTTON2 is pressed.
     */
    void gpio(CControl& comm, float& percentage_x, float& percentage_y, bool& BIGBUTTON1_button_pressed, bool& BIGBUTTON2_button_pressed);


    /**
     * @brief Update sketch state based on the latest inputs.
     *
     * Uses joystick percentages to update cursor motion, updates the line endpoints
     * (@ref pt1, @ref pt2), and manages colour selection / reset logic.
     *
     * @param[in] percentage_x Joystick X position as a percentage.
     * @param[in] percentage_y Joystick Y position as a percentage.
     * @param[in] colour_button_pressed True if the colour-change button is pressed.
     * @param[in,out] pt1 Previous/anchor point for drawing.
     * @param[in,out] pt2 Current point for drawing.
     * @param[in,out] index Colour index (selected colour).
     * @param[in,out] findex Accelerometer reading (float) forwarded to draw().
     *
     * @note `index` is specifically used as the colour selector for drawing.
     * @note `findex` is specifically used to carry an accelerometer-derived value
     *       from @ref update into @ref draw.
     */
    void update(float& percentage_x, float& percentage_y, bool& colour_button_pressed, cv::Point& pt1, cv::Point& pt2, int& index, float& findex, cv::Point& pos_ball, cv::Point& vel_ball);
  

    /**
     * @brief Draw the current frame and UI.
     *
     * Renders the Etch-A-Sketch drawing to the canvas, applies the currently selected
     * colour via `colour_index`, and may use the accelerometer reading (`findex`) for
     * extra behavior (e.g., shake-to-erase, tilt effects, etc.).
     *
     * @param[in,out] pt1 Previous/anchor point for drawing.
     * @param[in,out] pt2 Current point for drawing.
     * @param[in] colour_index Selected colour index used for drawing.
     * @param[in] reset_button_pressed True if reset/clear button is pressed.
     * @param[in] findex Accelerometer reading forwarded from update().
     *
     * @retval true Continue running / keep drawing frames.
     * @retval false Exit request (stop the main loop).
     */
    bool draw(cv::Point& pt1, cv::Point& pt2, int& colour_index, bool& reset_button_pressed, float& findex, cv::Point& pos_ball, int &spd);

};
