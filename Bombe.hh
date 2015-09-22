//
// Bombe.hh for bomberman in /home/dacost_c/bomberman
// 
// Made by chris dacostaesilva
// Login   <dacost_c@epitech.net>
// 
// Started on  Tue Apr 30 16:12:05 2013 chris dacostaesilva
// Last update Sun Jun  9 17:36:51 2013 bigott-a
//


#ifndef __BOMBE_HH__
#define __BOMBE_HH__

class Player;
class Map;
class Bombe;

#include "AObject.hpp"
#include "Player.hpp"
#include "Map.hh"
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include "./lib/libgdl_gl-2012.4/include/GameClock.hpp"
#include <unistd.h>

class Bombe : public AObject
{
public:
  Bombe(Player *gamer, gdl::GameClock const &gameClock);
  virtual ~Bombe();
  void		explode();
  void		initialize();
  int		update(gdl::GameClock const &gameClock, gdl::Input &input, std::list<AObject*> &list);
  void		draw();
  Genre		getTypeObject() const;
  float		getPosX() const;
  float		getPosY() const;
  float		getPosZ() const;
  void		play_anim(const std::string &text);
  bool		isAnimate() { return (false); }
private:
  gdl::GameClock const &B_Clock;
  Player			*proprio;
  unsigned int			power;
  size_t			xPos;
  size_t			yPos;
  int				time;
  gdl::Model			model_;
};

#endif
