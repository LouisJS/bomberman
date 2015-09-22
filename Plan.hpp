//
// Bonus.hpp for bomberman in /home/bigott_a/Documents/Bomberman/Projet/bomberman-2016-rucquo_a
// 
// Made by bigott-a
// Login   <bigott_a@epitech.net>
// 
// Started on  Tue Jun  4 10:55:06 2013 bigott-a
// Last update Sun Jun  9 17:35:29 2013 bigott-a
//

#ifndef	__BONUS_HPP__
#define	__BONUS_HPP__

class	Plan;

#include "AObject.hpp"
#include "Map.hh"
#include "ABlock.hh"

class	Plan : public AObject
{
public:
  Plan(float xt, float yt, float zt, float xr, float yr, float zr);
  virtual ~Plan();
  void		initialize(void);
  int		update(gdl::GameClock const &, gdl::Input &, std::list<AObject*> &);
  void		draw(void);
  enum Genre	getTypeObject() const { return (PLANS); }
  void		play_anim(const std::string &) {}
  bool		isAnimate() { return (true); }
  float		getPosX() const { return (this->position_.x); }
  float		getPosY() const { return (this->position_.y); }
  float		getPosZ() const { return (this->position_.z); }

private:

  gdl::Image	picture;
};

#endif
