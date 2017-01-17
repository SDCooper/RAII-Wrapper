#include "Car.h"
#include "ErrLog.h"

#include <iostream>

Car::Car()
{
  Reset();
}
  
Car::~Car()
{
  Reset();
}

void Car::Reset()
{
  Initialised = false;
  
  NumWheels = 0;
  Wheels = 0;
  TheEngine = 0;
}
  
bool Car::Create(int numWheels, EngineFuelType fuel, double engineSizeLitres)
{
  std::cout << "Car::Create called." << std::endl;
  if(!Initialised)
  {
    NumWheels = numWheels;
    Wheels = new Wheel[NumWheels];
    if(Wheels == 0)
    {
      ErrLog("Failed to allocate for Wheels");
    }
    
    TheEngine = new Engine;
    if(TheEngine == 0)
    {
      ErrLog("Failed to allocate for Wheels");
    }
    TheEngine->FuelType = fuel;
    TheEngine->SizeLitres = engineSizeLitres;
    
    Initialised = true;
  }
  else
  {
    ErrLog("Already initialised!");
  }
  
  return Initialised;
}
  
bool Car::Destroy()
{
  std::cout << "Car::Destroy called." << std::endl;
  if(!Initialised)
  {
    Initialised = false;
    
    delete TheEngine;
    delete[] Wheels;
  }
  
  Reset();
  return Initialised;
}

void Car::Drive()
{
  std::cout << "Driving with my " << NumWheels << " wheeled, " << ((TheEngine->FuelType == PETROL) ? "Petrol" : "Diesel") << " " << TheEngine->SizeLitres << "L car!" << std::endl;
}
