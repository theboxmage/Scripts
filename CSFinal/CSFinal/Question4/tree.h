#include <iomanip>


class node
{
	public:
		node()
		{
			v = -1;
			f = 0;
			left=NULL;
			right=NULL;
		}
		node(int vi)
		{
			v = vi;
			f = 1;
			left=NULL;
			right=NULL;
		}
		void add(box input)//69 43
		{
			if(v == -1)
			{
				v = input.getv();
			}
			if(input.getv() == v)
			{
				incrementF();
			}
			if(v > input.getv())
			{
				addLesser(input);
			}
			if(v < input.getv())
			{
				addGreater(input);
			}
		}

		void addGreater(box & input)
		{
			if(right!=NULL)
			{
				right->add(input);
			}
			else
			{
				right = new node(input.getv());
			}
		}

		void addLesser(box & input)
		{
			if(left!=NULL)
			{
				left->add(input);
			}
			else
			{
				left = new node(input.getv());
			}
		}
		void incrementF(){f++;}
		void display()
		{
			if(left!=NULL)
			{
				left->display();
			}
			std::cout <<  std::left << std::setw(2)  << v << " with a frequency of: " << f << "." << std::endl;
			if(right!=NULL)
			{
				right->display();
			}
		}
	private:
	int v;
	int f;
	node * left;
	node * right;
};
