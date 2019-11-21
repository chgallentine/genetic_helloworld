/*
* @Author: Charlie Gallentine
* @Date:   2019-11-21 08:38:21
* @Last Modified by:   Charlie Gallentine
* @Last Modified time: 2019-11-21 08:53:21
*/
#include "main.h"

/*
	Return: fitness typedef, the fitness of the organism
	Param1: organism typedef, organism to check for fitness
	Param2: organism typedef, ideal organism

	Checks two organisms of varying length for fitness
 */
fitness get_fitness(organism &org, organism &key)
{
	organism longer, shorter;
	int i;
	int fit = 0;

	// No guarantee of equal length organism DNA
	longer = org.length() > key.length() ? org : key;
	shorter = org.length() <= key.length() ? org : key;

	// For the parts that can be compared
	for (i = 0; i < shorter.length(); i++)
	{
		fit += abs((int) shorter[i] - (int) longer[i]);
	}

	// Add all non-comparable items into fitness
	while (i < longer.length())
	{
		i++;
		fit += (int) longer[i];	
	}

	return fit;
}

/*
	Return: void
	Param1: organism typedef, organism to mutate

	Mutates organism by changing a single character
 */
void mutate(organism *org)
{
	int index, mutation;

	// Some of the time add or decrease length
	if (rand() % 100 <= 10 && org->length() > 1 && org->length() < MAX_ORG_LENGTH)
	{
		if (rand() % 2 == 1 && org->length() > 1)
		{
			// ~ One in 40 times, remove the end character
			*org = org->substr(0, org->length() - 1);
		}
		else if (org->length() < MAX_ORG_LENGTH)
		{
			// ~ One in 40 times, add a new character to the end
			*org += ((double) rand() / RAND_MAX) * (MAX_DNA_CHAR - MIN_DNA_CHAR) + MIN_DNA_CHAR;
		}
	}
	else
	{
		// Get a random index of organism and mutate it
		index = rand() % org->length();

		mutation = rand() % MAX_MUTATION + 1;
		mutation *= rand() % 2 == 1 ? -1 : 1;

		(*org)[index] += mutation;
	}
}

/*
	Return: organism typedef, the bred organism
	Param1: organism typedef, organism to breed
	Param2: organism typedef, organism to breed

	Combines two organisms and mutates the offspring
 */
organism breed(organism &org1, organism &org2)
{
	organism longer, shorter, out;
	int i;

	longer = org1.length() > org2.length() ? org1 : org2;
	shorter = org2.length() <= org2.length() ? org1 : org2;

	// Randomly combine two input organisms over equal parts
	for (i = 0; i < shorter.length(); i++)
	{
		out += ((rand() % 2 == 1 ? shorter[i] : longer[i]));
	}

	// If longer organism, add around half excess DNA
	while (i < longer.length())
	{	
		if (rand() % 2 == 1)
		{
			out += longer[i];
		}
		i++;
	}

	// To follow breed-and-mutate procedure
	mutate(&out);

	return out;
}

/*
	Return: void
	Param1: integer, length of population to create
	Param2: population typedef pointer, empty population to fill

	Creates a new population of organisms
 */
void generate_population(int length, population *pop)
{
	int i, j, sublen;
	organism tmp_org;

	pop->reserve(length);

	for (i = 0; i < length; i++)
	{
		// Each organism has random length
		sublen = (rand() % (MAX_ORG_LENGTH - MIN_ORG_LENGTH + 1)) + MIN_ORG_LENGTH;
		tmp_org = "";

		for (j = 0; j < sublen; j++)
		{
			tmp_org += ((double) rand() / RAND_MAX) * (MAX_DNA_CHAR - MIN_DNA_CHAR) + MIN_DNA_CHAR;
		}

		pop->push_back(tmp_org);
	}
}

/*
	Return: void
	Param1: population typedef pointer, the population to sort
	Param2: organism typedef, the ideal organism to generate fitness
 */
void sort_by_fitness(population *pop, organism &key)
{
	map<fitness, organism> popfit;

	// Adds to map to sort by fitness
	for (auto it = pop->begin(); it != pop->end(); it++)
	{
		// POSSIBLE BUG: EQUAL FITNESS ORGANISMS GET ELIMINATED
		popfit[get_fitness(*it, key)] = *it;
	}

	pop->clear();

	// Put the sorted organisms back into population
	for (auto it = popfit.begin(); it != popfit.end(); it++)
	{
		pop->push_back(it->second);
	}
}

/*
	Return: organism typedef
	Param1: population typedef

	Uses a uniform product distribution to select a fit organism to breed
 */
organism get_fit_organism(population &pop)
{
	double r1;
	int index;

	// Weight towards higher values
	r1 = (double) rand() / RAND_MAX;

	// Weights to lower indices
	index = pow(r1, 2) * pop.size();

	return pop[index];
}














