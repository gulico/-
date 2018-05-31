// ImageStuDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ImageStu.h"
#include "ImgProcess.h"
#include "ImageStuDlg.h"
#include "DlgShowArray.h"
#include "DlgTask.h"
#include "XingtTaiXue.h"
#include "HSIProcess.h"
#include "RGBtoHSI.h"
#include "ImgHuffman.h"
#include <sstream>
#include <cmath>
#include <algorithm>
#include <cmath>
#ifdef _DEBUG
#define new DEBUG_NEW
#define PI 3.14
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	
	// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
//{{AFX_MSG_MAP(CAboutDlg)
// No message handlers
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageStuDlg dialog

CImageStuDlg::CImageStuDlg(CWnd* pParent /*=NULL*/)
: CDialog(CImageStuDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CImageStuDlg)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	// 图像已打开标记
	_flag = false;
	
}

void CImageStuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImageStuDlg)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CImageStuDlg, CDialog)
//{{AFX_MSG_MAP(CImageStuDlg)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_COMMAND(IDC_FILE_OPEN, OnFileOpen)
ON_WM_DESTROY()
ON_COMMAND(IDC_FILE_SHOW_ARRAY, OnFileShowArray)
ON_COMMAND(IDC_TEST, OnTest)
ON_COMMAND(IDC_FILE_SAVE, OnFileSave)
ON_COMMAND(beRed, OnbeRed)
ON_COMMAND(beRedBlue, OnbeRedBlue)
ON_COMMAND(beGrey, OnbeGrey)
ON_COMMAND(beBlack, OnbeBlack)
ON_COMMAND(ID_GreyPix, OnGreyPix)
ON_COMMAND(toBiger, OntoBiger)
ON_COMMAND(IDC_QIANXIANG, OnQianxiang)
ON_COMMAND(IDC_shuangxianxing, Onshuangxianxing)
ON_COMMAND(IDC_zuibiaobianhuan, Onzuibiaobianhuan)
ON_COMMAND(IDC_zhuanzhi, Onzhuanzhi)
ON_COMMAND(grayNegation, OngrayNegation)
ON_COMMAND(powerTransformation, OnpowerTransformation)
ON_COMMAND(logarithmicTransform, OnlogarithmicTransform)
ON_COMMAND(segmenteFunction, OnsegmenteFunction)
ON_COMMAND(planePositionChart, OnplanePositionChart)
ON_COMMAND(histogramEqualization, OnhistogramEqualization)
ON_COMMAND(swiftCaculate, OnswiftCaculate)
ON_COMMAND(swiftWeightCaculate, OnswiftWeightCaculate)
ON_COMMAND(swiftTresoldCaculate, OnswiftTresoldCaculate)
ON_COMMAND(medianFilter, OnmedianFilter)
ON_COMMAND(laplaceOperator, OnlaplaceOperator)
ON_COMMAND(Robert, OnRobert)
ON_COMMAND(Sobel, OnSobel)
ON_COMMAND(ID_fushi, Onfushi)
ON_COMMAND(pengzhang, Onpengzhang)
ON_COMMAND(kaicaozuo, Onkaicaozuo)
ON_COMMAND(bicaozuo, Onbicaozuo)
ON_COMMAND(qiubianjie, Onqiubianjie)
ON_COMMAND(tianchong, Ontianchong)
ON_COMMAND(qiuliantongquyu, Onqiuliantongquyu)
ON_COMMAND(xihua, Onxihua)
ON_COMMAND(rgbToHSITorgb, OnrgbToHSITorgb)
ON_COMMAND(wei216cecai, Onwei216cecai)
ON_COMMAND(upH, OnupH)
ON_COMMAND(downS, OndownS)
ON_COMMAND(downI, OndownI)
ON_COMMAND(hffuman, Onhffuman)
ON_COMMAND(yuzhi, Onyuzhi)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageStuDlg message handlers

BOOL CImageStuDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// Add "About..." menu item to system menu.
	
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CImageStuDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CImageStuDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
	
	// 绘图
	CDC * pDC = GetDC();
	if( _flag == true ){
		
		// 已经打开文件
		SetDIBitsToDevice(
			pDC->m_hDC  // 设备描述表
			, 0 // 设备描述表位图输出的起始逻辑x坐标
			, 0 // 设备描述表位图输出的起始逻辑y坐标
			, _infoHeader.biWidth // DIB的宽度
			, _infoHeader.biHeight // DIB的高度
			, 0 // DIB开始读取输出的像素数据的x位置
			, 0 // DIB开始读取输出的像素数据的y位置
			, 0 // DIB中像素的水平行号, 对应lpBits内存缓冲区的第一行数据
			, _infoHeader.biHeight  // DIB的行数
			, _lpBuf  // 像素数据
			, _bitmapInfo //BITMAPINFO数据
			, DIB_RGB_COLORS // 显示的颜色
			);
		
	}
	ReleaseDC( pDC );
	
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CImageStuDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//////////////////////////////////////////////////////////////////////////
// 销毁对话框, 映射WM_DESTORY消息
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
	if( _flag == true ){
		FreeData();
	}
	
	
}

/************************************************************************/
/*                           菜单                                       */
/************************************************************************/

//////////////////////////////////////////////////////////////////////////
// "文件"-->"打开"(IDC_FILE_OPEN)
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::OnFileOpen() 
{
	// TODO: Add your command handler code here
	
	LPCTSTR lpszFilter = "BMP Files(*.bmp)|*.bmp|任何文件|*.*|";
	CFileDialog dlg( TRUE, lpszFilter, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		lpszFilter, NULL );
	// 文件名
	CString fileName;
	CFile file;
	// 打开文件
	if( dlg.DoModal() == IDOK ){
		
		// 文件名
		fileName = dlg.GetPathName();
		if( file.Open( fileName, CFile::modeRead | CFile::shareDenyNone, NULL ) == 0 ){
			// 读取文件失败
			AfxMessageBox( "无法打开文件", MB_OK, MB_ICONERROR );
			return;
		}
		
		// 读取文件头
		if( !ReadFileHeader( file ) ){
			return;
		}
		
		// 读取信息头 
		if( !ReadInfoHeader( file ) ){
			return;
		}
		
		// 若前面已有文件打开，则释放相应的数据
		if( _flag == true ){
			FreeData();
			_flag = false;
		}
		
		// 计算调色板颜色数量
		_numQuad = CalcQuadNum();
		// 读取调色板数据
		ReadQuad( file );
		
		// 判断图像类型
		_imageType = CalcImageType();
		
		// 读入图像数据
		ReadImageData( file );
		
		
		
		
		// 分配处理后的数据
		_processBuf = ( BYTE * )HeapAlloc( GetProcessHeap(), 0, _infoHeader.biSizeImage );
		
		// 宽度不是4的倍数则补齐
		DWORD dwBytes = ((DWORD) _infoHeader.biWidth * _infoHeader.biBitCount) / 32;
		if(((DWORD) _infoHeader.biWidth * _infoHeader.biBitCount) % 32) {
			dwBytes++;
		}
		dwBytes *= 4;
		
		
		
		Invalidate( );
		
		int width = _infoHeader.biWidth;
        int height = _infoHeader.biHeight;
		
		// 分配空间
		_colorData = new CBaseColorInfo[ width * height ];
		_grayData = new int[ width * height ];
		
		// 根据图像类型，将其转换成相应的图像数据
		if( _imageType == COLOR_24_BIT ){
			// 24位颜色图像
			BMPConvertColor24();
			
		}
		else if( _imageType == COLOR_8_BIT ){
			// 256彩色图像
			BMPConvertColor8();
		}
		else if( _imageType == GRAY_8_BIT ){
			// 256灰度图像
			BMPConvertGray8();
			// 将8位灰度数据转成用24位颜色
			Gray8ConvertColor24( _grayData, _colorData, width, height );
		}
		else{
			MessageBox( "暂不支持该图像类型" );
			// 关闭图像
			file.Close();
			FreeData();
			return;
		}
		
		// 图像读取完毕
		file.Close();
		_flag = true;
		
	}
	
}


//////////////////////////////////////////////////////////////////////////
// "文件"-->"显示数组图像"
// 将转换后的24位彩色数据在对话框中显示
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::OnFileShowArray() 
{
	// TODO: Add your command handler code here
	
	if(_flag == FALSE){
		MessageBox("没有打开图像");
		return;
	}
	
	CDlgShowArray dlg;
	dlg.SetColorData( _colorData );
	dlg.SetWidth( _infoHeader.biWidth );
	dlg.SetHeight( _infoHeader.biHeight );
	dlg.DoModal();
	
}


//////////////////////////////////////////////////////////////////////////
// "文件"-->"保存"菜单
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::OnFileSave() 
{
	// TODO: Add your command handler code here
	if( ! _flag  ){
		MessageBox( "没有图片，无法保存" );
		return;
	}
	
	CFileDialog dlg(false,"*.bmp",NULL,NULL,"*.bmp|*.bmp||");
	if (dlg.DoModal()==IDOK)
	{
		SaveAsBmp( (LPTSTR)(LPCTSTR)dlg.GetPathName(), _lpBuf, _infoHeader.biWidth, _infoHeader.biHeight, _infoHeader.biBitCount,
			_quad );
	}
	
}


/************************************************************************/
/*                         私有函数                                     */
/************************************************************************/
//////////////////////////////////////////////////////////////////////////
// 读取文件头
// 参数:
//   file: CFile &, BMP文件
// 返回值:
//   BOOL, TRUE: 成功; FALSE: 失败
//////////////////////////////////////////////////////////////////////////
BOOL CImageStuDlg::ReadFileHeader( CFile &file ){
	
	// 读取文件头
	file.Read( &_fileHeader, sizeof( _fileHeader ) );
	// 判断是否为BMP文件
	if( _fileHeader.bfType != 0x4d42 ){
		// "BM"
		AfxMessageBox( "不是BMP文件", MB_OK, MB_ICONERROR );
		return FALSE;
	}
	
	// 判断文件是否损坏(文件大小是否与文件头的信息一致)
	if( file.GetLength() != _fileHeader.bfSize ){
		AfxMessageBox( "文件已损坏", MB_OK, MB_ICONERROR );
		return FALSE;
	}
	
	return TRUE;
	
}


//////////////////////////////////////////////////////////////////////////
// 读取文件信息头
// 参数:
//   file: CFile &, 已经打开的BMP文件
// 返回值:
//   BOOL, TRUE成功; 其它失败
//////////////////////////////////////////////////////////////////////////
BOOL CImageStuDlg::ReadInfoHeader( CFile &file ){
	
	// 读取文件信息头
	file.Read( &_infoHeader, sizeof( _infoHeader ) );
	
	// 将图片格式限定在8位图像
	// 	if( _infoHeader.biBitCount != 8 ){
	// 		AfxMessageBox( "必须为8位灰度图", MB_OK, MB_ICONERROR );
	// 		return FALSE;
	// 	}
	
	return TRUE;
	
}


//////////////////////////////////////////////////////////////////////////
// 释放数据
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::FreeData(){
	
	HeapFree( GetProcessHeap(), 0, _bitmapInfo );
	HeapFree( GetProcessHeap(), 0, _lpBuf );
	// 处理后的数据
	HeapFree( GetProcessHeap(), 0, _processBuf );
	// 灰度颜色数据
	delete [] _grayData;
	// 彩色颜色数据
	delete [] _colorData;
	
	
	
}

//////////////////////////////////////////////////////////////////////////
// 计算调色板颜色数量
// 参数: 无
// 返回值:
//   int, 调色板颜色数量
//////////////////////////////////////////////////////////////////////////
int CImageStuDlg::CalcQuadNum(){
	
	// 计算调色板数据
	int numQuad = 0;
	if( _infoHeader.biBitCount < 24){
		// 相当于2的biBitCount次方
		numQuad = ( 1 << _infoHeader.biBitCount );
	}
	
	return numQuad;
	
}

//////////////////////////////////////////////////////////////////////////
// 读取调色板数据
// 参数:
//   file: CFile &, BMP文件
// 返回值: 无
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::ReadQuad( CFile &file ){
	
	// 为图像信息pbi申请空间
	_bitmapInfo = ( BITMAPINFO * )HeapAlloc( 
		GetProcessHeap(), 
		0, 
		sizeof( BITMAPINFOHEADER ) + _numQuad * sizeof( RGBQUAD ) 
		);
	memcpy( _bitmapInfo, &_infoHeader, sizeof( _infoHeader ) );
	_quad = ( RGBQUAD * )( ( BYTE *)_bitmapInfo + sizeof( BITMAPINFOHEADER ) );
	
	// 读取调色板
	if( _numQuad != 0 ){
		file.Read( _quad, sizeof( RGBQUAD ) * _numQuad );
	}
	
}

//////////////////////////////////////////////////////////////////////////
// 判断是否为256色灰度图
// 判断依据，调色板中所有颜色的的RGB三个分量应该相等
// BOOL: TRUE为256色灰度图
//////////////////////////////////////////////////////////////////////////
BOOL CImageStuDlg::Is256Gray(){
	
	BOOL result = TRUE;
	for( int i = 0; i <= _numQuad - 1; i++ ){
		RGBQUAD color = *( _quad + i );
		//TRACE( "%d: %d, %d, %d\n", i, color.rgbRed,  color.rgbGreen, color.rgbBlue );
		if( !( color.rgbRed == color.rgbGreen && color.rgbRed == color.rgbBlue ) ){
			result = FALSE;
			break;
		}
	}
	
	return result;
	
}

//////////////////////////////////////////////////////////////////////////
// 读入图像数据
// 参数:
//   file: CFile &, BMP图像
// 返回值: 无
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::ReadImageData( CFile &file ){
	
	// 为图像数据申请空间
	_infoHeader.biSizeImage = _fileHeader.bfSize - _fileHeader.bfOffBits;
	_lpBuf = ( BYTE *)HeapAlloc( GetProcessHeap(), 0, _infoHeader.biSizeImage );
	// 读取图像数据
	file.Read( _lpBuf, _infoHeader.biSizeImage );
	
}

//////////////////////////////////////////////////////////////////////////
// 判断图像类型
// 参数: 无
// 返回值: IMAGE_TYPE, 图像类型, 参数枚举IMAGE_TYPE的定义
//////////////////////////////////////////////////////////////////////////
IMAGE_TYPE CImageStuDlg::CalcImageType(){
	
	IMAGE_TYPE type = COLOR_24_BIT;
	if( _infoHeader.biBitCount == IMAGE_TYPE_BIT_24 ){
		// 24彩色图像
		type = COLOR_24_BIT;
		//MessageBox( "24位图像" );
	}
	else if( _infoHeader.biBitCount == IMAGE_TYPE_BIT_1 ){
		// 二值图像　
		type = GRAY_1_BIT;
		//MessageBox( "1位图像" );
	}
	else if( _infoHeader.biBitCount == IMAGE_TYPE_BIT_8 ){
		// 8位
		if( Is256Gray() ){
			// 8位灰度图像
			type = GRAY_8_BIT;
			//MessageBox( "8位灰度图像" );
		}
		else{
			// 8位彩色图像
			type = COLOR_8_BIT;
			//MessageBox( "8位彩色图像" );
		}
	}
	
	return type;
	
}

//////////////////////////////////////////////////////////////////////////
// 将BMP数据转换成24位颜色数据
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::BMPConvertColor24(){
	
	// 宽度不是4的倍数则补齐
	DWORD dwBytes = ((DWORD) _infoHeader.biWidth * _infoHeader.biBitCount) / 32;
	if(((DWORD) _infoHeader.biWidth * _infoHeader.biBitCount) % 32) {
		dwBytes++;
	}
	dwBytes *= 4;
	
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	// 分配彩色数据
	
	int i,j;
	
	for( i = 0; i <= height - 1; i++ ){
		for( j = 0; j <= width - 1; j++ ){
			
			// BMP图片数据中的坐标
			DWORD index = i * 3 * width + 3 * j;
			if( dwBytes % 3 != 0 ){
				index = i * dwBytes + 3 * j ;
			}
			// 颜色数组中的坐标
			DWORD resultIndex = ( height - 1 - i ) * width + j;
			_colorData[ resultIndex ].SetRed( _lpBuf[ index  + 2 ] );
			_colorData[ resultIndex ].SetGreen( _lpBuf[ index  + 1 ] );
			_colorData[ resultIndex ].SetBlue( _lpBuf[ index ] );
			
		}// for j
	}// for i 
	
}

//////////////////////////////////////////////////////////////////////////
// 将8位彩色BMP数据转成24位颜色数据
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::BMPConvertColor8(){
	
	// 宽度不是4的倍数则补齐
	DWORD dwBytes = ((DWORD) _infoHeader.biWidth * _infoHeader.biBitCount) / 32;
	if(((DWORD) _infoHeader.biWidth * _infoHeader.biBitCount) % 32) {
		dwBytes++;
	}
	dwBytes *= 4;
	
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	// 分配彩色数据
	// 	if( _colorFlag == true ){
	// 		delete [] _colorData;
	// 	}
	// 	_colorData = new CBaseColorInfo[ width * height ];
	// 	_colorFlag = true;
	
	
	int i,j;
	// 	for( i = 0; i <= 100; i++ ){
	// 		TRACE( "%d->%d,", i, _lpBuf[ i ] );
	// 	}
	// 	TRACE( "\n" );
	for( i = 0; i <= height - 1; i++ ){
		for( j = 0; j <= width - 1; j++ ){
			
			// BMP图片数据中的坐标
			DWORD index = i * dwBytes + j ;
			
			// 颜色数组中的坐标
			DWORD resultIndex = ( height - 1 - i ) * width + j;
			// 			if( index >= _infoHeader.biSizeImage || resultIndex >= _infoHeader.biSizeImage ){
			// 				TRACE( "*** i = %d, j = %d, index = %d, resultIndex = %d, widht = %d, height = %d \n", 
			// 					i, j, index, resultIndex, width, height );
			// 			}
			
			// 			int red = _lpBuf[ index ] + 2;
			// 			int green = _lpBuf[ index ] + 1;
			// 			int blue = _lpBuf[ index ] + 0;
			// 
			// 			if( resultIndex <= width * height - 1 ){
			// 			_colorData[ resultIndex ].SetRed( red );
			// 			_colorData[ resultIndex ].SetGreen( green );
			// 			_colorData[ resultIndex ].SetBlue( blue );
			// 			}
			
			_colorData[ resultIndex ].SetRed( _quad[ _lpBuf[ index ] ].rgbRed );
			_colorData[ resultIndex ].SetGreen( _quad[ _lpBuf[ index ] ].rgbGreen );
			_colorData[ resultIndex ].SetBlue( _quad[ _lpBuf[ index ] ].rgbBlue );
			
			// 			TRACE( "%d,%d,%d\t", _colorData[ resultIndex ].GetRed(),
			// 				_colorData[ resultIndex ].GetGreen(), 
			// 				_colorData[ resultIndex ].GetBlue() );
			
			// 			if( i <= 10 && j <= 10 ){
			// 			  TRACE( "(%d,%d,%d)->(%d,%d,%d) ", i,j,index, _colorData[ resultIndex ].GetRed(),
			// 				_colorData[ resultIndex ].GetGreen(), 
			// 				_colorData[ resultIndex ].GetBlue() );
			/*			}*/
			
		}// for j
	}// for i 
	
}

//////////////////////////////////////////////////////////////////////////
// 将8位灰度BMP数据转成8位灰度数据
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::BMPConvertGray8(){
	
	// 宽度不是4的倍数则补齐
	DWORD dwBytes = ((DWORD) _infoHeader.biWidth * _infoHeader.biBitCount) / 32;
	if(((DWORD) _infoHeader.biWidth * _infoHeader.biBitCount) % 32) {
		dwBytes++;
	}
	dwBytes *= 4;
	
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	// 分配彩色数据
	// 	if( _colorFlag == true ){
	// 		delete [] _colorData;
	// 	}
	// 	_grayData = new BYTE[ width * height ];
	// 	_grayFlag = true;
	
	
	int i,j;
	// 	for( i = 0; i <= 100; i++ ){
	// 		TRACE( "%d->%d,", i, _lpBuf[ i ] );
	// 	}
	// 	TRACE( "\n" );
	for( i = 0; i <= height - 1; i++ ){
		for( j = 0; j <= width - 1; j++ ){
			
			// BMP图片数据中的坐标
			DWORD index = i * dwBytes + j ;
			
			// 颜色数组中的坐标
			DWORD resultIndex = ( height - 1 - i ) * width + j;
			// 			if( index >= _infoHeader.biSizeImage || resultIndex >= _infoHeader.biSizeImage ){
			// 				TRACE( "*** i = %d, j = %d, index = %d, resultIndex = %d, widht = %d, height = %d \n", 
			// 					i, j, index, resultIndex, width, height );
			// 			}
			
			// 			int red = _lpBuf[ index ] + 2;
			// 			int green = _lpBuf[ index ] + 1;
			// 			int blue = _lpBuf[ index ] + 0;
			// 
			// 			if( resultIndex <= width * height - 1 ){
			// 			_colorData[ resultIndex ].SetRed( red );
			// 			_colorData[ resultIndex ].SetGreen( green );
			// 			_colorData[ resultIndex ].SetBlue( blue );
			// 			}
			
			_grayData[ resultIndex ] = _lpBuf[ index ];
			
			
			// 			TRACE( "%d,%d,%d\t", _colorData[ resultIndex ].GetRed(),
			// 				_colorData[ resultIndex ].GetGreen(), 
			// 				_colorData[ resultIndex ].GetBlue() );
			
			// 			if( i <= 10 && j <= 10 ){
			// 			  TRACE( "(%d,%d,%d)->(%d,%d,%d) ", i,j,index, _colorData[ resultIndex ].GetRed(),
			// 				_colorData[ resultIndex ].GetGreen(), 
			// 				_colorData[ resultIndex ].GetBlue() );
			/*			}*/
			
		}// for j
	}// for i 
	
}

//////////////////////////////////////////////////////////////////////////
// 将8位灰度数据转成用24位颜色
// 灰度图的RGB值均相同
// 参数:
//   grayData: BYTE *, 灰度数据
//   colorData: CBaseColorInfo *, 24位颜色数据
//   width: 图片宽度
//   height: 图片高度
//  返回值: 无
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::Gray8ConvertColor24( BYTE * grayData, 
									   CBaseColorInfo * colorData, 
									   int width, 
									   int height ){
	
	
	int length = width * height;
	for( int i = 0; i <= length - 1; i++ ){
		colorData[ i ].SetRed( grayData[ i ] );
		colorData[ i ].SetGreen( grayData[ i ] );
		colorData[ i ].SetBlue( grayData[ i ] );
	}
	
}

// 将8位灰度数据转成用24位颜色
void CImageStuDlg::Gray8ConvertColor24( int * grayData, CBaseColorInfo * colorData, int width, int height ){
	
	int length = width * height;
	for( int i = 0; i <= length - 1; i++ ){
		colorData[ i ].SetRed( grayData[ i ] );
		colorData[ i ].SetGreen( grayData[ i ] );
		colorData[ i ].SetBlue( grayData[ i ] );
	}
	
}

//////////////////////////////////////////////////////////////////////////
// 显示图像(通过图像数组,彩色图像)
// 参数:
//   colorData: CBaseColorInfo, 颜色数据
//   width: int, 图像宽度
//   height: int, 图像高度
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::ShowPicByArray( CBaseColorInfo * colorData, 
								  int width, 
								  int height ){
	
	CDlgShowArray dlg;
	// 图像数据(24位彩色图像)
	dlg.SetColorData( colorData );
	// 图像宽度
	dlg.SetWidth( width );
	// 图像高度
	dlg.SetHeight( height );
	// 显示对话框
	dlg.DoModal();
	
}




//////////////////////////////////////////////////////////////////////////
// 显示图像(通过图像数组, 灰度图像)
// 参数:
//   colorData: CBaseColorInfo, 灰度图像数据
//   width: int, 图像宽度
//   height: int, 图像高度
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::ShowPicByArray( int * grayData, 
								  int width, 
								  int height ){
	
	// 将灰度图像转成彩色图像
	CBaseColorInfo * colorData = new CBaseColorInfo[ width * height ];
	Gray8ConvertColor24( grayData, colorData, width, height );
	
	CDlgShowArray dlg;
	// 图像数据(24位彩色图像)
	dlg.SetColorData( colorData );
	// 图像宽度
	dlg.SetWidth( width );
	// 图像高度
	dlg.SetHeight( height );
	// 显示对话框
	dlg.DoModal();
	
	// 释放彩色图像
	delete [] colorData;
	
}











void CImageStuDlg::OnTest() 
{
	// TODO: Add your command handler code here
	int x, y;
	int width = 800;
	int height = 600;
	CBaseColorInfo * img = new CBaseColorInfo[ width * height ];
	for( x = 0; x < width; ++x ){
		for( y = 0; y < height; ++y ){
			int index = y * width + x;
			if( x % 10 == 0 ){
				img[ index ] = CBaseColorInfo( 255, 0, 0 );
			}
			else{
				img[ index ] = CBaseColorInfo( 0, 255, 0 );
			}
			
		}
	}
	
	// 显示图像
	ShowPicByArray( img, width, height );
	
	delete []img;
}


//////////////////////////////////////////////////////////////////////////
// 功能：保存BMP图片
// 参数：
//   bmpName: char *, 文件名(含路径、文件后缀)
//   imgBuf: unsigned char *, 图像数据
//   width: int, 图像宽度
//   height: int, 图像高度
//   biBitCount: int, 像素深度
//   pColorTable: RGBAUAD *, 颜色表
//////////////////////////////////////////////////////////////////////////
bool CImageStuDlg::SaveAsBmp( char * bmpName, 
							 unsigned char * imgBuf, 
							 int width, 
							 int height,
							 int biBitCount, 
							 RGBQUAD * pColorTable 
							 ){
	
	// 如果位图数据为空，则没有数据传入
	if( !imgBuf ){
		return false;
	}
	
	// 颜色表大小，以字节为单位，灰度图像颜色表为1024，彩色图像颜色表大小为0
	int colorTableSize = 0;
	if( biBitCount == 8 ){
		colorTableSize = 1024; // 感觉不一定正确
	} 
	
	// 将带存储图像数据每行字节数转为4的倍数
	int lineByte = ( width * biBitCount / 8 + 3 ) / 4 * 4;
	// 以二进制的写的方式打开文件
	FILE *fp = fopen( bmpName, "wb" );
	if( !fp ){
		return false;
	}
	
	// 申请位图文件头结构变量，填写文件头信息
	BITMAPFILEHEADER fileHead;
	fileHead.bfType = 0x4D42;// bmp类型
	// bfSize是图像文件4个组成部分之和
	fileHead.bfSize = sizeof( BITMAPFILEHEADER ) 
		+ sizeof( BITMAPINFOHEADER )
		+ colorTableSize 
		+ lineByte * height; // 图像数据字节数
	fileHead.bfReserved1 = 0;
	fileHead.bfReserved2 = 0;
	
	// bfOffBits是图像文件前三部分所需空间之和
	fileHead.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)  + colorTableSize;
	// 文件头写入文件
	fwrite( &fileHead, sizeof( BITMAPFILEHEADER ) , 1, fp );
	
	// 申请位图信息头结构变量，填写信息头信息
	BITMAPINFOHEADER head;
	head.biSize = sizeof(BITMAPINFOHEADER); // 位图信息头结构的大小(40个字节)
	head.biWidth = width;// 图像宽度，以像素为单位
	head.biHeight = height;// 图像高度，以像素为单位
	head.biPlanes = 1;// 必须为1
	head.biBitCount = biBitCount; // 像素深度，每个像素的为数(bit数)
	head.biCompression = BI_RGB; // 图像是否压缩，一般是未压缩的
	head.biSizeImage = lineByte * height; // 实际的位图数据占据的字节数
	head.biXPelsPerMeter = 0; // 目标设备的水平分辨率
	head.biYPelsPerMeter = 0; // 目标设备的垂直分辨率
	head.biClrUsed = 0; // 本图像实际用到的颜色数
	head.biClrImportant = 0; // 本图像重要的颜色，如果为0，则所有的颜色均重要 
	
	// 写位图信息头进内存
	fwrite( &head, sizeof( BITMAPINFOHEADER ), 1, fp );
	
	// 如果图像时灰度图像，有颜色表，写入文件
	if( biBitCount == 8 ){
		fwrite( pColorTable, sizeof( RGBQUAD ), 256, fp );
	}
	
	// 写位图数据进文件
	fwrite( imgBuf, height * lineByte, 1, fp );
	
	// 关闭文件
	fclose( fp );
	
	return true;
	
}



void CImageStuDlg::OnbeRed() 
{
	// TODO: Add your command handler code here
	int width = 800;
	int height = 600;
	int size = width * height;
	CBaseColorInfo *img = new CBaseColorInfo[ size ];
	
	for(int i = 0; i <size ; ++i ){
		img[i] = CBaseColorInfo(255,0,0);
	}
	ShowPicByArray( img, width , height);
	
	//释放
	delete [] img;
	
}

void CImageStuDlg::OnbeRedBlue() 
{
	// TODO: Add your command handler code here
	int width = 800;
	int height = 600;
	int size = width * height;
	//生成图片
	CBaseColorInfo * img = new CBaseColorInfo[ size ];
	
	//赋值
	for( int x = 0; x < width; ++x ){
		for( int y = 0; y < height; ++y ){
			if( ( ( x / 40 ) % 2 ) ==  ( ( y / 30 ) % 2 ) ){
				//红色
				int index = y * width + x;
				img[ index ] = CBaseColorInfo( 255, 0, 0 );
			}
			else{
				//蓝色
				int index = y * width + x;
				img[ index ] = CBaseColorInfo( 0, 0, 255 );
			}
		}
	}
	
	//显示
	ShowPicByArray( img, width, height );
	
	//释放
	delete [] img ;
}

void CImageStuDlg::OnbeGrey() 
{
	// TODO: Add your command handler code here
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	//生成图片
	CBaseColorInfo * img = new CBaseColorInfo[ size ];
	int *grayData = new int[size];
	//赋值
	for( int x = 0; x < size; ++x ){
		CBaseColorInfo info = _colorData[x];
		int gray = 0.299 * info.GetRed()+ 0.587 * info.GetGreen()+ 0.114 * info.GetBlue();
		
		img[x] = CBaseColorInfo(gray,gray,gray);
		grayData[x] = gray;
	}
	
	//显示
	ShowPicByArray( grayData, width, height );
	
	//释放
	delete [] img ;	
}

void CImageStuDlg::OnbeBlack() 
{
	// TODO: Add your command handler code here
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	//生成图片
	int * img = new int[ size ];
	//赋值
	int gray =100;//阈值
	for( int i = 0; i < size; ++i ){
		if(_grayData[i]>gray){
			img[i] = 255;
		}else{
			img[i] = 0;
		}
	}
	
	//显示
	ShowPicByArray( img, width, height );
	
	//释放
	delete [] img ;	
}

void CImageStuDlg::OnGreyPix() 
{
	// TODO: Add your command handler code here
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	//生成图片
	int * img = new int[ size ];
	
	int level = 256 / 8;
	const int GRAY_LEVEL = 256;
	int rule[ GRAY_LEVEL ];
	
	for(int i = 0;i<GRAY_LEVEL;++i){
		rule[ i ] = i / level *level;
	}
	for( int j = 0; j < size ; ++j ){
		int oldGrey = _grayData[ j ];
		//int gray = oldGrey / level * level;
		img[ j ] = rule[ oldGrey ];
	}
	
	ShowPicByArray( img, width, height );
	//释放
	delete [] img ;	
}

void CImageStuDlg::OntoBiger() 
{
	// TODO: Add your command handler code here
	double scale = 0.8;//缩放系数
	int width = _infoHeader.biWidth * scale;//最终宽度
	int height = _infoHeader.biHeight * scale;//最终长度
	int size = width * height;//最终大小
	int * img = new int[ size ];
	
	int oldWidth = _infoHeader.biWidth;//原始宽度
	int oldHeight = _infoHeader.biHeight;//原始高度
	
	for( int x = 0 ; x < width ; ++x ){
		for( int y = 0 ; y < height ; ++y ){
			//计算坐标
			int oldX = x / scale ;
			int oldY = y / scale ;
			//赋值
			int newIndex = y * width + x;
			int oldIndex = oldY * oldWidth + oldX;
			img[ newIndex ] = _grayData[ oldIndex];
		}
	}
	ShowPicByArray( img, width, height );
	//释放
	delete [] img ;	
	
}

void CImageStuDlg::OnQianxiang() 
{
	// TODO: Add your command handler code here
	// TODO: Add your command handler code here
	double scale = 0.8;//缩放系数
	int width = _infoHeader.biWidth * scale;//最终宽度
	int height = _infoHeader.biHeight * scale;//最终长度
	int size = width * height;//最终大小
	int * img = new int[ size ];
	
	int oldWidth = _infoHeader.biWidth;//原始宽度
	int oldHeight = _infoHeader.biHeight;//原始高度
	
	for( int x = 0 ; x < oldWidth ; ++x ){
		for( int y = 0 ; y < oldHeight ; ++y ){
			//计算坐标
			int newX = x * scale ;
			int newY = y * scale ;
			//赋值
			int newIndex = newY * width + newX;
			int oldIndex = y * oldWidth + x;
			img[ newIndex ] = _grayData[ oldIndex];
		}
	}
	ShowPicByArray( img, width, height );
	//释放
	delete [] img ;	
}

void CImageStuDlg::Onshuangxianxing() //二次线性差值
{
	// TODO: Add your command handler code here
	double scale = 0.8;//缩放系数
	int width = _infoHeader.biWidth * scale;//最终宽度
	int height = _infoHeader.biHeight * scale;//最终长度
	int size = width * height;//最终大小
	int * img = new int[ size ];
	
	int oldWidth = _infoHeader.biWidth;//原始宽度
	int oldHeight = _infoHeader.biHeight;//原始高度
	
	for( int x = 0 ; x < width ; ++x ){
		for( int y = 0 ; y < height ; ++y ){
			double oldX = x / scale ;
			double oldY = y / scale ;
			//赋值
			int newIndex = y * width + x;
			int oldIndex = oldY * oldWidth + oldX;
			//img[ newIndex ] = _grayData[ oldIndex ];
			//1)确定四个领域ABCD
			//A点
			int Ax = oldX;
			int Ay = oldY;
			int AIndex = Ay * oldWidth + Ax ;
			int gA = _grayData[ AIndex ];
			
			//B点
			int Bx = oldX + 1;
			int By = oldY;
			int BIndex = AIndex + 1 ;
			int gB = _grayData[ BIndex ];
			
			//计算gE点
			double gE = (oldX - Ax) * (gB - gA) + gA;
			
			//C点
			int Cindex = AIndex + oldWidth;
			int gC = _grayData[ Cindex ];
			
			//D点
			int Dindex = BIndex +oldWidth;
			int gD = _grayData[Dindex];
			double gF = ( oldX - Ax ) *( gD - gC) + gC;
			
			//最终计算
			int gray = (oldY - Ay) * (gF -gE) + gE ;
			
			img[newIndex] = gray;
		}
	}
	ShowPicByArray( img, width, height );
	//释放
	delete [] img ;	
}

void CImageStuDlg::Onzuibiaobianhuan() //镜像
{
	// TODO: Add your command handler code here
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	//生成图片
	int * img = new int[ size ];
	for(int x = 0 ; x < width ; ++x){
		for(int y = 0 ; y < height  ; ++y ){
			img[ y * width + x ] = _grayData[ y * width + width - x];
		}
	}
	ShowPicByArray( img, width, height );
	//释放
	delete [] img ;	
}



void CImageStuDlg::Onzhuanzhi() //转置
{
	// TODO: Add your command handler code here
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	//生成图片
	int * img = new int[ size ];
	for(int y = 0 ; y < height  ; ++y){
		for(int x = 0 ; x < width  ; ++x ){
			img[ x * height + y ] = _grayData [ y * width + x];
		}
	}
	ShowPicByArray( img, height, width );
	//释放
	delete [] img ;	
}

void CImageStuDlg::OngrayNegation() //灰度变换
{
	// TODO: Add your command handler code here
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	//生成图片
	int * img = new int[ size ];
	for(int i = 0 ; i < size  ; ++i){
		img[i] = 255 - _grayData [ i ];
	}
	ShowPicByArray( img, width, height );
	//释放
	delete [] img ;	
}

void CImageStuDlg::OnpowerTransformation() //幂次变换
{
	// TODO: Add your command handler code here
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	//生成图片
	double c = 1;
	double Y = 0.4;
	int * img = new int[ size ];
	for(int i = 0 ; i < size  ; ++i){
		img[i] = c * pow(_grayData[i],Y);
	}
	ShowPicByArray( img, width, height );
	//释放
	delete [] img ;	
}

void CImageStuDlg::OnlogarithmicTransform() //对数变换
{
	// TODO: Add your command handler code here
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	//生成图片
	int * img = new int[ size ];
	int c = 40;
	for(int i = 0 ; i < size  ; ++i){
		img[i] = c * log(_grayData [ i ]+1) ;
	}
	ShowPicByArray( img, width, height );
	//释放
	delete [] img ;	
}

void CImageStuDlg::OnsegmenteFunction() //分段变换
{
	// TODO: Add your command handler code here
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	//生成图片
	int * img = new int[ size ];
	int min = 70;
	int max = 150;
	for(int i = 0 ; i < size  ; ++i){
		if(_grayData[i] > 70 && _grayData[i]<150){
			img[i] = _grayData[i]-50;
		}else{
			img[i] = _grayData[i];
		}	
	}
	ShowPicByArray( img, width, height );
	//释放
	delete [] img ;
}

void CImageStuDlg::OnplanePositionChart() //位平面
{
	// TODO: Add your command handler code here
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	//生成图片
	int * img = new int[ size ];
	int ** PositionChart = new int*[9];
	int i,j;
	for(i=0;i<9;i++){
		PositionChart[i] = new int[size];
	}
	//分离平面
	int * gray = new int[ size ];
	for(j=0;j<size;++j){
		gray[j] = _grayData[j];
	}
	for(i=0;i<8;++i){//8个平面
		for(j=0;j<size;++j){
			PositionChart[i][j] = gray[j]%2;
			gray[j]=gray[j]/2;
			//PositionChart[i][j] = (PositionChart[i][j]*((int)pow(2,i)))%2;
		}
	}
	
	for(j=0;j<size;j++){
		img[j] = 0;
		for(i=7;i>=0;--i){
			img[j] = img[j]*2;
			if(i!=6){//删去第6个平面
				img[j] = img[j]+PositionChart[i][j];
			}
		}
	}
	ShowPicByArray( img, width, height );
	//释放
	for(i=0;i<9;i++){
		delete[] PositionChart[i];
	}
	delete[] PositionChart;
	delete [] img ;
}

void CImageStuDlg::OnhistogramEqualization() //直方图均衡化
{
	// TODO: Add your command handler code here
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	//生成图片
	int * img = new int[ size ];
	const int LEVEL = 256;
	int rule[LEVEL] = {0};
	
	int i;
	int yuanshi[ LEVEL] = {0};//原始直方图
	//计算原始直方图
	for( i=0 ; i< size ;++i){
		int gray = _grayData[i];
		++yuanshi[gray];
	}
	//测试
	/*std::stringstream stream;
	for(i=0;i<LEVEL;++i){
	stream<<yuanshi[i]<<",";
	}
	::OutputDebugString(stream.str().c_str());*/
	//归一化
	double guiYiHua[LEVEL] = {0};
	for(i=0;i<LEVEL;++i){
		guiYiHua[i] = yuanshi[i]*1.0/size;
	}
	//调试
	/*std::stringstream stream;
	for(i=0;i<LEVEL;++i){
	stream<<guiYiHua[i]<<",";
	}
	::OutputDebugString(stream.str().c_str());*/
	//积累直方图
	double leiJi[LEVEL] = {0};
	leiJi[0] = guiYiHua[0];
	for(i = 1 ; i < LEVEL ; ++i){
		leiJi[i] = leiJi[i-1]+guiYiHua[i];
	}
	/*std::stringstream stream;
	for(i=0;i<LEVEL;++i){
	stream<<leiJi[i]<<",";
	}
	::OutputDebugString(stream.str().c_str());*/
	for(i=0;i<LEVEL;++i){
		rule[i] = (LEVEL-1)*leiJi[i] +0.5;
	}
	
	for(i=0;i<size;++i){
		int gray = _grayData[i];
		img[i] = rule[gray];
	}
	ShowPicByArray( img, width, height );
	//释放
	delete [] img ;	
}

void CImageStuDlg::OnswiftCaculate() //领域均值的快速运算
{
	// TODO: Add your command handler code here
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	//生成图片
	int * img = new int[ size ];
	int *temp =new int[size];
	
	//水平
	for(int y=1;y<height-1;++y){
		for(int x=1;x<width-1;++x){
			int sum = 0;
			for(int m=x-1;m<=x+1;++m){
				sum=sum+_grayData[y*width+m];
			}
			temp[y*width+x]=sum;
		}
	}
	//垂直
	for(int x = 1;x<width-1;++x){
		for(int y=1;y<height-1;++y){
			int sum = 0;
			for(int n=y-1;n<=y+1;++n){
				sum = sum+temp[n*width+x];
			}
			img[y*width+x] = sum;
		}
	}
	for(int i = 0 ; i<size;++i){
		img[i] = img[i]/9;
	}
	ShowPicByArray( img, width, height );
	//释放
	delete [] img ;	
	delete [] temp;
}

void CImageStuDlg::OnswiftWeightCaculate() //领域加权的快速运算
{
	// TODO: Add your command handler code here
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	//生成图片
	int * img = new int[ size ];
	int *temp =new int[size];
	
	//水平
	for(int y=1;y<height-1;++y){
		for(int x=1;x<width-1;++x){
			int sum = 0;
			for(int m=x-1;m<=x+1;++m){
				sum=sum+_grayData[y*width+m];
				if(m==x)//1 2 1
					sum=sum+_grayData[y*width+m];
			}
			temp[y*width+x]=sum;
		}
	}
	//垂直
	for(int x = 1;x<width-1;++x){
		for(int y=1;y<height-1;++y){
			int sum = 0;
			for(int n=y-1;n<=y+1;++n){
				sum = sum+temp[n*width+x];
				if(n==y)// 中间的一排*2
					sum = sum + temp[n*width+x];
			}
			img[y*width+x] = sum;
		}
	}
	for(int i = 0 ; i<size;++i){
		img[i] = img[i]/16;
	}
	ShowPicByArray( img, width, height );
	//释放
	delete [] img ;	
	delete [] temp;
}

void CImageStuDlg::OnswiftTresoldCaculate() 
{
	//针对"Fig3.36(a).bmp"，采用15×15邻域均值滤波。
	//滤波后的图像的最大值的40%作为滤波的阈值，大于该阈值的取原图像的灰度，小于该阈值的取0。
	// TODO: Add your command handler code here
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	//生成图片
	int * img = new int[ size ];
	//int *temp =new int[size];
	
	int scale = 15;
	int step = scale/2;
	//水平
	for(int y=step;y<height-step;++y){
		for(int x=step;x<width-step;++x){
			int sum = 0;
			for(int m=x-step;m<=x+step;++m){
				for(int n=y-step;n<=y+step;++n){
					sum = sum+_grayData[n*width+m];
				}
			}
			img[y*width+x]=sum/(scale*scale);
		}
	}
	//求出最高亮度
	int i,max;
	for(i=0;i<size;++i){
		if(img[i]>max){
			max = img[i];
		}
	}
	
	//阈值处理
	int Tresold = max*0.4;
	for(i=0;i<size;++i){
		if(img[i]<Tresold)
			img[i]=0;
		else
			img[i] = _grayData[i];
	}
	ShowPicByArray( img, width, height );
	//释放
	delete [] img ;	
	//delete [] temp;
}

void CImageStuDlg::OnmedianFilter() 
{
	// TODO: Add your command handler code here
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	//生成图片
	int * img = new int[ size ];
	
	int model = 3;
	int step = model/2;
	int *linYu = new int[model*model];
	for(int x = step ; x<width-step;++x){
		for(int y= step; y <height-step;++y){
			//取领域
			int order = 0;
			for(int m = x - step ; m <= x + step ; ++m ){
				for(int n = y - step ; n <= y + step ; ++n ){
					int index = n * width +m;
					linYu[order] = _grayData[index];
					++order;
				}
			}
			//排序
			std::stable_sort( linYu , linYu + model * model );
			//取中值
			img[ y * width + x ] = linYu[ model * model / 2 ];
		}
	}
	
	ShowPicByArray( img, width, height );
	//释放
	delete [] img ;	
	delete [] linYu;
}

void CImageStuDlg::OnlaplaceOperator() 
{
	// TODO: Add your command handler code here
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	//生成图片
	int * img = new int[ size ];
	
	for(int x = 1; x < width - 1; ++x ){
		for(int y = 1 ; y < height - 1 ; ++y ){
			int index = y * width + x;
			img[ index ] = 4 * _grayData[ index ]
				-_grayData[index-1]
				-_grayData[index+1]
				-_grayData[index-width]
				-_grayData[index+width];
			
			//处理负值
			if(img[index]<0){
				img[index]*=-1;
			}
		}
	}
	
	ShowPicByArray( img, width, height );
	//释放
	delete [] img ;	
}

void CImageStuDlg::OnRobert() //交叉算子
{
	// TODO: Add your command handler code here
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	//生成图片
	int * img = new int[ size ];
	for(int x = 0; x < width -1;++x){
		for(int y = 0 ;y < height-1;++y){
			int index = y*width+x;
			img[index] = fabs(_grayData[index+width+1]-_grayData[index])
				+fabs(_grayData[index+width]-_grayData[index+1]);
		}
	}
	
	ShowPicByArray( img, width, height );
	//释放
	delete [] img ;	
	
}

void CImageStuDlg::OnSobel() //sobel算子
{
	// TODO: Add your command handler code here
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	//生成图片
	int * img = new int[ size ];
	
	for(int x = 1; x < width - 1 ; ++x ){
		for(int y = 1 ; y < height - 1 ; ++y ){
			int index = y * width + x;
			img[index] = fabs(_grayData[index+width-1]+2*_grayData[index+width]+_grayData[index+width+1]
				-_grayData[index-width-1]-2*_grayData[index-width]-_grayData[index-width+1])
				+fabs(_grayData[index-width+1]+2*_grayData[index+1]+_grayData[index+width+1]
				-_grayData[index-width-1]-2*_grayData[index-1]-_grayData[index+width-1]);
		}
	}
	
	
	ShowPicByArray( img, width, height );
	//释放
	delete [] img ;	
}

void CImageStuDlg::OncolorChange() 
{
	// TODO: Add your command handler code here
	
}

void CImageStuDlg::Onfushi() 
{
	// TODO: Add your command handler code here
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int *pic = new int[size];
	ImgProcess bean(_grayData, width, height);
	bean.FuShi(_grayData);
	pic = bean.GetResult();
	
	ShowPicByArray(pic, width, height);
}

void CImageStuDlg::Onpengzhang() 
{
	// TODO: Add your command handler code here
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int *pic = new int[size];
	ImgProcess bean(_grayData, width, height);
	bean.PengZhang(_grayData);
	pic = bean.GetResult();
	
	ShowPicByArray(pic, width, height);
}

void CImageStuDlg::Onkaicaozuo() 
{
	// TODO: Add your command handler code here
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int *pic = new int[size];
	ImgProcess bean(_grayData, width, height);
	bean.FuShi(_grayData);
	bean.PengZhang(bean.GetResult());
	pic = bean.GetResult();
	
	ShowPicByArray(pic, width, height);	
}

void CImageStuDlg::Onbicaozuo() 
{
	// TODO: Add your command handler code here
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int *pic = new int[size];
	ImgProcess bean(_grayData, width, height);
	bean.PengZhang(_grayData);
	bean.FuShi(bean.GetResult());
	pic = bean.GetResult();
	
	ShowPicByArray(pic, width, height);	
}

void CImageStuDlg::Onqiubianjie() 
{
	// TODO: Add your command handler code here
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int *pic = new int[size];
	ImgProcess bean(_grayData, width, height);
	bean.BianJie();
	pic = bean.GetResult();
	
	ShowPicByArray(pic, width, height);	
}

void CImageStuDlg::Ontianchong() 
{
	// TODO: Add your command handler code here
	//（105,58）；（264,105）
	int model[9] = {
		0, 1, 0,
			1, 0, 1,
			0, 1, 0
	};
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	XingTaiXue bean = XingTaiXue (_grayData, width, height);
	bean.TianChong(105,58, model, 3, true);
	bean.TianChong(183, 46,model, 3, true);
	int *pic = bean.GetResult();
	ShowPicByArray(pic, width, height);
}

void CImageStuDlg::Onqiuliantongquyu() 
{
	// TODO: Add your command handler code here
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int i, j, k;
	int *ff = new int[size];
	XingTaiXue bean = XingTaiXue (_grayData, width, height);
	bean.LianTong();
	
	ff = bean.getliantong();
	
	int elem[3] = {0, 127,255};
	CBaseColorInfo *color = new CBaseColorInfo[216];
	CBaseColorInfo *pic = new CBaseColorInfo[size];
	int index = 0;
	int rule[256] = {0};
	for(i = 0; i < 3; ++ i)
	{
		for(j = 0; j < 3; ++ j)
		{
			for(k = 0; k < 3; ++ k)
			{
				color[index ++] = CBaseColorInfo (elem[i], elem[j], elem[k]);
			}
		}
	}
	
	for(i = 0; i < 20; ++ i)
	{
		rule[i] = i / 19.0 * 27;
	}
	
	for(i = 0; i < size; ++ i){
		pic[i] = color[ff[i]];
	}
	ShowPicByArray(pic, width, height);
}

void CImageStuDlg::Onxihua() 
{
	// TODO: Add your command handler code here
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int *pic = new int[size];
	
	XingTaiXue bean(_grayData, width, height);
	bean.XiHua();
	pic = bean.GetResult();
	ShowPicByArray(pic, width, height);
}

void CImageStuDlg::OnrgbToHSITorgb() 
{
	// TODO: Add your command handler code here
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	CBaseColorInfo *newColor = new CBaseColorInfo[size];
	
	for(int index = 0;index<size;index++){
		CBaseColorInfo colorInfo = _colorData[index];
		CRGBtoHSI bean(colorInfo);
		bean.RGBToHSI();
		bean.HSIToRGB();
		bean.ScaleRGB();
		
		CBaseColorInfo hsiInfo = bean.GetResult();
		newColor[index] = hsiInfo;
	}
	
	
	ShowPicByArray(newColor, width, height);
	delete []newColor;
}

void CImageStuDlg::Onwei216cecai() 
{
	// TODO: Add your command handler code here
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int temp[6] = {0, 51, 102, 153, 204, 255};
	int rule[256] = {0};
	CBaseColorInfo color[216];
	CBaseColorInfo *pic = new CBaseColorInfo[size];
	int index = 0;
	
	for (int i = 0;i < 256;++ i)
	{
		rule[i] = 1.0 * i / 256 * 216;
	}
	
	for (int r = 0;r < 6;++ r)
	{
		for (int g = 0;g < 6;++ g)
		{
			for (int b = 0;b < 6;++ b)
			{
				color[index] = CBaseColorInfo(temp[r], temp[g], temp[b]);
				index ++;
			}
		}
	}
	
	for (i = 0;i < size;++ i)
	{
		int gray = _grayData[i];
		pic[i] = color[rule[gray]];
	}
	ShowPicByArray(pic, width, height);
	delete []pic;
}

void CImageStuDlg::OnupH() 
{
	// TODO: Add your command handler code here
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	CBaseColorInfo *newColor = new CBaseColorInfo[size];
	
	for(int index = 0;index<size;index++){
		CBaseColorInfo colorInfo = _colorData[index];
		CRGBtoHSI bean(colorInfo);
		bean.RGBToHSI();
		
		CColorSpaceInfo hsi = bean.GetHSI();
		//增加60度
		double addH = PI/3.0;
		if(hsi.GetPara1()+addH>2*PI){
			hsi.SetPara1(hsi.GetPara1()+addH-2*PI);
		}else{
			hsi.SetPara1(hsi.GetPara1()+addH);
		}
		
		bean.SetHSI(hsi);
		bean.HSIToRGB();
		bean.ScaleRGB();
		
		CBaseColorInfo hsiInfo = bean.GetResult();
		newColor[index] = hsiInfo;
	}
	ShowPicByArray(newColor, width, height);
	delete []newColor;
}

void CImageStuDlg::OndownS() 
{
	// TODO: Add your command handler code here
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	CBaseColorInfo *newColor = new CBaseColorInfo[size];
	
	for(int index = 0;index<size;index++){
		CBaseColorInfo colorInfo = _colorData[index];
		CRGBtoHSI bean(colorInfo);
		bean.RGBToHSI();
		
		CColorSpaceInfo hsi = bean.GetHSI();
		
		hsi.SetPara2(hsi.GetPara2()*0.5);
		bean.SetHSI(hsi);
		bean.HSIToRGB();
		bean.ScaleRGB();
		
		CBaseColorInfo hsiInfo = bean.GetResult();
		newColor[index] = hsiInfo;
	}
	ShowPicByArray(newColor, width, height);
	delete []newColor;
}

void CImageStuDlg::OndownI() 
{
	// TODO: Add your command handler code here
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	CBaseColorInfo *newColor = new CBaseColorInfo[size];
	
	for(int index = 0;index<size;index++){
		CBaseColorInfo colorInfo = _colorData[index];
		CRGBtoHSI bean(colorInfo);
		bean.RGBToHSI();
		
		CColorSpaceInfo hsi = bean.GetHSI();
		
		hsi.SetPara3(hsi.GetPara3()*0.5);
		bean.SetHSI(hsi);
		bean.HSIToRGB();
		bean.ScaleRGB();
		
		CBaseColorInfo hsiInfo = bean.GetResult();
		newColor[index] = hsiInfo;
	}
	ShowPicByArray(newColor, width, height);
	delete []newColor;
}

void CImageStuDlg::Onhffuman() 
{
	// TODO: Add your command handler code here
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int pixelCount = width*height;
	int * grayData = new int[pixelCount];
	for(int index = 0;index<=pixelCount-1;index++){
		grayData[index] = _grayData[index];
	}
	
	//灰度等级
	const int GRAY_LEVEL = 256;
	//哈夫曼编码
	CImgHuffman huf(grayData,pixelCount,GRAY_LEVEL);
	huf.HuffmanCode();
	//码表
		  
	std::string * codeTable = huf.get_codeTable();
	TRACE("码表：\n");
	for(index = 0;index<=GRAY_LEVEL-1;index++){
		  TRACE("%d, %s\n",index,codeTable[index].c_str());
	}
		  
	delete [] grayData;
	//delete [] codeTable;
}

void CImageStuDlg::Onyuzhi() 
{
	double chuZhi = 0;
	// TODO: Add your command handler code here
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int * img = new int[size];
	
	int sum = 0 ;
	for(int i = 0 ;i < size; ++i ){
		sum+=_grayData[i];
		img[i] = _grayData[i];
	}
	chuZhi = sum /size;
	
	double diff = 100;
	while (diff >= 0.1)
	{
		
		//计算整值
		int sumXiao = 0;
		int sumDa = 0;
		int numXiao = 0;
		int numDa = 0;
		for(i=0;i<size;++i){
			if(_grayData[i] >chuZhi){
				sumDa+=_grayData[i];
				++numDa;
			}
			else{
				sumXiao += _grayData[i];
				++numXiao;
			}
		}
		
		double junXiao = sumXiao /numXiao;
		double junDa = sumDa /numDa;
		double newT = (junXiao+junDa)/2;
		//计算差值
		diff = fabs(newT-chuZhi);
		
		chuZhi = newT;
		
	}
	//阈值处理
	for(i=0;i<size;++i){
		if(img[i] <chuZhi){
			img[i] = 0;
		}
		else{
			img[i] = 255;
		}
	}
	
	CString str;
	str.Format("%lf",chuZhi);
	MessageBox(str);
	ShowPicByArray(img, width, height);
	delete []img;
}
