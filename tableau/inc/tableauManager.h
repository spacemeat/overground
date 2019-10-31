#ifndef TABLEAUMANAGER_H
#define TABLEAUMANAGER_H

#include <string>
#include <unordered_map>
#include "tableau.h"

namespace overground
{
  class TableauManager
  {
  public:
    void installPlugin(std::string_view name, makeTableauFn_t plugin);

    inline std::unordered_map<std::string, makeTableauFn_t> const & plugins() const noexcept;

    inline std::vector<std::unique_ptr<Tableau>> tableaus() const noexcept;

  private:
    std::unordered_map<std::string, makeTableauFn_t> plugins_;
    std::vector<std::unique_ptr<Tableau>> tableaus_;
  };


  #pragma region inline impl

  inline std::unordered_map<std::string, makeTableauFn_t> const & TableauManager::plugins() const noexcept
  {
    return plugins_;
  }

  inline std::vector<std::unique_ptr<Tableau>> TableauManager::tableaus() const noexcept
  {
    return tableaus_;
  }

  #pragma endregion


  static inline std::optional<TableauManager> tableauMan;
}

#endif // TABLEAUMANAGER_H
