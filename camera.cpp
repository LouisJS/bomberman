//
// camera.cpp for test in /home/bigott_a/Documents/Bomberman/Projet/test_lib
// 
// Made by bigott-a
// Login   <bigott_a@epitech.net>
// 
// Started on  Tue Apr 30 14:08:19 2013 bigott-a
// Last update Wed Jun  5 15:58:08 2013 louis lecocq
//

#include "camera.hh"
#include "Vector3f.hh"

Camera::Camera(void) : position_(20, 20, 0), rotation_(0, 0, 0)
{
}

Camera::Camera(float xp, float yp, float zp, float xr, float yr, float zr)
{
  this->position_.x = xp;
  this->position_.y = yp;
  this->position_.z = zp;

  this->rotation_.x = xr;
  this->rotation_.y = yr;
  this->rotation_.z = zr;
}

Camera::Camera(Vector3f position, Vector3f rotation) : position_(position.x, position.y, position.y), rotation_(rotation.x, rotation.y, rotation.z)
{

}

void	Camera::initialize(float height, float width)
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70.0f, width / height, 1.0f, 10000.0f);
  gluLookAt(this->position_.x, this->position_.y, this->position_.z,
	    this->rotation_.x, this->rotation_.y, this->rotation_.z,
	    0.0, 1.0, 0.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
}

void	Camera::updatePosition(float xp, float yp, float zp, float xr, float yr, float zr)
{
  this->position_.x = xp;
  this->position_.y = yp;
  this->position_.z = zp;
  this->rotation_.x = xr;
  this->rotation_.y = yr;
  this->rotation_.z = zr;
}
