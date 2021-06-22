#include <iostream>
#include <omp.h>
#include <random>
#include <fstream>
#include "point.h"  
#include "Node.h"
#include "Body.h"
#include "BarnesHutSequential.h"
#include "BarnesHutParallel.h"

using namespace std;

const double MIN_X = -10000;
const double MAX_X = 10000;
const double MIN_Y = -10000;
const double MAX_Y = 10000;

double getRandomDouble(double min, double max)
{
	random_device rd;
	default_random_engine eng(rd());
	uniform_real_distribution<double> distr(min, max);

	return distr(eng);
};

Body* generateRandomBodies(int count) 
{
	Body* bodies = new Body[count];

	for (int i = 0; i < count; i++)
	{
		Point newPoint = Point(getRandomDouble(MIN_X /100, MAX_X / 100), getRandomDouble(MIN_Y / 100, MAX_Y / 100));
		Point initial_velocity = Point(getRandomDouble(-1, 1), getRandomDouble(-1, 1));
		bodies[i] = Body(newPoint, getRandomDouble(0, 10), initial_velocity);
	}

	return bodies;
}

//runs a configuration on 1,2,4,6,8,12 threads and writes results to results.txt
void runAllConfigurations(int bodyCount, double maxT, double dt, double theta) {
	ofstream file;
	file.open("results.txt", ios::app);

	Body* randomBodies = generateRandomBodies(bodyCount);

	file << "bodies: " << bodyCount << ", theta: " << theta << ", cycles: " << (int)maxT * 10 << "\n";
	double start = omp_get_wtime();
	BarnesHutSequential BHS = BarnesHutSequential();
	BHS.compute(randomBodies, bodyCount, maxT, dt, theta);
	double end = omp_get_wtime();
	file << "1: "<< end - start <<"\n";
	start = omp_get_wtime();
	BarnesHutParallel BHP = BarnesHutParallel(2);
	BHP.compute(randomBodies, bodyCount, maxT, dt, theta);
	end = omp_get_wtime();
	file << "2: " << end - start << "\n";
	start = omp_get_wtime();
	BHP = BarnesHutParallel(4);
	BHP.compute(randomBodies, bodyCount, maxT, dt, theta);
	end = omp_get_wtime();
	file << "4: " << end - start << "\n";
	start = omp_get_wtime();
	BHP = BarnesHutParallel(6);
	BHP.compute(randomBodies, bodyCount, maxT, dt, theta);
	end = omp_get_wtime();
	file << "6: " << end - start << "\n";
	start = omp_get_wtime();
	BHP = BarnesHutParallel(8);
	BHP.compute(randomBodies, bodyCount, maxT, dt, theta);
	end = omp_get_wtime();
	file << "8: " << end - start << "\n";
	start = omp_get_wtime();
	BHP = BarnesHutParallel(10);
	BHP.compute(randomBodies, bodyCount, maxT, dt, theta);
	end = omp_get_wtime();
	file << "10: " << end - start << "\n";
	start = omp_get_wtime();
	BHP = BarnesHutParallel(12);
	BHP.compute(randomBodies, bodyCount, maxT, dt, theta);
	end = omp_get_wtime();
	file << "12: " << end - start << "\n";

	file.close();
}

int main() 
{
	//Single test with 1000 bodies, 1000 cycles, 0.1 step and theta = 1
	runAllConfigurations(1000, 100, 0.1, 1.0);

	//Uncomment to run 80 tests!
	////10 to 10000 bodies, 10 to 10000 cycles, 2 to 0 theta - It takes forever in the last few!
	//for (int bodyCount = 10; bodyCount <= 10000; bodyCount *= 10)
	//{
	//	for (int maxT = 1; maxT <= 1000; maxT *= 10)
	//	{
	//		for (double theta = 2; theta >= 0; theta -= 0.5)
	//		{
	//			runAllConfigurations(bodyCount, maxT, 0.1, theta);
	//		}
	//	}
	//}
	
	return 0;
};