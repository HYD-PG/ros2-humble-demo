#include "rclcpp/rclcpp.hpp"
#include "base_interfaces_demo/srv/add_ints.hpp"

using base_interfaces_demo::srv::AddInts;
using namespace std::chrono_literals;

class Addintsclient:public rclcpp::Node {
    public:
    Addintsclient():Node("demo01_client")
    {
        client_ = this->create_client<base_interfaces_demo::srv::AddInts>("add_ints");
        RCLCPP_INFO(this->get_logger(),"客户端创建完成,等待服务端响应");
    }
    bool connect_to_server()
    {
        while (!client_->wait_for_service(1s))
        {
            if(!rclcpp::ok())
            {
                RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"未等到服务器连接响应，连接失败！");
                return false;
               
            }
            RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"服务连接中!请等待……");
        }
        
        
        return true;
    }
    rclcpp::Client<AddInts>::FutureAndRequestId send_request(int num1,int num2){
        auto request = std::make_shared<AddInts::Request>();
        request->num1 = num1;
        request->num2 = num2;
        return client_->async_send_request(request);
    }
    private:
    rclcpp::Client<AddInts>::SharedPtr client_;
    };

int main(int argc, char  **argv)
{
    if(argc !=3)
    {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),"please input Two parameters:");
        return 1;
    }
    rclcpp::init(argc, argv);
    auto client=std::make_shared<Addintsclient>();
    bool flag =client->connect_to_server();
    if(!flag)
    {
        RCLCPP_FATAL(rclcpp::get_logger("rclcpp"),"服务器连接失败，退出主程序");
        return 0;
    }
    auto response =client->send_request(atoi(argv[1]),atoi(argv[2]));
    if (rclcpp::spin_until_future_complete(client,response)== rclcpp::FutureReturnCode::SUCCESS)
    {
        RCLCPP_INFO(client->get_logger(),"请求相应成功！响应结果为：%d",response.get()->sum);
    }
    else
    {
        RCLCPP_FATAL(client->get_logger(),"Invalid response from server-请求异常");
    }
    
    rclcpp::shutdown();
    return 0;
}
