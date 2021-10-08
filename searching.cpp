#include<iostream>
#include<fcntl.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
using namespace std;

int main()
{
	int pipeid[2], pid, i, size, choice, search;
	srand(time(NULL));
	pipe(pipeid);

	cout<<"Enter the size of the array: ";
	cin>>size;

	int array[size];

	cout<<"\nYou want to enter data or use random data ?\n1. Enter data\n2. Random data\n";
	cin>>choice;

	if (choice==1)
	{
		for (i = 0; i < size; i++)
		{
			cin>>array[i];
		}
	}

	else
	{
		for (i = 0; i < size; i++)
		{
			array[i]=rand()%100;
		}
	}

	cout<<"\nDisplaying array\n";
	for(i=0; i<size; i++)
	{
		cout<<array[i]<<" ";
	}

	cout<<endl;

	pid=fork();

	if(pid>0)
	{
		cout<<"\nEnter the number you want to search: ";
		cin>>search;

		fflush(stdin);
		write(pipeid[1], &search, sizeof(search));
		wait(NULL);
	}

	if(pid==0)
	{
		fflush(stdin);
		read(pipeid[0], &search, sizeof(search));

		for(i=0;i<size;i++)
		{
			if(search==array[i])
			{
				cout<<"\nFound\n";
				exit(0);
			}
		}

		cout<<"\nNot found\n";
	}
}