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

#include "rtls_ranging.h"
#include "restclient-cpp/connection.h"
#include "restclient-cpp/restclient.h"
#include <json.hpp>

using json = nlohmann::json;

RTLSRanging::RTLSRanging(std::string token, std::string url, std::string route){

    this->_token = token;
    this->_url = url;
    this->_route = route;

    RestClient::init();
}

RTLSRanging::~RTLSRanging() {
	RestClient::disable();
}


void RTLSRanging::newRanging(const gtec_msgs::Ranging::ConstPtr& ranging_msg) {


	std::stringstream stream;
	stream << std::hex << ranging_msg->anchorId;
	std::string anchorId(stream.str());

	std::stringstream stream2;
	stream2 << std::hex << ranging_msg->tagId;
	std::string tagId(stream2.str());

	std::string fullUrl = this->_url + anchorId;

	ROS_INFO("New ranging to send in rtls_ranging. Full URL: %s", fullUrl.c_str());;

	RestClient::Connection* conn = new RestClient::Connection(fullUrl);

	RestClient::HeaderFields headers;
	headers["Content-Type"] = "application/json";
	headers["x-access-token"] = this->_token;
	conn->SetHeaders(headers);

	json jsonMsg;
	json measurement;

	measurement["tagId"] = tagId;
	measurement["timestamp"] = 0;
	measurement["rss"] = ranging_msg->rss;
	measurement["range"] = ranging_msg->range;
	measurement["seq"] = ranging_msg->seq;
	measurement["errorEstimation"] = ranging_msg->errorEstimation;

	jsonMsg["measurements"] =  { measurement };

	RestClient::Response r = conn->post(this->_route, jsonMsg.dump());


}

