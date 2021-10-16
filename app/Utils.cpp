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
 * @author Phase 1 - Mayank Joshi (driver) and Naitri Rajyaguru (navigator)
 * @brief Utils class definition for Acme Robotics - Human Tracker
 * @version 0.1
 * 
 * @copyright MIT License
 * 
 */


#include <Utils.hpp>


cv::Point acme::Utils::FitWithinSize(const cv::Point &p, const cv::Size &s) {
    return cv::Point(-1, -1);
}

cv::Rect acme::Utils::FitWithinSize(const cv::Rect &b, const cv::Size &s) {
    return cv::Rect(-1, -1, -1, -1);
}

cv::Mat acme::Utils::DrawBbox(cv::Mat i, const std::vector<cv::Rect> &b) {
    cv::Mat frame = i.clone();
    cv::Scalar color = cv::Scalar(0, 0, 255);
    cv::Scalar l_color = cv::Scalar::all(255);
    int counter(0);
    std::string label;
    int f_face(0);
    double f_scale(1);
    cv::Point l_pt;
    cv::Point top_pt;
    cv::Point bottom_pt;
    int b_line(0);
    cv::Size l_size;
    for ( cv::Rect box : b ) {
        cv::rectangle(frame, box, color, 2, cv::LINE_AA);
        counter++;
        label = std::to_string(counter);
        l_size = cv::getTextSize(label, f_face, f_scale, 2, &b_line);
        top_pt = cv::Point(box.x, box.y);
        bottom_pt = cv::Point(box.x + l_size.width, box.y+l_size.height);
        l_pt = cv::Point(box.x, box.y+l_size.height);
        cv::rectangle(frame, top_pt, bottom_pt, color, -1, 16);
        cv::putText(frame, label, l_pt, f_face, f_scale, l_color, 2);
    }
    return frame;
}

cv::Point acme::Utils::GetBboxCenter(const cv::Rect &bbox) {
    return cv::Point(-1, -1);
}

double acme::Utils::GetBboxArea(const cv::Rect &bbox) {
    return -1.0;
}

cv::Mat acme::Utils::ResizeImage(const cv::Mat &i, const cv::Size &s) {
    cv::Mat out_img;
    cv::resize(i, out_img, s);
    return out_img;
}

double acme::Utils::CalculateIOU(const cv::Rect& b1, const cv::Rect& b2) {
    return -1.0;
}

acme::Pose acme::Utils::PixelsToPose(const cv::Rect &b, double calib_factor) {
    return acme::Pose();
}

acme::Pose acme::Utils::GetTransformedPose(const Pose& src, const Pose& dst) {
    return acme::Pose();
}
