#include "ImgHash.h"
#include "BitmapPixel.h"

#include <vector>

bool HashHbitmap(const std::wstring& filePath, std::wstring& pHash)
{
    HBITMAP hBMP = (HBITMAP)::LoadImage(NULL, filePath.data(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    if (hBMP != NULL)
    {
        BITMAP bmp = { 0 };
        ::GetObject(hBMP, sizeof(BITMAP), &bmp);
        int nChannels = 0;
        if (bmp.bmBitsPixel == 1)
        {
            nChannels = 1;
        }
        else
        {
            nChannels = bmp.bmBitsPixel / 8;
        }

        BitmapPixel pixels(bmp.bmHeight, bmp.bmWidth, nChannels);

        ::GetBitmapBits(hBMP, bmp.bmHeight*bmp.bmWidth*nChannels, &pixels.m_data[0]);

        // Reduce size
        pixels.Zoom(8, 8);
        // Reduce color
        pixels.Gray();
        // Compute the average value
        uint32_t mean = pixels.Mean();
        BitmapPixel pixelMask(pixels.m_row, pixels.m_column, pixels.m_chanles);
        pixels.GetGrayMask(mean, pixelMask);
        // Construct the hash
        std::wstring hash(64, '\0');
        int index = 0;
        for (int i = 0; i < pixelMask.m_row; i++)
        {
            for (int j = 0; j < pixelMask.m_column; j++)
            {
                uint32_t color = pixelMask.GetPixel(i, j);
                if ((color & 0x00FFFFFF) == 0)
                {
                    hash[index++] = '1';
                }
                else
                {
                    hash[index++] = '0';
                }
            }
        }
        pHash = hash;

        ::DeleteObject(hBMP);
        return true;
    }

    return false;
}

int32_t HanmingDistance(const std::wstring &a, const std::wstring &b, uint32_t length /* = 64 */)
{
    if ((a.length() != length) || (b.length() != length))
    {
        return -1;
    }

    int distance = 0;
    for (uint32_t i = 0; i < length; i++)
    {
        if (a[i] != b[i])
        {
            distance++;
        }
    }
    return distance;
}
