//Anthony Mace CSC240 2/8/14
//This program demonstrates how to use pointer
//manipulation at the low level in C++. It implements
//the Sieve of of Eratosthenes algorithm.

#include <iostream>
#include <math.h>
using namespace std; 

void displayIntro();
void quitProg();
char repeatProcess();
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
	char repeat;
	displayIntro();
	do {
		int lowerBound, upperBound = 0;
		int newArraySize;
		int index = 0;
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
		repeat = repeatProcess();
	} while (repeat == 'y' || repeat == 'Y');
	quitProg();
}

void displayIntro() {
	cout << "This program implements the Sieve of Eratosthenes"
		<< endl << "algorithm to find all the prime numbers within"
		<< endl << "a given range." << endl << endl;
}

void quitProg() {
	cout << "You have quit the program." << endl;
}

char repeatProcess() {
	char repeat;
	cout << "Would you like to repeat this process?" << endl;
	cout << "Enter y for yes, n for no: ";
	cin >> repeat;
	cout << endl;
	return repeat;
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
	int *firstIndex = zeroArray;
	*firstIndex = -1;
	int *secondIndex = zeroArray++;
	*secondIndex = -1;
	int *start = zeroArray + 2;
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
	int *factorIndex = primesArray + factor;
	*factorIndex = 1;
	int *start = factorIndex + factor;
	int *last = primesArray + size;
	while (start < last) {
		*start = -1;
		start += factor;
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
	newArraySize = 0;
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