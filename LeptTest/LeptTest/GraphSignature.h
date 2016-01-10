#pragma once

#include <leptonica\allheaders.h>

class GraphSignature
{
public:
	double aspectRatio_;
	
	double touchSpotTop_;
	double touchSpotTop_Length_;
	double touchSpotBottom_;
	double touchSpotBottom_Length_;
	double touchSpotLeft_;
	double touchSpotLeft_Length_;
	double touchSpotRight_;
	double touchSpotRight_Length_;

	int matchResult;

public:
	GraphSignature(void);
	~GraphSignature(void);

	l_int32 FindSignature(Pix *pixs);

	bool GraphSignature::Serialize(FILE* fp);
	bool GraphSignature::DeSerialize(FILE* fp);



};

