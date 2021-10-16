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


#include <Detector.hpp>



acme::Detector::Detector(double conf, const std::vector<std::string> &classes) {
    /// initializes default parameter and creates the model network
    InitModel(conf, classes);

    /// run the model once before actually performing detection on video frame
    WarmUp();
}
acme::Detector::~Detector() {}

std::vector<acme::Detection> acme::Detector::Detect(const cv::Mat& frame) {
    /// create a vector to store Detection objects
    std::vector<acme::Detection> detections = {};

    /// create a Mat to store the input blob
    cv::Mat b;
    if ( !frame.empty() ) {
        /// create a blob for the model to run a forward pass
        b = cv::dnn::blobFromImage(frame, scale_, size_, mean_, swap_, crop_);

        /// set input for the model
        network_.setInput(b);
        outputs_.clear();

        /// run a forward pass
        network_.forward(outputs_, out_names_);
        cv::Size img_size = frame.size();

        /// process the outputs of the model forward pass
        detections = ProcessNet(img_size);
    }
    return detections;
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

std::vector<acme::Detection> acme::Detector::ProcessNet(const cv::Size &s) {}
