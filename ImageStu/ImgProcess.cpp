// ImgProcess.cpp: implementation of the ImgProcess class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "imagestu.h"
#include "ImgProcess.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ImgProcess::ImgProcess(int *oldimg, int width, int height)
{
	_oldImg = oldimg;
	_width = width;
	_height = height;
	int size = width * height;
	_result = new int[ _width * _height ];

	/*for(int i = 0;i < size;++ i){
		_result[i] = _oldImg[i];
	}*/
	
}

ImgProcess::~ImgProcess()
{
	if( _result != NULL ){
		delete [] _result;
	}
}

void ImgProcess::FuShi(int *_oldImg)
{
	int level = 3;
	int banjin = level / 2;
	_result = new int[_width * _height];

	for(int x = banjin;x < _width - banjin;++ x)
	{
		for (int y = banjin;y < _height - banjin;++ y)
		{	
			int index = y * _width + x;
			_result[index] = _oldImg[index];
			if(_oldImg[index] == 0)
				continue;
			for (int m = x - banjin;m <= x + banjin;++m)
			{
				for (int n = y - banjin;n <= y + banjin;++n)
				{
					int tempIndex = n * _width + m;
					if (_oldImg[tempIndex] == 0)
					{
						_result[index] = 0;
							break;
					}
				}
			}
		}
	}
}

void ImgProcess::PengZhang(int *_oldImg)
{
	int level = 3;
	int banjin = level / 2;
	_result = new int[_width * _height];

	for(int x = banjin;x < _width - banjin;++ x)
	{
		for (int y = banjin;y < _height - banjin;++ y)
		{	
			int index = y * _width + x;
			_result[index] = _oldImg[index];
			if(_oldImg[index] == 255)
				continue;
			for (int m = x - banjin;m <= x + banjin;++m)
			{
				for (int n = y - banjin;n <= y + banjin;++n)
				{
					int tempIndex = n * _width + m;
					if (_oldImg[tempIndex] == 255)
					{
						_result[index] = 255;
							break;
					}
				}
			}
		}
	}
}

void ImgProcess::BianJie()
{
	int level = 3;
	int banjin = level / 2;
	_result = new int[_width * _height];
	int *pic =  new int[_width * _height];

	for(int x = banjin;x < _width - banjin;++ x)
	{
		for (int y = banjin;y < _height - banjin;++ y)
		{	
			int index = y * _width + x;
			//_result[index] = _oldImg[index];
			pic[index] = _oldImg[index];
			if(_oldImg[index] == 0)
				continue;
			for (int m = x - banjin;m <= x + banjin;++m)
			{
				for (int n = y - banjin;n <= y + banjin;++n)
				{
					int tempIndex = n * _width + m;
					if (_oldImg[tempIndex] == 0)
					{
						pic[index] = 0;
							break;
					}
					
				}
			}
			if(_oldImg[index] != pic[index])
				_result[index] = abs(_oldImg[index] - pic[index]);
		}
	}
}