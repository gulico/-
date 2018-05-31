#include "StdAfx.h"
//#include "imageprocess.h"
#include "RGBtoHSI.h"
#include "ImagePara.h"
#include "cmath"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#define		MIN_NUM 0.0001
#endif

CRGBtoHSI::CRGBtoHSI(CBaseColorInfo & colorInfo){
	_colorInfo  = colorInfo;
}

CRGBtoHSI::CRGBtoHSI( CColorSpaceInfo & hsiInfo){
	_hsi = hsiInfo;
	_h = _hsi.GetPara1();
	_s = _hsi.GetPara2();
	_i = _hsi.GetPara3();
}

CRGBtoHSI::~CRGBtoHSI(){

}

//RGBת��HSI
void CRGBtoHSI::RGBToHSI(){

	//RGB��һ��
	RGBPercent();

	int red = _colorInfo.GetRed();
	int green = _colorInfo.GetGreen();
	int blue = _colorInfo.GetBlue();

	//ǿ��
	_i = (_r+_g+_b)/3.0;

	//���Ͷ�
	int sum = red+green+blue;
	if( sum != 0 && !( red == blue && red == green && green == blue )){
		int minV = _colorInfo.GetRed();
		if(minV>_colorInfo.GetGreen()){
			minV = _colorInfo.GetGreen();
		}

		if(minV>_colorInfo.GetBlue()){
			minV = _colorInfo.GetBlue();			
		}

		//���Ͷ�
		_s = 1 - minV * 3.0 / sum;
	}
	else{
		_s = 0;
	}

	//��ɫ��H
	if((red==blue&&red==green&&green==blue)){
		_h = 0.0;
	}else{
		//ת����HSI
		if(blue<=green){
			_h = acos(CalcMedium());
		}else{
			_h = 2*PI-acos(CalcMedium());
		}
	}

	//����HSIϵ��
	_hsi.SetPara1(_h);
	_hsi.SetPara2(_s);
	_hsi.SetPara3(_i);
}

//��HSI��ֵӳ�䵽0~255֮��
void CRGBtoHSI::ScaleHSI(){

	int red = _h * 255.0 / (2*PI);
	int green = _s * 255;
	int blue = _i * 255;

	_result.SetRed(red);
	_result.SetGreen(green);
	_result.SetBlue(blue);
}

//��ȡ���
CBaseColorInfo CRGBtoHSI::GetResult() const{
	return _result;
}

//��ȡHSI
CColorSpaceInfo CRGBtoHSI::GetHSI() const{
	return _hsi;
}

void CRGBtoHSI::SetHSI(CColorSpaceInfo info){
	_hsi = info;
	_h = info.GetPara1();
	_s = info.GetPara2();
	_i = info.GetPara3();
}

//��ȡRGB
CColorSpaceInfo CRGBtoHSI::GetRGB() const{
	return _rgb;
}

//��HSIת����RGB
void CRGBtoHSI::HSIToRGB(){
	double r,g,b;

	CString str;
	str.Format("%lf,%lf,%lf\n",_h,_s,_i);
	TRACE(str);

	if(fabs(_i)<MIN_NUM){
		//��ɫͼ��
		r = 0;
		g = 0;
		b = 0;
	}
	else if(fabs(_s)<MIN_NUM){
		r=g=b=_i;
	}
	else{

	//	str.Format("_h = %lf,h-120=%lf\n",_h,_h-2*PI/3);
	//	::OutputDebugString(str);
		if(_h-2*PI/3<MIN_NUM){
			b=_i*(1.0-_s);
			r=_i*(1+_s*cos(_h)/cos(PI/3-_h));
			g = 3*_i-(b+r);
		}
		else if(_h-4*PI/3<MIN_NUM){
			r = _i*(1-_s);
			g = _i*(1+(_s*cos(_h-2*PI/3)/cos(PI-_h)));
			//����Ĵ��벻����
			b = 3*_i-(r+g);
		}
		else if((_h-2*PI)<MIN_NUM){
			g = _i * (1-_s);
			b = _i*(1+_s*cos(_h-4*PI/3)/cos(5*PI/3 - _h));
			r=3*_i-(g+b);
			//������벻����
		//	str.Format("s = %lf,cosl = %lf,cos2 = %lf\n", _s ,cos(_h-4*PI/3),cos(5*PI/3-_h));
				//::OutputDebugString(str);
		}
		else{
			
		}
	}
	//_rgb.SetPara1(RINT(r*255));
//	_rgb.SetPara2(RINT(g*255));
//	_rgb.SetPara3(RINT(b*255));

	_rgb.SetPara1(r);
	_rgb.SetPara2(g);
	_rgb.SetPara3(b);
}

//��RGB��ֵӳ�䵽0~255֮��
void CRGBtoHSI::ScaleRGB(){

	int red = int(_rgb.GetPara1()*255+0.5);
	int green = int (_rgb.GetPara2()*255+0.5);
	int blue = int (_rgb.GetPara3()*255+0.5);

	_result.SetRed(red);
	_result.SetGreen(green);
	_result.SetBlue(blue);
}

//RGB��һ��
//��RGB��������ת��0~1�ķ���
void CRGBtoHSI::RGBPercent(){
	//��һ��
	_r = _colorInfo.GetRed()*1.0/255;
	_g = _colorInfo.GetGreen()*1.0/255;
	_b = _colorInfo.GetBlue()*1.0/255;
}
//�����Сֵ��RGB���������е���Сֵ��
double CRGBtoHSI::MinRGB(){
	int min = _colorInfo.GetRed();
	if(min>_colorInfo.GetGreen()){
		min = _colorInfo.GetGreen();
	}

	if(min>_colorInfo.GetBlue()){
		min = _colorInfo.GetBlue();
	}

	return min*1.0/255.0;
}

//������ֵ
double CRGBtoHSI::MaxRGB(){

	int max = _colorInfo.GetRed();
	if(max<_colorInfo.GetGreen()){
		max = _colorInfo.GetGreen();
	}

	if(max<_colorInfo.GetBlue()){
		max = _colorInfo.GetBlue();
	}
	return max *1.0/255.0;
}

//����м�ֵ����Hʱ��
double CRGBtoHSI::CalcMedium(){
	//����
	double son = 0.5*((_r-_g)+(_r-_b));
	//��ĸ
	double mother = sqrt((_r-_g)*(_r-_g)+(_r-_b)*(_g-_b));
	
	if(fabs(mother)<MIN_NUM){
		return 0;
	}
	else{
		return son/mother;
	}
}