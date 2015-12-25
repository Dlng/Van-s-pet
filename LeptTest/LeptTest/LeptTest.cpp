// LeptTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <leptonica\allheaders.h>

#include "GraphOCR.h"
#include "strngs.h"  

int _tmain(int argc, _TCHAR* argv[])
{
	printf("\nTesting Leptonica Setup \n");
 
	// Read test.png from current working directory
	//char* filename = NULL;
	//filename = getcwd(filename, MAXPATHLEN);
	//strcat(filename, "\\test.png");
 //
	//PIX* pix = pixRead("d:\\tesseract\\1450449816362.jpg");
	//if (!pix) {
	//	printf("Error opening file");
	//	return 1;
	//}
	//printf("Image width : %d", pix->w);

	//PIX* pix_gray8 = pixConvertRGBToGray(pix, 1.0, 1.0, 1.0);
	//l_int32 ret = pixWrite("d:\\tesseract\\IMG_gray8.PNG", pix_gray8, IFF_PNG);


	//PIX* pix_sobel = pixSobelEdgeFilter(pix_gray8, L_ALL_EDGES);
	//ret = pixWrite("d:\\tesseract\\IMG_sobel.PNG", pix_sobel, IFF_PNG);

	//PIX* pix_TwoSided = pixSobelEdgeFilter(pix_gray8, L_ALL_EDGES);
	//ret = pixWrite("d:\\tesseract\\IMG_TwoSided.PNG", pix_TwoSided, IFF_PNG);


	//pixDestroy(&pix);

	

	//const char* image = "D:\\Tesseract\\NumberLine.jpg";//NULL;
  const char* image = "D:\\Tesseract\\IMG_FullPage.jpg";//NULL;
  const char* output = "D:\\Tesseract\\dd";//NULL;

	tesseract::GraphOCR ocr;
	STRING text_out;
	ocr.ProcessPages(image, &text_out);
	return 0;
}

