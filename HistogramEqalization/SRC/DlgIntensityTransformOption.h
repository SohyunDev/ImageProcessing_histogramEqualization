#pragma once


// DlgIntensityTransformOption ��ȭ �����Դϴ�.

class DlgIntensityTransformOption : public CDialog
{
	DECLARE_DYNAMIC(DlgIntensityTransformOption)

public:
	DlgIntensityTransformOption(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~DlgIntensityTransformOption();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_INTENSITY_TRANSFORM_OPTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	int m_nTransformType;
	double m_nLinearTransfromCoefficient_a;
	double m_nLinearTransfromCoefficient_b;
	BYTE m_byThresholdValue;
	BYTE m_byContrastStretching_Start;
	BYTE m_byContrastStretching_End;
};
