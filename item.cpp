#include "item.h"
#include <iostream>

using namespace std;

//no arg constructor that will set the price and weight to zero automatically
item::item()
{
	price = 0.0;
	weight = 0.0;
}

item::item(item &old_obj)
{
	price = old_obj.price;
	weight = old_obj.weight;
}

//setter method for the item price
void item::setPrice(float x)
{
	price = x;
}

//setter method for the item weight
void item::setWeight(float x)
{
	weight = x;
}

//getter method for the weight
float item::getWeight()
{
	return weight;
}

float item::getPrice()
{
	return price;
}
//getter method for the real price after delivery
float item::getRealPrice(float x)
{
	return price - x;
}