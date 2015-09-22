//
// Error.cpp for  in /home/couillere/cpp/bomberman
// 
// Made by arthur rucquois
// Login   <rucquo_a@epitech.net>
// 
// Started on  Fri May 10 15:52:33 2013 arthur rucquois
// Last update Fri May 10 15:59:42 2013 arthur rucquois
//

#include "Error.hh"

void	Error::show()
{
  std::cerr << this->msg << std::endl;
}

Error::Error(const char *str)
{
  this->msg = str;
}

Error::~Error()
{
}
