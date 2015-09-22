//
// test.hh for test in /media/bigott_a/fcf68f6c-ae09-4a35-9a71-539d19cb9a04/home/bigott_a/Documents/Bomberman/Projet/test_lib
// 
// Made by bigott-a
// Login   <bigott_a@epitech.net>
// 
// Started on  Tue Apr 30 10:31:03 2013 bigott-a
// Last update Sun Jun  9 17:32:24 2013 louis lecocq
//

#ifndef __INTERFACEGRAPHIQUE_HH__
#define __INTERFACEGRAPHIQUE_HH__

#include "./lib/libgdl_gl-2012.4/include/Clock.hpp"
#include "./lib/libgdl_gl-2012.4/include/Color.hpp"
#include "./lib/libgdl_gl-2012.4/include/Game.hpp"
#include "./lib/libgdl_gl-2012.4/include/GameClock.hpp"
#include "./lib/libgdl_gl-2012.4/include/Image.hpp"
#include "./lib/libgdl_gl-2012.4/include/Input.hpp"
#include "./lib/libgdl_gl-2012.4/include/Model.hpp"
#include "./lib/libgdl_gl-2012.4/include/Window.hpp"
#include "./lib/libgdl_gl-2012.4/include/Text.hpp"

#include "SFML/Audio.hpp"

#include <GL/glu.h>
#include <GL/gl.h>
#include <unistd.h>

class	InterfaceGraphique;

#include "camera.hh"
#include "Vector3f.hh"
#include "AObject.hpp"
#include "Map.hh"
#include "Bonus.hpp"

enum	Step
  {
    INTRO,
    GAME,
    HOME,
    SETTINGS,
    END_GAME
  };

#define	HEIGHT		900.0
#define	WIDTH		1600.0
#define SIZE_CUBE	200
#define	RATIO_DRAWER	600
#define	MAX_VERTICAL	5
#define	MAX_HORIZON	8


class			InterfaceGraphique : public gdl::Game
{
public:

  InterfaceGraphique();
  virtual ~InterfaceGraphique();

  void			push(AObject *src);
  void			clear();
  void			initialize(void);
  void			myInit();
  void			checkLave();
  void			update(void);
  void			draw(void);
  void			unload(void);
  void			erase_object_(size_t x_pos, size_t y_pos);
  void			set_map(size_t);
  void			set_nb_ia(size_t);
  size_t		get_map() const;
  size_t		get_nb_ia() const;
  void			push_map(Map *);
  void			set_step(Step);
  void			go_to_menu();
  size_t		getWindowX() const;
  size_t		getWindowY() const;
  void			setMusicStatus(bool);
  Step			getStep() const ;
  gdl::GameClock	&getGameClock();
  gdl::Input		&getInput();
  bool			getPause() const;
  std::list<AObject *>	&getList();
  void			lose();
  void			win();

private:

  Camera		camera_;
  std::list<AObject*>	objects_;
  Map			*map;
  size_t		size_map;
  size_t		nb_IA;
  Step			step_;
  sf::Music		music_;
  bool			pause;
};

#endif
