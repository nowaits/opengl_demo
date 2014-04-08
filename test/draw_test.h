#pragma once

#include "..\gl_draw\draw_method.h"
#include <vector>
#include <string>

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

// texture
class DrawTexture
  : public DrawMethod {
public:

  enum DrawWays{
    VERTEXS,        // original ways
    DRAW_ARRAYS,    // vertex arrays
    VBO,            // buffer object
  };

  DrawTexture(DrawWays draw_ways = DRAW_ARRAYS);
  virtual void OnInit() override;
  virtual void OnDraw() override;
  virtual void OnTimer() override;

private:
  bool LoadGLTextures(const std::vector<std::wstring>& files);

private:
  std::vector<unsigned int> textures_;

  float     roate_angle_;
  int w_;
  int h_;
  DrawWays  draw_ways_;
};