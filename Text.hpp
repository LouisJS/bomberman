//
// Text.hpp for Text in /home/lecocq_l/Documents/projets/3-Semestre/bomberman
// 
// Made by louis lecocq
// Login   <lecocq_l@epitech.net>
// 
// Started on  Fri May 10 15:05:17 2013 louis lecocq
// Last update Sun Jun  9 17:35:43 2013 bigott-a
//

#ifndef	__TEXT_HPP__
#define	__TEXT_HPP__

#include "InterfaceGraphique.hh"
#include "AObject.hpp"
#include <iostream>

class			Text : public AObject
{
public:

  Text();
  Text(unsigned int x, unsigned int y,
       std::string const &message, int size, Action set);
  ~Text();
  void			initialize();
  int			update(gdl::GameClock const &, gdl::Input &, std::list<AObject*> &);
  float			getPosX() const { return (this->position_.x); }
  float			getPosY() const { return (this->position_.y); }
  float			getPosZ() const { return (this->position_.z); }
  void			draw();
  Genre			getTypeObject() const { return (TEXT); }
  void			play_anim(const std::string &) {}
  void			setIG(InterfaceGraphique *);

private:
  gdl::Text		text_;
  Vector3f		position_;
  Vector3f		rotation_;
  unsigned int		x_;
  unsigned int		y_;
  InterfaceGraphique	*IG;
  Action		set_;
};


#endif
