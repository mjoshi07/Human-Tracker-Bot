/**
 * @file Utils.h
 * @author Mayank Joshi (driver) and Naitri Rajyaguru (navigator)
 * @brief Utils class declaration for Acme Robotics - Human Tracker
 * @version 0.1
 * @date 2021-10-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#ifndef INCLUDE_UTILS_H_
#define INCLUDE_UTILS_H_

#include <opencv2/core.hpp>

namespace acme {
struct Pose{
        Pose():x(-1), y(-1), z(-1) {}
        double x;
        double y;
        double z;
};

class Utils{
 public:
    static cv::Point GetPointWithinImage(cv::Point &p, cv::Size &img_size);
    static cv::Rect GetBboxWithinImage(cv::Rect &bbox, cv::Size &img_size);
    static cv::Point GetBboxCenter(cv::Rect &bbox);
    static double GetBboxArea(cv::Rect &bbox);
    static void ResizeImage(cv::Mat &input_img, cv::Size& target_size);
    static double CalculateIOU(const cv::Rect& bbox1, const cv::Rect& bbox2);
    static Pose PixelsToPose(cv::Rect &bbox, double calib_factor);
    static Pose GetTransformedPose(const Pose& dest_frame_of_ref, const Pose& src_frame_of_ref);
};
}  // namespace acme
#endif  // INCLUDE_UTILS_H_

