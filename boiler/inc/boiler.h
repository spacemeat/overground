#ifndef BOILER_H
#define BOILER_H


namespace overground
{
  constexpr auto defaultAssetsDefsPath = "./boiler/test-defs.hu";
  constexpr auto defaultAssetsOutputDir = "./boiler/test-assembly-output";
  constexpr auto defaultPluginsOutputDir = "./boiler/test-plugins-output";

  constexpr auto defaultEnumsHeaderPath = "../../balls/vulkan/1.1.77.0/x86_64/include/vulkan/vulkan.hpp";
  constexpr auto defaultEnumsOutputDir = "./boiler/test-output";


  int assetsMain(path_t const & defsPath, path_t const & outputPodsDir, path_t const & outputPluginsDir); 
  int enumsMain(path_t const & headerPath, path_t const & outputDir);
}


#endif // #ifndef BOILER_H
