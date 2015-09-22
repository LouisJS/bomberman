//
// ABlock.cpp for Bomberman in /home/couillere/cpp/bomberman
// 
// Made by arthur rucquois
// Login   <rucquo_a@epitech.net>
// 
// Started on  Thu May  2 11:21:27 2013 arthur rucquois
// Last update Wed Jun  5 16:27:22 2013 louis lecocq
//

#include "ABlock.hh"

Type	ABlock::getType() const
{
  return (this->type);
}

void		ABlock::setType(const Type t)
{
  this->type = t;
}

ABlock::ABlock()
{
  this->type = FLOOR;
}

ABlock::~ABlock()
{
}
