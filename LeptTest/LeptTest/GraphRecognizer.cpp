#include "stdafx.h"

#include <leptonica\allheaders.h>
#include "GraphRecognizer.h"
#include "MatchResult.h"
#include "GraphUtility.h"



GraphRecognizer::GraphRecognizer(void)
{
	template_config G0 = {33,0,0,0,0};
	template_config G1 = {66,0,0,0,0};
	template_config G2 = {66,0,0,0,0};
	template_config G3 = {66,0,0,0,0};
	template_config G4 = {33,0,0,0,0};
	template_config G5 = {33,0,0,0,0};
	template_config G6 = {66,0,0,0,0};
	template_config G7 = {66,0,0,0,0};
	template_config G8 = {33,0,0,0,0};
	template_config G9 = {33,0,0,0,0};
	template_config Ga = {33,0,0,0,0};
	template_config Gb = {66,0,0,0,0};
	templateConfig_.push_back(G0);
	templateConfig_.push_back(G1);
	templateConfig_.push_back(G2);
	templateConfig_.push_back(G3);
	templateConfig_.push_back(G4);
	templateConfig_.push_back(G5);
	templateConfig_.push_back(G6);
	templateConfig_.push_back(G7);
	templateConfig_.push_back(G8);
	templateConfig_.push_back(G9);
	templateConfig_.push_back(Ga);
	templateConfig_.push_back(Gb);
}							  


GraphRecognizer::~GraphRecognizer(void)
{
}

l_int32 GraphRecognizer::LoadTraningData(const char* trainingDataFile)
{
	FILE *fp = fopen(trainingDataFile, "rb");
	for(int i=0; i<GRAPH_NUM; i++){
		GraphSignature* sign = &graphTemplates[i];
		sign->DeSerialize(fp);
	}

	fclose(fp);
	return 0;
}

l_int32 GraphRecognizer::Recognize(Pix *pix, MatchResult *result)
{
	Pix *chop = GraphUtility::ChopMargin(pix);
	l_int32	ret = pixWrite("..\\PicSamples\\IMG_after_ChopMargin.PNG", chop, IFF_PNG);

	GraphSignature sign;
	if(sign.FindSignature(chop) == 0)
	{
		//match here
		MatchTemplates(sign);

	}

	return 0;
}

l_int32 GraphRecognizer::MatchTemplates(GraphSignature sign)
{

	//Match AspectRatio firstly
	GenericVector<graph_vote> vecAspectRatio;
	for(int i=0; i<GRAPH_NUM; i++)
	{
		double deta = sign.aspectRatio_ - graphTemplates[i].aspectRatio_;
		if(deta < 0) deta = -deta;

		graph_vote vote;
		vote.posibility = deta;
		vote.index = i;

		vecAspectRatio.push_back(vote);
	}

	vecAspectRatio.sort(graph_vote_compare);
	fprintf(stderr, "Recognize: [first] = %d, [second] = %d, [third] = %d\n", 
					vecAspectRatio[0].index+1,
					vecAspectRatio[1].index+1,
					vecAspectRatio[2].index+1);

	//Can't distincted by AspectRation, matching by touchSpot_top agin in first three
	if(templateConfig_[vecAspectRatio[0].index].arFactor < 66){
		GenericVector<graph_vote> vecTop;
		for(int i=0; i<3; i++)
		{
			double deta = sign.touchSpotTop_ - graphTemplates[vecAspectRatio[i].index].touchSpotTop_;
			if(deta < 0) deta = -deta;

			graph_vote vote;
			vote.posibility = deta;
			vote.index = vecAspectRatio[i].index;

			vecTop.push_back(vote);
		
		}

		vecTop.sort(graph_vote_compare);

		fprintf(stderr, "TouchSpot_top: [first] = %d, [second] = %d, [third] = %d\n", 
					vecTop[0].index+1,
					vecTop[1].index+1,
					vecTop[2].index+1);

		sign.matchResult = vecTop[0].index + 1;
	}
	else{


		sign.matchResult = vecAspectRatio[0].index + 1;
	}

	return 0;
}





