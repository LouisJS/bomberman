//
// InterfaceGraphique.cpp for InterfaceGraphique in /home/lecocq_l/bomberman-2016-rucquo_a
// 
// Made by louis lecocq
// Login   <lecocq_l@epitech.net>
// 
// Started on  Sat Jun  8 17:19:44 2013 louis lecocq
// Last update Mon Oct 21 13:37:11 2013 antoine bigotte
//

#include "InterfaceGraphique.hh"
#include "Menu.hpp"

InterfaceGraphique::InterfaceGraphique() : Game()
{
}

InterfaceGraphique::~InterfaceGraphique()
{
  sleep(2);
}

void	InterfaceGraphique::erase_object_(size_t x_pos, size_t y_pos)
{
  std::list<AObject*>::iterator it = this->objects_.begin();

  while (it != this->objects_.end())
    {
      if ((*it)->getPosX() == y_pos * SIZE_CUBE
	  && (*it)->getPosZ() == x_pos * SIZE_CUBE * -1
	  && (*it)->getTypeObject() == CUBE)
	{
	  (*it)->play_anim("Default Take");
	}
      it++;
    }
}

void	InterfaceGraphique::setMusicStatus(bool var)
{
  if (var == true)
    {
      if (this->music_.OpenFromFile("./Menu_assets/Sound/Storm_Eagle.ogg"))
	this->music_.Play();
    }
  else
    {
      if (this->music_.OpenFromFile("./Menu_assets/Sound/Storm_Eagle.ogg"))
	this->music_.Stop();
    }
}

void	InterfaceGraphique::push(AObject *src)
{
  this->objects_.push_back(src);
}

void    InterfaceGraphique::clear()
{
  this->objects_.clear();
}

void	InterfaceGraphique::initialize(void)
{
  std::list<AObject*>::iterator itb = this->objects_.begin();

  this->step_ = INTRO;
  this->size_map = 10;
  this->nb_IA = 2;
  this->pause = false;
  window_.setHeight(HEIGHT);
  window_.setWidth(WIDTH);
  window_.create();
  window_.catchEvent();
  camera_.initialize(HEIGHT, WIDTH);
  for (; itb != this->objects_.end(); ++itb)
    (*itb)->initialize();
  if (this->music_.OpenFromFile("./Menu_assets/Sound/The funeral - Band of horses.ogg"))
    this->music_.Play();
}

void	InterfaceGraphique::myInit()
{
  std::vector<std::vector<ABlock *> >	v = this->map->getBlocks();
  size_t			       	i = 0;
  size_t				j;
  std::list<AObject*>			player;
  AObject			       	*temp;
  std::list<AObject*>::iterator		itb;
  std::list<AObject*>::iterator		itc;
  static float				count_rot = 0;
  int					count_player = 0;


  itb = this->objects_.begin();
  for (int x = 0; x < 2 && itb != this->objects_.end() ;x++)
    {
      if ((*itb)->getTypeObject() == PLAYER)
	{
	  player.push_back(*itb);
	  count_player++;
	}
      itb++;
    }
  itb = this->objects_.begin();
  while (itb != this->objects_.end())
    {
      if ((*itb)->getTypeObject() == CUBE || (*itb)->getTypeObject() == BONUS
	  || (*itb)->getTypeObject() == LAVE || (*itb)->getTypeObject() == TEXT)
	itb = this->objects_.erase(itb);
      else
	itb++;
    }
  for (itc = player.begin(); itc != player.end(); itc++)
    {
      if ((*itc)->getPosX() / 200 - MAX_VERTICAL < 0)
	i = 0;
      else
	i = (*itc)->getPosX() / 200 - MAX_VERTICAL;
      while (i < ((*itc)->getPosX() / 200 + MAX_VERTICAL) && i < v.size())
	{
	  if ((*itc)->getPosZ() / -200 - (MAX_HORIZON / count_player) < 0)
	    j = 0;
	  else
	    j = (*itc)->getPosZ() / -200 - (MAX_HORIZON / count_player);
	  while (j < v[i].size() && j < (*itc)->getPosZ() / -200 + (MAX_HORIZON / count_player))
	    {
	      temp = NULL;
	      switch (v[i][j]->getType())
		{
		case FRAGILE:
		  temp = new Model::Object("./cube_texture/destructible_cube.fbx", i * SIZE_CUBE, 1 * SIZE_CUBE, j * SIZE_CUBE * -1, 0, 0, 0, CUBE);
		  break;
		case WALL:
		  temp = new Model::Object("./cube_texture/indestructible_cube.fbx", i * SIZE_CUBE, 1 * SIZE_CUBE, j * SIZE_CUBE * -1, 0, 0, 0, CUBE);
		  break;
		case TOTAL:
		  temp = new Bonus(i * SIZE_CUBE, 1 * SIZE_CUBE, j * SIZE_CUBE * -1, 0, count_rot, 30, TOTAL);
		  break;
		case RANGE:
		  temp = new Bonus(i * SIZE_CUBE, 1 * SIZE_CUBE, j * SIZE_CUBE * -1, 0, count_rot, 30, RANGE);
		  break;
		case SPEED:
		  temp = new Bonus(i * SIZE_CUBE, 1 * SIZE_CUBE, j * SIZE_CUBE * -1, 0, count_rot, 30, SPEED);
		  break;
		case FIRE:
		  temp = new Model::Object("./cube_texture/lave.fbx", i * SIZE_CUBE, 1 * SIZE_CUBE, j * SIZE_CUBE * -1, 0, 0, 0, LAVE);
		  break;
		default:
		  break;
		}
	      if (temp != NULL)
		{
		  temp->initialize();
		  this->push(temp);
		}
	      j++;
	    }
	  i++;
	}
    }
  count_rot += 5;
  if (count_rot > 360)
    count_rot = 0;
}

void	InterfaceGraphique::go_to_menu()
{
  Menu*		back = new Menu(1600.0, 900.0);

  back->setIG(this);
  this->step_ = HOME;
  this->objects_.clear();
  back->initialize();
  this->push(back);
}

gdl::GameClock	&InterfaceGraphique::getGameClock()
{
  return (this->gameClock_);
}

Step                  InterfaceGraphique::getStep() const
{
  return this->step_;
}


gdl::Input	&InterfaceGraphique::getInput()
{
  return (this->input_);
}

std::list<AObject *>	&InterfaceGraphique::getList()
{
  return (this->objects_);
}

bool          InterfaceGraphique::getPause() const
{
  return this->pause;
}

void	InterfaceGraphique::lose()
{
  AObject*	temp;

  this->objects_.clear();

  temp = new Picture(0.0, 0.0, 1600.0, 900.0, 0, NONE);
  temp->initialize();
  this->objects_.push_front(temp);

  temp = new Text(80, 400, "YOU LOSE MWAAHAH", 40, NONE);
  this->objects_.push_back(temp);
}

void	InterfaceGraphique::win()
{
  AObject*	temp;

  this->objects_.clear();

  temp = new Picture(0.0, 0.0, 1600.0, 900.0, 0, NONE);
  temp->initialize();
  this->objects_.push_front(temp);
  
  temp = new Text(80, 400, "YOU WIN BIATCH", 40, NONE);
  this->objects_.push_back(temp);
}

void	InterfaceGraphique::update(void)
{
  std::list<AObject*>::iterator itb = this->objects_.begin();
  static	bool	touche_esc = false;
  window_.setHeight(HEIGHT);
  window_.setWidth(WIDTH);

  /** BOOL GAME + PAUSE **/
  if (this->pause == false)
    {
      while (itb != this->objects_.end())
	{
	  if ((*itb)->getTypeObject() != CUBE)
	    if ((*itb)->update(gameClock_, input_, this->objects_) == 1)
	      break;
	  if ((*itb)->getToDelete() == true)
	    {
	      this->objects_.erase(itb);
	      break;
	    }
	  itb++;
	}
      if (this->step_ == GAME)
	this->myInit();
    }
  /* Check ECHAP */

  if (input_.isKeyDown(gdl::Keys::Escape) == true && touche_esc == false)
    {
      gameClock_.reset();
      touche_esc = true;
      switch (this->step_)
	{
	case INTRO:
	  go_to_menu();
	  setMusicStatus(true);
	  break;
	case GAME:
	  if (this->pause)
	    {
	      gameClock_.play();
	      this->pause = false;
	    }
	  else
	    {
	      this->push(new Text(500, 200, "PAUSE", 150, NONE));
	      gameClock_.pause();
	      this->pause = true;
	    }
	  break;
	case HOME:
	  window_.close();
	  break;
	case SETTINGS:
	  go_to_menu();
	  break;
	default:
	  break;
	}
    }

  if (input_.isKeyDown(gdl::Keys::Escape) == false)
    touche_esc = false;

  if (this->step_ == END_GAME)
    {
      sleep(3);
      go_to_menu();
      setMusicStatus(true);
    }
  /**/
}

void	InterfaceGraphique::draw(void)
{
  int				nbrPlayer = 0;
  int				nbrIa = 0;
  int				temp = 0;
  std::list<AObject*>	       	player;
  int				i;
  std::list<AObject*>::iterator	itb;
  std::list<AObject*>::iterator	itc;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0, 0, 0, 1);
  glClearDepth(1.0f);
  itb = this->objects_.begin();
  i = 0;
  while (i++ < 2 && itb != this->objects_.end())
    {
      if ((*itb)->getTypeObject() == PLAYER && (*itb)->getToDelete() == false)
	{
	  player.push_back(*itb);
	  temp++;
	}
      if ((*itb)->getTypeObject() == IA)
	nbrIa++;
      itb++;
    }
  if (this->step_ == GAME && (temp == 0 || (temp == 1 && nbrIa == 0)))
    {
      if (temp == 0)
	lose();
      else if (temp == 1 && nbrIa == 0)
	win();
      this->step_ = END_GAME;
      glViewport(0, 0, window_.getWidth(), window_.getHeight());
      this->camera_.updatePosition(-640, 0, 0, 0, 0, 0);
      camera_.initialize(HEIGHT, WIDTH);
      itb = this->objects_.begin();
      for (; itb != this->objects_.end(); ++itb)
        (*itb)->draw();
      return ;
    }
  itc = player.begin();
  for (; itc != player.end(); ++itc)
    {
      camera_.updatePosition((*itc)->getPosX() + 300, (*itc)->getPosY() + 1000, (*itc)->getPosZ(),
			     (*itc)->getPosX(), (*itc)->getPosY(), (*itc)->getPosZ());
      if (temp > 1)
	{
	  camera_.initialize(HEIGHT, WIDTH / 2);
	  if (nbrPlayer == 0)
	    glViewport(0, 0, (window_.getWidth() / 2.0) - 2, window_.getHeight());
	  else
	    glViewport((window_.getWidth() / 2.0) + 2, 0, (window_.getWidth() / 2.0) - 2, window_.getHeight());
	}
      else
	{
	  glViewport(0, 0, window_.getWidth(), window_.getHeight());
	  camera_.initialize(HEIGHT, WIDTH);
	}
      itb = this->objects_.begin();
      /**/
      for (; itb != this->objects_.end(); ++itb)
	(*itb)->draw();
      /**/
      nbrPlayer++;
    }
  if (temp == 0)
    {
      glViewport(0, 0, window_.getWidth(), window_.getHeight());
      this->camera_.updatePosition(-640, 0, 0, 0, 0, 0);
      camera_.initialize(HEIGHT, WIDTH);
      itb = this->objects_.begin();
      for (; itb != this->objects_.end(); ++itb)
	(*itb)->draw();
    }
  this->window_.display();
}

void	InterfaceGraphique::set_map(size_t map_)
{
  if (map_ < 10)
    this->size_map = 10;
  else
    this->size_map = map_;
}

void	InterfaceGraphique::set_nb_ia(size_t ia_)
{
  if (ia_ < 2)
    this->nb_IA = 2;
  else
    this->nb_IA = ia_;
}

void	InterfaceGraphique::push_map(Map *m)
{
  this->map = m;
}

void	InterfaceGraphique::set_step(Step step)
{
  this->step_ = step;
}

size_t	InterfaceGraphique::get_map() const
{
  return (this->size_map);
}

size_t	InterfaceGraphique::get_nb_ia() const
{
  return (this->nb_IA);
}

void	InterfaceGraphique::unload(void)
{
}

size_t	InterfaceGraphique::getWindowX() const
{
  return (this->window_.getWidth());
}

size_t	InterfaceGraphique::getWindowY() const
{
  return (this->window_.getHeight());
}
