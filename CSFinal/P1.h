#include <iostream>
#include <list>

using namespace std;

class Node
{
public:
	Node(){id = 'g';left=NULL;right=NULL;}
	Node(char c)
	{
		
		id=c;
		left = NULL;
		right = NULL;
		holdlist.push_back('g');
		litr = holdlist.begin();
		cout << litr->getchar();
	}
	Node(char c, char lc)
	{
		
	}
	char getchar()
	{
		return id;
	}
	void addChar(char c, char lc)
	{
		if(id = c)
		{
			holdlist.push_back(lc);
		}
		else if(c < id)
		{
			if(left == NULL)
			{
				left = new Node(c);
			}
			else
			{
				left->addChar(c, lc);
			}
		}
		else
		{
			if(right == NULL)
			{
				right = new Node(c);
			}
			else
			{
				right->addChar(c, lc);
			}
		}
	}
	void display()
	{
		if(left!=NULL)
		{
			left->display();
		}
		cout << "ID: " << id << endl;
		if(right!=NULL)
		{
			right->display();
		}
	}
	private:
	char id;
	list<char> holdlist;
	list<char>::iterator litr;
	Node * left;
	Node * right;
};