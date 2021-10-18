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
 * @file AutoBot.hpp
 * @author Phase 1 - Mayank Joshi (driver) and Naitri Rajyaguru (navigator)
 * @brief AutoBot class declaration for Acme Robotics - Human Tracker
 * @version 0.1
 * 
 * @copyright MIT License
 * 
 */


#ifndef INCLUDE_AUTOBOT_HPP_
#define INCLUDE_AUTOBOT_HPP_

#include <string>
#include <vector>
#include <memory>

#include <HumanTracker.hpp>

namespace acme {
     /**
      * @brief Different modes to run the program
      *
      */
  enum Mode {
       /// Run the Full Human Detector and Tracker module
      kRealTime = 0,
      /// Collect Training Data
      kTraining,
      /// Run Detector on user specified test data and generate metrics
      kTesting
  };

/**
 * @brief Acme Robotics Human Detection and Tracking Module
 * 
 * Module can run on different modes as required by the user
 * Output the human location in the Robot reference frame
 * 
 */
class AutoBot {
 public:
     /**
      * @brief Construct a new Auto Bot object
      * 
      * initializes default parameters used by AutoBot class
      * 
      * @param camera_id 
      * @param calib_factor 
      */
      explicit AutoBot(const int camera_id = 0, double calib_factor = -1);

      /**
       * @brief Destroy the Auto Bot object
       * 
       */
      ~AutoBot();

     /**
      * @brief Main function of AutoBot class to start the program
      * 
      * Based on the mode selected, program behavior changes
      * Can run Human-Detector and Tracker
      * Can Collect Training Data
      * Can Perform detection on test data and produce metrics
      * 
      * @param mode 
      */
      void Run(const acme::Mode mode);

     /**
      * @brief Set the Robot Pose in (x, y, z)
      * 
      * @param robo_pose 
      */
      void SetRobotPose(const acme::Pose &robo_pose);

     /**
      * @brief Set the Camera Pose in (x, y, z) respect to robot pose
      * 
      * @param camera_pose 
      */
      void SetCameraPose(const acme::Pose &camera_pose);

     /**
      * @brief Set the Focal Length of the camera
      * 
      * @param focal_length 
      */
      void SetFocalLength(double focal_length);

     /**
      * @brief Set the Processing Size 
      * 
      * @param width 
      * @param height 
      */
      void SetProcessingSize(const int width, const int height);

      /**
       * @brief Set the Processing Size object
       * 
       * @param processing size
       */
      void SetProcessingSize(const cv::Size & s);

     /**
      * @brief Set the avg human height 
      * 
      * @param avg_human_height 
      */
      void SetHumanHeight(const double avg_human_height);

     /**
      * @brief Set the Show Window object
      * 
      * @param show_window 
      */
      void SetShowWindow(const bool show_window);

     /**
      * @brief Set the Test Counter for Testing Purpose 
      * 
      * if Test Counter is set to some value greate than -1
      * Program will run for that many frames only
      * 
      * @param test counter 
      */
      void SetTestCounter(const int counter);

     /**
      * @brief Get the Objects [humans in our case]
      * 
      * @return vector of objects in robot reference frame
      */
      std::vector<acme::Pose> GetObjects();

      // [OPTIONAL - future] create a method to get ROI for processing

 private:
      /**
       * @brief When Mode is kTraining, Run Method will call CollectTrainData
       * 
       * Asks the user to input the output directory
       * Asks the user how many images to save
       * ASks the user for frame interval
       * 
       */
      void CollectTrainData();

      /**
       * @brief When Mode is kTesting, Run Method will call DetectTestData
       * 
       * Asks the user to input the test data directory
       * Test Data should be in yolo format
       * Run Detector on images
       * Calculate avg iou by comparing with ground truth
       * Display the metric output
       * 
       */
      void DetectTestData();

      /**
       * @brief When mode is kRealTime, Run Method will call RunRealTime
       * 
       * perform calibration if not calib_factor not set
       * Resizes the source frame according to processing size
       * Get human tracks by calling TrackHumans method of class HumanTracker
       * Call DrawBbox to draw bbox on the processing frame
       * Call ToRobotFrame to convert bbox from image plane to robot ref frame
       * if show_window_ is true, display the processing frame
       * 
       */
      void RunRealTime();

      /**
       * @brief Calculate the calib_factor
       * 
       * Uses resolution, focal length and a test subject in real world
       * Calib factor is used to convert human from pixels to robot ref frame 
       * 
       * 
       */
      void Calibrate();

     /**
      * @brief Converts bbox from image plane to robot reference frame
      * 
      * Uses calib factor, robot pose, camera pose to get locations
      * 
      * @param tracks 
      */
      void ToRobotFrame(const std::vector<cv::Rect> &tracks);

     /**
      * @brief Initializes parameters for the AutoBot class
      * 
      * set default value for camera id
      * set default value for calib factor
      * set default value for focal length
      * set default value for avg human height
      * opens camera with the camera id
      * set frame width from camera 
      * set frame height from camera
      * set frame rate from camera
      * set default value for processing size
      * set default value for conf threshold for Human Tracker object
      * initializes HumanTracker object with conf threshold
      * set default value for show window
      * set default value for test counter
      * 
      * @param camera_id 
      * @param calib_factor 
      */
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

#endif  // INCLUDE_AUTOBOT_HPP_
