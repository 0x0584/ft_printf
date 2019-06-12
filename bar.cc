#include <iostream>
#include <cstdarg>
using namespace std;

void average(int n, ...);
void print(char* list, ...);


int main()
{
	average(5, 1, 2, 3, 4, 5);
	average(10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

	print("fsfi", 3.144159, "Hello world", 2.7, 100);
	print("ss", "hello", "world");

	return 0;
}


// Technique #1 -- fixed argument that specifies the number of arguments.

void average(int n, ...)
{
	va_list	args;				// create a variable argument list
	int	sum = 0;

	va_start(args, n);			// begin accessing variable arguments

	for (int i = 0; i < n; i++)
		sum += va_arg(args, int);	// get a variable argument
	cout << "Average: " << sum / n << endl;

	va_end(args);				// finish accessing variable arguments
}


// Technique #2 -- fixed argument that encodes the number and type of arguments.
// The letters 's', 'i', and 'f' denote
//	* c-strings
//	* integers
//	* floating point
// values respectively.

void print(char* list, ...)
{
	va_list	args;

	va_start(args, list);

	char c;
	while(c = *list++)
		switch(c)
		{
			case 's' : cout << va_arg(args, char*) << endl;
				   break;
			case 'i' : cout << va_arg(args, int) << endl;
				   break;
			case 'f' : cout << va_arg(args, double) << endl;
				   break;
		}

	va_end(args);
}
