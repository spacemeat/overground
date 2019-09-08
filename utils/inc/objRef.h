#ifndef OBJREF_H
#define OBJREF_H

#include <string>

namespace overground
{
  template <class T>
  class ObjRef
  {
  public:
    ObjRef(std::string_view name, T * ref = nullptr)
    : name(name), ref(ref)
      { }

    void setName(std::string_view name)
    {
      this->name = name;
      ref = nullptr;
    }

    void setRef(T * ref)
      { this->ref = ref; }
    
    T & operator .()
      { return * ref; }
    
    T * operator ->()
      { return ref; }
    
  private:
    T * ref = nullptr;
    std::string name;
  };
}

#endif // #ifndef OBJREF_H
