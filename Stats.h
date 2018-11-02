#ifndef _STATS_H_
#define _STATS_H_

#include <iostream>
#include <algorithm>

template <typename T> double mean(T*, int);
template <typename T> double median(T*, int);
template <typename T> T max(T*, int);
template <typename T> int numOver(T*, int, T);

template <typename T> double mean(T* data, int size) {
  // Returns the mean value from an array of specified size, cast to a double
  T tot = 0;
  for (int i=0; i<size; ++i) {
    tot += data[i];
  }
  return (double)tot/size;
}

template <typename T> double median(T* data, int size) {
  // Returns the median value from an array of specified size, cast to a double
  std::sort(data, data + size);
  if (size % 2 == 1) {
    return (double)data[size/2];
  }
  else {
    return (double)(data[size/2] + data[size/2 - 1]) / 2;
  }
}

template <typename T> T max(T* data, int size) {
  // Returns the max element from an array of specified size
  T maxVal = 0;
  for (int i=0; i<size; ++i) {
    if (data[i] > maxVal) { maxVal = data[i]; }
  }
  return maxVal;
}

template <typename T> int numOver(T* data, int size, T cutoff) {
  // Returns a count of the number of elements exceeding the cutoff
  int count = 0;
  for (int i=0; i<size; ++i) {
    if (data[i] > cutoff) { count++; }
  }
  return count;
}

#endif
