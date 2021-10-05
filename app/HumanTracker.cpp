/**
 * @file HumanTracker.cpp
 * @author Mayank Joshi (driver) and Naitri Rajyaguru (navigator)
 * @brief HumanTracker class definition for Acme Robotics - Human Tracker
 * @version 0.1
 * @date 2021-10-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#include <HumanTracker.h>

using namespace acme;

HumanTracker::HumanTracker(double confidence) {}

HumanTracker::~HumanTracker() {}

void HumanTracker::InitParams(double confidence) {}

std::vector<cv::Rect> HumanTracker::TrackHumans(cv::Mat &frame) {
    return std::vector<cv::Rect>();
}

void HumanTracker::ProcessFrame(cv::Mat &frame) {}
