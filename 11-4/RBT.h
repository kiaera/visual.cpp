/*
RBT.h
project : Red Black Tree template 클래스 선언 및 구현한 헤더파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 28, 2026
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

// Red Black Tree template class 선언하기
template <typename T, typename Compare = std::less<T>>
class RBTree
{
private:
    // 노드 색상 정의하기
    enum Color { RED, BLACK };

    // Red Black Tree의 노드 구조체 선언하기
    struct Node
    {
        // 노드에 저장할 데이터
        T key;

        // 노드 색상 저장하기
        Color color;

        // 부모 노드 주소 저장하기
        Node* parent;

        // 왼쪽 자식 노드 주소 저장하기
        Node* left;

        // 오른쪽 자식 노드 주소 저장하기
        Node* right;

        // 기본 생성자
        Node()
            : key(), color(BLACK), parent(nullptr), left(nullptr), right(nullptr)
        {}

        // 데이터와 nil 노드로 노드 초기화하기
        Node(const T& key, Node* nil)
            : key(key), color(RED), parent(nil), left(nil), right(nil)
        {}
    };

    // 루트 노드 주소 저장하기
    Node* root;

    // nil 리프 노드 주소 저장하기
    Node* nil;

    // 비교 함수 객체 저장하기
    Compare comp;

public:
    // 생성자
    RBTree()
        : comp(Compare())
    {
        nil = new Node();
        nil->color = BLACK;
        nil->parent = nil;
        nil->left = nil;
        nil->right = nil;
        root = nil;
    }

    // 소멸자
    ~RBTree()
    {
        clear(root);
        delete nil;
    }

    // 루트 노드 반환하기
    Node* getRoot() const
    {
        return root;
    }

    // Red Black Tree 구조 출력하기
    void printRBT() const
    {
        if (root == nil)
        {
            return;
        }

        _printRBT(root, 0);
    }

    // 중위 순회 출력하기
    void inorderPrint() const
    {
        inorderPrint(root);
        std::cout << std::endl;
    }

    // 복사 생성자 사용 막기
    RBTree(const RBTree&) = delete;

    // 대입 연산자 사용 막기
    RBTree& operator=(const RBTree&) = delete;

    // 중위 순회로 데이터 출력하기
    void inorderPrint(Node* node) const
    {
        if (node == nil)
        {
            return;
        }

        inorderPrint(node->left);
        std::cout << node->key << " ";
        inorderPrint(node->right);
    }

    // 특정 key가 트리에 있는지 확인하기
    bool contains(const T& key) const
    {
        return findNode(key) != nil;
    }

    // u 위치의 노드를 v 노드로 교체하기
    void transplant(Node* u, Node* v)
    {
        if (u->parent == nil)
        {
            root = v;
        }
        else if (u == u->parent->left)
        {
            u->parent->left = v;
        }
        else
        {
            u->parent->right = v;
        }

        v->parent = u->parent;
    }

    // 서브트리에서 가장 작은 노드 찾기
    Node* treeMinimum(Node* x) const
    {
        while (x->left != nil)
        {
            x = x->left;
        }

        return x;
    }

    // key 삽입하기
    void insert(const T& key)
    {
        Node* z = new Node(key, nil);
        Node* y = nil;
        Node* x = root;

        while (x != nil)
        {
            y = x;

            if (comp(z->key, x->key))
            {
                x = x->left;
            }
            else
            {
                x = x->right;
            }
        }

        z->parent = y;

        if (y == nil)
        {
            root = z;
        }
        else if (comp(z->key, y->key))
        {
            y->left = z;
        }
        else
        {
            y->right = z;
        }

        z->left = nil;
        z->right = nil;
        z->color = RED;

        _insertFixup(z);
    }

    // key 삭제하기
    void erase(const T& key)
    {
        Node* z = findNode(key);

        if (z == nil)
        {
            return;
        }

        eraseNode(z);
    }

private:
    // Red Black Tree 구조를 depth별로 들여쓰기하여 출력하기
    void _printRBT(Node* node, int depth) const
    {
        if (node == nil)
        {
            return;
        }

        _printRBT(node->right, depth + 1);

        for (int i = 0; i < depth; i++)
        {
            std::cout << "    ";
        }

        std::cout << node->key << " ";

        if (node->color == RED)
        {
            std::cout << "(R)";
        }
        else
        {
            std::cout << "(B)";
        }

        std::cout << std::endl;

        _printRBT(node->left, depth + 1);
    }

    // 두 key가 같은지 확인하기
    bool equalKey(const T& a, const T& b) const
    {
        return !comp(a, b) && !comp(b, a);
    }

    // key를 가진 노드 찾기
    Node* findNode(const T& key) const
    {
        Node* current = root;

        while (current != nil)
        {
            if (equalKey(key, current->key))
            {
                return current;
            }
            else if (comp(key, current->key))
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }

        return nil;
    }

    // 전체 노드 삭제하기
    void clear(Node* node)
    {
        if (node == nil)
        {
            return;
        }

        clear(node->left);
        clear(node->right);
        delete node;
    }

    // 왼쪽으로 회전하기
    void _rotateLeft(Node* x)
    {
        Node* y = x->right;

        x->right = y->left;

        if (y->left != nil)
        {
            y->left->parent = x;
        }

        y->parent = x->parent;

        if (x->parent == nil)
        {
            root = y;
        }
        else if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }

        y->left = x;
        x->parent = y;
    }

    // 오른쪽으로 회전하기
    void _rotateRight(Node* y)
    {
        Node* x = y->left;

        y->left = x->right;

        if (x->right != nil)
        {
            x->right->parent = y;
        }

        x->parent = y->parent;

        if (y->parent == nil)
        {
            root = x;
        }
        else if (y == y->parent->right)
        {
            y->parent->right = x;
        }
        else
        {
            y->parent->left = x;
        }

        x->right = y;
        y->parent = x;
    }

    // 삽입 후 Red Black Tree 규칙 복구하기
    void _insertFixup(Node* z)
    {
        while (z->parent->color == RED)
        {
            if (z->parent == z->parent->parent->left)
            {
                Node* y = z->parent->parent->right;

                if (y->color == RED)
                {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->right)
                    {
                        z = z->parent;
                        _rotateLeft(z);
                    }

                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    _rotateRight(z->parent->parent);
                }
            }
            else
            {
                Node* y = z->parent->parent->left;

                if (y->color == RED)
                {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->left)
                    {
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

    // 실제 노드 삭제 처리하기
    void eraseNode(Node* z)
    {
        Node* y = z;
        Node* x;
        Color y_original_color = y->color;

        if (z->left == nil)
        {
            x = z->right;
            transplant(z, z->right);
        }
        else if (z->right == nil)
        {
            x = z->left;
            transplant(z, z->left);
        }
        else
        {
            y = treeMinimum(z->right);
            y_original_color = y->color;
            x = y->right;

            if (y->parent == z)
            {
                x->parent = y;
            }
            else
            {
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

        if (y_original_color == BLACK)
        {
            _eraseFixup(x);
        }
    }

    // 삭제 후 Red Black Tree 규칙 복구하기
    void _eraseFixup(Node* x)
    {
        while (x != root && x->color == BLACK)
        {
            if (x == x->parent->left)
            {
                Node* w = x->parent->right;

                if (w->color == RED)
                {
                    w->color = BLACK;
                    x->parent->color = RED;
                    _rotateLeft(x->parent);
                    w = x->parent->right;
                }

                if (w->left->color == BLACK && w->right->color == BLACK)
                {
                    w->color = RED;
                    x = x->parent;
                }
                else
                {
                    if (w->right->color == BLACK)
                    {
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
            else
            {
                Node* w = x->parent->left;

                if (w->color == RED)
                {
                    w->color = BLACK;
                    x->parent->color = RED;
                    _rotateRight(x->parent);
                    w = x->parent->left;
                }

                if (w->right->color == BLACK && w->left->color == BLACK)
                {
                    w->color = RED;
                    x = x->parent;
                }
                else
                {
                    if (w->left->color == BLACK)
                    {
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
        nil->color = BLACK;
    }
};

#endif