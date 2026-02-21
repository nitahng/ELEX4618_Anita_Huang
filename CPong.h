#pragma once
// CPong.h
// Anita Huang Feb 2026

#include "CBase4618.h"

/**
 * @class CPong
 * @brief Pong game implementation (player vs computer).
 *
 * Inherits from CBase4618 and implements a Pong game where the player
 * controls the right paddle with joystick Y-axis, and the computer
 * controls the left paddle automatically.
 */
class CPong : public CBase4618
{

protected:

    /**
     * @brief Speed multiplier from UI trackbar (100-400).
     */
    int spd;

    /**
     * @brief Radius of the ball in pixels (adjustable via UI).
     */
    int ball_radius;

    /**
     * @brief Computer's score (goals scored against player).
     */
    int botgoal;

    /**
     * @brief Player's score.
     */
    int playergoal;

    /**
     * @brief Joystick Y position as percentage (0-100).
     */
    float percentage_y;

    /**
     * @brief Flag for when reset button is pressed.
     */
    bool reset_button_pressed;

    /**
     * @brief Current frames per second for display.
     */
    float fps;

    /**
     * @brief Delta time between frames for frame-independent movement.
     */
    double dt;

    /**
     * @brief Game over state flag (true when player or computer reaches 5).
     */
    bool gameover;

    /**
     * @brief Top point of player's right paddle.
     */
    cv::Point paddletop;

    /**
     * @brief Bottom point of player's right paddle.
     */
    cv::Point paddlebottom;

    /**
     * @brief Top point of computer's left paddle.
     */
    cv::Point paddlebot_top;

    /**
     * @brief Bottom point of computer's left paddle.
     */
    cv::Point paddlebot_bottom;

    /**
     * @brief Current ball position.
     */
    cv::Point pos_ball;

    /**
     * @brief Current ball velocity (pixels per second).
     */
    cv::Point vel_ball;


public:

    /**
     * @brief Constructor for a new CPong object.
     *
     * Initializes the Pong game instance with given canvas size and COM port.
     * Sets up starting positions for paddles and ball, initializes scores,
     * and configures the UI window.
     *
     * @param canvassize Size of the drawing canvas (width/height).
     * @param comportnumber COM port number used to communicate with the controller.
     */
    CPong(cv::Size canvassize, int comportnumber);

    /**
     * @brief Destroy the CPong object.
     */
    ~CPong();

    /**
     * @brief Read joystick Y-axis input from microcontroller.
     *
     * Reads the analog joystick Y position and converts to percentage
     * for player paddle control.
     */
    void gpio();

    /**
     * @brief Update game state with delta time timing.
     *
     * Calculates delta time for frame-independent movement.
     * Updates paddle positions, ball physics, collision detection,
     * and scoring when game is active (not gameover).
     */
    void update();

    /**
     * @brief Render the game frame.
     *
     * Draws paddles, ball, UI window with scores and controls.
     * Displays win/lose message when game ends.
     * Handles reset button to restart game.
     *
     * @retval true Continue running.
     * @retval false Exit game.
     */
    bool draw();

    /**
     * @brief Move player paddle based on joystick input.
     *
     * Player paddle moves up/down with joystick Y percentage.
     * Computer paddle tracks ball position with velocity-based movement
     * when ball is in play.
     */
    void move_paddle();

    /**
     * @brief Update ball position based on velocity and delta time.
     */
    void move_ball();

    /**
     * @brief Create and update UI window with game controls.
     *
     * Displays FPS, scores, trackbars for ball radius and speed.
     * Contains Reset and Exit buttons.
     *
     * @retval true UI updated successfully.
     * @retval false Exit button pressed.
     */
    bool make_ui_window();

    /**
     * @brief Calculate ball velocity on paddle collisions.
     *
     * Handles collision detection with both paddles.
     * Ball angle changes based on where it hits the paddle
     * for realistic physics. Applies speed multiplier from UI.
     */
    void ballsetvelocity();

    /**
     * @brief Handle ball collisions with screen boundaries.
     *
     * Bounces ball off top, bottom, left, and right walls.
     * Prevents ball from going outside play area.
     */
    void ballbounds();

    /**
     * @brief Keep paddles within screen boundaries.
     */
    void make_bounds_paddle();

    /**
     * @brief Check and update scoring.
     *
     * If ball passes right edge, computer scores.
     * If ball passes left edge, player scores.
     * Resets ball to center after each goal.
     */
    void ball_goal();

};