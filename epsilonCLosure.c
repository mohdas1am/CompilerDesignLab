#include <stdio.h>
#include <stdlib.h>

int visited[10];
int arr[10][10];

void findClosure(int state,int n,int closure[]){
	if(visited[state]){
		return;
	}
	
	visited[state]=1;
	closure[state]=1;
	
	for(int i=0;i<n;i++){
		if(arr[state][i]){
			findClosure(i,n,closure);
		}
	}
}

void main(){
	int n;
	printf("Enter no of states: ");
	scanf("%d",&n);
	int flag;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			printf("Is there an epsilon transition from %d to %d(0/1): ",i,j);
			scanf("%d",&flag);
			if(flag==1){
				arr[i][j]=1;
			}else{
				arr[i][j]=0;
			}
		}
	}
	
	for(int start=0;start<n;start++){
		int closure[10]={0};
		
		for(int i=0;i<n;i++){
			visited[i]=0;
		}
		
		findClosure(start,n,closure);
		
		printf("epsilon closure of (%d) is {",start);
		for(int i=0;i<n;i++){
			if(closure[i]){
				printf("%d ",i);
			}
		}printf("}\n");
	}
}
