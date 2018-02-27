#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	char line1[1024];
	char line2[1024];
	char line3[1024];
	int stackcount = 1;
	int maxheight;

	gets(line1);
	gets(line2);
	gets(line3);
	printf("%s\n",line1);
	printf("%s\n",line2);
	printf("%s\n",line3);

	maxheight = atoi(line1);
	printf("\nmaxheight = %i\n", maxheight);
	
	for (int i=0; i<strlen(line2); i++) {
		if (line2[i]==';'){
			stackcount++;
		}
	}
	printf("\nstackcount = %i\n", stackcount);

	//stack matrix
	char stacks[maxheight][stackcount];
	int itemcount;
	int y;
	
	for (int i=0; i<maxheight; i++) {
		for (int j=0; j<stackcount; j++) {
			stacks[i][j] = '*';
		}
	}
	
	y = 0;
	itemcount = 0;
	for(int x=0; x<stackcount; x++) {
		while( y<strlen(line2) ) {
			if(line2[y]>='A' && line2[y]<='Z') {
				stacks[itemcount][x] = line2[y];
				itemcount++;
			}
			if (line2[y]==';') {
				y++;
				break;
			}
			y++;
		}
		itemcount=0;
	}

	printf("\nstacks\n");
	for (int i=maxheight-1; i>=0; i--) {
		for (int j=0; j<stackcount; j++) {
			printf("%c	",stacks[i][j]);
		}
		printf("\n");
	}

	//goal stack matrix
	char goalstacks[maxheight][stackcount];

	for (int i=0; i<maxheight; i++) {
		for (int j=0; j<stackcount; j++) {
			goalstacks[i][j] = '*';
		}
	}

	y = 0;
	itemcount = 0;
	for(int x=0; x<stackcount; x++) {
		while( y<strlen(line3) ) {
			if(line3[y]>='A' && line3[y]<='Z') {
				goalstacks[itemcount][x] = line3[y];
				itemcount++;
			}
			if (line3[y]==';') {
				y++;
				break;
			}
			y++;
		}
		itemcount=0;
	}
	
	printf("\ngoalstacks\n");
	for (int i=maxheight-1; i>=0; i--) {
		for (int j=0; j<stackcount; j++) {
			printf("%c	",goalstacks[i][j]);
		}
		printf("\n");
	}
	
	
	
	
	
	char frontier[10][maxheight][stackcount];
	int frontier_pathc[10];
	char explored[10][maxheight][stackcount];
	int explored_index = 0;
	int flag;
	int lowercost;
	int lowercostindex;
	int stack_item_count[stackcount];
	int n_options;
	
	memcpy( frontier[0], stacks, sizeof(stacks) );
	frontier_pathc[0] = 0;
	
	while(1) {
		flag = 1;
		for (int i=0; i<maxheight; i++) {
			for (int j=0; j<stackcount; j++) {
				if ( !((frontier[0][i][j]>='A' && frontier[0][i][j]<='Z') || frontier[0][i][j]=='*') ) {
					flag = 0;
					i = maxheight;
					break;
				}
			}
		}
		if (flag==0) {
			printf("Failure\n\n");
			return 0;
		}
		
		lowercost = 1000;
		for (int i=0; i<10; i++) {
			if (lowercost>frontier_pathc[i]) {
				lowercost = frontier_pathc[i];
				lowercostindex = i;
			}
		}
		
		flag = 1;
		for (int i=0; i<maxheight; i++) {
			for (int j=0; j<stackcount; j++) {
				if ( frontier[lowercostindex][i][j] != goalstacks[i][j] ) {
					flag = 0;
				}
			}
		}
		if (flag == 1) {
			printf("%i\n", frontier_pathc[lowercostindex]);
			return 0;
		}
		
		memcpy( explored[explored_index], frontier[lowercostindex], sizeof(frontier[lowercostindex]) );
		explored_index++;
		
		memset(stack_item_count, 0, stackcount);
		for (int j=0; j<stackcount; j++) {
			for (int i=0; i<maxheight; i++) {
				if (stacks[i][j]>='A' && stacks[i][j]<='Z') {
					stack_item_count[j]++;
				}
			}
		}
		n_options = 0;
		for (int i=0; i<stackcount; i++) {
			if (stack_item_count[i]<maxheight) {
				n_options++;
			}
		}
		n_options = n_options*(n_options-1);
		for (int i=n_options; i>0; i--) {
			
		}
	}
	
	return 0;
}
