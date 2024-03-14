/*************************************************************************************************************
This C++ code is using the OpenCV library and the MQTT library to capture video frames from a camera and publish them to an MQTT topic. 
The code starts by including the necessary libraries and defining some functions for handling MQTT connection events. 
The `on_connect` function is called when the client successfully connects to the MQTT broker, and it prints the result code of the connection. 
The `on_disconnect` function is called when the client is unexpectedly disconnected from the broker, and it prints a message if the disconnection reason code is not `SUCCESS`. 
The `on_publish` function is called when a message is successfully published, and it prints the message ID. 
In the `main` function, an MQTT client is created with the TCP protocol and the broker address is specified. 
The connection options are set to have a keep-alive interval of 60 seconds and to use a clean session. 
The callback function for publishing events is set to `on_publish`, and the connection lost handler is set to `on_disconnect`. 
The code then attempts to connect to the MQTT broker using the specified connection options and the `on_connect` function as the callback for the connection response. 
If the connection is successful, the client starts consuming messages. Next, the code creates a `VideoCapture` object to capture video frames from the default camera (index 0). 

If the camera fails to open, an error message is printed and the program returns with an exit code of 

1. Inside a while loop, the code reads a frame from the camera, encodes it as a JPEG image, and stores it in a vector of `uchar` (unsigned char) values. 
The JPEG image is then converted to a string and published to the MQTT topic "topic/test" with a QoS (Quality of Service) level of 0. 

If any exceptions occur during the execution of the code, an error message is printed and the program returns with an exit code of 
1. Finally, the `main` function returns 0 to indicate successful execution of the program.
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


