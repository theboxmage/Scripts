#include <iostream>
#include <list>

using namespace std;

class Node
{
public:
	Node(){id = 'n';holdlist.push_back('n');left=NULL;right=NULL;}
	Node(char c)
	{
		
		id=c;
		left = NULL;
		right = NULL;
		holdlist.push_back('m');
	}
	Node(char c, char lc)
	{
		id=c;
		left = NULL;
		right = NULL;
		holdlist.push_back(lc);
	}
	char getchar()
	{
		return id;
	}
	void addChar(char c, char lc)
	{
		 if(c==id)
		 {
		 	holdlist.push_back(lc);
		 }
		 if(c < id)
		{
			if(left == NULL)
			{
				left = new Node(c, lc);
			}
			else
			{
				left->addChar(c, lc);
			}
		}
		if(c > id)
		{
			if(right == NULL)
			{
				right = new Node(c, lc);
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
		cout << "ID: " << id  << "                Entries: ";
		litr = holdlist.begin();
		while(litr!=holdlist.end())
		{
			cout << *litr;
			litr++;
		}
		cout << endl;
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