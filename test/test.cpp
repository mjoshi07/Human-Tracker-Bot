/**
 * @file test.cpp
 * @author Mayank Joshi (driver) and Naitri Rajyaguru (navigator)
 * @brief Unit Test for Acme Robotics - Human Tracker
 * @version 0.1
 * @date 2021-10-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>


#include <AutoBot.h>
#include <HumanTracker.h>
#include <Detector.h>
#include <Utils.h>


std::unique_ptr<acme::AutoBot> robot_object;
std::unique_ptr<acme::HumanTracker> tracker_object;
std::unique_ptr<acme::Detector> detect_object;
acme::Utils utils_object;

TEST(AutoBot, Run) {
    acme::Mode mode = acme::Mode::kRealTime;
    ASSERT_NO_THROW(robot_object->Run(mode));

    mode = acme::Mode::kTesting;
    ASSERT_NO_THROW(robot_object->Run(mode));

    mode = acme::Mode::kTraining;
    ASSERT_NO_THROW(robot_object->Run(mode));
}
TEST(AutoBot, SetRobotPose) {
    acme::Pose p;
    ASSERT_NO_THROW(robot_object->SetRobotPose(p));
}
TEST(HumanTracker, TrackHumans) {
    cv::Mat img;
    tracker_object = std::make_unique<acme::HumanTracker>(0.4);
    auto output = tracker_object->TrackHumans(img);
    ASSERT_EQ(static_cast<int>(output.size()), 0);
}
TEST(Detector, Detect) {
    cv::Mat img;
    auto output = detect_object->Detect(img);
    ASSERT_EQ(static_cast<int>(output.size()), 0);
}
TEST(Detector, SetClassesToDetect) {
    ASSERT_NO_THROW(detect_object->SetClasses());
}
TEST(Detector, setNmsThresh) {
    ASSERT_NO_THROW(detect_object->setNmsThresh(0.4));
}
TEST(Detector, setInputWIdth) {
    ASSERT_NO_THROW(detect_object->setInputWIdth(640));
}
TEST(Detector, setInputHeight) {
    ASSERT_NO_THROW(detect_object->setInputHeight(480));
}
TEST(Detector, setSwapRB) {
    ASSERT_NO_THROW(detect_object->setSwapRB(true));
}
TEST(Detector, setCropImg) {
    ASSERT_NO_THROW(detect_object->setCropImg(false));
}
TEST(Detector, setBackend) {
    ASSERT_NO_THROW(detect_object->setBackend(0));
}
TEST(Detector, setTarget) {
    ASSERT_NO_THROW(detect_object->setTarget(0));
}
TEST(Detector, setNumChannels) {
    ASSERT_NO_THROW(detect_object->setNumChannels(3));
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
    cv::Mat img;
    cv::Size s = cv::Size();
    auto output  = utils_object.ResizeImage(img, s);
    ASSERT_EQ(static_cast<int>(output.cols), 1);
    ASSERT_EQ(static_cast<int>(output.rows), 1);
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
