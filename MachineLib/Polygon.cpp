/**
 * \file Polygon.cpp
 *
 * \author Charles Owen
 */

#include "pch.h"
#include "Polygon.h"

using namespace Gdiplus;
using namespace std;

/// Degrees in a circle
const double Circle = 360;

/**
 * Constructor
 */
CPolygon::CPolygon()
{
    // Create an initial brush in black
    mBrush = make_shared<Gdiplus::SolidBrush>(Color::Black);
}

/**
 * Destructor
 */
CPolygon::~CPolygon()
{
}


/**
 * Create a rectangle
 * \param x Left side X
 * \param y Bottom left Y
 * \param wid Width of the rectangle
 * \param hit Height of the rectangle
 */
void CPolygon::Rectangle(int x, int y, int wid, int hit)
{
    AddPoint(x, y);
    AddPoint(x, y-hit);
    AddPoint(x+wid, y-hit);
    AddPoint(x+wid, y);
}

/**
 * Create a rectangle
 * \param x Left side X
 * \param y Bottom left Y
 * \param wid Width of the rectangle
 * \param hit Height of the rectangle
 */
void CPolygon::Rectangle(double x, double y, double wid, double hit)
{
    Rectangle((int)(x + 0.5), (int)(y + 0.5), (int)(wid + 0.5), (int)(hit + 0.5));
}


/**
 * Create a centered square at location 0,0
 * \param size Width and height of the square
 */
void CPolygon::CenteredSquare(int size)
{
    Rectangle(-size / 2, size / 2, size, size);
}


/**
 * Set the color of the polygon. If we set a color, images are not used.
 * \param color A Gdiplus Color object.
 */
void CPolygon::SetColor(Gdiplus::Color color)
{
    mBrush = make_shared<Gdiplus::SolidBrush>(color);
    mTextureBrush = nullptr;
}

/**
 * Set an image we will use as a texture for the polygon
 * \param filename Image filename
 */
void CPolygon::SetImage(std::wstring filename)
{
    mTexture = shared_ptr<Gdiplus::Bitmap>(Bitmap::FromFile(filename.c_str()));
    if (mTexture->GetLastStatus() != Ok)
    {
        AfxMessageBox((wstring(L"Failed to open ") + filename).c_str());
    }
    mTextureBrush = make_shared<Gdiplus::TextureBrush>(mTexture.get());
    mBrush = mTextureBrush;
}



/**
 * Draw the polygon
 * \param graphics Gdiplus graphics object
 * \param x X location to draw in pixels
 * \param y Y location to draw in pixels
 */
void CPolygon::DrawPolygon(Gdiplus::Graphics *graphics, int x, int y)
{
    auto saveSM = graphics->GetSmoothingMode();
    graphics->SetSmoothingMode(SmoothingMode::SmoothingModeHighQuality);

    auto save = graphics->Save();
    graphics->TranslateTransform((REAL)x, (REAL)y);
    graphics->RotateTransform((REAL)(mRotation * Circle));

    if (mTextureBrush != nullptr)
    {
        ConfigureTextureBrush();
    }

    graphics->FillPolygon(mBrush.get(), &mPoints[0], mPoints.size());

    graphics->Restore(save);

    graphics->SetSmoothingMode(saveSM);
}

/**
 * Configure a brush to use for the texture map. 
 *
 * We only do this if we are using a texture map. It makes the 
 * bounds of the texture map to the extents of the polygon.
 */
void CPolygon::ConfigureTextureBrush()
{
    //
    // Find minimum and maximum x and y values
    //
    PointF min = mPoints[0];
    PointF max = mPoints[0];
    for (PointF p : mPoints)
    {
        if (p.X < min.X)
        {
            min.X = p.X;
        }

        if (p.X > max.X)
        {
            max.X = p.X;
        }

        if (p.Y < min.Y)
        {
            min.Y = p.Y;
        }

        if (p.Y > max.Y)
        {
            max.Y = p.Y;
        }
    }

    mTextureBrush->ResetTransform();
    mTextureBrush->TranslateTransform(min.X, min.Y);
    mTextureBrush->ScaleTransform((max.X - min.X) / mTexture->GetWidth(),
        (max.Y - min.Y) / mTexture->GetHeight());
}