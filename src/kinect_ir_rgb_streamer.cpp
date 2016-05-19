#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <ros/ros.h>

class IR_RGB_Streamer{

public:
    IR_RGB_Streamer(): it_(nh){
        rgb_sub = it_.subscribe("rgb_in", 1, &IR_RGB_Streamer::rgb_image_cb, this);
    }

    void rgb_image_cb(const sensor_msgs::ImageConstPtr& msg){
        cv::Mat rgb_image;
        try
        {
            rgb_image = cv_bridge::toCvShare(msg, "bgr8")->image;
        }
        catch (cv_bridge::Exception& e)
        {
            ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
        }
        rgb_sub.shutdown();
        ir_sub = it_.subscribe("ir_in", 1, &IR_RGB_Streamer::ir_image_cb, this);
        imshow("RGB Image",rgb_image);
        cv::waitKey(1);
    }

    void ir_image_cb(const sensor_msgs::ImageConstPtr& msg){
        cv::Mat ir_image;
        try
        {
            ir_image = cv_bridge::toCvShare(msg, "bgr8")->image;
        }
        catch (cv_bridge::Exception& e)
        {
            ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
        }
        ir_sub.shutdown();
        rgb_sub = it_.subscribe("rgb_in", 1, &IR_RGB_Streamer::rgb_image_cb, this);
        imshow("IR Image",ir_image);
        cv::waitKey(1);
    }


private:
    ros::NodeHandle nh;
    image_transport::ImageTransport it_;
    image_transport::Subscriber ir_sub;
    image_transport::Subscriber rgb_sub;
};


int main(int argc, char **argv)
{
    ros::init(argc, argv, "kinect_ir_rgb_streamer");
    IR_RGB_Streamer test;
    ros::spin();
    cv::destroyWindow("view");
}
