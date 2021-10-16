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

#include <vector>
 
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
 
namespace acme {
struct Pose{
        Pose() {
                x = -1.0;
                y = -1.0;
                z = -1.0;
        }
 
        Pose(double x1, double y1, double z1) {
                x = x1;
                y = y1;
                z = z1;
        }
        double x;
        double y;
        double z;
};
 
class Utils{
 public:
    static cv::Point FitWithinSize(const cv::Point &p, const cv::Size &s);
 
    static cv::Rect FitWithinSize(const cv::Rect &b, const cv::Size &s);
 
    static cv::Mat DrawBbox(cv::Mat i, const std::vector<cv::Rect> &bs);
 
    static cv::Point GetBboxCenter(const cv::Rect &bbox);
 
    static double GetBboxArea(const cv::Rect &bbox);
 
    static cv::Mat ResizeImage(const cv::Mat &i, const cv::Size &s);
 
    static double CalculateIOU(const cv::Rect& b1, const cv::Rect& b2);
 
    static Pose PixelsToPose(const cv::Rect &b, double calib_factor);
 
    static Pose GetTransformedPose(const Pose& src, const Pose& dst);
};
}  // namespace acme
#endif  // INCLUDE_UTILS_H_

