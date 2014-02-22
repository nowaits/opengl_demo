#pragma once
#include "gl_on_draw.h"

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