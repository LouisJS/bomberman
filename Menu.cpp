//
// Menu.cpp for Menu in /home/lecocq_l/bomberman-2016-rucquo_a
// 
// Made by louis lecocq
// Login   <lecocq_l@epitech.net>
// 
// Started on  Sat Jun  8 17:19:18 2013 louis lecocq
// Last update Sun Jun  9 17:36:01 2013 louis lecocq
//

#include "Plan.hpp"
#include "Menu.hpp"
#include "Ia.hpp"
#include <SFML/Audio.hpp>

#define	SIZE_CUBE	200

Menu::Menu(float size_x_, float size_y_)
{
  this->size_x = size_x_;
  this->size_y = size_y_;
}

Menu::~Menu()
{
}

void	Menu::one_player(std::list<AObject *> &list)
{
  Map		*m;
  AObject*	temp;
  size_t	size_map;

  size_map = this->IG->get_map();
  m = new Map(size_map, size_map);
  m->createBlocks();
  m->setBlocks();

  m->setIG(this->IG);

  this->IG->push_map(m);
  this->IG->set_step(GAME);

  list.clear();
  temp = new Player("./cube_texture/marvin.fbm/marvin.fbx", PLAYER, m, gdl::Keys::Z, gdl::Keys::S, gdl::Keys::Q, gdl::Keys::D, gdl::Keys::R);
  list.push_front(temp);
  for (size_t i = 0; i < this->IG->get_nb_ia(); i++)
    {  
      list.push_back(new IRobot("./cube_texture/marvin.fbm/marvin.fbx", IA, m, gdl::Keys::Z, gdl::Keys::S, gdl::Keys::Q, gdl::Keys::D, gdl::Keys::R));
    }
  m->spawnPlayers(&list);

  temp = new Plan(size_map, 0, size_map, 0, 0, 0);
  temp->initialize();
  list.push_back(temp);

  this->banzai_.Play();
  this->IG->setMusicStatus(false);

  return ;
}

void	Menu::two_player(std::list<AObject *> &list)
{
  Map		*m;
  std::vector<std::vector<ABlock *> >	v;
  AObject*	temp;
  size_t	size_map;

  size_map = this->IG->get_map();

  m = new Map(size_map, size_map);
  m->createBlocks();
  m->setBlocks();
  v = m->getBlocks();
  m->setIG(this->IG);

  this->IG->push_map(m);
  this->IG->set_step(GAME);

  list.clear();
  temp = new Player("./cube_texture/marvin.fbm/marvin.fbx", PLAYER, m, gdl::Keys::Z, gdl::Keys::S, gdl::Keys::Q, gdl::Keys::D, gdl::Keys::R);
  list.push_front(temp);
  temp = new Player("./cube_texture/marvin.fbm/marvin.fbx", PLAYER, m, gdl::Keys::Up, gdl::Keys::Down, gdl::Keys::Left, gdl::Keys::Right, gdl::Keys::Numpad0);
  list.push_back(temp);

  for (size_t i = 0; i < this->IG->get_nb_ia(); i++)
    list.push_back(new IRobot("./cube_texture/marvin.fbm/marvin.fbx", IA, m, gdl::Keys::Z, gdl::Keys::S, gdl::Keys::Q, gdl::Keys::D, gdl::Keys::R));

  m->spawnPlayers(&list);
  
  temp = new Plan(size_map, 0, size_map, 0, 0, 0);
  temp->initialize();
  list.push_back(temp);

  this->banzai_.Play();
  this->IG->setMusicStatus(false);

  return ;
}

void	Menu::settings(std::list<AObject *> &list)
{
  AObject*	temp;
  Picture*	tmp_picture;
  Text*		tmp_text;

  this->IG->set_step(SETTINGS);

  list.clear();

  temp = new Picture(0.0, 0.0, 1600.0, 900.0, 0, NONE);
  temp->initialize();
  list.push_front(temp);

  tmp_picture = new Picture(-450.0, 15.0, 30.0, 30.0, 1, NB_IA);
  tmp_picture->initialize();
  tmp_picture->setIG(this->IG);
  list.push_back(tmp_picture);


  tmp_picture = new Picture(-200.0, 15.0, 30.0, 30.0, 2, NB_IA);
  tmp_picture->initialize();
  tmp_picture->setIG(this->IG);
  list.push_back(tmp_picture);

  tmp_picture = new Picture(-275.0, -185.0, 30.0, 30.0, 1, MAP);
  tmp_picture->initialize();
  tmp_picture->setIG(this->IG);
  list.push_back(tmp_picture);

  tmp_picture = new Picture(-25.0, -185.0, 30.0, 30.0, 2, MAP);
  tmp_picture->initialize();
  tmp_picture->setIG(this->IG);
  list.push_back(tmp_picture);

  tmp_text = new Text(450, 400, "0", 50, NB_IA);
  tmp_text->initialize();
  tmp_text->setIG(this->IG);
  list.push_back(tmp_text);

  tmp_text = new Text(590, 600, "0", 50, MAP);
  tmp_text->initialize();
  tmp_text->setIG(this->IG);
  list.push_back(tmp_text);

  temp = new Text(300, 70, "SETTINGS", 90, NONE);
  list.push_back(temp);

  temp = new Text(50, 600, "TAILLE MAP", 50, NONE);
  list.push_back(temp);

  temp = new Text(50, 400, "NB IA", 50, NONE);
  list.push_back(temp);

  temp = new Text(80, 800, "echap to return to the menu", 40, NONE);
  list.push_back(temp);
}

void	Menu::highscores(std::list<AObject *> &coucou)
{
  (void)coucou;
  return ;
}

void	Menu::credits(std::list<AObject *> &list)
{
  AObject*	temp;

  this->IG->set_step(SETTINGS);

  list.clear();

  temp = new Picture(0.0, 0.0, 1600.0, 900.0, 0, NONE);
  temp->initialize();
  list.push_front(temp);

  temp = new Text(300, 70, "CREDITS", 40, NONE);
  list.push_back(temp);

  temp = new Text(50, 250, "Antoine Bigotte", 30, NONE);
  list.push_back(temp);

  temp = new Text(50, 300, "Chris Da Costa E Silva", 30, NONE);
  list.push_back(temp);

  temp = new Text(50, 350, "Louis Lecocq", 30, NONE);
  list.push_back(temp);

  temp = new Text(50, 400, "Arthur Rucquois", 30, NONE);
  list.push_back(temp);

  temp = new Text(50, 500, "THANKS TO :", 40, NONE);
  list.push_back(temp);

  temp = new Text(50, 600, "Romain Gerard (INTRODUCTION'S PICTURE)", 30, NONE);
  list.push_back(temp);

  temp = new Text(50, 650, "soundfxcenter.com (SOUND WAV)", 30, NONE);
  list.push_back(temp);

  temp = new Text(80, 800, "echap to return to the menu", 40, NONE);
  list.push_back(temp);

  return ;
}

void	Menu::setIG(InterfaceGraphique *ig)
{
  this->IG = ig;
}

void	Menu::initialize()
{
  if (this->banzai_buffer.LoadFromFile("./Menu_assets/Sound/banzai.wav"))
    this->banzai_.SetBuffer(this->banzai_buffer);


  this->list.insert(std::make_pair("./Menu_assets/1player.jpg", &Menu::one_player));
  this->list.insert(std::make_pair("./Menu_assets/2players.jpg", &Menu::two_player));
  this->list.insert(std::make_pair("./Menu_assets/3settings.jpg", &Menu::settings));
  this->list.insert(std::make_pair("./Menu_assets/4highscores.jpg", &Menu::highscores));
  this->list.insert(std::make_pair("./Menu_assets/5credits.jpg", &Menu::credits));
  this->it = list.begin();
  this->up = true;
  this->down = true;
  this->position_.x = 0.0;
  this->position_.y = 0.0;
  this->position_.z = 0.0;
  this->toDelete = false;
  this->picture_ = gdl::Image::load(this->it->first);
}

int	Menu::update(gdl::GameClock const &gameClock, gdl::Input &input, std::list<AObject*> &coucou)
{
  (void)gameClock;

  if (input.isKeyDown(gdl::Keys::Down) == true && this->down == true)
    {
      it++;
      if (this->it == this->list.end())
	this->it = this->list.begin();
      this->picture_ = gdl::Image::load(this->it->first);
      this->down = false;
    }
  if (input.isKeyDown(gdl::Keys::Up) == true && this->up == true)
    {
      if (this->it == this->list.begin())
	this->it = this->list.end();
      it--;
      this->picture_ = gdl::Image::load(this->it->first);
      this->up = false;
    }
  if (input.isKeyDown(gdl::Keys::Return) == true)
    {
      (this->*it->second)(coucou);
      return (1);
    }
  if (input.isKeyDown(gdl::Keys::Down) == false)
    {
      this->down = true;
    }
  if (input.isKeyDown(gdl::Keys::Up) == false)
    {
      this->up = true;
    }
  return (0);
}

void	Menu::draw(void)
{
  this->picture_.bind();
  glBegin(GL_QUADS);

  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(0.0f, this->size_y / 2 + this->position_.y, (-1 * this->size_x / 2) + this->position_.x);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(0.0f, (-1 * this->size_y / 2) + this->position_.y, (-1 * this->size_x / 2) + this->position_.x);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(0.0f, (-1 * this->size_y / 2) + this->position_.y, (this->size_x / 2) + this->position_.x);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(0.0f, (this->size_y / 2) + this->position_.y, (this->size_x / 2) + this->position_.x);
  glEnd();
}
