  ///// new
  enum class generalMembers_e : int
  { 
    none = 0,
    programName = 1 << 0,
    version = 1 << 1,
    numWorkerThreads = 1 << 2
  };
  struct generalDiffs_t
  {
    generalMembers_e diffs;
  };
  bool doPodsDiffer(general_t const & lhs, general_t const & rhs, generalDiffs_t & general)
  {
    if (lhs.programName != rhs.programName)
      { general.diffs |= generalMembers_e::programName; }
    if (lhs.version != rhs.version)
      { general.diffs |= generalMembers_e::version; }
    if (lhs.numWorkerThreads != rhs.numWorkerThreads)
      { general.diffs |= generalMembers_e::numWorkerThreads; }
    return general.diffs != generalMembers_e::none;
  }

  struct swapchainImageViewDiffs_t
  {
    swapchainImageView_e diffs;
    std::vector<size_t> componentDiffIdxs;
  };
  enum class swapchainImageView_e : int { none = 0, viewType = 1 << 0, components = 1 << 1, aspectMask = 1 << 2 };
  bool doPodsDiffer(swapchainImageView_t const & lhs, swapchainImageView_t const & rhs, swapchainImageViewDiffs_t & swapchainImageView)
  {
    if (lhs.viewType != rhs.viewType)
      { swapchainImageView.diffs |= swapchainImageView_e::viewType; }
    //if (lhs.components.size() != rhs.components.size())
    //  { swapchainImageView.diffs |= swapchainImageView_e::components; }
//    {
//      auto [mn, mx] = std::minmax(lhs.components.size(), rhs.components.size());
//      for (size_t i = 0; i < mn; ++i)
      for (size_t i = 0; i < lhs.components.size(); ++i)
      {
        if (lhs.components[i] != rhs.components[i])
        {
          swapchainImageView.diffs |= swapchainImageView_e::components;
          swapchainImageView.componentDiffIdxs.push_back(i);
        }
      }
      //for (size_t i = mn; i < mx; ++i)
      //{
      //  swapchainImageView.componentDiffIdxs.push_back(i);
      //}
//    }
    if (lhs.aspectMask != rhs.aspectMask)
      { swapchainImageView.diffs |= swapchainImageView_e::aspectMask; }
    return swapchainImageView.diffs != swapchainImageView_e::none;
  }

  struct formatPrioritiesDiffs_t
  {
    formatPriorities_e diffs;
  };
  enum class formatPriorities_e : int { none = 0, first = 1 << 0, second = 1 << 1 };
  bool doPodsDiffer(std::pair<vk::Format, vk::ColorSpaceKHR> const & lhs, std::pair<vk::Format, vk::ColorSpaceKHR> const & rhs, formatPrioritiesDiffs_t & formatPriorities)
  {
    if (lhs.first != rhs.first)
      { formatPriorities.diffs |= formatPriorities_e::first; }
    if (lhs.second != rhs.second)
      { formatPriorities.diffs |= formatPriorities_e::second; }
    return formatPriorities.diffs != formatPriorities_e::none;
  }


  struct swapchainDiffs_t
  {
    swapchain_e diffs;
    std::vector<std::pair<size_t, formatPrioritiesDiffs_t>> formatPrioritiesDiffs;
    swapchainImageViewDiffs_t swapchainImageView;
  };
  enum class swapchain_e : int { none = 0, formatPriorities = 1 << 0, imageView = 1 << 10 };
  bool doPodsDiffer(swapchain_t const & lhs, swapchain_t const & rhs, swapchainDiffs_t & swapchain)
  {
    if (lhs.formatPriorities.size() != rhs.formatPriorities.size())
      { swapchain.diffs |= swapchain_e::formatPriorities; }
    {
      auto [mn, mx] = std::minmax(lhs.formatPriorities.size(), rhs.formatPriorities.size());
      for (size_t i = 0; i < mn; ++i)
      {
        formatPrioritiesDiffs_t diffsEntry;
        if (doPodsDiffer(lhs.formatPriorities[i], rhs.formatPriorities[i], diffsEntry))
        {
          swapchain.diffs |= swapchain_e::formatPriorities;
          swapchain.formatPrioritiesDiffs.push_back({i, diffsEntry});
        }
      }
      for (size_t i = mn; i < mx; ++i)
      {
        formatPrioritiesDiffs_t diffsEntry = { .diffs = formatPriorities_e::first | formatPriorities_e::second };
        swapchain.formatPrioritiesDiffs.push_back({i, diffsEntry});
      }
    }
    if (doPodsDiffer(lhs.imageView, rhs.imageView, swapchain.swapchainImageView))
      { swapchain.diffs |= swapchain_e::imageView; }
    return swapchain.diffs != swapchain_e::none;
  }

  struct graphicsDiffs_t
  {
    graphics_e diffs;
    swapchainDiffs_t swapchain;
  };
  enum class graphics_e : int { none = 0, isConfigured = 1 << 0, headless = 1 << 1, swapchain = 1 << 10 };
  bool doPodsDiffer(graphics_t const & lhs, graphics_t const & rhs, graphicsDiffs_t & graphics)
  {
    if (lhs.isConfigured != rhs.isConfigured)
      { graphics.diffs != graphics_e::isConfigured; }
    if (lhs.headless != rhs.headless)
      { graphics.diffs != graphics_e::headless; }
    if (doPodsDiffer(lhs.swapchain, rhs.swapchain, graphics.swapchain))
      { graphics.diffs |= graphics_e::swapchain; }
    return graphics.diffs != graphics_e::none;
  }

  struct configDiffs_t
  {
    config_e diffs;
    generalDiffs_t general;
    graphicsDiffs_t graphics;
  };
  enum class config_e : int { none, general, graphics };
  bool doPodsDiffer(config_t const & lhs, config_t const & rhs, configDiffs_t & config)
  {
    if (doPodsDiffer(lhs.general, rhs.general, config.general))
      { config.diffs |= config_e::general; }
    if (doPodsDiffer(lhs.graphics, rhs.graphics, config.graphics))
      { config.diffs |= config_e::graphics; }
  }

  void foo()
  {
    config_t a, b;
    auto configDiffs = configDiffs_t { };
    if (doPodsDiffer(a, b, configDiffs))
    {
    }
  }
  /////
