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

