// DlgMosaicOption.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "DlgMosaicOption.h"


// DlgMosaicOption ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(DlgMosaicOption, CDialog)

DlgMosaicOption::DlgMosaicOption(CWnd* pParent /*=NULL*/)
	: CDialog(DlgMosaicOption::IDD, pParent)
	, m_dwWindowSize(10)
{

}

DlgMosaicOption::~DlgMosaicOption()
{
}

void DlgMosaicOption::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_MO_WIN_SIZE, m_dwWindowSize);
}


BEGIN_MESSAGE_MAP(DlgMosaicOption, CDialog)
END_MESSAGE_MAP()


// DlgMosaicOption �޽��� ó�����Դϴ�.
