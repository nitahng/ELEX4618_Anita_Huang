/**
 * @file CControl.h
 * @brief Declaration of the CControl class for serial-based I/O control.
 *
 * This class provides an interface for communicating with external hardware
 * using the Serial class. It supports sending and receiving digital and
 * analog data for ELEX 4618 Lab 3.
 */
#include "stdafx.h"

#pragma once
#include "Serial.h"   // Use Serial Class in CControl Class

 /**
  * @class CControl
  * @brief Handles serial communication and I/O control.
  *
  * The CControl class abstracts serial communication commands used to
  * get and set digital, analog, and button data.
  */
class CControl
{
private:
    /**
    * @brief Serial communication object.
    *
    * Handles low-level communication with the TM4C123G board,
    * including sending commands and receiving responses.
    */
    Serial _com;

public:
    /**
     * @brief Contructor of a CControl object.
     */
    CControl();

    /**
     * @brief Destructo the CControl object.
     */
    ~CControl();

    /**
     * @brief Initializes the serial communication port.
     *
     * @param comport COM port number to open (e.g., COM3).
     */
    void init_com(int comport);

    /**
     * @brief Retrieves data from the device.
     *
     * Sends a get command over serial communication and stores
     * the returned value in the result parameter.
     *
     * @param type Type of data to retrieve (digital, analog, etc.).
     * @param channel Channel number to read from.
     * @param result Reference to store the returned value.
     * @return true if the command succeeded, false otherwise.
     */
    bool get_data(int type, int channel, int& result);

    /**
     * @brief Sends data to the device.
     *
     * @param type Type of data to set (digital, servo, etc.).
     * @param channel Channel number to write to.
     * @param val Value to send.
     * @return true if the command succeeded, false otherwise.
     */
    bool set_data(int type, int channel, int val);

    /**
     * @brief Function to return raw and percentage analog values
     *
     * @param channel Channel number to read from GET function
     * @param result  Reference to store the returned value
     * @return percentage of the analog value
     */
    float get_analog(int channel, int& result);


    /**
     * @brief Reads digital input and debounces it
     */

    bool get_button(int channel, CControl &comm);
};
