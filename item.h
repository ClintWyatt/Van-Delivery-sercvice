#ifndef H_item
#define H_item

#include <iostream>

using namespace std;

class item {
public:

	item();
	item(item &old_obj);//copy constructor
	void setPrice(float x);
	void setWeight(float x);
	float getWeight();
	float getPrice();
	float getRealPrice(float x); //will return the cost of the item minus the cost of gas to get to the neighborhood

private:
	float price;
	float weight;
};

#endif 
#pragma once
