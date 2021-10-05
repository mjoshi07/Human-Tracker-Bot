/**
 * @file test.cpp
 * @author Mayank Joshi (driver) and Naitri Rajyaguru (navigator)
 * @brief Utils class definition for Acme Robotics - Human Tracker
 * @version 0.1
 * @date 2021-10-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#include <Utils.h>

cv::Point acme::Utils::GetPointWithinImage(cv::Point &p, cv::Size &img_size) {
    return cv::Point(-1, -1);
}

cv::Rect acme::Utils::GetBboxWithinImage(cv::Rect &bbox, cv::Size &img_size) {
    return cv::Rect(-1, -1, -1, -1);
}

cv::Point acme::Utils::GetBboxCenter(cv::Rect &bbox) {
    return cv::Point(-1, -1);
}

double acme::Utils::GetBboxArea(cv::Rect &bbox) {
    return -1.0;
}

void acme::Utils::ResizeImage(cv::Mat &input_img, cv::Size &target_size) {}

double acme::Utils::CalculateIOU(const cv::Rect& bbox1, const cv::Rect& bbox2) {
    return -1.0;
}

acme::Pose acme::Utils::PixelsToPose(cv::Rect &bbox, double calib_factor) {
    return acme::Pose();
}

acme::Pose acme::Utils::GetTransformedPose(const Pose& dest_frame_of_ref, const Pose& src_frame_of_ref) {
    return acme::Pose();
}
