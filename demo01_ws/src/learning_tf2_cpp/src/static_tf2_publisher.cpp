#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_ros/static_transform_broadcaster.h"

class static_tf2_publisher: public rclcpp::Node
{
    public:
    explicit static_tf2_publisher(char *transformation[]):Node("static_tf2_publisher")
    {
        tf_static_broadcaster_=std::make_shared<tf2_ros::StaticTransformBroadcaster>(this);
        this->make_transform(transformation);
    }
    private:
    std::shared_ptr<tf2_ros::StaticTransformBroadcaster> tf_static_broadcaster_;
    void make_transform(char *transformation[])
    {
        geometry_msgs::msg::TransformStamped t;
        t.header.stamp=this->get_clock()->now();
        t.header.frame_id="world";
        t.child_frame_id=transformation[1];
        
        t.transform.translation.x=atof(transformation[2]);
        t.transform.translation.y=atof(transformation[3]);
        t.transform.translation.z=atof(transformation[4]);
        tf2::Quaternion q;
        q.setRPY(
            atof(transformation[5]),
            atof(transformation[6]),
            atof(transformation[7])
        );
        t.transform.rotation.x=q.x();
        t.transform.rotation.y=q.y();
        t.transform.rotation.z=q.z();
        t.transform.rotation.w=q.w();
        tf_static_broadcaster_->sendTransform(t);
    }

};

int main(int argc, char **argv)
{
    auto logger=rclcpp::get_logger("logger");
    if(argc!=8){
        RCLCPP_INFO(logger,"Invalid number of parameters");
        return 1;
    }
    if(strcmp(argv[1],"world")==0){
        RCLCPP_INFO(logger,"Your static turtle name cannot be world");
        return 1;
    }

    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<static_tf2_publisher>(argv));
    rclcpp::shutdown();
    return 0;
}
