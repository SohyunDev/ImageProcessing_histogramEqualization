#pragma once


// DlgContrastStretchOption ��ȭ �����Դϴ�.

class DlgContrastStretchOption : public CDialog
{
	DECLARE_DYNAMIC(DlgContrastStretchOption)

public:
	DlgContrastStretchOption(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~DlgContrastStretchOption();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CONTRAST_STRETCH_OPTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	int m_nStretchType;
	float m_fLow;
	float m_fHigh;
};
