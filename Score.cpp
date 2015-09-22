//
// Score.cpp for Bomberman in /home/couillere/cpp/bomberman
// 
// Made by arthur rucquois
// Login   <rucquo_a@epitech.net>
// 
// Started on  Mon May  6 14:40:51 2013 arthur rucquois
// Last update Wed Jun  5 16:27:01 2013 louis lecocq
//

#include "Score.hh"

void			Score::setScore(const unsigned int val)
{
  this->score = val;
}

void			Score::addPoints(const unsigned int val)
{
  this->score += val;
  if (this->score > 9999999)
    this->score = 9999999;
}

unsigned int	Score::getScore() const
{
  return (this->score);
}

void			Score::setName(const char c1, const char c2, const char c3)
{
  this->name[0] = c1;
  this->name[1] = c2;
  this->name[2] = c3;
  this->name[3] = 0;
}

const char		*Score::getName()
{
  return (this->name);
}

void			Score::addScore(std::vector<Score> *tab)
{
  tab->push_back(*this);
  while (!(Score::sorted(tab)))
    this->sortTab(tab);
  tab->pop_back();
}

bool			Score::sorted(const std::vector<Score> *tab)
{
  size_t			i = 0;

  while (i + 1 < tab->size())
    {
      if ((*tab)[i].getScore() < (*tab)[i + 1].getScore())
	return (false);
      i++;
    }
  return (true);
}

void			Score::sortTab(std::vector<Score> *tab)
{
  size_t	i = 0;
  char		s[3];
  unsigned int	score;

  while (i + 1 < tab->size())
    {
      if ((*tab)[i].getScore() < (*tab)[i + 1].getScore())
	{
	  score = (*tab)[i].getScore();
	  s[0] = (*tab)[i].getName()[0];
	  s[1] = (*tab)[i].getName()[1];
	  s[2] = (*tab)[i].getName()[2];
	  (*tab)[i].setScore((*tab)[i + 1].getScore());
	  (*tab)[i].setName((*tab)[i + 1].getName()[0], (*tab)[i + 1].getName()[1], (*tab)[i + 1].getName()[2]);
	  (*tab)[i + 1].setScore(score);
	  (*tab)[i + 1].setName(s[0], s[1], s[2]);
	}
      i++;
    }
}

void			Score::displayTab(std::vector<Score> *tab)
{
  size_t		i = 0;

  while (!(Score::sorted(tab)))
    this->sortTab(tab);
  while (i < tab->size())
    {
      std::cout << i + 1 << ". " << (*tab)[i].getName() << " ----- " << (*tab)[i].getScore() << std::endl;
      i++;
    }
}

Score::Score()
{
  this->score = 0;
  this->name[0] = 'A';
  this->name[1] = 'A';
  this->name[2] = 'A';
  this->name[3] = 0;
}

Score::~Score()
{
}
