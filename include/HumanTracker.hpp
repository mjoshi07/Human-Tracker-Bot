/**
 * @file HumanTracker.hpp
 * @author Phase 1 - Mayank Joshi (driver) and Naitri Rajyaguru (navigator)
 * @brief HumanTracker class declaration for Acme Robotics - Human Tracker
 * @version 0.1
 * 
 * @copyright MIT License
 * 
 */


#ifndef INCLUDE_HUMANTRACKER_HPP_
#define INCLUDE_HUMANTRACKER_HPP_

#include <vector>
#include <memory>

#include <opencv2/tracking.hpp>
#include <opencv2/core/ocl.hpp>

#include <Detector.hpp>

namespace acme {

/**
 * @brief 
 * 
 */
class HumanTracker {
 public:
 /**
  * @brief Construct a new Human Tracker object
  * 
  * @param confidence 
  */
  explicit HumanTracker(double confidence);

  /**
   * @brief Destroy the Human Tracker object
   * 
   */
  ~HumanTracker();

  /**
   * @brief Tracks Humans present in a frame
   * 
   * @param frame 
   * @return vector of bbox
   */
  std::vector<cv::Rect> TrackHumans(const cv::Mat &frame);

 private:
  /**
   * @brief Initializes the default parameters
   * 
   * Required confidence to filter out the detections
   * 
   * @param confidence 
   */
  void InitParams(double confidence);

  /**
   * @brief Filter out the detections using a confidence threshold
   * 
   * @param unfiltered detections from the Detector
   */
  void RemoveNoise(const std::vector<acme::Detection>& detections);

 private:
  double conf_thresh_;
  std::vector<cv::Rect> humans_;
  std::unique_ptr<acme::Detector> detector_;
  cv::Ptr<cv::Tracker> tracker_;
};
}  // namespace acme
#endif  // INCLUDE_HUMANTRACKER_HPP_

