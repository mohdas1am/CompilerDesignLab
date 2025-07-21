#include <stdio.h>
#include <stdlib.h>

void main(){
	int n;
	printf("Enter no of states: ");
	scanf("%d",&n);
	int flag;
	int arr[10][10];
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
	
	for(int k=0;k<n;k++){
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				if(arr[i][k]==1 && arr[k][j]==1){
					arr[i][j]=1;
				}
			}
		}
	}
	
	for(int i=0;i<n;i++){
		printf("Epsilon closures of %d are { ",i);
		for(int j=0;j<n;j++){
			if(arr[i][j]==1){
				printf("%d ",j);
			}
		}printf("}\n");
	}
	
}
