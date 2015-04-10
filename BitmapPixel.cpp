#include "BitmapPixel.h"

BitmapPixel::BitmapPixel(uint32_t row, uint32_t column, uint32_t chanle) :
    m_row(row),
    m_column(column),
    m_chanles(chanle)
{
    uint32_t newSize = m_row * m_column * m_chanles;
    if (newSize > m_data.size())
    {
        m_data.resize(newSize);
    }
}

BitmapPixel::~BitmapPixel()
{

}

uint32_t BitmapPixel::GetPixel(int row, int column)
{
    uint32_t color = 0;
    if (((row >= 0) && (column >= 0)) &&
        ((row < m_row) && (column < m_column)))
    {
        memcpy(&color, GetRowData(row) + (column * m_chanles), sizeof(color));
    }
    return color;
}

void BitmapPixel::SetPixel(int row, int column, uint32_t color)
{
    if (((row >= 0) && (column >= 0)) &&
        ((row < m_row) && (column < m_column)))
    {
        memcpy(GetRowData(row) + (column * m_chanles), &color, sizeof(color));
    }
}

void BitmapPixel::Zoom(int width, int height)
{
    double xratio = (double)m_column / width;
    double yratio = (double)m_row / height;

    BitmapPixel matTemp(height, width, m_chanles);

    for (int32_t i = 0; i < width; i++)
    {
        for (int32_t j = 0; j < height; j++)
        {
            double xreal = i * xratio;
            double yreal = j * yratio;
            int x = (int)(xreal + 0.5);
            int y = (int)(yreal + 0.5);

            if (x < 0.000001)
            {
                x = (int)((xratio + 0.5) / 2);
            }
            if (y < 0.000001)
            {
                y = (int)((xratio + 0.5) / 2);
            }

            uint32_t color = GetPixel(y, x);
            matTemp.SetPixel(j, i, color);
        }
    }

    m_data.clear();
    m_data = matTemp.m_data;

    m_row = height;
    m_column = width;
}

void BitmapPixel::Gray()
{
    for (int i = 0; i < m_row; i++)
    {
        for (int j = 0; j < m_column; j++)
        {
            uint32_t color = GetPixel(i, j);
            uint8_t a = (uint8_t)((color & 0xFF000000) >> 24);
            uint8_t r = (uint8_t)((color & 0x00FF0000) >> 16);
            uint8_t g = (uint8_t)((color & 0x0000FF00) >> 8);
            uint8_t b = (uint8_t)(color & 0x000000FF);

            uint8_t gray = (r * 30 + g * 59 + b * 11) / 100;

            color = 0;
            color |= a << 24;       // A
            color |= gray << 16;    // R
            color |= gray << 8;     // G
            color |= gray;          //B

            SetPixel(i, j, color);
        }
    }
}

uint32_t BitmapPixel::Mean()
{
    uint64_t sumcolors = 0;
    for (int i = 0; i < m_row; i++)
    {
        for (int j = 0; j < m_column; j++)
        {
            sumcolors += GetPixel(i, j);
        }
    }
    return (uint32_t)(sumcolors / (m_row * m_column));
}

void BitmapPixel::GetGrayMask(uint32_t mean, BitmapPixel& pixels)
{
    for (int i = 0; i < m_row; i++)
    {
        for (int j = 0; j < m_column; j++)
        {
            uint32_t color = GetPixel(i, j);
            if (color > mean)
            {
                color = 0xFFFFFFFF;
            }
            else
            {
                color = 0x00000000;
            }
            pixels.SetPixel(i, j, color);
        }
    }
}

uint8_t* BitmapPixel::GetRowData(int32_t row)
{
    if ((row >= 0) && (row < m_row))
    {
        return (&m_data[0] + (row * m_column * m_chanles));
    }
    return NULL;
}
