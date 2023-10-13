#include "rclcpp/rclcpp.hpp"
#include "base_interfaces_demo/srv/add_ints.hpp"
using base_interfaces_demo::srv::AddInts;

class Addintservice:public rclcpp::Node
{
    public:
    Addintservice():Node("demo01_service"){
        service_=this->create_service<AddInts>("add_ints", std::bind(&Addintservice::add, this,std::placeholders::_1,std::placeholders::_2));
        RCLCPP_INFO(this->get_logger(),"服务端创建完毕");
    }
    private:
    void add(const AddInts::Request::SharedPtr req,const AddInts::Response::SharedPtr res)
    {
        res->sum=req->num1+req->num2;
        RCLCPP_INFO(this->get_logger(),"%d + %d = %d",req->num1,req->num2,res->sum);

    }
    rclcpp::Service<AddInts>::SharedPtr service_;
};

int main(int argc, char const *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Addintservice>());
    rclcpp::shutdown();
    return 0;
}