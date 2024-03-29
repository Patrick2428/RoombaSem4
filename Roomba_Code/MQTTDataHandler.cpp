/** @file */
///\brief MQTTDatahandler member functions 
#include "MQTTDataHandler.h"
#include "Config.h"
#include <iostream>
#include <mosquittopp.h>
#include <string>
///MQTTDataHandler class member function implementation
MQTTDataHandler::MQTTDataHandler(const std::string &data,
				 const std::string &appname,
				 const std::string &clientname,
				 const std::string &host,
				 int port)
  : receivedData(data), mosqpp::mosquittopp{(HOSTNAME + appname + clientname).c_str()} 
  
{
  std::cout << "Connecting to host = " <<host << " port = " << port
	    << std::endl;

  connect(host.c_str(), port, MQTT_KEEP_ALIVE);
    
}

MQTTDataHandler::~MQTTDataHandler()
{
  std::cout << "Disconnected from server" <<std::endl;
}

///function that subscribes to topic "ESEiot/TeamFyre/roomba/controller" to receive Commands/messages for roomba control
void MQTTDataHandler::on_connect(int rc)
{
  std::cout << "connected with rc = " << rc <<std::endl;
   if (rc == 0) {
      /// Only attempt to subscribe on a successful connect.
      rc = subscribe(nullptr, MQTT_TOPIC_ROOMBA_CONTROLLER.c_str(), MQTT_QoS_0);
      }
   
}

///If the MQTT server disconnected 
void MQTTDataHandler::on_disconnect(int rc)
{
  std::cout << " disconnected with rc = " << rc << std::endl;
}

///Handling received message from subscribed topic "ESEiot/TeamFyre/roomba/controller"
void MQTTDataHandler::on_message(const mosquitto_message *message)
{
 
  std::string topic{message->topic};

  if(topic == MQTT_TOPIC_ROOMBA_CONTROLLER)
    {
      receivedData = static_cast<char * >(message->payload);
      std::cout << "The received data is: " <<receivedData<<std::endl;
    }
  
}
///Publish message to topic "ESEiot/TeamFyre/roomba/interface"
void MQTTDataHandler::sendMessage(std::string ms)
{
  auto rc = publish(nullptr, MQTT_TOPIC_ROOMBA_INTERFACE.c_str(), ms.size(), ms.c_str(),MQTT_QoS_0);
  
  if(rc != MOSQ_ERR_SUCCESS)
    {
      on_log(1, mosquitto_strerror(rc));
    }

}

void MQTTDataHandler::on_subscribe(int mid, int qos_count,
                                        const int *granted_qos)
{
  std::cout << "subscription succeeded" <<std::endl;
}

///logging MQTT connection description
void MQTTDataHandler::on_log(int level, const char* str)
{
  std::cout<<"level = " <<level << ": " << str << std::endl;
}

void MQTTDataHandler::on_error()
{
  std::cout<<"Error"<<std::endl;
}

std::string MQTTDataHandler::getData() const
{
  return receivedData;
}
void MQTTDataHandler::resetData()
{
  receivedData.clear();
  receivedData = "idle";
}

void MQTTDataHandler::setMessage(std::string message)
{
  message_ = message;
}

void MQTTDataHandler::appendMessage(std::string message)
{
  message_.append(message);
}

std::string MQTTDataHandler::getMessage()
{
  return message_;
}
