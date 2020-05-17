#ifndef __ADT_VECTOR_H__
#define __ADT_VECTOR_H__
#include "Def.h"
#include "Fib.h"
namespace adt
{
#define DEFAULT_CAPACITY 3

template <class T>
class Vector
{
   protected:
    Rank size_     = 0;
    int  capacity_ = 0;
    T*   elem_     = nullptr;


    // =================================================================
    //                           Allocated Functions
    // =================================================================
    // copy array A from lo to hi
    void copyFrom(T const* A, Rank lo, Rank hi)
    {
        if (elem_ != nullptr)
            delete[] elem_;
        elem_ = new T[capacity_ = 2 * (hi - lo)];
        size_ = 0;
        while (lo < hi)
            elem_[size_++] = A[lo++];
    }

    // expanding capacity when capacity is not enough
    // normally, expanding twice capacity then old one
    void expand()
    {
        if (size_ < capacity_)
            return;

        if (capacity_ < DEFAULT_CAPACITY)
            capacity_ = DEFAULT_CAPACITY;

        T* old_elem = elem_;
        elem_       = new T[capacity_ << 1];
        for (int i = 0; i < size_; i++)
            elem_[i] = old_elem[i];

        delete[] old_elem;
    }

    // shrink, the inversion of expand
    void shrink()
    {
        // if capacity_ is smaller than DEFAULT_CAPACITY
        // it's not nessesary to shrink
        if (capacity_ < DEFAULT_CAPACITY)
            return;

        // shrinking when current size is less than 25% capacity
        if (size_ << 2 > capacity_)
            return;

        T* old_elem = elem_;
        // shrinking half capacity than old one
        elem_ = new T[capacity_ >> 1];
        for (int i = 0; i < size_; i++)
            elem_[i] = old_elem[i];

        delete[] old_elem;
    }

    void swap(T& e1, T&e2)
    {
        T tmp = e2;
        e2 = e1;
        e1 = tmp;
    }


    // =================================================================
    //                              Basic Algorithm
    // =================================================================
    // 扫描交换
    bool bubble(Rank lo, Rank hi)
    {
        bool sorted = true;
        while(++lo < hi)
        {
            if (elem_[lo - 1] > elem_[lo])
            {
                sorted = false;
                swap(elem_[lo - 1], elem_[lo]);
            }
        }
        return sorted;
    }

    Rank max(Rank lo, Rank hi);           // 选取最大元素
    Rank partition(Rank lo, Rank hi);     // 轴点构造算法

    // 归并算法
    void merge(Rank lo, Rank mi, Rank hi)
    {
        T* A = elem_ + lo;
        int lb = mi - lo;
        T* B = new T[lb];
        for(Rank i = 0; i < lb; B[i] = A[i++]);

        int lc = hi - mi;
        T* C = elem_ + mi;

        for (Rank i = 0, j = 0, k= 0; (j < lb) || (k < lc);)
        {
            if ((j < lb) && (!(k < lc) || (B[j] <= C[k])))
                A[i++] = B[j++];
            if ((k < lc) && (!(j < lb) || (C[k] > B[j])))
                A[i++] = C[k++];
        }

        delete []B;
    }


    // =================================================================
    //                              Inner Sort Algorithm
    // =================================================================

    // 气泡排序算法
    void bubbleSort(Rank lo, Rank hi)
    {
        while(!bubble(lo, hi--));
    }

    // 选择排序算法
    void selectSorted(Rank lo, Rank hi)
    {

    }

    // 归并排序算法
    void mergeSort(Rank lo, Rank hi)
    {
        if (hi - lo < 2)
            return;

        int mi = (hi + lo) >> 1;
        mergeSort(lo, mi);
        mergeSort(mi, hi);
        merge(lo, mi, hi);
    }

    void quickSort(Rank lo, Rank hi);     // 快速排序算法
    void heapSort(Rank lo, Rank hi);      // 堆排序

   public:
    // =================================================================
    //                        Constructors/Deconstructor
    // =================================================================
    Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0)
    {
        elem_ = new T[capacity_ = c];
        for (size_ = 0; size_ < s; elem_[size_++] = v)
            ;
    }
    Vector(const T* A, Rank n) { copyFrom(A, 0, n); }
    Vector(const T* A, Rank lo, Rank hi) { copyFrom(A, lo, hi); }
    Vector(const Vector<T>& V) { copyFrom(V.begin(), 0, V.size()); }
    Vector(const Vector<T>& V, Rank lo, Rank hi)
    {
        copyFrom(V.begin(), lo, hi);
    }

    ~Vector()
    {
        if (elem_ != nullptr)
            delete[] elem_;
    }


    // =================================================================
    //                           Read Only Interface
    // =================================================================
    T    front() const { return elem_[0]; }

    // 获取秩为r的元素
    T    get(int r) const { return elem_[r]; }
    int  size() const { return size_; }  // 返回元素总数
    bool empty() const { return !size_; }

    // 判断所有元素是否已按照非降序排列
    int disordered() const
    {
        int n = 0;
        for (int i = 0; i < size_ - 1; i++)
            if (elem_[i] > elem_[i + 1])
                ++n;
        return n;
    }

    // 无序查找
    Rank find(const T& e) const { return find(e, 0, size_); }
    Rank find(const T& e, Rank lo, Rank hi) const 
    {
        while(lo++ < hi)
            if (elem_[lo] == e)
                return lo - 1;

        return -1;
    }

    // 有序查找
    Rank search(const T& e) const
    {
        return (0 >= size_) ? -1 : search(e, 0, size_);
    }

    Rank search(const T& e, Rank lo, Rank hi) const 
    {
        // 二分查找
        // return binSearch(elem_, e, lo, hi);

        // fibonacci查找
        return fibSearch(elem_, e, lo, hi);
    }

    Rank binSearchA(const Vector<T>& elem, const T& e, Rank lo, Rank hi) const 
    {
        while (lo < hi) 
        {
            Rank mi = (lo + hi) >> 1;
            if (elem[mi] == e)
                return mi;
            else if (elem[mi] < e)
                lo = mi + 1;
            else if (elem[mi] > e)
                hi = mi;
        }
        return -1;
    }

    Rank binSearchB(const Vector<T>& elem, const T& e, Rank lo, Rank hi)
    {
        while(hi - lo > 1)
        {
            Rank mi = (lo + hi) >> 1;
            (elem[mi] > e) ? lo = mi : hi = mi;
        }
        return (e == elem[lo]) ? lo : -1;
    }

    Rank binSearchC(const Vector<T>& elem, const T& e, Rank lo, Rank hi)
    {
        while(lo < hi)
        {
            Rank mi = (lo + hi) >> 1;
            elem[mi] > e ? lo = mi + 1 : hi = mi;
        }
        return --lo;
    }

    Rank fibSearch(const Vector<T>& elem, const T& e, Rank lo, Rank hi) const 
    {

    }

    // =================================================================
    //                           Write/Read Interface
    // =================================================================
    T& operator[](Rank r) const
    {
        return elem_[r];
    }

    Vector<T>& operator=(const Vector<T>& V)
    {
        if (elem_ != nullptr)
            delete[] elem_;
        copyFrom(V.begin(), 0, V.size());
        return *this;  // 方便链式复制
    }
    T*   begin() const { return elem_; }

    //用e替换秩为r元素的数值
    void put(int r, const T& e) { elem_[r] = e; }

    int remove(Rank lo, Rank hi)
    {
        if (lo == hi) return 0;
        while (hi < size_)
        {
            elem_[lo++] = elem_[hi++];
        }
        size_ = lo;
        shrink();
        return hi - lo;
    }

    //移除秩为r的元素，返回元素中原存放的对象
    T remove(Rank r)
    {
        T tmp = elem_[r];
        remove(r, r + 1);
        return tmp;
    }

    Rank insert(Rank r, const T& e);  // e作为秩为r元素插入，原后继元素依次后移
    Rank insert(const T& e) { return insert(size_, e); }  // 插入元素到最后

    // =================================================================
    //                      Sort Algorithm Interface
    // =================================================================

    // 局部排序
    void sort(Rank lo, Rank hi)
    {

    }
    void sort() { sort(0, size_); }      // 整体排序
    void unsort(Rank lo, Rank hi);       // 局部置乱
    void unsort() { unsort(0, size_); }  // 整体置乱

    // 无序去重
    int deduplicate()
    {
        int old_size = size_;
        Rank i = 0;
        while (i < size_)
            find(elem_[i], i + 1, size_) < 0 ? ++i : remove(i);
        return old_size - size_;
    }

    // 有序去重
    int uniquify()
    {
        Rank i = 0, j = 0;
        int  old_size = size_;
        // 低效版
        // while (i < size_ - 1)
        //     elem_[i] == elem_[i + 1] ? ++i : remove(i);
        // return old_size - size_;
        // 高效版, 双索引法,直接进行值替换
        while (++j < size_)
            if (elem_[i] != elem_[j])
                elem_[++i] = elem_[j];
        size_ = ++i;
        shrink();
        return j - i;
    }

    // =================================================================
    //                          Traverse Alogrithm
    // =================================================================
    void traverse(void (*)(T&));
    template <typename VST>
    void traverse(VST& visit)
    {
        for(Rank i = 0; i < size_; ++i)
            visit(elem_[i]);
    }
};
}  // namespace adt
#endif  // __AD_VECTOR_H__