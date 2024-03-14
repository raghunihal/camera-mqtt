# Camera_Publish_Mqtt.cpp
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
