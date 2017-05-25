
// ImageProcessingDoc.h : CImageProcessingDoc Ŭ������ �������̽�
//


#pragma once


class CImageProcessingDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CImageProcessingDoc();
	DECLARE_DYNCREATE(CImageProcessingDoc)

// Ư���Դϴ�.
public:
	inline CxImage *GetImage() { return m_pImage; }

	inline long GetHistogramRed(int i) { return m_histogramRed[i]; }
	inline long GetHistogramGreen(int i) { return m_histogramGreen[i]; }
	inline long GetHistogramBlue(int i) { return m_histogramBlue[i]; }
	inline long GetHistogramGray(int i) { return m_histogramGray[i]; }
	inline long GetHistogramMax() { return m_histogramMax; }

private:
	CxImage * m_pImage;

	long m_histogramRed[256];
	long m_histogramGreen[256];
	long m_histogramBlue[256];
	long m_histogramGray[256];
	long m_histogramMax;

// �۾��Դϴ�.
public:
	CString FindExtension(const CString& name);
	CString RemoveExtension(const CString& name);
	int FindType(const CString& ext);
	void CalculateHistogram();

// �������Դϴ�.
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// �����Դϴ�.
public:
	virtual ~CImageProcessingDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnProcessBrightness();
	afx_msg void OnProcessMosaic();
	afx_msg void OnProcessComposite();
	afx_msg void OnProcessIntensityTransform();

	DECLARE_MESSAGE_MAP()	
	
public:
	afx_msg void OnProcessContrastStretch();
	afx_msg void OnProcessEqualization();
	afx_msg void OnHistogramSpecification();
};


