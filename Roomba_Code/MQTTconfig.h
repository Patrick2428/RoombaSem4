#ifndef MQTTCONFIG_H
#define MQTTCONFIG_H

#include <string>

const char *getHostname();
const std::string HOSTNAME{getHostname()};

/// MQTT uses a TCP/IP connection. If no data flows over an open connection
/// for a certain time period the client will generate a PINGREQ and expect
/// to receive a PINGRESP from the broker. The keep alive period is in
/// seconds.
///
/// A typical value might be 60 (seconds). This means that the MQTT client
/// is expected to send an MQTT packet at least once every #MQTT_KEEP_ALIVE
/// seconds.
const int MQTT_KEEP_ALIVE{60};
/// At most once, fire and forget.
const int MQTT_QoS_0{0};
/// At least once.
const int MQTT_QoS_1{1};
/// Exactly once.
const int MQTT_QoS_2{2};
/// Resets retain flag.
const bool MQTT_RETAIN_OFF{false};
/// Sets retain flag, newly connected subscribers should receive messages
/// immediately and shouldn't wait until a publishing client sends the next
/// message.
const bool MQTT_RETAIN_ON{true};

const std::string MQTT_LOCAL_BROKER{"broker.hivemq.com"};
const int MQTT_LOCAL_BROKER_PORT{1883};

const std::string GROUP{"TeamFyre"};
/// @note Every topic must start with MQTT_TOPIC_ROOT.
const std::string MQTT_TOPIC_ROOT{"ESEiot/" + GROUP + "/" + HOSTNAME};

#endif
