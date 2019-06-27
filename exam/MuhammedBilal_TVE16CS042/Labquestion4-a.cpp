#include<iostream>
#include<queue>
#include<pthread.h>
using namespace std;

queue<int> barberqueue;

void * customerThread(void * customerNumber){
	while(barberqueue.size() == 0); //customer checks if any barber is free
	int barber = barberqueue.front();//exits the loop when the barber is free and chooses the barber who finished earliest
	barberqueue.pop();//Removes that barber from the queue
	cout<<"Hair cutting done by barber "<<barber<<"for customer "<<(long)customerNumber;//Barber cuts hair 	
	barberqueue.push(barber);	//assigns the finished barber back to the queue
	
}


int main(){
	pthread_t customer1;
	pthread_t customer2;
	pthread_t customer3;
	pthread_t customer4;
	pthread_t customer5;
	int customerno;
	customerno=1;
	pthread_create(&customer1,NULL,customerThread,(void *)&customerno);
	customerno=2;
        pthread_create(&customer2,NULL,customerThread,(void *)&customerno);
 	customerno=3;
        pthread_create(&customer3,NULL,customerThread,(void *)&customerno);
  	customerno=4;
        pthread_create(&customer4,NULL,customerThread,(void *)&customerno);
  	customerno=5;
        pthread_create(&customer5,NULL,customerThread,(void *)&customerno);




	return 0;
}
