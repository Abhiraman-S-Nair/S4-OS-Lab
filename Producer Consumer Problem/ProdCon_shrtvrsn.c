#include<stdio.h>
#define BUFFER_SIZE 10
int main()
{
	char buffer[BUFFER_SIZE];
	int top=-1, ch=1;
	while (ch==1)
	{
		int ch2;
		printf("Press 1 to add, 2 to consume and 3 to display ");
		scanf("%i",&ch2);
		if (ch2==1)
		{
			int l;
			puts("How many items to be added by the producer? ");
			printf("There are %i free buffer spaces left ",BUFFER_SIZE-(top+1));
			scanf("%i",&l);
			if (l>BUFFER_SIZE||l>BUFFER_SIZE-(top+1))
			{
				puts("No of elements greater than the buffer size ");
				continue;
			}
			for (int i=0;i<l;i++)
			{
				if (top==BUFFER_SIZE-1)
				{
					puts("Process stack is full ");
					continue;
				}
				char data;
				puts("Enter the data ");
				scanf("%s",&data);
				top++;
				buffer[top]=data;
			}
		}
		else if (ch2==2)
		{
			puts("How many processes u want to consume? ");
			printf("There are only %i processes left ",top+1);
			int li;
			scanf("%i",&li);
			if (li>BUFFER_SIZE||li>top+1)
			{
				puts("Size underflow ");
				continue;
			}

			for (int i=0;i<li;i++)
			{
				if (top==-1)
				{
					puts("Process stack is empty ");
					continue;
				}
				top--;
			}

		}
		else if (ch2==3)
		{
			for (int i=0;i<=top;i++)
			{
				printf("%c\n",buffer[i]);
			}
		}
		else
		{
			puts("invalid");
		}
		puts("Press 1 to continue ");
		scanf("%i",&ch);
	}
}
