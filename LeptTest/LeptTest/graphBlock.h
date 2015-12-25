#pragma once

#include "MatchResult.h"

namespace tesseract{

class GraphBlock
{
public:
	GraphBlock(void);
	~GraphBlock(void);

	MatchResult result_;
};

}

