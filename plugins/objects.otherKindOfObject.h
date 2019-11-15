#ifndef OBJECTS_OTHERKINDOFOBJECT_H
#define OBJECTS_OTHERKINDOFOBJECT_H

#include "object.h"

namespace overground
{
  class Otherkindofobject : public Object
  {
  public:
    Otherkindofobject(tableaux::object_t const & desc);
    virtual ~Otherkindofobject();

  protected:
  };
}

#endif // #ifndef OBJECTS_OTHERKINDOFOBJECT_H

