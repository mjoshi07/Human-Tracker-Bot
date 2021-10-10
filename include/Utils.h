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
    static cv::Point FitWithinSize(const cv::Point &p, const cv::Size &s);
    static cv::Rect FitWithinSize(const cv::Rect &b, const cv::Size &s);
    static cv::Point GetBboxCenter(const cv::Rect &bbox);
    static double GetBboxArea(const cv::Rect &bbox);
    static cv::Mat ResizeImage(const cv::Mat &img, const cv::Size &s);
    static double CalculateIOU(const cv::Rect& b1, const cv::Rect& b2);
    static Pose PixelsToPose(const cv::Rect &b, double calib_factor);
    static Pose GetTransformedPose(const Pose& dst, const Pose& src);
};
}  // namespace acme
#endif  // INCLUDE_UTILS_H_

