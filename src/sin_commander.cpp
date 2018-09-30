// code written by Frank Qian CXQ41@case.edu for EECS 473 Homework PS1 node: 
#include <ros/ros.h> 
#include <std_msgs/Float64.h> 
#include <string>

//Project specific include:
#include <math.h>
#include <iostream>

//Service specific
#include <cxq41_p2/SinComponent.h>

std_msgs::float64 commander_amplitude; //Global variable for storing amplitude
std_msgs::float64 commander_frequency; //Global variable for storing frequency
std_msgs::float64 sin_output; //Global Variable for the sinusoidal output
const double PI  =3.141592653589793238463; //Yep too fucking lazy to figure out proper way to express pi!

//Service callback
bool callback(cxq41_p2::SinComponentRequest& request, cxq41_p2::SinComponentResponse& response) {
    // place received data in appropriate global variables
    commander_amplitude.data = request.amplitude;
    ROS_INFO("Obtained amplitude is: %f", commander_amplitude.amplitude);

    commander_frequency.data = request.frequency;
    ROS_INFO("Obtained frequency is: %f", commander_frequency.frequency);

    // let user know that the service was carried out
    response.completed = true;
}


int main(int argc, char **argv) {

    ros::init(argc, argv, "sin_commander"); //name this node 

    ros::NodeHandle nh; // node handle

    ros::ServiceServer service = nh.advertiseService("SinComponentExchange",callback)

    //Announcer for topic
    ros::Publisher sinWave_outputter = nh.advertise<std_msgs::Float64>("vel_cmd", 1);

    

    //Initiate sin_output
    sin_output.data = 0.00;
    //Initiate Time for sine generation:
    double current_time; // Initate the time
    current_time = 0.00; //Resets time to 0

    //This will both set the sleeper rate as well as the "T" for the sin wave generator
    double dt = 0.01;
    double sample_rate = 1.0 / dt; 
    ros::Rate naptime(sample_rate);


    while (ros::ok()) {
        //sin wave is generated below:
        sin_output.data = amplitude.data * sin(2.00 * frequency.data * PI * current_time);
        current_time = current_time + dt; //time is ticking!
        sinWave_outputter.publish(sin_output);
        ROS_INFO("Current sin_ouput is: %f", sin_output.data); //Debug info spit!
        //----Do not change below as they are critical for operation normally
        ros::spinOnce(); 
        naptime.sleep();
    }
    return 0; // Not used unless some dummy kills roscore 
} 
