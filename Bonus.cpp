//
// Bonus.cpp for Bomberman in /home/bigott_a/Documents/Bomberman/Projet/bomberman-2016-rucquo_a
// 
// Made by bigott-a
// Login   <bigott_a@epitech.net>
// 
// Started on  Tue Jun  4 11:06:22 2013 bigott-a
// Last update Wed Jun  5 16:38:08 2013 louis lecocq
//

#include "Bonus.hpp"

Bonus::Bonus(float xt, float yt, float zt, float xr, float yr, float zr, enum Type type)
{
  this->position_.x = xt;
  this->position_.y = yt;
  this->position_.z = zt;
  this->rotation_.x = xr;
  this->rotation_.y = yr;
  this->rotation_.z = zr;
  this->toDelete = false;
  this->type = type;
}

Bonus::~Bonus()
{

}

void	Bonus::initialize()
{
  switch (this->type)
    {
    case RANGE:
      {
	this->picture = gdl::Image::load("./cube_texture/ultimate_orb_lg.png");
	break;
      }
    case TOTAL:
      {
	this->picture = gdl::Image::load("./cube_texture/ability_rogue_distract.jpg");
	break;
      }
    case SPEED:
      {
	this->picture = gdl::Image::load("./cube_texture/travel_boots_lg.png");
	break;
      }
    default:
      break;
    }
}

int	Bonus::update(gdl::GameClock const &gameclock, gdl::Input &input, std::list<AObject *> &list)
{
  (void)gameclock;
  (void)input;
  (void)list;
  this->rotation_.y += 5;
  return (0);
}

void	Bonus::draw()
{
  this->picture.bind();
  glPushMatrix();
  glTranslatef(this->position_.x, this->position_.y, this->position_.z);
  glRotatef(this->rotation_.x, 1, 0, 0);
  glRotatef(this->rotation_.y, 0, 1, 0);
  glRotatef(this->rotation_.z, 0, 0, 1);
  glBegin(GL_QUADS);

  glTexCoord2f(0.0, 1.0);
  glVertex3f(0, 0, -50);

  glTexCoord2f(1.0, 1.0);
  glVertex3f(0, 0, 50);

  glTexCoord2f(1.0, 0.0);
  glVertex3f(0, 100, 50);

  glTexCoord2f(0.0, 0.0);
  glVertex3f(0, 100, -50);

  glEnd();
  glPopMatrix();
}
