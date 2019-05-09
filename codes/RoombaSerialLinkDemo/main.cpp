#include <chrono>
#include <thread>
#include <vector>

#include "OpenInterfaceConfig.h"
#include "SerialLink.h"

using namespace std::chrono_literals;

const bool FOREVER{true};

int main()
{
   SerialLink sl{"/dev/ttyUSB0",
                 static_cast<unsigned int>(Baud::ROOMBA_DEFAULT)};

   sl.write(startSafe());

   while (FOREVER) {
      sl.write(driveDirect(200, 200));
      std::this_thread::sleep_for(3s);

      sl.write(driveDirect(0, -300));
      std::this_thread::sleep_for(3s);

      sl.write(driveDirect(-300, -300));
      std::this_thread::sleep_for(3s);
      
      sl.write(driveDirect(200, 0));
      std::this_thread::sleep_for(3s);
   }

   return 0;
}
