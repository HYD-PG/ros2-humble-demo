#include "rclcpp/rclcpp.hpp"
#include "base_interfaces_demo/msg/student.hpp"
using namespace std::chrono_literals;
using base_interfaces_demo::msg::Student;
class talker02:public rclcpp::Node
{
    public:
    talker02():Node("student_publisher"),count_(0)
    {
        RCLCPP_INFO(this->get_logger(),"start talker02");
        publisher_=this->create_publisher<base_interfaces_demo::msg::Student>("student_chatter",10);
        timer_=this->create_wall_timer(1s,std::bind(&talker02::timer_callback,this));
    }
    private:
    void timer_callback()
    {
        auto stu=Student();
        stu.name="zhang san";
        stu.age=count_++;
        stu.height=175.58;
        RCLCPP_INFO(this->get_logger(),"publisher data are: student name=%s,age=%d,height=%.2f",stu.name.c_str(),stu.age,stu.height);
        publisher_->publish(stu);
    }
    rclcpp::Publisher<base_interfaces_demo::msg::Student>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    size_t count_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<talker02>()); 
    rclcpp::shutdown();
    return 0;
}
