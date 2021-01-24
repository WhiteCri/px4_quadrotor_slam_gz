#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>

static nav_msgs::Odometry odom;

bool update = false;

void odomSub(const nav_msgs::OdometryConstPtr &ptr){
    odom = *ptr;
    update = true;
}


int main(int argc, char *argv[]){
    ros::init(argc, argv, "map_baselink_broadcaster");
    ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe("mavros/local_position/odom", 10, odomSub);
    
    tf::TransformBroadcaster odom_broadcaster;
    geometry_msgs::TransformStamped odom_trans;

    ros::Rate loop_rate(100); //100hz
    while(ros::ok()){
        ros::spinOnce();
        if (!update) { //check if new data received
            loop_rate.sleep();
            continue;
        }
        
        odom_trans.header.seq = odom.header.seq;
        odom_trans.header.stamp = ros::Time::now();
        odom_trans.header.frame_id = "map"; //mavros frame
        odom_trans.child_frame_id = odom.child_frame_id;

        odom_trans.transform.translation.x      = odom.pose.pose.position.x;
        odom_trans.transform.translation.y      = odom.pose.pose.position.y;
        odom_trans.transform.translation.z      = odom.pose.pose.position.z;
        odom_trans.transform.rotation           = odom.pose.pose.orientation;

        odom_broadcaster.sendTransform(odom_trans);
        update = false;
    }
}