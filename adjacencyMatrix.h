#ifndef H_adjacencyMatrix
#define H_adjacencyMatrix
#include "neighborhood.h"
#include "item.h"
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class adjacencyMatrix
{
public:
	~adjacencyMatrix();
	adjacencyMatrix(int x, int y);
	void setHouseholds(int x, int y, int z); //will set the number of houses to be delivered to to be 200 (for now) and set all the items for the 
	//households
	int findMinDistance(int x);


private:
	float getMaxProfit(); //method will determine the maximum profit possible by using some dynamic programming, dijkstra's algorithm, and 
	//hashing
	neighborhood **matrix; //2d array of neighborhood objects
	neighborhood **matrix2;
	neighborhood *arr;//array of dynamically allocated 
	int currentIndex; //used to simulate a hashing like quality for acessing different rows in the matrix
	int weight;
	int size;

	
};

#endif // !H_adjacencyMatrix
#pragma once
