
// ImageViewerDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "ImageViewer.h"
#include "ImageViewerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageViewerDlg 대화 상자



CImageViewerDlg::CImageViewerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_IMAGEVIEWER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CImageViewerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CImageViewerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SELECT_BTN, &CImageViewerDlg::OnBnClickedSelectBtn)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CImageViewerDlg 메시지 처리기

BOOL CImageViewerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	GetClientRect(m_rect);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CImageViewerDlg::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		if(!m_image.IsNull())
		{
			dc.SetStretchBltMode(COLORONCOLOR);
			m_image.Draw(dc, m_rect);
		}
		//CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CImageViewerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CImageViewerDlg::OnBnClickedSelectBtn()
{
	wchar_t name_filter[] = L"모든 파일 (*.*)|*.*|Jpeg 파일 (*.jpg)|*.jpg|PNG 파일 (*.png)|*.png||";
	
	// 파일 열기 대화상자를 CFileDIalog에서 제공하고있음
	CFileDialog ins_dlg(TRUE, L"jpg", L"*.jpg", OFN_HIDEREADONLY | OFN_NOCHANGEDIR, name_filter);
	ins_dlg.m_ofn.nFilterIndex = 2;
	
	if (IDOK == ins_dlg.DoModal())
	{
		if (!m_image.IsNull()) m_image.Destroy();

		m_image.Load(ins_dlg.GetPathName());
		Invalidate(FALSE);
	}
}


void CImageViewerDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	/*GetClientRect(m_rect);*/
	m_rect.right = cx;
	m_rect.bottom = cy;
	Invalidate(FALSE);
}
