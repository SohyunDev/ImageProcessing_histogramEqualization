#pragma once


// DlgBrightnessOption ��ȭ �����Դϴ�.

class DlgBrightnessOption : public CDialog
{
	DECLARE_DYNAMIC(DlgBrightnessOption)

public:
	DlgBrightnessOption(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~DlgBrightnessOption();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_BRIGHTNESS_OPTION };

public:
	int m_nPlusMinus;
	BYTE m_byModifyValue;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:

};
