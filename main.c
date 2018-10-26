#include <stdio.h>
#include <string.h>
#include "graph.h"

int main(int argc,char *argv[]){
	FILE *fp = fopen("graph.txt","r");

	if( fp ){
		int weight = 0;
		char ver1[3] = "",
			 ver2[3] = "",
			 content[30] = "",
			 *temp = NULL;
		ALGraph algraph = {NULL,0};

		//read file content and create ALGraph
		while( !feof(fp) && fgets(content, 30, fp) ){
			if( strchr(content,':') ){
				temp = strchr(content,':') + 1;

				if( strstr(content,"Ver")==content ){
					CreateALGraph(&algraph, temp);
				}else if( strstr(content,"Arc")==content ){
					sscanf(temp, "%s %s %d\n", ver1, ver2, &weight);
					AddArcs(&algraph, ver1, ver2, weight);
				}
			}else{
				sscanf(content, "%s %s %d\n", ver1, ver2, &weight);
				AddArcs(&algraph, ver1, ver2, weight);
			}
		}

		//find the key path
		CriticalPath(algraph);

		clearALGraph(*algraph);
		fclose(fp);
	}
	return 0;
}