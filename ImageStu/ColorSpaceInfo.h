// ColorSpaceInfo.h: interface for the CColorSpaceInfo class.
// ��װ����ɫ�ռ������������double���洢����
// �����ˣ��˷�
// �������ڣ�2010-5-26
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COLORSPACEINFO_H__97EBBED7_A112_4F89_BE1A_1D18B4656D38__INCLUDED_)
#define AFX_COLORSPACEINFO_H__97EBBED7_A112_4F89_BE1A_1D18B4656D38__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CColorSpaceInfo  
{
public:
	CColorSpaceInfo();
	CColorSpaceInfo( double para1, double para2, double para3 );
	virtual ~CColorSpaceInfo();
	
	
public:
	// ���ظ�ֵ������
	CColorSpaceInfo & operator =( CColorSpaceInfo info );
	
public:
	// ������
	void SetPara1(double para1);
	double GetPara1();
	
	void SetPara2(double para2);
	double GetPara2();
	
	
	void SetPara3(double para3);
	double GetPara3();
	
private:
	// ������
	double _para1;
	double _para2;
	double _para3;
	
};

#endif // !defined(AFX_COLORSPACEINFO_H__97EBBED7_A112_4F89_BE1A_1D18B4656D38__INCLUDED_)
