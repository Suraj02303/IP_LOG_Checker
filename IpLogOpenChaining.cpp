#include<iostream>
#include<ctime>
#include <cstdlib>
#define max 256
#include<windows.h> 
using namespace std; 


// log time and ip
struct lg{
	time_t time;
	int IP;
}; 
lg log[50];


// list of log
struct List{
	lg logg;
	List *next;
	int count;
}; 

long a = 0;
List *A[20];  // head of all list
List *T[20];  // tail of all list

int h(int O){
	return O%20;
}

void Append(int O){
	struct List* L = (struct List*)malloc(sizeof(List));
	L->logg.IP = O;
	L->count = 0;
	L->count = L->count+1;
	L->next = NULL;
	if(A[h(O)] == NULL){
		A[h(O)] = L;
	}
	else{
		T[h(O)]->next = L;	
	}
	T[h(O)] = L;
}

int HashKey(int O){
	struct List*  L = A[h(O)];
	while(L->next!=NULL){
		if(O==L->logg.IP)
			return 1;
	}
	return 0;   // O not found.	
}

int Get(int O){
	struct List* L = A[h(O)];
	while(L->next!=NULL){
		if(O == L->logg.IP)
			return L->count;
	}
	return -1; // it shows that there is no entry for the O.
}

int Set(int O){
	struct List* L = A[h(O)];
	while(L!=NULL){
		
		if(O == L->logg.IP){
			L->count = L->count+1;
			return L->count; // found the ip searching for just increase the count
		}
		L = L->next;
	}
	Append(O);
}

void Remove(int O){
	struct List* L = A[h(O)];
	struct List* Tmp = A[h(O)];
	while(L!=NULL){
		if(O==L->logg.IP){
			L->count--;
			break;
		}
		Tmp = L;
		L = L->next;
	}
	
	if(L->count==0){
		if(A[h(O)]->next == NULL){
			A[h(O)]= NULL;
		}
		else{
			Tmp->next = L->next;
		}
	}	
			
}

void UpdateAccessList(int i , int j){

	while (log[i].time<=a && i< 50){
		Set(log[i].IP);
		i++;
	}
	cout<<endl;
	cout<<"Show me the logs of last 2 secs from "<<a<<endl;
	while (log[j].time <= a-2 && j < 50){
		Remove(log[j].IP);
		j++;
	}
}

int main(){
	for(int i=0;i<20;i++){
		A[i]=NULL;
		T[i]=NULL;
	}
	 
	for(int i=0;i<50;i++){
		log[i].IP=rand()%256;
		log[i].time = time(0);
		a = time(0);
		Sleep(1000);
	}
	
	cout<<"+++++++++++++++++++++++ Before Update ++++++++++++++++++++++++++"<<endl;
	
	for(int i=0;i<50;i++){
		cout<<log[i].IP<<" and ";
		cout<<log[i].time;
		cout<<endl;
	}
	
	UpdateAccessList(0,0);
	cout<<"+++++++++++++++++++++++++++ After Update +++++++++++++++++++++++++++"<<endl;

	for(int i=0;i<20;i++){
		struct List* L = A[i];
		while(L!=NULL){
			if(L->count!=0)
				cout<<L->logg.IP<<"  "<<L->count<<endl;
			L = L->next;
		}		
	}
	return 0;
}
