#include <bits/stdc++.h>
using namespace std;

int maxbitdiff;

struct node
{
    node *child[2];
    node(){
            child[0]=child[1]=NULL;
        }
};

void insert(node *trie, int key)
{   
    for(int i = 31;i>=0;i--){
        int k = 1&(key>>i);
        if(trie->child[k] == NULL)
            trie->child[k]=new node;
        trie = trie->child[k];    
    }
}

void setmaxbitdiff(node *trie, int key)
{   
    for(int i = 31;i>=0;i--){
        int k = 1&(key>>i);
        k ^= 1;
        if(trie->child[k]==NULL)
            k ^= 1;
        maxbitdiff = (maxbitdiff<<1)|k;
        trie = trie->child[k];
    }
}

int main()
{
    int n,q,i;
    cin>>n>>q;
    node *trie = new node;
    for(i=0;i<n;++i) {
        int val;
        cin>>val;
        insert(trie,val);
    }
    
    for(i=0;i<q;i++){
        int num;
        cin>>num;
        maxbitdiff = 0;
        setmaxbitdiff(trie,num);
        cout<<(maxbitdiff^num)<<endl;
    }
    
    return 0;
}
