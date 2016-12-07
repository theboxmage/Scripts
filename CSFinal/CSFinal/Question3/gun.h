#include <iomanip>

class gun{
	public:
	gun(std::list<target> & tarvec,  std::default_random_engine generator)
	{
		gen = generator;
		targets = tarvec;
		targets.sort();
	}

	void fire()
	{
		std::uniform_int_distribution<int> dis(1,100);
		taritr = targets.begin();
		while(taritr!=targets.end())
		{
			int hold = dis(gen);
			taritr->incrementAttempts();
			while(hold>85)
			{
				hold=dis(gen);
				taritr->incrementAttempts();
			}
			taritr++;
		}
	}
	
	void display()
	{
		taritr = targets.begin();
		int i = 1;
		while(taritr != targets.end())
		{
			std::cout << "Target " <<  i << " Threat: " <<  std::setw(3) << taritr->getT()  << " " << taritr->getB();
			if(taritr->getB() > 1)
			{
				std::cout << " bursts";
			}
			else
			{
				std::cout << " burst";
			}
			std::cout << std::endl;
			
			//std::endl;
			taritr++;
			i++;
		}
	}
	private:
	std::list<target> targets;
	std::list<target>::iterator taritr;
	std::default_random_engine gen;
};
