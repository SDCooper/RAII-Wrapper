#ifndef CAR_H
#define CAR_H


enum EngineFuelType
{
  PETROL = 0,
  DIESEL,
};

// Some example components for a car.
// In a real project these would be actual proper
// classes in their own files, possibly even interfaces
// for types of wheels and types of engine, etc. But that
// is outside the scope of an example "legacy" non-RAII
// library
struct Wheel {};
struct Engine { double SizeLitres; EngineFuelType FuelType; };

// Example legacy class which uses a Create and a Destroy method 
// and whose constructor and destructor do not do much.
class Car
{
public:

  Car();
  virtual ~Car();
  
  bool Create(int numWheels, EngineFuelType fuel, double engineSizeLitres);
  bool Destroy();
  
  void Drive();

private:
  bool Initialised;
  
  int NumWheels;
  Wheel *Wheels;
  
  Engine *TheEngine;
  
  void Reset();
  
};

#endif // CAR_H
