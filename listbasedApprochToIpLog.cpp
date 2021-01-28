#include<iostream>
#include<ctime>
#include <cstdlib>
#define max 256
#include<windows.h> 
using namespace std; 
//Ip address 
struct IPV4{
	int ip1=0;
	int ip2=0;
	int ip3=0;
	int ip4=0;
};
// log time and ip
struct lg{
	time_t time;
	IPV4 IP ;
}; 
lg log[100];
//list of log
struct List{
	int iplog;
	List *next;
}; 

long a = 0;
List *head = NULL;
List *tail = NULL;

void Append(lg adres){
	struct List* L = (struct List*)malloc(sizeof(List));
	L->iplog = adres.IP.ip1*64+adres.IP.ip2*16+adres.IP.ip3*4+adres.IP.ip4;
	cout<<L->iplog<<endl;
	L->next = NULL;
	if(head == NULL){
		head = L;
	}
	else{
		tail->next = L;	
	}
	tail = L;
}
void Remove(){
	if(head == tail){
		head == NULL;
		tail == NULL;
	}
	if(head!= NULL){
		cout<<head->iplog<<endl;
		head = head->next;
	}
}
int AccessedLastHour(int IpPrsnt){
	struct List* L;
	L= head;
	while(L!=NULL){
		if(L->iplog == IpPrsnt)
			return 1;
		L = L->next;
	}
	return 0;
}

int AccessedCountLastHour(int IpPrsnt){
	int count = 0;
	struct List* L;
	L= head;
	while(L!=NULL){
		if(L->iplog == IpPrsnt)
			count++;
		L = L->next;
	}
	return count;
}
void UpdateAccessList(int i , int j){
	//time_t t = time(0);
	cout<<"Show me the logs of last 2 secs from "<<a<<endl;
	while (log[i].time<=a && i<100){
		Append(log[i]);
		i++;
	}
	cout<<endl;
	while (log[j].time<=a-7 && j < 100){
		Remove();
		j++;
	}
}

int main(){
	
	for(int i=0;i<100;i++){
		log[i].IP.ip1=rand()%4;
		log[i].IP.ip2=rand()%4;
		log[i].IP.ip3=rand()%4;
		log[i].IP.ip4=rand()%4;
		
		log[i].time = time(0);
		a = time(0);
		Sleep(100);
	}
	
	cout<<"+++++++++++++++++++++++ Before Update ++++++++++++++++++++++++++"<<endl;
	
	for(int i=0;i<100;i++){
		cout<<log[i].IP.ip1*64+log[i].IP.ip2*16+log[i].IP.ip3*4+log[i].IP.ip4<<" and ";
		cout<<log[i].time;
		cout<<endl;
	}
	
	UpdateAccessList(0,0);
	cout<<"+++++++++++++++++++++++++++ After Update +++++++++++++++++++++++++++"<<endl;
	struct List* L;
	L= head;
	while(L!=NULL){
		cout<<L->iplog<<endl;
		L = L->next;
	}
	
	if(AccessedLastHour(74)==1){
		cout<<"Yes";
	}
	cout<<AccessedCountLastHour(74);
	return 0;
}
