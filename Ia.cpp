//
// Ia.cpp for bomberman in /home/dacost_c/bomberman-2016-rucquo_a/robots
// 
// Made by chris dacostaesilva
// Login   <dacost_c@epitech.net>
// 
// Started on  Mon Jun  3 14:22:53 2013 chris dacostaesilva
// Last update Sun Jun  9 17:13:17 2013 chris dacostaesilva
//

#include "Ia.hpp"

IRobot::IRobot(const std::string path, Genre type_player, Map *map, gdl::Keys::Key top_, gdl::Keys::Key down_, gdl::Keys::Key left_, gdl::Keys::Key right_, gdl::Keys::Key Bombe_) : Player(path,type_player, map, top_, down_, left_, right_,  Bombe_)
{
  this->map_ia_done = false;
  this->alive = true;
  this->moving = false;
  this->take_bomb = false;
  this->rec = false;
  this->tmp = 0;
}

IRobot::~IRobot()
{
  
}

int     IRobot::update(gdl::GameClock const &gameClock, gdl::Input &input, std::list<AObject*> &list)
{

  (void)input;
  if (list.empty())
    return 0;
  if (this->map->getBlocks()[this->yPos][this->xPos]->getType() == FIRE || this->map->getBlocks()[this->yPos][this->xPos]->getType() == EXPLODING)
    {
      this->die();
    }
  switch (this->map->getBlocks()[this->yPos][this->xPos]->getType())
    {
    case (RANGE):
      {
	this->bonus_range++;
	this->map->getBlocks()[this->yPos][this->xPos]->setType(FLOOR);
	break;
      }
    case (TOTAL):
      {
	this->nb_bombe_total++;
	this->nb_bombe++;
	this->bonus_bombe++;
	this->map->getBlocks()[this->yPos][this->xPos]->setType(FLOOR);
	break;
      }
    case (SPEED):
      {
	if (speed < 1.4)
	  {
	    this->speed += 0.2;
	    this->bonus_speed++;
	  }
	this->map->getBlocks()[this->yPos][this->xPos]->setType(FLOOR);
	break;
      }
    default:
      break;
    }
 
  this->take_bomb = false;
  this->rec = false;
  Play_like_an_IA(gameClock,list);
 
  return (0);
}

void	IRobot::actualise_map()
{
  size_t	i;
  size_t	j;

  if (this->getPosX() / 200 - MAX_VERTICAL < 0)
    i = 0;
  else
    i = this->getPosX() / 200 - MAX_VERTICAL;  
  while (i < (this->getPosX() / 200 + MAX_VERTICAL) && i < this->map->getBlocks().size())
    {
      if (this->getPosZ() / -200 - MAX_HORIZON < 0)
	j = 0;
      else
	j = this->getPosZ() / -200 - MAX_HORIZON;
      while (j < this->map->getBlocks().size()  && j < this->getPosZ() / -200 + MAX_HORIZON)
	{
	  if (this->map->getBlocks()[i][j]->getType() == FLOOR || this->map->getBlocks()[i][j]->getType() >= 6) 
	    (*intel_map)[i][j] = 0;
	  else if (this->map->getBlocks()[i][j]->getType() == WALL || this->map->getBlocks()[i][j]->getType() == FRAGILE)
	    (*intel_map)[i][j] = 2;
	  else
	    (*intel_map)[i][j] = 1;
	  j++;
	}
      i++;
    }
}

void	IRobot::Ia_play_init()
{
  size_t                                        i = 0;
  size_t                                        j;
  size_t                                        x = this->map->getBlocks()[0].size();
  size_t                                        y = this->map->getBlocks().size();
  std::vector<int>                              slot;

  this->intel_map = new std::vector<std::vector<int> >;
  while (i < y)
    {
      j = 0;
      intel_map->push_back(slot);
      while (j < x)
        {
	  (*intel_map)[i].push_back(0);
          j++;
        }
      i++;
    }
  this->map_ia_done = true;
  this->iMax = (*intel_map).size();
  this->jMax = (*intel_map)[0].size();
}

void    IRobot::marque_up(size_t i, size_t j)
{

  while (1)
  {
    if ((*intel_map)[i][j] == 2)
      break;
    if ((*intel_map)[i][j] != 1)
      (*intel_map)[i][j] = 3;
    if (i == 0)
      return;
    i --;
  }
}

void   IRobot::marque_down(size_t i, size_t j)
{
  while (i < intel_map[0].size())
    {
      if ((*intel_map)[i][j] == 2)
	break;
      if ((*intel_map)[i][j] != 1)
	(*intel_map)[i][j] = 3;
      i++;
    }
}

void    IRobot::marque_left(size_t i, size_t j)
{
  while (1)
  {
    if ((*intel_map)[i][j] == 2)
      break;
    if ((*intel_map)[i][j] != 1)
      (*intel_map)[i][j] = 3;
    if (j == 0)
      return;
    j--;
  }
}

void    IRobot::marque_right(size_t i, size_t j)
{
  while (j < intel_map->size())
    {
      if ((*intel_map)[i][j] == 2)
	break;
      if ((*intel_map)[i][j] != 1)
	(*intel_map)[i][j] = 3;
      j++;
    }
}

void IRobot::place_danger(size_t i, size_t j)
{
  marque_left(i, j);
  marque_right(i, j);
  marque_up(i, j);
  marque_down(i, j);
}


void IRobot::actualise_intel_map()
{
  size_t                                        i = 0;
  size_t                                        j;

  while (i < iMax)
    {
      j = 0;
      while (j < jMax)
        {
	  if ((*intel_map)[i][j] == 1)
	    {
	      place_danger(i , j);
	    }
          j++;
        }
      i++;
    }
}

void	IRobot::print_map()
{
  size_t                                        i = 0;
  size_t                                        j;
   std::cout <<" i = "  << xPos << std::endl;
   std::cout <<" j = " << yPos << std::endl;
  while (i < iMax)
    {
      j = 0;
      while (j < jMax)
        {
	  std::cout << (*intel_map)[i][j];
          j++;
        }
      std::cout << std::endl;
      i++;
    }
  std::cout << std::endl;
  std::cout << std::endl;
}

void            IRobot::Play_like_an_IA(gdl::GameClock const &gameClock, std::list<AObject*> &list)
{

  if (this->map_ia_done == false)
    Ia_play_init();
  else
    actualise_map();
  actualise_intel_map();
  if ((*intel_map)[this->yPos][this->xPos] == 1 || (*intel_map)[this->yPos][this->xPos] == 3)
    {
      search_path_protect();
    }
  else
    {
      if (this->nb_bombe == 0)
	{
	  this->dir = 0;
	}
      else
	search_path_offensiv();
    }
  go_run(gameClock, list);
}

int          IRobot::search_up()
{
  int		howmany = 0;
  size_t	i = this->yPos;
  size_t	j = this->xPos;

  while (1)
    {
      if (i == 0)
	return 0;
      i--;
      if ((*intel_map)[i][j] == 2 || (*intel_map)[i][j] == 1)
        return 0;
      if ((*intel_map)[i][j] == 0)
        {
	  howmany++;
          return howmany;
        }
      else if ((*intel_map)[i][j] == 3)
        {
	  howmany++;
	  if (j > 0 && (*intel_map)[i][j - 1] == 0)
	    {
	      this->rec = true;
	      return howmany + 2;
	    }
	  if (j < (*intel_map).size() && (*intel_map)[i][j + 1] == 0)
	    {
	      this->rec = true;
	      return howmany + 2;
	    }
        }
      howmany++;
    }
  return 0;
}

int          IRobot::search_down()
{
  int		howmany = 0;
  size_t	i = this->yPos;
  size_t	j = this->xPos;

  while (i < (*intel_map).size() - 1)
    {
      if (i == (*intel_map).size() - 1)
	return 0;
      i++;
      if ((*intel_map)[i][j] == 2 || (*intel_map)[i][j] == 1)
	return 0;
      if ((*intel_map)[i][j] == 0)
	{
	  howmany++;
	  return howmany;
	}
      else if ((*intel_map)[i][j] == 3)
	{
	  howmany++;
	  if (j > 0 && (*intel_map)[i][j - 1] == 0)
	    {
	      this->rec = true;
	      return howmany + 2;
	    }
	  else if (j < (*intel_map).size() - 1 && (*intel_map)[i][j + 1] == 0)
	    {
	      this->rec = true;
	      return howmany + 2;
	    }
	}
      howmany++;
    }
  return 0;
}

int          IRobot::search_left()
{
  int howmany = 0;
  size_t	i = this->yPos;
  size_t	j = this->xPos;

  while (j > 0)
    {
      if (j == 0)
	return 0;
      j --;
      if ((*intel_map)[i][j] == 2 || (*intel_map)[i][j] == 1)
        return 0;
      if ((*intel_map)[i][j] == 0)
        {
	  howmany++;
          return howmany;
        }
      else if ((*intel_map)[i][j] == 3)
        {
	  howmany++;
          if (i < (*intel_map).size() - 1 && (*intel_map)[i + 1][j] == 0)
	    {
	      this->rec = true;
	      return howmany + 2;
	    }
          else if (i > 0 && (*intel_map)[i - 1][j] == 0)
	    {
	      this->rec = true;
	      return howmany + 2;
	    }
        }
      howmany++;
    }
  return 0;
}

int          IRobot::search_right()
{
  int howmany = 0;
  size_t	i = this->yPos;
  size_t	j = this->xPos;

  while (j < (*intel_map).size() - 1)
    {
      if (j == (*intel_map).size() - 1)
	return 0;
      j ++;
      if ((*intel_map)[i][j] == 2 || (*intel_map)[i][j] == 1)
        return 0;
      if ((*intel_map)[i][j] == 0)
        {
	  howmany++;
          return howmany;
        }
      else if ((*intel_map)[i][j] == 3)
        {
	  howmany++;
          if (i < (*intel_map).size() - 1 && (*intel_map)[i + 1][j] == 0)
	    {
	      this->rec = true;
	      return howmany + 2;
	    }	  
	  else if (i > 0 && (*intel_map)[i - 1][j] == 0)
	    {
	      this->rec = true;  
	      return howmany + 2;
	    }
        }
      howmany++;
    }
  return 0;
}

void             IRobot::search_path_protect()
{
  int		dir[5];
  int           choice = 1;
  int           save = 0;

  dir[0] = 0;
  dir[1] = search_up();
  dir[3] = search_left();
  dir[2] = search_right();
  dir[4] = search_down();
  while (choice <= 5)
    {
      if ((dir[choice] < dir[save] && dir[choice] > 0) || (dir[save] == 0))
        save = choice;
      if (dir[choice] > dir[save])
	this->path_long = choice;
      choice++;
    }
  if (dir[save] != 0)
    this->dir = save;
  else
    this->dir = 0;
  this->path_short = dir[save];
}


int	IRobot::search_up_walk()
{
  int		howmany = 0;
  size_t	i = this->yPos;
  size_t	j = this->xPos;

  while (1)
    {
      if (i == 0)
	return 0;
      i--;
      if ((*intel_map)[i][j] == 2 || (*intel_map)[i][j] == 1 || (*intel_map)[i][j] == 3)
	{
	  this->rec = true;
	  return 0;
	}
      if ((*intel_map)[i][j] == 0)
        {
	  howmany++;
        }
      else if ((*intel_map)[i][j] == 4)
        {
	  howmany++;
	  if (j > 0 && (*intel_map)[i][j - 1] == 0)
	    {
	      return howmany ++;
	    }
	  if (j < (*intel_map).size() - 1 && (*intel_map)[i][j + 1] == 0)
	    {
              return howmany++;
	    }
        }
      howmany++;
    }
  return 0;
}

int	IRobot::search_left_walk()
{
  int howmany = 0;
  size_t	i = this->yPos;
  size_t	j = this->xPos;

  while (j > 0)
    {
      if (j == 0)
	return 0;
      j --;
      if ((*intel_map)[i][j] == 2 || (*intel_map)[i][j] == 1 || (*intel_map)[i][j] == 3)
	{
	  this->rec = true;
	  return 0;
	}
      if ((*intel_map)[i][j] == 0)
        {
	  howmany++;
          return howmany;
        }
      else if ((*intel_map)[i][j] == 4)
        {
	  howmany++;
          if (i < (*intel_map).size() - 1 && (*intel_map)[i + 1][j] == 0)
	    {
              return howmany++;
	    }
          else if (i > 0 && (*intel_map)[i - 1][j] == 0)
	    {
	      return howmany++;
	    }
	}
    }
  howmany++;
  return 0;
}

int	IRobot::search_right_walk()
{
  int howmany = 0;
  size_t	i = this->yPos;
  size_t	j = this->xPos;

  while (j < (*intel_map).size() - 1)
    {
      if (j == (*intel_map).size() - 1)
	return 0;
      j ++;
      if ((*intel_map)[i][j] == 2 || (*intel_map)[i][j] == 1 || (*intel_map)[i][j] == 3)
	return 0;
      if ((*intel_map)[i][j] == 0)
	{
	  howmany++;
	  return howmany;
	}
      else if ((*intel_map)[i][j] == 3 || (*intel_map)[i][j] == 4)
	{
	  howmany++;
	  if (i < (*intel_map).size() - 1 && (*intel_map)[i + 1][j] == 0)
	    {
	       return howmany++;	    
	    }	  
	  else if (i > 0 && (*intel_map)[i - 1][j] == 0)
	    {
	      return howmany++;
	    }
	}
      howmany++;
    }
  return 0;
}

int	IRobot::search_down_walk()
{
  int		howmany = 0;
  size_t	i = this->yPos;
  size_t	j = this->xPos;

  while (i < (*intel_map).size() - 1)
    {
      if (i == (*intel_map).size() - 1)
	return 0;
      i++;
      if ((*intel_map)[i][j] == 2 || (*intel_map)[i][j] == 1 || (*intel_map)[i][j] == 3)
	{
	  this->rec = true;
	  return 0;
	}
      if ((*intel_map)[i][j] == 0)
	{
	  howmany++;
	  return howmany;
	}
      else if ((*intel_map)[i][j] == 3)
	{
	  howmany++;
	  if (j > 0 && ((*intel_map)[i][j - 1] == 0 || (*intel_map)[i][j] == 4))
	    {
	    return howmany ++;
	    }
	  else if (j < (*intel_map).size() - 1 && (*intel_map)[i][j + 1] == 0)
	    {
	      return howmany++;
	    }
	}
      howmany++;
    }
  return 0;
}

void    IRobot::fake_marque_up(size_t i, size_t j)
{
  while (1)
    {
      if ((*intel_map)[i][j] == 2)
	break;
      if ((*intel_map)[i][j] == 0)
	(*intel_map)[i][j] = 4;
      if (i == 0)
	return;
      i--;
    }
}

void   IRobot::fake_marque_down(size_t i, size_t j)
{
  while (i < intel_map->size())
    {
      if ((*intel_map)[i][j] == 2)
	break;
      if ((*intel_map)[i][j] == 0)
	(*intel_map)[i][j] = 4;
      i++;
    }
}

void    IRobot::fake_marque_left(size_t i, size_t j)
{
  while (1)
    {
      if ((*intel_map)[i][j] == 2)
	break;
      if ((*intel_map)[i][j] == 0)
	(*intel_map)[i][j] = 4;
      if (j == 0)
	return;
      j--;
    }
}

void    IRobot::fake_marque_right(size_t i, size_t j)
{
  while (j < intel_map[0].size())
    {
      if ((*intel_map)[i][j] == 2)
	break;
      if ((*intel_map)[i][j] == 0)
	(*intel_map)[i][j] = 4;
      j++;
    }
}


void	IRobot::Marque_fake_bombe(size_t i, size_t j)
{
  fake_marque_left(i, j);
  fake_marque_right(i, j);
  fake_marque_up(i, j);
  fake_marque_down(i, j);
  return;
}

void            IRobot::search_path_offensiv()
{
  int           dir[5];
  bool		path[5];
  int           choice = 1;
  int           save = 0;

  this->take_bomb = false;
  this->rec = false;
  Marque_fake_bombe(this->yPos, this->xPos); 
  dir[0] = 0;
  path[0] = false;
  dir[1] = search_up_walk();
  path[1] = this->rec;
  this->rec = false;
  dir[3] = search_left_walk();
  path[3] = this->rec;
  this->rec = false;
  dir[2] = search_right_walk();
  path[2] = this->rec;
  this->rec = false;
  dir[4] = search_down_walk();
  path[4] = this->rec;
  this->rec = false;
  while (choice <= 4)
    {
      if (dir[choice] > 0 && path[choice] == false)
	{
	  if (dir[choice] <= dir[save] || save == 0)
	    save = choice;
	}
      choice++;
    }
  if (path[save] == true)
    {
      print_map();
      this->dir = 0;
      return;
    }
  this->dir = save;
  if (dir[save] != 0 && this->nb_bombe >= nb_bombe_total - 1 && dir[save] < 3)
    this->take_bomb = true;
}

void            IRobot::go_run(gdl::GameClock const &gameClock, std::list<AObject*> &list)
{
  AObject       *b;

  if (this->moving == true || this->alive == false)
    {
      return;
    }
  if (this->dir == 0)
    {
      this->touchZ = false;
      this->touchD = false;
      this->touchS = false;
      this->touchQ = false;
      return;
    }
  switch (this->dir)
    {
    case 1:
      {
	this->left = false;
	this->right = false;
	this->touchZ = true;
	this->touchD = false;
	this->touchS = false;
	this->touchQ = false;
	this->rotation_.y = 270;
	break;
      }
    case 2:
      {

	this->right = true;
	this->left = false;
	this->touchD = true;
	this->touchS = false;
	this->touchQ = false;
	this->touchZ = false;
	this->rotation_.y = 180;
	break;
      }
    case 3:
      {
	this->left = true;
	this->right = false;
	this->touchQ = true;
	this->touchS = false;
	this->touchD = false;
	this->touchZ = false;
	this->rotation_.y = 0;
	break;
      }
    case 4:
      {
	this->left = true;
	this->right = true;
	this->touchS = true;
	this->touchQ = false;
	this->touchD = false;
	this->touchZ = false;
	this->rotation_.y = 90;
	break;
      }
    }
  if (this->take_bomb == true)
    {
      b = this->take_down_a_claymore(gameClock);
      if (b != NULL)
	list.push_back(b);
    }
  move();
}
