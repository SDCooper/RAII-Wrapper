#ifndef RCAR_H
#define RCAR_H

#include "raii/raii.h"
#include "legacy/Car.h"

using RCar = Template_Wrapper<Car, CREATOR(Create), DESTROYER(Destroy)>;

#endif // RCAR_H
