#ifndef __ADT_VECTOR_H__
#define __ADT_VECTOR_H__
namespace adt
{
typedef int Rank;
#define DEFAULT_CAPACITY 3

template <class T>
class Vector
{
   protected:
    Rank size_;
    int  capacity_;
    T*   elem_;

    void copyFrom(T const* A, Rank lo, Rank hi);  // 复制数组区间A[lo, hi)
    void expand();                                // 空间不足时扩容
    void shrink();                                // 装填因子过小时压缩
    bool bubble(Rank lo, Rank hi);                // 扫描交换
    void bubbleSort(Rank lo, Rank hi);            // 气泡排序算法
    Rank max(Rank lo, Rank hi);                   // 选取最大元素
    void selectSorted(Rank lo, Rank hi);          // 选择排序算法
    void merge(Rank lo, Rank hi);                 // 归并算法
    void mergeSort(Rank lo, Rank hi);             // 归并排序算法
    Rank partition(Rank lo, Rank hi);             // 轴点构造算法
    void quickSort(Rank lo, Rank hi);             // 快速排序算法
    void heapSort(Rank lo, Rank hi);              // 堆排序

   public:
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

    ~Vector() { delete[] elem_; }

    // 只读接口
    T    front() const { return elem_[0]; }
    T    get(int r) const;        // 获取秩为r的元素
    int  size() const { return size_; }  // 返回元素总数
    bool empty() const { return !size_; }
    int disordered() const;  // 判断所有元素是否已按照非降序排列

    Rank find(const T& e) const { return find(e, 0, size_); }
    Rank find(const T& e, Rank lo, Rank hi) const { return find(e, lo, hi); }

    Rank search(const T& e) const
    {
        return (0 >= size_) ? -1 : search(e, 0, size_);
    }
    Rank search(const T& e, Rank lo, Rank hi) const;

    // 可写接口
    T&         operator[](Rank r) const;
    Vector<T>& operator=(Vector<T> const&);
    T*   begin() const { return &elem_[0]; }
    void put(int r, const T& e);  //用e替换秩为r元素的数值

    T remove(Rank r);  //移除秩为r的元素，返回元素中原存放的对象
    int remove(Rank lo, Rank hi);

    Rank insert(Rank r, const T& e);  // e作为秩为r元素插入，原后继元素依次后移
    Rank insert(const T& e) { return insert(size_, e); } // 插入元素到最后

    void sort(Rank lo, Rank hi);         // 局部排序
    void sort() { sort(0, size_); }      // 整体排序
    void unsort(Rank lo, Rank hi);       // 局部置乱
    void unsort() { unsort(0, size_); }  // 整体置乱
    void deduplicate();  // 无序去重
    void uniquify();     // 有序去重

    // 遍历
    void traverse(void (*)(T&));
    template <typename VST>
    void traverse(VST&);
};
}  // namespace adt
#endif  // __AD_VECTOR_H__