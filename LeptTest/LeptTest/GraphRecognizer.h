#pragma once

#include "GraphSignature.h"
#include "MatchResult.h"
#include "GenericVector.h"

#define GRAPH_NUM 12


class GraphRecognizer
{
public:
	struct graph_vote {
		double posibility;
		int index;
		//int vote;
	};

	struct template_config{
		int arFactor;
		int factorTouchPoint_top;
		int factorTouchPoint_bottom;
		int factorTouchPoint_left;
		int factorTouchPoint_right;
	};

	GraphRecognizer(void);
	~GraphRecognizer(void);

public:
	l_int32 LoadTraningData(const char* trainingDataFile);
	l_int32 Recognize(Pix *pix, MatchResult *result);

private:
	GraphSignature graphTemplates[GRAPH_NUM];
	template_config templateConfig[GRAPH_NUM];
	GenericVector<template_config> templateConfig_;
	l_int32 MatchTemplates(GraphSignature sign);

private:
  static int graph_vote_compare(const void* a, const void* b) {
    const graph_vote* g_a = reinterpret_cast<const graph_vote*>(a);
    const graph_vote* g_b = reinterpret_cast<const graph_vote*>(b);
    return (g_a->posibility > g_b->posibility) ? 1 : ((g_a->posibility < g_b->posibility) ? -1 : 0);
  }

};

