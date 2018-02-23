#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	char line1[1024] = {' '};
	char line2[1024] = {'*'};
	char line3[1024] = {'*'};
	int stackcount = 0;
	int maxheight;

	fgets(line1, 1024, stdin);
	fgets(line2, 1024, stdin);
	fgets(line3, 1024, stdin);

	maxheight = atoi(line1);

	//stack matrix
	char stacks[maxheight][stackcount];
	int itemcount = 0;
	
	for(int x=0; x<stackcount; x++){
		for(int y=0; y<1024; y++){
			if(itemcount==maxheight || line2[y]==';'){
				break;
			}
			if(line2[y]!='(' || line2[y]!=' ' || line2[y]!=';' || line2[y]!=','){
				stacks[itemcount][x]=line2[y];
				itemcount++;
			}
		}
		itemcount=0;
	}


	//goal stack matrix
	char goalstacks[maxheight+1][stackcount];
	itemcount = 0;

	for (int x=0; x<stackcount; x++){
		for(int y=0; y<1024; y++){
			if(line3[y]==';'){
				break;
			}
			if(line3[y]!='(' || line3[y]!=' ' || line3[y]!=';' || line3[y]!=','){
				goalstacks[itemcount][x]=line3[y];
				itemcount++;
			}
		}
		itemcount=0;
	}
	
	
	char frontier[10][maxheight][stackcount];
	int frontier_pathc[10];
	char explored[10][maxheight][stackcount];
	int lowercost = 1000;
	int lowercostindex;
	int equal = 1;
	
	frontier[0] = stacks;
	frontier_pathc[0] = 0;
	
	while(1){
		if (frontier[0][0][0]==0) {
			printf("Failure\n\n");
		}
		for (int i=0; i<10; i++) {
			if (lowercost>frontier_pathc[i]) {
				lowercost = frontier_pathc[i];
				lowercostindex = i;
			}
		}
		for (int i=0; i<maxheight; i++) {
			for (int j=0; j<stackcount; j++) {
				if (frontier[lowercostindex][i][j] != goalstacks[i][j]) {
					equal = 0;
				}
			}
		}
		if (equal == 1) {
			
		}
	}
	
	return 0;
}
