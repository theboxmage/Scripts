#include <iostream>
#include <random>
#include <ctime>
#include <cmath>
#include <list>
#include "target.h"
#include "gun.h"
using namespace std;

int main()
{
    default_random_engine gen(time(NULL));
	uniform_int_distribution<int> dis(4,10);
	normal_distribution<float> threatdist(100.0, 15.0);
	list<target> tarvec;
	for(int i = 0; i < dis(gen); i++)
	{
		tarvec.push_back(target(threatdist(gen)));
	}
	gun hold = gun(tarvec, gen);
		hold.fire();
	hold.display();
	//target newtar = target(10);
	//cout << newtar.getT();

}