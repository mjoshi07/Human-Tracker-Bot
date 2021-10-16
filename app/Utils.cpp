/******************************************************************************
 * MIT License
 * 
 * Copyright (c) 2021 Mayank Joshi, Naitri Rajyaguru
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 ******************************************************************************/

/**
 * @file Utils.cpp
 * @author Mayank Joshi (driver) and Naitri Rajyaguru (navigator)
 * @brief Utils class definition for Acme Robotics - Human Tracker
 * @version 0.1
 * @date 2021-10-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#include <Utils.h>


cv::Point acme::Utils::FitWithinSize(const cv::Point &p, const cv::Size &s) {
    return cv::Point(-1, -1);
}

cv::Rect acme::Utils::FitWithinSize(const cv::Rect &b, const cv::Size &s) {
    return cv::Rect(-1, -1, -1, -1);
}

cv::Point acme::Utils::GetBboxCenter(const cv::Rect &bbox) {
    return cv::Point(-1, -1);
}

double acme::Utils::GetBboxArea(const cv::Rect &bbox) {
    return -1.0;
}

cv::Mat acme::Utils::ResizeImage(const cv::Mat &img, const cv::Size &s) {
    return cv::Mat(cv::Size(1, 1), 0);
}

double acme::Utils::CalculateIOU(const cv::Rect& b1, const cv::Rect& b2) {
    return -1.0;
}

acme::Pose acme::Utils::PixelsToPose(const cv::Rect &b, double calib_factor) {
    return acme::Pose();
}

acme::Pose acme::Utils::GetTransformedPose(const Pose& dst, const Pose& src) {
    return acme::Pose();
}
