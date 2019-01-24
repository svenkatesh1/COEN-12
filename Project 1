#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//defining the length variable
#define MAX_WORD_LENGTH 30

int read_file(char*); //defining a function to read the file

int main(int argc, char *argv[])
{
	//Checks if the file name is provided or not
	if(argc == 1)
	{
		printf("File name is missing\n");
		return -1;
	}
	//Prints total number of words
	printf("%d total words/n", read_file(argv[1]));
	return 0;
}

int read_file(char name[])
{
	//Creates a file pointer and opens file taken in as arugument
	FILE *fp;
	fp = fopen(name,"r");

	//Checks for empty or non-existent file
	if(fp == NULL)
	{
		printf("Error opening file\n");
		return -1;
	}

	//create necessary variables
	char string[MAX_WORD_LENGTH +1];
	int count = 0;

	//counts number of words
	while(fscanf(fp, "%s", string) == 1)
	{
		count++;
	}
	//Returns the number of words
	return count;
}
