#include "RCar.h"
#include "RFileStream.h"

#include <iostream>

void non_raii()
{
  Car c;
  c.Create(4, PETROL, 1.2);
  c.Drive();
  c.Destroy();
  
  FileStream f;
  f.OpenStream("Test.txt", true);
  f.Write("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.");
  f.Close();
}

void raii()
{
  RCar c(4, DIESEL, 1.6);
  c.Drive();
  
  RFileStream f("Test.txt", true);
  f.Write("Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.");
}

int main()
{
  std::cout << "Non-RAII test: " << std::endl;
  non_raii();
  std::cout << "===============" << std::endl;
  
  std::cout << "RAII test: " << std::endl;
  raii();
  std::cout << "===============" << std::endl;
  
  return 0;
}
