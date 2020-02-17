/*
MIT License

Copyright (c) 2020 Group of Electronic Technology and Communications. University of A Coruna.

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

#include "rtls_pose.h"
#include "restclient-cpp/connection.h"
#include "restclient-cpp/restclient.h"
#include <json.hpp>

using json = nlohmann::json;

RTLSPose::RTLSPose(std::string token, std::string url, std::string route, std::string targetDeviceId, std::string scenarioId, std::string levelId){

    this->_token = token;
    this->_url = url;
    this->_route = route;
    this->_targetDeviceId = targetDeviceId;
    this->_scenarioId = scenarioId;
    this->_levelId = levelId;

    RestClient::init();
}

RTLSPose::~RTLSPose() {
	RestClient::disable();
}


void RTLSPose::newPose(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& pose_msg) {

	std::vector<double> covarianceVector;


	std::string fullUrl = this->_url + this->_targetDeviceId + this->_route;
	ROS_DEBUG("New pose to send in rtls_pose. Full URL: %s", fullUrl.c_str());;

	RestClient::Connection* conn = new RestClient::Connection(fullUrl);

	RestClient::HeaderFields headers;
	headers["Content-Type"] = "application/json";
	headers["x-access-token"] = this->_token;
	conn->SetHeaders(headers);

	json jsonMsg;
	json jsonPosition, jsonError;

	jsonMsg["techsUsed"] = {"UWB"};
	jsonMsg["timeWindow"] = 0;
	jsonMsg["timestamp"] = 0;

	jsonError["type"] = "geometric";
	jsonError["covariance"] = covarianceVector;
	jsonMsg["error"] = jsonError;

	jsonPosition["type"] = "geometric";
	jsonPosition["pose"]["position"] = {pose_msg->pose.pose.position.x,pose_msg->pose.pose.position.y,pose_msg->pose.pose.position.z};
	jsonPosition["pose"]["quaternion"] = {	pose_msg->pose.pose.orientation.x,pose_msg->pose.pose.orientation.y,pose_msg->pose.pose.orientation.z,pose_msg->pose.pose.orientation.w};
	jsonMsg["position"] =  jsonPosition;

	RestClient::Response r = conn->post(this->_route, jsonMsg.dump());


}

