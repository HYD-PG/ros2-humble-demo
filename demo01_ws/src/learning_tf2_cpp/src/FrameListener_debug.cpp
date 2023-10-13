#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"
#include "tf2/exceptions.h"
#include "turtlesim/srv/spawn.hpp"
using namespace std::chrono_literals;

class FrameListener_debug : public rclcpp::Node
{
public:
    FrameListener_debug() : Node("FrameListener_debug"), turtle_spawning_service_ready_(false), turtle_spawned_(false)
    {
        target_frame_ = this->declare_parameter<std::string>("target_frame", "turtle1");
        tf_buffer_ = std::make_unique<tf2_ros::Buffer>(this->get_clock());
        tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);

        /* 创建小乌龟的客户端对象 */
        spawner_ = this->create_client<turtlesim::srv::Spawn>("spawn");
        /* 创建速度的发布者 */
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("turtle2/cmd_vel", 10);
        /* 创将定时器 */
        timer_ = this->create_wall_timer(1s, std::bind(&FrameListener_debug::on_timer, this));
    }

private:
    bool turtle_spawning_service_ready_;
    bool turtle_spawned_;
    std::string target_frame_;
    std::unique_ptr<tf2_ros::Buffer> tf_buffer_;
    std::shared_ptr<tf2_ros::TransformListener> tf_listener_;
    rclcpp::Client<turtlesim::srv::Spawn>::SharedPtr spawner_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    void on_timer()
    {
        std::string fromFrameRel = target_frame_.c_str();
        std::string toFrameRel = "turtle2";

        if (turtle_spawning_service_ready_)
        {
            if (turtle_spawned_)
            {
                geometry_msgs::msg::TransformStamped t;

                try
                {
                    t = tf_buffer_->lookupTransform(toFrameRel, fromFrameRel, tf2::TimePointZero);
                }
                catch (const tf2::TransformException &ex)
                {
                    RCLCPP_INFO(this->get_logger(), "Could not transform %s to %s: %s", toFrameRel.c_str(), fromFrameRel.c_str(), ex.what());
                    return;
                }
                geometry_msgs::msg::Twist msg;
                static const double scaleRotationRate = 1.0;
                msg.angular.z = scaleRotationRate * atan2(t.transform.translation.y, t.transform.translation.x);

                static const double scaleForwardSpeed = 0.5;
                msg.linear.x = scaleForwardSpeed * sqrt(pow(t.transform.translation.x, 2) + pow(t.transform.translation.y, 2));
                publisher_->publish(msg);
            }
            else
            {
            RCLCPP_INFO(this->get_logger(), "成功运动");
            turtle_spawned_ = true;
            }
            
        }
    else
    {
        if (spawner_->service_is_ready())
        {
            auto request = std::make_shared<turtlesim::srv::Spawn::Request>();
            request->x = 4.0;
            request->y = 2.0;
            request->theta = 0.0;
            request->name = "turtle2";

            using ServiceResponseFuture = rclcpp::Client<turtlesim::srv::Spawn>::SharedFuture;
            auto response_received_callback = [this](ServiceResponseFuture future)
            {
                auto result = future.get();
                if (strcmp(result->name.c_str(), "turtle2") == 0)
                {
                    turtle_spawning_service_ready_ = true;
                }
                else
                {
                    RCLCPP_ERROR(this->get_logger(), "服务回调结果不匹配");
                }
            };
            auto result = spawner_->async_send_request(request, response_received_callback);
        }
        else
        {
            RCLCPP_INFO(this->get_logger(), "服务未准备完成");
        }
    }
}
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<FrameListener_debug>());
    rclcpp::shutdown();
    return 0;
}
