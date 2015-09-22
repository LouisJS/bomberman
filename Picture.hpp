//
// Picture.hpp for Picture in /home/lecocq_l/Documents/projets/3-Semestre/bomberman
// 
// Made by louis lecocq
// Login   <lecocq_l@epitech.net>
// 
// Started on  Mon May 13 11:31:10 2013 louis lecocq
// Last update Sun Jun  9 17:35:11 2013 bigott-a
//

#ifndef	__PICTURE_HPP__
# define	__PICTURE_HPP__

#include "InterfaceGraphique.hh"
#include "AObject.hpp"
#include <iostream>

class			Picture : public AObject
{
public:

  Picture();
  Picture(float, float, float, float, int, Action set);
  ~Picture();
  void			initialize();
  int			update(gdl::GameClock const &, gdl::Input &, std::list<AObject*> &);
  void			draw();
  Genre			getTypeObject() const { return (PICTURE); }
  float			getPosX() const { return (this->position_.x); }
  float			getPosY() const { return (this->position_.y); }
  float			getPosZ() const { return (this->position_.z); }
  void			play_anim(const std::string &) {};
  void			setIG(InterfaceGraphique *);
  int			check_zone(gdl::Input &);

private:
  int			type_;
  float			size_x;
  float			size_y;
  bool			clic;
  Action		set_;
  gdl::Image		picture_;
  InterfaceGraphique	*IG;
};

#endif /* PICTURE_HPP */
