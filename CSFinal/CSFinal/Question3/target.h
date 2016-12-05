class target{
	public:
	target(int i)
	{
		threat = i;
		attempts=0;
	}
	int getT(){return threat;}
	int getB(){return attempts;}
	void incrementAttempts(){attempts++;}
    bool operator<(target& t)
	{
		return threat > t.getT();
	}
	
	private:
	int threat;
	int attempts;
};
