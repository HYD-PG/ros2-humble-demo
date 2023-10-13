#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
using namespace std::chrono_literals;

class talker: public rclcpp::Node{
    public:
    talker():Node("talker_node_cpp"),count_(0){
        RCLCPP_INFO(this->get_logger(),"发布节点创建！");
        publisher_= this->create_publisher<std_msgs::msg::String>("chatter",10);
        timer_=this->create_wall_timer<>(1s,std::bind(&talker::on_timer,this));
    }
    private:
    void on_timer(){
        auto message=std_msgs::msg::String();
        message.data="Hello world!"+std::to_string(count_++);
        RCLCPP_INFO(this->get_logger(),"发布的消息：%s",message.data.c_str());
        publisher_->publish(message);
    }
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    size_t count_;
};

int main(int argc, char const **argv)
{
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<talker>());
    rclcpp::shutdown();
    return 0;
}
