**************************************************************************************************************/
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <mqtt/client.h>
/**************************************************************************************************************/
void on_connect(mqtt::client& client, mqtt::connect_options& connOpts, mqtt::connect_response& response) 
{
    std::cout << "Connected with result code: " << response.get_return_code() << std::endl;
}
/**************************************************************************************************************/
void on_disconnect(mqtt::client& client, mqtt::disconnect_response& response) 
{
    if (response.get_reason_code() != mqtt::reason_code::SUCCESS) 
	{
        std::cout << "Unexpected disconnection." << std::endl;
    }
}
/**************************************************************************************************************/
void on_publish(mqtt::client& client, std::uint16_t mid) 
{
    std::cout << "publish: " << mid << std::endl;
}
/**************************************************************************************************************/
int main() 
{
    mqtt::client client("tcp://localhost:1883", "cpp_client");
    mqtt::connect_options connOpts;
    connOpts.set_keep_alive_interval(60);
    connOpts.set_clean_session(true);

    client.set_callback(on_publish);
    client.set_connection_lost_handler(on_disconnect);

    try 
	{
        client.connect(connOpts, nullptr, on_connect);
        client.start_consuming();

        cv::VideoCapture camera(0);
        if (!camera.isOpened()) 
		{
            std::cerr << "Failed to open camera." << std::endl;
            return 1;
        }

        while (true) 
		{
            cv::Mat frame;
            camera.read(frame);

            std::vector<uchar> buffer;
            cv::imencode(".jpg", frame, buffer);

            std::string jpg_original(buffer.begin(), buffer.end());

            client.publish("topic/test", jpg_original, 0);
        }
    } 
	catch (const mqtt::exception& exc) 
	{
        std::cerr << "Error: " << exc.what() << std::endl;
        return 1;
    }

    return 0;
}
/**************************************************************************************************************/


