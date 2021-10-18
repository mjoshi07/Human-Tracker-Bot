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
 * @file HumanTracker.cpp
 * @author Mayank Joshi (driver) and Naitri Rajyaguru (navigator)
 * @brief HumanTracker class definition for Acme Robotics - Human Tracker
 * @version 0.1
 * @date 2021-10-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#include <HumanTracker.hpp>


acme::HumanTracker::HumanTracker(double confidence) {
    /// initialize default parameters used by HumanTracker class object
    InitParams(confidence);
}

acme::HumanTracker::~HumanTracker() {}

void acme::HumanTracker::InitParams(double confidence) {
    /// set conf threshold value to filter out the detections
    conf_thresh_ = confidence;

    /// set conf for detector object
    double detector_conf(0.2);

    /// set the classes to detect by the Detector
    std::vector<std::string> classes{"person"};

    /// create a Detector class object
    detector_ = std::make_unique<acme::Detector>(detector_conf, classes);

    /// clear the vector which will store the detections
    humans_.clear();

    /// create an opencv tracker
    tracker_ = cv::TrackerKCF::create();
}

std::vector<cv::Rect> acme::HumanTracker::TrackHumans(const cv::Mat &frame) {
    /// clear the vector which will store the detections
    humans_.clear();

    /// get vector of Detection object by running Detector on the frame
    std::vector<acme::Detection> output = detector_->Detect(frame);

    /// filter out the detections
    RemoveNoise(output);

    return humans_;
}

void acme::HumanTracker::RemoveNoise(const std::vector<acme::Detection> &d) {
    for ( acme::Detection detect : d ) {
        if (detect.confidence >= conf_thresh_) {
            /// store the detection only if the detected conf > conf_thresh
            humans_.push_back(detect.bbox);
        }
    }
}
