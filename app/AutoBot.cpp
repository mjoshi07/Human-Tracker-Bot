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
 * @file AutoBot.cpp
 * @author Phase:1 Naitri Rajyaguru(driver) and Mayank Joshi(navigator)
 * @brief AutoBot class definition for Acme Robotics - Human Tracker
 * @version 0.1
 * @date 2021-10-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */



#include <AutoBot.hpp>

acme::AutoBot::AutoBot(const int camera_id, double calib_factor) {
    /// initializes default parameters
    InitParams(camera_id, calib_factor);
}

acme::AutoBot::~AutoBot() {}

void acme::AutoBot::Run(const Mode mode) {
    /// Based on the mode selected, run the specific module
    switch ( static_cast<int>(mode) ) {
        case 1:
            CollectTrainData();
            break;
        case 2:
            DetectTestData();
            break;
        default:
            RunRealTime();
            break;
    }
}

void acme::AutoBot::SetRobotPose(const Pose &robo_pose) {}

void acme::AutoBot::CollectTrainData() {}

void acme::AutoBot::DetectTestData() {}

std::vector<acme::Pose>  acme::AutoBot::RunRealTime() {
    return std::vector<acme::Pose>();
}

void acme::AutoBot::Calibrate() {}


void acme::AutoBot::InitParams(int camera_id, double calib_factor) {
    /// set camera id
    camera_id_ = camera_id;

    /// set calib_factor default value
    calib_factor_ = calib_factor;

    objects_in_frame_.clear();

    /// set focal length in meters default value
    focal_length_ = 0.036;

    /// set human height, in meters default value
    avg_human_height_ = 1.7;


    /// open camera stream using the video capture object
    cap_.open(camera_id_);

    /// check if camera is open
    if ( cap_.isOpened() ) {
        /// set srouce frame width
        frame_width_ = cap_.get(cv::CAP_PROP_FRAME_WIDTH);

        /// set srouce frame height
        frame_height_ = cap_.get(cv::CAP_PROP_FRAME_HEIGHT);

        // set srouce frame rate
        frame_rate_ = cap_.get(cv::CAP_PROP_FPS);

        /// if height or width is 0, throw error
        if (frame_height_ == 0 || frame_width_ == 0) {
            // Display error msg and EXIT
            std::cout << "Frame is empty" << std::endl;
            return;
        }
    } else {
            // Display error msg and EXIT
            std::cout << "Cannot open camera" << std::endl;
            return;
    }

    /// set processing size default value
    p_size_ = cv::Size(640, 480);

    /// set confidence threshold for human_tracker default value
    double conf_threshold = 0.6;

    /// initialize HumanTracker Object
    human_tracker_ = std::make_unique<acme::HumanTracker>(conf_threshold);

    /// set show window default value
    show_window_ = true;

    /// set test counter default value
    test_counter_ = -1;
}
