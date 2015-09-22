//
// ABlock.hh for Bomberman in /home/couillere/cpp/bomberman
// 
// Made by arthur rucquois
// Login   <rucquo_a@epitech.net>
// 
// Started on  Thu May  2 11:21:31 2013 arthur rucquois
// Last update Wed Jun  5 17:25:04 2013 bigott-a
//

#ifndef __ABLOCK_HH__
#define __ABLOCK_HH__

#include "include.h"

enum	Type
  {
    FLOOR = 0,
    FRAGILE = 1,
    WALL = 2,
    BOMB = 3,
    FIRE = 4,
    EXPLODING = 5,
    SPEED = 6,
    RANGE = 7,
    TOTAL = 8,
    PLAN
  };

class	ABlock
{
private:
  Type	type;

public:
  Type		getType() const;
  void		setType(const Type);

public:
  ABlock();
  ~ABlock();
};

#endif
