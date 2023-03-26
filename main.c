#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define space 1
#define DIR "dir"
#define MKDIR "mkdir"
#define CHDIR "chdir"
#define RMDIR "rmdir"
#define COUNTER "count"

typedef struct node
{
	char name[40];
	struct node * firstChild;
	struct node * nextSibling;
	struct node * parentNode;

}Node;

char *my_strcpy(char *destination, char *source)
{
    char *start = destination;

    while(*source != '\0')
    {
        *destination = *source;
        destination++;
        source++;
    }

    *destination = '\0'; 
    return start;
}


void *my_strcat(char *destination, char *source)
{
    char *start = destination;

    while(*destination != '\0')
    {
        destination++;
    }
    while(*source != '\0')
    {
        *destination = *source;
        destination++;
        source++;
    }


    *destination = '\0'; 
    
}

int cmpStr(char first[],char second[]){
	int firstL= strlen(first);
	int secondL= strlen(second);

	if(firstL != secondL){
		return 0;
	}
	else{
		for(int i = 0 ; i < firstL; i++){
			if(first[i]!=second[i]){
				return 0;
			}
		}
	}
	return 1;
}


void printTree(Node * root, Node * trav){

	Node * tmp= trav;

	char temp[30]="";
	char temp2[30];
	char path2[30][30];
	int j=1;
	
	while(tmp -> parentNode !=NULL){
		my_strcpy(temp2,"/");
		my_strcat(temp2,tmp->name);
		my_strcpy(temp,temp2);
		my_strcpy(path2[j],temp);
		
		j++;
		tmp= tmp->parentNode;
	}

	printf("Root");
	for(int i = j-1; i > 0 ; i--){
		printf("%s",path2[i]);
	}
	printf(">");
}

void showDirect(Node * trav){
	
	Node * tmp = trav->firstChild;
	
	while(tmp != NULL){
		printf("\n%s",tmp->name);
		tmp= tmp->nextSibling;
	}
	printf("\n");
}

int countDirect(Node * trav){
	Node * tmp = trav->firstChild;
	int count=0;
	while(tmp != NULL){
		count++;
		tmp= tmp->nextSibling;
	}
	return count;
}


void removeDirect(Node * trav, char name[]){
	Node* tmp = trav->firstChild;
	if(tmp==NULL){
		printf("\nEmpty directory. The directory does not exist ");
		return;
	}
	else if(cmpStr(tmp->name,name)){
		if(tmp->firstChild!=NULL){
			printf("\nCannot delete folder. The directory is not empty.\n");
		}
		else{
			printf("\n %s directory deleted successfully\n",name);
			trav->firstChild=tmp->nextSibling;
			
			free(tmp);
			
			
		}
		return;
	}
	while(tmp ->nextSibling!= NULL){

		if(cmpStr(tmp->nextSibling->name,name)){
			if(tmp->nextSibling->firstChild!=NULL){
				printf("\nCannot delete folder. The directory is not empty.\n");
			}
			else{
				printf("\n %s directory deleted successfully\n",name);
				Node * deletedNext = tmp-> nextSibling -> nextSibling; 
				free(tmp->nextSibling);
				tmp->nextSibling = deletedNext;
			
			}
			return;
		}

		tmp=tmp->nextSibling;
	}
	printf("\nThe directory does not exist\n");

}

void makeChild(Node * parent, char name[]){

	Node * tmp = parent ;
	if(tmp -> firstChild == NULL){

		tmp -> firstChild=(Node *)malloc(sizeof(Node));
		tmp->firstChild->parentNode=tmp;
		tmp= tmp -> firstChild;
		tmp -> firstChild =NULL;
		tmp -> nextSibling = NULL;
		my_strcpy(tmp->name,name);
		
	}
	else{
		tmp = parent -> firstChild;

		while(tmp -> nextSibling !=NULL){
			if(cmpStr(tmp->name,name)){
				printf("\n Warning! This directory is already exist. \n");
				return;
			}
			tmp = tmp -> nextSibling;
		}
		if(cmpStr(tmp->name,name)){
			printf("\n Warning! This directory is already exist. \n");
			return;
		}
		tmp->nextSibling=(Node *)malloc(sizeof(Node));
		tmp->nextSibling->parentNode=tmp->parentNode;
		tmp= tmp->nextSibling;
		tmp -> firstChild =NULL;
		tmp -> nextSibling = NULL;
		my_strcpy(tmp->name,name);
		
	}
}

void changeDirect(Node ** trav, char parameter[]){
	Node *tmp = *trav;
	if(cmpStr(parameter,"..")){
		if(tmp->parentNode != NULL){
			*trav= tmp->parentNode;
			
		}
		else{
			printf("\n Warning! There aren't any directory before Root \n");
		}
		return;
	}
	if(tmp-> firstChild == NULL){
		printf("\n The directory does not exist\n ");
		return;
	}
	
	tmp=tmp->firstChild;
	while(tmp !=NULL){
		if(cmpStr(tmp->name,parameter)){
			*trav = tmp;
			return;
		}
		tmp= tmp->nextSibling;
	}
	printf("\n Unvalid directory parameter. The directory does not exist \n");
	
}



int main(){

	Node * root;
	root=(Node *)malloc(sizeof(Node));
	my_strcpy(root->name,"Root");
	root->nextSibling=NULL;
	root->firstChild=NULL;

	char islem[40];
	char parameter[40];

	Node * trav = root;
	printTree(root,trav);

	while(1){

	
		scanf("%s",&islem);		
			
		if(cmpStr(islem,MKDIR)){

			scanf("%s",&parameter);
			
			makeChild(trav, parameter);
			printTree(root,trav);
		} 
		else if (cmpStr(islem,CHDIR)){

			scanf("%s",&parameter);
			
			changeDirect(&trav, parameter);
			
			printTree(root,trav);
		}
		else if (cmpStr(islem,RMDIR)){

			scanf("%s",&parameter);
			
			removeDirect(trav, parameter);
			
			printTree(root,trav);
		}
		else if (cmpStr(islem,DIR)){
			
			showDirect(trav);
			printTree(root,trav);	
		}
		else if (cmpStr(islem,COUNTER)){

			printf("%s has %d Directory inside.\n",trav->name,countDirect(trav));
			printTree(root,trav);
			
		}
		else{

			printf("\n Wrong operation");
		}		
	}

	return 0;
}