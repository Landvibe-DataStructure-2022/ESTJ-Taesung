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
    void appendChildAtFront(Node* child){
        //push front 더 좋은 방법이 있겠지만 귀찮아서 안함 - O(1) time 이 아닌 O(N)에 수행되고있다 -> 링리로 push front 하면 O(1) 에 가능
        child_list.push_back(nullptr);
        for (int i = child_list.size()-1; i >=1; --i) {
            child_list[i] = child_list[i - 1];
        }
        child_list[0]=child;
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
        //sol1 거꾸로 본다
        cout << n->elem << " ";
        for (int i = n->child_list.size()-1; i >=0; --i) {
            preOrder(n->child_list[i]);
        }

        /**sol2 정석대로 본다
           for (int i = 0; i < n->child_list.size(); ++i) {
            preOrder(n->child_list[i]);
        }
         *
         */

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
        t.root->elem = value[m-1];
        int curDepth = depth[m-1];
        //2번과 유사하지만 순회 순서를 거꾸로 보면서 2번처럼 깊이 따라서 처리해주면됨 - 그려보면앎
        //직접 그려보면 알게됨
        for (int i = m-2; i >=0; --i) {
            Node *child = new Node(value[i]);
            if (curDepth < depth[i]) {
                curPtr->appendChild(child);//sol1 -> 이론상 역순으로 넣고있다 -> 역순으로 넣고 읽을때 역순으로 읽는다
//                curPtr->appendChildAtFront(child);//sol2 -> 정석대로 거꾸로 넣어준다
                curPtr=child;
                curDepth++;
            } else if (curDepth == depth[i]) {
                curPtr->parent->appendChild(child);
//                curPtr->parent->appendChildAtFront(child);
                curPtr=child;
            }else{
                while (curDepth >= depth[i]) {
                    curDepth--;
                    curPtr = curPtr->parent;
                }
                curPtr->appendChild(child);
//                curPtr->appendChildAtFront(child);
                curPtr=child;
                curDepth++;
            }
        }
        t.preOrder(t.root);
        cout<<'\n';
    }
    return 0;
}
