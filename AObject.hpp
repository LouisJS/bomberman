//
// AObject.hh for test in /home/bigott_a/Documents/Bomberman/Projet/test_lib
// 
// Made by bigott-a
// Login   <bigott_a@epitech.net>
// 
// Started on  Tue Apr 30 14:38:09 2013 bigott-a
// Last update Sun Jun  9 17:36:07 2013 bigott-a
//

#ifndef __AOBJECT_HPP__
#define __AOBJECT_HPP__

#include "./lib/libgdl_gl-2012.4/include/Clock.hpp"
#include "./lib/libgdl_gl-2012.4/include/Color.hpp"
#include "./lib/libgdl_gl-2012.4/include/Game.hpp"
#include "./lib/libgdl_gl-2012.4/include/GameClock.hpp"
#include "./lib/libgdl_gl-2012.4/include/Image.hpp"
#include "./lib/libgdl_gl-2012.4/include/Input.hpp"
#include "./lib/libgdl_gl-2012.4/include/Model.hpp"
#include "./lib/libgdl_gl-2012.4/include/Window.hpp"
#include "./lib/libgdl_gl-2012.4/include/Text.hpp"

#include <GL/glu.h>
#include <GL/gl.h>
#include <iostream>
#include <string>

#include "Vector3f.hh"

enum	Action
  {
    MAP = 0,
    NB_IA,
    NONE
  };

enum	Genre
  {
    PLAYER = 0,
    IA,
    CUBE,
    BOMBE,
    LAVE,
    BONUS,
    TEXT,
    PICTURE,
    MENU,
    PLANS,
    ENV
  };

class	AObject
{
public:

  AObject(void) : position_(0.0f, 0.0f, 0.0f), rotation_(0.0f, 0.0f, 0.0f) {}
  virtual void		initialize(void) = 0;
  virtual int		update(gdl::GameClock const &, gdl::Input &, std::list<AObject*> &) = 0;
  virtual void		draw(void) = 0;
  virtual enum Genre	getTypeObject() const = 0;
  virtual float		getPosX() const = 0;
  virtual float		getPosY() const = 0;
  virtual float		getPosZ() const = 0;
  virtual void		setPosX(const float x) {this->position_.x = x;};
  virtual void		setPosZ(const float z) {this->position_.z = z;};
  virtual void		play_anim(const std::string &) = 0;
  void			deleteMe() { this->toDelete = true; }
  bool			getToDelete() { return (this->toDelete); }

protected:

  bool			toDelete;
  Vector3f		position_;
  Vector3f		rotation_;
};

#endif
