#include <iostream>
#include "P1.h"
using namespace std;


int main()
{
	Node root = Node('n', 'q');
	root.addChar('d', 'b');
	root.addChar('a', 'b');
	root.addChar('b', 'b');
	root.addChar('d', 'c');
	root.display();
}