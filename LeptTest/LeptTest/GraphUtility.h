#pragma once
#include <leptonica\allheaders.h>

class GraphUtility
{
public:
	GraphUtility(void);
	~GraphUtility(void);

	static l_int32	FindTouchSpotInRow(Pix *pixs, l_uint32 rowIdx, l_uint32 *touchSpotStart, l_uint32 *touchSpotLength);
	static l_int32	FindTouchSpotInColumn(Pix *pixs, l_uint32 colIdx, l_uint32 *touchSpotStart, l_uint32 *touchSpotLength);
	static Pix*		ChopMargin(Pix *pixs);

};

