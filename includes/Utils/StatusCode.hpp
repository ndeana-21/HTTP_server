#ifndef STATUSCODE_HPP
# define STATUSCODE_HPP

#include "Define.hpp"

class StatusCode {
 public:
  StatusCode();
  std::string &operator[](int status_code);

 private:
  std::map<int, std::string> error_codes_;
};

#endif