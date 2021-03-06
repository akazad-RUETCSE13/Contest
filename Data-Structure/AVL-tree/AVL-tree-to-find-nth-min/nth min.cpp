#include<stdio.h>
#include<stdlib.h>
#include<iostream>
 using namespace std;

// An AVL tree node
struct node
{
    int key;
    int l;
    int r;
    struct node *left;
    struct node *right;
    int height;
};

// A utility function to get maximum of two integers
int max(int a, int b);

// A utility function to get height of the tree
int height(struct node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}


// A utility function to get maximum of two integers
int max(int a, int b)
{
    return (a > b)? a : b;
}

/* Helper function that allocates a new node with the given key and
    NULL left and right pointers. */
struct node* newNode(int key)
{
    struct node* node = (struct node*)malloc(sizeof(struct node));
    node->key   = key;
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1; // new node is initially added at leaf
    node->l = 0;
    node->r =0;
    return(node);
}

// A utility function to right rotate subtree rooted with y
// See the diagram given above.
struct node *rightRotate(struct node *y)
{
    struct node *x = y->left;
    struct node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    if(T2!=NULL)
        y->l = (T2->l+T2->r)+1;
    else if(T2==NULL)
        y->l = 0;
    x->r = (y->l + y->r)+1;



    // Update heights
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;

    // Return new root
    return x;
}

// A utility function to left rotate subtree rooted with x
// See the diagram given above.
struct node *leftRotate(struct node *x)
{
    struct node *y = x->right;
    struct node *T2 = y->left;


    // Perform rotation
    y->left = x;
    x->right = T2;

    //cout<<y->key<<endl;


    if(T2!=NULL)
        x->r = (T2->l+T2->r)+1;
    else if(T2==NULL)
        x->r=0;
    y->l= (x->l+x->r)+1;
    //  Update heights
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;

    // Return new root
    return y;
}

// Get Balance factor of node N
int getBalance(struct node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

struct node* insert(struct node* node, int key)
{
    /* 1.  Perform the normal BST rotation */

    if (node == NULL)
        return(newNode(key));

    else if (key < node->key)
    {
        node->left  = insert(node->left, key);
        node->l = (node->l) +1;
    }
    else
    {
        node->right = insert(node->right, key);
        node->r = (node->r) +1;
    }

    /* 2. Update height of this ancestor node */
    node->height = max(height(node->left), height(node->right)) + 1;


    /* 3. Get the balance factor of this ancestor node to check whether
       this node became unbalanced */
    int balance = getBalance(node);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }



    /* return the (unchanged) node pointer */
    return node;
}

int sarc(struct node* node, int n)
{
    //cout<<node->key<<" "<<node->l<<" "<<n<<endl;
    if(node->l==n-1)
        return node->key;
    else if(node->l>=n)
    {
        sarc(node->left,n);
    }
    else if(node->l<n)
        sarc(node->right,n-node->l-1);
}


/* Drier program to test above function*/
int main()
{
  struct node *root = NULL;

  /* Constructing tree given in the above figure */

  int n,a[100010],b[100010];

  scanf("%d",&n);

  for(int i=0;i<n;i++)
  {
      scanf("%d",&a[i]);
  }
  for(int i=0;i<n;i++)
  {
      scanf("%d",&b[i]);
  }

  for(int i=0;i<n;i++)
  {

     root = insert(root, a[i]);
     printf("%d\n",sarc(root,b[i]));

  }
  return 0;
}

