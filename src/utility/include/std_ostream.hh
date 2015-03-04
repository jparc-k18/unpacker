// -*- C++ -*-

// Author: Tomonori Takahashi

#ifndef HDDAQ__UNPACKER_STD_OSTREAM_H
#define HDDAQ__UNPACKER_STD_OSTREAM_H

#include <iostream>

namespace hddaq
{

  // if cerr or cout is used without namespace, it means that 
  // it belongs not to std but to namespace hddaq::unpacker
  std::ostream cerr(std::cerr.rdbuf());
  std::ostream cout(std::cout.rdbuf());
  std::ostream tag_summary(std::cout.rdbuf());
  
  void
  set_cerr(const std::string& name);

  void
  set_cout(const std::string& name);

  void
  set_tag_summary(const std::string& name);

}

#endif
