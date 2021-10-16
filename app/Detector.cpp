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

void acme::Detector::SetClasses(const std::vector<std::string> &classes) {
    classes_ = classes;
}

void acme::Detector::SetNmsThresh(const double nms_thresh) {
    nms_thresh_ = nms_thresh;
}

void acme::Detector::SetInputWIdth(const int input_width) {
    input_width_ = input_width;
}

void acme::Detector::SetInputHeight(const int input_height) {
    input_height_ = input_height;
}

void acme::Detector::SetScaleFactor(const double scale_factor) {
    scale_ = scale_factor;
}

void acme::Detector::SetSwapRB(const bool swap_rb) {
    swap_ = swap_rb;
}

void acme::Detector::SetMeanToSubtract(const cv::Scalar &mean) {
    mean_ = mean;
}

void acme::Detector::SetCropImg(const bool crop_img) {
    crop_ = crop_img;
}

void acme::Detector::SetBackend(const int backend) {
    backend_ = backend;
}

void acme::Detector::SetTarget(const int target) {
    target_ = target;
}

void acme::Detector::SetNumChannels(const int num_channels) {
    num_channels_ = num_channels;
}

void acme::Detector::InitModel(double conf, const std::vector<std::string> &c) {
    conf_thresh_ = conf;
    classes_ = c;
    nms_thresh_ = 0.4;
    input_width_ = 416;
    input_height_ = 416;
    size_ = cv::Size(input_width_, input_height_);
    scale_ = 0.00392157;
    mean_ = cv::Scalar();
    swap_ = true;
    crop_ = false;
    backend_ = 0;
    target_ = 0;
    num_channels_ = 3;
    all_classes_ = {"person", "bicycle", "car", "motorbike", "aeroplane",
     "bus", "train", "truck", "boat", "traffic light", "fire hydrant",
      "stop sign", "parking meter", "bench", "bird", "cat", "dog", "horse",
      "sheep", "cow", "elephant", "bear", "zebra", "giraffe", "backpack",
      "umbrella", "handbag", "tie", "suitcase", "frisbee", "skis", "snowboard",
      "sports ball", "kite", "baseball bat", "baseball glove", "skateboard",
      "surfboard", "tennis racket", "bottle", "wine glass", "cup", "fork",
      "knife", "spoon", "bowl", "banana", "apple", "sandwich", "orange",
      "broccoli", "carrot", "hot dog", "pizza", "donut", "cake", "chair",
      "sofa", "pottedplant", "bed", "diningtable", "toilet", "tvmonitor",
      "laptop", "mouse", "remote", "keyboard", "cell phone", "microwave",
      "oven", "toaster", "sink", "refrigerator", "book", "clock", "vase",
      "scissors", "teddy bear", "hair drier", "toothbrush" };

    std::string weights_path = "..//data//yolov4-tiny.weights";
    std::string config_path = "..//data//yolov4-tiny.cfg";
    network_ = cv::dnn::readNet(weights_path, config_path);
    network_.setPreferableBackend(backend_);
    network_.setPreferableTarget(target_);
    out_names_ = network_.getUnconnectedOutLayersNames();
}

void acme::Detector::WarmUp() {}

std::vector<acme::Detection> acme::Detector::ProcessNet(const cv::Size &s) {}
