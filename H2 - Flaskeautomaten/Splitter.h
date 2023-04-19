#pragma once
class Splitter
{
public:
	Splitter() {}
	~Splitter() {}
	void Run();
private:
	int amountOfWaters = 0;
	int amountOfBeers = 0;

	void SplitBottles();
	void SplitBeer();
	void SplitWater();
};

