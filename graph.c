#include "graph.h"

//获取字符串的字母
char** getContentLetters(char *content,int *nums){
	char **letters = NULL;
	char *temp = NULL;
	int st = 0;
	size_t clen = strlen(content);

	for(size_t i = 0; i < clen; ++i){
		if( content[i]==' ' ){
			*nums += 1;
		}
	}
	*nums += 1;
	letters = (char**)malloc((*nums) * sizeof(char*));
	if( letters ){
		while( (temp = strsep(&content," \n")) != NULL ){
			if( strlen(temp) ){
				letters[st++] = temp;
			}
		}
	}else{
		*nums = 0;
	}
	
	return letters;
}

//获取key在vertices中的位置
int getVertexPos(ALGraph *g,char *key){
	int pos = 0;

	for(int i = 0; i < g->length; ++i){
		if( strcmp(g->vertices[i].data, key) == 0 ){
			pos = i;
			break;
		}
	}
	return pos;
}

//插入弧
void addArcToVertex(Vertex *vers,int st,int et,int weight){
	Arc *temp = vers[st].firstarc,
		*addNote = (Arc*)malloc(sizeof(Arc));
	
	if( addNote ){
		addNote->adjvex = et;
		addNote->cost = weight;
		addNote->nextarc = NULL;
		//increace the out degree of the arc
		vers[st].dOut += 1;

		//增加弧头的入度
		vers[et].dIn += 1;
		
		if( !temp ){
			vers[st].firstarc = addNote;
		}else{
			for( ; temp->nextarc; temp = temp->nextarc);
			temp->nextarc = addNote;
		}
	}
}

//构建有向图
void CreateALGraph(ALGraph *g,char *contents){
	int clen = 0;
	char **letters = getContentLetters(contents, &clen);

	if( letters && clen ){
		g->vertices = (Vertex*)malloc(clen * sizeof(Vertex));
		if( g->vertices ){
			g->length = clen;
			for(int i = 0; i < clen; ++i){
				g->vertices[i].data = strdup(letters[i]);
				g->vertices[i].dIn = g->vertices[i].dOut = 0;
				g->vertices[i].firstarc = NULL;
			}
		}
	}
}

//添加弧
void AddArcs(ALGraph *g,char *head,char *tail,int weight){
	int headPos = getVertexPos(g, head),
		tailPos = getVertexPos(g, tail);
	
	addArcToVertex(g->vertices, headPos, tailPos, weight);
}

//topological sort
int TopologicalOrder(ALGraph g,Stack *t,Stack *s,int *ve){
	int count = 0,j,k,
		*inDegee = (int*)malloc(g.length * sizeof(int));

	if( inDegee ){
		for(int i = 0; i < g.length; ++i){
			inDegee[i] = g.vertices[i].dIn;
			if( !inDegee[i] ){
				Push(t, i);
			}
		}

		while( !StackEmpty(*t) ){
			Pop(t, &j);
			Push(s, j);
			count++;

			for(Arc *temp = g.vertices[j].firstarc; temp; temp = temp->nextarc){
				k = temp->adjvex;
				--inDegee[k];
				if( !inDegee[k] ){
					Push(t, k);
				}
				if( ve[j] + temp->cost > ve[k] ){
					ve[k] = ve[j] + temp->cost;
				}
			}
		}
	}

	if( count < g.length ){
		return 0;
	}else{
		return 1;
	}
}

void OppTopologicalOrder(ALGraph g,Stack *t,int *ve,int *vl){
	int j,k;

	for(int i = 0; i < g.length; ++i){
		vl[i] = ve[i];
	}

	while( !StackEmpty(*t) ){
		Pop(t, &j);

		if( g.vertices[j].dIn ){
			for(Arc *temp = g.vertices[j].firstarc; temp; temp = temp->nextarc){
				k = temp->adjvex;
				if(vl[k] - temp->cost > vl[j]){
					vl[j] = vl[k] - temp->cost;
				}
			}
		}
	}
}

//find key path
int CriticalPath(ALGraph g){
	int ve[g.length],vl[g.length];
	Stack st = {NULL,0,0},tt = {NULL,0,0};

	InitStack(&st, g.length);
	InitStack(&tt, g.length);
	for(int i = 0; i < g.length; ++i){
		ve[i] = vl[i] = 0;
	}

	if( !TopologicalOrder(g,&st,&tt,ve) ){
		return 0;
	}

	//calulation vl array
	OppTopologicalOrder(g,&tt,ve,vl);

	//output critical vertex
	printf("critical path is:");
	for(int i = 0; i < g.length; ++i){
		if(ve[i] == vl[i]){
			printf("%s ", g.vertices[i].data);
		}
	}
	printf("\n");
	return 1;
}

//visit graph
void outPutALGraph(ALGraph g){
	for(int i = 0; i < g.length; ++i){
		printf("%s(%d)", g.vertices[i].data, g.vertices[i].dIn);
		Arc *temp = g.vertices[i].firstarc;

		for( ; temp; temp = temp->nextarc){
			printf("-->%d(%d)", temp->adjvex, temp->cost);
		}
		printf("\n");
	}
}

//清除有向图
void clearALGraph(ALGraph *g){
	for(int i = 0; i < g->length; ++i){
		Arc *temp = g->vertices[i].firstarc;		
		while( temp ){
			g->vertices[i].firstarc = temp->nextarc;
			free(temp);
			temp = g->vertices[i].firstarc;
		}
	}
	free(g->vertices);
	g->vertices = NULL;
	g->length = 0;
}