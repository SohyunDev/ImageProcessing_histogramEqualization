// DlgCompositeOption.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "ImageProcessingDoc.h"

#include "DlgCompositeOption.h"


// DlgCompositeOption 대화 상자입니다.

IMPLEMENT_DYNAMIC(DlgCompositeOption, CDialog)

DlgCompositeOption::DlgCompositeOption(CWnd* pParent /*=NULL*/)
	: CDialog(DlgCompositeOption::IDD, pParent)
{
	m_pFirstImage = NULL;
	m_pSecondImage = NULL;
}

DlgCompositeOption::~DlgCompositeOption()
{
}

void DlgCompositeOption::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CO_OPERATOR, m_Combo_Operator);
	DDX_Control(pDX, IDC_CO_SECOND_IMAGE, m_Combo_SecondImage);
}


BEGIN_MESSAGE_MAP(DlgCompositeOption, CDialog)
	ON_WM_PAINT()
	ON_CBN_SELCHANGE(IDC_CO_OPERATOR, &DlgCompositeOption::OnCbnSelchangeCoOperator)
	ON_CBN_SELCHANGE(IDC_CO_SECOND_IMAGE, &DlgCompositeOption::OnCbnSelchangeCoSecondImage)
END_MESSAGE_MAP()


// DlgCompositeOption 메시지 처리기입니다.

BOOL DlgCompositeOption::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	// Set first image
	CImageProcessingDoc* pDoc = (CImageProcessingDoc*) ((CMDIFrameWnd*)AfxGetMainWnd())->MDIGetActive()->GetActiveView()->GetDocument();
	m_pFirstImage = pDoc->GetImage();

	// Set operator combobox
	m_Combo_Operator.AddString(_T("+"));
	m_Combo_Operator.AddString(_T("−"));
	m_Combo_Operator.AddString(_T("×"));
	m_Combo_Operator.AddString(_T("÷"));
	m_Combo_Operator.SetItemData(0, 0);
	m_Combo_Operator.SetItemData(1, 1);
	m_Combo_Operator.SetItemData(2, 2);
	m_Combo_Operator.SetItemData(3, 3);
	m_Combo_Operator.SetCurSel(0);
	m_nOperatorID = m_Combo_Operator.GetItemData(m_Combo_Operator.GetCurSel());

	// Set second image & combobox
	POSITION docTemplatePosiotion = AfxGetApp()->GetFirstDocTemplatePosition();
	CDocTemplate * pDocTemplate = AfxGetApp()->GetNextDocTemplate(docTemplatePosiotion);

	POSITION docPosition = pDocTemplate->GetFirstDocPosition();
	while (docPosition != NULL) {
		pDoc = (CImageProcessingDoc*) pDocTemplate->GetNextDoc(docPosition);
		m_Combo_SecondImage.AddString(pDoc->GetTitle());
		m_Combo_SecondImage.SetItemDataPtr(m_Combo_SecondImage.GetCount()-1, pDoc->GetImage());
	}
	m_Combo_SecondImage.SetCurSel(0);
	m_pSecondImage = (CxImage*)m_Combo_SecondImage.GetItemDataPtr(m_Combo_SecondImage.GetCurSel());

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void DlgCompositeOption::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialog::OnPaint()을(를) 호출하지 마십시오.

	if (m_pFirstImage)
		m_pFirstImage->Draw(dc.GetSafeHdc(), CRect(25,30,225,230));

	if (m_pSecondImage)
		m_pSecondImage->Draw(dc.GetSafeHdc(), CRect(403,30,603,230));
}

void DlgCompositeOption::OnCbnSelchangeCoOperator()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_nOperatorID = m_Combo_Operator.GetItemData(m_Combo_Operator.GetCurSel());
}

void DlgCompositeOption::OnCbnSelchangeCoSecondImage()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_pSecondImage = (CxImage*)m_Combo_SecondImage.GetItemDataPtr(m_Combo_SecondImage.GetCurSel());

	Invalidate();
}
