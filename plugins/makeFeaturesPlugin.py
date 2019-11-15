import sys

if len(sys.argv) < 2:
  pluginName = "example"
else:
  pluginName = sys.argv[1]

macroName = pluginName.upper()
className = "".join([pluginName[0].capitalize(), pluginName[1:]])

src = f'''\
#ifndef FEATURES_{macroName}_H
#define FEATURES_{macroName}_H

#include "feature.h"

namespace overground
{{
  class {className} : public Feature
  {{
  public:
    {className}(tableaux::feature_t const & desc);
    virtual ~{className}();
  }};
}}

#endif // #ifndef FEATURES_{macroName}_H
'''

print (src)
