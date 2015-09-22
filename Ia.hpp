//
// Ia.hpp for bomberman in /home/dacost_c/bomberman-2016-rucquo_a/robots
// 
// Made by chris dacostaesilva
// Login   <dacost_c@epitech.net>
// 
// Started on  Mon Jun  3 14:22:46 2013 chris dacostaesilva
// Last update Sat Jun  8 14:32:29 2013 chris dacostaesilva
//



#include "Player.hpp"


class IRobot : public Player
{
public:
  IRobot(const std::string path,Genre type_player, Map *map, gdl::Keys::Key top_, gdl::Keys::Key down_, gdl::Keys::Key left_, gdl::Keys::Key right_, gdl::Keys::Key bombe_);
  virtual ~IRobot();
  void		Ia_play_init();
  void		actualise_map();
  int		update(gdl::GameClock const &gameClock, gdl::Input &input, std::list<AObject*> &list);
  void		marque_up(size_t i, size_t j);
  void		marque_down(size_t i, size_t j);
  void		marque_left(size_t i, size_t j);
  void		marque_right(size_t i, size_t j);
  void		place_danger(size_t i, size_t j);
  void		fake_marque_up(size_t i, size_t j);
  void		fake_marque_down(size_t i, size_t j);
  void		fake_marque_left(size_t i, size_t j);
  void		fake_marque_right(size_t i, size_t j);
  void		actualise_intel_map();
  void          Play_like_an_IA(gdl::GameClock const &gameClock, std::list<AObject*> &list);
  int		search_up();
  int		search_down();
  int		search_left();
  int		search_right();
  void		search_path_protect();
  void		search_path_offensiv();
  void		go_run(gdl::GameClock const &gameClock, std::list<AObject*> &list);
  void		print_map();
  int		search_up_walk();
  int		search_left_walk();
  int		search_right_walk();
  int		search_down_walk();
  void		Marque_fake_bombe(size_t i, size_t j);
protected:
  bool						map_ia_done;
  std::vector<std::vector<int> >		*intel_map;
  int						dir;
  size_t					iMax;
  size_t					jMax;
  int						path_short;
  int						path_long;
  bool						take_bomb;
  size_t					tmp;
  size_t					tmp_y;
  bool						rec;
};
