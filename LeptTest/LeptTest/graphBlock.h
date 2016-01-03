#pragma once

#include "MatchResult.h"

namespace tesseract{

class GraphBlock
{
public:
	GraphBlock(void);
	~GraphBlock(void);

	MatchResult result_;

	l_int32 left_;
	l_int32 right_;
	Pix *pix_host_page;

	bool Recongize();
};

}

