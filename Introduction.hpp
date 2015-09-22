//
// Introduction.hpp for Introduction in /home/lecocq_l/bomberman-2016-rucquo_a
// 
// Made by louis lecocq
// Login   <lecocq_l@epitech.net>
// 
// Started on  Sat Jun  8 16:03:46 2013 louis lecocq
// Last update Sun Jun  9 17:37:28 2013 bigott-a
//

#ifndef	__INTRODUCTION_HPP__
#define	__INTRODUCTION_HPP__

#include "InterfaceGraphique.hh"
#include "AObject.hpp"
#include <iostream>

class			Introduction : public AObject
{
public:

  Introduction(float, float, float, float);
  ~Introduction();

  void			initialize();
  int			update(gdl::GameClock const &, gdl::Input &, std::list<AObject*> &);
  void			draw();
  Genre			getTypeObject() const { return (PICTURE); }
  float			getPosX() const { return (this->position_.x); }
  float			getPosY() const { return (this->position_.y); }
  float					getPosZ() const { return (this->position_.z); }
  void					play_anim(const std::string &) {};
  void					setIG(InterfaceGraphique *);

private:

  float					time_;
  bool					first_time;
  gdl::Image				picture_;
  float					size_x;
  float					size_y;
  InterfaceGraphique			*IG;
  std::list<std::string>		list;
  std::list<std::string>::iterator	itb;
};

#endif
