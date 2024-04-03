# Camera_Publish_Mqtt.cpp
  
This C++ code is a program that captures video frames from a webcam and publishes them to an MQTT (Message Queuing Telemetry Transport) broker. Here's a breakdown of the code: 1. The program includes the necessary header files: `<iostream>` for input/output operations, `<opencv2/opencv.hpp>` for OpenCV library functions, and `<mqtt/async_client.h>` for MQTT client functionality. 
2. The program uses the `std` and `cv` namespaces for easier access to the standard library and OpenCV functions, respectively. 
3. It defines the MQTT server address, client ID, and topic name as constants. 
4. The `on_connect` and `on_publish` functions are defined as callbacks for the MQTT client. These functions will be called when the client connects to the MQTT broker and when a message is published, respectively.
5. The `main` function is the entry point of the program. 
6. Inside the `main` function, an MQTT asynchronous client is initialized with the server address and client ID. 
7. The MQTT connection options are set, including the "clean session" flag, which means the client will start with a fresh session. 
8. The MQTT callbacks (`on_connect` and `on_publish`) are set for the client. 
9. The client connects to the MQTT broker, and the connection is waited for.
10. A video capture object is created to access the webcam. 
11. If the video capture is successfully opened, the program enters a loop to capture video frames. 
12. Inside the loop, each captured frame is converted to JPEG format using the OpenCV `imencode` function. 
13. The JPEG-encoded frame data is then published to the MQTT topic using the MQTT client's `publish` function. 
14. After the loop, the MQTT client is disconnected from the broker. 
15. The program returns 0, indicating successful execution. 

In summary, this program captures video frames from a webcam, converts them to JPEG format, and publishes them to an MQTT broker for potential consumption by other MQTT clients.

# Command for Compiling the Program
g++ Camera_Publish_Mqtt.cpp `pkg-config --cflags --libs opencv4` -lpaho-mqttpp3 -lpaho-mqtt3as - o Camera_Publish_Mqtt



# Camera_Subscriber_Mqtt.cpp


# Command for Compiling the Program
g++ Camera_Subscriber_Mqtt.cpp `pkg-config --cflags --libs opencv4` -lpaho-mqttpp3 -lpaho-mqtt3as - o Camera_Subscriber_Mqtt
