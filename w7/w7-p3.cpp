//
// Created by 윤태성 on 2022/04/05.
//

#include <iostream>
#include <vector>

using namespace std;

class Node {
public:
    int elem;
    Node* parent;
    vector<Node*> child_list;
    Node(int elem=0){
        this->elem=elem;
    }
    void appendChild(Node* child){
        child_list.push_back(child);
        child->parent=this;
    }
};

class Tree {
public:
    Node* root;
    vector<Node*> node_list;
    Tree() {
        root = new Node();
        root->elem = 1;
        node_list.push_back(root);
    }

    Node* search(int elem) {
        Node* tmp = NULL;
        for (Node* n : node_list) {
            if (n->elem == elem) {
                tmp = n;
                break;
            }
        }
        return tmp;
    }

    void insertNode(int par, int child) {
        Node* parNode = search(par);
        Node* tmp = new Node();
        tmp->elem = child;
        tmp->parent = parNode;
        parNode->child_list.push_back(tmp);
        node_list.push_back(tmp);
    }
    void preOrder(Node* n) {
        cout << n->elem << " ";
        for (Node* child : n->child_list) {
            preOrder(child);
        }
    }
    void postOrder(Node* n) {
        for (Node* child : n->child_list) {
            postOrder(child);
        }
        cout <<(n==root?0: n->parent->elem) << " ";
    }

};
const int MAXN=100;
const int MAXV=100001;
int parNum[MAXN];
int value[MAXN];
Node* nodeList[MAXV];
int main() {
    int T;
    cin >> T;
    while(T--) {
        Tree t;
        int m;
        cin >> m;
        for (int i = 0; i < m; i++) {
            cin >> parNum[i]>> value[i];
        }
        nodeList[1]=t.root;

        //value 가 최대 10만이라 value 로 index 접근해서 처리함
        for (int i = 0; i <m ; ++i) {
            if(value[i]!=1){
                Node *child = new Node(value[i]);
                nodeList[value[i]]=child;
                if (nodeList[parNum[i]] == nullptr) {
                    nodeList[parNum[i]] = new Node(parNum[i]);
                    nodeList[parNum[i]]->appendChild(child);
                }else{
                    nodeList[parNum[i]]->appendChild(child);
                }
            }
        }

        t.postOrder(t.root);
        cout<<'\n';
    }
    return 0;
}