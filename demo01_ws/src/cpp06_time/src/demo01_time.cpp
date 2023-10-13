#include "rclcpp/rclcpp.hpp"
using namespace std::chrono_literals;


class demo_time:public rclcpp::Node {
    public:
    demo_time():Node("demo_time")
    {
        demo_rate();

    }
    private:
    void demo_rate()
    {
        rclcpp::Rate rate(500ms);//设置休眠时间
        rclcpp::Rate rate1(1.0);//设置执行频率
        while (rclcpp::ok())
        {
          rate.sleep();
          RCLCPP_INFO(this->get_logger(),"hello rate");
        }
        
    }

};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<demo_time>());
  rclcpp::shutdown();
  return 0;
}