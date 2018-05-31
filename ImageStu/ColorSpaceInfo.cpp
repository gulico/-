// ColorSpaceInfo.cpp: implementation of the CColorSpaceInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "imageprocess.h"
#include "ColorSpaceInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CColorSpaceInfo::CColorSpaceInfo()
{
	
}

CColorSpaceInfo::CColorSpaceInfo( double para1, double para2, double para3 ){
	_para1 = para1;
	_para2 = para2;
	_para3 = para3;
}

CColorSpaceInfo::~CColorSpaceInfo()
{
	
}

/************************************************************************/
/*                        ����������                                    */
/************************************************************************/
// ���ظ�ֵ������
CColorSpaceInfo & CColorSpaceInfo::operator =( CColorSpaceInfo info ){
	
	// ����һ
	SetPara1( info.GetPara1() );
	// ������
	SetPara2( info.GetPara2() );
	// ������
	SetPara3( info.GetPara3() );
	
	return *this;
	
}

/************************************************************************/
/*                          �ֶζ�ȡ                                    */
/************************************************************************/

// ������
void CColorSpaceInfo::SetPara1(double para1){
	_para1 = para1;
}
double CColorSpaceInfo::GetPara1(){
	return _para1;
}

void CColorSpaceInfo::SetPara2(double para2){
	_para2 = para2;
}
double CColorSpaceInfo::GetPara2(){
	return _para2;
}


void CColorSpaceInfo::SetPara3(double para3){
	_para3 = para3;
}
double CColorSpaceInfo::GetPara3(){
	return _para3;
}
