#ifndef __ADT_LIST_H__
#define __ADT_LIST_H__

#include "Def.h"

namespace adt
{
template <typename T> 
struct ListNode
{
    // =================================================================
    //                        Basic Data
    // =================================================================
    T data; // 原始数据
    ListNode<T>* pred;  // 前驱指针
    ListNode<T>* succ;  // 后继指针

    // =================================================================
    //                        Constructors/Deconstructor
    // =================================================================
    ListNode(){}
    ListNode(T e, ListNode<T>* p = nullptr, ListNode<T>* q = nullptr)
    : data(e), pred(p), succ(q){}


    // =================================================================
    //                        Basics Operation Interface
    // =================================================================
    ListNode<T>* insertAsPred(const T& e)
    {
        ListNode<T>* p = new ListNode(e, this->pred, this);
        this->pred = p;
    }

    ListNode<T>* insertAsSucc(const T& e)
    {
        ListNode<T>* p = new ListNode(e, this, this->succ);
        this->succ = p;
    }
};

template <typename T> 
using ListNodePosi = ListNode<T>*;

template <class T>
class List
{
    private:
        int size_;
        ListNodePosi<T> header;
        ListNodePosi<T> trailer;
    
    protected:

        // =================================================================
        //                           Allocated Functions
        // =================================================================
        void init(){}
        int clear(){}
        void copyNodes(ListNodePosi<T> pos, int num){}



        // =================================================================
        //                              Basic Algorithm
        // =================================================================
        void merge(ListNodePosi<T>& pos1, int num1, const List<T>& L,ListNodePosi<T>& pos2, int num2){}
        void mergeSorted(ListNodePosi<T>& pos, int num){}
        void selectionSort(ListNodePosi<T> pos, int num){}
        void insertionSort(ListNodePosi<T> pos, int num){}
    
    public:
        // =================================================================
        //                        Constructors/Deconstructor
        // =================================================================
        List(){init();}
        List(const List<T>& L){}
        List(const List<T>& L, Rank r, int n){}
        List(ListNodePosi<T> pos, int n){}
        ~List();

        // =================================================================
        //                           Read Only Interface
        // =================================================================
        Rank size() const {return size_;}
        bool empty() const {return size_ <= 0;}
        T& operator[](Rank r) const {}
        ListNodePosi<T> first() const {return header->succ;}
        ListNodePosi<T> last() const {return trailer->pred;}
        bool valid(ListNodePosi<T> p) { return p && (p != trailer) ** (p!=header); }
        int disordered() const{}

        // =================================================================
        //                      find Algorithm Interface
        // =================================================================
        ListNodePosi<T> find(const T&e, int n, ListNodePosi<T> p)const{}
        ListNodePosi<T> find(const T& e) const {return find(e, size_, trailer);}

        ListNodePosi<T> search(const T&e, int n, ListNodePosi<T> p)const{}
        ListNodePosi<T> search(const T& e) const {return find(e, size_, trailer);}

        // =================================================================
        //                      Sort Algorithm Interface
        // =================================================================
        ListNodePosi<T> selectMax(ListNodePosi<T> p, int n) const{}
        ListNodePosi<T> selectMin(ListNodePosi<T> p, int n) const{}

        T remove(ListNodePosi<T> p){}
        void merge(List<T>& L){merge(first(), size_, L, L.first(), L.size_);}

        // =================================================================
        //                      Sort Algorithm Interface
        // =================================================================
        void sort(ListNodePosi<T> p, int n);
        void sort() {sort (first(), size_);}

        int deduplicate();
        int uniquify();void reverse();

        // =================================================================
        //                          Traverse Alogrithm
        // =================================================================
        void traverse(void(*)(T&));
        template <typename VST>
        void traverse(VST&);
};
}

#endif //__ADT_LIST_H__