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


#ifndef HEADER_HUMAN_TRACKER_H_
#define HEADER_HUMAN_TRACKER_H_

#include <Detector.h>
#include <opencv2/tracking.hpp>
#include <opencv2/core/ocl.hpp>

namespace acme {
   class HumanTracker {
   public:
      HumanTracker(double confidence);
      ~HumanTracker();

      std::vector<cv::Rect> TrackHumans(cv::Mat &frame);

   private:
      void InitParams(double confidence);
      void ProcessFrame(cv::Mat &frame);

   private:
      std::unique_ptr<acme::Detector> detector_;
      cv::Ptr<cv::Tracker> tracker_;
   };
}
#endif // HEADER_HUMAN_TRACKER_H_
