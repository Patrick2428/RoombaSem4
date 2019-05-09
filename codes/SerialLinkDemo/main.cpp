#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

#include "SerialLink.h"

void printChr(SerialLink *sl, unsigned char c)
{
   std::vector<uint8_t> dt{{c, '-', 'h', 'e', 'l', 'l', 'o', '!'}};

   for (int i = 0; i < 10; i++) {
      sl->write(dt);
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
   }
}

void readChr(SerialLink *sl)
{
   std::vector<uint8_t> dt{};

   for (int i = 0; i < 10; i++) {
      dt = sl->read(7);
      for (const auto &e : dt) {
         std::cerr << e;
      }
      std::cerr << '\n';
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
   }
}

void doIt(SerialLink *sl)
{
   std::vector<uint8_t> dt{{'g', 'h', 'f', 'l', 'p', 'o', '!'}};
   std::vector<uint8_t> ot{};

   for (int i = 0; i < 15; i++) {
      ot = sl->writeRead(dt, dt.size());
      for (const auto &e : ot) {
         std::cerr << e;
      }
      std::cerr << '\n';
      std::this_thread::sleep_for(std::chrono::milliseconds(50));
   }
}

int main()
{
   SerialLink sl{"/dev/ttyUSB0", 9600};
   /*std::vector<uint8_t> dat{{'a', 'd', 'x'}};
   for (int i = 0; i < 5; i++) {
       sl.write(dat);
       std::this_thread::sleep_for(std::chrono::seconds(1));
   }
   std::vector<uint8_t> rd{};
   sl.read(rd, 10);
   for (const auto& e: rd) {
       std::cerr << e << '\n';
   }*/

   std::thread t1{&printChr, &sl, 'd'};
   std::thread t2{&readChr, &sl};
   std::thread t3{&doIt, &sl};

   t1.join();
   t2.join();
   t3.join();

   return 0;
}
