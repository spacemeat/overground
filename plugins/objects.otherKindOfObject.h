#ifndef OBJECTS_OTHERKINDOFOBJECT_H
#define OBJECTS_OTHERKINDOFOBJECT_H

#include "object.h"

namespace overground
{
  class OtherKindOfObject : public Object
  {
  public:
    OtherKindOfObject(tableau::object_t const & desc);
    virtual ~OtherKindOfObject();

  protected:
  };
}

#endif // #ifndef OBJECTS_OTHERKINDOFOBJECT_H

