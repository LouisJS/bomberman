//
// Map.cpp for Bomberman in /home/couillere/cpp/bomberman
// 
// Made by arthur rucquois
// Login   <rucquo_a@epitech.net>
// 
// Started on  Tue Apr 30 15:34:10 2013 arthur rucquois
// Last update Fri Jul 19 14:58:44 2013 bigott-a
//

#include <unistd.h>
#include "Map.hh"

size_t					Map::getXLen() const
{
  return (this->xLen);
}

size_t					Map::getYLen() const
{
  return (this->yLen);
}

void						Map::createBlocks()
{
  std::vector<ABlock *>				memHeeder;
  size_t					blocks = 0;

  if (this->xLen < 3 || this->yLen < 3)
    {
      throw Error("Map dimensions too low.");
    }
  while (this->blocks.size() < this->yLen)
    {
      this->blocks.push_back(memHeeder);
      while (this->blocks.back().size() < this->xLen)
	this->blocks.back().push_back(new ABlock);
      blocks++;
    }
}
bool                  Map::getCheck() const
 {
 return (this->check);
 }

void						Map::setBlocks()
{
  // Creation auto de la map
  size_t					i = 0;
  size_t					j;
  size_t					x = this->blocks[0].size();
  size_t					y = this->blocks.size();

  while (i < y)
    {
      j = 0;
      while (j < x)
	{
	  if (((i % 3) + (j % 3)) <= 1 || ((i % 3) + (j % 3)) == 4)
	    this->blocks[i][j]->setType(FLOOR);
	  else
	    this->blocks[i][j]->setType(FRAGILE);
	  if (i > 0 && i + 1 != y &&
	      j > 0 && j + 1 < x &&
	      ((j % 4 == 3 && i % 4 == 3) || (j % 4 == 1 && i % 4 == 1)))
	    this->blocks[i][j]->setType(WALL);
	  j++;
	}
      i++;
    }
  this->blocks[y - 1][x - 1]->setType(FLOOR);
  this->blocks[y - 2][x - 1]->setType(FLOOR);
  this->blocks[y - 1][x - 2]->setType(FLOOR);
  this->blocks[y - 1][0]->setType(FLOOR);
  this->blocks[y - 1][1]->setType(FLOOR);
  this->blocks[y - 2][0]->setType(FLOOR);
  this->blocks[0][x - 1]->setType(FLOOR);
  this->blocks[1][x - 1]->setType(FLOOR);
  this->blocks[0][x - 2]->setType(FLOOR);
  this->blocks[0][0]->setType(FLOOR);
  this->blocks[0][1]->setType(FLOOR);
  this->blocks[1][0]->setType(FLOOR);
}

const std::vector<std::vector<ABlock *> >	Map::getBlocks()
{
  return (this->blocks);
}

void						Map::clearBlocks()
{
  std::vector<std::vector<ABlock *> >::iterator	it1 = this->blocks.begin();
  std::vector<ABlock *>::iterator		it;
  size_t					i = 0;

  std::cout << "Clearing map..." << std::endl;
  while (it1 != this->blocks.end())
    {
      it = (*it1).begin();
      while (it != (*it1).end())
	{
	  delete (*it);
	  it++;
	}
      (*it1).clear();
      i++;
      std::cout << (i * 100) / this->yLen << " %" << std::endl;
      it1++;
    }
  this->blocks.clear();
  std::cout << "Map cleared..." << std::endl;
}

void						Map::setIG(InterfaceGraphique *ig)
{
  this->IG = ig;
}

void						Map::setBlock(const size_t x, const size_t y, const Type t)
{
  this->blocks[x][y]->setType(t);
}

size_t						Map::validSlots() const
{
  size_t					x = 0;
  size_t					y = 0;
  size_t					count = 0;

  while (y < this->blocks.size())
    {
      x = 0;
      while (x < this->blocks[0].size())
	{
	  if (this->blocks[y][x]->getType() == FLOOR &&
	      (((y > 0 && this->blocks[y - 1][x]->getType() == FLOOR) ||
		(y < this->blocks.size() - 1 && this->blocks[y + 1][x]->getType() == FLOOR)) &&
	       ((x > 0 && this->blocks[y][x - 1]->getType() == FLOOR) ||
		(x < this->blocks[0].size() - 1 && this->blocks[y][x + 1]->getType() == FLOOR))))
	    count++;
	  x++;
	}
      y++;
    }
  return (count);
}

void                                            Map::spawnPlayers(std::list<AObject *> *list)
{
  std::list<AObject *>::iterator                it = list->begin();
  std::list<AObject *>::iterator                r;
  size_t                                        i = 0;
  size_t                                        x = 0;
  size_t                                        y = 0;
  size_t                                        xs;
  size_t                                        ys;
  size_t                                        c = 0;

  while (it != list->end())
    {
      switch (i)
        {
        case (0):
          {
            (*it)->setPosX(0);
            (*it)->setPosZ(0);
            break;
          }
        case (1):
          {
            (*it)->setPosX((this->blocks.size() - 1) * 200.0);
            (*it)->setPosZ(0);
            break;
          }
        case (2):
          {
            (*it)->setPosX(0);
            (*it)->setPosZ((this->blocks[0].size() - 1) * -200.0);
            break;
          }
        case (3):
          {
            (*it)->setPosZ((this->blocks[0].size() - 1) * -200.0);
	    (*it)->setPosX((this->blocks.size() - 1) * 200.0);
            break;
          }
        default:
          {
            r = list->begin();
            while (r != it)
              {
		x += (*r)->getPosZ() / -200.0;
                y += (*r)->getPosX() / 200.0;
                r++;
		c++;
              }
	    xs = (this->blocks.size() / 2) * ((rand() % this->blocks.size())) / (y / c);
	    ys = (this->blocks.size() / 2) * ((rand() % this->blocks[0].size())) / (x / c);
	    if (xs >= this->blocks.size())
	      xs = this->blocks.size() / 2;
	    if (ys >= this->blocks[0].size())
	      ys = this->blocks.size() / 2;
            (*it)->setPosZ(xs * -200.0);
            (*it)->setPosX(ys * 200.0);
	    this->spawnRoom(xs, ys);
	    break;
          }
        }
      i++;
      it++;
    }
  r = list->begin();
  while (r != list->end())
    {
      (*r)->initialize();
      r++;
    }
}

void						Map::spawnRoom(const size_t x, const size_t y)
{
  if (x < this->blocks[0].size() && y < this->blocks.size())
    {
      this->blocks[y][x]->setType(FLOOR);
      if (x > 0)
	this->blocks[y][x - 1]->setType(FLOOR);
      if (y > 0)
	this->blocks[y - 1][x]->setType(FLOOR);
      if (x + 1 < this->blocks[0].size())
	this->blocks[y][x + 1]->setType(FLOOR);
      if (y + 1 < this->blocks.size())
	this->blocks[y + 1][x]->setType(FLOOR);
    }
}

void						Map::bonusPop(const size_t x, const size_t y)
{
  int	pop;
  int	b;

  pop = rand() % 10;
  b = rand() % 3;
  if (pop > 5)
    {
      if (b == 0)
      	this->blocks[y][x]->setType(SPEED);
      else if (b == 1)
      	this->blocks[y][x]->setType(RANGE);
      else
      	this->blocks[y][x]->setType(TOTAL);
    }
}

void						Map::addBomb(const size_t x, const size_t y)
{
  this->blocks[y][x]->setType(BOMB);
}

void						Map::explosion(const unsigned int power, const size_t x, const size_t y)
{
  this->blocks[y][x]->setType(FLOOR);
  this->explosionUp(power, x, y);
  this->explosionDown(power, x, y);
  this->explosionLeft(power, x, y);
  this->explosionRight(power, x, y);
  usleep(500000);
  this->cleanLeft(power, x, y);
  this->cleanRight(power, x, y);
  this->cleanUp(power, x, y);
  this->cleanDown(power, x, y);
}

void						Map::explosionLeft(const unsigned int power, const size_t x, const size_t y)
{
  unsigned int					i = 0;
  size_t					tx = x;
  size_t					ty = y;

  this->blocks[y][x]->setType(FLOOR);
  while (i <= power)
    {
      if (this->blocks[ty][tx]->getType() != FLOOR)
	{
	  if (this->blocks[ty][tx]->getType() == FRAGILE)
	    {
	      this->IG->erase_object_(tx, ty);
	      this->blocks[ty][tx]->setType(FLOOR);
	      this->bonusPop(tx, ty);
	    }
	  else if (this->blocks[ty][tx]->getType() == BOMB)
	    this->blocks[ty][tx]->setType(EXPLODING);
	  return;
	}
      this->blocks[ty][tx]->setType(FIRE);
      i++;
      if (tx == 0)
	return;
      tx--;
    }
}

void						Map::explosionRight(const unsigned int power, const size_t x, const size_t y)
{
  unsigned int					i = 0;
  size_t					tx = x;
  size_t					ty = y;

  this->blocks[y][x]->setType(FLOOR);
  while (i <= power && tx < this->xLen)
    {
      if (this->blocks[ty][tx]->getType() != FLOOR)
	{	
	  if (this->blocks[ty][tx]->getType() == FRAGILE)
	    {
	      this->IG->erase_object_(tx, ty);
	      this->blocks[ty][tx]->setType(FLOOR);
	      this->bonusPop(tx, ty);
	    }
	  else if (this->blocks[ty][tx]->getType() == BOMB)
	    this->blocks[ty][tx]->setType(EXPLODING);
	  return;
	}
      this->blocks[ty][tx]->setType(FIRE);
      i++;
      tx++;
    }
}

void						Map::explosionUp(const unsigned int power, const size_t x, const size_t y)
{
  unsigned int					i = 0;
  size_t					tx = x;
  size_t					ty = y;

  this->blocks[y][x]->setType(FLOOR);
  while (i <= power && ty < this->yLen)
    { 
      if (this->blocks[ty][tx]->getType() != FLOOR)
	{
	  if (this->blocks[ty][tx]->getType() == FRAGILE)
	    {
	      this->IG->erase_object_(tx, ty);
	      this->blocks[ty][tx]->setType(FLOOR);
	      this->bonusPop(tx, ty);
	    }
	  else if (this->blocks[ty][tx]->getType() == BOMB)
	    this->blocks[ty][tx]->setType(EXPLODING);
	  return;
	}
      this->blocks[ty][tx]->setType(FIRE);
      i++;
      ty++;
    }
}

void						Map::explosionDown(const unsigned int power, const size_t x, const size_t y)
{
  unsigned int					i = 0;
  size_t					tx = x;
  size_t					ty = y;

  this->blocks[y][x]->setType(FLOOR);
  while (i <= power)
    {
      if (this->blocks[ty][tx]->getType() != FLOOR)
	{
	  if (this->blocks[ty][tx]->getType() == FRAGILE)
	    {
	      this->IG->erase_object_(tx, ty);
	      this->blocks[ty][tx]->setType(FLOOR);
	      this->bonusPop(tx, ty);
	    }
	  else if (this->blocks[ty][tx]->getType() == BOMB)
	    this->blocks[ty][tx]->setType(EXPLODING);
	  return;
	}
      this->blocks[ty][tx]->setType(FIRE);
      i++;
      if (ty == 0)
	return;
      ty--;
    }
}

void						Map::cleanLeft(const unsigned int power, const size_t x, const size_t y)
{
  unsigned int					i = 0;
  size_t					tx = x;
  size_t					ty = y;

  i = 0;
  while (i <= power)
    {
      if (this->blocks[ty][tx]->getType() == FIRE || this->blocks[ty][tx]->getType() == EXPLODING)
	this->blocks[ty][tx]->setType(FLOOR);
      i++;
      if (tx == 0)
	return;
      tx--;
    }
}

void						Map::cleanRight(const unsigned int power, const size_t x, const size_t y)
{
  unsigned int					i = 0;
  size_t					tx = x;
  size_t					ty = y;

  while (i <= power && tx < this->xLen)
    {
      if (this->blocks[ty][tx]->getType() == FIRE || this->blocks[ty][tx]->getType() == EXPLODING)
	this->blocks[ty][tx]->setType(FLOOR);
      i++;
      tx++;
    }
}

void						Map::cleanUp(const unsigned int power, const size_t x, const size_t y)
{
  unsigned int					i = 0;
  size_t					tx = x;
  size_t					ty = y;

  while (i <= power && ty < this->yLen)
    {
      if (this->blocks[ty][tx]->getType() == FIRE || this->blocks[ty][tx]->getType() == EXPLODING)
	this->blocks[ty][tx]->setType(FLOOR);
      i++;
      ty++;
    }
}

void						Map::cleanDown(const unsigned int power, const size_t x, const size_t y)
{
  unsigned int					i = 0;
  size_t					tx = x;
  size_t					ty = y;

  while (i <= power)
    {
      if (this->blocks[ty][tx]->getType() == FIRE || this->blocks[ty][tx]->getType() == EXPLODING)
	this->blocks[ty][tx]->setType(FLOOR);
      i++;
      if (ty == 0)
	return;
      ty--;
    }
}

Map::Map(const size_t x, const size_t y)
{
  srand(time(NULL));
  this->xLen = x;
  this->yLen = y;
}

Map::~Map()
{
  sleep(2);
  this->clearBlocks();
}
