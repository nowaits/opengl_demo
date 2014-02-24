#pragma once
class DrawMethod {
public:
  virtual ~DrawMethod() {};
  virtual void OnInit() = 0;
  virtual void OnDraw() = 0;
  virtual void OnTimer() = 0;
};