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

using namespace acme;

Detector::Detector(double conf_thresh, std::vector<std::string> classes_to_detect, double nms_thresh,  int input_width, int input_height, bool swap_RB, bool crop_img, int backend, int target, int num_channels) {}
Detector::~Detector() {}

std::vector<cv::Rect> Detector::Detect(cv::Mat& frame) {
    return std::vector<cv::Rect>();
}

void Detector::SetClassesToDetect(std::vector<std::string> classes_to_detect) {}

void Detector::setNmsThresh(double nms_thresh) {}

void Detector::setInputWIdth(int input_width) {}

void Detector::setInputHeight(int input_height) {}

void Detector::setSwapRB(bool swap_rb) {}

void Detector::setCropImg(bool crop_img) {}

void Detector::setBackend(int backend) {}

void Detector::setTarget(int target) {}

void Detector::setNumChannels(int num_channels) {}

void Detector::initModel(std::string weights, std::string config, int backend, int target) {}

void Detector::WarmUp() {}

