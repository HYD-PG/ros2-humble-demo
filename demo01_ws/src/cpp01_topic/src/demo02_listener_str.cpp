#include "rclcpp/rclcpp.hpp"
#include "base_interfaces_demo/msg/student.hpp"
using std::placeholders::_1;
using base_interfaces_demo::msg::Student;

class listener02 : public rclcpp::Node
{
public:
  listener02():Node("student_listener")
  {
    subscription_=this->create_subscription<base_interfaces_demo::msg::Student>("student_chatter",10,std::bind(&listener02::topic_callback,this,std::placeholders::_1));
  }
  private:
  void topic_callback(const Student & msg)
  {
    RCLCPP_INFO(this->get_logger(), "received message: name=%s, age=%d, height=%.2f", msg.name.c_str(), msg.age,msg.height);
  }
  rclcpp::Subscription<Student>::SharedPtr subscription_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<listener02>());
    rclcpp::shutdown();
    return 0;
}

