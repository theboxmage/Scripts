#include <iostream>
#include <queue>

class box
{
	public:
		box(int vin)
		{
			v = vin;
		}
		int getv(){return v;}
	private:
	int v;
};