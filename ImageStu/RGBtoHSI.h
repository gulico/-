#if !defined(AFX_RGBTOHSI_H__1B8D8923_E957_45A4_A3EF_B131COA8C971__INCLUDED_)
#define AFX_RGBTOHSI_H__1B8D8923_E957_45A4_A3EF_B131COA8C971__INCLUDED_

#if _MSC_VER >100
#pragma once
#endif

#include "BaseColorInfo.h"
#include "ColorSpaceInfo.h"

#define RINT(x) ((x)-floor(x)>0.5?ceil(x):floor(x))

class CRGBtoHSI{
public:
	CRGBtoHSI(CBaseColorInfo & colorInfo);
	CRGBtoHSI(CColorSpaceInfo & hsiInfo );
	virtual ~CRGBtoHSI();

public:
	//RGBת��HSI
	void RGBToHSI();
	//��HSI��ֵӳ�䵽0~255֮��
	void ScaleHSI();
	//��HSIת����RGB
	void HSIToRGB();
	//��RGB��ֵӳ�䵽0~255֮��
	void ScaleRGB();

public:
	//��ȡ���
	CBaseColorInfo GetResult() const;
	//��ȡRGB
	CColorSpaceInfo GetRGB() const;
	//��ȡHSI
	CColorSpaceInfo GetHSI() const;
	void SetHSI( CColorSpaceInfo info );

private:
	//RGB��һ��
	void RGBPercent();
	//�����Сֵ
	double MinRGB();
	//������ֵ
	double MaxRGB();
	//����м�ֵ����hʱ��
	double CalcMedium();

private:
	//RGBֵ��ԭֵ���룩
	CBaseColorInfo _colorInfo;
	//���
	CBaseColorInfo _result;

	//hsiϵ��
	CColorSpaceInfo _hsi;
	//rgbϵ����0-1��Χ�ڣ�
	CColorSpaceInfo _rgb;

	//��һ�����RGB
	double _r;
	double _g;
	double _b;

	//ֱ������������hsi
	double _h;
	double _s;
	double _i;

};

#endif
