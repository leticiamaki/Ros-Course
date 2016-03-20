#include<ros/ros.h>
#include<std_msgs/Float64.h>
#include<geometry_msgs/Twist.h>

int main(int argc, char **argv){
    
    double v = 1, w = 0; 
    double b = 0.35, r = 0.1;
    
    //start ros within this node
    ros::init(argc, argv, "controller");
    
    ros::NodeHandle node; 
    
    ros::Publisher pub_right = node.advertise<std_msgs::Float64>("/vrep/vehicle/motorRightSpeed", 1);  // 1 mensagem fica guardada no buffer
    
    ros::Publisher pub_left = node.advertise<std_msgs::Float64>("/vrep/vehicle/motorLeftSpeed", 1);
    
    ros::Rate loop_rate(60);
    
     std_msgs::Float64 wr;
     std_msgs::Float64 wl;
         
    while(ros::ok()){
        
        wr.data = (v + (b/2) * w) / r;
        wl.data = (v - (b/2) * w) / r;        
               
        pub_right.publish(wr);
        pub_left.publish(wl);        
            
        ros::spinOnce();
        loop_rate.sleep();
    }
    
    return 0;

}