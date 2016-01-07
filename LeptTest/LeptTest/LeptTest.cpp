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
	//PIX* pix = pixRead("..\\PicSamples\\1450449816362.jpg");
	//if (!pix) {
	//	printf("Error opening file");
	//	return 1;
	//}
	//printf("Image width : %d", pix->w);

	//PIX* pix_gray8 = pixConvertRGBToGray(pix, 1.0, 1.0, 1.0);
	//l_int32 ret = pixWrite("..\\PicSamples\\IMG_gray8.PNG", pix_gray8, IFF_PNG);


	//PIX* pix_sobel = pixSobelEdgeFilter(pix_gray8, L_ALL_EDGES);
	//ret = pixWrite("..\\PicSamples\\IMG_sobel.PNG", pix_sobel, IFF_PNG);

	//PIX* pix_TwoSided = pixSobelEdgeFilter(pix_gray8, L_ALL_EDGES);
	//ret = pixWrite("..\\PicSamplesIMG_TwoSided.PNG", pix_TwoSided, IFF_PNG);


	//pixDestroy(&pix);

	

	const char* image = "..\\PicSamples\\GraphLine.png";//NULL;
	//const char* image = "..\\PicSamples\\NumberLine.jpg";//NULL;
	//const char* image = "..\\PicSamples\\FullPage.jpg";//NULL;
	//const char* image = "..\\PicSamples\\Dec-17\\12.jpg";//NULL;
	//const char* image = "..\\PicSamples\\Pic_test01.png";//NULL;
	const char* output = "..\\PicSamples\\dd";//NULL;

	tesseract::GraphOCR ocr;
	STRING text_out;
	ocr.ProcessPages(image, &text_out, "trainingData");

	//ocr.Training("..\\PicSamples\\Dec-17", "trainingData");
	return 0;
}

