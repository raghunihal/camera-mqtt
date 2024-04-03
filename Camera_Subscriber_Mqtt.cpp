#include <iostream>
#include <opencv2/opencv.hpp>
#include <mqtt/async_client.h>

using namespace cv;

class MqttSubscriber 
{
  public: MqttSubscriber(const std::string & serverURI,
    const std::string & clientId,
      const std::string & topic): serverURI(serverURI),
  clientId(clientId),
  topic(topic) 
  {

  }

  void connect() 
  {
    mqtt::connect_options connOpts;
    connOpts.set_keep_alive_interval(20);
    connOpts.set_clean_session(true);
    client = std::make_shared < mqtt::async_client > (serverURI, clientId);
    client -> set_callback( * this);

    try 
    {
      mqtt::token_ptr conntok = client -> connect(connOpts);
      conntok -> wait();
      std::cout << "Connected to MQTT broker" << std::endl;
      client -> subscribe(topic, 1) -> wait();
      std::cout << "Subscribed to topic: " << topic << std::endl;
    } 
    catch (const mqtt::exception & exc) 
    {
      std::cerr << "Error: " << exc.what() << std::endl;
    }
  }

  void disconnect() 
  {
    try 
    {
      client -> unsubscribe(topic) -> wait();
      std::cout << "Unsubscribed from topic: " << topic << std::endl;

      client -> disconnect() -> wait();
      std::cout << "Disconnected from MQTT broker" << std::endl;
    } 
    catch (const mqtt::exception & exc) 
    {
      std::cerr << "Error: " << exc.what() << std::endl;
    }
  }

  void message_arrived(mqtt::const_message_ptr msg) override 
  {
    std::vector < uchar > data(msg -> payload().begin(), msg -> payload().end());
    cv::Mat frame = cv::imdecode(data, cv::IMREAD_COLOR);

    if (!frame.empty()) 
    {
      cv::imshow("Received Frame", frame);
      cv::waitKey(1);
    }
  }

  private: std::string serverURI;
  std::string clientId;
  std::string topic;
  std::shared_ptr < mqtt::async_client > client;
};

int main() 
{
  std::string serverURI = "tcp://localhost:1883";
  std::string clientId = "mqtt_subscriber";
  std::string topic = "video_frame_topic";
  MqttSubscriber subscriber(serverURI, clientId, topic);
  subscriber.connect();

  while (true) 
  {
    // Keep the program running
  }
  subscriber.disconnect();
  return 0;
}
