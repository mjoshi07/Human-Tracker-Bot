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

using namespace acme;

AutoBot::AutoBot() {}

AutoBot::AutoBot(bool is_calibrated, double calib_factor) {}

AutoBot::~AutoBot() {}

void AutoBot::Run(Mode mode) {}

void AutoBot::SetRobotPose(Pose robo_pose) {}

void AutoBot::CollectTrainData(std::string out_path, int num_imgs, int fps) {}

void AutoBot::DetectTestData(std::string test_data_path) {}

std::vector<Pose>  AutoBot::RunRealTime(std::string in_path, InputType type) {
    return std::vector<Pose>();
}

void AutoBot::Calibrate() {}
