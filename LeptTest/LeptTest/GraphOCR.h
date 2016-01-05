#pragma once

#include <leptonica\allheaders.h>
#include "ccutil\strngs.h"
#include "thresholder.h"
#include "GraphSignature.h"

namespace tesseract {
	/**
 * Minimum believable resolution. Used as a default if there is no other
 * information, as it is safer to under-estimate than over-estimate.
 */
const int kMinCredibleResolution = 70;
/** Maximum believable resolution.  */
const int kMaxCredibleResolution = 2400;

class GraphOCR
{
public:
	GraphOCR(void);
	~GraphOCR(void);

	bool ProcessPages(const char* filename, STRING* text_out, const char* trainingDataFile);

	bool Training(const char* folder, const char* trainingDataFile);

private:
	GraphSignature graphTemplates[12];

	l_int32 FindTouchSpotInRow(Pix *pixs, l_uint32 rowIdx, l_uint32 *touchSpotStart, l_uint32 *touchSpotLength);
	l_int32 FindTouchSpotInColumn(Pix *pixs, l_uint32 colIdx, l_uint32 *touchSpotStart, l_uint32 *touchSpotLength);

protected:

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
   void SetImage(const Pix* pix);
	
   void Threshold(Pix** pix);
	   
	void Clear();

	void PixelsStat();

	Pix *ChopMargin(Pix *pixs);


  ImageThresholder* thresholder_;     ///< Image thresholding module.

  // Image used for input to layout analysis and tesseract recognition.
  // May be modified by the ShiroRekhaSplitter to eliminate the top-line.
  Pix* pix_binary_;

  // Grey-level input image if the input was not binary, otherwise NULL.
  Pix* pix_grey_;
  
  // Input image resolution after any scaling. The resolution is not well
  // transmitted by operations on Pix, so we keep an independent record here.
  int source_resolution_;

    /**
   * @defgroup ThresholderParams Thresholder Parameters
   * Parameters saved from the Thresholder. Needed to rebuild coordinates.
   */
  /* @{ */
  int rect_left_;
  int rect_top_;
  int rect_width_;
  int rect_height_;
  int image_width_;
  int image_height_;
  /* @} */

};

}