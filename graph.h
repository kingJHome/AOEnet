#ifndef _AOE_NETWORK
#define _AOE_NETWORK

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

typedef struct arc{
	int adjvex;
	int cost;
	struct arc *nextarc;
}Arc;

typedef struct vertex{
	char *data;
	int dIn;
	struct arc *firstarc;
}Vertex;

typedef struct alGraph{
	Vertex *vertices;
	int length;
}ALGraph;

//构建有向图
void CreateALGraph(ALGraph *g,char *contents);

//添加弧
void AddArcs(ALGraph *g,char *head,char *tail,int weight);

//find key path
int CriticalPath(ALGraph g);

//清除有向图
void clearALGraph(ALGraph *g);
#endif