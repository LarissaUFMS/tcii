#ifndef __Collection_h
#define __Collection_h

template <typename T> class Collection;
template <typename T> class Iterator;
template <typename T> class IteratorPtr;

template <typename T>
class Collection
{
public:
  virtual void add(const Collection<T>&) = 0;
  virtual void add(const T&) = 0;
  virtual bool remove(const T&) = 0;
  virtual void clear() = 0;
  virtual bool contains(const T&) const = 0;
  virtual bool isEmpty() const = 0;
  virtual int size() const = 0;
  virtual IteratorPtr<T> iterator() const = 0;

}; // Collection

template <typename T>
class Iterator
{
public:
  virtual bool hasNext() const = 0;
  virtual const T& next() = 0;

}; // Iterator

template <typename T>
class IteratorPtr
{
public:
  // Constructor
  IteratorPtr(Iterator<T>* i)
  {
    iterator = i;
  }

  // Destructor
  ~IteratorPtr()
  {
    delete iterator;
  }

  Iterator<T>* operator ->() const
  {
    return iterator;
  }

private:
  Iterator<T>* iterator;

}; // IteratorPtr

#endif // __Collection_h
