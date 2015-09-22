//
// Score.hh for Bomberman in /home/couillere/cpp/bomberman
// 
// Made by arthur rucquois
// Login   <rucquo_a@epitech.net>
// 
// Started on  Mon May  6 14:40:59 2013 arthur rucquois
// Last update Wed Jun  5 15:45:05 2013 louis lecocq
//

#ifndef __SCORE_HH__
#define __SCORE_HH__

#include "include.h"

class	Score
{
private:
  char		name[4];
  unsigned int	score;

private:
  void			setScore(const unsigned int);

public:
  void			addPoints(const unsigned int);
  unsigned int		getScore() const;
  void			setName(const char, const char, const char);
  const char		*getName();
  void			addScore(std::vector<Score> *);
  static bool		sorted(const std::vector<Score> *);
  void			sortTab(std::vector<Score> *);
  void			displayTab(std::vector<Score> *);

public:
  Score();
  ~Score();
};

#endif
