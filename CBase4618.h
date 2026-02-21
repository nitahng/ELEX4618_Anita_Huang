/**
 * @file CBase4618.h
 * @brief Base class for all ELEX 4618 labs.
 *
 * Child classes implement hardware I/O, state updates, and drawing.
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
  * Child classes must implement gpio(), update(), and draw().
  */
class CBase4618
{
protected:
    /**
     * @brief Communication with the TM4C123G board.
     */
    CControl comm;

    /**
     * @brief OpenCV image buffer for drawing.
     */
    cv::Mat _canvas;

public:
    /**
     * @brief Constructor.
     */
    CBase4618();

    /**
     * @brief Destructor.
     */
    virtual ~CBase4618();

    /**
     * @brief Main loop that calls gpio(), update(), and draw().
     *
     * @param lab Lab identifier.
     */
    void run(int lab);

    /**
     * @brief Read/write hardware I/O (implement in child class).
     */
    virtual void gpio() = 0;

    /**
     * @brief Update game state (implement in child class).
     */
    virtual void update() = 0;

    /**
     * @brief Render the scene (implement in child class).
     *
     * @retval true Continue running.
     * @retval false Exit loop.
     */
    virtual bool draw() = 0;

};