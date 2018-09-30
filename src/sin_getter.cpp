// code written by Frank Qian CXQ41@case.edu for EECS 473 Homework PS2:
// This node is responsible for getting values and pass along: 
#include <ros/ros.h>
#include <string>
//IO specific
#include <iostream>
#include <math.h>
//Service specificfrequency
#include <cxq41_ps2/SinComponent.h>

int main(int argc, char **argv) {
    //Local storage for IO value:
    std_msgs::float64 getter_amplitude; //Global variable for storing amplitude
    std_msgs::float64 getter_frequency; //Global variable for storing frequency

    //client initiation
    ros::init(argc, argv, "sin_getter");
    //node handler
    ros::NodeHandle n;
    
    ros::ServiceClient client = n.serviceClient<cxq41_ps2::SinComponent>("SinComponentExchange");

    cxq41_ps2::SinComponent srv;

    while (ros::ok()) {

            getter_amplitude.data = 0.00;
            std::cout << std::endl;
            std::cout << "Please input the amplitude you want to set.......(Use CTRL+C to Quit)" << std::endl << "Input: ";
            std::cin >> getter_amplitude.data;
            while(std::cin.fail()) {
                ROS_ERROR("Input is not valid! Please try again....(Use CTRL+C to Quit)");
                std::cout<< "Input: ";
                std::cin.clear();
                std::cin.ignore(256,'\n');
                std::cin >> getter_amplitude.data;
            }
            srv.request.amplitude = getter_amplitude.data;
            ROS_INFO("The amplitude you set is: %f", getter_amplitude.data);

            //Get input for frequency:
            getter_frequency.data = 0.00;
            std::cout << std::endl;
            std::cout << "Please input the frequency you want to set.......(Use CTRL+C to Quit)" << std::endl << "Input: ";
            std::cin >> getter_frequency.data;
            while(std::cin.fail()) {
                ROS_ERROR("Input is not valid! Please try again....(Use CTRL+C to Quit)");
                std::cout<< "Input: ";
                std::cin.clear();
                std::cin.ignore(256,'\n');
                std::cin >> getter_frequency.data;
            }
            srv.request.frequency = getter_frequency.data;
            ROS_INFO("The frequency you set is: %f", getter_frequency.data);

            //Confirmation of get
            if(client.call(srv)){
                ROS_INFO("Both input obtained! Handover to commander.......");
            }

        } else {
            ROS_ERROR("Failed to call service SinComponentExchange");
            return 1;
        }
    return 0; // Not used unless some dummy kills roscore 
}
