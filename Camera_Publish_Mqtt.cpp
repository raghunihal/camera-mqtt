#include <iostream>
#include <opencv2/opencv.hpp>
#include <mqtt/async_client.h>

using namespace std;
using namespace cv;

const string MQTT_SERVER_ADDRESS = "tcp://localhost:1883";
const string MQTT_CLIENT_ID = "video_publisher";
const string MQTT_TOPIC = "video_frames";

void on_connect(const mqtt::token & token) 
{
  cout << "Connected to MQTT broker" << endl;
}

void on_publish(const mqtt::token & token) 
{
  cout << "Frame published" << endl;
}

int main() 
{
  // Initialize MQTT client
  mqtt::async_client client(MQTT_SERVER_ADDRESS, MQTT_CLIENT_ID);

  // Set MQTT connection options
  mqtt::connect_options connOpts;
  connOpts.set_clean_session(true);

  // Set MQTT callbacks
  client.set_callback(on_connect);
  client.set_callback(on_publish);

  // Connect to MQTT broker
  mqtt::token_ptr conntok = client.connect(connOpts);
  conntok -> wait();

  // Open video capture
  VideoCapture cap(0);
  if (!cap.isOpened()) 
  {
    cerr << "Failed to open video capture" << endl;
    return 1;
  }

  // Publish video frames
  Mat frame;
  while (true) 
  {
    cap >> frame;
    if (frame.empty()) 
    {
      cerr << "Failed to capture frame" << endl;
      break;
    }

    // Convert frame to JPEG format
    vector < uchar > buf;
    imencode(".jpg", frame, buf);

    // Publish frame to MQTT topic
    mqtt::message_ptr pubmsg = mqtt::make_message(MQTT_TOPIC, buf.data(), buf.size());
    client.publish(pubmsg) -> wait();
  }
  // Disconnect from MQTT broker
  mqtt::token_ptr disctok = client.disconnect();
  disctok -> wait();

  return 0;
}
