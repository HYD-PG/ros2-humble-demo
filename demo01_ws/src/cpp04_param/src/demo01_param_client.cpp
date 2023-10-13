#include "rclcpp/rclcpp.hpp"

class param_client:public rclcpp::Node{
        public:
        param_client():Node("param_client")
        {
            RCLCPP_INFO(this->get_logger(),"参数客户端开启");
        }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<param_client>());
    rclcpp::shutdown();
    return 0;
}
