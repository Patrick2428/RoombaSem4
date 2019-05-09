// RAII: Resource Acquisition Is Initialization.
// Dynamic memory allocation by new uses the HEAP.

#include <iostream>
#include <memory>

class RawPointers
{
public:
   RawPointers()
      : pInt_{new int}
      , pDouble_{new double}
   {
      *pInt_ = 100;
      *pDouble_ = 123.123;
   }
   ~RawPointers()
   {
      delete pInt_;
      delete pDouble_;
      std::cerr << "DTOR " << __func__ << " explicit deleted allocated memory"
                << std::endl;
   }

private:
   // raw pointers, naked pointers
   int *pInt_;
   double *pDouble_;
};

class SmartPointers
{
public:
   SmartPointers()
      : pInt_{std::unique_ptr<int>{}}
      , pDouble_{std::unique_ptr<double>{}}
   {
   }
   ~SmartPointers()
   {
      // No need to deallocate, dtor of unique_ptr will do this.
      std::cerr << "DTOR " << __func__ << " implicit deleted allocated memory"
                << std::endl;
   }

private:
   std::unique_ptr<int> pInt_;
   std::unique_ptr<double> pDouble_;
};

int main()
{
   RawPointers rp;
   SmartPointers sp;

   {
      std::unique_ptr<RawPointers> pRP1{new RawPointers};
      // Unique pointers are moveable.
      // std::unique_ptr<RawPointers> pRP2{pRP1};  ==> compiler error
      std::unique_ptr<RawPointers> pRP2{move(pRP1)};

      std::cerr << pRP1.get() << std::endl;
      std::cerr << pRP2.get() << std::endl;
   }

   return 0;
}
