//
// Map.hh for Bomberman in /home/couillere/cpp/bomberman
// 
// Made by arthur rucquois
// Login   <rucquo_a@epitech.net>
// 
// Started on  Tue Apr 30 15:01:02 2013 arthur rucquois
// Last update Sat Jun  8 14:55:14 2013 chris dacostaesilva
//

#ifndef __MAP_HH__
#define __MAP_HH__

#include "include.h"
#include "Error.hh"
#include "ABlock.hh"
#include "Player.hpp"
#include "Object.hpp"
#include "InterfaceGraphique.hh"

class	Player;

class	Map
{
private:
  size_t					xLen;
  size_t					yLen;
  std::vector<std::vector<ABlock *> >		blocks;
  std::vector<Player *>				players;

public:
  size_t					getXLen() const;
  size_t					getYLen() const;
  void						createBlocks();
  void						setBlocks();
  const std::vector<std::vector<ABlock *> >	getBlocks();
  void						clearBlocks();
  void						setIG(InterfaceGraphique *);
  void						setBlock(const size_t, const size_t, const Type);
  size_t					validSlots() const;
  void						bonusPop(const size_t x, const size_t y);
  void						spawnPlayers(std::list<AObject *> *);
  void						spawnRoom(const size_t, const size_t);
  void						addBomb(const size_t, const size_t);
  void						explosion(const unsigned int, const size_t, const size_t);
  void						explosionLeft(const unsigned int, const size_t, const size_t);
  void						explosionRight(const unsigned int, const size_t, const size_t);
  void						explosionUp(const unsigned int, const size_t, const size_t);
  void						explosionDown(const unsigned int, const size_t, const size_t);
  void						cleanLeft(const unsigned int, const size_t, const size_t);
  void						cleanRight(const unsigned int, const size_t, const size_t);
  void						cleanUp(const unsigned int, const size_t, const size_t);
  void						cleanDown(const unsigned int, const size_t, const size_t);
  InterfaceGraphique				*IG;
  bool                  getCheck() const ;
public:
  Map(const size_t, const size_t);
  ~Map();
  bool	check;
};

#endif
