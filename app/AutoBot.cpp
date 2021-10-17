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


void acme::AutoBot::SetRobotPose(const Pose &robo_pose) {
    robot_pose_ = robo_pose;
}

void acme::AutoBot::SetCameraPose(const Pose &camera_pose) {
    camera_pose_ = camera_pose;
}

void acme::AutoBot::SetFocalLength(const double fl) {
    focal_length_ = fl;
}

void acme::AutoBot::SetProcessingSize(const int w, const int h) {
    cv::Size s = cv::Size(w, h);
    SetProcessingSize(s);
}

void acme::AutoBot::SetProcessingSize(const cv::Size &s) {
    p_size_ = s;
}

void acme::AutoBot::SetHumanHeight(const double h) {
    avg_human_height_ = h;
}

void acme::AutoBot::SetShowWindow(const bool show_window) {
    show_window_ = show_window;
}

void acme::AutoBot::SetTestCounter(const int counter) {
    test_counter_ = counter;
}

std::vector<acme::Pose> acme::AutoBot::GetObjects() {
    return std::vector<acme::Pose>();
}


void acme::AutoBot::CollectTrainData() {}

void acme::AutoBot::DetectTestData() {}



void acme::AutoBot::RunRealTime() {
    /// if calib_factor == default value, calculate calib_factor
    if (calib_factor_ == -1) {
        Calibrate();
    }

    /// setup the display window name
    const std::string kWindowName = "Display";

    if ( show_window_ ) {
        /// create a display window if show window is true
        cv::namedWindow(kWindowName, cv::WINDOW_FREERATIO);
    }

    /// initialize a variable to store frame counter with 0
    unsigned int frame_counter = 0;

    /// initialize an empty vector to store bounding boxes
    std::vector<cv::Rect> human_tracks{};

    /// create a variable to store the source frame size
    cv::Size src_size;

    /// run an indefinite loop to read video stream
    while (true) {
        /// create a variable to store the source video frame
        cv::Mat src_frame;
        if ( cap_.read(src_frame) ) {
            if ( frame_counter == 0 ) {
                /// calculate the source frame size once
                src_size = src_frame.size();
            }

            /// resize src frame according to processing size
            p_frame_ = acme::Utils::ResizeImage(src_frame, p_size_);

            /// get bboxes of objects tracked by HumanTracker class in frame
            human_tracks = human_tracker_->TrackHumans(p_frame_);

            /// draw bboxes on the frame
            p_frame_ = Utils::DrawBbox(p_frame_, human_tracks);

            /// convert the bboxes from img plane to robot ref frame
            ToRobotFrame(human_tracks);

            /// resize process frame back to src frame size
            p_frame_ = acme::Utils::ResizeImage(p_frame_, src_size);

            if ( show_window_ ) {
                /// if show window is true, display the current video frame
                cv::imshow(kWindowName, p_frame_);
                char k = cv::waitKey(1);
                if ( k == 27 || k == 'q' ) {
                    /// EXIT if user hits 'Esc' or 'q' on the keyboard
                    return;
                }
            }

            /// increment the frame counter
            frame_counter++;

            /// for Testing purpose only, run the loop for test_counter times
            if ( test_counter_ != -1 ) {
                if ( static_cast<int>(frame_counter) > test_counter_ ) {
                    return;
                }
            }
        } else {
            std::cout << "Cannot read frame" << std::endl;
            return;
        }
    }
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

void acme::AutoBot::ToRobotFrame(const std::vector<cv::Rect> &tracks) {
    objects_in_frame_.clear();
    if ( tracks.size() ) {
        /// create a variable to store Pose of the detected object
        acme::Pose obj_pose;
        for ( cv::Rect box : tracks ) {
            /// convert from img plane to Pose(x, y, z) using calib_factor
            obj_pose = acme::Utils::PixelsToPose(box, calib_factor_);

            // from world coordinates to camera coordinates using homogeneous
            // CHECK UTILS GET TRANSFORMED POSE METHOD

            /// convert from camera Pose to Pose
            obj_pose.x -= robot_pose_.x;
            obj_pose.y -= robot_pose_.y;
            obj_pose.z -= robot_pose_.z;

            /// store detected obj Pose in a vector
            objects_in_frame_.push_back(obj_pose);
        }
    }
}
