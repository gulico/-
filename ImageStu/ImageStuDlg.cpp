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
	
	// ͼ���Ѵ򿪱��
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
	
	// ��ͼ
	CDC * pDC = GetDC();
	if( _flag == true ){
		
		// �Ѿ����ļ�
		SetDIBitsToDevice(
			pDC->m_hDC  // �豸������
			, 0 // �豸������λͼ�������ʼ�߼�x����
			, 0 // �豸������λͼ�������ʼ�߼�y����
			, _infoHeader.biWidth // DIB�Ŀ��
			, _infoHeader.biHeight // DIB�ĸ߶�
			, 0 // DIB��ʼ��ȡ������������ݵ�xλ��
			, 0 // DIB��ʼ��ȡ������������ݵ�yλ��
			, 0 // DIB�����ص�ˮƽ�к�, ��ӦlpBits�ڴ滺�����ĵ�һ������
			, _infoHeader.biHeight  // DIB������
			, _lpBuf  // ��������
			, _bitmapInfo //BITMAPINFO����
			, DIB_RGB_COLORS // ��ʾ����ɫ
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
// ���ٶԻ���, ӳ��WM_DESTORY��Ϣ
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
/*                           �˵�                                       */
/************************************************************************/

//////////////////////////////////////////////////////////////////////////
// "�ļ�"-->"��"(IDC_FILE_OPEN)
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::OnFileOpen() 
{
	// TODO: Add your command handler code here
	
	LPCTSTR lpszFilter = "BMP Files(*.bmp)|*.bmp|�κ��ļ�|*.*|";
	CFileDialog dlg( TRUE, lpszFilter, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		lpszFilter, NULL );
	// �ļ���
	CString fileName;
	CFile file;
	// ���ļ�
	if( dlg.DoModal() == IDOK ){
		
		// �ļ���
		fileName = dlg.GetPathName();
		if( file.Open( fileName, CFile::modeRead | CFile::shareDenyNone, NULL ) == 0 ){
			// ��ȡ�ļ�ʧ��
			AfxMessageBox( "�޷����ļ�", MB_OK, MB_ICONERROR );
			return;
		}
		
		// ��ȡ�ļ�ͷ
		if( !ReadFileHeader( file ) ){
			return;
		}
		
		// ��ȡ��Ϣͷ 
		if( !ReadInfoHeader( file ) ){
			return;
		}
		
		// ��ǰ�������ļ��򿪣����ͷ���Ӧ������
		if( _flag == true ){
			FreeData();
			_flag = false;
		}
		
		// �����ɫ����ɫ����
		_numQuad = CalcQuadNum();
		// ��ȡ��ɫ������
		ReadQuad( file );
		
		// �ж�ͼ������
		_imageType = CalcImageType();
		
		// ����ͼ������
		ReadImageData( file );
		
		
		
		
		// ���䴦��������
		_processBuf = ( BYTE * )HeapAlloc( GetProcessHeap(), 0, _infoHeader.biSizeImage );
		
		// ��Ȳ���4�ı�������
		DWORD dwBytes = ((DWORD) _infoHeader.biWidth * _infoHeader.biBitCount) / 32;
		if(((DWORD) _infoHeader.biWidth * _infoHeader.biBitCount) % 32) {
			dwBytes++;
		}
		dwBytes *= 4;
		
		
		
		Invalidate( );
		
		int width = _infoHeader.biWidth;
        int height = _infoHeader.biHeight;
		
		// ����ռ�
		_colorData = new CBaseColorInfo[ width * height ];
		_grayData = new int[ width * height ];
		
		// ����ͼ�����ͣ�����ת������Ӧ��ͼ������
		if( _imageType == COLOR_24_BIT ){
			// 24λ��ɫͼ��
			BMPConvertColor24();
			
		}
		else if( _imageType == COLOR_8_BIT ){
			// 256��ɫͼ��
			BMPConvertColor8();
		}
		else if( _imageType == GRAY_8_BIT ){
			// 256�Ҷ�ͼ��
			BMPConvertGray8();
			// ��8λ�Ҷ�����ת����24λ��ɫ
			Gray8ConvertColor24( _grayData, _colorData, width, height );
		}
		else{
			MessageBox( "�ݲ�֧�ָ�ͼ������" );
			// �ر�ͼ��
			file.Close();
			FreeData();
			return;
		}
		
		// ͼ���ȡ���
		file.Close();
		_flag = true;
		
	}
	
}


//////////////////////////////////////////////////////////////////////////
// "�ļ�"-->"��ʾ����ͼ��"
// ��ת�����24λ��ɫ�����ڶԻ�������ʾ
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::OnFileShowArray() 
{
	// TODO: Add your command handler code here
	
	if(_flag == FALSE){
		MessageBox("û�д�ͼ��");
		return;
	}
	
	CDlgShowArray dlg;
	dlg.SetColorData( _colorData );
	dlg.SetWidth( _infoHeader.biWidth );
	dlg.SetHeight( _infoHeader.biHeight );
	dlg.DoModal();
	
}


//////////////////////////////////////////////////////////////////////////
// "�ļ�"-->"����"�˵�
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::OnFileSave() 
{
	// TODO: Add your command handler code here
	if( ! _flag  ){
		MessageBox( "û��ͼƬ���޷�����" );
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
/*                         ˽�к���                                     */
/************************************************************************/
//////////////////////////////////////////////////////////////////////////
// ��ȡ�ļ�ͷ
// ����:
//   file: CFile &, BMP�ļ�
// ����ֵ:
//   BOOL, TRUE: �ɹ�; FALSE: ʧ��
//////////////////////////////////////////////////////////////////////////
BOOL CImageStuDlg::ReadFileHeader( CFile &file ){
	
	// ��ȡ�ļ�ͷ
	file.Read( &_fileHeader, sizeof( _fileHeader ) );
	// �ж��Ƿ�ΪBMP�ļ�
	if( _fileHeader.bfType != 0x4d42 ){
		// "BM"
		AfxMessageBox( "����BMP�ļ�", MB_OK, MB_ICONERROR );
		return FALSE;
	}
	
	// �ж��ļ��Ƿ���(�ļ���С�Ƿ����ļ�ͷ����Ϣһ��)
	if( file.GetLength() != _fileHeader.bfSize ){
		AfxMessageBox( "�ļ�����", MB_OK, MB_ICONERROR );
		return FALSE;
	}
	
	return TRUE;
	
}


//////////////////////////////////////////////////////////////////////////
// ��ȡ�ļ���Ϣͷ
// ����:
//   file: CFile &, �Ѿ��򿪵�BMP�ļ�
// ����ֵ:
//   BOOL, TRUE�ɹ�; ����ʧ��
//////////////////////////////////////////////////////////////////////////
BOOL CImageStuDlg::ReadInfoHeader( CFile &file ){
	
	// ��ȡ�ļ���Ϣͷ
	file.Read( &_infoHeader, sizeof( _infoHeader ) );
	
	// ��ͼƬ��ʽ�޶���8λͼ��
	// 	if( _infoHeader.biBitCount != 8 ){
	// 		AfxMessageBox( "����Ϊ8λ�Ҷ�ͼ", MB_OK, MB_ICONERROR );
	// 		return FALSE;
	// 	}
	
	return TRUE;
	
}


//////////////////////////////////////////////////////////////////////////
// �ͷ�����
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::FreeData(){
	
	HeapFree( GetProcessHeap(), 0, _bitmapInfo );
	HeapFree( GetProcessHeap(), 0, _lpBuf );
	// ����������
	HeapFree( GetProcessHeap(), 0, _processBuf );
	// �Ҷ���ɫ����
	delete [] _grayData;
	// ��ɫ��ɫ����
	delete [] _colorData;
	
	
	
}

//////////////////////////////////////////////////////////////////////////
// �����ɫ����ɫ����
// ����: ��
// ����ֵ:
//   int, ��ɫ����ɫ����
//////////////////////////////////////////////////////////////////////////
int CImageStuDlg::CalcQuadNum(){
	
	// �����ɫ������
	int numQuad = 0;
	if( _infoHeader.biBitCount < 24){
		// �൱��2��biBitCount�η�
		numQuad = ( 1 << _infoHeader.biBitCount );
	}
	
	return numQuad;
	
}

//////////////////////////////////////////////////////////////////////////
// ��ȡ��ɫ������
// ����:
//   file: CFile &, BMP�ļ�
// ����ֵ: ��
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::ReadQuad( CFile &file ){
	
	// Ϊͼ����Ϣpbi����ռ�
	_bitmapInfo = ( BITMAPINFO * )HeapAlloc( 
		GetProcessHeap(), 
		0, 
		sizeof( BITMAPINFOHEADER ) + _numQuad * sizeof( RGBQUAD ) 
		);
	memcpy( _bitmapInfo, &_infoHeader, sizeof( _infoHeader ) );
	_quad = ( RGBQUAD * )( ( BYTE *)_bitmapInfo + sizeof( BITMAPINFOHEADER ) );
	
	// ��ȡ��ɫ��
	if( _numQuad != 0 ){
		file.Read( _quad, sizeof( RGBQUAD ) * _numQuad );
	}
	
}

//////////////////////////////////////////////////////////////////////////
// �ж��Ƿ�Ϊ256ɫ�Ҷ�ͼ
// �ж����ݣ���ɫ����������ɫ�ĵ�RGB��������Ӧ�����
// BOOL: TRUEΪ256ɫ�Ҷ�ͼ
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
// ����ͼ������
// ����:
//   file: CFile &, BMPͼ��
// ����ֵ: ��
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::ReadImageData( CFile &file ){
	
	// Ϊͼ����������ռ�
	_infoHeader.biSizeImage = _fileHeader.bfSize - _fileHeader.bfOffBits;
	_lpBuf = ( BYTE *)HeapAlloc( GetProcessHeap(), 0, _infoHeader.biSizeImage );
	// ��ȡͼ������
	file.Read( _lpBuf, _infoHeader.biSizeImage );
	
}

//////////////////////////////////////////////////////////////////////////
// �ж�ͼ������
// ����: ��
// ����ֵ: IMAGE_TYPE, ͼ������, ����ö��IMAGE_TYPE�Ķ���
//////////////////////////////////////////////////////////////////////////
IMAGE_TYPE CImageStuDlg::CalcImageType(){
	
	IMAGE_TYPE type = COLOR_24_BIT;
	if( _infoHeader.biBitCount == IMAGE_TYPE_BIT_24 ){
		// 24��ɫͼ��
		type = COLOR_24_BIT;
		//MessageBox( "24λͼ��" );
	}
	else if( _infoHeader.biBitCount == IMAGE_TYPE_BIT_1 ){
		// ��ֵͼ��
		type = GRAY_1_BIT;
		//MessageBox( "1λͼ��" );
	}
	else if( _infoHeader.biBitCount == IMAGE_TYPE_BIT_8 ){
		// 8λ
		if( Is256Gray() ){
			// 8λ�Ҷ�ͼ��
			type = GRAY_8_BIT;
			//MessageBox( "8λ�Ҷ�ͼ��" );
		}
		else{
			// 8λ��ɫͼ��
			type = COLOR_8_BIT;
			//MessageBox( "8λ��ɫͼ��" );
		}
	}
	
	return type;
	
}

//////////////////////////////////////////////////////////////////////////
// ��BMP����ת����24λ��ɫ����
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::BMPConvertColor24(){
	
	// ��Ȳ���4�ı�������
	DWORD dwBytes = ((DWORD) _infoHeader.biWidth * _infoHeader.biBitCount) / 32;
	if(((DWORD) _infoHeader.biWidth * _infoHeader.biBitCount) % 32) {
		dwBytes++;
	}
	dwBytes *= 4;
	
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	// �����ɫ����
	
	int i,j;
	
	for( i = 0; i <= height - 1; i++ ){
		for( j = 0; j <= width - 1; j++ ){
			
			// BMPͼƬ�����е�����
			DWORD index = i * 3 * width + 3 * j;
			if( dwBytes % 3 != 0 ){
				index = i * dwBytes + 3 * j ;
			}
			// ��ɫ�����е�����
			DWORD resultIndex = ( height - 1 - i ) * width + j;
			_colorData[ resultIndex ].SetRed( _lpBuf[ index  + 2 ] );
			_colorData[ resultIndex ].SetGreen( _lpBuf[ index  + 1 ] );
			_colorData[ resultIndex ].SetBlue( _lpBuf[ index ] );
			
		}// for j
	}// for i 
	
}

//////////////////////////////////////////////////////////////////////////
// ��8λ��ɫBMP����ת��24λ��ɫ����
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::BMPConvertColor8(){
	
	// ��Ȳ���4�ı�������
	DWORD dwBytes = ((DWORD) _infoHeader.biWidth * _infoHeader.biBitCount) / 32;
	if(((DWORD) _infoHeader.biWidth * _infoHeader.biBitCount) % 32) {
		dwBytes++;
	}
	dwBytes *= 4;
	
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	// �����ɫ����
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
			
			// BMPͼƬ�����е�����
			DWORD index = i * dwBytes + j ;
			
			// ��ɫ�����е�����
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
// ��8λ�Ҷ�BMP����ת��8λ�Ҷ�����
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::BMPConvertGray8(){
	
	// ��Ȳ���4�ı�������
	DWORD dwBytes = ((DWORD) _infoHeader.biWidth * _infoHeader.biBitCount) / 32;
	if(((DWORD) _infoHeader.biWidth * _infoHeader.biBitCount) % 32) {
		dwBytes++;
	}
	dwBytes *= 4;
	
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	// �����ɫ����
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
			
			// BMPͼƬ�����е�����
			DWORD index = i * dwBytes + j ;
			
			// ��ɫ�����е�����
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
// ��8λ�Ҷ�����ת����24λ��ɫ
// �Ҷ�ͼ��RGBֵ����ͬ
// ����:
//   grayData: BYTE *, �Ҷ�����
//   colorData: CBaseColorInfo *, 24λ��ɫ����
//   width: ͼƬ���
//   height: ͼƬ�߶�
//  ����ֵ: ��
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

// ��8λ�Ҷ�����ת����24λ��ɫ
void CImageStuDlg::Gray8ConvertColor24( int * grayData, CBaseColorInfo * colorData, int width, int height ){
	
	int length = width * height;
	for( int i = 0; i <= length - 1; i++ ){
		colorData[ i ].SetRed( grayData[ i ] );
		colorData[ i ].SetGreen( grayData[ i ] );
		colorData[ i ].SetBlue( grayData[ i ] );
	}
	
}

//////////////////////////////////////////////////////////////////////////
// ��ʾͼ��(ͨ��ͼ������,��ɫͼ��)
// ����:
//   colorData: CBaseColorInfo, ��ɫ����
//   width: int, ͼ����
//   height: int, ͼ��߶�
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::ShowPicByArray( CBaseColorInfo * colorData, 
								  int width, 
								  int height ){
	
	CDlgShowArray dlg;
	// ͼ������(24λ��ɫͼ��)
	dlg.SetColorData( colorData );
	// ͼ����
	dlg.SetWidth( width );
	// ͼ��߶�
	dlg.SetHeight( height );
	// ��ʾ�Ի���
	dlg.DoModal();
	
}




//////////////////////////////////////////////////////////////////////////
// ��ʾͼ��(ͨ��ͼ������, �Ҷ�ͼ��)
// ����:
//   colorData: CBaseColorInfo, �Ҷ�ͼ������
//   width: int, ͼ����
//   height: int, ͼ��߶�
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::ShowPicByArray( int * grayData, 
								  int width, 
								  int height ){
	
	// ���Ҷ�ͼ��ת�ɲ�ɫͼ��
	CBaseColorInfo * colorData = new CBaseColorInfo[ width * height ];
	Gray8ConvertColor24( grayData, colorData, width, height );
	
	CDlgShowArray dlg;
	// ͼ������(24λ��ɫͼ��)
	dlg.SetColorData( colorData );
	// ͼ����
	dlg.SetWidth( width );
	// ͼ��߶�
	dlg.SetHeight( height );
	// ��ʾ�Ի���
	dlg.DoModal();
	
	// �ͷŲ�ɫͼ��
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
	
	// ��ʾͼ��
	ShowPicByArray( img, width, height );
	
	delete []img;
}


//////////////////////////////////////////////////////////////////////////
// ���ܣ�����BMPͼƬ
// ������
//   bmpName: char *, �ļ���(��·�����ļ���׺)
//   imgBuf: unsigned char *, ͼ������
//   width: int, ͼ����
//   height: int, ͼ��߶�
//   biBitCount: int, �������
//   pColorTable: RGBAUAD *, ��ɫ��
//////////////////////////////////////////////////////////////////////////
bool CImageStuDlg::SaveAsBmp( char * bmpName, 
							 unsigned char * imgBuf, 
							 int width, 
							 int height,
							 int biBitCount, 
							 RGBQUAD * pColorTable 
							 ){
	
	// ���λͼ����Ϊ�գ���û�����ݴ���
	if( !imgBuf ){
		return false;
	}
	
	// ��ɫ���С�����ֽ�Ϊ��λ���Ҷ�ͼ����ɫ��Ϊ1024����ɫͼ����ɫ���СΪ0
	int colorTableSize = 0;
	if( biBitCount == 8 ){
		colorTableSize = 1024; // �о���һ����ȷ
	} 
	
	// �����洢ͼ������ÿ���ֽ���תΪ4�ı���
	int lineByte = ( width * biBitCount / 8 + 3 ) / 4 * 4;
	// �Զ����Ƶ�д�ķ�ʽ���ļ�
	FILE *fp = fopen( bmpName, "wb" );
	if( !fp ){
		return false;
	}
	
	// ����λͼ�ļ�ͷ�ṹ��������д�ļ�ͷ��Ϣ
	BITMAPFILEHEADER fileHead;
	fileHead.bfType = 0x4D42;// bmp����
	// bfSize��ͼ���ļ�4����ɲ���֮��
	fileHead.bfSize = sizeof( BITMAPFILEHEADER ) 
		+ sizeof( BITMAPINFOHEADER )
		+ colorTableSize 
		+ lineByte * height; // ͼ�������ֽ���
	fileHead.bfReserved1 = 0;
	fileHead.bfReserved2 = 0;
	
	// bfOffBits��ͼ���ļ�ǰ����������ռ�֮��
	fileHead.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)  + colorTableSize;
	// �ļ�ͷд���ļ�
	fwrite( &fileHead, sizeof( BITMAPFILEHEADER ) , 1, fp );
	
	// ����λͼ��Ϣͷ�ṹ��������д��Ϣͷ��Ϣ
	BITMAPINFOHEADER head;
	head.biSize = sizeof(BITMAPINFOHEADER); // λͼ��Ϣͷ�ṹ�Ĵ�С(40���ֽ�)
	head.biWidth = width;// ͼ���ȣ�������Ϊ��λ
	head.biHeight = height;// ͼ��߶ȣ�������Ϊ��λ
	head.biPlanes = 1;// ����Ϊ1
	head.biBitCount = biBitCount; // ������ȣ�ÿ�����ص�Ϊ��(bit��)
	head.biCompression = BI_RGB; // ͼ���Ƿ�ѹ����һ����δѹ����
	head.biSizeImage = lineByte * height; // ʵ�ʵ�λͼ����ռ�ݵ��ֽ���
	head.biXPelsPerMeter = 0; // Ŀ���豸��ˮƽ�ֱ���
	head.biYPelsPerMeter = 0; // Ŀ���豸�Ĵ�ֱ�ֱ���
	head.biClrUsed = 0; // ��ͼ��ʵ���õ�����ɫ��
	head.biClrImportant = 0; // ��ͼ����Ҫ����ɫ�����Ϊ0�������е���ɫ����Ҫ 
	
	// дλͼ��Ϣͷ���ڴ�
	fwrite( &head, sizeof( BITMAPINFOHEADER ), 1, fp );
	
	// ���ͼ��ʱ�Ҷ�ͼ������ɫ��д���ļ�
	if( biBitCount == 8 ){
		fwrite( pColorTable, sizeof( RGBQUAD ), 256, fp );
	}
	
	// дλͼ���ݽ��ļ�
	fwrite( imgBuf, height * lineByte, 1, fp );
	
	// �ر��ļ�
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
	
	//�ͷ�
	delete [] img;
	
}

void CImageStuDlg::OnbeRedBlue() 
{
	// TODO: Add your command handler code here
	int width = 800;
	int height = 600;
	int size = width * height;
	//����ͼƬ
	CBaseColorInfo * img = new CBaseColorInfo[ size ];
	
	//��ֵ
	for( int x = 0; x < width; ++x ){
		for( int y = 0; y < height; ++y ){
			if( ( ( x / 40 ) % 2 ) ==  ( ( y / 30 ) % 2 ) ){
				//��ɫ
				int index = y * width + x;
				img[ index ] = CBaseColorInfo( 255, 0, 0 );
			}
			else{
				//��ɫ
				int index = y * width + x;
				img[ index ] = CBaseColorInfo( 0, 0, 255 );
			}
		}
	}
	
	//��ʾ
	ShowPicByArray( img, width, height );
	
	//�ͷ�
	delete [] img ;
}

void CImageStuDlg::OnbeGrey() 
{
	// TODO: Add your command handler code here
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	//����ͼƬ
	CBaseColorInfo * img = new CBaseColorInfo[ size ];
	int *grayData = new int[size];
	//��ֵ
	for( int x = 0; x < size; ++x ){
		CBaseColorInfo info = _colorData[x];
		int gray = 0.299 * info.GetRed()+ 0.587 * info.GetGreen()+ 0.114 * info.GetBlue();
		
		img[x] = CBaseColorInfo(gray,gray,gray);
		grayData[x] = gray;
	}
	
	//��ʾ
	ShowPicByArray( grayData, width, height );
	
	//�ͷ�
	delete [] img ;	
}

void CImageStuDlg::OnbeBlack() 
{
	// TODO: Add your command handler code here
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	//����ͼƬ
	int * img = new int[ size ];
	//��ֵ
	int gray =100;//��ֵ
	for( int i = 0; i < size; ++i ){
		if(_grayData[i]>gray){
			img[i] = 255;
		}else{
			img[i] = 0;
		}
	}
	
	//��ʾ
	ShowPicByArray( img, width, height );
	
	//�ͷ�
	delete [] img ;	
}

void CImageStuDlg::OnGreyPix() 
{
	// TODO: Add your command handler code here
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	//����ͼƬ
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
	//�ͷ�
	delete [] img ;	
}

void CImageStuDlg::OntoBiger() 
{
	// TODO: Add your command handler code here
	double scale = 0.8;//����ϵ��
	int width = _infoHeader.biWidth * scale;//���տ��
	int height = _infoHeader.biHeight * scale;//���ճ���
	int size = width * height;//���մ�С
	int * img = new int[ size ];
	
	int oldWidth = _infoHeader.biWidth;//ԭʼ���
	int oldHeight = _infoHeader.biHeight;//ԭʼ�߶�
	
	for( int x = 0 ; x < width ; ++x ){
		for( int y = 0 ; y < height ; ++y ){
			//��������
			int oldX = x / scale ;
			int oldY = y / scale ;
			//��ֵ
			int newIndex = y * width + x;
			int oldIndex = oldY * oldWidth + oldX;
			img[ newIndex ] = _grayData[ oldIndex];
		}
	}
	ShowPicByArray( img, width, height );
	//�ͷ�
	delete [] img ;	
	
}

void CImageStuDlg::OnQianxiang() 
{
	// TODO: Add your command handler code here
	// TODO: Add your command handler code here
	double scale = 0.8;//����ϵ��
	int width = _infoHeader.biWidth * scale;//���տ��
	int height = _infoHeader.biHeight * scale;//���ճ���
	int size = width * height;//���մ�С
	int * img = new int[ size ];
	
	int oldWidth = _infoHeader.biWidth;//ԭʼ���
	int oldHeight = _infoHeader.biHeight;//ԭʼ�߶�
	
	for( int x = 0 ; x < oldWidth ; ++x ){
		for( int y = 0 ; y < oldHeight ; ++y ){
			//��������
			int newX = x * scale ;
			int newY = y * scale ;
			//��ֵ
			int newIndex = newY * width + newX;
			int oldIndex = y * oldWidth + x;
			img[ newIndex ] = _grayData[ oldIndex];
		}
	}
	ShowPicByArray( img, width, height );
	//�ͷ�
	delete [] img ;	
}

void CImageStuDlg::Onshuangxianxing() //�������Բ�ֵ
{
	// TODO: Add your command handler code here
	double scale = 0.8;//����ϵ��
	int width = _infoHeader.biWidth * scale;//���տ��
	int height = _infoHeader.biHeight * scale;//���ճ���
	int size = width * height;//���մ�С
	int * img = new int[ size ];
	
	int oldWidth = _infoHeader.biWidth;//ԭʼ���
	int oldHeight = _infoHeader.biHeight;//ԭʼ�߶�
	
	for( int x = 0 ; x < width ; ++x ){
		for( int y = 0 ; y < height ; ++y ){
			double oldX = x / scale ;
			double oldY = y / scale ;
			//��ֵ
			int newIndex = y * width + x;
			int oldIndex = oldY * oldWidth + oldX;
			//img[ newIndex ] = _grayData[ oldIndex ];
			//1)ȷ���ĸ�����ABCD
			//A��
			int Ax = oldX;
			int Ay = oldY;
			int AIndex = Ay * oldWidth + Ax ;
			int gA = _grayData[ AIndex ];
			
			//B��
			int Bx = oldX + 1;
			int By = oldY;
			int BIndex = AIndex + 1 ;
			int gB = _grayData[ BIndex ];
			
			//����gE��
			double gE = (oldX - Ax) * (gB - gA) + gA;
			
			//C��
			int Cindex = AIndex + oldWidth;
			int gC = _grayData[ Cindex ];
			
			//D��
			int Dindex = BIndex +oldWidth;
			int gD = _grayData[Dindex];
			double gF = ( oldX - Ax ) *( gD - gC) + gC;
			
			//���ռ���
			int gray = (oldY - Ay) * (gF -gE) + gE ;
			
			img[newIndex] = gray;
		}
	}
	ShowPicByArray( img, width, height );
	//�ͷ�
	delete [] img ;	
}

void CImageStuDlg::Onzuibiaobianhuan() //����
{
	// TODO: Add your command handler code here
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	//����ͼƬ
	int * img = new int[ size ];
	for(int x = 0 ; x < width ; ++x){
		for(int y = 0 ; y < height  ; ++y ){
			img[ y * width + x ] = _grayData[ y * width + width - x];
		}
	}
	ShowPicByArray( img, width, height );
	//�ͷ�
	delete [] img ;	
}



void CImageStuDlg::Onzhuanzhi() //ת��
{
	// TODO: Add your command handler code here
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	//����ͼƬ
	int * img = new int[ size ];
	for(int y = 0 ; y < height  ; ++y){
		for(int x = 0 ; x < width  ; ++x ){
			img[ x * height + y ] = _grayData [ y * width + x];
		}
	}
	ShowPicByArray( img, height, width );
	//�ͷ�
	delete [] img ;	
}

void CImageStuDlg::OngrayNegation() //�Ҷȱ任
{
	// TODO: Add your command handler code here
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	//����ͼƬ
	int * img = new int[ size ];
	for(int i = 0 ; i < size  ; ++i){
		img[i] = 255 - _grayData [ i ];
	}
	ShowPicByArray( img, width, height );
	//�ͷ�
	delete [] img ;	
}

void CImageStuDlg::OnpowerTransformation() //�ݴα任
{
	// TODO: Add your command handler code here
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	//����ͼƬ
	double c = 1;
	double Y = 0.4;
	int * img = new int[ size ];
	for(int i = 0 ; i < size  ; ++i){
		img[i] = c * pow(_grayData[i],Y);
	}
	ShowPicByArray( img, width, height );
	//�ͷ�
	delete [] img ;	
}

void CImageStuDlg::OnlogarithmicTransform() //�����任
{
	// TODO: Add your command handler code here
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	//����ͼƬ
	int * img = new int[ size ];
	int c = 40;
	for(int i = 0 ; i < size  ; ++i){
		img[i] = c * log(_grayData [ i ]+1) ;
	}
	ShowPicByArray( img, width, height );
	//�ͷ�
	delete [] img ;	
}

void CImageStuDlg::OnsegmenteFunction() //�ֶα任
{
	// TODO: Add your command handler code here
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	//����ͼƬ
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
	//�ͷ�
	delete [] img ;
}

void CImageStuDlg::OnplanePositionChart() //λƽ��
{
	// TODO: Add your command handler code here
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	//����ͼƬ
	int * img = new int[ size ];
	int ** PositionChart = new int*[9];
	int i,j;
	for(i=0;i<9;i++){
		PositionChart[i] = new int[size];
	}
	//����ƽ��
	int * gray = new int[ size ];
	for(j=0;j<size;++j){
		gray[j] = _grayData[j];
	}
	for(i=0;i<8;++i){//8��ƽ��
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
			if(i!=6){//ɾȥ��6��ƽ��
				img[j] = img[j]+PositionChart[i][j];
			}
		}
	}
	ShowPicByArray( img, width, height );
	//�ͷ�
	for(i=0;i<9;i++){
		delete[] PositionChart[i];
	}
	delete[] PositionChart;
	delete [] img ;
}

void CImageStuDlg::OnhistogramEqualization() //ֱ��ͼ���⻯
{
	// TODO: Add your command handler code here
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	//����ͼƬ
	int * img = new int[ size ];
	const int LEVEL = 256;
	int rule[LEVEL] = {0};
	
	int i;
	int yuanshi[ LEVEL] = {0};//ԭʼֱ��ͼ
	//����ԭʼֱ��ͼ
	for( i=0 ; i< size ;++i){
		int gray = _grayData[i];
		++yuanshi[gray];
	}
	//����
	/*std::stringstream stream;
	for(i=0;i<LEVEL;++i){
	stream<<yuanshi[i]<<",";
	}
	::OutputDebugString(stream.str().c_str());*/
	//��һ��
	double guiYiHua[LEVEL] = {0};
	for(i=0;i<LEVEL;++i){
		guiYiHua[i] = yuanshi[i]*1.0/size;
	}
	//����
	/*std::stringstream stream;
	for(i=0;i<LEVEL;++i){
	stream<<guiYiHua[i]<<",";
	}
	::OutputDebugString(stream.str().c_str());*/
	//����ֱ��ͼ
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
	//�ͷ�
	delete [] img ;	
}

void CImageStuDlg::OnswiftCaculate() //�����ֵ�Ŀ�������
{
	// TODO: Add your command handler code here
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	//����ͼƬ
	int * img = new int[ size ];
	int *temp =new int[size];
	
	//ˮƽ
	for(int y=1;y<height-1;++y){
		for(int x=1;x<width-1;++x){
			int sum = 0;
			for(int m=x-1;m<=x+1;++m){
				sum=sum+_grayData[y*width+m];
			}
			temp[y*width+x]=sum;
		}
	}
	//��ֱ
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
	//�ͷ�
	delete [] img ;	
	delete [] temp;
}

void CImageStuDlg::OnswiftWeightCaculate() //�����Ȩ�Ŀ�������
{
	// TODO: Add your command handler code here
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	//����ͼƬ
	int * img = new int[ size ];
	int *temp =new int[size];
	
	//ˮƽ
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
	//��ֱ
	for(int x = 1;x<width-1;++x){
		for(int y=1;y<height-1;++y){
			int sum = 0;
			for(int n=y-1;n<=y+1;++n){
				sum = sum+temp[n*width+x];
				if(n==y)// �м��һ��*2
					sum = sum + temp[n*width+x];
			}
			img[y*width+x] = sum;
		}
	}
	for(int i = 0 ; i<size;++i){
		img[i] = img[i]/16;
	}
	ShowPicByArray( img, width, height );
	//�ͷ�
	delete [] img ;	
	delete [] temp;
}

void CImageStuDlg::OnswiftTresoldCaculate() 
{
	//���"Fig3.36(a).bmp"������15��15�����ֵ�˲���
	//�˲����ͼ������ֵ��40%��Ϊ�˲�����ֵ�����ڸ���ֵ��ȡԭͼ��ĻҶȣ�С�ڸ���ֵ��ȡ0��
	// TODO: Add your command handler code here
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	//����ͼƬ
	int * img = new int[ size ];
	//int *temp =new int[size];
	
	int scale = 15;
	int step = scale/2;
	//ˮƽ
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
	//����������
	int i,max;
	for(i=0;i<size;++i){
		if(img[i]>max){
			max = img[i];
		}
	}
	
	//��ֵ����
	int Tresold = max*0.4;
	for(i=0;i<size;++i){
		if(img[i]<Tresold)
			img[i]=0;
		else
			img[i] = _grayData[i];
	}
	ShowPicByArray( img, width, height );
	//�ͷ�
	delete [] img ;	
	//delete [] temp;
}

void CImageStuDlg::OnmedianFilter() 
{
	// TODO: Add your command handler code here
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	//����ͼƬ
	int * img = new int[ size ];
	
	int model = 3;
	int step = model/2;
	int *linYu = new int[model*model];
	for(int x = step ; x<width-step;++x){
		for(int y= step; y <height-step;++y){
			//ȡ����
			int order = 0;
			for(int m = x - step ; m <= x + step ; ++m ){
				for(int n = y - step ; n <= y + step ; ++n ){
					int index = n * width +m;
					linYu[order] = _grayData[index];
					++order;
				}
			}
			//����
			std::stable_sort( linYu , linYu + model * model );
			//ȡ��ֵ
			img[ y * width + x ] = linYu[ model * model / 2 ];
		}
	}
	
	ShowPicByArray( img, width, height );
	//�ͷ�
	delete [] img ;	
	delete [] linYu;
}

void CImageStuDlg::OnlaplaceOperator() 
{
	// TODO: Add your command handler code here
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	//����ͼƬ
	int * img = new int[ size ];
	
	for(int x = 1; x < width - 1; ++x ){
		for(int y = 1 ; y < height - 1 ; ++y ){
			int index = y * width + x;
			img[ index ] = 4 * _grayData[ index ]
				-_grayData[index-1]
				-_grayData[index+1]
				-_grayData[index-width]
				-_grayData[index+width];
			
			//����ֵ
			if(img[index]<0){
				img[index]*=-1;
			}
		}
	}
	
	ShowPicByArray( img, width, height );
	//�ͷ�
	delete [] img ;	
}

void CImageStuDlg::OnRobert() //��������
{
	// TODO: Add your command handler code here
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	//����ͼƬ
	int * img = new int[ size ];
	for(int x = 0; x < width -1;++x){
		for(int y = 0 ;y < height-1;++y){
			int index = y*width+x;
			img[index] = fabs(_grayData[index+width+1]-_grayData[index])
				+fabs(_grayData[index+width]-_grayData[index+1]);
		}
	}
	
	ShowPicByArray( img, width, height );
	//�ͷ�
	delete [] img ;	
	
}

void CImageStuDlg::OnSobel() //sobel����
{
	// TODO: Add your command handler code here
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	//����ͼƬ
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
	//�ͷ�
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
	//��105,58������264,105��
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
		//����60��
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
	
	//�Ҷȵȼ�
	const int GRAY_LEVEL = 256;
	//����������
	CImgHuffman huf(grayData,pixelCount,GRAY_LEVEL);
	huf.HuffmanCode();
	//���
		  
	std::string * codeTable = huf.get_codeTable();
	TRACE("���\n");
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
		
		//������ֵ
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
		//�����ֵ
		diff = fabs(newT-chuZhi);
		
		chuZhi = newT;
		
	}
	//��ֵ����
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
