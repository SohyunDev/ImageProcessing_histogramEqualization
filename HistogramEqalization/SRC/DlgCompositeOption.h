#pragma once
#include "afxwin.h"


// DlgCompositeOption ��ȭ �����Դϴ�.

class DlgCompositeOption : public CDialog
{
	DECLARE_DYNAMIC(DlgCompositeOption)

public:
	DlgCompositeOption(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~DlgCompositeOption();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_COMPOSITE_OPTION };

// Ư���Դϴ�.
public:
	inline int GetCompositeOperatorID() { return m_nOperatorID; }
	inline CxImage * GetSecondImage() { return m_pSecondImage; }

private:
	CxImage * m_pFirstImage;
	CxImage * m_pSecondImage;
	int m_nOperatorID;

	CComboBox m_Combo_Operator;
	CComboBox m_Combo_SecondImage;

// �������Դϴ�.
public:
	virtual BOOL OnInitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnPaint();
	afx_msg void OnCbnSelchangeCoOperator();
	afx_msg void OnCbnSelchangeCoSecondImage();

	DECLARE_MESSAGE_MAP()
};
