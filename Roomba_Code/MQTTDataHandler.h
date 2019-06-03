#ifndef MQTTDATAHANDLER_H
#define MQTTDATAHANDLER_H

#include <mosquittopp.h>
#include <string>

///MQTTDataHandler is a MQTT client class derived from mosquittopp
///Control for subscriptions and publishing to MQTT topics

class MQTTDataHandler : public mosqpp::mosquittopp
{
 public:
  ///Constructor to initialise MQTT parameters and data parameter
  MQTTDataHandler(const std::string &data,
		  const std::string &appname,
		  const std::string &clientname,
		  const std::string &host, int port);

  virtual ~MQTTDataHandler();
  std::string getData() const;
  ///Publish message to topic "ESEiot/TeamFyre/roomba/interface"
  void sendMessage(std::string ms);
  ///Resets received data from topic "ESEiot/TeamFyre/roomba/controller"
  void resetData();
  ///Sets the message send my sendMessage()
  void setMessage(std::string message);
  ///Appends the message send by sendMessage()
  void appendMessage(std::string message);
  std::string getMessage();

protected:

  ///virtual functions supplied by mosquittopp.h for handling MQTT connections
  virtual void on_connect(int rc) override;
  virtual void on_disconnect(int rc) override;
  virtual void on_message(const struct mosquitto_message *message) override;
  virtual void on_subscribe(int mid, int qos_count,
                             const int *granted_qos) override;
  virtual void on_log(int level, const char *str) override;
  virtual void on_error() override;

 private:
  ///Data received by subscription
   std::string receivedData;
   ///Data send via publish
   std::string message_;
   

};

#endif
