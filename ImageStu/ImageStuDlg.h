//////////////////////////////////////////////////////////////////////////
// ImageStuDlg.h : header file
// ͼ����ʵ��ѧ��ƽ̨
// ������: �˷�
// ����ʱ��: 2008-8-31
//////////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGESTUDLG_H__8B975AD1_2A07_4F7F_B0EC_1B03621056BF__INCLUDED_)
#define AFX_IMAGESTUDLG_H__8B975AD1_2A07_4F7F_B0EC_1B03621056BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "BaseColorInfo.h"

class CImageStuDlg : public CDialog
{
// Construction
public:
	CImageStuDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CImageStuDlg)
	enum { IDD = IDD_IMAGESTU_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageStuDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CImageStuDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnFileOpen();
	afx_msg void OnDestroy();
	afx_msg void OnFileShowArray();
	afx_msg void OnTest();
	afx_msg void OnFileSave();
	afx_msg void OnbeRed();
	afx_msg void OnbeRedBlue();
	afx_msg void OnbeGrey();
	afx_msg void OnbeBlack();
	afx_msg void OnGreyPix();
	afx_msg void OntoBiger();
	afx_msg void OnQianxiang();
	afx_msg void Onshuangxianxing();
	afx_msg void Onzuibiaobianhuan();
	afx_msg void Onzhuanzhi();
	afx_msg void OngrayNegation();
	afx_msg void OnpowerTransformation();
	afx_msg void OnlogarithmicTransform();
	afx_msg void OnsegmenteFunction();
	afx_msg void OnplanePositionChart();
	afx_msg void OnhistogramEqualization();
	afx_msg void OnswiftCaculate();
	afx_msg void OnswiftWeightCaculate();
	afx_msg void OnswiftTresoldCaculate();
	afx_msg void OnmedianFilter();
	afx_msg void OnlaplaceOperator();
	afx_msg void OnRobert();
	afx_msg void OnSobel();
	afx_msg void OncolorChange();
	afx_msg void Onfushi();
	afx_msg void Onpengzhang();
	afx_msg void Onkaicaozuo();
	afx_msg void Onbicaozuo();
	afx_msg void Onqiubianjie();
	afx_msg void Ontianchong();
	afx_msg void Onqiuliantongquyu();
	afx_msg void Onxihua();
	afx_msg void OnrgbToHSITorgb();
	afx_msg void Onwei216cecai();
	afx_msg void OnupH();
	afx_msg void OndownS();
	afx_msg void OndownI();
	afx_msg void Onhffuman();
	afx_msg void Onyuzhi();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
		// ��ȡ�ļ�ͷ
	BOOL ReadFileHeader( CFile & file );
	// ��ȡ�ļ���Ϣͷ
	BOOL ReadInfoHeader( CFile & file );
	// �ͷ�����
	void FreeData();
	// �����ɫ����ɫ����
	int CalcQuadNum();
	// ��ȡ��ɫ������
	void ReadQuad( CFile &file );
	// �ж��Ƿ�Ϊ256ɫ�Ҷ�ͼ
	BOOL Is256Gray();
	// ����ͼ������
	void ReadImageData( CFile &file );
	// �ж�ͼ������
	IMAGE_TYPE CalcImageType();
	// ��24λ��ɫBMP����ת����24λ��ɫ����
	void BMPConvertColor24();
	// ��8λ��ɫBMP����ת��24λ��ɫ����
	void BMPConvertColor8();
	// ��8λ�Ҷ�BMP����ת��8λ�Ҷ�����
	void BMPConvertGray8();
	// ��8λ�Ҷ�����ת����24λ��ɫ
	void Gray8ConvertColor24( BYTE * grayData, CBaseColorInfo * colorData, int width, int height );
	// ��8λ�Ҷ�����ת����24λ��ɫ
	void Gray8ConvertColor24( int * grayData, CBaseColorInfo * colorData, int width, int height );


	// ��ʾͼ��(ͨ��ͼ������, ��ɫͼ��)
	void ShowPicByArray( CBaseColorInfo * colorData, int width, int height );
	// ��ʾͼ��(ͨ��ͼ������, �Ҷ�ͼ��)
	void ShowPicByArray( int * grayData, int width, int height );

	// ����BMPͼƬ
	bool SaveAsBmp( char * bmpName, unsigned char * imgBuf, int width, int height, int biBitCount, RGBQUAD * pColorTable );
	
public:
	// �ļ�ͷ
	BITMAPFILEHEADER _fileHeader;
	
	// ��ɫ��
	RGBQUAD * _quad;
	// ��ɫ����Ŀ
	int _numQuad;
	// ͼ������
	BYTE * _lpBuf;
	BITMAPINFO * _bitmapInfo;
	// ������ͼ������
	BYTE * _processBuf;
	// �Ƿ����bmp�ļ�
	bool _flag;
	
	// ��Ϣͷ
	BITMAPINFOHEADER _infoHeader;

	// ͼ������
	IMAGE_TYPE _imageType;
	// �Ҷ�(256�Ҷ�����, �����ϵ���, �����ҵ�˳������,һά��������)
	int * _grayData;
	// ��ɫ����(�����ϵ���, �����ҵ�˳������,һά��������)
	CBaseColorInfo * _colorData;




};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGESTUDLG_H__8B975AD1_2A07_4F7F_B0EC_1B03621056BF__INCLUDED_)
