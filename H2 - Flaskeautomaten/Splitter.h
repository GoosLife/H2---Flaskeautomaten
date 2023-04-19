#pragma once

/// <summary>
/// Splitter class that handles the splitting of bottles.
/// </summary>
class Splitter
{
public:
	Splitter() {}
	~Splitter() {}

	/// <summary>
	/// While run is running, the splitter will split the bottles
	/// </summary>
	void Run();
private:
	// Counters for how many bottles the splitter needs to split (the splitter stores the bottles as a simple integer value, as  opposed to the buffer which stores them in an array
	// This is done to show what happens when the global buffer or water/beer buffers are full, as the splitter will not be able to split the bottles.
	// Fx, we can produce more bottles than are consumed, and the splitter will start storing large amounts of bottles it can't get rid of.
	// We could also set a limit on how many bottles the splitter can store, as that would make the process more complicated, but in this case, we prefer to show what happens when the splitter starts building up a backlog of bottles.
	int amountOfWaters = 0;
	int amountOfBeers = 0;

	// Sort the bottles in to water and beer bottles, then send them to their respective buffers
	void SplitBottles();
	void SplitBeer();
	void SplitWater();
};

