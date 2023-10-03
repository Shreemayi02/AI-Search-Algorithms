#include <stdio.h>
#include <stdlib.h>
struct graph
{
	char name;
	struct graph* next;
	int lsize;
	struct graph* opp[5];
	int pos;
	struct graph* list [5];
	int heur;
};
typedef struct graph *node;
node start = NULL;
node goal = NULL;
node createNode(char a)
{
	node temp;
	temp = (node)(malloc(sizeof(struct graph)));
	temp->name = a;
	return temp;
}
int n = 0;
void appendList ()
{
	printf("Enter number of nodes\n");
	scanf ("%d",&n);
	int i = 0;
	node prev = NULL;
	printf("Enter the source first and the destination last\n");
	while(i<n)
	{
		char name;
		printf ("Enter name of node\n");
		scanf (" %c", &name);
		node temp = createNode(name);
		if(prev!=NULL)
		{	
			prev->next = temp;
			prev = temp;
			int h;
			printf("Enter heuristics of node\n");
			scanf("%d", &h);
			temp->heur = h;
		}
		else
		{
			start = temp;
			prev = temp;
		}
		if(i==(n-1))
		goal = temp;
		i++;
	}
	printf("This is a directed graph. For every node mentioned, give the list of nodes it is connected to and the number of nodes it is connected to\n");
	node temp = start;
	while (temp!=NULL)
	{
		printf("How many nodes is %c directed towards?", temp->name);
		scanf ("%d", &temp->lsize);
		for (int i = 0; i<temp->lsize; i++)
		{
			char child;
			printf("Enter node name\n");
			scanf (" %c", &child);
			int flag = 0;
			node find = start;
			while (find!=NULL)
			{
				if(find->name == child)
				{
					temp->list[i] = find;
					find->opp[find->pos] = temp;
					find->pos = find->pos + 1;
					flag = 1;
				}
				find = find->next;
			}
			while (flag==0)
			{
				printf("The node you have specified has not been previously created\n");
				i--;
				break;
			}
		}
		temp = temp->next;
	}
}
void traversal ()
{
	node temp = start;
	while (temp!=NULL)
	{
		if(temp->lsize!=0)
		{
			printf("%c is directed towards ", temp->name);
			for (int i = 0; i<temp->lsize; i++)
			{
				printf("%c ", temp->list[i]->name);
			}
			printf("\n");
		}
		else
		printf("%c is a leaf node\n", temp->name);
		temp = temp->next;
	}
}
void sort ()
{
	node temp = start;
	while (temp!=NULL)
	{
		if(temp->lsize != 1)
		{
			for(int j = 0; j<temp->lsize; j++)
			{
				char small = temp->list[j]->heur;
				int pos = j;
				for (int i = j+1; i<temp->lsize; i++)
				{
					if(temp->list[i]->heur<small)
					{
						small = temp->list[i]->heur;
						pos = i;
					}
					if(temp->heur==small)
					{
						if(temp->list[i]->name < temp->list[pos]->name)
						{
							small = temp->list[i]->heur;
							pos = i;
						}
					}
				}
				node c = temp->list[j];
				temp->list[j] = temp->list[pos];
				temp->list[pos] = c;
			}
		}
		temp = temp->next;
	}
}
char letters[5];
char check[7];
int cnt =0;
int flag = 0;
int position = 0;
void paths (node temp, int i)
{
	if(temp==goal)
	{
		flag = 1;
		for(int z = 0; z<cnt; z++)
		{
			printf("%c", check[z]);
		}
		printf("%c\n", goal->name);
		exit(0);
	}
	else if (temp->lsize == 0)
	{

		return;
	}
	else
	{
		for(int j = 0; j<temp->lsize; j++)
		{
			check[cnt] = temp->name;
			cnt++;
			node inter = temp->list[j];
			int x = 0;
			for(int z = 0; z<cnt; z++)
			{
				if(check[z]==(inter->name))
				{
					cnt--;
					x = 1;
					break;
				}
			}
			if(x==1)
			continue;
			paths(inter, i+1);
			cnt--;
		}
	
	}
}
void main ()
{
	appendList();
	printf("The information entered can be depicted by the graph containing the following relationships\n");
	sort();
	traversal();
	printf("The path obtained using Hill Climbing is :\n");
	paths(start, 1);
}
