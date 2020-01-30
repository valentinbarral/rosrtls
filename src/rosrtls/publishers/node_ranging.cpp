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
#include <gtec_msgs/Ranging.h>

int main(int argc, char *argv[])
{


    ros::init(argc, argv, "rtlsranging");
    ros::NodeHandle n("~");

    std::string token;
    std::string url;
    std::string route;

    n.getParam("token", token);
    n.getParam("url", url);
    n.getParam("route", route);

    RTLSRanging rtlsRanging(token, url, route);
    
    ros::Subscriber sub0 = n.subscribe<gtec_msgs::Ranging>("/gtec/toa/ranging", 12, &RTLSRanging::newRanging, &rtlsRanging);

    ros::spin();

    return 0;
}
