
/-------------Undirected Graph----------------/



#include <iostream>
#include <cstdlib>
using namespace std;
struct graph
{
  int data;
  struct adjlistnode *list_node;
};	
struct adjlistnode
{
  struct adjlist *head;
};
struct adjlist 
{
   int value; 
   struct adjlist *next;
};
struct graph * create_graph(int n)
{
	struct graph *tmp=(struct graph *)malloc(sizeof(struct graph));
	tmp->data=n;
	tmp->list_node=(struct adjlistnode *)malloc(n*sizeof(struct adjlistnode));
	for(int i=0;i<n;i++)
	{
		tmp->list_node[i].head=NULL;
	}
	return tmp;
}
struct adjlist * create_list(int y)
{
	struct adjlist *newnode=(struct adjlist *)malloc(sizeof(struct adjlist));
    newnode->next=NULL;
    newnode->value=y;
	return newnode;
}
void add_edge(struct graph *tmp,int x,int y)
{
   struct adjlist *list=create_list(y);
   list->next=tmp->list_node[x].head;
   tmp->list_node[x].head=list;
   list=create_list(x);
   list->next=tmp->list_node[y].head;
   tmp->list_node[y].head=list;
}
void display_graph(struct graph *tmp)
{
	
	for(int i=0;i<tmp->data;i++)
	{
		struct adjlist *dis=tmp->list_node[i].head;
		cout << "Node " << i << "has edge to ";
		while(dis!=NULL)
		{
			cout << dis->value << " ";
			dis=dis->next;
		}
		cout <<endl;
	}
}
int main()
{
  struct graph *node=NULL;	
  int n,x,y;
  cout << "Number of Vertices" <<endl;
  //cin >> n;
  node=create_graph(5);
  //for(int i=0;i<7;i++)
  //{ cout << "Enter edge " << endl;
  //  cin >> x >>y;
   add_edge(node,1,2);
   add_edge(node,3,5);
   add_edge(node,2,4);
   add_edge(node,4,3);
   add_edge(node,5,1);	
  //}
  display_graph(node);
 return 0;
}
