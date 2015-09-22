//
// Player.cpp for  in /home/couillere/cpp/bomberman/bomberman-2016-rucquo_a
// 
// Made by arthur rucquois
// Login   <rucquo_a@epitech.net>
// 
// Started on  Mon Jun  3 16:20:41 2013 arthur rucquois
// Last update Sun Jun  9 17:25:45 2013 bigott-a
//

#include "Player.hpp"

#define MOVE 50.0

void	Player::initialize(void)
{
  gdl::Color	test((rand() % 255) + 1, (rand() % 255) + 1, (rand() % 255) + 1);

  if (this->sound_buffer.LoadFromFile("./Menu_assets/Sound/bonus.wav"))
    {
      this->sound_.SetBuffer(this->sound_buffer);
    }

  this->model_ = gdl::Model::load(this->path_);
  this->speed = 0;
  this->carry = false;
  this->shoot = false;
  this->toDelete = false;
  this->model_.set_default_model_color(test);
  this->model_.cut_animation(this->model_, "Take 001", 35, 53, "run");
  this->model_.cut_animation(this->model_, "Take 001", 0, 0, "idle");
  this->xPos = (this->position_.z * -1) / 200;
  this->yPos = this->position_.x / 200;
  this->position_.y = 100;
}

Player::Player(const std::string path, Genre type_player, Map *map, gdl::Keys::Key top_, gdl::Keys::Key down_, gdl::Keys::Key left_, gdl::Keys::Key right_, gdl::Keys::Key bombe_)
{
  this->path_ = path;
  this->type_player = type_player;
  this->nb_bombe = 1;
  this->nb_bombe_total = 1;
  this->bonus_bombe = 0;
  this->bonus_range = 0;
  this->bonus_speed = 0;
  this->speed = 1;
  this->map = map;
  this->moving = false;
  this->alive = true;
  this->p_bomb = false;
  this->t_top = top_;
  this->t_down = down_;
  this->t_left = left_;
  this->t_right = right_;
  this->t_bombe = bombe_;
}

Player::~Player(void)
{
}

int	Player::update(gdl::GameClock const &gameClock, gdl::Input &input, std::list<AObject*> &list)
{
  AObject	*b;

  if (this->map->getBlocks()[this->yPos][this->xPos]->getType() == FIRE ||
      this->map->getBlocks()[this->yPos][this->xPos]->getType() == EXPLODING)
    this->die();
  switch (this->map->getBlocks()[this->yPos][this->xPos]->getType())
    {
    case (RANGE):
      {
	this->sound_.Play();
	this->bonus_range++;
	this->map->getBlocks()[this->yPos][this->xPos]->setType(FLOOR);
	break;
      }
    case (TOTAL):
      {
	this->sound_.Play();
	this->nb_bombe_total++;
	this->nb_bombe++;
	this->bonus_bombe++;
	this->map->getBlocks()[this->yPos][this->xPos]->setType(FLOOR);
	break;
      }
    case (SPEED):
      {
	this->sound_.Play();
	if (speed < 1.2)
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
  this->touchZ = input.isKeyDown(this->t_top);
  this->touchQ = input.isKeyDown(this->t_left);
  this->touchS = input.isKeyDown(this->t_down);
  this->touchD = input.isKeyDown(this->t_right);
  this->model_.update(gameClock);
  if (((this->touchZ == true && this->touchQ == false && this->touchS == false && this->touchD == false)
       || (this->touchZ == false && this->touchQ == true && this->touchS == false && this->touchD == false)
       || (this->touchZ == false && this->touchQ == false && this->touchS == true && this->touchD == false)
       || (this->touchZ == false && this->touchQ == false && this->touchS == false && this->touchD == true))
      && this->moving == false)
    {
      if (input.isKeyDown(this->t_right) == true)
	{
	  this->right = 1;
	  this->left = 0;
	  this->rotation_.y = 180;
	  this->move();
	}
      if (input.isKeyDown(this->t_left) == true)
	{
	  this->right = 0;
	  this->left = 1;
	  this->rotation_.y = 0;
	  this->move();
	}
      if (input.isKeyDown(this->t_top) == true)
	{
	  this->right = 0;
	  this->left = 0;
	  this->rotation_.y = 270;
	  this->move();
	}
      if (input.isKeyDown(this->t_down) == true)
	{
	  this->right = 1;
	  this->left = 1;
	  this->rotation_.y = 90;
	  this->move();
	}
    }
  if (input.isKeyDown(this->t_bombe) == true && p_bomb == false)
    {
      this->p_bomb = true;
      b = this->take_down_a_claymore(gameClock);
      if (b != NULL)
	list.push_back(b);
    }
  if (input.isKeyDown(this->t_bombe) == false)
    p_bomb = false;
  return (0);
}

void	Player::draw(void)
{
  glPushMatrix();
  glTranslatef(this->position_.x, this->position_.y, this->position_.z);
  glScalef(0.5, 0.5, 0.5);
  glRotatef(this->rotation_.x, 1, 0, 0);
  glRotatef(this->rotation_.y, 0, 1, 0);
  glRotatef(this->rotation_.z, 0, 0, 1);
  this->model_.draw();
  glPopMatrix();
}

void    *tramp_bombe(void *data)
{
  Bombe *claymore = reinterpret_cast<Bombe *>(data);
  
  claymore->explode();
  pthread_exit(0);
}

void                    Player::die()
{
  this->deleteMe();
  this->alive = false;
  this->nb_bombe_total = 0;
  this->nb_bombe = 0;
  this->bonus_range = 0;
  this->bonus_speed = 0;
  this->bonus_bombe = 0;
}

void			Player::play_anim(const std::string &animation)
{
  this->model_.play(animation);
}

Bombe			*Player::take_down_a_claymore(gdl::GameClock const &clock)
{
  pthread_t		bombe;
  Bombe *test = NULL;

  if (this->alive == false)
    return (NULL);
  if (nb_bombe > 0)
    {
      test = new Bombe(this, clock);
      test->initialize();
      pthread_create(&(bombe), NULL, tramp_bombe, test);
      down_bombe();
    }
  return (test);
}

int			Player::get_bombe() const
{
  return (this->nb_bombe);
}

int			Player::get_bonus_range() const
{
  return (this->bonus_range);
}

void			Player::up_bombe()
{
  nb_bombe += 1;
}

void			Player::down_bombe()
{
  nb_bombe -= 1;
}

void			Player::setDir(const bool l, const bool r)
{
  if (this->alive == false)
    return;
  this->left = l;
  this->right = r;
}

void			Player::Play()
{
  this->model_.set_anim_speed("run", 1 + this->speed / 10);
  this->model_.play("run");
}

void			Player::Stop_animation()
{
  this->model_.stop_animation("run");
  this->model_.play("idle");
}

std::string		Player::getDir() const
{
  std::string		ret;

  this->left ? (this->right ? ret = "up" : ret = "left") : (this->right ? ret = "right" : ret = "down");
  return (ret);
}

void			*AnimateMe(void *src)
{
  Player		*temp = reinterpret_cast<Player *>(src);
  float			i = 0;

  temp->Play();
  while (i < 200)
    {
      if (temp->getLeft() && !(temp->getRight()))
	temp->setPosZ(temp->getPosZ() + (1 + temp->getSpeed()));
      if (!(temp->getLeft()) && temp->getRight())
	temp->setPosZ(temp->getPosZ() - (1 + temp->getSpeed()));
      if (temp->getLeft() && temp->getRight())
	temp->setPosX(temp->getPosX() + (1 + temp->getSpeed()));
      if (!(temp->getLeft()) && !(temp->getRight()))
	temp->setPosX(temp->getPosX() - (1 + temp->getSpeed()));
      i += 1 + temp->getSpeed();
      if (i > 200)
	{
	  if (temp->getLeft() && !(temp->getRight()))
	    temp->setPosZ(temp->getPosZ() + (1 + temp->getSpeed() - (i - 200)));
	  if (!(temp->getLeft()) && temp->getRight())
	    temp->setPosZ(temp->getPosZ() - (1 + temp->getSpeed() - (i - 200)));
	  if (temp->getLeft() && temp->getRight())
	    temp->setPosX(temp->getPosX() + (1 + temp->getSpeed() - (i - 200)));
	  if (!(temp->getLeft()) && !(temp->getRight()))
	    temp->setPosX(temp->getPosX() - (1 + temp->getSpeed() - (i - 200)));
	}
      usleep(1000);
    }
  temp->setMoving(false);
  if (temp->getToucheZ() == false
      && temp->getToucheQ() == false
      && temp->getToucheS() == false
      && temp->getToucheD() == false)
    temp->Stop_animation();
  pthread_exit(0);
}

void			Player::move()
{
  int			x = 0;
  int			y = 0;
  pthread_t		t;

  if (this->alive == false)
    return;
  this->left ? (this->right ? y = 1 : x = -1) : (this->right ? x = 1 : y = -1);
  if ((this->yPos > 0 && y == -1) || this->yPos + y < this->map->getBlocks().size())
    if ((this->xPos > 0 && x == -1) || this->xPos + x < this->map->getBlocks()[0].size())
      if ((this->map->getBlocks()[this->yPos + y][this->xPos + x]->getType() == FLOOR ||
	   this->map->getBlocks()[this->yPos + y][this->xPos + x]->getType() == FIRE ||
	   this->map->getBlocks()[this->yPos + y][this->xPos + x]->getType() == TOTAL ||
	   this->map->getBlocks()[this->yPos + y][this->xPos + x]->getType() == SPEED ||
	   this->map->getBlocks()[this->yPos + y][this->xPos + x]->getType() == RANGE))
	{
	  this->moving = true;
	  pthread_create(&t, NULL, AnimateMe, this);
	  this->xPos += x;
	  this->yPos += y;
	}
      else
	this->Stop_animation();
    else
      this->Stop_animation();
  else
    this->Stop_animation();
}

Genre  	Player::getTypeObject() const
{
  return (this->type_player);
}
