#pragma once

#include "..\gl_draw\draw_method.h"

class DrawSample 
  : public DrawMethod {
public:
  virtual void OnDraw() override;
};

// 二十四面体
class DrawIcosahedrons
  : public DrawMethod {
public:
  virtual void OnDraw() override;
};