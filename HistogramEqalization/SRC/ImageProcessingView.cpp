
// ImageProcessingView.cpp : CImageProcessingView Ŭ������ ����
//

#include "stdafx.h"
#include "ImageProcessing.h"

#include "MainFrm.h"
#include "ImageProcessingDoc.h"
#include "ImageProcessingView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageProcessingView

IMPLEMENT_DYNCREATE(CImageProcessingView, CScrollView)

BEGIN_MESSAGE_MAP(CImageProcessingView, CScrollView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CImageProcessingView ����/�Ҹ�

CImageProcessingView::CImageProcessingView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CImageProcessingView::~CImageProcessingView()
{
}

BOOL CImageProcessingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CScrollView::PreCreateWindow(cs);
}

// CImageProcessingView �׸���

void CImageProcessingView::OnDraw(CDC* pDC)
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	if(pDoc->GetImage())
	{
		pDoc->GetImage()->Draw(pDC->GetSafeHdc());
	}
}

void CImageProcessingView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);


	CImageProcessingDoc* pDoc = GetDocument();
	CxImage* ima = pDoc->GetImage();
	if (ima) {
		int px=GetScrollPos(SB_HORZ);
		int py=GetScrollPos(SB_VERT);
		CSize sz(GetTotalSize());
		int x=(int)(ima->GetWidth());
		int y=(int)(ima->GetHeight());
		SetScrollSizes(MM_TEXT,	CSize(x,y));
		CSize sz2(GetTotalSize());

		CWnd* pFrame=GetParentFrame();
		RECT rClient;
		pFrame->GetClientRect(&rClient);

		if (sz.cx!=0 && sz.cy!=0){
			if (x>rClient.right) SetScrollPos(SB_HORZ,sz2.cx*px/sz.cx); else  SetScrollPos(SB_HORZ,0);
			if (y>rClient.bottom) SetScrollPos(SB_VERT,sz2.cy*py/sz.cy); else SetScrollPos(SB_VERT,0);
		}

		if (!(pFrame->IsIconic()||pFrame->IsZoomed())){
			RECT rMainCl,rFrame,rMainFr;
			(AfxGetApp()->m_pMainWnd)->GetClientRect(&rMainCl);
			(AfxGetApp()->m_pMainWnd)->GetWindowRect(&rMainFr);
			pFrame->GetWindowRect(&rFrame);
			pFrame->SetWindowPos(0,0,0,
				(4+rFrame.right-rFrame.left-rClient.right+rClient.left)+
				min(rMainCl.right-(rFrame.left-rMainFr.left+12),x),
				(4+rFrame.bottom-rFrame.top-rClient.bottom+rClient.top)+
				min(rMainCl.bottom-(rFrame.top-rMainFr.top+12),y),
				SWP_NOMOVE|SWP_NOZORDER);
		}

		CMainFrame* pMain = (CMainFrame*) AfxGetMainWnd();
		if (pMain->GetHistogramDlg()->IsWindowVisible()){
			pMain->GetHistogramDlg()->Invalidate();
		}
	}
}

void CImageProcessingView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	CImageProcessingDoc* pDoc = GetDocument();
	if (pDoc){
		CxImage*  ima  = pDoc->GetImage();
		if (ima){
			SetScrollSizes(MM_TEXT,CSize((int)(ima->GetWidth()), (int)(ima->GetHeight())));
		}
	}

	// TODO: ������׷� â ��ȿȭ // DONE
	((CMainFrame*)AfxGetMainWnd())->GetHistogramDlg()->Invalidate();

	CScrollView::OnUpdate(pSender, lHint, pHint);
}

void CImageProcessingView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
	// TODO: ������׷� â ��ȿȭ // DONE
	if (bActivate){
		((CMainFrame*)AfxGetMainWnd())->GetHistogramDlg()->Invalidate();
	}

	CScrollView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}


// CImageProcessingView �μ�

BOOL CImageProcessingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CImageProcessingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CImageProcessingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CImageProcessingView ����

#ifdef _DEBUG
void CImageProcessingView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImageProcessingView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImageProcessingDoc* CImageProcessingView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageProcessingDoc)));
	return (CImageProcessingDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageProcessingView �޽��� ó����



void CImageProcessingView::OnDestroy()
{
	CScrollView::OnDestroy();

	// TODO: ������׷� â ��ȿȭ // DONE
	((CMainFrame*)AfxGetMainWnd())->GetHistogramDlg()->Invalidate();
}


