#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"


class node_name:public rclcpp::Node{
  public:
  node_name()
  : Node("node_name","t1_ns"){
    RCLCPP_INFO(this->get_logger(),"node_name");
    pub_ = this->create_publisher<std_msgs::msg::String>("hello", 10);

  }
  private:
      rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_;

};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<node_name>());
  rclcpp::shutdown();
  return 0;
}
