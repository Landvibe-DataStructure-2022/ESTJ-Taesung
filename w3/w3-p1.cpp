//
// Created by 윤태성 on 2022/03/16.
//
#include <iostream>
using namespace std;

class stack{
private:
    int size=0;
    int MAX_SIZE=0;
    int arr[10]={};
public:
    stack(int s){
        MAX_SIZE=s;
    }
    bool empty(){
        return size==0;
    }
    int top(){
        if(empty()) return -1;
        return arr[size-1];
    }
    void push(int x){
        if(size>=MAX_SIZE){
            cout<<"FULL\n";
            return;
        }
        arr[size++]=x;
    }
    void pop(){
        if(size==0){
            cout<<-1<<'\n';
            return;
        }
        cout<<top()<<'\n';
        size--;
    }
};

int main(){
    int t,n;
    cin>>t>>n;
    string init;
    stack s(t);
    while(n--){
        cin>>init;
        if(init=="empty"){
            cout<<s.empty()<<'\n';
        }
        else if(init=="top"){
            cout<<s.top()<<'\n';
        }
        else if(init=="pop"){
            s.pop();
        }
        else{
            int x;
            cin>>x;
            s.push(x);
        }
    }
}