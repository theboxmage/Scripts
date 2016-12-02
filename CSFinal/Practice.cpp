#include <iostream>
#include "P1.h"
using namespace std;


int main()
{
	Node root = Node('g');
	for(int i = 0; i < 5; i++)
	{
		char hold;
		cin >> hold;
		char hold2;
		cin >> hold2;
		root.addChar(hold, hold2);
		root.display();
	}
}