#include "adjacencyMatrix.h"
#include "neighborhood.h"
#include <iostream>
#include <vector>
#include <time.h>
#include <queue>
#include <climits>

using namespace std;

adjacencyMatrix::adjacencyMatrix(int x, int y)
{
	size = x;
	arr = new neighborhood[x];
	weight = y;//setting the weight
	matrix = new neighborhood*[x];
	matrix2 = new neighborhood*[x];
	for (int i = 0; i < x; i++)
	{
		matrix[i] = new neighborhood[x];
		matrix2[i] = new neighborhood[x];
	}
	//use this if you want to put memory on the stack instead of the heap
	/*matrix.resize(x);
	matrix2.resize(x);
	for (int i = 0; i < x; i++)
	{
		matrix[i].resize(x);
		matrix2[i].resize(x);
	}*/
	
}

//destructor
adjacencyMatrix::~adjacencyMatrix()
{
	
	for (int i = 0; i < size; i++)
	{
		delete [] matrix[i];
		delete [] matrix2[i];
	}
	delete[] matrix;
	delete[] matrix2;
	delete[] arr;
}

//distance is the x parameter, price is the y parameter, z is the weight parameter
void adjacencyMatrix::setHouseholds(int x, int y, int z)
{
	int dist; //distance from the distribution center
	float wght; //weight of each individual item
	float price;//price for each item in a household
	float distance; //distance from other houses
	int deviation = x; //used to 
	int previousRow = 0;
	srand(time(NULL));//setting up the random number generator
	for (int i = 0; i < size; i++)
	{
		dist = rand() % 50;//setting the distance from the distribution center
		wght = static_cast <float> ((rand() % z)+1); //converting a integer (rand) to a float for the item's weight
		price = static_cast <float> ((rand() % y) +.99); //converting a integer (rand) to a float
		arr[i].setDistributionCenter(dist);//setting the distance from the distribution center
		arr[i].setItemAttributes(wght, price);//setting the item's attribute 
	}

	for (int i = 0; i < size; i++)
	{
		previousRow = i;
		for (int j = 0; j < size; j++)
		{
			if (i == j) //if we are on the current household
			{
				dist = rand() % 50;//setting the distance from the distribution center
				matrix[i][j].setDistance(0);//setting the distance to zero since the current household 
				matrix[i][j].setDistributionCenter(dist);//setting the distance from the distribution center
				matrix[i][j].setItemAttributes(arr[i].getWeight(), arr[i].getPrePrice());//setting the item's price and weight
				matrix2[i][j].setDistance(0);//setting the distance to zero since the current household 
				matrix2[i][j].setDistributionCenter(arr[i].getDistributionCenter());//setting the distance from the distribution center
				matrix2[i][j].setItemAttributes(arr[i].getWeight(), arr[i].getPrePrice());//setting the item's price and weight
			}
			else //adjacent household
			{
				if (previousRow > 0)//helping with keeping the adjacency matrix's values in previous rows 
					//that have already been set consistent in later rows
				{
					matrix[i][j].setDistance(matrix[i-previousRow][j + previousRow].getDistance()); //generating a random number between 0 and six miles from the house on the current
					//row
					matrix[i][j].setItemAttributes(matrix[i - previousRow][j + previousRow].getWeight(), matrix[i - previousRow][j + previousRow].getPrePrice());//setting the attributes for the weight and price
					matrix2[i][j].setDistance(matrix2[i - previousRow][j + previousRow].getDistance()); //generating a random number between 0 and six miles from the house on the current
					//row
					matrix2[i][j].setItemAttributes(matrix[i - previousRow][j + previousRow].getWeight(), matrix[i - previousRow][j + previousRow].getPrePrice());//setting the attributes for the weight and price
					previousRow--;
				}
				else//setting new random values for homes to the right of the zero(diagonal) in the adjacency matirx
				{
					distance = static_cast<float> ((rand() % deviation) + 0.1);//getting a random float for the distacne from the main household
					//on this row
					matrix[i][j].setDistance(distance); //generating a random number from the house on the current row
					//row
					matrix[i][j].setItemAttributes(arr[j].getWeight(), arr[j].getPrePrice());//setting the attributes for the weight and price
					matrix2[i][j].setDistance(distance); //generating a random number between 0 and six miles from the house on the current
					//row
					matrix2[i][j].setItemAttributes(arr[j].getWeight(), arr[j].getPrePrice());//setting the attributes for the weight and price
				}
			}
		}

	}
	int max = 0;
	for (int i = 0; i < size; i++)
	{
		if (max < arr[i].getDistributionCenter())//testing to see where the van will deliver to first
		{
			max = matrix[i][i].getDistributionCenter();//getting the max 
			currentIndex = i;
		}
	}
	matrix[currentIndex][currentIndex].setDistance(0);
	float max1 = getMaxProfit();
	cout << "Max profit for this trip is " << max1 * .10 << endl;
}

float adjacencyMatrix::getMaxProfit()
{
	float price;
	vector<float> prices; //used as the terminating variable for this method
	float currentWeight =0;
	currentWeight += arr[currentIndex].getWeight();//getting the first weight of the item being delivered
	prices.push_back(arr[currentIndex].getDistributionCenter()); //getting the first price for delivering the first item
	int counter =0;//used as the terminating factor for dijkstras
	int previousIndex = currentIndex;//previousIndex is used for the previous home delivered to
	float distance = 0.0;//used in dijkstras
	float max;//used to get the max delivery sale
	int index =0;//used to find the smallest neighborhood(vertex) distance
	int instances = 0;
	//setting all household distances to infinity 
	while (prices.size() < size && currentWeight < weight)
	{
		counter = 0;
		if (prices.size() == 1)//if we are on the very first neighborhood 
		{
			for (int i = 0; i < size; i++)
			{
				if (matrix[i][i].getKnown() == false && i != 
					currentIndex && matrix[i][i].getFound() == false)//if the neighborhood has not been delivered to yet
					//and we are not on the current house
				{
					matrix[i][i].setDistance(INT_MAX);//setting the base neighborhoods to distance of infinity
				}
			}
		}
		else
		{
			matrix[previousIndex][previousIndex].setDistance(0);//since we are starting from the previous house, the distance
			//must be set to zero
			for (int i = 0; i < size; i++)
			{
				if (i != previousIndex)//if the neighborhood has not been delivered to yet
					//and we are not at the last house that was delivered to
				{
					matrix[i][i].setDistance(INT_MAX);//setting the base neighborhoods to distance of infinity
				}
			}
		}
		//dijkstra's algorithm modified to get the max price for delivering a item
		while (counter < size)
		{
			index = findMinDistance(index);//finding the closest home
			for (int i = 0; i < size; i++)
			{
				matrix[i][index].setKnown(true);//setting the house to known, but not found
			}
			counter++;
			//iterating through all neighborhoods on the row
			for(int i =0; i < size; i++)
			{
				if (index != i && matrix[i][i].getKnown() == false)//if the 
					//neighborhood has not been delivered to and has not been encountered yet
				{
					distance = matrix[index][i].getDistance();//getting the distance from the adjacent neighborhood 
					//from the neighborhood with the least distance 
					if (matrix[index][index].getDistance() + distance < matrix[i][i].getDistance())
					{
						matrix[i][i].setDistance(matrix[index][index].getDistance() + distance);//setting the regular array 
						//with the distance in the adjacency matrix
					}
				}
			}
		}
		max = 0.0;
		//now, we find the biggest price with all the smallest distances from the current location
		for (int i = 0; i < size; i++)
		{
			if(matrix[i][i].getFound() == false && i != previousIndex) //if not the current house we are at and the house has
				//not been delivered to yet
			{
				price = matrix[i][i].getPrice();
				if (currentWeight + matrix[i][i].getWeight() <= weight && price > max)
				{
					max = matrix[i][i].getPrice();//setting the max to the price of the neighborhood's item minus milage
					currentIndex = i;//setting the currentIndex to where the max price neighborhood is
				}
			}
		}

		if (max > 0.0)//if we were able to deliver the item
		{
			//setting up the same neighborhood in the other adjacency matrix to true for found and known. 
			//The neighborhood being set to true for known and found not be processed again
			for (int i = 0; i < size; i++)
			{
				matrix2[i][previousIndex].setFound(true);
			}
		}
		prices.push_back(max + prices[prices.size() - 1]);//add the price to the array that will be returned from this method
		currentWeight += arr[currentIndex].getWeight();
		//need to reset the new starting location to zero
		previousIndex = currentIndex; //going on to the next neighborhood to deliver
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				matrix[i][j] = matrix2[i][j];//copying the second array to the first array
			}
		
		}
	}

	return prices[prices.size() - 1];
}

int adjacencyMatrix::findMinDistance(int x) //similiar to finding the smallest distance in regular dijkstras
{
	int index = 0;
	float small = INT_MAX; //setting to zero to see if the first loop iteration is greater than 0
	for (int i = 0; i < size; i++)
	{
		if (small >=matrix[i][i].getDistance() && matrix[i][i].getKnown() == false) //if we have not processed the house yet
		{
			index = i;//reseting the index to the lesser distance index in the current row of the 2d matrix
			small = matrix[i][i].getDistance();//resetting the big variable to be used with the idnex
		}
	}
	
	return index;//represents the row that the next max search will take place
}
