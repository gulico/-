// XingTaiXue.cpp: implementation of the XingTaiXue class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "imagestu.h"
#include "XingtTaiXue.h"
#include <algorithm>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
XingTaiXue::XingTaiXue(int *img, int width, int height)
{
	
	int size = width * height;
	_img = new int[size];
	_oldimg = new int[size];
	_fanxiangimg = new int[size];
	flag_liantong = new int[size];
	for(int i = 0; i < size; ++ i){
		_img[i] = img[i];
		_oldimg[i] = img[i];
		flag_liantong[i] = 0;
		if(img[i] == 0)
			_fanxiangimg[i] = 255;
		else
			_fanxiangimg[i] = 0;
	}
	_width = width;
	_height = height;
}

XingTaiXue::~XingTaiXue()
{
if(_img != NULL)
		delete []_img;
	if(_oldimg != NULL)
		delete []_oldimg;
/*	if(rgb_img != NULL)
		delete []rgb_img;*/
	if(_fanxiangimg != NULL)
		delete [] _fanxiangimg;
	if(flag_liantong != NULL)
		delete []flag_liantong;

}


// model: 模板
void XingTaiXue::FuShi( int * model, int size, bool white ){
	int _size = _width * _height;
	int *temp = new int [_size];
	std::copy( _img, _img + _size, temp);
	for( int x = size / 2; x < _width - size / 2; ++x ){
		for( int y = size / 2; y < _height - size / 2; ++y ){
			int index = y * _width + x;
			if( white == true ){
				// 白色做腐蚀
				if( temp[ index ] == 0 ){
					continue;
				}
			}
			else{
				if( temp[ index ] == 255 ){
					continue;
				}
			}
			
			// 取邻域
			int step = 0;
			for( int m = x - size / 2; m <= x + size / 2; ++m ){
				for( int n = y - size / 2; n <= y + size / 2; ++n ){
					
					if( model[ step ] == 0 ){
						// 模板为0，不需要处理
						++step;
						continue;
					}
					++step;
					
					int tempIndex = n * _width + m;
					if( white == true ){
						if( temp[ tempIndex ] == 0 ){
							_img[ index ] = 0;
						}
					}
					else{
						if( temp[ tempIndex ] == 255 ){
							_img[ index ] = 255;
						}
					}
				}
			}
		}
	}
}

// 判断两个图像相等
bool XingTaiXue::XiangDeng( int * first, int * second ){
int size = _width * _height;
	for(int i = 0; i < size; ++ i)
	{
		if(first[i] != second[i])
			return false;
	}
	return true;
}
// 交集
void XingTaiXue::JiaoJi( int * first, int * second, int * result ){
	int size = _width * _height;
	for(int i = 0; i < size; ++ i){
		if(first[i] == 255 && second[i] == 255)
			result[i] = 255;
		else
			result[i] = 0;
		
	}
}
void XingTaiXue::TianChong(int x, int y, int *model, int level, bool white){

	//CImageProcess(_img, _width, _height);
	int size = _width * _height;
	int i;
	for(i = 0; i < size; ++ i){
		
		_oldimg[i] = _img[i];
		if(_img[i] == 0)
			_fanxiangimg[i] = 255;
		else
			_fanxiangimg[i] = 0;
	}
	
	int *pic = new int[size];
	
	if(white == true){
		for(i = 0; i < size; ++ i)
			pic[i] = 0;
		pic[y * _width + x] = 255;
	}
	else{
		for(i = 0; i < size; ++ i)
			pic[i] = 255;
		pic[y * _width + x] = 0;
	}
//	int *beforeImg = new int[size];
//std::copy(pic, pic + size, beforeImg);
	std::copy(pic, pic + size, _img);
	
	FuShi(model, level, !white);
	int *jiaojiImg = new int[size];

	//jisuan_pengzhang(5);
	JiaoJi(_img, _fanxiangimg, jiaojiImg);	

	int p = 0;
	while(!XiangDeng(pic, jiaojiImg)){

	//	std::copy(jiaojiImg, jiaojiImg + size, beforeImg);
		std::copy(jiaojiImg, jiaojiImg + size, _img);
		std::copy(jiaojiImg, jiaojiImg + size, pic);
		FuShi(model, level, !white);
		//int *jiaojiImg = new int[size];

		JiaoJi(_img, _fanxiangimg, jiaojiImg);
	
		/*if(p ++ > 100)
			break;*/
	}
	
	for(i = 0; i < size; ++ i)
	{
		if(white != true){
			if(_oldimg[i] == 0)
				_img[i] = 0;
		}else{
			if(_oldimg[i] == 255)
				_img[i] = 255;
		}
	}
	//std::copy(_fanxiangimg, _fanxiangimg + size, _img);
/*	for(i = 0; i < size; ++ i){
		if(_oldimg[i] == 255)
			_img[i] = 255;
	}*/
	delete[] pic;
	delete[] jiaojiImg;

}
int fang[8][2] = {1, -1, 1, 1, 1, 0, 0, 1, 0,-1, -1, 0, -1, 1, -1, -1};
void XingTaiXue::dfs_liantong(int x, int y, int index, int top){
	
	flag_liantong[index] = top;
	
	for(int i = 0; i < 8; ++ i)
	{
		int nx = x + fang[i][0];
		int ny = y + fang[i][1];
		int id = ny * _width + nx;
		if(nx >= 0 && nx < _width && ny >= 0 && ny < _height && _img[id] == 255 && flag_liantong[id] == 0){
			dfs_liantong(nx, ny, id, top);
		}
	}
	
}

void XingTaiXue::jisuan_fushi(int level)
{
	int size = _width * _height;
	int pp = level / 2;
	int i, j;
	for(i = pp; i < _width - pp; ++ i )
	{
		for(j = pp; j <_height - pp; ++ j)
		{
			int index = j * _width + i;
			if(_oldimg[index] == 0)
				continue;
			for(int x = i - pp; x <= i + pp; ++ x)
			{
				for(int y = j - pp; y <= j + pp; ++ y)
				{
					int temp = y * _width + x;
					if(_oldimg[temp] == 0){
						_img[index] = 0;
						break;
					}
				}
			}
		}
	}
}

void XingTaiXue::LianTong()
{
	int size = _width * _height;
	int i, j;
	for(i = 0; i < size; ++ i)
	{
		if(_img[i] > 200)
		{
			_img[i] = 255;
			_oldimg[i] = 255;
		}else
		{
			_img[i] = 0;
			_oldimg[i] = 0;
		}
	}
	jisuan_fushi(5);
	std::copy(_img, _img + size, _oldimg);
	int top = 1;
	//	flag_liantong = new int[size];
	//	memset(flag_liantong, 0, sizeof(flag_liantong));
	for(i = 0; i < _width; ++ i){
		for(j = 0; j <_height; ++ j){
			int index = j * _width + i;
			if(flag_liantong[index] == 0 && _img[index] == 255){
				dfs_liantong(i, j, index, top);
				top ++;
			}
		}
	}
	
	
}

void XingTaiXue::XiHua()
{
	int erasetable[256] =  {
		0,0,1,1,0,0,1,1, 1,1,0,1,1,1,0,1,
			1,1,0,0,1,1,1,1, 0,0,0,0,0,0,0,1,
			0,0,1,1,0,0,1,1, 1,1,0,1,1,1,0,1,
			1,1,0,0,1,1,1,1, 0,0,0,0,0,0,0,1,
			1,1,0,0,1,1,0,0, 0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
			1,1,0,0,1,1,0,0, 1,1,0,1,1,1,0,1,
			0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
			0,0,1,1,0,0,1,1, 1,1,0,1,1,1,0,1,
			1,1,0,0,1,1,1,1, 0,0,0,0,0,0,0,1,
			0,0,1,1,0,0,1,1, 1,1,0,1,1,1,0,1,
			1,1,0,0,1,1,1,1, 0,0,0,0,0,0,0,0,
			1,1,0,0,1,1,0,0, 0,0,0,0,0,0,0,0,
			1,1,0,0,1,1,1,1, 0,0,0,0,0,0,0,0,
			1,1,0,0,1,1,0,0, 1,1,0,1,1,1,0,0,
			1,1,0,0,1,1,1,0, 1,1,0,0,1,0,0,0
	};
	
	bool finished = false;
	while(!finished){
		//	for (int i = 0;i < _size;++ i)
		//		_result[i] = _source[i];
		finished = true;
		for (int y = 1;y < _height - 1 ;y ++)
		{
			int x = 1;
			while (x<_width-1)
			{
				int index = y * _width + x;
				//	_result[index] = _source[index];
				if(_oldimg[index] == 0)
				{
					int w = _oldimg[index - 1];//左
					int e = _oldimg[index + 1];//右
					if (w == 255 || e == 255)//其中一点为白
					{
						int nw = _oldimg[index - 1 - _width];//左上
						int n = _oldimg[index - _width];//上
						int ne = _oldimg[index + 1 - _width];//右上
						int sw = _oldimg[index - 1 + _width];//左下
						int s = _oldimg[index + _width];//下
						int se = _oldimg[index + 1 + _width];//右下
						int num = (nw/255+ 2 * n/255 + 4 * ne/255
							+ w/255 * 8 + e/255 * 16 + sw/255 * 32 
						+ s/255 * 64 + se/255 * 128 ) ;
					if (erasetable[num] == 1)//1则删除
					{
						_oldimg[index] = 255;
						_img[index] = 255;
						finished = false;
						x++;
					}
				}
			}
			x++;
		}
	}
	
	for (int x = 1;x < _width - 1;x ++)
	{
		int y = 1;
		while (y<_height-1)
		{
			int index = y * _width + x;
			_img[index] = _oldimg[index];
			if(_oldimg[index] == 0)
			{
				int n = _oldimg[index - _width];
				int s = _oldimg[index +  _width];
				if (n == 255 || s == 255)
				{
					int nw = _oldimg[index - 1 - _width];//左上
					int ne = _oldimg[index + 1 - _width];//右上
					int w = _oldimg[index - 1];
					int e = _oldimg[index + 1];
					int sw = _oldimg[index - 1 + _width];//左下
					int se = _oldimg[index + 1 + _width];//右下
					int num = (nw/255.0 + 2 * n/255.0 + 4 * ne/255.0
						+ w/255.0 * 8  + e/255.0 * 16 + sw/255.0 * 32
						+ s/255.0 * 64  + se/255.0 * 128 );
					if (erasetable[num] == 1)
					{
						_oldimg[index] = 255;
						_img[index] = 255;
						finished = false;
						y++;
					}
				}
			}
			y++;
		}
	}

	}
}