#ifndef __BITMAPPIXEL__
#define __BITMAPPIXEL__ 1

#include <cstdint>
#include <vector>

class BitmapPixel
{
public:
    BitmapPixel(uint32_t row, uint32_t column, uint32_t chanle);
    BitmapPixel(const BitmapPixel&) = default;
    BitmapPixel &operator = (const BitmapPixel&) = default;
    ~BitmapPixel();

    uint32_t GetPixel(int row, int column);
    void SetPixel(int row, int column, uint32_t color);

    void Zoom(int width, int height);
    void Gray();
    uint32_t Mean();
    void GetGrayMask(uint32_t mean, BitmapPixel& pixels);

private:

    inline uint8_t* GetRowData(int32_t row);

public:

    int m_row;
    int m_column;
    int m_chanles;
    std::vector<uint8_t> m_data;
};

#endif // !__BITMAPPIXEL__
