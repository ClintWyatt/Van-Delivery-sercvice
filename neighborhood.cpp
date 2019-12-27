#include "neighborhood.h"
#include "item.h"
#include <iostream>

using namespace std;

neighborhood::neighborhood()
{
	distance = 0;
	distCenterDist = 0; //distance from the distribution center

}

//copy constructor
neighborhood::neighborhood(const neighborhood &house)
{
	distance = house.distance;
	found = house.found;
	known = house.known;
	itm = house.itm;
}

//setter method for the distance
void neighborhood::setDistance(double x)
{
	distance = x;
}

//the distance here is the distance from a single neighborhood
float neighborhood::getDistance()
{
	return distance;
}

//setter method for whether the neighborhood has been encountered yet. 
void neighborhood::setKnown(bool x)
{
	known = x;
}

//getter method for whether the neighborhood has been processed yet
bool neighborhood::getKnown()
{
	return known;
}

void neighborhood::setFound(bool x)
{
	found = x;
}

bool neighborhood::getFound()
{
	return found;
}

bool neighborhood::enoughWeight(float currentWeight, float weightLimit)
{
	currentWeight += itm.getWeight(); //adding the items weight to the current weight
	if (currentWeight > weightLimit) //if the item added overflows the max weight
	{
		return false; //return false
	}

	return true; //the if statement is false, so the current is <= weightLimit
}

void neighborhood::setItemAttributes(float weight, float price)
{
	itm.setPrice(price);//setting the item's price
	itm.setWeight(weight);//setting the item's weight
}

//getting the price of delivering to the neighborhood
float neighborhood::getPrice()
{
	float x = itm.getPrice();
	return x - distance;//returning the cost of the item minus the cost of driving to the house
}

void neighborhood::setDistributionCenter(int x)
{
	distCenterDist = x; //setting the distance from the distribution center
}

//gettin the total cost of going to the distribution center to the first house for delivery. Every mile costs $1.00
int neighborhood::getDistributionCenter()
{
	return itm.getPrice() - distCenterDist;//returning the distance away from the distribution center from the item price
}

float neighborhood::getWeight()
{
	float x = itm.getWeight();
	return x;//returning the items weight
}

//getting the price of the item before milage is considered
float neighborhood::getPrePrice()
{
	
	return itm.getPrice();
}