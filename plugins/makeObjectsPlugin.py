import sys

if len(sys.argv) < 2:
  pluginName = "example"
else:
  pluginName = sys.argv[1]

macroName = pluginName.upper()
className = pluginName.capitalize()

src = f'''\
#ifndef OBJECTS_{macroName}_H
#define OBJECTS_{macroName}_H

#include "object.h"

namespace overground
{{
  class {className} : public Object
  {{
  public:
    {className}(tableaux::object_t const & desc);
    virtual ~{className}();

  protected:
  }};
}}

#endif // #ifndef OBJECTS_{macroName}_H
'''

print (src)
