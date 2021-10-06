# Acme-Robotics-Human-Tracker

[![Build Status](https://app.travis-ci.com/mjoshi07/Acme-Robotics-Human-Tracker.svg?branch=main)](https://app.travis-ci.com/mjoshi07/Acme-Robotics-Human-Tracker)
[![Coverage Status](https://coveralls.io/repos/github/mjoshi07/Acme-Robotics-Human-Tracker/badge.svg?branch=main)](https://coveralls.io/github/mjoshi07/Acme-Robotics-Human-Tracker?branch=main)

Detects and Tracks Human in Robot Reference Frame

## Project contibutors

1) [Naitri Rajyaguru](https://github.com/naitri), Robotics Graduate Student at University of Maryland, College Park. 
2) [Mayank Joshi](https://github.com/mjoshi07), Robotics Graduate Student at University of Maryland, College Park. 


## Overview
Human detection is a part of object detection where primary class “human/person” is detected in images or video frames. In robotics, human detection is very necessary as humans are dynamic obstacles and no one would want a robot colliding with a human. Therefore, for navigation, a robot needs to detect and identify humans in its field of view. 

We propose a human detection and tracking module, which uses computer vision algorithms to perceive the environment. The module uses a monocular camera to get frames in which humans are first detected by a deep neural network model and then those are tracked till they are present in the frame. Alot of research has been done in the field of object detection, especially human detection. Although quite a lot algorithms are quite efficient, like HOG (Histogram of Oriented Gradients) but they are not as robust as a deep neural network. Now days we have processing power that could run DNN model in real time and the accuracy of the model can be increased by training it on more data, therefore a scope of improvement is always present.
Our module also has the capability to obtain training data and check the performance of DNN model on the test data, which can be provided by the user.

We plan to use YoloV4-tiny, a pre-trained model based on [Darknet framework](https://pjreddie.com/darknet/).

![image](https://user-images.githubusercontent.com/31381335/136114967-78ee8c5d-ee8c-40ac-a300-24189d6a8104.png)

Image taken from this [article](https://medium.com/@luanaebio/detecting-people-with-yolo-and-opencv-5c1f9bc6a810)


## Potential Risks and Mitigation
* The model is trained on [MS COCO dataset](https://cocodataset.org/#home) which contains RGB images therefore would not able to work with infrared cameras or in low light. Training on additional low light and data from infrared camera can make the model more robust
* Since yoloV4-tiny is the compressed version of yoloV4, therefore it lacks in accuracy. YoloV4 achieves an average precision of 64.9% while yoloV4-tiny achieves an average precision of 40.2%. Check full comparison [here](https://user-images.githubusercontent.com/4096485/85734112-6e366700-b705-11ea-95d1-fcba0de76d72.png)
* Running the system on the robot can memory expensive due to deep learning model, one possible solution is to quantize the weights of the model so that it takes less memory and is faster


## Technology 
* We will be following [AIP](https://en.wikipedia.org/wiki/Agile_software_development) (Agile Iterative Process) and implement the software using [TDD](https://en.wikipedia.org/wiki/Test-driven_development) (Test Driven Development)
* Quality shall be ensured by unit testing and cppcheck, adhering to [Google C++ style guide](https://google.github.io/styleguide/cppguide.html)
* Operating System (Ubuntu 18.04 LTS)
* Programming Language (Modern C++)
* Build System (CMake >= 3.2.1)
* External Library (Opencv >= 4.5.0)
* Pre-trained model (yoloV4-tiny)

