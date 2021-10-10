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


acme::HumanTracker::HumanTracker(double confidence) {}

acme::HumanTracker::~HumanTracker() {}

void acme::HumanTracker::InitParams(double confidence) {}

std::vector<cv::Rect> acme::HumanTracker::TrackHumans(const cv::Mat &frame) {
    return std::vector<cv::Rect>();
}

void acme::HumanTracker::ProcessFrame(const cv::Mat &frame) {}
