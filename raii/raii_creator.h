#ifndef RAII_CREATOR
#define RAII_CREATOR

#include <utility>

#define CREATOR(func) Creator_##func

#define DECLARE_CREATOR(func) \
template<class T> \
class CREATOR(func) \
{ \
public: \
  template<class...Args> \
  static bool Create(T& t, Args&&... args) \
  { \
    return t.func(std::forward<Args>(args)...); \
  } \
  \
}

DECLARE_CREATOR(Create);
DECLARE_CREATOR(OpenStream);

#endif
