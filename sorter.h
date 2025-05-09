#ifndef SORTER_H
#define SORTER_H

#include "patient.h"

#include <vector>

namespace sorter {
/// @brief функция сортировки пузырьком
void bubleSort(Patient a[], long size) {
  bool swapped;

  for (long i=0; i < size - 1; i++) {
    swapped = false;
    for (long j = 0; j < size - (i + 1); j++) {
      if (a[j] > a[j+1]) {
        std::swap(a[j], a[j+1]);
        swapped = true;
      }
    }
    if (!swapped) {
      break;
    }
  }
};

/// @brief функция для сортировки простыми вставками
void insertSort(Patient a[], long size) {
  long j;
  for (long i = 0; i < size; i++) {
    auto patient = a[i];

    for (j = i-1; j>=0 && a[j] > patient; j--) {
      a[j+1] = a[j];
    }
    a[j+1] = patient;
  }
};

/// @brief функция для соединения двух массивов в один
/// @param a массив для сортировки
/// @param low нижняя граница для сортировки
/// @param mid средняя граница для сортировки
/// @param high верхняя граница для сортировки
void merge(Patient a[], long low, long mid, long high) {
  // Variables declaration.
  Patient *b = new Patient[high+1-low];
  long h = low, i = 0, j = mid+1, k;
  // Merges the two array's into b[] until the first one is finish
  while ((h<=mid) && (j<=high)) {
    if (a[h]<=a[j]) {
      b[i] = a[h];
      h++;
    } else {
      b[i] = a[j];
      j++;
    }
    i++;
  }
  // Completes the array filling in it the missing values
  if (h>mid) {
    for (k=j;k<=high;k++) {
      b[i] = a[k];
      i++;
    }
  } else {
    for (k=h;k<=mid;k++) {
      b[i] = a[k];
      i++;
    }
  }
  // Prints into the original array
  for (k=0;k<=high-low;k++) {
    a[k+low] = b[k];
  }
  delete[] b;
}

/// @brief функция для сортировки слиянием
/// @param a массив для сортировки
/// @param low нижняя граница диапазона сортировки
/// @param high верхняя граница диапазона сортировки
void mergeSort(Patient a[], long low, long high) {
  ///TODO: mergeSort
  if (low < high) {
    long mid = (high + low)/2;
    mergeSort(a, low, mid);
    mergeSort(a, mid+1, high);
    merge(a, low, mid, high);
  }
};

}

#endif // SORTER_H
