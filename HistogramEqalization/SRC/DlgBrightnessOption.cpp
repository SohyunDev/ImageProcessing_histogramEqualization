// DlgBrightnessOption.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "DlgBrightnessOption.h"


// DlgBrightnessOption ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(DlgBrightnessOption, CDialog)

DlgBrightnessOption::DlgBrightnessOption(CWnd* pParent /*=NULL*/)
	: CDialog(DlgBrightnessOption::IDD, pParent)
	, m_nPlusMinus(0)
	, m_byModifyValue(0)
{

}

DlgBrightnessOption::~DlgBrightnessOption()
{
}

void DlgBrightnessOption::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Radio(pDX, IDC_BO_PLUS, m_nPlusMinus);
	DDX_Text(pDX, IDC_BO_MODIFY_VALUE, m_byModifyValue);
}


BEGIN_MESSAGE_MAP(DlgBrightnessOption, CDialog)
END_MESSAGE_MAP()


// DlgBrightnessOption �޽��� ó�����Դϴ�.



