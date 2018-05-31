// ImgProcess.h: interface for the ImgProcess class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMGPROCESS_H__B29CA766_BD7E_4BE0_AD56_458CF31C604C__INCLUDED_)
#define AFX_IMGPROCESS_H__B29CA766_BD7E_4BE0_AD56_458CF31C604C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ImgProcess  
{
public:
	ImgProcess(int *oldImg, int width, int height);
	virtual ~ImgProcess();

	int * GetResult()
	{
		return _result;
	}
public:
	void FuShi(int *_oldImg);
	void PengZhang(int *_oldImg);
	void BianJie();
private:
	int * _oldImg;
	int _width;
	int _height;
	
	int *_result;
};

#endif // !defined(AFX_IMGPROCESS_H__B29CA766_BD7E_4BE0_AD56_458CF31C604C__INCLUDED_)
