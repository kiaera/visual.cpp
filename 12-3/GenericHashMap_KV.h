/*
GenericHashMap_KV.h
project : GenericHashMap_KV template class를 선언하고 구현한 헤더파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : June 04, 2026
*/

// GENERIC_HASHMAP_KV_H가 선언되어 있지 않은 경우에만 포함하기
#ifndef GENERIC_HASHMAP_KV_H
// GENERIC_HASHMAP_KV_H 매크로 정의하기
#define GENERIC_HASHMAP_KV_H

// hash 함수를 사용하기 위한 헤더파일
#include <functional>

// 출력 형식 제어를 사용하기 위한 헤더파일
#include <iomanip>

// 표준 입출력 사용하기 위한 헤더파일
#include <iostream>

// list 자료구조를 사용하기 위한 헤더파일
#include <list>

// 문자열 자료형을 사용하기 위한 헤더파일
#include <string>

// vector 자료구조를 사용하기 위한 헤더파일
#include <vector>

// Entry_KV class를 사용하기 위한 헤더파일
#include "Entry_KV.h"

// key-value 데이터를 저장하는 GenericHashMap_KV template class 선언하기
template <typename K, typename V>
class GenericHashMap_KV
{
protected:
    // Entry_KV를 저장하는 bucket 자료형 정의하기
    typedef std::list<Entry_KV<K, V>> Bucket;

    // bucket들을 저장하는 bucket array 자료형 정의하기
    typedef std::vector<Bucket> BktArray;

    // bucket array iterator 자료형 정의하기
    typedef typename BktArray::iterator BItor;

    // bucket 안의 Entry_KV iterator 자료형 정의하기
    typedef typename Bucket::iterator EItor;

protected:
    // 저장된 Entry_KV 개수 저장하기
    int num_entry;

    // bucket array 저장하기
    BktArray BA;

    // hash map 이름 저장하기
    std::string name;

public:
    // Iterator class 전방 선언하기
    class Iterator;

public:
    // 생성자
    GenericHashMap_KV(std::string nm, int hashTblSize = 101)
        : num_entry(0), BA(hashTblSize), name(nm)
    {}

    // hash map 이름 반환하기
    std::string getName()
    {
        return name;
    }

    // 저장된 Entry_KV 개수 반환하기
    int size() const
    {
        return num_entry;
    }

    // hash map이 비어 있는지 확인하기
    bool empty() const
    {
        return num_entry == 0;
    }

    // key가 k인 Entry_KV 찾기
    Iterator find(const K& k)
    {
        return _find(k);
    }

    // key와 value 삽입하기
    Iterator insert(const K& k, const V& v)
    {
        // 같은 key가 이미 있는지 확인하기
        Iterator p = _find(k);

        // 같은 key가 있으면 기존 value를 새 value로 교체하기
        if (p != end())
        {
            (*p).setValue(v);
            return p;
        }

        // key에 해당하는 bucket index 계산하기
        int bucketIndex = getBucketIndex(k);

        // 해당 bucket의 끝 위치를 삽입 위치로 설정하기
        Iterator insertPos(BA, BA.begin() + bucketIndex, BA[bucketIndex].end());

        // 새로운 Entry_KV 삽입하기
        return _insert(insertPos, Entry_KV<K, V>(k, v));
    }

    // key가 k인 Entry_KV 삭제하기
    void erase(const K& k)
    {
        // 삭제할 key 찾기
        Iterator p = _find(k);

        // key를 찾은 경우 삭제하기
        if (p != end())
        {
            _erase(p);
        }
    }

    // iterator 위치의 Entry_KV 삭제하기
    void erase(const Iterator& p)
    {
        _erase(p);
    }

    // 첫 번째 Entry_KV 위치 반환하기
    Iterator begin()
    {
        // 비어 있지 않은 첫 번째 bucket 찾기
        for (BItor b = BA.begin(); b != BA.end(); ++b)
        {
            if (!b->empty())
            {
                return Iterator(BA, b, b->begin());
            }
        }

        return end();
    }

    // 마지막 다음 위치 반환하기
    Iterator end()
    {
        return Iterator(BA, BA.end());
    }

    // key가 k인 Entry_KV 찾기 보조 함수
    Iterator _find(const K& k)
    {
        // key에 해당하는 bucket index 계산하기
        int bucketIndex = getBucketIndex(k);

        // 해당 bucket iterator 설정하기
        BItor b = BA.begin() + bucketIndex;

        // 해당 bucket 안에서 key 찾기
        for (EItor e = b->begin(); e != b->end(); ++e)
        {
            if (e->getKey() == k)
            {
                return Iterator(BA, b, e);
            }
        }

        return end();
    }

    // iterator 위치에 Entry_KV 삽입하기 보조 함수
    Iterator _insert(const Iterator& p, const Entry_KV<K, V>& e)
    {
        // 지정된 위치에 Entry_KV 삽입하기
        EItor inserted = p.bkt->insert(p.ent, e);

        // 저장된 Entry_KV 개수 증가시키기
        ++num_entry;

        return Iterator(BA, p.bkt, inserted);
    }

    // iterator 위치의 Entry_KV 삭제하기 보조 함수
    void _erase(const Iterator& p)
    {
        // end 위치이면 삭제하지 않기
        if (p == end())
        {
            return;
        }

        // 현재 bucket에서 Entry_KV 삭제하기
        p.bkt->erase(p.ent);

        // 저장된 Entry_KV 개수 감소시키기
        --num_entry;
    }

    // bucket 안에서 다음 Entry_KV로 이동하기
    static void _next(Iterator& p)
    {
        ++p.ent;
    }

    // 현재 iterator가 bucket 끝인지 확인하기
    static bool endOfBkt(const Iterator& p)
    {
        return p.ent == p.bkt->end();
    }

    // bucket별 Entry_KV 개수 출력하기
    void fprintBucketSizes(std::ostream& fout)
    {
        // 최대 bucket 원소 개수 저장하기
        int max_ent = 0;

        // 최소 bucket 원소 개수 저장하기
        int min_ent = 0;

        // 전체 Entry_KV 개수 저장하기
        int total_ent = 0;

        // bucket array가 비어 있지 않으면 첫 번째 bucket 크기를 최소값으로 설정하기
        if (!BA.empty())
        {
            min_ent = static_cast<int>(BA[0].size());
        }

        // 모든 bucket의 크기 출력하기
        for (int i = 0; i < static_cast<int>(BA.size()); ++i)
        {
            int bucketSize = static_cast<int>(BA[i].size());

            fout << "Bucket[" << std::setw(3) << i << "] : "
                << bucketSize << " entries" << std::endl;

            if (bucketSize > max_ent)
            {
                max_ent = bucketSize;
            }

            if (bucketSize < min_ent)
            {
                min_ent = bucketSize;
            }

            total_ent += bucketSize;
        }

        // bucket당 평균 Entry_KV 개수 계산하기
        double avg = 0.0;

        if (!BA.empty())
        {
            avg = static_cast<double>(total_ent) / BA.size();
        }

        // 최대, 최소, 평균 bucket 크기 출력하기
        fout << "Max_ent (" << std::setw(2) << max_ent
            << "); min_ent (" << std::setw(2) << min_ent
            << "); avg (" << std::fixed << std::setprecision(2) << avg << ")"
            << std::endl;
    }

    // key에 대한 bucket index 계산하기
    int getBucketIndex(const K& k) const
    {
        return static_cast<int>(std::hash<K>{}(k) % BA.size());
    }

public:
    // HashMap에서 사용할 Iterator class 선언하기
    class Iterator
    {
    private:
        // bucket 안의 Entry_KV iterator 저장하기
        EItor ent;

        // bucket array iterator 저장하기
        BItor bkt;

        // bucket array 주소 저장하기
        BktArray* ba;

    public:
        // 기본 생성자
        Iterator()
            : ba(nullptr)
        {}

        // bucket array, bucket iterator, Entry_KV iterator를 초기화하는 생성자
        Iterator(BktArray& a, const BItor& b, const EItor& q = EItor())
            : ent(q), bkt(b), ba(&a)
        {}

        // Entry_KV iterator 반환하기
        EItor& getEntry_KV()
        {
            return ent;
        }

        // bucket iterator 반환하기
        BItor& getBkt()
        {
            return bkt;
        }

        // 현재 위치의 Entry_KV 반환하기
        Entry_KV<K, V>& operator*()
        {
            return *ent;
        }

        // 두 iterator가 같은지 확인하기
        bool operator==(const Iterator& p) const
        {
            if (ba != p.ba)
            {
                return false;
            }

            if (ba == nullptr)
            {
                return true;
            }

            if (bkt == ba->end() && p.bkt == p.ba->end())
            {
                return true;
            }

            return bkt == p.bkt && ent == p.ent;
        }

        // 두 iterator가 다른지 확인하기
        bool operator!=(const Iterator& p) const
        {
            return !(*this == p);
        }

        // 다음 Entry_KV로 이동하기
        Iterator& operator++()
        {
            if (ba == nullptr || bkt == ba->end())
            {
                return *this;
            }

            // 현재 bucket 안에서 다음 Entry_KV로 이동하기
            ++ent;

            // 아직 현재 bucket 안에 Entry_KV가 남아 있으면 그대로 반환하기
            if (ent != bkt->end())
            {
                return *this;
            }

            // 다음 bucket으로 이동하기
            ++bkt;

            // 비어 있는 bucket은 건너뛰기
            while (bkt != ba->end() && bkt->empty())
            {
                ++bkt;
            }

            // 비어 있지 않은 다음 bucket을 찾으면 그 bucket의 첫 Entry_KV로 이동하기
            if (bkt != ba->end())
            {
                ent = bkt->begin();
            }

            return *this;
        }

        // GenericHashMap_KV에서 Iterator의 private 멤버에 접근할 수 있게 하기
        friend class GenericHashMap_KV;
    };
};

#endif