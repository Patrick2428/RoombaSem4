// fccfMQTT: MQTT client, temperature value converter
// Fahrenheit to Celcius and Celcius to Fahrenheit converter

#include "AppInfo.h"
#include "Config.h"
#include "TemperatureConverter.h"

#include <csignal>
#include <iostream>
#include <string>

using namespace std;

volatile sig_atomic_t receivedSIGINT{false};

void handleSIGINT(int /* s */)
{
   receivedSIGINT = true;
}

int main(int argc, char *argv[])
{
   try {
      string mqttBroker{MQTT_LOCAL_BROKER};
      int mqttBrokerPort{MQTT_LOCAL_BROKER_PORT};
      /// @warning Processing of the command line arguments is not robust.
      /// No syntax checking implemented.
      switch (argc) {
         case 1:
            // Using MQTT_LOCAL_BROKER and MQTT_LOCAL_BROKER_PORT
            break;
         case 2:
            // Using MQTT_LOCAL_BROKER_PORT
            mqttBroker = string(argv[1]);
            break;
         case 3:
            mqttBroker = string(argv[1]);
            mqttBrokerPort = stoi(argv[2]);
            break;
         default:
            cerr << endl
                 << "ERROR command line arguments: "
                    "fccfMQTT <URL broker> <broker port>"
                 << endl;
            exit(EXIT_FAILURE);
      }

      int major{0};
      int minor{0};
      int revision{0};

      signal(SIGINT, handleSIGINT);

      cout << "-- MQTT application: " << APPNAME_VERSION << "  ";
      mosqpp::lib_init();
      mosqpp::lib_version(&major, &minor, &revision);
      cout << "uses Mosquitto lib version " << major << '.' << minor << '.'
           << revision << endl;

      TemperatureConverter tempconv("fccf", "tempconv", mqttBroker,
                                    mqttBrokerPort);
      while (!receivedSIGINT) {
         int rc{tempconv.loop()};
         if (rc) {
            cerr << "-- MQTT reconnect rc = " << rc << " '"
                 << mosquitto_strerror(rc) << "'" << std::endl;
            tempconv.reconnect();
         }
      }
   } catch (invalid_argument &e) {
      cerr << "Exception invalid argument: " << e.what() << std::endl;
   } catch (exception &e) {
      cerr << "Exception: " << e.what() << std::endl;
   }
   /// @note catch(...): ... ellipsis, catches all unhandled unexpected
   /// exceptions.
   catch (...) {
      cerr << "UNKNOWN EXCEPTION \n";
   }

   cout << "-- MQTT application: " << APPNAME_VERSION << " stopped" << endl
        << endl;
   mosqpp::lib_cleanup();

   return 0;
}
