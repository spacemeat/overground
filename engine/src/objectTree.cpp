#include "objectTree.h"
#include "object.h"

using namespace std;
using namespace overground;


ObjectTree::ObjectTree(std::vector<tableau::tableau_t> const & tableaux)
{
  for (auto & tab : tableaux)
  {
    for (auto const & obj : tab.objects)
    {
      auto objC = makeObject(obj);
      objects_.push_back(objC);

      Object * objP = objC.get();
      
      for (auto & fea : obj.features)
      {
        auto feaC = make_unique<Feature>(fea);
        features_.push_back(feaC);

        Feature * feaP = feaC.get();


        for (auto & ren : )
      }
    }
  }
}
