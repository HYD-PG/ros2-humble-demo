#include "rclcpp/rclcpp.hpp"
class mynode: public rclcpp::Node{
public: 
mynode():Node("helloworld_cpp"){
  RCLCPP_INFO(this->get_logger(),"helloworld");
}
};

int main(int argc, char **argv)
{
  rclcpp::init(argc,argv);
  auto node=std::make_shared<mynode>();
  rclcpp::shutdown();
  return 0;
}


/* #include "rclcpp/rclcpp.hpp"

int main(int argc, char ** argv)
{
  // 初始化 ROS2
  rclcpp::init(argc,argv);
  // 创建节点
  auto node = rclcpp::Node::make_shared("helloworld_node");
  // 输出文本
  RCLCPP_INFO(node->get_logger(),"hello world!");
  // 释放资源
  rclcpp::shutdown();
  return 0;
} */
