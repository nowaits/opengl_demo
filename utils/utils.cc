#include <fstream>

#include "utils.h"
#include <algorithm>
#include <assert.h>
namespace dcodec_utils {

  bool load_file(const wchar_t* file_name, std::vector<unsigned char>& buffer) {
    std::ifstream ifs(file_name, std::ios::binary);
    if (!ifs.is_open())
      return false;
    ifs.exceptions( std::ifstream::eofbit | std::ifstream::failbit | std::ifstream::badbit );  

    int current_pos = ifs.tellg();
    ifs.seekg(0, std::ios_base::end);
    unsigned long file_size = ifs.tellg();
    ifs.seekg(current_pos);

    buffer.resize(file_size);

    ifs.read((char *)&buffer[0], buffer.size());
    return true;
  }

  bool save_file(const wchar_t* file_name, std::vector<unsigned char>& buffer) {
    if (buffer.empty())
      return false;

    std::ofstream ifs(file_name, std::ios::binary);
    ifs.exceptions( std::ifstream::eofbit | std::ifstream::failbit | std::ifstream::badbit );  

    ifs.write((char *)&buffer[0], buffer.size());
    return true;
  }

  bool parse_bmp(const std::vector<unsigned char>& buffer, BitmapData& output) {
    int pos = 0;

    if (buffer.size() <= sizeof(BITMAPFILEHEADER))
      return false;

    BITMAPFILEHEADER* pbh = (BITMAPFILEHEADER*)(&buffer[pos]);
    pos += sizeof(BITMAPFILEHEADER);

    if (pbh->bfType != 0x4d42 || pbh->bfSize != buffer.size())
      return false;

    BITMAPINFOHEADER* bmp_header = (BITMAPINFOHEADER*)(&buffer[pos]);

    pos = pbh->bfOffBits;

    output.w = bmp_header->biWidth;
    output.h = bmp_header->biHeight;
    output.pixel_bytes = bmp_header->biBitCount/8;
    output.data.assign(&buffer[pos], 
      &buffer[pos + bmp_header->biWidth * bmp_header->biHeight * output.pixel_bytes]);
    return true;
  }

  bool save_bmp(const BitmapData& input, std::vector<unsigned char>& output) {

    if (input.w * input.h * input.pixel_bytes  != input.data.size())
      return false;

    BITMAPFILEHEADER bh = {0};
    bh.bfType = 0x4d42;  //bitmap  
    bh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD);
    bh.bfSize = bh.bfOffBits + input.data.size();

    BITMAPINFOHEADER bmp_header = {sizeof(BITMAPINFOHEADER),0};
    bmp_header.biWidth = input.w;
    bmp_header.biHeight = input.h;
    bmp_header.biPlanes = 1;
    bmp_header.biBitCount = input.pixel_bytes * 8;
    bmp_header.biSizeImage = input.w * input.h ;

    RGBQUAD plane[256] = {0};

    for(int i = 0; i < _countof(plane); i ++) {
      plane[i].rgbBlue = i;
      plane[i].rgbGreen = i;
      plane[i].rgbRed = i;
    }

    output.resize(bh.bfSize);

    int pos = 0;

    ::memcpy(&output[pos], &bh, sizeof(BITMAPFILEHEADER));
    pos += sizeof(BITMAPFILEHEADER);

    ::memcpy(&output[pos], &bmp_header, sizeof(BITMAPINFOHEADER));

    pos += sizeof(BITMAPINFOHEADER);

    ::memcpy(&output[pos], plane, sizeof(RGBQUAD) * _countof(plane));

    pos = bh.bfOffBits;
    ::memcpy(&output[pos], &input.data[0], input.data.size());
    return true;
  }

  HBITMAP CreateWinBitmap(const BitmapData& bitmap) {
    std::vector<unsigned char> raw_data;
    if (!save_bmp(bitmap, raw_data))
      return NULL;

    int pos = 0;

    BITMAPFILEHEADER* pbh = (BITMAPFILEHEADER*)(&raw_data[pos]);
    pos += sizeof(BITMAPFILEHEADER);

    if (pbh->bfType != 0x4d42 || pbh->bfSize != raw_data.size())
      return false;

    BITMAPINFOHEADER* bmp_header = ( BITMAPINFOHEADER*)(&raw_data[pos]);

    HDC dc = GetDC(NULL);
    HBITMAP hBitmap = CreateDIBitmap(dc,	bmp_header, 
      (LONG)CBM_INIT,
      &raw_data[pbh->bfOffBits],
      (BITMAPINFO*)bmp_header, DIB_RGB_COLORS);

    ReleaseDC(NULL, dc);

    return hBitmap;
  }

}