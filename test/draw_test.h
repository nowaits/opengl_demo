#pragma once

#include "..\gl_draw\draw_method.h"

class DrawSample 
  : public DrawMethod {
public:

  virtual void OnInit() override;
  virtual void OnDraw() override;
};

// 二十四面体
class DrawIcosahedrons
  : public DrawMethod {
public:

  virtual void OnInit() override;
  virtual void OnDraw() override;
};

// cube
class DrawCube 
  : public DrawMethod {
public:
  DrawCube();
  virtual void OnInit() override;
  virtual void OnDraw() override;

private:
  bool user_vertex_obj_;
};