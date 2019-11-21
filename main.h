#ifndef MAIN_H
#define MAIN_H

#include <cmath>
#include <iostream>
#include <map>
#include <vector>

#define MAX_MUTATION 1
#define MAX_DNA_CHAR 126
#define MIN_DNA_CHAR 32
#define MAX_ORG_LENGTH 20
#define MIN_ORG_LENGTH 1

#define POPULATION_SIZE 20
#define PROGENATORS_SIZE 8
#define FAMILY_SIZE 2 // Do not change this one
#define NUM_OFFSPRING (POPULATION_SIZE / (PROGENATORS_SIZE / FAMILY_SIZE))

#define MAX_GENERATIONS 5000000

using namespace std;

typedef string organism;
typedef vector<string> population;
typedef int fitness;

void generate_population(int length, population *pop);

void mutate(organism *org);
organism breed(organism &org1, organism &org2);

fitness get_fitness(organism &org1, organism &key);
void sort_by_fitness(population *pop, organism &key);
organism get_fit_organism(population &pop);

#endif