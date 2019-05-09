#ifndef TEMPERATURE_CONVERTER_H
#define TEMPERATURE_CONVERTER_H

#include <mosquittopp.h>
#include <string>

/// The class TemperatureConverter is a MQTT client class, public derived
/// from mosqpp::mosquittopp.
class TemperatureConverter : public mosqpp::mosquittopp
{
public:
   TemperatureConverter(const std::string &appname,
                        const std::string &clientname,
                        const std::string &host, int port);
   virtual ~TemperatureConverter();

protected:
   const std::string className_;
   const std::string mqttID_;
   /// @note C++11: override (compiler check)
   virtual void on_connect(int rc) override;
   virtual void on_disconnect(int rc) override;
   virtual void
   on_message(const struct mosquitto_message *message) override;
   virtual void on_subscribe(int mid, int qos_count,
                             const int *granted_qos) override;
   virtual void on_log(int level, const char *str) override;
   virtual void on_error() override;
};

#endif
