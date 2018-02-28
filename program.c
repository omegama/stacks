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
	int i;
	int j;
	int x;
	int y;

	gets(line1);
	gets(line2);
	gets(line3);
	printf("%s\n",line1);
	printf("%s\n",line2);
	printf("%s\n",line3);

	maxheight = atoi(line1);
	printf("\nmaxheight = %i\n", maxheight);
	
	for (i=0; i<strlen(line2); i++) {
		if (line2[i]==';'){
			stackcount++;
		}
	}
	printf("\nstackcount = %i\n", stackcount);

	//stack matrix
	char stacks[maxheight][stackcount];
	int itemcount;
	
	for (i=0; i<maxheight; i++) {
		for (j=0; j<stackcount; j++) {
			stacks[i][j] = '*';
		}
	}
	
	y = 0;
	itemcount = 0;
	for(x=0; x<stackcount; x++) {
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
	for (i=maxheight-1; i>=0; i--) {
		for (j=0; j<stackcount; j++) {
			printf("%c	",stacks[i][j]);
		}
		printf("\n");
	}

	//goal stack matrix
	char goalstacks[maxheight][stackcount];

	for (i=0; i<maxheight; i++) {
		for (j=0; j<stackcount; j++) {
			goalstacks[i][j] = '*';
		}
	}

	y = 0;
	itemcount = 0;
	for(x=0; x<stackcount; x++) {
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
	for (i=maxheight-1; i>=0; i--) {
		for (j=0; j<stackcount; j++) {
			printf("%c	",goalstacks[i][j]);
		}
		printf("\n");
	}
	
	
	
	
	
	char frontier[10][maxheight][stackcount];
	int frontier_pathc[10];
	int frontier_index = 0;
	char explored[10][maxheight][stackcount];
	int explored_index = 0;
	int flag;
	int lowercost;
	int lowercostindex;
	int stack_item_count[stackcount];
	char childs[50][maxheight][stackcount];
	int n_child;
	int checker1;
	int checker2;
	int k;
	int l;
	int m;
	int flag2;
	int p;
	int q;
	int r;
	int counter;
	
	memcpy( frontier[0], stacks, sizeof(stacks) );
	frontier_pathc[0] = 0;
	frontier_index++;
	
	while(1) {
		flag = 1;
		for (i=0; i<maxheight; i++) {
			for (j=0; j<stackcount; j++) {
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
		for (i=0; i<10; i++) {
			if (lowercost>frontier_pathc[i]) {
				lowercost = frontier_pathc[i];
				lowercostindex = i;
			}
		}
		
		flag = 1;
		for (i=0; i<maxheight; i++) {
			for (j=0; j<stackcount; j++) {
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
		for (j=0; j<stackcount; j++) {
			for (i=0; i<maxheight; i++) {
				if (stacks[i][j]>='A' && stacks[i][j]<='Z') {
					stack_item_count[j]++;
				}
			}
		}
		memcpy( childs[0], frontier[0], sizeof(frontier[0]) );
		n_child = 1;
		checker1 = -1;
		checker2 = -1;
		for (j=0; j<stackcount; j++) {
			for (k=maxheight-1; k>=0; k--) {
				if ( childs[0][k][j]>='A' && childs[0][k][j]>='Z' && k!=(maxheight-1) && j!=checker1 ) {
					for (l=0; l<stackcount; l++) {
						for (m=maxheight-1; m>=0; m--) {
							if ( childs[0][m][l]>='A' && childs[0][m][l]>='Z' && k!=(maxheight-1) && j!=l && k!=m && l!=checker2 ) {
								memcpy( childs[n_child], childs[0], sizeof(childs[0]) );
								childs[n_child][m+1][l] = childs[n_child][k][j];
								childs[n_child][k][j] = '*';
								counter = 0;
								flag = 0;
								for (p=0; p<frontier_index; p++) {
									for (q=0; q<maxheight; q++) {
										for (r=0; r<stackcount; r++) {
											if (frontier[p][q][r] == childs[n_child][q][r]) {
												counter++;
											}
										}
									}
									if (counter==(maxheight*stackcount)) {
										flag = 1;
									}
								}
								counter = 0;
								flag2 = 0;
								for (p=0; p<explored_index; p++) {
									for (q=0; q<maxheight; q++) {
										for (r=0; r<stackcount; r++) {
											if (explored[p][q][r] == childs[n_child][q][r]) {
												counter++;
											}
										}
									}
									if (counter==(maxheight*stackcount)) {
										flag2 = 1;
									}
								}
								if (flag==0 || flag2==0) {
									memcpy( frontier[frontier_index], childs[n_child], sizeof(childs[n_child]) );
									frontier_index++;
								} /*else if () {
									
								}*/
								n_child++;
								checker2 = l;
							}
						}
					}
					checker1 = j;
				}
			}
		}
	}
	
	return 0;
}
