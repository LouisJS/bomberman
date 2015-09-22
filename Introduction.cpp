//
// Introduction.cpp for Introduction in /home/lecocq_l/bomberman-2016-rucquo_a
// 
// Made by louis lecocq
// Login   <lecocq_l@epitech.net>
// 
// Started on  Sat Jun  8 16:11:32 2013 louis lecocq
// Last update Sun Jun  9 17:12:29 2013 louis lecocq
//

#include "Introduction.hpp"
#include <iostream>

Introduction::Introduction(float xt, float yt, float size_x_, float size_y_)
{
  this->position_.x = xt;
  this->position_.y = yt;
  this->position_.z = 0.0;
  this->size_x = size_x_;
  this->size_y = size_y_;
  this->toDelete = false;
}

Introduction::~Introduction()
{
}

void	Introduction::setIG(InterfaceGraphique *ig)
{
  this->IG = ig;
}

void	Introduction::initialize()
{
  this->list.push_front("/Menu_assets/intro/bomberman01.png");
  this->list.push_back("/Menu_assets/intro/bomberman02.png");
  this->list.push_back("/Menu_assets/intro/bomberman03.png");
  this->list.push_back("/Menu_assets/intro/bomberman04.png");
  this->list.push_back("/Menu_assets/intro/bomberman05.png");
  this->list.push_back("/Menu_assets/intro/bomberman06.png");
  this->list.push_back("/Menu_assets/intro/bomberman07.png");
  this->list.push_back("/Menu_assets/intro/bomberman08.png");
  this->list.push_back("/Menu_assets/intro/bomberman09.png");
  this->list.push_back("/Menu_assets/intro/bomberman10.png");
  this->list.push_back("/Menu_assets/intro/bomberman11.png");
  this->list.push_back("/Menu_assets/intro/bomberman12.png");
  this->list.push_back("/Menu_assets/intro/bomberman13.png");
  this->list.push_back("/Menu_assets/intro/bomberman14.png");
  this->list.push_back("/Menu_assets/intro/bomberman15.png");
  this->list.push_back("/Menu_assets/intro/bomberman16.png");

  this->itb = this->list.begin();
  this->picture_ = gdl::Image::load(*(this->itb));
  this->first_time = true;
  this->time_ = 0.0;
}

int	Introduction::update(gdl::GameClock const &gameClock, gdl::Input &input, std::list<AObject*> &list)
{
  (void)list;
  (void)input;

  if (first_time == true)
    {
      this->time_ = gameClock.getTotalGameTime();
      first_time = false;
    }
  else
    {
      if (gameClock.getTotalGameTime() > this->time_ + 7.5)
	{
	  this->time_ = this->time_ + 7.5;
	  itb++;
	  if (this->itb != this->list.end())
	    {
	      this->picture_ = gdl::Image::load(*(this->itb));
	    }
	  else
	    itb--;
	}
    }
  /**/
  
  // Load le suivant au bout de 7.5 secondes

  /**/

  return (0);
}

void	Introduction::draw(void)
{
  this->picture_.bind();
  glBegin(GL_QUADS);

  // Vertex superieur gauche
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(0.0f, this->size_y / 2 + this->position_.y, (-1 * this->size_x / 2) + this->position_.x);
  /// Vertex inferieur gauche
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(0.0f, (-1 * this->size_y / 2) + this->position_.y, (-1 * this->size_x / 2) + this->position_.x);
  /// Vertex inferieur droit
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(0.0f, (-1 * this->size_y / 2) + this->position_.y, (this->size_x / 2) + this->position_.x);
  /// Vertex superieur droit
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(0.0f, (this->size_y / 2) + this->position_.y, (this->size_x / 2) + this->position_.x);
  glEnd();
}
