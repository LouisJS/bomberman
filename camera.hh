//
// camera.hh for test in /home/bigott_a/Documents/Bomberman/Projet/test_lib
// 
// Made by bigott-a
// Login   <bigott_a@epitech.net>
// 
// Started on  Tue Apr 30 14:08:27 2013 bigott-a
// Last update Wed Jun  5 15:58:14 2013 louis lecocq
//

#ifndef __CAMERA_HH__
#define __CAMERA_HH__

#include "./lib/libgdl_gl-2012.4/include/Clock.hpp"
#include "./lib/libgdl_gl-2012.4/include/Color.hpp"
#include "./lib/libgdl_gl-2012.4/include/Game.hpp"
#include "./lib/libgdl_gl-2012.4/include/GameClock.hpp"
#include "./lib/libgdl_gl-2012.4/include/Image.hpp"
#include "./lib/libgdl_gl-2012.4/include/Input.hpp"
#include "./lib/libgdl_gl-2012.4/include/Model.hpp"
#include "./lib/libgdl_gl-2012.4/include/Window.hpp"

#include <GL/glu.h>
#include <GL/gl.h>

#include "Vector3f.hh"

class Camera
{

public:

  Camera(void);
  Camera(float xp, float yp, float zp, float xr, float yr, float zr);
  Camera(Vector3f position, Vector3f rotation);
  void	initialize(float height, float width);
  void	updatePosition(float xp, float yp, float zp, float xr, float yr, float zr);
private:

  Vector3f position_;
  Vector3f rotation_;
};

#endif
