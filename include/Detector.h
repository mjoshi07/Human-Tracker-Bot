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


#ifndef HEADER_DETECTOR_H_
#define HEADER_DETECTOR_H_

#include <memory>
#include <vector>
#include <Utils.h>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn/dnn.hpp>
#include <opencv2/dnn/shape_utils.hpp>

namespace acme {
    class Detector {
    public:
        Detector(double conf_thresh, std::vector<std::string> classes_to_detect={}, double nms_thresh=0.4,  int input_width=416, int input_height=416, bool swap_RB=true, bool crop_img=false, int backend=0, int target=0, int num_channels=3);
        ~Detector();

        std::vector<cv::Rect> Detect(cv::Mat& frame);
        void SetClassesToDetect(std::vector<std::string> classes_to_detect={});
        void setNmsThresh(double nms_thresh);
        void setInputWIdth(int input_width);
        void setInputHeight(int input_height);
        void setSwapRB(bool swap_rb);
        void setCropImg(bool crop_img);
        void setBackend(int backend);
        void setTarget(int target);
        void setNumChannels(int num_channels);

    private:
        void WarmUp();
        void initModel(std::string model_weights, std::string model_config, int backend, int target);

    private:
        double conf_threshold_;
        std::vector<std::string> classes_to_detect_;
        double nms_threshold_;
        double input_width_;
        double input_height_;
        bool swap_rb_;
        bool crop_img_;
        int backend_;
        int target_;
        int num_channels_;
        //std::unique_ptr<cv::dnn::Net> network_;
    };
}
#endif // HEADER_DETECTOR_H_
