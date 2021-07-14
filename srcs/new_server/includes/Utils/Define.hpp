#ifndef DEFINE_HPP
# define DEFINE_HPP

# include <iostream>
# include <map>
# include <string>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <dirent.h>
# include <time.h>
# include <string.h>
# include <errno.h>
# include <algorithm>
# include <vector>
# include <stdlib.h>
# include <cstring>
# include <limits>
# include <sstream>

# include "MimeTypes.hpp"
# include "Logger.hpp"
# include "StringUtils.hpp"
# include "MimeTypes.hpp"

struct auto_listing {
  std::string name_;
  bool is_dir_;
  std::string date_;
  size_t size_;

  auto_listing() : is_dir_(false) {};
};


#endif