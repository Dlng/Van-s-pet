#include "stdafx.h"
#include "GraphSignature.h"
#include "GraphUtility.h"


GraphSignature::GraphSignature(void)
{
	aspectRatio_ = 0;
	
	touchSpotTop_ = 0;
	touchSpotTop_Length_ = 0;
	touchSpotBottom_ = 0;
	touchSpotBottom_Length_ = 0;
	touchSpotLeft_ = 0;
	touchSpotLeft_Length_ = 0;
	touchSpotRight_ = 0;
	touchSpotRight_Length_ = 0;
}


GraphSignature::~GraphSignature(void)
{
}

l_int32 GraphSignature::FindSignature(Pix *pixs)
{
	l_uint32 width = pixGetWidth(pixs);
	l_uint32 height = pixGetHeight(pixs);

	aspectRatio_ = (double)height / width;

	l_uint32 start, length;
	//touch spot of the first line
	l_int32 ret = GraphUtility::FindTouchSpotInRow(pixs, 0, &start, &length);
	if(ret == 0){
		touchSpotTop_ = (double)start / width;
		touchSpotTop_Length_ = (double)length / width;
	}

	//touch spot of the latest line
	ret = GraphUtility::FindTouchSpotInRow(pixs, height - 1, &start, &length);
	if(ret == 0){
		touchSpotBottom_ = (double)start / width;
		touchSpotBottom_Length_ = (double)length / width;
	}

	//touch spot of the left column
	ret = GraphUtility::FindTouchSpotInColumn(pixs, 0, &start, &length);
	if(ret == 0){
		touchSpotLeft_ = (double)start / height;
		touchSpotLeft_Length_ = (double)length / height;
	}

	//touch spot of the right column
	ret = GraphUtility::FindTouchSpotInColumn(pixs, width - 1, &start, &length);
	if(ret == 0){
		touchSpotRight_ = (double)start / height;
		touchSpotRight_Length_ = (double)length / height;
	}

	return 0;
}


bool GraphSignature::Serialize(FILE* fp) {
  if (fwrite(&aspectRatio_, sizeof(aspectRatio_), 1, fp) != 1) return false;

  if (fwrite(&touchSpotTop_, sizeof(touchSpotTop_), 1, fp) != 1) return false;
  if (fwrite(&touchSpotTop_Length_, sizeof(touchSpotTop_Length_), 1, fp) != 1) return false;

  if (fwrite(&touchSpotBottom_, sizeof(touchSpotBottom_), 1, fp) != 1) return false;
  if (fwrite(&touchSpotBottom_Length_, sizeof(touchSpotBottom_Length_), 1, fp) != 1) return false;

  if (fwrite(&touchSpotLeft_, sizeof(touchSpotLeft_), 1, fp) != 1) return false;
  if (fwrite(&touchSpotLeft_Length_, sizeof(touchSpotLeft_Length_), 1, fp) != 1) return false;

  if (fwrite(&touchSpotRight_, sizeof(touchSpotRight_), 1, fp) != 1) return false;
  if (fwrite(&touchSpotRight_Length_, sizeof(touchSpotRight_Length_), 1, fp) != 1) return false;

  return true;
}

bool GraphSignature::DeSerialize(FILE* fp) {
  if (fread(&aspectRatio_, sizeof(aspectRatio_), 1, fp) != 1) return false;

  if (fread(&touchSpotTop_, sizeof(touchSpotTop_), 1, fp) != 1) return false;
  if (fread(&touchSpotTop_Length_, sizeof(touchSpotTop_Length_), 1, fp) != 1) return false;

  if (fread(&touchSpotBottom_, sizeof(touchSpotBottom_), 1, fp) != 1) return false;
  if (fread(&touchSpotBottom_Length_, sizeof(touchSpotBottom_Length_), 1, fp) != 1) return false;

  if (fread(&touchSpotLeft_, sizeof(touchSpotLeft_), 1, fp) != 1) return false;
  if (fread(&touchSpotLeft_Length_, sizeof(touchSpotLeft_Length_), 1, fp) != 1) return false;

  if (fread(&touchSpotRight_, sizeof(touchSpotRight_), 1, fp) != 1) return false;
  if (fread(&touchSpotRight_Length_, sizeof(touchSpotRight_Length_), 1, fp) != 1) return false;

  return true;
}
