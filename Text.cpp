//
// Text.cpp for Test in /home/lecocq_l/Documents/projets/3-Semestre/bomberman
// 
// Made by louis lecocq
// Login   <lecocq_l@epitech.net>
// 
// Started on  Fri May 10 15:11:00 2013 louis lecocq
// Last update Sun Jun  9 15:25:37 2013 bigott-a
//

#include "Text.hpp"
#include <iostream>
#include <sstream>
#include <string>

void	Text::initialize()
{
}

Text::Text(unsigned int x, unsigned int y,
	   std::string const &message, int size, Action set)
{
  this->text_.setText(message);
  this->text_.setSize(size);
  this->text_.setPosition(x, y);
  this->text_.setFont("./Menu_assets/JUNEBUG.TTF");
  this->x_ = x;
  this->y_ = y;
  this->toDelete = false;
  this->IG = NULL;
  this->set_ = set;
}

Text::~Text()
{
}

void	Text::setIG(InterfaceGraphique *ig)
{
  this->IG = ig;
}

int	Text::update(gdl::GameClock const &Gameclock, gdl::Input &input, std::list<AObject*> &list)
{
  std::ostringstream sstr;
  std::string	message;
  size_t	size;

  if (this->IG != NULL && this->set_ != NONE)
    {
      if (this->set_ == MAP)
	size = this->IG->get_map();
      else if (this->set_ == NB_IA)
	size = this->IG->get_nb_ia();
      sstr << size;
      message = sstr.str();
      this->text_.setText(message);
    }

  (void)Gameclock;
  (void)input;
  (void)list;
  return (0);
}

void	Text::draw(void)
{
  this->text_.draw();
}

