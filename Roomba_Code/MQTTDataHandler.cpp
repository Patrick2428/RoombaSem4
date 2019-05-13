#include "MQTTDataHandler.h"
#include "Config.h"
#include <iostream>
#include <mosquittopp.h>
#include <string>

MQTTDataHandler::MQTTDataHandler(const std::string &appname,
				 const std::string &clientname,
				 const std::string &host,
				 int port)
  : mosqpp::mosquittopp{(HOSTNAME + appname + clientname).c_str()}
  
{
  std::cout << "Connecting to host = " <<host << " port = " << port
	    << std::endl;

  connect(host.c_str(), port, MQTT_KEEP_ALIVE);
    
}

MQTTDataHandler::~MQTTDataHandler()
{
  std::cout << "Disconnected from server" <<std::endl;
}

void MQTTDataHandler::on_connect(int rc)
{
  std::cout << "connected with rc = " << rc <<std::endl;
   if (rc == 0) {
      /// Only attempt to subscribe on a successful connect.
      rc = subscribe(nullptr, MQTT_TOPIC_ROOMBA_CONTROLLER.c_str(), MQTT_QoS_0);
      }
   
}

void MQTTDataHandler::on_disconnect(int rc)
{
  std::cout << " disconnected with rc = " << rc << std::endl;
}

void MQTTDataHandler::on_message(const mosquitto_message *message)
{
 
  std::string topic{message->topic};

  if(topic == MQTT_TOPIC_ROOMBA_CONTROLLER)
    {
      receivedData = static_cast<char * >(message->payload);
      std::cout << "The received data is: " <<receivedData<<std::endl;
    }
  
}

void MQTTDataHandler::on_subscribe(int mid, int qos_count,
                                        const int *granted_qos)
{
  std::cout << "subscription succeeded" <<std::endl;
}

void MQTTDataHandler::on_log(int level, const char* str)
{
  std::cout<<"level = " <<level << ": " << str << std::endl;
}

void MQTTDataHandler::on_error()
{
  std::cout<<"Error"<<std::endl;
}
