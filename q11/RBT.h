/*
RBT.h
project : Red Black Tree template class를 선언하고 구현한 헤더파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 29, 2026
*/

// RBT_H가 선언되어 있지 않은 경우에만 포함하기
#ifndef RBT_H

// RBT_H 매크로 정의하기
#define RBT_H

// 표준 입출력 사용하기 위한 헤더파일
#include <iostream>

// 문자열 자료형을 사용하기 위한 헤더파일
#include <string>

// less 비교 함수를 사용하기 위한 헤더파일
#include <functional>

// std에 포함된 모든 식별자들을 사용할 수 있게 선언하기
using namespace std;

template <typename T, typename Compare = std::less<T>>
class RBTree {
private:
    enum Color { RED, BLACK };

    // 노드 구조체 구현하기
    struct Node {
        T data;
        Color color;
        Node* parent;
        Node* left;
        Node* right;

        // 생성자
        Node() : color(BLACK), parent(nullptr), left(nullptr), right(nullptr) {}
        Node(T val) : data(val), color(RED), parent(nullptr), left(nullptr), right(nullptr) {}
    };

    // RBT의 루트노드
    Node* root; 

    // 리프노드
    Node* nil;  
    Compare comp;

public:
    // 생성자 
    RBTree() : comp(Compare()) {
        nil = new Node();
        nil->color = BLACK;
        root = nil;
    }

    // 소멸자 
    ~RBTree() {
        clear(root);
        delete nil;
    }

    Node* getRoot() const {
        return root;
    }

    // 전체 트리 구조 출력하기
    void printRBT() const {
        _printRBT(root, 0);
    }

    // 중위 순회 출력하기
    void inorderPrint() const {
        inorderPrint(root);
        std::cout << std::endl;
    }

    RBTree(const RBTree&) = delete;
    RBTree& operator=(const RBTree&) = delete;

    // 중위 순회 재귀 구현하기
    void inorderPrint(Node* node) const {
        if (node != nil) {
            inorderPrint(node->left);
            std::cout << node->data << " ";
            inorderPrint(node->right);
        }
    }

    // 노드 이식 구현하기
    void transplant(Node* u, Node* v) {
        if (u->parent == nil) {
            root = v;
        }
        else if (u == u->parent->left) {
            u->parent->left = v;
        }
        else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    // 삽입 구현
    void insert(const T& key) {
        Node* z = new Node(key);
        Node* y = nil;
        Node* x = root;

        while (x != nil) {
            y = x;
            if (comp(z->data, x->data)) {
                x = x->left;
            }
            else {
                x = x->right;
            }
        }

        z->parent = y;
        if (y == nil) {
            root = z;
        }
        else if (comp(z->data, y->data)) {
            y->left = z;
        }
        else {
            y->right = z;
        }

        z->left = nil;
        z->right = nil;
        z->color = RED;

        _insertFixup(z);
    }

    // 삭제 구현하기
    void erase(const T& key) {
        Node* z = findNode(key);

        // 키를 찾지 못한 경우
        if (z == nil) return; 

        Node* y = z;
        Node* x;
        Color y_original_color = y->color;

        if (z->left == nil) {
            x = z->right;
            transplant(z, z->right);
        }
        else if (z->right == nil) {
            x = z->left;
            transplant(z, z->left);
        }
        else {
            y = _treeMinimum(z->right);
            y_original_color = y->color;
            x = y->right;

            if (y->parent == z) {
                x->parent = y;
            }
            else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;

        if (y_original_color == BLACK) {
            _deleteFixup(x);
        }
    }

private:
    // 메모리 해제 재귀 구현하기
    void clear(Node* node) {
        if (node != nil) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    // 키 동등성 검사 구현하기
    bool equalKey(const T& a, const T& b) const {
        return !comp(a, b) && !comp(b, a);
    }

    // 노드 탐색 구현하기
    Node* findNode(const T& key) const {
        Node* current = root;
        while (current != nil && !equalKey(key, current->data)) {
            if (comp(key, current->data)) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }
        return current;
    }

    // 트리 출력 재귀 구현 하기
    void _printRBT(Node* node, int depth) const {
        if (node == nil) return;

        _printRBT(node->right, depth + 1);

        for (int i = 0; i < depth; i++) {
            std::cout << "\t"; 
        }
        std::cout << node->data << " (" << (node->color == RED ? "R" : "B") << ")" << std::endl;

        _printRBT(node->left, depth + 1);
    }

    // 좌회전 구현하기
    void _rotateLeft(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != nil) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nil) {
            root = y;
        }
        else if (x == x->parent->left) {
            x->parent->left = y;
        }
        else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    // 우회전 구현하기
    void _rotateRight(Node* y) {
        Node* x = y->left;
        y->left = x->right;
        if (x->right != nil) {
            x->right->parent = y;
        }
        x->parent = y->parent;
        if (y->parent == nil) {
            root = x;
        }
        else if (y == y->parent->right) {
            y->parent->right = x;
        }
        else {
            y->parent->left = x;
        }
        x->right = y;
        y->parent = x;
    }

    // 삽입 후 균형 유지하기
    void _insertFixup(Node* z) {
        while (z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                // 삼촌 노드
                Node* y = z->parent->parent->right; 
                if (y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        _rotateLeft(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    _rotateRight(z->parent->parent);
                }
            }
            else {
                // 삼촌 노드
                Node* y = z->parent->parent->left; 
                if (y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        _rotateRight(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    _rotateLeft(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    // 서브트리에서 최솟값 찾기
    Node* _treeMinimum(Node* node) const {
        while (node->left != nil) {
            node = node->left;
        }
        return node;
    }

    // 삭제 후 균형 유지하기
    void _deleteFixup(Node* x) {
        while (x != root && x->color == BLACK) {
            if (x == x->parent->left) {
                Node* w = x->parent->right;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    _rotateLeft(x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == BLACK && w->right->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                }
                else {
                    if (w->right->color == BLACK) {
                        w->left->color = BLACK;
                        w->color = RED;
                        _rotateRight(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    _rotateLeft(x->parent);
                    x = root;
                }
            }
            else {
                Node* w = x->parent->left;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    _rotateRight(x->parent);
                    w = x->parent->left;
                }
                if (w->right->color == BLACK && w->left->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                }
                else {
                    if (w->left->color == BLACK) {
                        w->right->color = BLACK;
                        w->color = RED;
                        _rotateLeft(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    _rotateRight(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }
};

#endif



