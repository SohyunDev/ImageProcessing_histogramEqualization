#pragma once


// DlgMosaicOption ��ȭ �����Դϴ�.

class DlgMosaicOption : public CDialog
{
	DECLARE_DYNAMIC(DlgMosaicOption)

public:
	DlgMosaicOption(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~DlgMosaicOption();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MOSAIC_OPTION };

public:
	DWORD m_dwWindowSize;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
