/**
 * @file HumanTracker.h
 * @author Mayank Joshi (driver) and Naitri Rajyaguru (navigator)
 * @brief HumanTracker class declaration for Acme Robotics - Human Tracker
 * @version 0.1
 * @date 2021-10-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#ifndef INCLUDE_HUMANTRACKER_H_
#define INCLUDE_HUMANTRACKER_H_

#include <vector>
#include <memory>
 
#include <opencv2/tracking.hpp>
#include <opencv2/core/ocl.hpp>
 
#include <Detector.hpp>
 
namespace acme {
 
class HumanTracker {
 public:
  explicit HumanTracker(double confidence);
 
  ~HumanTracker();
 
  std::vector<cv::Rect> TrackHumans(const cv::Mat &frame);
 
 private:
  void InitParams(double confidence);
 
  void RemoveNoise(const std::vector<acme::Detection>& detections);
 
 private:
  double conf_thresh_;
  std::vector<cv::Rect> humans_;
  std::unique_ptr<acme::Detector> detector_;
  cv::Ptr<cv::Tracker> tracker_;
};
}  // namespace acme
#endif  // INCLUDE_HUMANTRACKER_H_

