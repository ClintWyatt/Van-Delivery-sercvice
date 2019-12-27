#include <iostream>
#include "adjacencyMatrix.h"

using namespace std;

int main()
{
	int number;
	int weight;
	int distance;
	int maxPrice;
	int itmWeight;
	cout << "Enter the amount of neighborhoods near the distribution center: ";
	cin >> number;
	cout << "Enter the maximum weight that the van can carry: ";
	cin >> weight;
	cout << "Enter the maximum distance between 2 houses: ";
	cin >> distance;
	cout << "Enter the maximum amount of ptice for an item: ";
	cin >> maxPrice;
	cout << "Enter the maximum weight for an item: ";
	cin >> itmWeight;
	adjacencyMatrix matrix(number, weight);
	matrix.setHouseholds(distance, maxPrice, itmWeight);

	return 0;
}