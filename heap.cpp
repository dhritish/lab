#include<bits/stdc++.h>
using namespace std;

class Page{
    public:
        int size;
        int count;
        Page *prev; 
        Page *next; 
        int free_space;
        vector<int> data;

        Page(int s){
            size = s-16;
            count=0;
            prev = nullptr;
            next = nullptr;
            free_space = s-16;
        }

        bool has_free_space(int s){
            return free_space >= s+4;
        }

        void insert(int s,int pk){
            data.push_back(pk);
            free_space =free_space- s-4;
            count++;
        }
};

class HeapFile{
    public:
        Page *root;
        int pageSize;

        HeapFile(int s){
            root = nullptr;
            pageSize = s;
        }

        void insert(int s,int pk){
            if(root == nullptr){
                root = new Page(pageSize);
                root->insert(s,pk);
                return;
            }
            Page *curr;
            curr = root;
            while(curr != nullptr){
                if(curr->has_free_space(s)){
                    curr->insert(s,pk);
                    return;
                }
                if(curr->next == nullptr){
                    curr->next = new Page(pageSize);
                    curr->next->prev = curr;
                    curr->next->insert(s,pk);
                    return;
                }
                curr = curr->next;
            }
        }

        void search(int pk){
            int page_id=0;
            Page *curr;
            curr = root;
            while(curr != nullptr){
                for (int i = 0; i < curr->data.size(); i++){
                    if(curr->data[i]==pk){
                        cout<<page_id<<" "<<i<<"\n";
                        return;
                    }
                }
                curr = curr->next;
                page_id++;
            }
            cout<<"-1 -1\n";
        }

        void status(){
            int page_id=0;
            Page *curr;
            curr = root;
            while(curr != nullptr){
                curr = curr->next;
                page_id++;
            }
            curr = root;
            cout<<page_id<<" ";
            while(curr != nullptr){
                cout<<curr->count<<" ";
                curr = curr->next;
            }
            cout<<endl;
        }
};

int main(){
    int s;
    cin>>s;
    HeapFile *h = new HeapFile(s);
    int n,size,key;
    while (cin >> n) {
        if (n == 1) {
            cin >> size >> key;
            h->insert(size,key);
        } else if (n == 2) {
            h->status();
        } else if (n == 3) {
            cin >> key;
            h->search(key);
        } else {
            return 0;
        }
    }
    return 0;
}