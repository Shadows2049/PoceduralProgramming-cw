/************************************************************************
University of Leeds
School of Computing
COMP1711/XJCO1711- Procedural Programming
Coursework 3
File: logic.c

I confirm that the following code has been developed and written by me and it is entirely the result of my own work.
I also confirm that I have not copied any parts of this program from another person or any other source or facilitated someone to copy this program from me.
I confirm that I will not publish the program online or share it with anyone without permission of the module leader.

Student Name: 201388927
Student ID: LeShan Wang
Email: sc19l2w@leeds.ac.uk
Date Work Commenced: 12/2/2020
*************************************************************************/

// ********************************************************************************************************************
// DO NOT CHANGE ANYTHING IN THE FOLLOWING SECTION. IF YOU CHANGE ANYTHING, YOUR CODE WILL FAIL THE AUTOGRADER TESTS.
// However, please read through this section and look at the declarations of arrays and global vars that you will be using in your program

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include "uni.h"

int SerNum = 0;	  // a counter to create unique star numbers (identifiers)
int numStars = 0; // the actual number of stars in the universe (not the same as the maximum)
int numPairs = 0; // the number of pairs that have been named

Star *stars[MaxStar]; // the array of stars (an array of pointers to stars)
Pair *pairs[MaxPair]; // the array of named pairs (an array of pointers to pairs)

// END OF CODE SECTION THAT SHOULD NOT BE CHANGED
// ************************************************

// --------------------------------------------------------------------------------------------------
// NOW IT IS YOUR TURN, YOU CAN DEFINE ANY OTHER GLOBAL VARIABLES YOU MAY NEED IN YOUR CODE BELOW THIS LINE

Star star[MaxStar];

Pair pair[MaxPair];

int cop = 0;
int pop = 0;

// END OF SECTION FOR DECLARRING ADDITIONAL GLOBAL VARIABLES
// ----------------------------------------------------------

// -------------------------------------------------------------------------------------------------
// NOW, IMPLEMENT THE FOLLOWING FUNCTIONS BY WRITING THE CORRECT CODE IN THE BODIES OF THE FUNCTIONS
// please, don't change the functions' names, return types, or parameters. If you change any of these the grader will crash
// Initially, some of these functions contain 'return 0' or 'return -99'. Before implementing a function you should delete this statement
// None of the functions should cause memory leaks

// The purpose of this function is to find a star through its coordinates.
// The first two parameters are the coordinates of the star we are looking for.
// Since the coordinates are double (real) numbers, we cannot compare them for exact equality,
// hence the 3rd parameter to this function is a very small number (e.g. 0.00000001) called the tolerance.
// If the absolute difference between the x (or y) coordinate of a star and the given x (or y) coordinate
// is less than the tolerance, we assume that the two values are equal.
// If a star with the given x and y coordinates is found, the function should return a pointer to this star
// otherwise the function returns 0 indicating failure to find a star with such coordinates.
// 4-6 lines of code.
Star *findStarByXY(double x, double y, double tolerance)
{

	for (int i = 0; i < numStars; ++i)
	{
		if ((stars[i]->x - x <= tolerance && stars[i]->x - x >= -tolerance) && (stars[i]->y - y <= tolerance && stars[i]->y - y >= -tolerance))
			return stars[i];
	}
	return 0;
}

// The purpose of this function is to create a new universe containing stars only.
// The number of stars in this new universe is given by the parameter n_stars.
// The stars should be randomly scattered within the universe, i.e, each star should be assigned a random value
// for its x and y coordinates. x can take any random value from [0 - MaxX] inclusive,
// and y can take any random value from [0 - MaxY] inclusive.
// Although the x and y coordinates of a star are defined as double numbers, for simplicity we will only
// assign whole numbers to x and y. Every star should have its unique location, no two stars can have the same x and y coordinates.
// Hence the maximum number of stars in a completely filled universe that is 60 lights years long and 30 light years wide
// is 1891 stars (this is the value of MaxStar defined in uni.h). The minimum number of stars in a universe is 1.
// If the function fails to create the universe for any reason (including an invalid value of n_stars), it should return 0
// indicating failure, otherwise it should return 1 indicating success.
// Since this function is the start of a new universe, it should also initialise all global variables.
int bigBang(int n_stars)
{

	SerNum = 0;
	numStars = 0;
	numPairs = 0;
	numStars = n_stars;

	if (n_stars >= 1 && n_stars <= MaxStar)

	{

		for (int i = 0; i < MaxStar; i++)
		{

			stars[i] = &star[i];
		}

		for (int q = 0; q < MaxPair; q++)
		{

			pairs[q] = &pair[q];
		}

		int grid[31][61];
		for (int rat = 0; rat < 31; ++rat)
		{
			for (int cot = 0; cot < 61; ++cot)
				grid[rat][cot] = 0;
		}

		int row;
		int col;

		for (int k = 0; k < MaxStar; k++)
		{
			memset(stars[k]->name, 0, sizeof(stars[k]->name));
			stars[k]->id = 0;
			stars[k]->x = 0;
			stars[k]->y = 0;
			stars[k]->named = 0;
		}

		for (int r = 0; r < MaxPair; r++)
		{

			pairs[r]->d = 0;
			pairs[r]->h = NULL;
			pairs[r]->w = NULL;
		}

		/*time_t t;
   srand((unsigned) time(&t));*/

		for (int s = 0; s < n_stars; s++)
		{

			row = rand() % 31;

			col = rand() % 61;

			if (grid[row][col] == 0)
			{
				grid[row][col] = 1;
				stars[s]->id = s;
				stars[s]->x = col;
				stars[s]->y = row;
			}

			else
				s = s - 1;
		}

		return 1;
	}

	else
		numStars = 0;
	return 0;
}

// The purpose of this function is to compute the distance between two points in a Cartesian plane.
// The coordinates of the first point are x1 , y1.
// The coordinates of the second point are x2, y2.
// The function returns the distance between the two points.
// 2 lines of code.
double pointDistance(double x1, double y1, double x2, double y2)
{

	double distance;
	distance = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));

	return distance;
}

// The purpose of this function is to find the closest pair of stars that have not been named yet.
// If a pair cannot be found (e.g. because all pairs have already been named) the function should return 0 (null),
// otherwise the function should return a pointer to a Pair structure initialised with h pointing to the first star in the pair
// and w pointing to the second star.
Pair *closestPair()
{

	double distance;
	double min = 800;
	int number;
	number = 0;

	for (int cout = 0; cout < numStars; ++cout)
	{
		if (stars[cout]->named == 0)
		{
			number = number + 1;
		}
	}

	if (number >= 2)
	{
		for (int c1 = 0; c1 < numStars - 1; c1++)
		{
			for (int c2 = c1 + 1; c2 < numStars; c2++)
			{
				distance = pointDistance(stars[c1]->x, stars[c1]->y, stars[c2]->x, stars[c2]->y);
				if (distance < min && stars[c1]->named == 0 && stars[c2]->named == 0)
				{
					min = distance;
					pairs[numPairs]->h = stars[c1];
					pairs[numPairs]->w = stars[c2];
					pairs[numPairs]->d = min;
				}
			}
		}
	}

	if (min == 800)
		return 0;

	else
		return pairs[numPairs];
}

// The purpose of this function is to assign the name of a person to a star.
// The first parameter is a pointer to the star to be named.
// The second parameter is the first name of the person.
// The last parameter is the surname of the person.
// The function should append the surname to the first name - with one single space in between - to create one single string for the full name.
// For example, if the first name is "Mr" and the surname is "Bean", the full name string will be "Mr Bean".
// If everything goes well and the star is named, the function returns 1 indicating success.
// The function also sets the named flag of the star to 1.
// If anything goes wrong (including invalid parameter values), the function should return 0 indicating failure.
int nameStar(Star *s, char *first_name, char *sur_name)
{
	int counter = 0;

	if (s == NULL || first_name == NULL || sur_name == NULL || strlen(first_name) + strlen(sur_name) > 30)
		return 0;

	else
	{

		for (counter = 0; counter < strlen(first_name) + strlen(sur_name) + 1; counter++)
		{
			if (counter < strlen(first_name))
				s->name[counter] = first_name[counter];

			if (counter == strlen(first_name))
				s->name[counter] = ' ';

			if (strlen(first_name) < counter && counter < strlen(first_name) + strlen(sur_name) + 1)
				s->name[counter] = sur_name[counter - strlen(first_name) - 1];
		}

		s->name[counter + 1] = '\0';
		s->named = 1;

		return 1;
	}
}

// The purpose of this function is to find a pair by the name of either spouse (one of the owners of the pair).
// The parameter to this function is the full name of a person.
// If either star in a named pair have this name, the function returns a pointer to this pair,
// If no such pair is found the function returns 0
Pair *findPairByName(char *name)
{

	int counter = 0;
	int switch1 = 0;
	int indicator = 0;

	for (int i = 0; i < numPairs; ++i)
	{
		switch1 = 1;

		for (counter = 0; counter < strlen(name); counter++)
		{
			if (name[counter] == (pairs[i]->h)->name[counter] && strlen(name) == strlen((pairs[i]->h)->name) && switch1 == 1)
			{
				switch1 = 1;
				if (counter == strlen(name) - 1)
				{

					return pairs[i];
				}
			}

			else
			{
				switch1 = 0;
				break;
			}
		}
	}

	for (int i = 0; i < numPairs; ++i)
	{
		switch1 = 1;

		for (counter = 0; counter < strlen(name); counter++)
		{
			if (name[counter] == (pairs[i]->w)->name[counter] && strlen(name) == strlen((pairs[i]->w)->name) && switch1 == 1)
			{
				switch1 = 1;
				if (counter == strlen(name) - 1)
				{

					return pairs[i];
					break;
				}
			}

			else
			{
				switch1 = 0;
				break;
			}
		}
	}

	return 0;
}

// The purpose of this function is to save all the data of the program to a binary file called "universe.bin".
// If the file cannot be opened, the function should return 0 indicating failure,
// If everything goes well, the function returns 1 indicating success in saving the universe
int saveUniverse()
{
	int k = 0;
	int j = 0;

	cop = numStars;
	pop = numPairs;

	FILE *out;
	out = fopen("universe.bin", "wb");
	if (out != NULL)
	{

		fwrite(&cop, sizeof(int), 1, out);
		fwrite(&pop, sizeof(int), 1, out);

		for (k = 0; k < cop; ++k)
			fwrite(stars[k], sizeof(Star), 1, out);

		for (j = 0; j < pop; ++j)
			fwrite(pairs[j], sizeof(Pair), 1, out);

		fclose(out);
		return 1;
	}
	return 0;
}

// The purpose of this function is to load a universe from a binary file called "universe.bin".
// If the file cannot be opened, the function should return 0 indicating failure,
// If everything goes well, the function returns 1, indicating success in loading the universe
int loadUniverse()
{
	int k = 0;
	int j = 0;



	FILE *in;
	in = fopen("universe.bin", "rb");
	if (in != NULL)
	{

		fread(&cop, sizeof(int), 1, in);
		fread(&pop, sizeof(int), 1, in);

		for (k = 0; k < cop; ++k)
			fread(stars[k], sizeof(Star), 1, in);

		for (j = 0; j < pop; ++j)
			fread(pairs[j], sizeof(Pair), 1, in);
		numStars = cop;
		numPairs = pop;

		fclose(in);
		return 1;
	}
	return 0;
}

// IF YOU NEED ADDITIONAL FUNCTIONS YOU CAN DEFINE THEM BELOW
// WITH THEIR PROTOTYPES DEFINED IN THE GLOBAL VARS SECTION OF THIS FILE
//----------------------------------------------------------------------


