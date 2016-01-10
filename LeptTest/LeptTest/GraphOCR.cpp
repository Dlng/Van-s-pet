#include "stdafx.h"
#include "GraphOCR.h"

#include <leptonica\allheaders.h>
#include "thresholder.h"
#include "tprintf.h"

#include "GraphSignature.h"
#include "GraphUtility.h"

#define WORDLENGTH 32 

namespace tesseract {

GraphOCR::GraphOCR(void)
{
}


GraphOCR::~GraphOCR(void)
{
	pixDestroy(&pix_binary_);
	pixDestroy(&pix_grey_);
}

bool GraphOCR::Training(const char* folder, const char* trainingDataFile)
{
	bool success = true;
	const unsigned int nTemplates = 12;
	char* filename = new char[256];
	Pix *pix;
	FILE *fp = fopen(trainingDataFile, "wb");
	if(fp == NULL)
		return false;


	for(int i = 1; i<=nTemplates; i++){
		strcpy(filename, "\0");
		sprintf(filename, "%s\\%d.jpg", folder, i);

		pix = pixRead(filename);
		if (pix != NULL) {

			SetImage(pix);

			if (pix_binary_ == NULL){
				Threshold(&pix_binary_);

				l_int32 ret = pixWrite("..\\PicSamples\\IMG_binary.PNG", pix_binary_, IFF_PNG);

				Pix *chop = GraphUtility::ChopMargin(pix_binary_);
				ret = pixWrite("..\\PicSamples\\IMG_after_ClipRectangle.PNG", chop, IFF_PNG);

				if(chop != NULL){

					GraphSignature graphSign;
					if(graphSign.FindSignature(chop) == 0){
						if(!graphSign.Serialize(fp))
							return false;
					}

					if(thresholder_ != NULL)
					{
						thresholder_->Clear();
						delete thresholder_;
						thresholder_ = NULL;
					}
					Clear();
					pixDestroy(&chop);	
				}
			}
			pixDestroy(&pix);	

		}
	}

	fclose(fp);
	return false;
}


bool GraphOCR::ProcessPages(const char* filename, STRING* text_out, const char* trainingDataFile)
{
	FILE *fp = fopen(trainingDataFile, "rb");
	for(int i=0; i<12; i++){
		GraphSignature* sign = &graphTemplates[i];
		sign->DeSerialize(fp);
	}
	fclose(fp);

	if( recognize_.LoadTraningData(trainingDataFile) != 0)
		return false;


	bool success = true;
	Pix *pix;
	pix = pixRead(filename);
	if (pix != NULL) {

		SetImage(pix);

		if (pix_binary_ == NULL)
		{
			Clear();
			Threshold(&pix_binary_);
		}

		l_int32 ret = pixWrite("..\\PicSamples\\IMG_binary.PNG", pix_binary_, IFF_PNG);

		Pix *chop = GraphUtility::ChopMargin(pix_binary_);
		ret = pixWrite("..\\PicSamples\\IMG_after_ClipRectangle.PNG", chop, IFF_PNG);
		pixDestroy(&chop);


		//Todo(Van): search GraphBlock in pix_binary_ and saved in a block verctor
		BOX *box = SplitGraph(pix_binary_);

		//Todo(Van): matching each block with templates

		//Todo(Van): assemble result and return final result string

		pixDestroy(&pix);
		return true;
	}
	
	return false;

}

BOX *GraphOCR::SplitGraph(Pix *pixBinary)
{
	NUMA *na = pixCountPixelsByColumn(pixBinary);
	if(na != NULL)
	{
		
		l_int32 left = -1, right = -1;
		l_int32 w = numaGetCount(na);
		for (int i = 0; i < w-1; i++) {
			if(na->array[i] > 3 && na->array[i+1] > 3)
			{
				left = i;
				for (int j = left + 1; j < w-1 ; j++){
					if(na->array[j] == 0 && na->array[j+1] == 0){
						right = j;
						i = right + 1;
						break;
					}
				}

				if(right != -1){

					//fprintf(stderr, "Recognize: [left] = %d, [right] = %d\n", left, right);

					BOX *box1 = boxCreate(left, 0, right - left, pixBinary->h);
					Pix *clipRectangle = pixClipRectangle(pix_binary_, box1, NULL);
					boxDestroy(&box1);

					MatchResult result;
					if(recognize_.Recognize(clipRectangle, &result) == 0)
					{

					}
					pixDestroy(&clipRectangle);
				}
			}

			left = right = -1;
		}

	}
	return NULL;
}

void GraphOCR::PixelsStat()
{
	if(pix_binary_ != NULL)
	{

	}

}

/**
 * Provide an image for Tesseract to recognize. As with SetImage above,
 * Tesseract doesn't take a copy or ownership or pixDestroy the image, so
 * it must persist until after Recognize.
 * Pix vs raw, which to use?
 * Use Pix where possible. A future version of Tesseract may choose to use Pix
 * as its internal representation and discard IMAGE altogether.
 * Because of that, an implementation that sources and targets Pix may end up
 * with less copies than an implementation that does not.
 */
void GraphOCR::SetImage(const Pix* pix) {

  if (thresholder_ == NULL)
  {
    thresholder_ = new ImageThresholder;
    thresholder_->SetImage(pix);
  }
}


/**
 * Run the thresholder to make the thresholded image, returned in pix,
 * which must not be NULL. *pix must be initialized to NULL, or point
 * to an existing pixDestroyable Pix.
 * The usual argument to Threshold is Tesseract::mutable_pix_binary().
 */
void GraphOCR::Threshold(Pix** pix) {
  ASSERT_HOST(pix != NULL);
  if (!thresholder_->IsBinary()) {
	  pixDestroy(&pix_grey_);
      pix_grey_ = thresholder_->GetPixRectGrey();
  }

  l_int32 ret = pixWrite("..\\PicSamples\\IMG_after_PixRectGrey.PNG", pix_grey_, IFF_PNG);
  if (*pix != NULL)
    pixDestroy(pix);
  // Zero resolution messes up the algorithms, so make sure it is credible.
  int y_res = thresholder_->GetScaledYResolution();
  if (y_res < kMinCredibleResolution || y_res > kMaxCredibleResolution) {
    // Use the minimum default resolution, as it is safer to under-estimate
    // than over-estimate resolution.
    thresholder_->SetSourceYResolution(kMinCredibleResolution);
  }
  thresholder_->ThresholdToPix(pix);
  thresholder_->GetImageSizes(&rect_left_, &rect_top_,
                              &rect_width_, &rect_height_,
                              &image_width_, &image_height_);

  ret = pixWrite("..\\PicSamples\\IMG_after_ThresholdToPix.PNG", *pix, IFF_PNG);

  // Set the internal resolution that is used for layout parameters from the
  // estimated resolution, rather than the image resolution, which may be
  // fabricated, but we will use the image resolution, if there is one, to
  // report output point sizes.
  int estimated_res = ClipToRange(thresholder_->GetScaledEstimatedResolution(),
                                  kMinCredibleResolution,
                                  kMaxCredibleResolution);
  if (estimated_res != thresholder_->GetScaledEstimatedResolution()) {
    tprintf("Estimated resolution %d out of range! Corrected to %d\n",
            thresholder_->GetScaledEstimatedResolution(), estimated_res);
  }
  source_resolution_ = estimated_res;
}

void GraphOCR::Clear() {
  pixDestroy(&pix_binary_);
  //pixDestroy(&cube_binary_);
  pixDestroy(&pix_grey_);

  //pixDestroy(&scaled_color_);
  //deskew_ = FCOORD(1.0f, 0.0f);
  //reskew_ = FCOORD(1.0f, 0.0f);
  //splitter_.Clear();
  //scaled_factor_ = -1;
  //ResetFeaturesHaveBeenExtracted();
  //for (int i = 0; i < sub_langs_.size(); ++i)
  //  sub_langs_[i]->Clear();
}


}