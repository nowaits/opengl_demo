#pragma once
#include <vector>
#include <Windows.h>

namespace dcodec_utils {
  struct BitmapData {
    int w;
    int h;
    int pixel_bytes;
    std::vector<unsigned char> data;

    BitmapData() : w(0), h(0) {
    }
  };

  bool load_file(const wchar_t* file_name, std::vector<unsigned char>& buffer);

  bool save_file(const wchar_t* file_name, std::vector<unsigned char>& buffer);

  bool parse_bmp(const std::vector<unsigned char>& buffer, BitmapData& output);

  bool save_bmp(const BitmapData& input, std::vector<unsigned char>& output);

  HBITMAP CreateWinBitmap(const BitmapData& bitmap);
}