#pragma once
#include "gl_on_draw.h"

class DrawSample 
  : public DrawMethod {
public:
  virtual void OnDraw() override;
};

// ��ʮ������
class DrawIcosahedrons
  : public DrawMethod {
public:
  virtual void OnDraw() override;
};