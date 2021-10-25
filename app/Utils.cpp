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
 * @author Phase 2 -  Naitri Rajyaguru (driver) and Mayank Joshi (navigator)
 * @brief Utils class definition for Acme Robotics - Human Tracker
 * @version 0.1
 * 
 * @copyright MIT License
 * 
 */


#include <Utils.hpp>


cv::Mat acme::Utils::DrawBbox(cv::Mat i, const cv::Rect& b,
    const std::string &l) {
    /// creating a copy of frame
    cv::Mat frame = i.clone();

    /// set color for Bbox
    cv::Scalar color = cv::Scalar(0, 0, 255);

    /// set color for label x
    cv::Scalar l_color = cv::Scalar::all(255);

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

    /// draws rectangle on frame
    cv::rectangle(frame, b, color, 2, cv::LINE_AA);

    /// get label size
    l_size = cv::getTextSize(l, f_face, f_scale, 2, &b_line);

    /// get top point for label rectangle
    top_pt = cv::Point(b.x, b.y);

    /// get bottom point for label rectangle
    bottom_pt = cv::Point(b.x + l_size.width, b.y+l_size.height);

    ///  get point for label
    l_pt = cv::Point(b.x, b.y+l_size.height);

    /// draw rectangle for label
    cv::rectangle(frame, top_pt, bottom_pt, color, -1, 16);

    /// display text of label
    cv::putText(frame, l, l_pt, f_face, f_scale, l_color, 2);
    return frame;
}

cv::Point acme::Utils::GetBboxCenter(const cv::Rect &bbox) {
    int x_center = bbox.width / 2 + bbox.x;
    int y_center = bbox.height / 2 + bbox.y;
    return cv::Point(x_center, y_center);
}

double acme::Utils::GetBboxArea(const cv::Rect &bbox) {
    double area = 0;
    area = bbox.width*bbox.height;
    return area;
}

cv::Mat acme::Utils::ResizeImage(const cv::Mat &i, const cv::Size &s) {
    cv::Mat out_img;
    cv::resize(i, out_img, s);
    return out_img;
}

double acme::Utils::CalculateIOU(const cv::Rect& b1, const cv::Rect& b2) {
    /// get min and max values of 1st bounding box
    double minx1 = b1.x;
    double maxx1 = b1.x + b1.width;
    double miny1 = b1.y;
    double maxy1 = b1.y+ b1.height;

    /// get min and max values of 2nd bounding box
    double minx2 = b2.x;
    double maxx2 = b2.x + b2.width;
    double miny2 = b2.y;
    double maxy2 = b2.y + b2.height;

    /// calculate intersecting x and y point
    double inter_x = std::min(maxx2, maxx1) - std::max(minx2, minx1);
    double inter_y = std::min(maxy2, maxy1) - std::max(miny2, miny1);

    /// calculate area of bboxes
    double area1 = (maxx1 - minx1)*(maxy1 - miny1);
    double area2 = (maxx2 - minx2)*(maxy2 - miny2);

    /// calculate intersection
    double inter = inter_x * inter_y;
    /// calculate union
    double uni = area1 + area2 - inter;
    /// calculate Intersection over Union
    if ( uni != 0 ) {
    return inter / uni;
    } else { return 0.0; }
}

acme::Pose acme::Utils::PixelsToPose(const cv::Rect &b, double calib_factor) {
    /// height of object in pixels
    double height = b.height;
    /// calibrated distance using focal length and calib factor
    double calib_distance = calib_factor/ height;
    /// get centre of bbox
    cv::Point centre = acme::Utils::GetBboxCenter(b);


    return acme::Pose(calib_distance, centre.x, centre.y);
}

