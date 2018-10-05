/**********************************
* class DataQueue
* Copyright (c) @ hust, maotianjiao
*
* description:
* 	This class defined a queue which can
* hold two minutes' data of cpu or swap usage.
* notice that the length of queue is fixed(= MAX_SECONDS)
**********************************/

#include "DataQueue.h"

//constructor of DataQueue
DataQueue::DataQueue()
{
	for (int i = 0; i < MAX_SECONDS; i++)
		m_dataArray[i] = -1;
	
	m_iFront = 0;
	m_iTail = -1;
	m_bFull = false;
}

//destructor of DataQueue
DataQueue::~DataQueue()
{
	
}

//get the size of queue
int DataQueue::size()
{
	if (!m_bFull)
	{
		return m_iTail + 1;
	}
	else
	{
		return MAX_SECONDS;
	}
}

//add a number to the queue
int DataQueue::push(int n)
{
	if (!m_bFull)  //if the queue is not full
	{
		m_iTail++;
		m_dataArray[m_iTail] = n;
		
		if (m_iTail == MAX_SECONDS - 1)
		{
			m_bFull = true;
		}
	}
	else  //if the queue is full
	{
		if (m_iTail < MAX_SECONDS - 1)
			m_iTail++;
		else
			m_iTail = 0;
			
		m_dataArray[m_iTail] = n;
		
		if (m_iFront < MAX_SECONDS - 1)
			m_iFront++;
		else
			m_iFront = 0;
	}
}

//get the number at giving position
int DataQueue::getAt(int n)
{
	if (n >= MAX_SECONDS)
		return -1;
	if (!m_bFull)
	{
		return m_dataArray[n];
	}
	else 
	{
		int pos = -1;
		pos = (n + m_iFront) % MAX_SECONDS;
		return m_dataArray[pos];
	}
}















