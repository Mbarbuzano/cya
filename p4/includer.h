#ifndef INCLUDER_H
#define INCLUDER_H

#include "comment.h"

class Includer {
 public:
  Includer() {}
  Includer(bool system) : system_{system} {}

  bool system() const { return system_; }
  void set_system(const bool& modif) { system_ = modif; }

  std::string type() const {
    return system_ ? "STD" : "USER";
  }

 private:
  bool system_{false};
};

#endif