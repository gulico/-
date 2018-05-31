//////////////////////////////////////////////////////////////////////////
// ImageStuDlg.h : header file
// 图像处理实验学生平台
// 创建人: 邓飞
// 创建时间: 2008-8-31
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
		// 读取文件头
	BOOL ReadFileHeader( CFile & file );
	// 读取文件信息头
	BOOL ReadInfoHeader( CFile & file );
	// 释放数据
	void FreeData();
	// 计算调色板颜色数量
	int CalcQuadNum();
	// 读取调色板数据
	void ReadQuad( CFile &file );
	// 判断是否为256色灰度图
	BOOL Is256Gray();
	// 读入图像数据
	void ReadImageData( CFile &file );
	// 判断图像类型
	IMAGE_TYPE CalcImageType();
	// 将24位彩色BMP数据转换成24位颜色数据
	void BMPConvertColor24();
	// 将8位彩色BMP数据转成24位颜色数据
	void BMPConvertColor8();
	// 将8位灰度BMP数据转成8位灰度数据
	void BMPConvertGray8();
	// 将8位灰度数据转成用24位颜色
	void Gray8ConvertColor24( BYTE * grayData, CBaseColorInfo * colorData, int width, int height );
	// 将8位灰度数据转成用24位颜色
	void Gray8ConvertColor24( int * grayData, CBaseColorInfo * colorData, int width, int height );


	// 显示图像(通过图像数组, 彩色图像)
	void ShowPicByArray( CBaseColorInfo * colorData, int width, int height );
	// 显示图像(通过图像数组, 灰度图像)
	void ShowPicByArray( int * grayData, int width, int height );

	// 保存BMP图片
	bool SaveAsBmp( char * bmpName, unsigned char * imgBuf, int width, int height, int biBitCount, RGBQUAD * pColorTable );
	
public:
	// 文件头
	BITMAPFILEHEADER _fileHeader;
	
	// 调色板
	RGBQUAD * _quad;
	// 调色板数目
	int _numQuad;
	// 图像数据
	BYTE * _lpBuf;
	BITMAPINFO * _bitmapInfo;
	// 处理后的图像数据
	BYTE * _processBuf;
	// 是否打开了bmp文件
	bool _flag;
	
	// 信息头
	BITMAPINFOHEADER _infoHeader;

	// 图像类型
	IMAGE_TYPE _imageType;
	// 灰度(256灰度数据, 按从上到下, 从左到右的顺序排列,一维矩阵排列)
	int * _grayData;
	// 彩色数据(按从上到下, 从左到右的顺序排列,一维矩阵排列)
	CBaseColorInfo * _colorData;




};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGESTUDLG_H__8B975AD1_2A07_4F7F_B0EC_1B03621056BF__INCLUDED_)
