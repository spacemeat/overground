import sys

if len(sys.argv) < 2:
  pluginName = "example"
else:
  pluginName = sys.argv[1]

macroName = pluginName.upper()
className = "".join([pluginName[0].capitalize(), pluginName[1:]])

src = f'''\
#ifndef ASSETS_{macroName}_H
#define ASSETS_{macroName}_H

#include "asset.h"

namespace overground
{{
  class {className} : public Asset
  {{
  public:
    {className}(asset::asset_t const & desc);
    virtual ~{className}();

  protected:
    virtual void loadAssetInfo_impl(path_t file, bool loadFromSrc) override;

    virtual void compileToAss_impl() override;
    virtual void compileToBuffer_impl(std::byte * buffer) override;
  }};
}}

#endif // #ifndef ASSETS_{macroName}_H
'''

print (src)
