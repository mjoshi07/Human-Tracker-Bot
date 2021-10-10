/**
 * @file Detector.cpp
 * @author Mayank Joshi (driver) and Naitri Rajyaguru (navigator)
 * @brief Detection class definition for Acme Robotics - Human Tracker
 * @version 0.1
 * @date 2021-10-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#include <Detector.h>


acme::Detector::Detector(double conf, const std::vector<std::string> &classes) {
}
acme::Detector::~Detector() {}

std::vector<cv::Rect> acme::Detector::Detect(const cv::Mat& frame) {
    return std::vector<cv::Rect>();
}

void acme::Detector::SetClasses(const std::vector<std::string> &classes) {}

void acme::Detector::setNmsThresh(const double nms_thresh) {}

void acme::Detector::setInputWIdth(const int input_width) {}

void acme::Detector::setInputHeight(const int input_height) {}

void acme::Detector::setSwapRB(const bool swap_rb) {}

void acme::Detector::setCropImg(const bool crop_img) {}

void acme::Detector::setBackend(const int backend) {}

void acme::Detector::setTarget(const int target) {}

void acme::Detector::setNumChannels(const int num_channels) {}

void acme::Detector::initModel(int backend, int target) {}

void acme::Detector::WarmUp() {}

