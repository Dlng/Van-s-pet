#include "stdafx.h"
#include "GraphOCR.h"

#include <leptonica\allheaders.h>
#include "thresholder.h"
#include "tprintf.h"

namespace tesseract {

GraphOCR::GraphOCR(void)
{
}


GraphOCR::~GraphOCR(void)
{
}

bool GraphOCR::ProcessPages(const char* filename, STRING* text_out)
{
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

		//Todo(Van): search GraphBlock in pix_binary_ and saved in a block verctor

		//Todo(Van): matching each block with templates

		//Todo(Van): assemble result and return final result string
	}
	
	return false;

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

  l_int32 ret = pixWrite("d:\\tesseract\\IMG_after_PixRectGrey.PNG", pix_grey_, IFF_PNG);
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

  ret = pixWrite("d:\\tesseract\\IMG_after_ThresholdToPix.PNG", *pix, IFF_PNG);

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