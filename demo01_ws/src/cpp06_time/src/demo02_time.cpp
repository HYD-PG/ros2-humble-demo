#include "rclcpp/rclcpp.hpp"

using namespace std::chrono_literals;
class demo02_time:public rclcpp::Node{

    public:
          demo02_time():Node("demo02_time"){
          demo_time();
          demo_duration();
          }
    private:
    void demo_time(){
            rclcpp::Time t1(500000000L);
            rclcpp::Time t2(2,500000000L);
            //获取当前时刻的操作
            rclcpp::Time right_now=this->get_clock()->now();
            rclcpp::Time right_now1=this->now();

            RCLCPP_INFO(this->get_logger(),"s= %.2f,ns= %ld",t1.seconds(),t1.nanoseconds());
            RCLCPP_INFO(this->get_logger(),"s= %.2f,ns= %ld",t2.seconds(),t2.nanoseconds());

            RCLCPP_INFO(this->get_logger(),"s= %.2f,ns= %ld",right_now.seconds(),right_now1.nanoseconds());
            RCLCPP_INFO(this->get_logger(),"s= %.2f,ns= %ld",right_now.seconds(),right_now1.nanoseconds());

    }
    void demo_duration(){
        rclcpp::Duration d1(1s);
        rclcpp::Duration d2(2,500000000L);
        
        RCLCPP_INFO(this->get_logger(),"s=%.2f,ns=%ld",d2.seconds(),d2.nanoseconds());
        RCLCPP_INFO(this->get_logger(),"s=%.2f,ns=%ld",d1.seconds(),d1.nanoseconds());
    }
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<demo02_time>());
    rclcpp::shutdown();
    return 0;
}
