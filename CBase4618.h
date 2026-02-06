/**
 * @file CBase4618.h
 * @brief Class definition for CBase4618
 *
 * This class will hold common code used in all of the following labs for this course.
 * An essential encapsulation of the functionalities to use the controller.
 */

#pragma once
#include "stdafx.h"
#include "CControl.h"
#include "cvui.h"
#include <opencv2/opencv.hpp>

class CBase4618
{


protected:



    /**
    * @brief CControl Communication Object.
    *
    * Handles low-level communication with the TM4C123G board,
    * including board initialization and Get and Set functions.
    */
    CControl comm;






    /**
    * @brief OpenCV Image Object.
    *
    * The image screen for the drawing surface of the Etch-A-Sketch
    * All Images and Graphics for the labs are processed within this object.
    * 
    */
    cv::Mat _canvas;





public:
    /**
     * @brief Contructor of a CControl object.
     */
    CBase4618();

    /**
     * @brief Destructor for a CControl object.
     */
    ~CBase4618();



    /**
     * @brief Runs gpio, update and draw in a loop until quit key pressed.
     */
    void run();



    /**
     * @brief gpio: virtual method (defined in child)
     * @brief Performs the read and write processes to interact with the Microcontroller.
     */
    virtual void gpio() = 0;
     


    /**
     * @brief update: virtual method (defined in child)
   * @brief 
 
    */
    virtual void update() = 0;



    /**
     * @brief draw: virtual method (defined in child)

     * @brief 

    */
    virtual bool draw() = 0;


};

