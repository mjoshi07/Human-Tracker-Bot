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
 * @author Phase:2 Naitri Rajyaguru(driver) and Mayank Joshi(navigator)
 * @brief AutoBot class definition for Acme Robotics - Human Tracker
 * @version 0.1
 * @date 2021-10-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <eigen3/Eigen/Dense>


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
    return objects_in_frame_;
}


void acme::AutoBot::CollectTrainData() {
    std::string address;
    /// Number of frames to be captured
    int frame_count = 0;
    /// Get address where images are to be saved
    /// Uncommnent the lines below while running in training mode
    /// std::cout << "Enter the full path to save frames" << std::endl;
    /// std::getline(std::cin, address);

    /// comment the line below when running in training mode
    address = "..//data//train//";

    /// Uncommnent the lines below while running in training mode
    /// Get number of frames to be captured
    /// std::cout << "Enter frame count" << std::endl;
    /// std::cin >> frame_count;

    /// comment the line below when running in training mode
    frame_count = 2;
    cv::VideoCapture cap(camera_id_);

  if (!cap.isOpened()) {
    std::cerr << "ERROR: Could not open video " << std::endl;
    return;
  } else {
        for (int counter = 0; counter < frame_count; counter++) {
    cv::Mat frame;
    cap >> frame;
    std::string file_name = address+"//"+std::to_string(counter) + ".jpg";
    cv::imwrite(file_name, frame);
  }
}

  return;
}


void acme::AutoBot::DetectTestData() {
    cap_.release();
    cv::Mat img1 = cv::imread("..//data//test//1.png");
    cv::Mat img2 = cv::imread("..//data//test//2.png");
    cv::Mat img3 = cv::imread("..//data//test//3.png");
    cv::Mat img4 = cv::imread("..//data//test//4.png");
    cv::Mat img5 = cv::imread("..//data//test//5.jpeg");

    /// ground truth for img 2
    std::vector<cv::Rect> ground_truth_2 = {cv::Rect(330, 107, 160, 294)};

    /// ground truth for img 3
    std::vector<cv::Rect> ground_truth_3 = {cv::Rect(298, 126, 98, 228)};

    /// ground truth for img 1
    std::vector<cv::Rect> ground_truth_1 = {cv::Rect(300, 21, 197, 310)};

    /// ground truth for img 4
    std::vector<cv::Rect> ground_truth_4 = {cv::Rect(297, 84, 147, 265)};

    /// ground truth for img 4
    std::vector<cv::Rect> ground_truth_5 = {cv::Rect(320, 55, 110, 400),
        cv::Rect(430, 50, 120, 415)};
    std::vector<std::vector<cv::Rect>> gts = {ground_truth_1, ground_truth_2,
        ground_truth_3, ground_truth_4, ground_truth_5};


    std::vector <cv::Mat> imgs = {img1, img2, img3, img4, img5};
    for (int i = 0; i < static_cast<int>(imgs.size()); i++) {
        p_frame_ = acme::Utils::ResizeImage(imgs[i], p_size_);

        /// get bboxes of objects tracked by HumanTracker class in frame
        auto box2 = human_tracker_->TrackHumans(p_frame_);
        for ( int j = 0; j < static_cast<int>(gts[i].size()); j++ ) {
        double iou = acme::Utils::CalculateIOU(gts[i][j], box2[j]);
        std::cout << " IoU:" << iou << std::endl;
        /// Uncomment this block when using Testing mode
        /*
        cv::rectangle ( p_frame_, gts[i][j], cv::Scalar(0,255,0), 2 );
        cv::rectangle ( p_frame_, box2[j], cv::Scalar(0,0,255), 2 );

        std::string label1 = "ID: " + std::to_string(j);
        std::string label2 = "IoU: " + std::to_string(static_cast<float>(iou));

        cv::putText(p_frame_, label1, cv::Point(gts[i][j].x,
            gts[i][j].y), 0, 0.5, cv::Scalar(255,255,255), 4);
        cv::putText(p_frame_, label1, cv::Point(gts[i][j].x,
            gts[i][j].y), 0, 0.5, cv::Scalar(255,0,0), 2);

        cv::putText( p_frame_, label2, cv::Point(gts[i][j].x,
            gts[i][j].y+20), 0, 0.5, cv::Scalar(255,255,255), 4);
        cv::putText (p_frame_, label2, cv::Point(gts[i][j].x,
            gts[i][j].y+20), 0, 0.5, cv::Scalar(255,0,0), 2);*/
    }

        /// Uncomment this line when in Testing mode

        /*
        cv::imshow("img", p_frame_);
        cv::waitKey(0);*/
    }
}



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
            //  p_frame_ = Utils::DrawBbox(p_frame_, human_tracks);

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

void acme::AutoBot::Calibrate() {
    /// calculate calib factor and focal length here
    cv::Mat image = cv::imread("..//data//calibrate.jpg", 0);
    cv::Mat thr;
    /// original distance between object and camera
    double original_distance = 20;
    /// original width of the object
    double original_width = 10;
    /// thresholding the image
    cv::threshold(image, thr, 150, 255, cv::THRESH_BINARY);
    /// variable tostore contours
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    /// search for the contour
    cv::findContours(thr, contours, hierarchy,
                    cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
    double maxArea = 0;
    int maxAreaContourId = -1;
    /// get ID for contour of maximum area
    for (int j = 0; j < static_cast<int>(contours.size()); j++) {
        double newArea = cv::contourArea(contours.at(j));
        if (newArea > maxArea) {
            maxArea = newArea;
            maxAreaContourId = j;
        }
    }
    /// make bounding box
    cv::Rect box = cv::boundingRect(contours[maxAreaContourId]);
    /// calculate focal length
    double focalLength = (box.width * original_distance) / original_width;
    std::cout << focalLength;
    /// set focal length
    SetFocalLength(focalLength);
    calib_factor_ = focalLength * avg_human_height_;
}



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

    /// open camera stream using the video capture object
    /// Uncomment the line below if using webcam
    /// auto path = camera_id_;

    /// Path for testing on a video; comment this line if using webcam
    auto path = "..//data//test.mov";
    cap_.open(path);

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

    // initialize robot pose
    robot_pose_ = acme::Pose(7, 5, 8);

    // initialize camera pose
    camera_pose_ = acme::Pose(2, 2, 3);
}

void acme::AutoBot::ToRobotFrame(const std::vector<cv::Rect> &tracks) {
    objects_in_frame_.clear();
    Eigen::Matrix4d transform_mat;
    Eigen::Vector4d obj_in_cam;
    Eigen::Vector4d obj_in_robot;
    /// transformation matrix considering
    transform_mat << 1, 0, 0, robot_pose_.x - camera_pose_.x,
                     0, 1, 0, robot_pose_.y - camera_pose_.y,
                     0, 0, 1, robot_pose_.z - camera_pose_.z,
                     0, 0, 0, 1;

    if ( tracks.size() ) {
        /// create a variable to store Pose of the detected object
        acme::Pose obj_pose;
        int bbox_id = 0;
        for ( cv::Rect box : tracks ) {
            bbox_id++;
            double factor = avg_human_height_ / box.height;
            /// convert from img plane to Pose(x, y, z) using calib_factor
            obj_pose = acme::Utils::PixelsToPose(box, calib_factor_);
            obj_pose.y = obj_pose.y * factor;
            obj_pose.z = obj_pose.z * factor;

            // from world coordinates to camera coordinates using homogeneous
            // CHECK UTILS GET TRANSFORMED POSE METHOD
            obj_in_cam << obj_pose.x , obj_pose.y, obj_pose.z , 1;
            /// convert from camera Pose to Robot Pose
            obj_in_robot = transform_mat * obj_in_cam;

            /// store detected obj Pose in a vector
            objects_in_frame_.push_back(acme::Pose(obj_in_robot[0],
                obj_in_robot[1], obj_in_robot[2]));

            std::string label = std::to_string(bbox_id) + " (" +
                            std::to_string(static_cast<int>(obj_in_robot[0]))
                                + ","+
                            std::to_string(static_cast<int>(obj_in_robot[1]))
                                + ","+
                            std::to_string(static_cast<int>(obj_in_robot[2]))
                                + ")";

            p_frame_ = acme::Utils::DrawBbox(p_frame_, box, label);
        }
    }
}
