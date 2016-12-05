#include <iostream>
#include <random>
#include <queue>
#include <ctime>
#include "box.h"
#include "tree.h"
using namespace std;

int main()
{
	//default_random_engine gen(10000000000);
	//default_random_engine gen(10);

	uniform_int_distribution<int> dis(0,100);	
	queue<box> boxes = queue<box>();
	
	cout << "Input the amount of boxes to be added." << endl;
	int boxcount;
	cin >> boxcount;
	
	cin.ignore();
	cout << endl << "Contents of the queue: \n";
	for(int i = 0; i < boxcount; i++)
	{
		box holdbox = box(dis(gen));
		boxes.push(holdbox);
		cout << holdbox.getv() << endl;
	}
	cout << endl << "Displaying the boxes: \n";
	
	node root = node();
	while(!boxes.empty())
	{
		root.add(boxes.front());
		boxes.pop();
	}
	root.display();
	
	cout << endl;

	while(!boxes.empty())
	{
		cout << boxes.front().getv() << endl;
		boxes.pop();
	}
}