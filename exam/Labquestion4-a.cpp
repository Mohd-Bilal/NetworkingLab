#include<iostream>
#include<queue>
#include<pthread.h>
#include<semaphore.h>
using namespace std;


queue<int> barberqueue;
queue<int> customers;
void * customerThread(void * customerNumber){
	while(barberqueue.size() == 0); //customer checks if any barber is free
	int barber = barberqueue.front();//exits the loop when the barber is free and chooses the barber who finished earliest
	barberqueue.pop();//Removes that barber from the queue
	cout<<"Hair cutting done by barber "<<barber<<"for customer "<<(long)customerNumber<<"\n";//Barber cuts hair 	
	barberqueue.push(barber);	//assigns the finished barber back to the queue
}


int main(){
	pthread_t customer1,customer2,customer3;
	for(int i =0 ;i<12;i++)
		customers.push(i);	//Creating the queue of customers
	for(int i = 0;i<3;i++)
		barberqueue.push(i);	//Creating the barber queue
	for(int i = 0;i<12;i+=3){//Creating three customers for the three barbers
		pthread_create(&customer1,NULL,customerThread,(void *)customers.front());
		customers.pop();
    	pthread_create(&customer2,NULL,customerThread,(void *)customers.front());
		customers.pop();
    	pthread_create(&customer3,NULL,customerThread,(void *)customers.front());
		customers.pop();
	}



	return 0;
}
