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

#include <HumanTracker.h>

namespace acme {
  enum Mode {
      kRealTime = 0,
      kTraining,
      kTesting
  };

  enum InputType {
      kImage = 0,
      kVideo,
      kIpCam,
      kWebcam
  };

class AutoBot {
 public:
      AutoBot();
      AutoBot(bool is_calibrated, double calib_factor);
      ~AutoBot();

      void Run(const acme::Mode mode);
      void SetRobotPose(const acme::Pose &robo_pose);

 private:
      void CollectTrainData();
      void DetectTestData();
      std::vector<Pose> RunRealTime();
      void Calibrate();

 private:
  double calib_factor_;
  Pose robot_pose_;
  std::unique_ptr<acme::HumanTracker> human_tracker_;
};
}  // namespace acme

#endif  // INCLUDE_AUTOBOT_H_
