//Anita Huang Feb 2026
//CPong.cpp (CHILD)

#include "stdafx.h"
#include "CPong.h"
#include "cvui.h"
#include <chrono>
#include <thread>
#include "math.h"



const int IMGTYPE = CV_8UC3;

const int JOYSTICK_X = 2;
const int JOYSTICK_Y = 26;

const int ACCL_Y = 23;
const int ACCL_Z = 24;

const int PUSH_BUTTON_2 = 42;
const int DIGITAL = 0;
const int BIG_BUTTON_1 = 32;
const int BIG_BUTTON_2 = 33;

const int PIXEL_BOUNDS_B = 792;
const int PIXEL_BOUNDS_U = 5;

const int SLOW_BOUNDS_X = 55;
const int FAST_BOUNDS_X = 80;

const int SLOW_BOUNDS_Y = 45;
const int FAST_BOUNDS_Y = 20;

const int RGB_RED = 39;
const int RGB_GRN = 38;
const int RGB_BLU = 37;

const int ui_left = 100;
const int ui_right = 180;


const int R_paddlemargin = 950;
const int L_paddlemargin = 50;

const int buffer = 10;

//

CPong::CPong(cv::Size canvassize, int comportnumber) {

	comm.init_com(comportnumber);
	cvui::init("Pong");
	_canvas = cv::Mat::zeros(canvassize, IMGTYPE);

	percentage_y = 0;
	spd = 100;
	ball_radius = 5;

	paddletop = cv::Point(R_paddlemargin, 350);
	paddlebottom = cv::Point(R_paddlemargin, 450);

	paddlebot_top = cv::Point(L_paddlemargin, 350);
	paddlebot_bottom = cv::Point(L_paddlemargin, 450);

	pos_ball = cv::Point(500, 400);
	vel_ball = cv::Point(100, 0); //Inital speed


	botgoal = 0;
	playergoal = 0;
	reset_button_pressed = false;
	fps = 0;
	gameover = false;
	dt = 0;


}


CPong::~CPong() {

}


void CPong::gpio() {

	//Reading Joystick Y Input
	int raw_y;
	percentage_y = comm.get_analog(JOYSTICK_Y, raw_y);


}


void CPong::update()
{
	float timescale = 0.9;
	static double last_time = cv::getTickCount() / cv::getTickFrequency(); // note on this 
	double new_time = cv::getTickCount() / cv::getTickFrequency();
	dt = new_time - last_time;
	last_time = new_time;
	std::cout << "\n" << dt << "\n";

	double start_tic, freq, elapsed_time;
	start_tic = cv::getTickCount();
	freq = cv::getTickFrequency();
	auto end_time = std::chrono::steady_clock::now() + std::chrono::milliseconds(24);


	// This segment gets its time recorded //
	if (gameover == false) {
		make_bounds_paddle();
		move_paddle();
		ballsetvelocity();
		ballbounds();
		move_ball();
		ball_goal();
	}

	std::this_thread::sleep_until(end_time);
	elapsed_time = (cv::getTickCount() - start_tic) / freq;
	fps = (timescale / elapsed_time) ;

}


bool CPong::draw() {


	cv::Scalar White = cv::Scalar(255, 255, 255);


	//Clear Current Canvas
	cv::Size canvassize = cv::Size(1000, 800);
	_canvas = cv::Mat::zeros(canvassize, IMGTYPE);

	//Make UI Mini Window 
	if (make_ui_window() == 0) { return false; }

	if (playergoal == 5) {
		cvui::text(_canvas, 300, 100, "You Win!", 4);
		gameover = true;
	}
	else if (botgoal == 5) {
		cvui::text(_canvas, 300, 100, "You Lose!", 4);
		gameover = true;

	}

	//Draw Paddles
	cv::line(_canvas, paddletop, paddlebottom, White, 4, cv::LINE_AA);
	cv::line(_canvas, paddlebot_top, paddlebot_bottom, White, 4, cv::LINE_AA);

	//The Ball
	cv::circle(_canvas, pos_ball, ball_radius, White, CVUI_FILLED);


	//Update and Show
	cvui::update();
	cv::imshow("Pong", _canvas);

	return 1;

}





//      //        !The Helper Functions!      //         //


void CPong::make_bounds_paddle() {

	//your bounds
	if (PIXEL_BOUNDS_U > paddletop.y) {
		paddletop.y = PIXEL_BOUNDS_U;
		paddlebottom.y = PIXEL_BOUNDS_U + 100;

	}
	else if (PIXEL_BOUNDS_B < paddlebottom.y) {
		paddlebottom.y = PIXEL_BOUNDS_B;
		paddletop.y = PIXEL_BOUNDS_B - 100;
	}
	//bot bounds
	if (PIXEL_BOUNDS_U > paddlebot_top.y) {
		paddlebot_top.y = PIXEL_BOUNDS_U;
		paddlebot_bottom.y = PIXEL_BOUNDS_U + 100;

	}
	else if (PIXEL_BOUNDS_B < paddlebot_bottom.y) {
		paddlebot_bottom.y = PIXEL_BOUNDS_B;
		paddlebot_top.y = PIXEL_BOUNDS_B - 100;
	}
}




void CPong :: move_paddle() {

	//for player 
	if (80 < percentage_y) { //move up 

		paddletop.y = paddletop.y - 15;
		paddlebottom.y = paddlebottom.y - 15;

	}
	else if (20 > percentage_y) { //move down 

		paddletop.y = paddletop.y + 15;
		paddlebottom.y = paddlebottom.y + 15;

	}

	//for bot 

	if (pos_ball.x < 600 && pos_ball.x > 100) {

		int centerofbot = paddlebot_bottom.y - 50;

		if (centerofbot < pos_ball.y) {// if paddle (lowervalue) higher than ball

			paddlebot_top.y = paddlebot_top.y + std::abs(vel_ball.y * dt);
			paddlebot_bottom.y = paddlebot_bottom.y + std::abs(vel_ball.y * dt);

		}
		else if (centerofbot > pos_ball.y) { // if paddle (higherval) is lower than ball

			paddlebot_top.y = paddlebot_top.y - std::abs(vel_ball.y * dt);
			paddlebot_bottom.y = paddlebot_bottom.y - std::abs(vel_ball.y * dt);

		}
		else{
			//do nothing
		}

		

	}

}

void CPong::move_ball() {

	pos_ball.x = pos_ball.x + vel_ball.x * dt ;
	pos_ball.y = pos_ball.y + vel_ball.y * dt ;

}



bool CPong:: make_ui_window () {

	//Draw CVUI for Buttons and Text
	cvui::window(_canvas, 90, 10, 210, 210, "Anita's Pong Game!");
	cvui::text(_canvas, 90, 40, cv::format("FPS: %.1f", fps));
	cvui::text(_canvas, ui_left, 60, cv::format("PLAYER: %i", playergoal));
	cvui::text(_canvas, ui_right, 60, cv::format("COMPUTER: %i", botgoal));

	//Track Bars
	cvui::text(_canvas, 150, 90, "Ball Radius");
	cvui::trackbar(_canvas, ui_left, 90, 190, &ball_radius, 5, 100);

	cvui::text(_canvas, 150, 140, "Speed");
	cvui::trackbar(_canvas, ui_left, 140, 190, &spd, 100, 400);


	reset_button_pressed = cvui::button(_canvas, ui_left, 190, "Reset");

	if (reset_button_pressed) {

		cv::Size canvassize = cv::Size(1000, 800);
		_canvas = cv::Mat::zeros(canvassize, IMGTYPE);
		playergoal = 0;
		botgoal = 0;
		gameover = false;

		paddletop = cv::Point(R_paddlemargin, 350);
		paddlebottom = cv::Point(R_paddlemargin, 450);

		paddlebot_top = cv::Point(L_paddlemargin, 350);
		paddlebot_bottom = cv::Point(L_paddlemargin, 450);

		pos_ball = cv::Point(500, 400);
		vel_ball = cv::Point(100, 0); 


	}
	if (cvui::button(_canvas, 210, 190, "Exit")) {
		return false;
	}


	return true;


}

void CPong:: ballsetvelocity() {

	//Make changes for speed modualtion bar (verlocity overall scaled higher)
	double speed_factor = spd / (sqrt((vel_ball.x * vel_ball.x) + (vel_ball.y * vel_ball.y))); 
	vel_ball.x = vel_ball.x * speed_factor; 
	vel_ball.y = vel_ball.y * speed_factor;
	//

	if (ball_radius + pos_ball.x + buffer >= R_paddlemargin &&
		pos_ball.y  + ball_radius >= paddletop.y &&
		pos_ball.y  - ball_radius <= paddlebottom.y
		) {

		double p_y, p_x;
		double paddle_center_pos = (paddletop.y + paddlebottom.y) / 2;
		double difference_center = paddle_center_pos - pos_ball.y;


		p_y = difference_center * 0.7 * 0.02;
		p_x = 1 - p_y;

		if (difference_center == 0) {

			vel_ball.x = std::abs(vel_ball.x) * -1;

		}
		else if (difference_center > 0) { //higher portion

			vel_ball.x = -spd * p_x;
			vel_ball.y = -spd * p_y;

		}
		else if (difference_center < 0) { //lower portion 

			vel_ball.x = -spd * p_x;
			vel_ball.y = -spd * p_y;

		}

	}

	 else if (-ball_radius + pos_ball.x - buffer <= L_paddlemargin &&
		pos_ball.y + ball_radius >= paddlebot_top.y &&
		pos_ball.y - ball_radius <= paddlebot_bottom.y
		) {
			double p_y, p_x;
			double paddle_center_pos = (paddlebot_top.y + paddlebot_bottom.y) / 2;
			double difference_center = paddle_center_pos - pos_ball.y;


			p_y = difference_center * 0.6 * 0.02;
			p_x = 1 - p_y;

			if (difference_center == 0) {

				vel_ball.x = std::abs(vel_ball.x);

			}
			else if (difference_center > 0) { //higher portion

				vel_ball.x = std::abs (spd * p_x);
				vel_ball.y = -spd * p_y;

			}
			else if (difference_center < 0) { //lower portion 

				vel_ball.x = std::abs (spd * p_x);
				vel_ball.y = -spd * p_y;

			}

		}





}

void CPong::ballbounds() {

	//Ball bounds
	float ball_top = ball_radius + buffer;
	float ball_bottom = 800 - buffer - ball_radius;

	float boundright = ball_radius;
	float boundleft = -ball_radius + 1000;

	if (pos_ball.y <= ball_top) {

		pos_ball.y = ball_top;

		vel_ball.y = std::abs(vel_ball.y);


	}

	if (pos_ball.y >= ball_bottom) {

		pos_ball.y = ball_bottom;

		vel_ball.y = -1 * std::abs(vel_ball.y);

	}

	if (pos_ball.x <= boundright) {

		pos_ball.x = boundright;

		vel_ball.x = std::abs(vel_ball.x);

	}

	if (pos_ball.x >= boundleft) {

		pos_ball.x = boundleft;

		vel_ball.x = -1*std::abs(vel_ball.x);

	}


}


void CPong::ball_goal() {
	if (pos_ball.x + ball_radius >= 995) {
		botgoal++;
		pos_ball = cv::Point(500, 400);
		vel_ball = cv::Point(std::abs(vel_ball.x), 0);
	}
	if (pos_ball.x - ball_radius <= 5) {
		playergoal++;
		pos_ball = cv::Point(500, 400);
		vel_ball = cv::Point(std::abs(vel_ball.x), 0);
	}
}