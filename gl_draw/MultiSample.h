#pragma once
#include <Windows.h>

class MultiSample {
public:
  MultiSample();
  ~MultiSample();
  bool InitMultiSample(HWND hwnd);

  bool ExtentionSurpported(){ return multisampleSupportted;}

  int GetMultiSampleFormat(){ return MultiSampleFormat;}

  void SetMultiSample(UINT sample){Multisample = sample; }

  UINT GetSupportedFormatNum(){ return numofFormats;}
  int GetSupportedFormats(UINT i){ return i < numofFormats ? pixelformat[i] : 0;}

private:
  bool WGLisExtensionSupported(const char *extension);

  UINT Multisample;
  bool multisampleSupportted;
  int MultiSampleFormat;
  UINT numofFormats;
  int pixelformat[20];
};