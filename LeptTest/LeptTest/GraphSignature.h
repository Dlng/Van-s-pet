#pragma once
class GraphSignature
{
public:
	double aspectRatio;
	
	double touchSpotTop;
	double touchSpotTop_Length;
	double touchSpotBottom;
	double touchSpotBottom_Length;
	double touchSpotLeft;
	double touchSpotLeft_Length;
	double touchSpotRight;
	double touchSpotRight_Length;

public:
	GraphSignature(void);
	~GraphSignature(void);

bool GraphSignature::Serialize(FILE* fp);
bool GraphSignature::DeSerialize(FILE* fp);


};

