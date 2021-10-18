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
 * @file test.cpp
 * @author Phase 1 - Mayank Joshi (driver) and Naitri Rajyaguru (navigator)
 * @brief Unit Tests for Acme Robotics - Human Tracker
 * @version 0.1
 * 
 * @copyright MIT License
 * 
 */

#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>


#include <AutoBot.hpp>
#include <HumanTracker.hpp>
#include <Detector.hpp>
#include <Utils.hpp>


acme::AutoBot robot_object(0, -1);
acme::HumanTracker tracker_object(0.1);
std::vector<std::string> classes = {"person"};
acme::Detector detect_object(0.2, classes);
acme::Utils utils_object;

TEST(AutoBot, Run) {
    acme::Mode mode = acme::Mode::kRealTime;
    robot_object.SetTestCounter(1);
    robot_object.SetShowWindow(false);
    ASSERT_NO_THROW(robot_object.Run(mode));

    mode = acme::Mode::kTesting;
    ASSERT_NO_THROW(robot_object.Run(mode));

    mode = acme::Mode::kTraining;
    ASSERT_NO_THROW(robot_object.Run(mode));
}
TEST(AutoBot, SetRobotPose) {
    acme::Pose p;
    ASSERT_NO_THROW(robot_object.SetRobotPose(p));
}
TEST(AutoBot, SetCameraPose) {
    acme::Pose p;
    ASSERT_NO_THROW(robot_object.SetCameraPose(p));
}
TEST(AutoBot, SetFocalLength) {
    double fl = 0.036;
    ASSERT_NO_THROW(robot_object.SetFocalLength(fl));
}
TEST(AutoBot, SetProcessingSize) {
    int w = 416;
    int h = 416;
    cv::Size s(w, h);
    ASSERT_NO_THROW(robot_object.SetProcessingSize(w, h));
    ASSERT_NO_THROW(robot_object.SetProcessingSize(s));
}
TEST(AutoBot, GetObjects) {
    ASSERT_EQ(0, static_cast<int>(robot_object.GetObjects().size()));
}
TEST(AutoBot, SetHumanHeight) {
    double height = 1.6;
    ASSERT_NO_THROW(robot_object.SetHumanHeight(height));
}

TEST(HumanTracker, TrackHumans) {
    cv::Mat img = cv::imread("..//data//test.png");
    auto output = tracker_object.TrackHumans(img);
    ASSERT_EQ(static_cast<int>(output.size()), 1);
}
TEST(Detection, structure) {
    std::string class_name = "person";
    acme::Detection temp_object(cv::Rect(1, 1, 1, 1), 0.4, class_name);

    ASSERT_EQ(static_cast<int>(temp_object.bbox.x), 1);
    ASSERT_EQ(static_cast<int>(temp_object.bbox.y), 1);
    ASSERT_EQ(static_cast<int>(temp_object.bbox.width), 1);
    ASSERT_EQ(static_cast<int>(temp_object.bbox.height), 1);
    ASSERT_EQ(temp_object.confidence, 0.4);
    ASSERT_EQ(temp_object.name, class_name);
}
TEST(Detector, Detect) {
    cv::Mat img = cv::imread("..//data//test.png");
    auto output = detect_object.Detect(img);
    ASSERT_EQ(static_cast<int>(output.size()), 1);
}
TEST(Detector, SetClassesToDetect) {
    ASSERT_NO_THROW(detect_object.SetClasses());
}
TEST(Detector, setNmsThresh) {
    ASSERT_NO_THROW(detect_object.SetNmsThresh(0.4));
}
TEST(Detector, setInputWIdth) {
    ASSERT_NO_THROW(detect_object.SetInputWIdth(640));
}
TEST(Detector, setInputHeight) {
    ASSERT_NO_THROW(detect_object.SetInputHeight(480));
}
TEST(Detector, setSwapRB) {
    ASSERT_NO_THROW(detect_object.SetSwapRB(true));
}
TEST(Detector, setCropImg) {
    ASSERT_NO_THROW(detect_object.SetCropImg(false));
}
TEST(Detector, setBackend) {
    ASSERT_NO_THROW(detect_object.SetBackend(0));
}
TEST(Detector, setTarget) {
    ASSERT_NO_THROW(detect_object.SetTarget(0));
}
TEST(Detector, setNumChannels) {
    ASSERT_NO_THROW(detect_object.SetNumChannels(3));
}
TEST(Detector, SetScaleFactor) {
    double sf = 1.0;
    ASSERT_NO_THROW(detect_object.SetScaleFactor(sf));
}
TEST(Detector, SetMeanToSubtract) {
    cv::Scalar mean = cv::Scalar();
    ASSERT_NO_THROW(detect_object.SetMeanToSubtract(mean));
}
TEST(Utils, FitWithinSize) {
    cv::Point p = cv::Point();
    cv::Size s = cv::Size();
    auto output = utils_object.FitWithinSize(p, s);
    ASSERT_EQ(output.x, -1);
    ASSERT_EQ(output.y, -1);

    cv::Rect r = cv::Rect();
    auto output2 = utils_object.FitWithinSize(r, s);
    ASSERT_EQ(output2.x, -1);
    ASSERT_EQ(output2.y, -1);
    ASSERT_EQ(output2.width, -1);
    ASSERT_EQ(output2.height, -1);
}
TEST(Utils, DrawBbox) {
    cv::Mat img = cv::Mat::zeros(cv::Size(100, 100), CV_8UC3);
    std::vector<cv::Rect> boxes = {cv::Rect(2, 2, 2, 2)};
    auto output  = utils_object.DrawBbox(img, boxes);
    ASSERT_EQ(static_cast<int>(output.cols), 100);
    ASSERT_EQ(static_cast<int>(output.rows), 100);
}
TEST(Utils, GetBboxCenter) {
    cv::Rect r = cv::Rect();
    auto output = utils_object.GetBboxCenter(r);
    ASSERT_EQ(output.x, -1);
    ASSERT_EQ(output.y, -1);
}
TEST(Utils, GetBboxArea) {
    cv::Rect r = cv::Rect();
    auto output = utils_object.GetBboxArea(r);
    ASSERT_EQ(output, -1.0);
}
TEST(Utils, ResizeImage) {
    cv::Mat img = cv::Mat::zeros(cv::Size(10, 10), CV_8UC3);
    cv::Size s = cv::Size(20, 20);
    auto output  = utils_object.ResizeImage(img, s);
    ASSERT_EQ(static_cast<int>(output.cols), 20);
    ASSERT_EQ(static_cast<int>(output.rows), 20);
}
TEST(Utils, CalculateIOU) {
    cv::Rect r1 = cv::Rect();
    cv::Rect r2 = cv::Rect();
    auto output = utils_object.CalculateIOU(r1, r2);
    ASSERT_EQ(output, -1);
}
TEST(Utils, CalcuPixelsToPoselateIOU) {
    cv::Rect r = cv::Rect();
    double calib_factor = 0.2;
    auto output = utils_object.PixelsToPose(r, calib_factor);
    ASSERT_EQ(output.x, -1);
    ASSERT_EQ(output.y, -1);
    ASSERT_EQ(output.z, -1);
}
TEST(Utils, GetTransformedPose) {
    acme::Pose p1 = acme::Pose();
    acme::Pose p2 = acme::Pose();
    auto output = utils_object.GetTransformedPose(p1, p2);
    ASSERT_EQ(output.x, -1);
    ASSERT_EQ(output.y, -1);
    ASSERT_EQ(output.z, -1);
}
