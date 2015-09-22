//
// Menu.hpp for Menu in /home/lecocq_l/bomberman/partie_arthur
// 
// Made by louis lecocq
// Login   <lecocq_l@epitech.net>
// 
// Started on  Fri May 17 13:00:28 2013 louis lecocq
// Last update Sun Jun  9 17:34:19 2013 bigott-a
//

#ifndef	__MENU_HPP__
# define __MENU_HPP__

#include "AObject.hpp"
#include <iostream>
#include <map>
#include "Map.hh"
#include "Score.hh"
#include <string>
#include "InterfaceGraphique.hh"
#include "Object.hpp"
#include "Player.hpp"
#include "Picture.hpp"
#include "Text.hpp"

class Player;

class			Menu : public AObject
{
public:

  Menu(float, float);
  ~Menu();
  void			initialize();
  int			update(gdl::GameClock const &, gdl::Input &, std::list<AObject*> &);
  void			draw();
  Genre			getTypeObject() const { return (MENU); }
  float			getPosX() const { return (this->position_.x); }
  float			getPosY() const { return (this->position_.y); }
  float			getPosZ() const { return (this->position_.z); }
  void			play_anim(const std::string &) { return ; }
  void			one_player(std::list<AObject *> &);
  void			two_player(std::list<AObject *> &);
  void			settings(std::list<AObject *> &);
  void			highscores(std::list<AObject *> &);
  void			credits(std::list<AObject *> &);
  void			setIG(InterfaceGraphique *);
 private:

  Vector3f		position_;
  std::map<std::string, void (Menu::* const)(std::list<AObject*>&)>	list;
  std::map<std::string, void (Menu::* const)(std::list<AObject*>&)>::iterator	it;
  gdl::Image		picture_;
  bool			up;
  bool			down;
  float			size_x;
  float			size_y;
  InterfaceGraphique	*IG;
  sf::Sound		banzai_;
  sf::SoundBuffer	banzai_buffer;
 };

#endif  /* __MENU_HPP */
