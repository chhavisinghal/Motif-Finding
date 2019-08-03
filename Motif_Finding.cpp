
#include<iostream>
#include<string.h>
#include<bits/stdc++.h>
#define MAX 50
using namespace std;

int maxi = 0;
char ans[7];
int i,j;
int nos[7];
int nmer=7;
//string str[12];
//string strnew[12];
int a[7];
int c[7];
int g[7];
int t[7];
struct node
{
    char data;
    unsigned endofstring: 1;
    int Count;
    struct node *left, *right, *eq;
};

struct node* newnode(char data)
{
    struct node* root = (struct node*) malloc(sizeof( struct node ));
    root->data = data;
    root->endofstring = 0;
    root->Count = 0;
    root->left = root->right = root->eq = NULL;
    return root;
};

void insert(struct node** root, char* word)
{
    if(!(*root))
        *root = newnode(*word);
    if((*root)->data > (*word))
        insert(&((*root)->left), word);
    else if((*root)->data < (*word))
        insert(&((*root)->right), word);
    else
    {
        if(*(word+1))
            insert(&((*root)->eq), word+1);
        else
            (*root)->endofstring = 1;
    }
}

void traverseTSTUtil(struct node* root, char* buffer, int depth)
{
    if (root)
    {
        traverseTSTUtil(root->left, buffer, depth);

        buffer[depth] = root->data;
        if (root->endofstring)
        {
            buffer[depth+1] = '\0';
            cout << buffer << endl;
        }

        traverseTSTUtil(root->eq, buffer, depth + 1);

        traverseTSTUtil(root->right, buffer, depth);
    }
}

void traverseTST(struct node* root)
{
    char buffer[MAX];
    traverseTSTUtil(root, buffer, 0);
}

int searchTST(struct node *root, char *word)
{
    if (!root)
        return 0;

    if (*word < (root)->data)
        return searchTST(root->left, word);

    else if (*word > (root)->data)
        return searchTST(root->right, word);

    else
    {
        while(*(word+1) == '\0')
        {
            root->Count = root->Count + 1;
            return root->endofstring;
        }

        return searchTST(root->eq, word+1);
    }
}

void MtraverseTSTUtil(struct node* root, char* buffer, int depth)
{
    if (root)
    {
        MtraverseTSTUtil(root->left, buffer, depth);

        buffer[depth] = root->data;
        if(root->Count > ::maxi)
        {
            ::maxi = root->Count;
            buffer[depth+1] = '\0';
            for(int h=0;h<7;h++)
            {
                ::ans[h] = *(buffer+h);
            }
        }

        MtraverseTSTUtil(root->eq, buffer, depth + 1);

        MtraverseTSTUtil(root->right, buffer, depth);
    }
}

void MtraverseTST(struct node* root)
{
    char buffer[MAX];
    MtraverseTSTUtil(root, buffer, 0);
}

int maxj(int q,int w,int e,int r)
{
    if((q>=w)&&(q>=e)&&(q>=r))
        return q;
    else if((w>=q)&&(w>=e)&&(w>=r))
        return w;
    else if((e>=w)&&(e>=q)&&(e>=r))
        return e;
    else
     return r;
}

void con(string a1,int i)
{
    if(i==7)
    {
        cout<<a1<<endl;
    }
    else
    {
    if(a[i]==maxj(a[i],c[i],g[i],t[i]))
    {
        a1.push_back('A');
        con(a1,i+1);
        a1= a1.substr(0, a1.size()-1);
    }
    if(c[i]==maxj(a[i],c[i],g[i],t[i]))
    {
        a1.push_back('C');
        con(a1,i+1);
        a1= a1.substr(0, a1.size()-1);
    }
    if(t[i]==maxj(a[i],c[i],g[i],t[i]))
    {
        a1.push_back('T');
        con(a1,i+1);
        a1= a1.substr(0, a1.size()-1);
    }
    if(g[i]==maxj(a[i],c[i],g[i],t[i]))
    {
        a1.push_back('G');
        con(a1,i+1);
        a1= a1.substr(0, a1.size()-1);
    }
    }
}

int main()
{
    struct node* root = NULL;
    string word[7];
    string worknew[7];
    int i,j,k = 0;
    cout << "ENTER DNA STRUCTURE\n";
    for(i=0;i<7;i++)
        cin >> word[i];
    for(i=0;i<34;i++)
    {
        string a;
        a = word[0].substr(i,7);

        cout << a << "\n";
        char* ch;
        ch = (char *)malloc(sizeof(char)*7);
        for(j=0;j<7;j++)
        {
            *(ch+j) = a[j];
            cout << *(ch+j) << "\t";
        }
        insert(&root, ch);
        cout << "\n";
    }

    cout << "\nTotal Lmers In a Tree" << endl;
    traverseTST(root);
    cout << "\n";

    for(i=1;i<7;i++)
    {
        for(j=0;j<34;j++)
        {
            string b;
            b = word[i].substr(j,7);

            cout << b << "\n";
            char* ch1;
            ch1 = (char *)malloc(sizeof(char)*7);
            for(k=0;k<7;k++)
            {
                *(ch1+k) = b[k];
                cout << *(ch1+k) << "\t";
            }
            cout << "\n";
            searchTST(root, ch1)? printf("Found\n"): printf("Not Found\n");
        }
        cout << "\n\n";
    }
    cout << "\n\n";
    MtraverseTST(root);
    if((maxi+1) == 7)
    {
        cout << "The Lmer with maximum count\n";
        cout << "Our Motif---------";
        cout << ::ans << endl;
        cout << "Count value of Motif---";
        cout << ::maxi+1 << endl;
    }
    else
    {
        string wordnew[7];
        for(i=0;i<nmer;i++)
        {
            a[i]=c[i]=g[i]=t[i]=0;
        }

        cout<<"ENTRE THE SEQUENCE SET";
        for(i=0;i<7;i++)
        {
            cin>>nos[i];
        }

        for(i=0;i<12;i++)
        {
            wordnew[i] = word[i].substr(nos[i],nmer);
            cout << wordnew[i] << endl;
        }

        for(i=0;i<12;i++)
        {
            for(j=0;j<nmer;j++)
            {
                char ch=wordnew[i][j];
                if(ch=='T')
                {
                    t[j]++;
                }
                else if(ch=='A')
                {
                    a[j]++;
                }
                else if(ch=='G')
                {
                    g[j]++;
                }
                else if(ch=='C')
                {
                    c[j]++;
                }
            }
        }

        for(i=0;i<12;i++)
        {
            cout<<wordnew[i]<<endl;
        }

        for(i=0;i<nmer;i++)
        {
            cout<<a[i]<<" ";
        }
        cout<<endl;
        for(i=0;i<nmer;i++)
        {
            cout<<c[i]<<" ";
        }
        cout<<endl;
        for(i=0;i<nmer;i++)
        {
            cout<<g[i]<<" ";
        }
        cout<<endl;
        for(i=0;i<nmer;i++)
        {
            cout<<t[i]<<" ";
        }
        cout<<endl;
        con("",0);
    }
    return 0;
}



