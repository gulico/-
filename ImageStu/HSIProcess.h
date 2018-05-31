// HSIProcess.h: interface for the CHSIProcess class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HSIPROCESS_H__3A4123DB_6667_4351_856E_FFF34F82D21E__INCLUDED_)
#define AFX_HSIPROCESS_H__3A4123DB_6667_4351_856E_FFF34F82D21E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "BaseColorInfo.h"
class CHSIProcess  
{
public:
	CHSIProcess(CBaseColorInfo *oldimg, int width, int height);
	virtual ~CHSIProcess();
private:
	CBaseColorInfo *img;
	CBaseColorInfo *oldimg;
	int width;
	int height;
	
public:
	void HSIToRGB();
	void RGBToHSI();
	void AddH();
	void ReduceS();
	void ReduceI();
public:
	CBaseColorInfo * getColorImg(){
		return img;
	}
};

#endif // !defined(AFX_HSIPROCESS_H__3A4123DB_6667_4351_856E_FFF34F82D21E__INCLUDED_)
