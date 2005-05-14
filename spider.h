/*
 * Spider-Arachnid: A plugin for the Video Disk Recorder
 *
 * See the README file for copyright information and how to reach the author.
 *
 * $Id$
 */

#ifndef VDR_SPIDER_H
#define VDR_SPIDER_H

#define USE_TEMPLATES_FROM_STL

#ifdef USE_TEMPLATES_FROM_STL

#include <vector>
#define Array std::vector
#define Vector std::vector

#else // use own templates

/** --- template class Array ----------------------------------------------- **/

template <class T>
class Array
{
protected:
  T* array;
  int count;
public:

  /** Constructor */
  Array(int length)
  {
    array = new T[length];
    count = length;
  }

  /** Destructor */
  ~Array()
  {
    delete[] array;
  }

  /** Reference to an item of the array */
  T& operator[](int p)
  {
    return array[p];
  }

  /** Reference to an item of the array */
  const T& operator[](int p) const
  {
    return array[p];
  }

  /** Length of the array */
  unsigned int size() const
  {
    return count;
  }

  /** Is the array empty? */
  bool empty() const
  {
    return count == 0;
  }
};


/** --- template class Vector ---------------------------------------------- **/

template <class T>
class Vector
{
protected:
  T* vector;
  int max;
  int count;
  int steps;

  /** Resize the vector to the new length */
  void resize(int m)
  {
    if (m < steps)
      m = steps;
    else
      m = ((m - 1) / steps + 1) * steps;
    if (m != max)
    {
      T* v = new T[m];
      for (int i = 0; i < count; ++i)
        v[i] = vector[i];
      delete[] vector;
      vector = v;
      max = m;
    }
  }

public:

  /** Contructor */
  Vector(int stepCount = 10)
  {
    vector = new T[stepCount];
    max = steps = stepCount;
    count = 0;
  }

  /** Destructor */
  ~Vector()
  {
    delete[] vector;
  }

  /** Reference to an item of the vector */
  T& operator[](int p)
  {
    return vector[p];
  }

  /** Reference to an item of the vector */
  const T& operator[](int p) const
  {
    return vector[p];
  }

  /** Reference to an item of the vector */
  T& back()
  {
    return vector[count - 1];
  }

  /** Reference to an item of the vector */
  const T& back() const
  {
    return vector[count - 1];
  }

  /** Current length of the vector */
  unsigned int size() const
  {
    return count;
  }

  /** Is the vector empty? */
  bool empty() const
  {
    return count == 0;
  }

  /** Add an item to the end of the vector */
  void push_back(const T& item)
  {
    resize(count + 1);
    vector[count] = item;
    ++count;
  }

  /** Remove an item from the end of the vector */
  void pop_back()
  {
    if (count > 0)
    {
      --count;
      resize(count);
    }
  }
};
#endif

#endif // VDR_SPIDER_H
