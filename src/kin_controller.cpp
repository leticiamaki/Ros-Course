#include<ros/ros.h>
#include<std_msgs/Float64.h>
#include<geometry_msgs/Twist.h>

ros::Publisher pub_right;
ros::Publisher pub_left;
std_msgs::Float64 wr;
std_msgs::Float64 wl;

void fcnCallback(const geometry_msgs::TwistConstPtr &msg){
    double v, w;
    double b = 0.35, r = 0.1;
    v = msg->linear.x;
    w = msg->angular.z;    
                
    wr.data = (v + (b/2) * w) / r;
    wl.data = (v - (b/2) * w) / r;        
               
    pub_right.publish(wr);
    pub_left.publish(wl);      
                
}

int main(int argc, char **argv){
    //start ros within this node
    ros::init(argc, argv, "controller");
    
    ros::NodeHandle node; 
    pub_right = node.advertise<std_msgs::Float64>("/vrep/vehicle/motorRightSpeed", 1);  // 1 mensagem fica guardada no buffer
    
    pub_left = node.advertise<std_msgs::Float64>("/vrep/vehicle/motorLeftSpeed", 1);
    
    ros::Subscriber sub = node.subscribe("/cmd_vel", 1, fcnCallback); 
    
    ros::spin();
    return 0;

}