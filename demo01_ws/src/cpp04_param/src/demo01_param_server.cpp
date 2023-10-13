#include "rclcpp/rclcpp.hpp"

class param_server:public rclcpp::Node{
        public:
        param_server():Node("param_server",rclcpp::NodeOptions().allow_undeclared_parameters(true))
        {
            RCLCPP_INFO(this->get_logger(),"参数服务端启动");
        }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<param_server>());
    rclcpp::shutdown();
    return 0;
}
