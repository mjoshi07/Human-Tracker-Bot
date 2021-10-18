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
    /// creating a copy of frame
    cv::Mat frame = i.clone();

    /// set color for Bbox
    cv::Scalar color = cv::Scalar(0, 0, 255);

    /// set color for label x
    cv::Scalar l_color = cv::Scalar::all(255);

    /// initialize ID for each box
    int id(0);

    std::string label;

    /// initialize font type
    int f_face(0);

    /// initialize font scale
    double f_scale(1);

    /// variable to store label point
    cv::Point l_pt;
    /// variable to store label top point
    cv::Point top_pt;
    /// variable to store label bottom point
    cv::Point bottom_pt;

    /// initialize baseline
    int b_line(0);

    /// variable for label size
    cv::Size l_size;

    for ( cv::Rect box : b ) {
        /// draws rectangle on frame
        cv::rectangle(frame, box, color, 2, cv::LINE_AA);

        /// increment ID for next Bbox
        id++;

        /// converting ID type to string for displaying
        label = std::to_string(id);

        /// get label size
        l_size = cv::getTextSize(label, f_face, f_scale, 2, &b_line);

        /// get top point for label rectangle
        top_pt = cv::Point(box.x, box.y);

        /// get bottom point for label rectangle
        bottom_pt = cv::Point(box.x + l_size.width, box.y+l_size.height);

        ///  get point for label
        l_pt = cv::Point(box.x, box.y+l_size.height);

        /// draw rectangle for label
        cv::rectangle(frame, top_pt, bottom_pt, color, -1, 16);

        /// display text of label
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
