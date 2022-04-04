#include<iostream>
#include<vector>
#include<math.h>
#include<conio.h>
#include<string.h>
using namespace std;




int hashing(int x,int d)
{
    int y,p;
    p=pow(2,d);
    y=x%p;
    return y;
}

void swap(int *a,int *b)
{
    char temp = *a;
    *a=*b;
    *b=temp;

}

vector<int> binaryconverter(int a,int k)
{
    int b,c=1;
    vector<int> d;
    b=hashing(a,k);
    if (b==0)
    {
        d.push_back(0);
    }
    else{
    while(c==1)
    {
        d.push_back(b%2);
        b=b/2;
        if(b==1)
        {
            d.push_back(1);
            break;
        }
    }}
    return d;
}

vector<int> finalbinary(int a,int k)
{
    vector<int> d = binaryconverter(a,k);
    int i = d.size();
    for(int j=0;j<=i/2;j++)
    {
        if (j==(i-1-j))
        {
            break;
        }
        if (j>(i-1-j))
        {
            break;
        }
        swap(&d.at(j),&d.at(i-1-j));
    }
    if (d.size()!=k)
        {
            while(1)
            {
                d.insert(d.begin(),0);
                if (d.size()==k)
                {
                    break;
                }
                
            }
        }
    return d;
}

typedef struct
{
    vector<int> elements;
    int capacity;
    int ld;

}bucket;


vector<bucket*> initialization(int a,int b)
{
    int p=pow(2,a);
    vector<bucket*> D;
    D.resize(p);
    for(int i=0;i<p;i++)
    {
        bucket* B=new bucket;
        B->ld=a;
        B->capacity=0;
        D[i]=B;
    }
    return D;
}

void directory2(vector<bucket*>& D,int& gd)
{
    int p,q;
    q=pow(2,gd);
    D.resize(p=pow(2,gd+1));

    for(int i=q;i<p;i++)
    {
        D[i]=D[i-q];
    }
    gd++;
}

void split(vector<bucket*>& D,int key,int b,int gd)
{

int p=pow(2,gd-1),q=pow(2,gd),altkey,newkey,position=0;
bucket* B=new bucket;
    B->ld=gd;
    B->capacity=0;
    D[key]->ld=gd;

    if (key<p)
    {
        altkey=key+p;
        D[altkey]=B;

        for(int i=0;i<b;i++)
        {
        newkey=hashing(D[key]->elements[i],gd);
        if (newkey==altkey)
        {
            D[altkey]->elements.push_back(D[key]->elements[position]);
            D[key]->elements.erase(D[key]->elements.begin()+position);
            D[key]->capacity=D[key]->elements.size();
            D[altkey]->capacity=D[altkey]->elements.size();
            break;
        }
        else{
           position++;
        }
    }
    }
    
    if (key>=p)
    {
        altkey=key;
        key=key-p;
        D[altkey]=B;

        for(int i=0;i<b;i++)
        {
        newkey=hashing(D[key]->elements[position],gd);
        if (newkey==altkey)
        {
            D[altkey]->elements.push_back(D[key]->elements[position]);
            D[altkey]->elements.push_back(D[key]->elements[position]);
            D[key]->capacity=D[key]->elements.size();
            D[altkey]->capacity=D[altkey]->elements.size();
            break;
        }
        else{
            position++;

        }
    }
    }
    

}

void insert(int x,int gd,vector<bucket*> D,int b)
{
    int key=hashing(x,gd);
    int p;

    if (D[key]->capacity==b)
    {
        if (gd==D[key]->ld)
        {
            directory2(D,gd);
            insert(x,gd,D,b);
        }
        else
        {
            split(D,key,b,gd);
            insert(x,gd,D,b);
        }
    }
    else
    {
        D[key]->elements.push_back(x);
        D[key]->capacity=D[key]->elements.size();
    }

}

void search(vector<bucket*>& D,int x,int gd)
{
    int key=hashing(x,gd);
    for(int i=0;i<(D[key]->capacity);i++)
    {
        if (x==D[key]->elements[i])
        {
            cout<<"element is present"<<endl;
        }
        cout<<"search complete"<<endl;
    }
}

void delet(vector<bucket*>& D,int x)
{
    int key=hashing(x,gd);
    
}


int main()
{
    
    int b,gd;
    cin>>gd>>b;
    vector<bucket*> D;
    D=initialization(gd,b);
    directory2(D,gd);
    D[1]->capacity=b;
    D[1]->elements.push_back(3);
    D[1]->elements.push_back(5);
   // split(D,1,b,gd);
   insert(1,gd,D,b);
    cout<<D.size()<<"    "<<gd<<"   "<<D[3]->capacity;
    return 0;
}