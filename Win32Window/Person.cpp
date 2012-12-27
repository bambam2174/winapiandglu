#include "Person.h"
#include <stdio.h>
#include <iostream>

Person::Person(void)
{
	this->id = 0;
	strcpy(this->vorname, "Sedat");
	strcpy(this->nachname, "Kilinc");

}

Person::~Person(void)
{
}
