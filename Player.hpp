//
// Player.hpp for Player in /home/lecocq_l/Documents/projets/3-Semestre/bomberman
// 
// Made by louis lecocq
// Login   <lecocq_l@epitech.net>
// 
// Started on  Tue May 14 14:10:40 2013 louis lecocq
// Last update Sun Jun  9 17:25:31 2013 bigott-a
//

#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

class	Player;

#include <stdlib.h>
#include <iostream>
#include <SFML/Audio.hpp>

#include "AObject.hpp"
#include "./lib/libgdl_gl-2012.4/include/Color.hpp"
#include "Bombe.hh"

class Player : public AObject
{
public:
  Player(const std::string path, Genre type_player, Map *map, gdl::Keys::Key top_, gdl::Keys::Key down_, gdl::Keys::Key left_, gdl::Keys::Key right_, gdl::Keys::Key Bombe_);
  virtual ~Player(void);
  void			pose_bomb(gdl::GameClock const &);
  void			initialize(void);
  int			update(gdl::GameClock const &, gdl::Input &, std::list<AObject*> &);
  void			draw(void);
  Genre			getTypeObject() const;
  void			die();
  void			play_anim(const std::string &);

  float			getPosX() const { return (this->position_.x); }
  float			getPosY() const { return (this->position_.y); }
  float			getPosZ() const { return (this->position_.z); }
  void			setPosX(float i) { this->position_.x = i; }
  void			setPosY(float i) { this->position_.y = i; }
  void			setPosZ(float i) { this->position_.z = i; }
  bool			getLeft() const { return(this->left); }
  bool			getRight() const { return(this->right); }
  void			setMoving(bool temp) { this->moving = temp; }
  bool			getMoving() const { return(this->moving); }
  bool			getToucheZ() const { return (this->touchZ); }
  bool			getToucheQ() const { return (this->touchQ); }
  bool			getToucheS() const { return (this->touchS); }
  bool			getToucheD() const { return (this->touchD); }
  float			getSpeed() const { return (this->speed); }
  bool			getAlive() const { return (this->alive); }

  size_t		getXPos() const { return (this->xPos); }
  size_t		getYPos() const { return (this->yPos); }
  Bombe			*take_down_a_claymore(gdl::GameClock const &);
  void			up_bombe();
  void			down_bombe();
  int			get_bombe() const;
  int			get_bonus_range() const;
  void			setDir(const bool, const bool);
  std::string		getDir() const;
  void			move();
  void			Play();
  void			Stop_animation();
  bool			isAnimate() { return (true); }
  Map		*map;

protected:
  gdl::Keys::Key	t_top;
  gdl::Keys::Key	t_down;
  gdl::Keys::Key	t_left;
  gdl::Keys::Key	t_right;
  gdl::Keys::Key	t_bombe;
  bool			touchZ;
  bool			touchQ;
  bool			touchS;
  bool			touchD;
  bool			p_bomb;
  bool			alive;
  bool			left;
  bool			right;
  gdl::Model		model_;
  bool			moving;
  std::string		path_;
  Genre			type_player;
  size_t		xPos;
  size_t		yPos;
  int			nb_bombe;
  int			nb_bombe_total;
  int			bonus_range;
  int			bonus_speed;
  int			bonus_bombe;
  float			speed;
  bool			carry;
  bool			shoot;
  sf::Sound		sound_;
  sf::SoundBuffer	sound_buffer;
};

void    *tramp_bombe(void *data);
void	*AnimateMe(void *);

#endif
