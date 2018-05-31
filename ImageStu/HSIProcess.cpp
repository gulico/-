// HSIProcess.cpp: implementation of the CHSIProcess class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "imagestu.h"
#include "HSIProcess.h"
#include "BaseColorInfo.h"
#include <cmath>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHSIProcess::CHSIProcess(CBaseColorInfo *_oldimg, int _width, int _height)
{
	width = _width;
	height = _height;
	int size = width * height;
	img = new CBaseColorInfo[size];
	oldimg = new CBaseColorInfo[size];

	for(int i=0; i<size; i++){
		img[i] = _oldimg[i];	
		oldimg[i] = _oldimg[i];
	}
}

CHSIProcess::~CHSIProcess()
{
	
}
void CHSIProcess::HSIToRGB()
{
	int size = width * height;

	for(int j = 0;j < size;++ j)
	{
		CBaseColorInfo info = oldimg[j];
		double r = info.GetRed() / 255.0;
		double g = info.GetGreen() / 255.0;
		double b = info.GetBlue() / 255.0;
		double min = r;
		
		if (min > g)
			min = g;
		if(min > b)
			min = b;

		double i = 1.0 * (r + g + b) / 3;
		double s = 0;
		double angle = 0.0;
		if(r == g && r == b && g == b)
			s = 0;
		else
			s = 1 - 3.0 * min / (r + g + b);
		
		if(r == g && r == b && g == b)
			angle = 0;
		else
			angle = acos((r - g + r - b)/ 2.0 / sqrt((r - g) * (r - g) + (r - b) * (g - b)));
		double h = 0.0;
		if(b <= g)
			h = angle;
		else
			h = 2 * PI - angle;

		img[j] = CBaseColorInfo(h * 255 / (2 * PI), s * 255, i * 255);
	}
}

void CHSIProcess::RGBToHSI()
{
	int size = width * height;

	for(int j = 0;j < size;++ j)
	{
		CBaseColorInfo info = oldimg[j];
		double r = info.GetRed() / 255.0;
		double g = info.GetGreen() / 255.0;
		double b = info.GetBlue() / 255.0;
		double min = r;
		
		if (min > g)
			min = g;
		if(min > b)
			min = b;

		double i = 1.0 * (r + g + b) / 3;
		double s = 0;
		double angle = 0.0;
		if(r == g && r == b && g == b)
			s = 0;
		else
			s = 1 - 3.0 * min / (r + g + b);
		
		if(r == g && r == b && g == b)
			angle = 0;
		else
			angle = acos((r - g + r - b)/ 2.0 / sqrt((r - g) * (r - g) + (r - b) * (g - b)));
		double h = 0.0;
		if (r == g && r == b && g == b)
			h = 0.0;
		else
		{
			if(b <= g)
				h = angle ;
			else
				h = 2 * PI - angle ;
		}

		//h = h / PI * 180;
		if (h < 2.0 * PI / 3)
		{
			r = 1.0 * i * (1 + s * cos(h) / cos(PI / 3.0 - h));
			g = 3 * i - r - b;	
			b = 1.0 * i * (1 - s);
		}
		else if (h < 4.0 * PI / 3 && h > 2.0 * PI / 3)
		{
			g = 1.0 * i * (1 + s * cos(h - 2.0 * PI / 3) / cos(PI - h));
			b = 3.0 * i - r - g;
			r = i * (1 - s);
		}
		else if(h < 2.0 * PI && h > 4.0 * PI / 3)
		{
			b = 1.0 * i * (1 + s * cos(h - 4 * PI / 3) / cos(5.0 * PI / 3 - h));
			r = 3 * i - g - b;
			g = 1.0 * i * (1 - s);		
		}
		if(s==0){
			 b = g = r;
		}
		img[j] = CBaseColorInfo(r * 255.0, g * 255.0, b * 255.0);
	}
	
}

void CHSIProcess::AddH()
{
	int size = width * height;

	for(int j = 0;j < size;++ j)
	{
		CBaseColorInfo info = oldimg[j];
		double r = info.GetRed() / 255.0;
		double g = info.GetGreen() / 255.0;
		double b = info.GetBlue() / 255.0;
		double min = r;
		
		if (min > g)
			min = g;
		if(min > b)
			min = b;

		double i = 1.0 * (r + g + b) / 3;
		double s = 0;
		double angle = 0.0;
		if(r == g && r == b && g == b)
			s = 0;
		else
			s = 1 - 3.0 * min / (r + g + b);
		
		if(r == g && r == b && g == b)
			angle = 0;
		else
			angle = acos((r - g + r - b)/ 2.0 / sqrt((r - g) * (r - g) + (r - b) * (g - b)));
		double h = 0.0;
		if(b <= g)
			h = angle;
		else
			h = 2 * PI - angle;

		h = h  + PI / 3;
		if(h >= 2 * PI)
			h = 0;

		if (h < 2.0 * PI / 3)
		{
			b = 1.0 * i * (1 - s);
			r = 1.0 * i * (1 + s * cos(h) / cos(PI / 3.0 - h));
			g = 3 * i - r - b;	
		}
		else if (h < 4.0 * PI / 3 && h > 2.0 * PI / 3)
		{
			h = h - 2.0 * PI / 3;
			r = i * (1 - s);
			g = 1.0 * i * (1 + s * cos(h) / cos(PI / 3.0 - h));
			b = 3.0 * i - r - g;
		}
		else if(h < 2.0 * PI && h > 4.0 * PI / 3)
		{
			h = h - 4.0 * PI / 3;
			b = 1.0 * i * (1 + s * cos(h) / cos(PI / 3.0 - h));
			r = 3 * i - g - b;
		}
		if(s==0){
			 b = g = r;
		}
		img[j] = CBaseColorInfo(r * 255.0, g * 255.0, b * 255.0);
	}
}

void CHSIProcess::ReduceI()
{
	int size = width * height;

	for(int j = 0;j < size;++ j)
	{
		CBaseColorInfo info = oldimg[j];
		double r = info.GetRed() / 255.0;
		double g = info.GetGreen() / 255.0;
		double b = info.GetBlue() / 255.0;
		double min = r;
		
		if (min > g)
			min = g;
		if(min > b)
			min = b;

		double i = 1.0 * (r + g + b) / 3;
		double s = 0;
		double angle = 0.0;
		if(r == g && r == b && g == b)
			s = 0;
		else
			s = 1 - 3.0 * min / (r + g + b);
		
		if(r == g && r == b && g == b)
			angle = 0;
		else
			angle = acos((r - g + r - b)/ 2.0 / sqrt((r - g) * (r - g) + (r - b) * (g - b)));
		double h = 0.0;
		if(b <= g)
			h = angle;
		else 
			h = 2 * PI - angle;

		
		i = i - i * 0.5;
		if (h < 2.0 * PI / 3)
		{
			b = 1.0 * i * (1 - s);
			r = 1.0 * i * (1 + s * cos(h) / cos(PI / 3.0 - h));
			g = 3 * i - r - b;	
		}
		else if (h < 4.0 * PI / 3 && h > 2.0 * PI / 3)
		{
			h = h - 2.0 * PI / 3;
			r = i * (1 - s);
			g = 1.0 * i * (1 + s * cos(h) / cos(PI / 3.0 - h));
			b = 3.0 * i - r - g;
		}
		else if(h < 2.0 * PI && h > 4.0 * PI / 3)
		{
			h = h - 4.0 * PI / 3;
			b = 1.0 * i * (1 + s * cos(h) / cos(PI / 3.0 - h));
			r = 3 * i - g - b;
		}
		if(s==0){
			 b = g = r;
		}
		img[j] = CBaseColorInfo(r * 255.0, g * 255.0, b * 255.0);
	}
}

void CHSIProcess::ReduceS()
{
	int size = width * height;

	for(int j = 0;j < size;++ j)
	{
		CBaseColorInfo info = oldimg[j];
		double r = info.GetRed() / 255.0;
		double g = info.GetGreen() / 255.0;
		double b = info.GetBlue() / 255.0;
		double min = r;
		
		if (min > g)
			min = g;
		if(min > b)
			min = b;

		double i = 1.0 * (r + g + b) / 3;
		double s = 0;
		double angle = 0.0;
		if(r == g && r == b && g == b)
			s = 0;
		else
			s = 1 - 3.0 * min / (r + g + b);
		
		if(r == g && r == b && g == b)
			angle = 0;
		else
			angle = acos((r - g + r - b)/ 2.0 / sqrt((r - g) * (r - g) + (r - b) * (g - b)));
		double h = 0.0;
		if(b <= g)
			h = angle;
		else
			h = 2 * PI - angle;

		//h = h / PI;
		s = s - s * 0.5;
		if (h < 2.0 * PI / 3)
		{
			b = 1.0 * i * (1 - s);
			r = 1.0 * i * (1 + s * cos(h) / cos(PI / 3.0 - h));
			g = 3 * i - r - b;	
		}
		else if (h < 4.0 * PI / 3 && h > 2.0 * PI / 3)
		{
			h = h - 2.0 * PI / 3;
			r = i * (1 - s);
			g = 1.0 * i * (1 + s * cos(h) / cos(PI / 3.0 - h));
			b = 3.0 * i - r - g;
		}
		else if(h < 2.0 * PI && h > 4.0 * PI / 3)
		{
			h = h - 4.0 * PI / 3;
			b = 1.0 * i * (1 + s * cos(h) / cos(PI / 3.0 - h));
			r = 3 * i - g - b;
		}
		if(s==0){
			 b = g = r;
		}
		img[j] = CBaseColorInfo(r * 255.0, g * 255.0, b * 255.0);
	}
}