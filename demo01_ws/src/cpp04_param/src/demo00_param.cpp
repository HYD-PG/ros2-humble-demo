#include "rclcpp/rclcpp.hpp"

class parameter_node:public rclcpp::Node
{
    public:
    parameter_node():Node("my_param_node"){
        RCLCPP_INFO(this->get_logger(),"参数使用");
        rclcpp::Parameter p1("car_name","Tiger");
        rclcpp::Parameter p2("height",1.68);
        rclcpp::Parameter p3("wheels",4);

        RCLCPP_INFO(this->get_logger(),"car_name=%s",p1.as_string().c_str());
        RCLCPP_INFO(this->get_logger(),"height=%.2f",p2.as_double());
        RCLCPP_INFO(this->get_logger(),"wheels=%ld",p3.as_int());

        RCLCPP_INFO(this->get_logger(),"name=%s",p1.get_name().c_str());
        RCLCPP_INFO(this->get_logger(),"type_name=%s",p1.get_type_name().c_str());

    }
    private:
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<parameter_node>());
    rclcpp::shutdown();
    return 0;
}
