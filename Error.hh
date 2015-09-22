//
// Error.hh for  in /home/couillere/cpp/bomberman
// 
// Made by arthur rucquois
// Login   <rucquo_a@epitech.net>
// 
// Started on  Fri May 10 15:54:24 2013 arthur rucquois
// Last update Fri May 10 15:57:16 2013 arthur rucquois
//

#ifndef __ERROR_HH__
#define __ERROR_HH__

#include "include.h"

class	Error
{
private:
  std::string	msg;

public:
  void	show();

public:
  Error(const char *);
  ~Error();
};

#endif
