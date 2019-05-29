#ifndef MQTTDATAHANDLER_H
#define MQTTDATAHANDLER_H

#include <mosquittopp.h>
#include <string>

//MQTTDataHandler is a MQTT client class derived from mosquittopp

class MQTTDataHandler : public mosqpp::mosquittopp
{
public:
  MQTTDataHandler(const std::string &data,
		  const std::string &appname,
		  const std::string &clientname,
		  const std::string &host, int port);

  virtual ~MQTTDataHandler();
  std::string getData() const;
  void resetData();

protected:

  virtual void on_connect(int rc) override;
  virtual void on_disconnect(int rc) override;
  virtual void on_message(const struct mosquitto_message *message) override;
  virtual void on_subscribe(int mid, int qos_count,
                             const int *granted_qos) override;
  virtual void on_log(int level, const char *str) override;
  virtual void on_error() override;

 private:
   std::string receivedData;
   

};

#endif
