#include <iostream>
#include <random>
#include <ctime>
#include <stack>
#include <queue>
using namespace std;

int current;

int main()
{
	uniform_int_distribution<int> radist(1, 100);
	int state=0;
	stack<int> popstack;
	priority_queue<int> queue[4];
	default_random_engine gen(time(NULL));
	uniform_int_distribution<int> amdist(1, 5);
	uniform_int_distribution<int> qudist(0, 3);



	bool flag = true;
	while(flag)
	{
		for(int y = 0; y < 5; y++)//Timesteps
		{
			int amount = amdist(gen);
			for(int i = 0; i < amount; i++)
			{
	
				queue[state].push(radist(gen));
				if(state<3)
				{
					state++;
				}
				else
				{
					state=0;
				}
			}
			int popqueue = qudist(gen);
			if(!queue[popqueue].empty())
			{
				popstack.push(queue[popqueue].top());
				queue[popqueue].pop();
			}
		}
		queue[0].pop();
		for(int z = 0; z < 4; z++)
		{
		  cout << "Queue: " << z+1 << ": ";
			priority_queue<int> holdqueue = queue[z];
			while(!holdqueue.empty())
			{
				cout << holdqueue.top() << " ";
				holdqueue.pop();
			}
		     cout << endl;
		}
		cout << "Stack: ";
		stack<int> emptystack = popstack;
		while(!emptystack.empty())
		{
			cout << emptystack.top() << " ";
			emptystack.pop();
		}
		cout << endl << "Would you like to run for another 5 timesteps? (y/n)" << endl;
		string hold = "";
		cin >> hold;
		if(hold=="n"||hold=="q")
		{
			flag = false;
		}
	}
	
}
