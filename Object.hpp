//
// Object.hpp for Object in /home/lecocq_l/Documents/projets/3-Semestre/bomberman
// 
// Made by louis lecocq
// Login   <lecocq_l@epitech.net>
// 
// Started on  Tue May 14 11:54:54 2013 louis lecocq
// Last update Sun Jun  9 17:34:40 2013 bigott-a
//

#ifndef	__OBJECT_HPP__
#define	__OBJECT_HPP__

#include "AObject.hpp"

namespace Model
{
  class Object : public AObject
  {
  public:
  
    Object(const std::string,
	   float xt, float yt, float zt,
	   float rt, float yr, float zr, Genre type);
    Object(const std::string ,
	   float xt, float yt, float zt,
	   float xr, float yr, float zr, Genre type, float scale_);
    ~Object(void);
    void	initialize(void);
    int		update(gdl::GameClock const &, gdl::Input &, std::list<AObject*> &);
    void	draw(void);
    float	getPosX() const { return (this->position_.x); }
    float	getPosY() const { return (this->position_.y); }
    float	getPosZ() const { return (this->position_.z); }
    void	play_anim(const std::string &);
    Genre	getTypeObject() const;
    bool       	isAnimate() { return (this->model_.anim_is_ended("Default Take")); }
  private:
    gdl::Model model_;
    std::string	path_;
    Genre      	type_cube;
    float      	scale_;
  };
}


#endif
