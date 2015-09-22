//
// Bombe.cpp for bomberman in /home/dacost_c/bomberman
// 
// Made by chris dacostaesilva
// Login   <dacost_c@epitech.net>
// 
// Started on  Tue Apr 30 16:12:39 2013 chris dacostaesilva
// Last update Sun Jun  9 17:37:04 2013 bigott-a
//

#include "Bombe.hh"

Bombe::Bombe(Player *gamer, gdl::GameClock const &gameClock): B_Clock(gameClock), proprio(gamer)
{
  power =  2 + gamer->get_bonus_range();
  this->proprio->map->addBomb(gamer->getXPos(), gamer->getYPos());
  this->xPos = gamer->getXPos();
  this->yPos = gamer->getYPos();
  this->toDelete = false;
}

Bombe::~Bombe()
{
}

void		Bombe::explode()
{
  bool		first = false;
  float		time_boom = this->B_Clock.getTotalGameTime();
  float		pause = 0;
  float		explose = time_boom + 2.5;

  while (time_boom < explose)
    {
      if (this->proprio->map->getBlocks()[this->yPos][this->xPos]->getType() == EXPLODING)
	break;
      usleep(5000);
      if (this->proprio->map->IG->getPause() == true)
	{
	  if (first == false)
	    {
	      pause = explose - time_boom;
	      first = true;
	    }
	  explose = pause + this->B_Clock.getTotalGameTime();
	}
      else
	{
	  time_boom = this->B_Clock.getTotalGameTime();
	}
    }
  if (!this->proprio || !this->proprio->map)
    return;
  this->proprio->up_bombe();
  this->proprio->map->explosion(this->power, this->xPos, this->yPos);
  this->deleteMe();
}

void		Bombe::initialize()
{
  this->model_ = gdl::Model::load("./lib/libgdl_gl-2012.4/assets/bomb.fbx");
}

int		Bombe::update(gdl::GameClock const &gameClock, gdl::Input &input, std::list<AObject*> &list)
{
  (void)gameClock;
  (void)input;
  (void)list;
  return (0);
}

void		Bombe::draw()
{
  glPushMatrix();
  glTranslatef(this->yPos * 200.0, 200.0, this->xPos * -200.0);
  glScalef(0.5, 0.5, 0.5);
  this->model_.draw();
  glPopMatrix();
}

Genre		Bombe::getTypeObject() const
{
  return (BOMBE);
}

float		Bombe::getPosX() const
{
  return (this->yPos * 200.0);
}

float		Bombe::getPosY() const
{
  return (200.0);
}

float		Bombe::getPosZ() const
{
  return (this->xPos * (-200.0));
}

void		Bombe::play_anim(const std::string &text)
{
  (void)text;
}
