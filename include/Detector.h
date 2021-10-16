/**
 * @file Detector.h
 * @author Mayank Joshi (driver) and Naitri Rajyaguru (navigator)
 * @brief Detector class declaration for Acme Robotics - Human Tracker
 * @version 0.1
 * @date 2021-10-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#ifndef INCLUDE_DETECTOR_H_
#define INCLUDE_DETECTOR_H_

#include <memory>
#include <vector>
#include <string>

#include <opencv2/opencv.hpp>
#include <opencv2/dnn/dnn.hpp>
#include <opencv2/dnn/shape_utils.hpp>

#include <Utils.hpp>


namespace acme {
struct Detection {
      Detection(cv::Rect box, double conf, const std::string &n) :name(n) {
            bbox = box;
            confidence = conf;
      }
      cv::Rect bbox;
      double confidence;
      std::string name;
};

class Detector {
 public:
      Detector(double conf, const std::vector<std::string> &classes);

      ~Detector();

      std::vector<acme::Detection> Detect(const cv::Mat& frame);

      void SetClasses(const std::vector<std::string> &classes = {});

      void SetNmsThresh(const double nms_thresh);

      void SetInputWIdth(const int input_width);

      void SetInputHeight(const int input_height);

      void SetScaleFactor(const double scale_factor);

      void SetMeanToSubtract(const cv::Scalar &mean);

      void SetSwapRB(const bool swap_rb);

      void SetCropImg(const bool crop_img);

      void SetBackend(const int backend);

      void SetTarget(const int target);

      void SetNumChannels(const int num_channels);

 private:
      void WarmUp();

      void InitModel(double conf, const std::vector<std::string> &c);

      std::vector<acme::Detection> ProcessNet(const cv::Size &s);

 private:
      double conf_thresh_;
      std::vector<std::string> all_classes_;
      std::vector<std::string> classes_;
      double nms_thresh_;
      double input_width_;
      double input_height_;
      cv::Size size_;
      double scale_;
      cv::Scalar mean_;
      bool swap_;
      bool crop_;
      int backend_;
      int target_;
      int num_channels_;
      cv::dnn::Net network_;
      std::vector<std::string> out_names_;
      std::vector<cv::Mat> outputs_;
};
}  // namespace acme
#endif  // INCLUDE_DETECTOR_H_
