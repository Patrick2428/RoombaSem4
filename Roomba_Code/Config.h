/** @file */
///\brief MQTT topic initialisation
#ifndef CONFIG_H
#define CONFIG_H

#include "MQTTconfig.h"

#include <string>

//MQTT publisher topic to controll the roomba
const std::string MQTT_TOPIC_ROOMBA_CONTROLLER{MQTT_TOPIC_ROOT + "/roomba/controller"}; ///receive mesage from this topic

const std::string MQTT_TOPIC_ROOMBA_INTERFACE{MQTT_TOPIC_ROOT + "/roomba/interface"}; ///send message to this topic

#endif
