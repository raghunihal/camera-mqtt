# Camera_Publish_Mqtt.cpp


# Command for Compiling the Program
g++ Camera_Publish_Mqtt.cpp `pkg-config --cflags --libs opencv4` -lpaho-mqttpp3 -lpaho-mqtt3as - o Camera_Publish_Mqtt



# Camera_Subscriber_Mqtt.cpp


# Command for Compiling the Program
g++ Camera_Subscriber_Mqtt.cpp `pkg-config --cflags --libs opencv4` -lpaho-mqttpp3 -lpaho-mqtt3as - o Camera_Subscriber_Mqtt
