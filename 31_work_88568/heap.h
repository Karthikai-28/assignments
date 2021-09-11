#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <functional>
#include <utility>
#include <algorithm>
#include <stdexcept>
#include <unordered_map>

template <
         typename T,
         typename TComparator = std::equal_to<T>,
         typename PComparator = std::less<double>,
         typename Hasher = std::hash<T> >
class Heap
{
public:
    /// Constructs an m-ary heap. M should be >= 2
    Heap(int m = 2,
         const PComparator& c = PComparator(),
         const Hasher& hash = Hasher(),
         const TComparator& tcomp = TComparator()  );

    /// Destructor as needed
    ~Heap();

    /// Adds an item with the provided priority
    void push(double pri, const T& item);

    /// returns the element at the top of the heap
    ///  max (if max-heap) or min (if min-heap)
    T const & top() const;

    /// Removes the top element
    void pop();

    /// returns true if the heap is empty
    bool empty() const;

    /// decreaseKey reduces the current priority of
    /// item to newpri, moving it up in the heap
    /// as appropriate.
    void decreaseKey(double newpri, const T& item);

    void heapify(unsigned int index); //trickle down; makes sure order is fine
    void trickleUp(int index);

private:
    /// Add whatever helper functions you need below


    // These should be all the data members you need.
    std::vector< std::pair<double, T> > store_;
    int m_;
    PComparator c_;
    std::unordered_map<T, size_t, Hasher, TComparator> keyToLocation_;

};

// Complete
template <typename T, typename TComparator, typename PComparator, typename Hasher >
Heap<T,TComparator,PComparator,Hasher>::Heap(
    int m,
    const PComparator& c,
    const Hasher& hash,
    const TComparator& tcomp ) :

    store_(),
    m_(m),
    c_(c),
    keyToLocation_(100, hash, tcomp)

{

}

// Complete
template <typename T, typename TComparator, typename PComparator, typename Hasher >
Heap<T,TComparator,PComparator,Hasher>::~Heap()
{

}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::push(double priority, const T& item)
{
    // You complete.

    store_.push_back(std::make_pair(priority, item));
    keyToLocation_.insert(std::make_pair(item, store_.size()-1));
    trickleUp(store_.size()-1);
}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::decreaseKey(double priority, const T& item)
{
    // You complete

    int i = keyToLocation_[item];
    store_[i].first = priority;

    trickleUp(i);

}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
T const & Heap<T,TComparator,PComparator,Hasher>::top() const
{
    // Here we use exceptions to handle the case of trying
    // to access the top element of an empty heap
    if(empty()) {
        throw std::logic_error("can't top an empty heap");
    }

    return store_[0].second;

}

/// Removes the top element
template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::pop()
{
    if(empty()) {
        throw std::logic_error("can't pop an empty heap");
    }
    
    store_[0] = store_.back();
    store_.pop_back();

    heapify(0);


}

/// returns true if the heap is empty
template <typename T, typename TComparator, typename PComparator, typename Hasher >
bool Heap<T,TComparator,PComparator,Hasher>::empty() const
{
    return store_.empty();
}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::heapify(unsigned int index)
{

    if(index*m_+1 > store_.size()) {
        keyToLocation_[store_[index].second] = index;
        return;
    }

    else {

        int minChild = m_*index+1; //smaller child

        for(int i = 1; i<=m_; i++) {
            if(m_*index + i < store_.size()) {

                int rChild = m_*index + i;

                if(c_(store_[rChild].first, store_[minChild].first)) {
                    minChild = rChild;
                }
            }
        }

  if (!c_(store_[index].first, store_[minChild].first))
        {
            //swap values if out of place
            std::swap(store_[index], store_[minChild]);

            heapify(minChild);
        }

  }


}


//  promote it up while
// it is less than its parent (can be implemented recursively)
template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::trickleUp(int index)
{
    int parent = (index-1) / m_;

    while(parent>=0 && c_(store_[index].first, store_[parent].first)) {

        std::swap(store_[parent], store_[index]);

        index = parent;
        parent = (index-1)/ m_;
    }

    //update key value
    keyToLocation_[store_[index].second] = index;
}



#endif
