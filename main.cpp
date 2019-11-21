#include <cmath>
#include <iostream>
#include <map>
#include <vector>

#include "main.h"


using namespace std;


int main(int argc, char **argv)
{
	srand(time(NULL));

	int i, generation = 0;
	organism key = "Hello, World!";
	vector<organism> pop;
	vector<organism> fornicators;

	generate_population(POPULATION_SIZE, &pop);

	cout << "Initial Population [" << pop.size() << "]: \n";
	for (auto it = pop.begin(); it != pop.end(); it++)
	{
		cout << *it << endl;
	}

	do
	{
		fornicators.clear();
		for (i = 0; i < PROGENATORS_SIZE; i++)
		{
			fornicators.push_back(get_fit_organism(pop));
		}

		pop.clear();
		while (pop.size() < POPULATION_SIZE)
		{
			for (i = 0; i < PROGENATORS_SIZE; i += 2)
			{
				pop.push_back(breed(fornicators[i], fornicators[i+1]));
			}
		}
		pop.resize(POPULATION_SIZE);

		sort_by_fitness(&pop, key);

		if (pop[0].compare(key) == 0) 
		{ 
			cout 
				<< "\nDone at: " << pop[0] 
				<< " " << get_fitness(pop[0], key) 
				<< " GENERATION#: " << generation 
				<< endl;
			break;
		}

		if (generation > MAX_GENERATIONS)
		{
			cout << "\nMax generation [" << generation << "] reached\n";
			break;
		}

		generation++;
	} while(1);

	sort_by_fitness(&pop, key);

	cout << "\nFinal Population [" << pop.size() << "]: \n";
	for (auto it = pop.begin(); it != pop.end(); it++)
	{
		cout << *it << endl;
	}

	return 0;
}



