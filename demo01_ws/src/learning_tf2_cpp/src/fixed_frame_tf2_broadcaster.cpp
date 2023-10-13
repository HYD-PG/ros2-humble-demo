#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "tf2_ros/transform_broadcaster.h"

using namespace std::chrono_literals;

class fixed_frame_tf2_broadcaster:public rclcpp::Node{
public:
    fixed_frame_tf2_broadcaster():Node("fixed_frame_tf2_broadcaster"){
            tf_broadcaster_=std::make_shared<tf2_ros::TransformBroadcaster>(this);
            timer_ = this->create_wall_timer(
                100ms,
                std::bind(&fixed_frame_tf2_broadcaster::broadcast_timer_callback, this));
    }
private:
        std::shared_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
        rclcpp::TimerBase::SharedPtr timer_;
        void broadcast_timer_callback()
        {
            geometry_msgs::msg::TransformStamped t;
            t.header.stamp=this->get_clock()->now();
            t.header.frame_id="turtle1";
            t.child_frame_id="carrot1";
            t.transform.translation.x=0.0;
            t.transform.translation.y=2.0;
            t.transform.translation.z=0.0;
            t.transform.rotation.x=0.0;
            t.transform.rotation.y=0.0;
            t.transform.rotation.z=0.0;
            t.transform.rotation.w=1.0;
            tf_broadcaster_->sendTransform(t);
        }
};

int main(int argc, char const **argv)
{
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<fixed_frame_tf2_broadcaster>());
    rclcpp::shutdown();

    return 0;
}
