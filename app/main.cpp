/**
 * @file main.cpp
 * @author Mayank Joshi (driver) and Naitri Rajyaguru (navigator)
 * @brief main function for Acme Robotics - Human Tracker
 * @version 0.1
 * @date 2021-10-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#include <AutoBot.h>

int main(int argc, char **argv) {
    acme::Mode mode = acme::Mode::kRealTime;
    acme::AutoBot humanTrackingRobot(false, 0.5);
    humanTrackingRobot.Run(mode);
    std::cout << "Successfully Created Acme AutoBot" << std::endl;
    return 0;
}
