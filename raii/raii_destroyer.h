#ifndef RAII_DESTROYER_H
#define RAII_DESTROYER_H

#define DESTROYER(func) Destroyer_##func

#define DECLARE_DESTROYER(func) \
template<class T> \
class DESTROYER(func) \
{ \
public: \
  static bool Destroy(T& t) \
  { \
    return t.func(); \
  } \
}

DECLARE_DESTROYER(Close);
DECLARE_DESTROYER(Destroy);

#endif
