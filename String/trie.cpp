struct node {
    bool endmark;
    node* next[28];
    node()
    {
        endmark=false;
        for (int i=0;i<26;i++)
            next[i]=NULL;
    }
}* root;
 
void insert(string& str)
{
    node* curr=root;
    for (int i=0;i<str.length();i++) {
        int id=str[i]-'a';
        if (curr->next[id]==NULL)    curr->next[id]=new node();
        curr=curr->next[id];
    }
    curr->endmark=1;
}
 
bool search(string& str)
{
    node* curr=root;
    for (int i=0;i<str.length();i++) {
        int id=str[i]-'a';
        if (curr->next[id]==NULL)    return false;
        curr=curr->next[id];
    }
    return curr->endmark;
}