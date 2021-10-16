/**
 * @file AutoBot.h
 * @author Mayank Joshi (driver) and Naitri Rajyaguru (navigator)
 * @brief AutoBot class declaration for Acme Robotics - Human Tracker
 * @version 0.1
 * @date 2021-10-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#ifndef INCLUDE_AUTOBOT_H_
#define INCLUDE_AUTOBOT_H_

#include <string>
#include <vector>
#include <memory>
 
#include <HumanTracker.hpp>
 
namespace acme {
  enum Mode {
      kRealTime = 0,
      kTraining,
      kTesting
  };
 
class AutoBot {
 public:
      explicit AutoBot(const int camera_id = 0, double calib_factor = -1);
 
      ~AutoBot();
 
      void Run(const acme::Mode mode);
 
      void SetRobotPose(const acme::Pose &robo_pose);
 
      void SetCameraPose(const acme::Pose &camera_pose);
 
      void SetFocalLength(double focal_length);
 
      void SetProcessingSize(const int width, const int height);
 
      void SetProcessingSize(const cv::Size & s);
 
      void SetHumanHeight(const double avg_human_height);
 
      void SetShowWindow(const bool show_window);
 
      void SetTestCounter(const int counter);
 
      std::vector<acme::Pose> GetObjects();
 
      // [OPTIONAL - future] create a method to get ROI for processing
 
 private:
      void CollectTrainData();
 
      void DetectTestData();
 
      void RunRealTime();
 
      void Calibrate();
 
      void ToRobotFrame(const std::vector<cv::Rect> &tracks);
 
      void InitParams(int camera_id, double calib_factor);
 
 
 
 private:
  int camera_id_;
  double focal_length_;
  int frame_width_;
  int frame_height_;
  int frame_rate_;
  double avg_human_height_;
  cv::Mat p_frame_;
  cv::Size p_size_;
  double calib_factor_;
  acme::Pose robot_pose_;
  acme::Pose camera_pose_;
  std::vector<acme::Pose> objects_in_frame_;
  std::unique_ptr<acme::HumanTracker> human_tracker_;
  cv::VideoCapture cap_;
  bool show_window_;
  int test_counter_;
};
}  // namespace acme

#endif  // INCLUDE_AUTOBOT_H_
