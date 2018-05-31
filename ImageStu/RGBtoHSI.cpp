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

//RGB转到HSI
void CRGBtoHSI::RGBToHSI(){

	//RGB归一化
	RGBPercent();

	int red = _colorInfo.GetRed();
	int green = _colorInfo.GetGreen();
	int blue = _colorInfo.GetBlue();

	//强度
	_i = (_r+_g+_b)/3.0;

	//饱和度
	int sum = red+green+blue;
	if( sum != 0 && !( red == blue && red == green && green == blue )){
		int minV = _colorInfo.GetRed();
		if(minV>_colorInfo.GetGreen()){
			minV = _colorInfo.GetGreen();
		}

		if(minV>_colorInfo.GetBlue()){
			minV = _colorInfo.GetBlue();			
		}

		//饱和度
		_s = 1 - minV * 3.0 / sum;
	}
	else{
		_s = 0;
	}

	//求色度H
	if((red==blue&&red==green&&green==blue)){
		_h = 0.0;
	}else{
		//转换成HSI
		if(blue<=green){
			_h = acos(CalcMedium());
		}else{
			_h = 2*PI-acos(CalcMedium());
		}
	}

	//设置HSI系数
	_hsi.SetPara1(_h);
	_hsi.SetPara2(_s);
	_hsi.SetPara3(_i);
}

//将HSI的值映射到0~255之间
void CRGBtoHSI::ScaleHSI(){

	int red = _h * 255.0 / (2*PI);
	int green = _s * 255;
	int blue = _i * 255;

	_result.SetRed(red);
	_result.SetGreen(green);
	_result.SetBlue(blue);
}

//读取结果
CBaseColorInfo CRGBtoHSI::GetResult() const{
	return _result;
}

//读取HSI
CColorSpaceInfo CRGBtoHSI::GetHSI() const{
	return _hsi;
}

void CRGBtoHSI::SetHSI(CColorSpaceInfo info){
	_hsi = info;
	_h = info.GetPara1();
	_s = info.GetPara2();
	_i = info.GetPara3();
}

//读取RGB
CColorSpaceInfo CRGBtoHSI::GetRGB() const{
	return _rgb;
}

//从HSI转换到RGB
void CRGBtoHSI::HSIToRGB(){
	double r,g,b;

	CString str;
	str.Format("%lf,%lf,%lf\n",_h,_s,_i);
	TRACE(str);

	if(fabs(_i)<MIN_NUM){
		//黑色图像
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
			//上面的代码不完整
			b = 3*_i-(r+g);
		}
		else if((_h-2*PI)<MIN_NUM){
			g = _i * (1-_s);
			b = _i*(1+_s*cos(_h-4*PI/3)/cos(5*PI/3 - _h));
			r=3*_i-(g+b);
			//上面代码不完整
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

//将RGB的值映射到0~255之间
void CRGBtoHSI::ScaleRGB(){

	int red = int(_rgb.GetPara1()*255+0.5);
	int green = int (_rgb.GetPara2()*255+0.5);
	int blue = int (_rgb.GetPara3()*255+0.5);

	_result.SetRed(red);
	_result.SetGreen(green);
	_result.SetBlue(blue);
}

//RGB归一化
//将RGB三个分量转成0~1的分量
void CRGBtoHSI::RGBPercent(){
	//归一化
	_r = _colorInfo.GetRed()*1.0/255;
	_g = _colorInfo.GetGreen()*1.0/255;
	_b = _colorInfo.GetBlue()*1.0/255;
}
//求出最小值（RGB三个参数中的最小值）
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

//求出最大值
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

//求出中间值（求H时）
double CRGBtoHSI::CalcMedium(){
	//分子
	double son = 0.5*((_r-_g)+(_r-_b));
	//分母
	double mother = sqrt((_r-_g)*(_r-_g)+(_r-_b)*(_g-_b));
	
	if(fabs(mother)<MIN_NUM){
		return 0;
	}
	else{
		return son/mother;
	}
}