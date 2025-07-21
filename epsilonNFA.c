#include <stdio.h>
#include <stdlib.h>

void main(){
	int n;
	printf("Enter no of states: ");
	scanf("%d",&n);
	
	int symbols;
	printf("Enter no. of symbols: ");
	scanf("%d",&symbols);
	
	int flag;
	int arr[10][10];
	int table[10][10][10];
	
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(i==j){
				arr[i][j]=1;
			}else{
				printf("Is there an epsilon transition from %d to %d(0/1): ",i,j);
				scanf("%d",&flag);
				if(flag==1){
					arr[i][j]=1;
				}else{
					arr[i][j]=0;
				}
			}
		}
	}
	
	for(int sym=0;sym<symbols;sym++){
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				printf("Transition from %d to %d by symbol %d (0/1) :",i,j,sym);
				scanf("%d",&table[i][sym][j]);
			}
		}
	}
	
	for(int k=0;k<n;k++){
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				if(arr[i][k]==1 && arr[k][j]==1){
					arr[i][j]=1;
				}
			}
		}
	}
	
	for(int states=0;states<n;states++){
		for(int sym=0;sym<symbols;sym++){
			int nfaTable[10]={0};
			for(int i=0;i<n;i++){
				if(arr[states][i]){
					for(int target=0;target<n;target++){
						if(table[i][sym][target]){
							for(int j=0;j<n;j++){
								if(arr[target][j]){
									nfaTable[j]=1;
								}
							}
						}
					}
				}
			}
			printf("From %d on symbol %d { ",states,sym);
			for(int i=0;i<n;i++){
				if(nfaTable[i]){
					printf("%d ",i);
				}
			}printf("}\n");
		}
	}
	
}
