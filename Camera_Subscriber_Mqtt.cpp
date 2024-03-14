


/************************************************************************************/
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <mqtt/client.h>
/************************************************************************************/
void on_connect(mqtt::client& client, void* userdata, int rc) 
{
  std::cout << "Connected with result code " << rc << std::endl;
  client.subscribe("topic/test", 0);
}
/************************************************************************************/
void on_disconnect(mqtt::client& client, void* userdata, int rc) 
{
  if (rc != 0) 
  {
    std::cout << "Unexpected disconnection." << std::endl;
  }
}
/************************************************************************************/
void on_message(mqtt::client& client, void* userdata, const mqtt::message& msg) 
{
  std::vector<uint8_t> payload = msg.get_payload();
  cv::Mat image_buffer = cv::imdecode(payload, cv::IMREAD_COLOR);
  cv::imshow("image", image_buffer);
  int key = cv::waitKey(10);
  
  if (key == 27) 
  {
    cv::destroyAllWindows();
  }
}
/************************************************************************************/
int main() 
{
  mqtt::client client("tcp://localhost:1883", "client_id");
  client.set_callback(on_message);
  
  try 
  {
    client.connect();
    client.subscribe("topic/test", 0);
    client.loop_forever();
  } 
  catch (const mqtt::exception& exc) 
  {
    std::cerr << "Error: " << exc.what() << std::endl;
    return 1;
  }
  
  return 0;
}
/************************************************************************************/

