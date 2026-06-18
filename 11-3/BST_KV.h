/*
BST_KV.h
project : Generic Binary Search Tree Key-Value template class를 선언하고 구현한 헤더파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 28, 2026
*/

// BST_KV_H가 선언되어 있지 않은 경우에만 포함하기
#ifndef BST_KV_H
// BST_KV_H 매크로 정의하기
#define BST_KV_H

// 표준 입출력 사용하기 위한 헤더파일
#include <iostream>
// 파일 입출력 사용하기 위한 헤더파일
#include <fstream>
// 문자열 자료형을 사용하기 위한 헤더파일
#include <string>
// vector container를 사용하기 위한 헤더파일
#include <vector>
// BSTN_KV template class를 사용하기 위한 헤더파일
#include "BSTN_KV.h"

// Generic Binary Search Tree Key-Value template class 선언하기
template<typename K, typename V>
class BST_KV
{
public:
    // 생성자
    BST_KV(std::string nm)
        : _root(nullptr), num_entry(0), name(nm)
    {}

    // 소멸자
    ~BST_KV()
    {
        clear(_root);
    }

    // 트리 이름 반환하기
    std::string getName()
    {
        return name;
    }

    // 트리 노드 개수 반환하기
    int size() const
    {
        return num_entry;
    }

    // 트리가 비어 있는지 확인하기
    bool empty() const
    {
        return num_entry == 0;
    }

    // 루트 노드 주소 반환하기
    BSTN_KV<K, V>* getRoot()
    {
        return _root;
    }

    // 루트 노드 주소의 주소 반환하기
    BSTN_KV<K, V>** getRootAddr()
    {
        return &_root;
    }

    // 루트 노드의 value 반환하기
    V& getRootValue()
    {
        return _root->getValue();
    }

    // 지정된 노드 삭제하기
    BSTN_KV<K, V>* eraseBSTN_KV(BSTN_KV<K, V>** pp)
    {
        if (pp == nullptr || *pp == nullptr)
        {
            return nullptr;
        }

        BSTN_KV<K, V>* target = *pp;
        BSTN_KV<K, V>* parent = target->getpPr();
        BSTN_KV<K, V>* replace = nullptr;

        if (target->getpLc() == nullptr)
        {
            replace = target->getpRc();
        }
        else if (target->getpRc() == nullptr)
        {
            replace = target->getpLc();
        }
        else
        {
            BSTN_KV<K, V>* minNode = _minBSTN_KV(target->getpRc());
            target->setKey(minNode->getKey());
            target->setValue(minNode->getValue());

            BSTN_KV<K, V>** minAddr;
            if (minNode->getpPr()->getpLc() == minNode)
            {
                minAddr = minNode->getpPr()->getppLc();
            }
            else
            {
                minAddr = minNode->getpPr()->getppRc();
            }

            return eraseBSTN_KV(minAddr);
        }

        if (replace != nullptr)
        {
            replace->setpPr(parent);
        }

        *pp = replace;
        delete target;
        num_entry--;

        return replace;
    }

    // key 기준으로 정렬 위치에 노드 삽입하기
    void insertInOrder(const K key, const V value)
    {
        _insertInOrder(&_root, nullptr, key, value);
    }

    // key를 가진 노드 검색하기
    BSTN_KV<K, V>* searchBSTN_KV(K k)
    {
        return _searchBSTN_KV(_root, k);
    }

    // key를 가진 노드의 value 검색하기
    V searchBST(K k)
    {
        BSTN_KV<K, V>* pTN = searchBSTN_KV(k);

        if (pTN == nullptr)
        {
            return V();
        }

        return pTN->getValue();
    }

    // 가장 작은 key의 value 반환하기
    V& minEntry()
    {
        BSTN_KV<K, V>* pTN = _minBSTN_KV(_root);
        return pTN->getValue();
    }

    // 가장 큰 key의 value 반환하기
    V& maxEntry()
    {
        BSTN_KV<K, V>* pTN = _maxBSTN_KV(_root);
        return pTN->getValue();
    }

    // depth가 보이도록 트리 구조 출력하기
    void fprint_with_Depth(std::ostream& fout)
    {
        fout << name << " : current size (" << num_entry << ")" << std::endl;

        if (_root == nullptr)
        {
            fout << "BST is Empty now !!" << std::endl;
            return;
        }

        _fprint_with_Depth(_root, fout, 0);
    }

    // 중위 순회로 트리 출력하기
    void fprint_inOrder(std::ostream& fout)
    {
        _fprint_inOrder(_root, fout);
    }

protected:
    // 서브트리에서 가장 큰 key를 가진 노드 찾기
    BSTN_KV<K, V>* _maxBSTN_KV(BSTN_KV<K, V>* subRoot)
    {
        if (subRoot == nullptr)
        {
            return nullptr;
        }

        while (subRoot->getpRc() != nullptr)
        {
            subRoot = subRoot->getpRc();
        }

        return subRoot;
    }

    // 서브트리에서 가장 작은 key를 가진 노드 찾기
    BSTN_KV<K, V>* _minBSTN_KV(BSTN_KV<K, V>* subRoot)
    {
        if (subRoot == nullptr)
        {
            return nullptr;
        }

        while (subRoot->getpLc() != nullptr)
        {
            subRoot = subRoot->getpLc();
        }

        return subRoot;
    }

    // key 기준으로 알맞은 위치에 노드 삽입하기
    BSTN_KV<K, V>* _insertInOrder(BSTN_KV<K, V>** p,
        BSTN_KV<K, V>* parentPos, const K key, const V value)
    {
        if (*p == nullptr)
        {
            BSTN_KV<K, V>* newNode = new BSTN_KV<K, V>(key, value);
            newNode->setpPr(parentPos);
            *p = newNode;
            num_entry++;
            return newNode;
        }

        if (key < (*p)->getKey())
        {
            return _insertInOrder((*p)->getppLc(), *p, key, value);
        }
        else
        {
            return _insertInOrder((*p)->getppRc(), *p, key, value);
        }
    }

    // rebalancing 없이 삽입 함수 호출하기
    BSTN_KV<K, V>* _insertAndRebalance(BSTN_KV<K, V>** ppTN,
        BSTN_KV<K, V>* pPr, const K key, const V value)
    {
        return _insertInOrder(ppTN, pPr, key, value);
    }

    // 중위 순회 결과를 vector에 저장하기
    void _traversal_inOrder(BSTN_KV<K, V>* p, std::vector<V>& array_value)
    {
        if (p == nullptr)
        {
            return;
        }

        _traversal_inOrder(p->getpLc(), array_value);
        array_value.push_back(p->getValue());
        _traversal_inOrder(p->getpRc(), array_value);
    }

    // 전위 순회 결과를 vector에 저장하기
    void _traversal_preOrder(BSTN_KV<K, V>* pos, std::vector<V>& array_value)
    {
        if (pos == nullptr)
        {
            return;
        }

        array_value.push_back(pos->getValue());
        _traversal_preOrder(pos->getpLc(), array_value);
        _traversal_preOrder(pos->getpRc(), array_value);
    }

    // 후위 순회 결과를 vector에 저장하기
    void _traversal_postOrder(BSTN_KV<K, V>* pos, std::vector<V>& array_value)
    {
        if (pos == nullptr)
        {
            return;
        }

        _traversal_postOrder(pos->getpLc(), array_value);
        _traversal_postOrder(pos->getpRc(), array_value);
        array_value.push_back(pos->getValue());
    }

    // key를 가진 노드 검색하기
    BSTN_KV<K, V>* _searchBSTN_KV(BSTN_KV<K, V>* pos, K k)
    {
        if (pos == nullptr)
        {
            return nullptr;
        }

        if (k == pos->getKey())
        {
            return pos;
        }
        else if (k < pos->getKey())
        {
            return _searchBSTN_KV(pos->getpLc(), k);
        }
        else
        {
            return _searchBSTN_KV(pos->getpRc(), k);
        }
    }

    // depth가 보이도록 트리 구조 출력하기
    void _fprint_with_Depth(BSTN_KV<K, V>* pTN, std::ostream& fout, int depth)
    {
        if (pTN == nullptr)
        {
            return;
        }

        _fprint_with_Depth(pTN->getpRc(), fout, depth + 1);

        for (int i = 0; i < depth; i++)
        {
            fout << "    ";
        }

        printValue(fout, pTN->getValue());
        fout << std::endl;

        _fprint_with_Depth(pTN->getpLc(), fout, depth + 1);
    }

    // 중위 순회로 출력하기
    void _fprint_inOrder(BSTN_KV<K, V>* pTN, std::ostream& fout)
    {
        if (pTN == nullptr)
        {
            return;
        }

        _fprint_inOrder(pTN->getpLc(), fout);
        printValue(fout, pTN->getValue());
        fout << std::endl;
        _fprint_inOrder(pTN->getpRc(), fout);
    }

private:
    // 일반 value 출력하기
    template<typename X>
    void printValue(std::ostream& fout, const X& value)
    {
        fout << value;
    }

    // 포인터 value 출력하기
    template<typename X>
    void printValue(std::ostream& fout, X* value)
    {
        if (value == nullptr)
        {
            fout << "NULL";
        }
        else
        {
            fout << *value;
        }
    }

    // 전체 노드 삭제하기
    void clear(BSTN_KV<K, V>* node)
    {
        if (node == nullptr)
        {
            return;
        }

        clear(node->getpLc());
        clear(node->getpRc());
        delete node;
    }

    // 루트 노드 주소 저장하기
    BSTN_KV<K, V>* _root;

    // 트리 노드 개수 저장하기
    int num_entry;

    // 트리 이름 저장하기
    std::string name;
};

#endif