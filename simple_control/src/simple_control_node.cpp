#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <prius_msgs/Control.h>
#include <stdlib.h>
#include <turtlesim/Pose.h>
#include <iomanip>

//Initialize parameters to be used in the process
float linx, angZ;
int throttle = 0;
int steer = 0; 
int gear = 0;

//Callback function to pass linx and angZ into the main function as an argument
void chatterCallback(const geometry_msgs::Twist& msg)
{
   linx = msg.linear.x;      
   angZ = msg.angular.z;
}

int main(int argc, char** argv) {

    ros::init(argc, argv, "publish_situation");

    //Initialize nodehanndle, subscriber and publisher
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("turtle1/cmd_vel", 1000, &chatterCallback); 
    ros::Publisher pub = nh.advertise<prius_msgs::Control>("prius", 1000);
    //Initialize the sampling rate of the program, set at 10Hz
    ros::Rate rate(10);

    //Main loop
    while(ros::ok()){
        //Initialize objects Twist and Control
        geometry_msgs::Twist msg;
        prius_msgs::Control tvt;

        //Set linear.x and angular.z equal to linx and angZ
        msg.linear.x = linx;     
        msg.angular.z = angZ;
        
        //Check user input and decide the proper prius action
        if (linx==-2){
            gear=3;
            throttle=-1;
            steer=0;
        
        }
        else if (linx==2){
            gear=2;
            throttle=1;
            steer=0;
        }
        else if (angZ==-2){
            steer=-1;
        }
        else if (angZ==2){
            steer=1;
        }
        
        //Set rosparams accordingly
        ros::param::set("throttle_param",throttle);
        ros::param::set("steer_param",steer);

        //Set throttle, steer and shift_gears to their proper values
        tvt.throttle        = throttle;
        tvt.steer           = steer;
        tvt.shift_gears     = gear;

        //Print steer, throttle and shift_gears
        ROS_INFO_STREAM("steer: "<<tvt.steer<<" throttle: "<<tvt.throttle<<" gear: "<<tvt.shift_gears);

        //Publish to object
        pub.publish(tvt);

        //Sleep for a while, given by Rate
        rate.sleep();
        ros::spinOnce();
    }

}
