#ifndef CONFIG_H
#define CONFIG_H

#include "MQTTconfig.h"

#include <string>

const std::string MQTT_TOPIC_CELSIUS_Q{MQTT_TOPIC_ROOT + "/celsiusQ"};
/// Reply to MQTT_TOPIC_CELSIUS_Q (Question), in message converted
/// Celsius value to Fahrenheit (Answer).
const std::string MQTT_TOPIC_FAHRENHEIT_A{MQTT_TOPIC_ROOT +
                                          "/fahrenheitA"};
const std::string MQTT_TOPIC_FAHRENHEIT_Q{MQTT_TOPIC_ROOT +
                                          "/fahrenheitQ"};

/// Reply to MQTT_TOPIC_FAHRENHEIT_Q (question), in message converted
/// Fahrenheit value to Celsius (answer).
const std::string MQTT_TOPIC_CELSIUS_A{MQTT_TOPIC_ROOT + "/celsiusA"};

#endif
