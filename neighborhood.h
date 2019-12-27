#ifndef H_neighborhood
#define H_neighborhood
#include "item.h"
#include <iostream>

using namespace std;

class neighborhood
{
public:

	neighborhood();
	neighborhood(const neighborhood &house);//copy constructor
	void setDistance(double x);//distance from other neighborhoods
	float getDistance();//distance from other neoghborhoods
	bool enoughWeight(float currentWeight, float weightLimit); //enough weight from the current weight 
	void setKnown(bool x);
	void setFound(bool x);
	bool getFound();
	bool getKnown(); 
	void setItemAttributes(float weight, float price);
	float getWeight();
	float getPrice();
	float getPrePrice(); //getting the price of the item before milage is considered
	void setDistributionCenter(int x);
	int getDistributionCenter();
	void setName(int x);
	int getName();

private:
	bool found = false;
	float distance;
	int distCenterDist;
	bool known = false;
	int name;
	item itm; //item that is specific to this object (neighborhood)
};

#endif // !H_neighborhood
#pragma once
