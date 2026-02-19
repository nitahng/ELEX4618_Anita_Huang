/**
 * @file CBase4618.h
 * @brief Base class shared by all ELEX 4618 labs.
 *
 * Provides the common “game loop” interface and shared resources for labs that
 * use the TM4C123G controller + OpenCV/cvui rendering. Child classes implement
 * hardware I/O, state updates, and drawing behavior.
 *
 * @note The joystick percentages (`percentage_x`, `percentage_y`) represent **analog inputs**
 *       normalized to a percentage range.
 * @note `index` and `findex` are **general-purpose state values** (integer/float) used to pass
 *       any data from @ref update to @ref draw.
 */

#pragma once
#include "stdafx.h"
#include "CControl.h"
#include "cvui.h"
#include <opencv2/opencv.hpp>

 /**
  * @class CBase4618
  * @brief Abstract base class that defines the lab framework.
  *
  * Child classes must implement:
  * - @ref gpio   (read/write controller I/O)
  * - @ref update (compute next state)
  * - @ref draw   (render based on current state)
  */
class CBase4618
{
protected:
    /**
     * @brief Communication object for the TM4C123G board.
     *
     * Handles low-level communication with the microcontroller, including board
     * initialization and GPIO Get/Set style functions.
     */
    CControl comm;

    /**
     * @brief Drawing surface for the lab UI.
     *
     * OpenCV image buffer used as the main canvas for all graphics and processing.
     */
    cv::Mat _canvas;

public:
    /**
     * @brief Construct a new CBase4618 object.
     */
    CBase4618();

    /**
     * @brief Destroy the CBase4618 object.
     */
    virtual ~CBase4618();

    /**
     * @brief Main loop runner that repeatedly calls gpio(), update(), and draw().
     *
     * Runs until a quit condition is met (e.g., quit key pressed).
     *
     * @param lab Lab identifier used to select/organize lab-specific behavior.
     */
    void run(int lab);

    /**
     * @brief Read/write hardware I/O for the controller (implemented in child class).
     *
     * Reads analog inputs (as percentages) and button states from the controller /
     * microcontroller interface.
     *
     * @param comm Communication interface to the TM4C123G board.
     * @param[out] percentage_x Joystick X position as a percentage (analog input).
     * @param[out] percentage_y Joystick Y position as a percentage (analog input).
     * @param[out] BIGBUTTON1_pressed True if BIGBUTTON1 is pressed.
     * @param[out] BIGBUTTON2_pressed True if BIGBUTTON2 is pressed.
     */
    virtual void gpio(CControl& comm, float& percentage_x, float& percentage_y, bool& BIGBUTTON1_pressed, bool& BIGBUTTON2_pressed) = 0;

    /**
     * @brief Update the lab/game state (implemented in child class).
     *
     * Consumes the latest inputs (e.g., joystick percentages) and updates internal
     * state variables used for drawing and interaction.
     *
     * @param[in,out] percentage_x Joystick X as a percentage (analog input).
     * @param[in,out] percentage_y Joystick Y as a percentage (analog input).
     * @param[in,out] colour_button_pressed True if the colour/change button is pressed.
     * @param[in,out] pt1 First point used for drawing (previous/anchor point).
     * @param[in,out] pt2 Second point used for drawing (current point).
     * @param[in,out] index General-purpose integer value to pass from update() to draw().
     * @param[in,out] findex General-purpose float value to pass from update() to draw().
     *
     * @note `index` and `findex` are not limited to analog inputs—use them for any
     *       state you want to carry into @ref draw.
     */
    virtual void update(float& percentage_x, float& percentage_y, bool& colour_button_pressed, cv::Point& pt1, cv::Point& pt2, int& index, float& findex, cv::Point& pos_ball, cv::Point& vel_ball) = 0;


    /**
     * @brief Render the scene and perform draw/erase behavior (implemented in child class).
     *
     * Uses state prepared in @ref update (e.g., points, indices, and flags) to render
     * graphics onto the canvas.
     *
     * @param[in,out] pt1 First point used for drawing (previous/anchor point).
     * @param[in,out] pt2 Second point used for drawing (current point).
     * @param[in,out] colour_index Selected colour index used by draw().
     * @param[in,out] reset_button_pressed True if reset/clear button is pressed.
     * @param[in,out] findex General-purpose float value forwarded from update().
     *
     * @retval true Continue running.
     * @retval false Request exit from the main loop (quit condition).
     */
    virtual bool draw(cv::Point& pt1, cv::Point& pt2, int& colour_index, bool& reset_button_pressed, float& findex, cv::Point& pos_ball, int &spd) = 0;

};
