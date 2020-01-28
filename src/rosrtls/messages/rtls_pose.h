/*
MIT License

Copyright (c) 2018 Group of Electronic Technology and Communications. University of A Coruña.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#ifndef gtec_rosrtls_pose_H
#define gtec_rosrtls_pose_H


#include <string>
#include <vector>
#include <stdint.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <armadillo>

#include "ros/ros.h"
#include <sstream>
#include <geometry_msgs/PoseWithCovarianceStamped.h>


class RTLSPose
{

public:
     RTLSPose(std::string token, std::string url, std::string route, std::string targetDeviceId, std::string scenarioId, std::string levelId);
    ~RTLSPose();

    void newPose(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& pose_msg);

private:
    std::string _token;
    std::string _url;
    std::string _route;
    std::string _targetDeviceId;
    std::string _scenarioId;
    std::string _levelId;
};


#endif
