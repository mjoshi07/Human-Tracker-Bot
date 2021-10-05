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
#include <AutoBot.h>
#include <HumanTracker.h>
#include <Detector.h>
#include <Utils.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>

using namespace acme;

std::unique_ptr<AutoBot> robot_object;
std::unique_ptr<HumanTracker> tracker_object = std::make_unique<HumanTracker>(0.4);
std::unique_ptr<Detector> detect_object;
Utils utils_object;

TEST(AutoBot, Run) {
    Mode mode = Mode::kRealTime;
    ASSERT_NO_THROW(robot_object->Run(mode));

    mode = Mode::kTesting;
    ASSERT_NO_THROW(robot_object->Run(mode));

    mode = Mode::kTraining;
    ASSERT_NO_THROW(robot_object->Run(mode));
}
TEST(AutoBot, SetRobotPose) {
    Pose p;
     ASSERT_NO_THROW(robot_object->SetRobotPose(p));
}
TEST(HumanTracker, TrackHumans) {
     cv::Mat img;
    auto output = tracker_object->TrackHumans(img);
     ASSERT_EQ(static_cast<int>(output.size()), 0);
}
TEST(Detector, Detect) {
    cv::Mat img;
     auto output = detect_object->Detect(img);
      ASSERT_EQ(static_cast<int>(output.size()), 0);
}
TEST(Detector, SetClassesToDetect) {
    ASSERT_NO_THROW(detect_object->SetClassesToDetect());
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
TEST(Utils, GetPointWithinImage) {
    cv::Point p = cv::Point();
    cv::Size s = cv::Size();
    auto output = utils_object.GetPointWithinImage(p, s);
    ASSERT_EQ(output.x, -1);
    ASSERT_EQ(output.y, -1);
}
TEST(Utils, GetBboxWithinImage) {
    cv::Rect r = cv::Rect();
    cv::Size s = cv::Size();
    auto output = utils_object.GetBboxWithinImage(r, s);
    ASSERT_EQ(output.x, -1);
    ASSERT_EQ(output.y, -1);
    ASSERT_EQ(output.width, -1);
    ASSERT_EQ(output.height, -1);
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
    ASSERT_EQ(output, -1);
}
TEST(Utils, ResizeImage) {
    cv::Mat img;
    cv::Size s = cv::Size();
    ASSERT_NO_THROW(utils_object.ResizeImage(img, s));
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
    auto output = utils_object.GetTransformedPose(Pose(), Pose());
    ASSERT_EQ(output.x, -1);
    ASSERT_EQ(output.y, -1);
    ASSERT_EQ(output.z, -1);
}