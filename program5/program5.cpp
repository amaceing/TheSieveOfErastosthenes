//Anthony Mace CSC240 2/8/14
//This program demonstrates how to use array
//manipulation at the low level in C++. It implements
//the Sieve of of Eratosthenes algorithm.

#include <iostream>
#include <math.h>
using namespace std; 

void displayIntro();
int getLowerBoundary();
int getUpperBoundary();
void checkBoundaries(int &lowerBound, int &upperBound);
int *initializeArray(int size);
int getIndexOfFirstZero(int *primesArray, int size);
void findMultiplesOfFactors(int factor, int arraySize, int *primesArray);
void findMultiples(int *startArray, int size, int factor);
void convertZeroestoOnes(int *primesArray, int size);
int *getPrimeNumbers(int *primesArray, int size, int &newArraySize);
void displayPrimeNumbers(int *primeNumbers, int lowerBound, 
						 int upperBound, int newArraySize);

void main() {
	int lowerBound, upperBound = 0;
	int newArraySize = 0;
	int index = 0;
	displayIntro();
	lowerBound = getLowerBoundary();
	upperBound = getUpperBoundary();
	checkBoundaries(lowerBound, upperBound);
	int arraySize = upperBound;
	int *primesArray = initializeArray(arraySize);
	int factor = getIndexOfFirstZero(primesArray, arraySize);
	findMultiplesOfFactors(factor, arraySize, primesArray);
	convertZeroestoOnes(primesArray, arraySize);
	int *primeNumbers = getPrimeNumbers(primesArray, arraySize, newArraySize);
	displayPrimeNumbers(primeNumbers, lowerBound, upperBound, newArraySize);
}

void displayIntro() {
	cout << "This program implements the Sieve of Eratosthenes"
		<< endl << "algorithm to find all the prime numbers within"
		<< endl << "a given range." << endl << endl;
}

int getLowerBoundary() {
	int lowerBound;
	cout << "Please enter a lower bound on the range of numbers" << endl;
	cout << "Lower bound: ";
	cin >> lowerBound;
	while (lowerBound <= 0) {
		cout << "Please enter a positive number: ";
		cin >> lowerBound;
	}
	cout << endl;
	return lowerBound;
}

int getUpperBoundary() {
	int upperBound;
	cout << "Please enter an upper bound on the range of numbers" << endl;
	cout << "Upper bound: ";
	cin >> upperBound;
	while (upperBound <= 0) {
		cout << "Please enter a positive number: ";
		cin >> upperBound;
	}
	cout << endl;
	return upperBound;
}

void checkBoundaries(int &lowerBound, int &upperBound) {
	while (upperBound <= lowerBound) {
		cout << "The upper bound is lower than the lower bound!" << endl
			<< "Please re-enter the boundaries." << endl;
		lowerBound = getLowerBoundary();
		upperBound = getUpperBoundary();
		cout << endl << endl;
	}
}

int *initializeArray(int size) {
	int *zeroArray = new int[size];
	int *last = zeroArray + size;
	zeroArray[0] = -1;
	zeroArray[1] = -1;
	int *start = &zeroArray[2];
	while (start < last) {
		*start = 0;
		start++;
	}
	return zeroArray;
}

int getIndexOfFirstZero(int *primesArray, int size) {
	int *start = primesArray;
	int *last = primesArray + size;
	while ((*primesArray != 0) && (primesArray < last)) {
		primesArray++;
	}
	int index = primesArray - start;
	return index;
}

void findMultiplesOfFactors(int factor, int arraySize, int *primesArray) {
	while (factor <= sqrt(arraySize)) {
		findMultiples(primesArray, arraySize, factor);
		factor = getIndexOfFirstZero(primesArray, arraySize);
	}
}

void findMultiples(int *primesArray, int size, int factor) {
	primesArray[factor] = 1;
	int *start = &primesArray[factor + 1];
	int *last = primesArray + size;
	while (start < last) {
		if ((start - primesArray) % factor == 0) {
			*start = -1;
		}
		start++;
	}
}

void convertZeroestoOnes(int *primesArray, int size) {
	int *last = primesArray + size;
	while (primesArray < last) {
		if (*primesArray == 0) {
			*primesArray = 1;
		}
		primesArray++;
	}
}

int *getPrimeNumbers(int *primesArray, int size, int &newArraySize) {
	int *start = primesArray;
	int *last = primesArray + size;
	int index = 0;
	while (start < last) {
		if (*start == 1) {
			newArraySize++;
		} 
		start++;
	}
	int *primeNumbers = new int[newArraySize];
	int *primeNumbersStart = primeNumbers;
	start = primesArray;
	while (start < last) {
		if (*start == 1) {
			*primeNumbers = start - primesArray;
			primeNumbers++;
		}
		start++;
	}
	return primeNumbersStart;
}

void displayPrimeNumbers(int *primeNums, int lowerBound, 
						 int upperBound, int arraySize) {
	cout << "Primes between "<<lowerBound<< " and " << upperBound << ": "
		<< endl << endl;
	int *start = primeNums;
	int *last = primeNums + arraySize;
	while (start < last) {
		if (*start >= lowerBound) {
			cout << *start << endl << endl;
		}
		start++;
	}
}