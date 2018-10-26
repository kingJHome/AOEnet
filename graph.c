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
				g->vertices[i].dIn = 0;
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

int TopologicalOrder(ALGraph g,Stack t){

}

//find key path
int CriticalPath(ALGraph g){
	Stack st = {NULL,0,0};

	InitStack(&st, g->length);
	if( !() ){
		return 
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