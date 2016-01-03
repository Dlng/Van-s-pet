#include "stdafx.h"
#include "GraphSignature.h"


GraphSignature::GraphSignature(void)
{
	aspectRatio = 0;
	
	touchSpotTop = 0;
	touchSpotTop_Length = 0;
	touchSpotBottom = 0;
	touchSpotBottom_Length = 0;
	touchSpotLeft = 0;
	touchSpotLeft_Length = 0;
	touchSpotRight = 0;
	touchSpotRight_Length = 0;
}


GraphSignature::~GraphSignature(void)
{
}

bool GraphSignature::Serialize(FILE* fp) {
  if (fwrite(&aspectRatio, sizeof(aspectRatio), 1, fp) != 1) return false;

  if (fwrite(&touchSpotTop, sizeof(touchSpotTop), 1, fp) != 1) return false;
  if (fwrite(&touchSpotTop_Length, sizeof(touchSpotTop_Length), 1, fp) != 1) return false;

  if (fwrite(&touchSpotBottom, sizeof(touchSpotBottom), 1, fp) != 1) return false;
  if (fwrite(&touchSpotBottom_Length, sizeof(touchSpotBottom_Length), 1, fp) != 1) return false;

  if (fwrite(&touchSpotLeft, sizeof(touchSpotLeft), 1, fp) != 1) return false;
  if (fwrite(&touchSpotLeft_Length, sizeof(touchSpotLeft_Length), 1, fp) != 1) return false;

  if (fwrite(&touchSpotRight, sizeof(touchSpotRight), 1, fp) != 1) return false;
  if (fwrite(&touchSpotRight_Length, sizeof(touchSpotRight_Length), 1, fp) != 1) return false;

  return true;
}

bool GraphSignature::DeSerialize(FILE* fp) {
  if (fread(&aspectRatio, sizeof(aspectRatio), 1, fp) != 1) return false;

  if (fread(&touchSpotTop, sizeof(touchSpotTop), 1, fp) != 1) return false;
  if (fread(&touchSpotTop_Length, sizeof(touchSpotTop_Length), 1, fp) != 1) return false;

  if (fread(&touchSpotBottom, sizeof(touchSpotBottom), 1, fp) != 1) return false;
  if (fread(&touchSpotBottom_Length, sizeof(touchSpotBottom_Length), 1, fp) != 1) return false;

  if (fread(&touchSpotLeft, sizeof(touchSpotLeft), 1, fp) != 1) return false;
  if (fread(&touchSpotLeft_Length, sizeof(touchSpotLeft_Length), 1, fp) != 1) return false;

  if (fread(&touchSpotRight, sizeof(touchSpotRight), 1, fp) != 1) return false;
  if (fread(&touchSpotRight_Length, sizeof(touchSpotRight_Length), 1, fp) != 1) return false;

  return true;
}
