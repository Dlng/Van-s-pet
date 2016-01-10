#include "stdafx.h"
#include "GraphUtility.h"


GraphUtility::GraphUtility(void)
{
}


GraphUtility::~GraphUtility(void)
{
}

l_int32 GraphUtility::FindTouchSpotInRow(Pix *pixs, l_uint32 rowIdx, l_uint32 *touchSpotStart, l_uint32 *touchSpotLength)
{
	if(pixs == NULL)
		return -1;
	if(pixGetDepth(pixs) != 1)
		return -1;
	if(touchSpotLength == NULL || touchSpotStart == NULL)
		return -1;

	*touchSpotLength = 0, *touchSpotStart = 0;

	l_int32		h = pixGetHeight(pixs);
	if(rowIdx >= h)
		return -1;
	
	bool		start_pos = false;
	l_int32		w = pixGetWidth(pixs);
	l_uint32	*line = pixGetData(pixs) + pixGetWpl(pixs) * rowIdx;
	l_int32		val = 0;
	for(int x=0; x<w; x++){
		val = GET_DATA_BIT(line, x);
		if(!start_pos){
			if(val == 1){
				start_pos = true;
				*touchSpotStart = x;
			}
		}
		else{
			if(val == 0){
				*touchSpotLength = x - *touchSpotStart;
				return 0;
			}
		}
	}

	return -1;
}

l_int32 GraphUtility::FindTouchSpotInColumn(Pix *pixs, l_uint32 colIdx, l_uint32 *touchSpotStart, l_uint32 *touchSpotLength)
{
	if(pixs == NULL)
		return -1;
	if(pixGetDepth(pixs) != 1)
		return -1;
	if(touchSpotLength == NULL || touchSpotStart == NULL)
		return -1;

	*touchSpotLength = 0, *touchSpotStart = 0;

	l_int32		w = pixGetWidth(pixs);
	if(colIdx >= w)
		return -1;
	
	bool		start_pos = false;
	l_int32		h = pixGetHeight(pixs);
	l_int32		val = 0;
	l_uint32	*line, *data = pixGetData(pixs);
	for(int y=0; y<h; y++){
		line = data + pixGetWpl(pixs) * y;
		val = GET_DATA_BIT(line, colIdx);
		if(!start_pos){
			if(val == 1){
				start_pos = true;
				*touchSpotStart = y;
			}
		}
		else{
			if(val == 0){
				*touchSpotLength = y - *touchSpotStart;
				return 0;
			}
		}
	}

	return -1;
}

Pix *GraphUtility::ChopMargin(Pix *pixs)
{
	l_int32 top, bottom;

	NUMA *na = pixCountPixelsByRow(pixs, NULL);
	if(na != NULL)
	{
		l_int32 h = numaGetCount(na);
		for (int i = 0; i < h; i++) {
			if(na->array[i] > 3)
			{
				top = i;
				break;
			}
			//if(start && na->array[i] > 0)
			//{
			//	fprintf(stderr, "array[%d] = %d\n", i, (int)(na->array[i]));
			//}
		}

		for (int i = h - 1; i >= 0; i--) {
			if(na->array[i] > 3)
			{
				bottom = i;
				break;
			}
		}
	}
	numaDestroy(&na);

	l_int32 left, right;
	na = pixCountPixelsByColumn(pixs);
	if(na != NULL)
	{
		l_int32 w = numaGetCount(na);
		for (int i = 0; i < w; i++) {
			if(na->array[i] > 3)
			{
				left = i;
				break;
			}
		}

		for (int i = w - 1; i >= 0; i--) {
			if(na->array[i] > 3)
			{
				right = i;
				break;
			}
		}
	}

	BOX *box1 = boxCreate(left, top, right - left, bottom - top);
	Pix *clipRectangle = pixClipRectangle(pixs, box1, NULL);
	boxDestroy(&box1);

	return clipRectangle;
}

