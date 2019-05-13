#include "TemperatureConverter.h"
#include "Config.h"
#include <iostream>
#include <mosquittopp.h>
#include <string>

#define CERR std::cerr << className_ << "::" << __func__ << "()\n   "

TemperatureConverter::TemperatureConverter(const std::string &appname,
                                           const std::string &clientname,
                                           const std::string &host,
                                           int port)
   : mosqpp::mosquittopp{(HOSTNAME + appname + clientname).c_str()}
   , className_{__func__}
   , mqttID_{HOSTNAME + appname + clientname}
{
   CERR << " connect() host = '" << host << "'  port = " << port
        << "  id = " << mqttID_ << "  topic root = " << MQTT_TOPIC_ROOT
        << std::endl;
   connect(host.c_str(), port, MQTT_KEEP_ALIVE);
}

TemperatureConverter::~TemperatureConverter()
{
   CERR << " disconnect()" << std::endl;
}

void TemperatureConverter::on_connect(int rc)
{
   CERR << " connected with rc = " << rc << std::endl;
   if (rc == 0) {
      /// Only attempt to subscribe on a successful connect.
      rc = subscribe(nullptr, MQTT_TOPIC_CELSIUS_Q.c_str(), MQTT_QoS_0);
      CERR << " " << MQTT_TOPIC_CELSIUS_Q << std::endl;
      if (rc != MOSQ_ERR_SUCCESS) {
         on_log(1, mosquitto_strerror(rc));
      }
   }
}

void TemperatureConverter::on_disconnect(int rc)
{
   CERR << " disconnected with rc = " << rc << " '"
        << mosquitto_strerror(rc) << "'" << std::endl;
}

/// @todo Implement the conversion: Fahrenheit to Celsius.
void TemperatureConverter::on_message(const mosquitto_message *message)
{
   double temp_celsius{0.0};
   double temp_fahrenheit{0.0};
   std::string topic{message->topic};

   if (topic == MQTT_TOPIC_CELSIUS_Q) {
      try {
         /// @note C++11: stod() can throw invalid_argument exception.
         temp_celsius = std::stod(static_cast<char *>(message->payload));
	 std::cout << "The received value is: " << temp_celsius <<std::endl;
         temp_fahrenheit = temp_celsius * 9.0 / 5.0 + 32.0;
         std::string messg{std::to_string(temp_fahrenheit)};
         auto rc = publish(nullptr, MQTT_TOPIC_FAHRENHEIT_A.c_str(),
                           messg.size(), messg.c_str(), MQTT_QoS_0);
         if (rc != MOSQ_ERR_SUCCESS) {
            on_log(1, mosquitto_strerror(rc));
         }
      } catch (std::invalid_argument &e) {
         on_log(1, "Invalid argument in message for temperature");
      }
   }
}

void TemperatureConverter::on_subscribe(int mid, int qos_count,
                                        const int *granted_qos)
{
   CERR << "subscription succeeded, mid = " << mid
        << " qos_count = " << qos_count
        << " granted_qos = " << *granted_qos << std::endl;
}

void TemperatureConverter::on_log(int level, const char *str)
{
   CERR << " level = " << level << ": " << str << std::endl;
}

void TemperatureConverter::on_error()
{
   CERR << " ERROR " << std::endl;
}
