#pragma once

#include "..\gl_draw\draw_method.h"

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