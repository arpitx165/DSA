#include <iostream>
#include <queue>
#include <cstdlib>
#include <stack>
#include <map>
using namespace std;
struct node
{
  int data;
  struct node *left;
  struct node *right;
};
//
struct node *insert(struct node *root,int val) /*simple insertion method */
{                                                       /*Inserting each level completely then moving to next level for insertion*/
   if(root==NULL)
    {
      root=(struct node *)malloc(sizeof(struct node));
      root->data=val;
      root->left=NULL;
      root->right=NULL;
      return root;
    }
   else
   {
     queue < struct node *> bfs;
     bfs.push(root);
     while(!bfs.empty())
     {
       struct node *tmp=bfs.front();
        bfs.pop();
       if(tmp->left==NULL)
        {
          tmp->left=insert(tmp->left,val);
          //bfs.clear();
          return root;
        }
        if(tmp->right==NULL)
        {
          tmp->right=insert(tmp->right,val);
          //bfs.clear();
          return root;
        }
       else
         {
           bfs.push(tmp->left);
           bfs.push(tmp->right);
         }
      }
   }
}
                                                  /*Traversals*/

void inorder(struct node *root)      /*recursive Time Complexity O(n*/
{
  if(root==NULL)
   return ;
  else
  {
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
  }
}
void preorder(struct node *root)     /*recursive Time Complexity O(n*/
{
  if(root==NULL)
   return ;
  else
  {
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
  }
}
void postorder(struct node *root)    /*recursive Time Complexity O(n*/
{
  if(root==NULL)
   return ;
  else
  {
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
  }
}
void inorder_iterative(struct node *root)   /*iterative Time Complexity O(n)*/
{
  if(root==NULL)
    return ;
  stack < struct node *> init;
  while(1)
    {
      if(root!=NULL)
      {
        init.push(root);
        root=root->left;
      }
      else
      {
         if(!init.empty())
         {
          cout << init.top()->data << " ";
          root=init.top()->right;
          init.pop();
         }
         else
           break;
      }
    }

}
void preorder_iterative(struct node *root) //iterative/ Time Complexity O(n)
{
   if(root==NULL)
     return ;
   stack < struct node *> preit;
   while(1)
   {
      if(root!=NULL)
      {
        cout << root->data << " ";
        if(root->right!=NULL)
         preit.push(root->right);
        root=root->left;
      }
      else
      {
        if(!preit.empty())
        {
          struct node *tmp=preit.top();
          preit.pop();
          cout << tmp->data << " ";
          if(tmp->right!=NULL)
          {
            preit.push(tmp->right);
          }
          root=tmp->left;
        }
        else
           break;
      }
   }
}
void postorder_iterative(struct node *root)  //iterative Time Complexity O(n)
{
  if(root==NULL)
    return ;
  stack < struct node * > postit;
  while(1)
   {
      if(root!=NULL)
      {
        if(root->right!=NULL)
         postit.push(root->right);
        postit.push(root);
        root=root->left;
      }
      else
      {
        if(!postit.empty())
        {
           struct node *tmp=postit.top(),*tmp1=NULL;
           postit.pop();
           if(!postit.empty()&&tmp->right==postit.top())
           {
             tmp1=postit.top();
             postit.pop();
             postit.push(tmp);
             root=tmp1;
           }
          else
           cout << tmp->data << " ";
        }
        else
          break;
      }
   }
}
void levelorder_traversal(struct node *root)  /*Breath First-search Time Complexity O(n)*/
{
  if(root==NULL)
   return ;
  queue < struct node *>bfs;
  bfs.push(root);
  while(!bfs.empty())
  {
    if(bfs.front()->left!=NULL)
      bfs.push(bfs.front()->left);
    if(bfs.front()->right!=NULL)
      bfs.push(bfs.front()->right);
      cout << bfs.front()->data << " ";
      bfs.pop();
  }
}
void inorder_without_stack(struct node *root) /*Threaded Binary tree Morris Traversal Time Complexity O(n)*/
{
  while(root!=NULL)
  {
    if(root->left==NULL)
    {
      cout << root->data << " ";
      root=root->right;
    }
    else
    {
      struct node *tmp=root->left; /*inorder predecessor*/
      while(tmp->right!=NULL&&tmp->right!=root)
       tmp=tmp->right;
      if(tmp->right==NULL)
      {
        tmp->right=root;
        root=root->left;
      }
      else
      {
        tmp->right=NULL;
        cout << root->data << " ";
        root=root->right;
      }
    }
  }
}
void width_in_map(map< int,vector <int> > &nodes,struct node *root,int wd) /*finding all width nodes and storing in map */
{
  if(root==NULL)
   return ;
   nodes[wd].push_back(root->data);
   width_in_map(nodes,root->left,wd-1);
   width_in_map(nodes,root->right,wd+1);
}
void vertical_order_traversal(struct node *root) /*vertical order traversal with the help of width and map Time complexity O(n) */
{
  if(root==NULL)
  return ;
  map < int,vector <int> > nodes;
   width_in_map(nodes,root,0);
  map <int,vector <int > > :: iterator it;
  for(it=nodes.begin();it!=nodes.end();it++)
  {
     for(int i=0;i<it->second.size();i++)
     {
       cout << it->second[i] << " ";
     }
     cout << endl;
  }
}
void top_view_map(map< int,int > &nodes,struct node *root,int wd) /*finding all width nodes and storing in map */
{
  if(root==NULL)
   return ;
   if(nodes.find(wd)==nodes.end())
   nodes.insert(make_pair(wd,root->data));
  top_view_map(nodes,root->left,wd-1);
  top_view_map(nodes,root->right,wd+1);
}
void top_view_tree(struct node *root)/*top_view of tree in time complexity O(n)*/
{
  if(root==NULL)
   return ;
   map < int,int > nodes;
   top_view_map(nodes,root,0);
    map < int,int > ::iterator it;
    for(it=nodes.begin();it!=nodes.end();it++)
    {
      cout << "width :" << it->first << " Data : "  <<   it->second << endl;
    }
}
void bottom_view_tree(struct node *root) /*Bottom view of tree in Time Complexity O(n)*/
{
  if(root==NULL)
   return ;
  queue < pair <struct node *,int> > bfs;
  map <int,int> ans;
  map <int,int>::iterator it;
  bfs.push(make_pair(root,0));
  while(!bfs.empty())
  {
    struct node *tmp=bfs.front().first;
    int hd=bfs.front().second;
    bfs.pop();
    if(tmp->left!=NULL)
      bfs.push(make_pair(tmp->left,hd-1));
    if(tmp->right!=NULL)
     bfs.push(make_pair(tmp->right,hd+1));
    if(ans.find(hd)==ans.end())
      ans.insert(make_pair(hd,tmp->data));
    else
      ans[hd]=tmp->data;
  }
  for(it=ans.begin();it!=ans.end();it++)
   cout << "hd : " << it->first << " Value : "<< it->second << endl;

}
void left_boundary(struct node *root)
{
  if(root==NULL)
   return ;
  else
  {

    if(root->left!=NULL)
     {
       cout << root->data << " ";
       left_boundary(root->left);
     }
    else if(root->right!=NULL)
      {
        cout << root->data << " ";
        left_boundary(root->right);
      }
  }
}
void right_boundary(struct node *root)
{
  if(root==NULL)
   return ;
  else
  {

    if(root->right!=NULL)
     {
      right_boundary(root->right);
       cout << root->data << " ";
     }
    else if(root->left!=NULL)
      {
        right_boundary(root->left);
        cout << root->data << " ";
      }
  }
}
void leaf_nodes(struct node *root)
{
  if(root==NULL)
   return ;
  else
  {
     leaf_nodes(root->left);
     if(root->left==NULL&&root->right==NULL)
      cout << root->data << " ";
     leaf_nodes(root->right);

  }
}

void boundary_traversal(struct node *root) /*Boundary traversal in time complexity O(n)*/
{
   if(root==NULL)
     return ;
    cout << root->data << " ";
    left_boundary(root->left);
    leaf_nodes(root->left);
    leaf_nodes(root->right);
    right_boundary(root->right);
}
int main()
{
  struct node *root=NULL;
  int n,val;
  cin >> n; /*number of nodes */
  for(int i=0;i<n;i++)
   {
     cin >> val;
     root=insert(root,val);
   }
  inorder(root);
  cout << endl;
  preorder(root);
  cout << endl;
  postorder(root);
  cout << endl;
  levelorder_traversal(root);
  cout << endl;
  vertical_order_traversal(root);
  cout << endl;
  top_view_tree(root);
  cout << endl;
  bottom_view_tree(root);
  cout << endl;
  boundary_traversal(root);
  cout << endl;
return 0;
}
