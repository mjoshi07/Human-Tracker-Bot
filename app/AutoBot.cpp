/**
 * @file AutoBot.cpp
 * @author Mayank Joshi (driver) and Naitri Rajyaguru (navigator)
 * @brief AutoBot class definition for Acme Robotics - Human Tracker
 * @version 0.1
 * @date 2021-10-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <AutoBot.h>


acme::AutoBot::AutoBot() {}

acme::AutoBot::AutoBot(bool is_calibrated, double calib_factor) {}

acme::AutoBot::~AutoBot() {}

void acme::AutoBot::Run(const Mode mode) {}

void acme::AutoBot::SetRobotPose(const Pose &robo_pose) {}

void acme::AutoBot::CollectTrainData() {}

void acme::AutoBot::DetectTestData() {}

std::vector<acme::Pose>  acme::AutoBot::RunRealTime() {
    return std::vector<acme::Pose>();
}

void acme::AutoBot::Calibrate() {}
