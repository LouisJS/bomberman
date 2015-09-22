//
// Object.cpp for Object in /home/lecocq_l/Documents/projets/3-Semestre/bomberman
// 
// Made by louis lecocq
// Login   <lecocq_l@epitech.net>
// 
// Started on  Tue May 14 11:55:49 2013 louis lecocq
// Last update Sun Jun  9 17:34:50 2013 bigott-a
//

#include "Object.hpp"

namespace Model
{
  void Object::initialize(void)
  {
    ////////////////////////////////////////////////////////////////////////////////
    /// Charge le modele
    ////////////////////////////////////////////////////////////////////////////////
    this->model_ = gdl::Model::load(this->path_);
  }

  Object::Object(const std::string path, float xt, float yt, float zt, float xr, float yr, float zr, Genre type)
  {
    this->path_ = path;
    this->position_.x = xt;
    this->position_.y = yt;
    this->position_.z = zt;
    this->rotation_.x = xr;
    this->rotation_.y = yr;
    this->rotation_.z = zr;
    this->toDelete = false;
    this->type_cube = type;
    this->scale_ = 0;
  }

  Object::Object(const std::string path, float xt, float yt, float zt, float xr, float yr, float zr, Genre type, float scale_)
  {
    this->path_ = path;
    this->position_.x = xt;
    this->position_.y = yt;
    this->position_.z = zt;
    this->rotation_.x = xr;
    this->rotation_.y = yr;
    this->rotation_.z = zr;
    this->toDelete = false;
    this->type_cube = type;
    this->scale_ = scale_;
  }  

  Object::~Object(void)
  {
  }

  void	Object::play_anim(const std::string &animation)
  {
    if (this->type_cube == CUBE)
      {
	this->model_.set_anim_speed(animation, 5);
	this->model_.play(animation);
      }
  }

  int Object::update(gdl::GameClock const &gameClock, gdl::Input &input, std::list<AObject*> &list)
  {
    if (this->type_cube == CUBE)
      {
	this->model_.update(gameClock);
	this->model_.set_anim_speed("Default Take", 5);
      }
    ////////////////////////////////////////////////////////////////////////////////
    /// Joue l’animation portant le nom "Take 001" quand on appuie sur la touche "p"
    ////////////////////////////////////////////////////////////////////////////////
    
    (void)input;
    (void)list;
    return (0);
  }

  void Object::draw(void)
  {
    ////////////////////////////////////////////////////////////////////////////////
    /// Affichage du modele
    ////////////////////////////////////////////////////////////////////////////////
    glPushMatrix();
    glTranslatef(this->position_.x, this->position_.y, this->position_.z);
    if (this->type_cube == LAVE)
      glScalef(0.8, 0.8, 0.8);
    else if (this->type_cube == ENV)
      glScalef(this->scale_, this->scale_, this->scale_);
    glRotatef(this->rotation_.x, 1, 0, 0);
    glRotatef(this->rotation_.y, 0, 1, 0);
    glRotatef(this->rotation_.z, 0, 0, 1);
    this->model_.draw();
    glPopMatrix();
  }

  Genre	Object::getTypeObject() const
  {
    return (this->type_cube);
  }
}
