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

#include <Utils.h>


namespace acme {
class Detector {
 public:
    Detector(double conf, const std::vector<std::string> &classes);
    ~Detector();

       std::vector<cv::Rect> Detect(const cv::Mat& frame);
       void SetClasses(const std::vector<std::string> &classes = {});
       void setNmsThresh(const double nms_thresh);
       void setInputWIdth(const int input_width);
       void setInputHeight(const int input_height);
       void setSwapRB(const bool swap_rb);
       void setCropImg(const bool crop_img);
       void setBackend(const int backend);
       void setTarget(const int target);
       void setNumChannels(const int num_channels);

 private:
       void WarmUp();
       void initModel(int backend, int target);

 private:
        double conf_threshold_;
        std::vector<std::string> classes_;
        double nms_threshold_;
        double input_width_;
        double input_height_;
        bool swap_rb_;
        bool crop_img_;
        int backend_;
        int target_;
        int num_channels_;
        std::unique_ptr<cv::dnn::Net> network_;
};
}  // namespace acme
#endif  // INCLUDE_DETECTOR_H_
