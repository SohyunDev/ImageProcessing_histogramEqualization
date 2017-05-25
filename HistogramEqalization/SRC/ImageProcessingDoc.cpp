
// ImageProcessingDoc.cpp : Implement a CImageProcessingDoc Class
//

#include "stdafx.h"
#include "ImageProcessing.h"

#include "DlgBrightnessOption.h"
#include "DlgMosaicOption.h"
#include "DlgCompositeOption.h"
#include "DlgIntensityTransformOption.h"
#include "DlgContrastStretchOption.h"

#include "ImageProcessingDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageProcessingDoc

IMPLEMENT_DYNCREATE(CImageProcessingDoc, CDocument)

BEGIN_MESSAGE_MAP(CImageProcessingDoc, CDocument)
	ON_COMMAND(ID_PROCESS_MOSAIC, &CImageProcessingDoc::OnProcessMosaic)
	ON_COMMAND(ID_PROCESS_BRIGHTNESS, &CImageProcessingDoc::OnProcessBrightness)
	ON_COMMAND(ID_PROCESS_COMPOSITE, &CImageProcessingDoc::OnProcessComposite)
	ON_COMMAND(ID_PROCESS_INTENSITY_TRANSFORM, &CImageProcessingDoc::OnProcessIntensityTransform)
	ON_COMMAND(ID_PROCESS_CONTRAST_STRETCH, &CImageProcessingDoc::OnProcessContrastStretch)
	ON_COMMAND(ID_PROCESS_EQUALIZATION, &CImageProcessingDoc::OnProcessEqualization)
	ON_COMMAND(ID_32783, &CImageProcessingDoc::OnHistogramSpecification)
END_MESSAGE_MAP()


// CImageProcessingDoc Contruction/Destuction

CImageProcessingDoc::CImageProcessingDoc()
{
	//// TODO: Add an one-time generating code here
	m_pImage = NULL;
}

CImageProcessingDoc::~CImageProcessingDoc()
{
	if (NULL != m_pImage)
		delete m_pImage;
}

BOOL CImageProcessingDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO: load imagefile // DONE
	m_pImage = new CxImage;
	m_pImage->Load(lpszPathName, FindType(lpszPathName));

	CalculateHistogram();

	return TRUE;
}

BOOL CImageProcessingDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	//// TODO: Add a re-initialization code here
	//// SDI documents will reuse this article

	return TRUE;
}




// CImageProcessingDoc serialization

void CImageProcessingDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		//// TODO: Add a saving code here
	}
	else
	{
		//// TODO: Add a loading code here
	}
}


// CImageProcessingDoc diagnosis

#ifdef _DEBUG
void CImageProcessingDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageProcessingDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImageProcessingDoc command

CString CImageProcessingDoc::FindExtension(const CString& name)
{
	int len = name.GetLength();
	int i;
	for (i = len-1; i >= 0; i--){
		if (name[i] == '.'){
			return name.Mid(i+1);
		}
	}
	return CString(_T(""));
}

CString CImageProcessingDoc::RemoveExtension(const CString& name)
{
	int len = name.GetLength();
	int i;
	for (i = len-1; i >= 0; i--){
		if (name[i] == '.'){
			return name.Mid(0,i);
		}
	}
	return name;
}

int CImageProcessingDoc::FindType(const CString& ext)
{
	return CxImage::GetTypeIdFromName(ext);
}

void CImageProcessingDoc::CalculateHistogram()
{
	// TODO: Add a calculating histogram code here
	if (m_pImage) {
		// Histogram function, which is implemented in Cximage
		//m_histogramMax = m_pImage->Histogram(m_histogramRed, m_histogramGreen, m_histogramBlue, m_histogramGray);

		
		DWORD width = m_pImage->GetWidth();
		DWORD height = m_pImage->GetHeight();
		RGBQUAD color;

		for (int i = 0; i <= 255; i++) {
			m_histogramRed[i] = 0;
			m_histogramGreen[i] = 0;
			m_histogramBlue[i] = 0;
			m_histogramGray[i] = 0;
		}

		for (DWORD y = 0; y < height; y++) {
			for (DWORD x = 0; x < width; x++) {
				color = m_pImage->GetPixelColor(x, y);
				m_histogramRed[color.rgbRed] += 1;
				m_histogramGreen[color.rgbGreen] += 1;
				m_histogramBlue[color.rgbBlue] += 1;
				m_histogramGray[((color.rgbBlue + color.rgbGreen + color.rgbRed) / 3)] += 1;
			}
		}

		m_histogramMax = 0;
		for (int i = 0; i < 256; i++){
			m_histogramMax = max(m_histogramMax, m_histogramRed[i]  );
			m_histogramMax = max(m_histogramMax, m_histogramGreen[i]);
			m_histogramMax = max(m_histogramMax, m_histogramBlue[i] );
			m_histogramMax = max(m_histogramMax, m_histogramGray[i] );
		}
		//////////////////////////////////////////////////////////////
	}
}

void CImageProcessingDoc::OnProcessBrightness()
{
	// TODO: Add a changing the brightness histogram code here
	if (m_pImage) {
		DlgBrightnessOption dlg;

		if (dlg.DoModal() == IDOK) {
			// write your own code
			// for applying your effect, you must use m_pImage
			// this code is a simple example for manufacturing image : grayscaling

			int nPlusMinus = dlg.m_nPlusMinus;
			BYTE byModifyValue = dlg.m_byModifyValue;

			DWORD width = m_pImage->GetWidth();
			DWORD height = m_pImage->GetHeight();
			RGBQUAD color;
			RGBQUAD newcolor;

			for (DWORD y = 0; y < height; y++) {
				for (DWORD x = 0; x < width; x++) {
					color = m_pImage->GetPixelColor(x, y);
					if (nPlusMinus == 0){
						if (color.rgbBlue * 2 >255){
							newcolor.rgbBlue = 255;
						}
						else if (color.rgbBlue * 2 < 0){
							newcolor.rgbBlue = 0;
						}
						else{
							newcolor.rgbBlue = color.rgbBlue * 2;
						}

						if (color.rgbGreen * 2 >255){
							newcolor.rgbGreen = 255;
						}
						else if (color.rgbGreen * 2< 0){
							newcolor.rgbGreen = 0;
						}
						else{
							newcolor.rgbGreen = color.rgbGreen * 2;
						}

						if (color.rgbRed * 2 > 255){
							newcolor.rgbRed = 255;
						}
						else if (color.rgbRed * 2< 0){
							newcolor.rgbRed = 0;
						}
						else{
							newcolor.rgbRed = color.rgbRed * 2;
						}
					}
					else if (nPlusMinus == 1){
						if (color.rgbBlue / 2  >255){
							newcolor.rgbBlue = 255;
						}
						else if (color.rgbBlue / 2 < 0){
							newcolor.rgbBlue = 0;
						}
						else{
							newcolor.rgbBlue = color.rgbBlue / 2;
						}

						if (color.rgbGreen / 2  >255){
							newcolor.rgbGreen = 255;
						}
						else if (color.rgbGreen / 2  < 0){
							newcolor.rgbGreen = 0;
						}
						else{
							newcolor.rgbGreen = color.rgbGreen / 2;
						}if (color.rgbRed / 2  >255){
							newcolor.rgbRed = 255;
						}
						else if (color.rgbRed / 2 < 0){
							newcolor.rgbRed = 0;
						}
						else{
							newcolor.rgbRed = color.rgbRed / 2;
						}
					}
					m_pImage->SetPixelColor(x, y, newcolor);
				}
			}

			// code to view overflow, Keep observation with the debugger
			BYTE a = 255;
			BYTE b = 1;
			int  c = 10;
			BYTE r;

			r = a + b;
			r = a + c;
			r = b + c;
		}
	}

	CalculateHistogram();
	UpdateAllViews(NULL);
}

void CImageProcessingDoc::OnProcessMosaic()
{
	// TODO: Add a mosaic code here
	if (m_pImage) {
		DlgMosaicOption dlg;

		if (dlg.DoModal() == IDOK) {
			// write your own code
			// for applying your effect, you must use m_pImage
			// this code is a simple example for manufacturing image : grayscaling

			DWORD dwWindowSize = dlg.m_dwWindowSize;

			DWORD width = m_pImage->GetWidth();
			DWORD height = m_pImage->GetHeight();
			RGBQUAD color;
			RGBQUAD newcolor;
			
			unsigned int addB, addG, addR;
			unsigned int aveB, aveG, aveR;

			for (DWORD i = 0; i < height; i = i+dwWindowSize){
				for (DWORD j = 0; j < width; j=j+dwWindowSize){
					if (i + dwWindowSize <= height && j + dwWindowSize <= width){
						for (DWORD y = i; y < i + dwWindowSize; y++){
							for (DWORD x = j; x < j + dwWindowSize; x++){
								color = m_pImage->GetPixelColor(x, y);
								if (y == i && x == j){
									
									addB = color.rgbBlue;
									addG = color.rgbGreen;
									addR = color.rgbRed;

								}
								else{
									addB += color.rgbBlue;
									addG += color.rgbGreen;
									addR += color.rgbRed;

								}
							}
						}
						aveB = (BYTE)((unsigned int)addB / (dwWindowSize*dwWindowSize));
						aveG = (BYTE)((unsigned int)addG / (dwWindowSize*dwWindowSize));
						aveR = (BYTE)((unsigned int)addR / (dwWindowSize*dwWindowSize));
						
						// Æò±Õ Àû¿ë
						for (DWORD y = i; y < i + dwWindowSize; y++){
							for (DWORD x = j; x < j + dwWindowSize; x++){
								newcolor.rgbBlue = (BYTE)aveB;
								newcolor.rgbGreen = (BYTE)aveG;
								newcolor.rgbRed = (BYTE)aveR;
								m_pImage->SetPixelColor(x, y, newcolor);
							}
						}
					}
					
					else if (i + dwWindowSize > height && j + dwWindowSize <= width){
						// rgbÃßÃâ
						for (DWORD y = i; y < height; y++){
							for (DWORD x = j; x < j + dwWindowSize; x++){
								color = m_pImage->GetPixelColor(x, y);
								if (y == i && x == j){
				
									addB = color.rgbBlue;
									addG = color.rgbGreen;
									addR = color.rgbRed;

								}
								else{
									addB += color.rgbBlue;
														addG += color.rgbGreen;
									addR += color.rgbRed;

								}
							}
						}
						aveB = (BYTE)((unsigned int)addB / (dwWindowSize*dwWindowSize));
						aveG = (BYTE)((unsigned int)addG / (dwWindowSize*dwWindowSize));
						aveR = (BYTE)((unsigned int)addR / (dwWindowSize*dwWindowSize));

						// Æò±Õ Àû¿ë
						for (DWORD y = i; y < height; y++){
							for (DWORD x = j; x < j + dwWindowSize; x++){
								newcolor.rgbBlue = (BYTE)aveB;
								newcolor.rgbGreen = (BYTE)aveG;
								newcolor.rgbRed = (BYTE)aveR;
								m_pImage->SetPixelColor(x, y, newcolor);
							}
						}
					}
					else if (i + dwWindowSize <= height && j + dwWindowSize > width){
						// rgbÃßÃâ
						for (DWORD y = i; y < i+dwWindowSize; y++){
							for (DWORD x = j; x < width; x++){
								color = m_pImage->GetPixelColor(x, y);
								if (y == i && x == j){
									addB = color.rgbBlue;
									addG = color.rgbGreen;
									addR = color.rgbRed;
								}
								else{
									addB += color.rgbBlue;
									addG += color.rgbGreen;
									addR += color.rgbRed;

								}
							}
						}
						aveB = (BYTE)((unsigned int)addB / (dwWindowSize*dwWindowSize));
						aveG = (BYTE)((unsigned int)addG / (dwWindowSize*dwWindowSize));
						aveR = (BYTE)((unsigned int)addR / (dwWindowSize*dwWindowSize));
						
						// Æò±Õ Àû¿ë
						for (DWORD y = i; y < i + dwWindowSize; y++){
							for (DWORD x = j; x < width; x++){
								newcolor.rgbBlue = (BYTE)aveB;
								newcolor.rgbGreen = (BYTE)aveG;
								newcolor.rgbRed = (BYTE)aveR;
								m_pImage->SetPixelColor(x, y, newcolor);
							}
						}
					}
					else if (i + dwWindowSize > height && j + dwWindowSize > width){
						for (DWORD y = i; y < i + height; y++){
							for (DWORD x = j; x < width; x++){
								color = m_pImage->GetPixelColor(x, y);
								if (y == i && x == j){
									addB = color.rgbBlue;
									addG = color.rgbGreen;
									addR = color.rgbRed;
								}
								else{
									addB += color.rgbBlue;
									addG += color.rgbGreen;
									addR += color.rgbRed;
								}
							}
						}
						aveB = (BYTE)((unsigned int)addB / (dwWindowSize*dwWindowSize));
						aveG = (BYTE)((unsigned int)addG / (dwWindowSize*dwWindowSize));
						aveR = (BYTE)((unsigned int)addR / (dwWindowSize*dwWindowSize));

						// Æò±Õ Àû¿ë
						for (DWORD y = i; y < height; y++){
							for (DWORD x = j; x < width; x++){
								newcolor.rgbBlue = (BYTE)aveB;
								newcolor.rgbGreen = (BYTE)aveG;
								newcolor.rgbRed = (BYTE)aveR;
								m_pImage->SetPixelColor(x, y, newcolor);
							}
						}
					}
				}
			}
		}
	}

	CalculateHistogram();
	UpdateAllViews(NULL);
}

void CImageProcessingDoc::OnProcessComposite()
{
	// TODO: Add a composite code here
	if (m_pImage) {
		DlgCompositeOption dlg;

		if (dlg.DoModal() == IDOK) {
			int nOperatorID = dlg.GetCompositeOperatorID();
			CxImage * pSecondImage = dlg.GetSecondImage();

			DWORD width = m_pImage->GetWidth();
			DWORD height = m_pImage->GetHeight();
			RGBQUAD firstColor;
			RGBQUAD secondColor;
			RGBQUAD newColor;

			for (DWORD y = 0; y < height; y++) {
				for (DWORD x = 0; x < width; x++) {
					firstColor = m_pImage->GetPixelColor(x, y);
					secondColor = pSecondImage->GetPixelColor(x, y);

					// Add function
					if (nOperatorID == 0) {
						if (firstColor.rgbBlue == 0 && secondColor.rgbBlue != 0) {
							newColor.rgbBlue = secondColor.rgbBlue;
						}
						else if (firstColor.rgbBlue != 0 && secondColor.rgbBlue == 0) {
							newColor.rgbBlue = firstColor.rgbBlue;
						}
						else {
							newColor.rgbBlue = 0;
						}

						if (firstColor.rgbRed == 0 && secondColor.rgbRed != 0) {
							newColor.rgbRed = secondColor.rgbRed;
						}
						else if (firstColor.rgbRed != 0 && secondColor.rgbRed == 0) {
							newColor.rgbRed = firstColor.rgbRed;
						}
						else {
							newColor.rgbRed = 0;
						}

						if (firstColor.rgbGreen == 0 && secondColor.rgbGreen != 0) {
							newColor.rgbGreen = secondColor.rgbGreen;
						}
						else if (firstColor.rgbGreen != 0 && secondColor.rgbGreen == 0) {
							newColor.rgbGreen = firstColor.rgbGreen;
						}
						else {
							newColor.rgbGreen = 0;
						}

					}
					// Substract function
					else if (nOperatorID == 1) {
						if (secondColor.rgbRed != 0 || secondColor.rgbGreen!=0 || secondColor.rgbBlue !=0 ) {
							if (firstColor.rgbRed == secondColor.rgbRed && firstColor.rgbBlue == secondColor.rgbBlue && firstColor.rgbGreen == secondColor.rgbGreen) {
								newColor.rgbRed = 0;
								newColor.rgbGreen = 0;
								newColor.rgbBlue = 0;
							}
							else {
								newColor.rgbBlue = firstColor.rgbBlue;
								newColor.rgbRed = firstColor.rgbRed;
								newColor.rgbGreen = firstColor.rgbGreen;
							}
						}
						else {
							newColor.rgbBlue = firstColor.rgbBlue;
							newColor.rgbRed = firstColor.rgbRed;
							newColor.rgbGreen = firstColor.rgbGreen;
						}
					}

					m_pImage->SetPixelColor(x, y, newColor);
				}
			}
		}
	}

	CalculateHistogram();
	UpdateAllViews(NULL);
}

void CImageProcessingDoc::OnProcessIntensityTransform()
{
	// TODO: Add a Contrast conversion code here
	if (m_pImage) {
		DlgIntensityTransformOption dlg;

		if (dlg.DoModal() == IDOK) {
			int nTransformType = dlg.m_nTransformType;
			double nLinearTransfromCoefficient_a = dlg.m_nLinearTransfromCoefficient_a;
			double nLinearTransfromCoefficient_b = dlg.m_nLinearTransfromCoefficient_b;

			int byThresholdValue = dlg.m_byThresholdValue;

			BYTE byContrastStretching_Start = dlg.m_byContrastStretching_Start;
			BYTE byContrastStretching_End = dlg.m_byContrastStretching_End;

			DWORD width = m_pImage->GetWidth();
			DWORD height = m_pImage->GetHeight();
			RGBQUAD color;
			RGBQUAD newcolor;
		}
	}

	CalculateHistogram();
	UpdateAllViews(NULL);
}

void CImageProcessingDoc::OnProcessContrastStretch()
{
	// TODO: Add a Contrast stretching code here
	if (m_pImage) {
		DlgContrastStretchOption dlg;

		if (dlg.DoModal() == IDOK) {
			int nStretchType = dlg.m_nStretchType;
			float fLow = dlg.m_fLow;
			float fHigh = dlg.m_fHigh;

			DWORD width = m_pImage->GetWidth();
			DWORD height = m_pImage->GetHeight();
			RGBQUAD color;
			RGBQUAD newcolor;

			BYTE LUT[256];
			
			// initialize thresholds
			int nLowThresh = 0;
			int nHighThresh = 255;


			// compute thresholds
			if (nStretchType == 0) { // Auto
				color = m_pImage->GetPixelColor(0, 0);
				nLowThresh = color.rgbBlue;
				nHighThresh = color.rgbBlue;

				for (DWORD y = 0; y < height; y++) {
					for (DWORD x = 0; x < width; x++) {
						color = m_pImage->GetPixelColor(x, y);
						if (nLowThresh > color.rgbBlue) {
							nLowThresh = color.rgbBlue;
						}
						if (nLowThresh > color.rgbRed) {
							nLowThresh = color.rgbRed;
						}
						if (nLowThresh > color.rgbGreen) {
							nLowThresh = color.rgbGreen;
						}
						if (nHighThresh < color.rgbBlue) {
							nHighThresh = color.rgbBlue;
						}
						if (nHighThresh < color.rgbRed) {
							nHighThresh = color.rgbRed;
						}
						if (nHighThresh < color.rgbGreen) {
							nHighThresh = color.rgbGreen;
						}
					}
				}


			}
			else if (nStretchType == 1) { // Ends-In
				if (fLow < 0) {
					nLowThresh = 0;
				}
				else if (fLow > 255) {
					nLowThresh = 255;
				}
				else {
					nLowThresh = fLow;
				}
				if (fHigh < 0) {
					nHighThresh = 0;
				}
				else if (fHigh > 255) {
					nHighThresh = 255;
				}
				else {
					nHighThresh = fHigh;
				}
				
			}


			// compute LUT
			for (DWORD x = 0; x < 256; x++) {
				LUT[x] = 255 * (x - nLowThresh) / (nHighThresh - nLowThresh);
				if (LUT[x] < 0) {
					LUT[x] = 0;
				}
				else if (LUT[x] > 255) {
					LUT[x] = 255;
				}
			}

			// trnasfer image
			for (DWORD y = 0; y < height; y++) {
				for (DWORD x = 0; x < width; x++) {
					color = m_pImage->GetPixelColor(x, y);

					// using LUT
					newcolor.rgbBlue = LUT[color.rgbBlue];
					newcolor.rgbGreen = LUT[color.rgbGreen];
					newcolor.rgbRed = LUT[color.rgbRed];


					m_pImage->SetPixelColor(x, y, newcolor);
				}
			}
		}
	}

	CalculateHistogram();
	UpdateAllViews(NULL);
}

void CImageProcessingDoc::OnProcessEqualization()
{
	// TODO: Add a Histogram equalization code here
	if (m_pImage) 
	{

		DWORD width = m_pImage->GetWidth();
		DWORD height = m_pImage->GetHeight();
		RGBQUAD color;	// Save the current color value
		RGBQUAD newcolor;	// After the conversion, save the color value

		//(1) Histogram has already been generated histogram(Omission) 
		//(2) Create a cumulative histogram
		DWORD sum = 0;
		float scale_factor = 255.0 / (width*height);
		DWORD sum_hist[256]; // a cumulative histogram
		
		for(int i=0; i<256 ; i++)
		{
		// (Coding)
			sum += m_histogramGray[i];
			sum_hist[i] = sum;
		}

		
		//(3) Calculating look-up table
		BYTE LUT[256]; // look-up table

		for(int i=0; i<256 ; i++)
		{
			LUT[i] = round(sum_hist[i]*scale_factor);

		}

		// (4) Image Conversion
		for (DWORD y = 0; y < height; y++) 
		{
			for (DWORD x = 0; x < width; x++) 
			{
				color = m_pImage->GetPixelColor(x, y);
				// (Coding)
				newcolor.rgbBlue = LUT[color.rgbBlue];
				newcolor.rgbGreen = LUT[color.rgbGreen];
				newcolor.rgbRed = LUT[color.rgbRed];

				m_pImage->SetPixelColor(x, y, newcolor);
			}
		}		
	}

	CalculateHistogram();
	UpdateAllViews(NULL);
}



void CImageProcessingDoc::OnHistogramSpecification()
{
	// TODO: Add a Histogram specifications code here
	if (m_pImage) 
	{

		DWORD width = m_pImage->GetWidth();
		DWORD height = m_pImage->GetHeight();
		RGBQUAD color;	// Save the current color value
		RGBQUAD newcolor;	// After the conversion, save the color value

		//(1) Histogram has already been generated histogram(Omission) 
		//(2) Create a cumulative histogram
		DWORD sum = 0;
		float scale_factor = 255.0 / (width*height);
		DWORD sum_hist[256]; // a cumulative histogram

		for(int i=0; i<256 ; i++)
		{
		// (coding)

		}


		//(3) Calculating look-up table
		BYTE LUT[256]; // look-up table

		for(int i=0; i<256 ; i++)
		{
		// (coding)  


		}


		// Same as histogram equalization code from here.
		// However, After a cumulative histogram convert to float sum_hist[256] and
		// modifing to be entered in the real number on calculating sum_hist


		//(4) 
		DWORD desired_histogram[256];
		// Making desired_histogram
/*
		//1.
		for (int i=0; i<=255; i++)
		{
			desired_histogram[i]=i;
		}
*/
/*
		//2.
		for (int i=0; i<=255; i++)
		{
			desired_histogram[i]=255-i;
		}
*/
/*
		//3.		
		for (int i=0; i<=127; i++)
		{
			desired_histogram[i]=127-i;
		}
		for (int i=128; i<=255; i++)
		{
			desired_histogram[i]=i-127;
		}
*/

		// redefinition
		sum = 0;
		scale_factor = 255.0 / (width*height);

		//(5) Create the cumulative histogram of histogram you want
		for(int i=0; i<256; i++)
		{
			//(coding)



		}

		//(6) Is the inverse.
		float difference;	// calculate the difference
		int min;	// Calculate the minimum of the difference
		DWORD inv_hist[256];	// reverse-histogram

		//(Hint) will use dual-route.
		// float fabs() Use library functions.
		for(int i=0; i<256; i++)
		{
		//(coding)




		}

		//(7) Create look-up table of reverse-histogram
		for(int i=0; i<256 ; i++)
		{
		//(coding)

		}
		
		

		// (8) Image Conversion
		for (DWORD y = 0; y < height; y++) 
		{
			for (DWORD x = 0; x < width; x++) 
			{
				color = m_pImage->GetPixelColor(x, y);
				// (coding)



				m_pImage->SetPixelColor(x, y, newcolor);
			}
		}		
	} // if(m_pImage)

	CalculateHistogram();
	UpdateAllViews(NULL);

	

}
