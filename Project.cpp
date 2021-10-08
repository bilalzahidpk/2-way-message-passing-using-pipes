#include<iostream>
#include<fcntl.h>
#include <sys/wait.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
using namespace std;

int main()
{
	int pipefd[2], pid, row, col, size, i, j, num, count=1, k=0, choice;

	pipe(pipefd);

	cout<<"Enter the size of row and column (square matrix): ";
	cin>>row>>col;

	int m1[row][col], m2[row][col];

	size=(row * col);

	cout<<"\nYou want to enter data for matrix or use random data? \n1. Enter data\n2. Random data\n";
	cin>>choice;


	if(choice==2)
	{
		srand(time(NULL));
	
		for(i=1;i<=row;i++)
		{
			for(j=1;j<=col;j++)
			{
				m1[i][j]=rand()%100;
				m2[i][j]=rand()%100;
			}
		}
	}

	else
	{
		cout<<"\nEnter data for matrix one:\n";
		for(i=1;i<=row;i++)
		{
			for(j=1;j<=col;j++)
			{
				cin>>m1[i][j];
			}
		}

		cout<<"\nEnter data for matrix two:\n";
		for(i=1;i<=row;i++)
		{
			for(j=1;j<=col;j++)
			{
				cin>>m2[i][j];
			}
		}
	}
	

	cout<<"\nDisplaying matrix 1:\n";
	for(i=1;i<=row;i++)
	{
		for(j=1;j<=col;j++)
		{
			cout<<m1[i][j]<<" ";
		}
		cout<<endl;
	}	

	cout<<"Displaying matrix 2:\n";
	for(i=1;i<=row;i++)
	{
		for(j=1;j<=col;j++)
		{
			cout<<m2[i][j]<<" ";
		}
		cout<<endl;
	}

     
    i=1;
    j=1;

	pid=fork();

	
	
    while(count<=size)
    {
    	
    	if (pid>0)
	{
		fflush(stdin);
		wait(NULL);
		// cout<<"Reading from parent:\n";
	
		read(pipefd[0],&num,sizeof(num));


		if(k%row==0)
    	printf("\n");

		printf("%d ",num);
				k++;

	}

	if(pid==0)
	{
		fflush(stdin);
		// cout<<"writing from child\n";
		num = ((m1[i][j]) * (m2[i][j]));
		write(pipefd[1],&num,sizeof(num));
		j++;
	}
    
    if(count==size)
    	printf("\n");

	count++;

    }


	return 0;
}