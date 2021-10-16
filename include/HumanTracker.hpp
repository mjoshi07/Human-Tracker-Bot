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

