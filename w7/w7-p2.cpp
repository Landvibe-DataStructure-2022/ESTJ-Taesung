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
        cout << n->elem << " ";
    }

};
const int MAXN=100;
int depth[MAXN];
int value[MAXN];
int main() {
    int T;
    cin >> T;
    while(T--) {
        Tree t;
        int m;
        cin >> m;
        for (int i = 0; i < m; i++) {
            cin >> value[i];
        }
        for (int i = 0; i < m; i++) {
            cin >> depth[i];
        }
        Node* curPtr=t.root;
        t.root->elem = value[0];
        int curDepth = depth[0];
        //value, depth 순서대로 읽으면서 깊이의 변화에 따라 처리해주면됨
        for (int i = 1; i < m; ++i) {
            Node *child = new Node(value[i]);
            if (curDepth < depth[i]) {//무조건 1차이
                curPtr->appendChild(child);
                curPtr=child;
                curDepth++;
            } else if (curDepth == depth[i]) {//형제노드 추가
                curPtr->parent->appendChild(child);
                curPtr=child;
            }else{//그려보면 value[i] 자리는 depth[i]-1까지 올라간다음에 그 노드의 자식으로 추가해주면됨
                while (curDepth >= depth[i]) {
                    curDepth--;
                    curPtr = curPtr->parent;
                }
                curPtr->appendChild(child);
                curPtr=child;
                curDepth++;
            }
        }
        t.postOrder(t.root);
        cout<<'\n';
    }
    return 0;
}