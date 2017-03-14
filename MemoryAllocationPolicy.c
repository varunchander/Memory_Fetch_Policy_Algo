#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<math.h>
struct freespace{
int startadr;
int endadr;
int size;
int pid;
struct freespace *next;
}*albk=NULL,*frbk,*root,*dup,*ralbk;
typedef struct freespace frsp;
// displaying the contents of free block and allocated blocks of memory
void display(){
	printf("the free blocks are \n");
	dup = root;
	while(dup != NULL){
		printf("%d %d \n", dup->startadr,dup->endadr);
		dup = dup->next;
	}
	printf("the allocated blocks are \n");
	dup = ralbk;
	while(dup != NULL){
		printf("%d %d \n", dup->startadr,dup->endadr);
		dup = dup->next;
	}
}

//allocated memory link list with pid and psize
void allocs(int id,int size,int startadr,int endadr){

if(albk == NULL){
	albk = (frsp *)malloc(sizeof(frsp));
	albk->startadr = startadr;
	albk->endadr = endadr;
	albk->pid = id;
	albk->size = size;
	albk->next = NULL;
	ralbk = albk;
}
else{
	albk = ralbk;
	while(albk->next != NULL){
		albk = albk->next;
	}
	dup = (frsp *)malloc(sizeof(frsp));
	dup->startadr = startadr;
	dup->endadr = endadr;
	dup->size = size;
	dup->pid=id;
	dup->next=NULL;
	albk->next=dup;

}

}

//first fit algo
void firstfit(int id , int size){
frbk = root;
int flag = 1;
int count = 1;
while(frbk->next != NULL && flag ==1){
	if(frbk->size >= size){
		if(count == 1){
			root = frbk->next;
			flag = 0;
			printf("freed block of in size %d \n", frbk->size);
		}
		else{
			dup->next = frbk->next;
			flag =0;
			printf("freed block of size in %d \n", frbk->size);
		}
		allocs(id,size,frbk->startadr,frbk->endadr);
	}
	dup=frbk;
	frbk = frbk->next;
	count++;
}
if(frbk->size >= size && frbk->next == NULL && flag == 1){ // last block check
//printf(" %d %d %d\n",dup->startadr,dup->endadr,dup->pid);
if(dup){	
	dup->next = NULL;
}
else{
    root = NULL;
}
printf("freed block of size out %d  \n", frbk->size);
allocs(id,size,frbk->startadr,frbk->endadr);
flag =0;
}
if(flag == 1){printf("the memory for the process cannot be allocated as there is no memory available \n");}
}

//worst fit algo
void worstfit(int id,int size){
frbk = root;
int count = 0, max = frbk->size,pos=0;
while(frbk != NULL){
if(frbk->size > max){
	max = frbk->size;
	pos = count;
}
frbk = frbk->next;
count++;
}
if(size > max){
printf("the memory for the process cannot be allocated as there is no memory available \n");
}else{
	frbk = root;
	if(pos == 0){
		root = frbk->next;
		printf("freed block is of size %d \n",frbk->size);
		allocs(id,size,frbk->startadr,frbk->endadr); 
	}
	else{
	while(pos > 0){
		dup = frbk;
		frbk = frbk->next;
		pos--;
	}
	dup->next = frbk->next;
	printf("freed block is of size  %d %d \n",frbk->size,count);	
	allocs(id,size,frbk->startadr,frbk->endadr); 
	}
 }
}

// bestfit algos  assuming minimum block size as 9999 bytes
void bestfit(int id,int size){
frbk=root;
int min=9999,count=0,pos=0;
while(frbk != NULL){
if(frbk->size < min && frbk->size >= size){
min = frbk->size;
pos = count;
}
dup=frbk;
frbk = frbk->next;
count++;
}
if(min == 9999){
 printf("the memory for the process cannot be allocated as there is no memory available \n");
}else{
frbk = root;
if(pos == 0 ){
  root = frbk->next;
  printf("freed block is of size %d \n",frbk->size);
  allocs(id,size,frbk->startadr,frbk->endadr); 
}else{
	while(pos > 0){
		dup = frbk;
		frbk = frbk->next;
		pos--;
	}
	dup->next = frbk->next;
	printf("freed block is of size  %d %d \n",frbk->size,count);	
	allocs(id,size,frbk->startadr,frbk->endadr); 
 }
}

}


//freeblock allocation
void freealloc(int start,int end,int size){
frsp *dup1;
frbk = root;
dup = (frsp *)malloc(sizeof(frsp));
if(frbk == NULL){
dup->startadr = start;
dup->endadr = end;
dup->size = size;
dup->pid = -1;
dup->next = NULL;
root = dup;	
return;
}
if(frbk->startadr > end){
dup->startadr = start;
dup->endadr = end;
dup->size = size;
dup->pid = -1;
dup->next = frbk;
root = dup;
}
else{
while(frbk != NULL){
	if(frbk->startadr > end){
		dup->startadr = start;
		dup->endadr = end;
		dup->size = size;
		dup->pid = -1;
		dup->next = frbk;
		dup1->next = dup;
		return;
	}
  dup1 = frbk;
  frbk = frbk->next;
  }
//to allocate at last of freeblock list
  dup->startadr=start;
  dup->endadr=end;
  dup->size=size;
  dup->pid=-1;
  dup->next=NULL;
  dup1->next=dup;
  return;

}
}

// process completion
void processComplete(){
	frsp *dup1=NULL;
	printf("the process in progress are : \n");
	dup = ralbk;
	if(dup == NULL){
		printf("No process are in active \n");
		return;
	}
	else{
		while(dup != NULL){
			printf("%d \n",dup->pid);
			dup = dup->next;
		}
		printf("enter the process id from above to terminate it \n");
		int id,flag=0,count=0;
		scanf("%d",&id);
		dup = ralbk;
		while(dup->next != NULL){
			if(dup->pid == id){
				if(count == 0){
					ralbk = dup->next;
					freealloc(dup->startadr,dup->endadr,dup->size);	
					return;
				}else{
					dup1->next=dup->next;
					freealloc(dup->startadr,dup->endadr,dup->size);
					return;
				}
			}
			dup1=dup;
			dup = dup->next;
			count++;
		}
		if(dup->next == NULL && dup->pid == id){
			if(dup1)
				dup1->next = NULL;
			else
				ralbk=NULL;
			freealloc(dup->startadr,dup->endadr,dup->size);
			return;
		}
	}
}


// block optimization
// assumptions: all the free blocks are in a sorted order with respect to the start address and to optimize to the adjacent blocks into one
void blockOptimize(){
frbk = root;
if(frbk->next == NULL)
	return ;
while(frbk->next != NULL){
	if(frbk->endadr == frbk->next->startadr -1){
		frbk->endadr = frbk->next->endadr;
		frbk->next = frbk->next->next;
	}
	if(frbk->next == NULL)
		return;
	frbk = frbk->next;
}
return ;
}

// process check
int processCheck(int id){

dup=ralbk;
while(dup != NULL){
	if(dup->pid == id)
		return 0;
	dup = dup->next;
}
return 1;
}



int main(){
int size,badr,eadr;
frbk=NULL;
albk=NULL;
printf("enter the total no of free space adress blocks \n");
scanf("%d",&size);
int i=1,flag=0;
//allocating free memory blocks
while(i<=size){
printf("enter the start addr and end addr of block %d\n",i);
scanf("%d %d",&badr,&eadr);
if(badr<=eadr){
if(frbk == NULL){
frbk = (struct freespace *)malloc(sizeof(struct freespace));
frbk->startadr=badr;
frbk->endadr=eadr;
frbk->size=eadr-badr;
frbk->pid=-1;
frbk->next=NULL;
root = frbk;
i++;
}
else{
frbk=root;
while(frbk->next!=NULL){
//printf("%d %d \n",frbk->endadr,badr);
if(badr < frbk->endadr){
printf("memory block addressing conflicts %d \n",frbk->endadr);
flag=1;
}
else{
printf("endadr %d badr %d\n",frbk->endadr,badr);
}
frbk = frbk->next;
}
if(frbk->next == NULL){
printf("%d %d \n",frbk->endadr,badr);
if(badr < frbk->endadr){
printf("memory block addressing conflicts %d \n",frbk->endadr);
flag=1;
}
}
if(flag!=1){
dup = (frsp *)malloc(sizeof(frsp));
dup->startadr = badr;
dup->endadr = eadr;
dup->size = eadr-badr;
dup->pid=-1;
dup->next=NULL;
frbk->next=dup;
i++;
}
flag=0;
}
}
else{
//outer if loop
printf("enter the addresses in correct order %d %d \n",badr,eadr);
}
}

dup=root;
while(dup->next!=NULL){
printf("%d \n",dup->startadr);
dup=dup->next;
}
printf("%d \n",dup->startadr);

/// placement algos best fit worst fit and first fit
int choice;
while(1){
int pid;
int psize,status;
printf("enter 1 for first fit \n 2 for best fit \n 3 for worst fit \n 4 for  process completion \n 5 for displaying free and allocated space \n 6 for freeblock optimization \n ");
int choice;
scanf("%d",&choice);
switch(choice){
case 1: do{
printf("enter the process id and process size\n");
scanf("%d %d",&pid,&psize);
pid = abs(pid);
psize = abs(psize);
status = processCheck(pid);
}while(status == 0);
firstfit(pid,psize); 
break;
case 2: do{
printf("enter the process id and process size\n");
scanf("%d %d",&pid,&psize);
pid = abs(pid);
psize = abs(psize);
status = processCheck(pid);
}while(status == 0);
bestfit(pid,psize);
break;
case 3: do{
printf("enter the process id and process size\n");
scanf("%d %d",&pid,&psize);
pid = abs(pid);
psize = abs(psize);
status = processCheck(pid);
}while(status == 0);
worstfit(pid,psize);
break;
case 4: processComplete();
break;
case 5: display();
break;
case 6: blockOptimize();
break;
default:
break;
}

}
return 0;
}

