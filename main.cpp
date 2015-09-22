//
// main.cpp for  in /home/couillere/cpp/bomberman
// 
// Made by arthur rucquois
// Login   <rucquo_a@epitech.net>
// 
// Started on  Thu May  2 11:29:09 2013 arthur rucquois
// Last update Sun Jun  9 17:13:02 2013 louis lecocq
//

#include "Map.hh"
#include "Score.hh"

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include "InterfaceGraphique.hh"
#include "Object.hpp"
#include "Player.hpp"
#include "Picture.hpp"
#include "Text.hpp"
#include "Menu.hpp"
#include "Ia.hpp"
#include "Introduction.hpp"

#define	SIZE_CUBE	200

void	init_game()
{
  InterfaceGraphique	test;
  Introduction*		intro = new Introduction(0.0, 0.0, 1600.0, 900.0);

  intro->setIG(&test);
  test.push(intro);
  test.run();
}

int			conv(char *str)
{
  int			ret;
  std::stringstream	s;

  s << str;
  s >> ret;
  return (ret);
}

bool	checkEnv(char **env)
{
  int	i = 0;

  if (!env)
    return (false);
  while (env[i] != NULL)
    {
      if (strcmp(env[i], "DISPLAY=:0") == 0)
	return (true);
      i++;
    }
  return (false);
}

int	main(int argc, char **argv, char **env)
{
  (void)argc;
  (void)argv;

  if (!checkEnv(env))
    return (0);
  init_game();
  return (0);
}
