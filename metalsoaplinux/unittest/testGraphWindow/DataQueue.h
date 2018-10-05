/**********************************
* class DataQueue
* Copyright (c) @ hust, maotianjiao
*
* description:
* 	This class defined a queue which can
* hold two minutes' data of cpu or swap usage.
**********************************/

#define MAX_SECONDS 120

class DataQueue
{
public:
	DataQueue();
	~DataQueue();
	
	//get the size of queue
	int size();
	
	//add a number to the queue
	int push(int n);
	
	//get the number at giving position
	int getAt(int n); 
private:
	//interger array to hold two minutes's data
	int m_dataArray[MAX_SECONDS];
	
	//point to the first data's position
	int m_iFront;
	
	//point to the last data's position
	int m_iTail;
	
	//judge if the queue is full
	bool m_bFull;
};





