#ifndef RAII_TEMPLATE_H
#define RAII_TEMPLATE_H

#include <utility>

template<
  class T                 // non-RAII type to be wrapped
, template<class> class C // has static Create function
, template<class> class D // has static Destroy function
>
class Template_Wrapper
: public T
{
private:
  using Creator = C<T>;
  using Destroyer = D<T>;
  
  bool ValidSetup;
  
public:
  template<class... Args>
  Template_Wrapper(Args&&... args)
  {
    ValidSetup = Creator::Create(*this, std::forward<Args>(args)...);
  }
  
  virtual ~Template_Wrapper()
  {
    Destroyer::Destroy(*this);
  }
  
  // Implicit cast to bool to determine success of creation.
  // Note that this is merely a substitute for testing creation
  // success by return value .
  // The actual information for why the creation might have failed 
  // is logged to stderr in the actual legacy object's creation 
  // function.
  operator bool() const
  {
    return ValidSetup;
  }
  
  // Copy and move constructors & assignment operators
  // are not trusted in legacy classes that this class
  // is designed to wrap. In most cases they create
  // shallow copies and double deletes, and as such should
  // simply be disallowed.
  // (Rule of 5)
  Template_Wrapper(const Template_Wrapper&) = delete;
  Template_Wrapper& operator=(const Template_Wrapper&) = delete;
  Template_Wrapper(Template_Wrapper&&) = delete;
  Template_Wrapper& operator=(Template_Wrapper&&) = delete;
  
}; 

#endif
