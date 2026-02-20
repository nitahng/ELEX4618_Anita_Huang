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


void move_paddle(cv::Point& pt1, cv::Point& pt2, float& percentage_y);
void move_ball(cv::Point& pos_ball, cv::Point& vel_ball, double &dt);



CPong::CPong(cv::Size canvassize, int comportnumber) {

	comm.init_com(comportnumber);
	cvui::init("Pong");
	_canvas = cv::Mat::zeros(canvassize, IMGTYPE);
	spd = 100;
	ball_radius = 5;
	paddlebot_top = cv::Point(L_paddlemargin, 350);
	paddlebot_bottom = cv::Point(L_paddlemargin, 450);
	botgoal = 0;
	playergoal = 0;

}


CPong::~CPong() {

}


void CPong::gpio(CControl& comm, float& percentage_x, float& percentage_y, bool& bigbutton1, bool& bigbutton2) {

	//Reading Joystick Y Input
	int raw_y;
	percentage_y = comm.get_analog(JOYSTICK_Y, raw_y);

	//Live Input Read
	//std::cout << "ANALOG TEST: " << "    Y_CH" << JOYSTICK_Y << " = " << raw_y << " (" << percentage_y << "%" << ") " << "\n";

}


void CPong::update(float& percentage_x, float& percentage_y, bool& colour_button_pressed, cv::Point& paddletop, cv::Point& paddlebottom, int& ball_radius, float& fps, cv::Point& pos_ball, cv::Point& vel_ball)
{
	static double last_time = cv::getTickCount() / cv::getTickFrequency(); // note on this 
	double new_time = cv::getTickCount() / cv::getTickFrequency();
	double dt = new_time - last_time;
	last_time = new_time;
	std::cout << "\n" << dt << "\n";

	double start_tic, freq, elapsed_time;
	start_tic = cv::getTickCount();
	freq = cv::getTickFrequency();
	auto end_time = std::chrono::steady_clock::now() + std::chrono::milliseconds(19);
	

	// This segment gets its time recorded //
	
	make_bounds_paddle(paddletop, paddlebottom, paddlebot_top, paddlebot_bottom); //bounds for the paddle
	move_paddle(paddletop, paddlebottom, percentage_y);
	ballsetvelocity(pos_ball, vel_ball, paddletop, paddlebottom);
	ballbounds(pos_ball, vel_ball);
	move_ball(pos_ball, vel_ball, dt);

	
	if (pos_ball.x >= 995) {
		botgoal++;
		pos_ball = cv::Point(500, 400);
		vel_ball = cv::Point(std::abs(vel_ball.x), 0); 
	}
	if (pos_ball.x <= 5) {
		playergoal++;
		pos_ball = cv::Point(500, 400);
		vel_ball = cv::Point(std::abs(vel_ball.x), 0);
	}

	//
	
	std::this_thread::sleep_until(end_time);
	elapsed_time = (cv::getTickCount() - start_tic) / freq;
	fps = 1/elapsed_time;
	//std::cout << "  elapsed time:" << elapsed_time << "   " << "  fps: " << fps << "   ";
	

}


bool CPong::draw(cv::Point& paddletop, cv::Point& paddlebottom, int& ball_radius, bool& reset_button_pressed, float& fps, cv::Point& pos_ball) {


	cv::Scalar White = cv::Scalar(255, 255, 255);


	//Clear Current Canvas
	cv::Size canvassize = cv::Size(1000, 800);
	_canvas = cv::Mat::zeros(canvassize, IMGTYPE);

	//Make UI Mini Window 
	if (make_ui_window(ball_radius, reset_button_pressed, fps) == 0) { return false; }

	//Draw Paddles
	cv::line(_canvas, paddletop, paddlebottom, White, 4, cv::LINE_AA);
	cv::line(_canvas, paddlebot_top, paddlebot_bottom, White, 4, cv::LINE_AA);

	//The Ball
	cv::circle(_canvas, pos_ball, ball_radius, White, CVUI_FILLED);


	cv::Point wintext = (400, 10);

	if (playergoal == 5) {
		cv::putText(_canvas, "You Win!", wintext, cv::FONT_HERSHEY_SIMPLEX, 1, White, 2, cv::LINE_AA);

	}
	if (botgoal == 5) {
		cv::putText(_canvas, "You Lose!", wintext, cv::FONT_HERSHEY_SIMPLEX, 1, White, 2, cv::LINE_AA);

	}


	//Update and Show
	cvui::update();
	cv::imshow("Pong", _canvas);

	return 1;

}





//      //        !The Helper Functions!      //         //


void CPong::make_bounds_paddle(cv::Point& paddletop, cv::Point& paddlebottom, cv::Point& paddlebot_top, cv::Point& paddlebot_bottom) {

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




void move_paddle(cv::Point& pt1, cv::Point& pt2, float& percentage_y) {

	if (80 < percentage_y) { //move up 

		pt1.y = pt1.y - 15;
		pt2.y = pt2.y - 15;

	}


	else if (20 > percentage_y) { //move down 

		pt1.y = pt1.y + 15;
		pt2.y = pt2.y + 15;

	}

}

void move_ball(cv::Point& pos_ball, cv::Point& vel_ball, double &dt) {

	pos_ball.x = pos_ball.x + vel_ball.x * dt ;
	pos_ball.y = pos_ball.y + vel_ball.y * dt ;

}



bool CPong:: make_ui_window(int& ball_radius, bool& reset_button_pressed, float& fps) {

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

	if (cvui::button(_canvas, ui_left, 190, "Reset") || reset_button_pressed == true) {
		//Implement this correctly 
		cv::Size canvassize = cv::Size(1000, 800);
		_canvas = cv::Mat::zeros(canvassize, IMGTYPE);
	}
	if (cvui::button(_canvas, 210, 190, "Exit")) {
		return false;
	}

	return true;


}

void CPong:: ballsetvelocity(cv::Point& pos_ball, cv::Point& vel_ball, cv::Point& paddletop, cv::Point& paddlebottom) {

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
}

void CPong::ballbounds(cv::Point& pos_ball, cv::Point& vel_ball) {

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