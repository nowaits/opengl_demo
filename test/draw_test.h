#pragma once

#include "..\gl_draw\draw_method.h"

class DrawSample 
  : public DrawMethod {
public:

  virtual void OnInit() override;
  virtual void OnDraw() override;
  virtual void OnTimer() override{};
};

// 二十四面体
class DrawIcosahedrons
  : public DrawMethod {
public:

  virtual void OnInit() override;
  virtual void OnDraw() override;
  virtual void OnTimer() override{};
};

// cube
class DrawCube 
  : public DrawMethod {
public:

  enum DrawWays{
    VERTEXS,        // original ways
    DRAW_ARRAYS,    // vertex arrays
    VBO,            // buffer object
  };

  DrawCube(DrawWays draw_ways = VBO);
  virtual void OnInit() override;
  virtual void OnDraw() override;
  virtual void OnTimer() override;

private:
  void DrawInner();

private:
  float     roate_angle_;
  DrawWays  draw_ways_;
};