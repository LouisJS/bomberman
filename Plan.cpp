//
// Bonus.cpp for Bomberman in /home/bigott_a/Documents/Bomberman/Projet/bomberman-2016-rucquo_a
// 
// Made by bigott-a
// Login   <bigott_a@epitech.net>
// 
// Started on  Tue Jun  4 11:06:22 2013 bigott-a
// Last update Fri Jun  7 16:28:19 2013 bigott-a
//

#include "Plan.hpp"

Plan::Plan(float xt, float yt, float zt, float xr, float yr, float zr)
{
  this->position_.x = xt;
  this->position_.y = yt;
  this->position_.z = zt;
  this->rotation_.x = xr;
  this->rotation_.y = yr;
  this->rotation_.z = zr;
  this->toDelete = false;
}

Plan::~Plan()
{

}

void	Plan::initialize()
{
  this->picture = gdl::Image::load("./Menu_assets/floor.jpg");
}

int	Plan::update(gdl::GameClock const &gameclock, gdl::Input &input, std::list<AObject *> &list)
{
  (void)gameclock;
  (void)input;
  (void)list;
  return (0);
}

void	Plan::draw()
{
  this->picture.bind();
  glPushMatrix();
  glBegin(GL_QUADS);

  //glColor3f(255, 0, 0);

  glTexCoord2f(0.0, 0.0);
  glVertex3f(-100, 100, this->position_.z * -200 + 100);

  glTexCoord2f(0.0, 1.0);
  glVertex3f(this->position_.x * 200 - 100, 100, this->position_.z * -200 + 100);

  glTexCoord2f(1.0, 1.0);
  glVertex3f(this->position_.x * 200 - 100, 100, 100);

  glTexCoord2f(1.0, 0.0);
  glVertex3f(-100, 100, 100);

  glEnd();
  glPopMatrix();
}
