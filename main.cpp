/**
 * \file
 * \authors Штренев В.С., СКБ221
 */

#include "sorter.h"

#include <algorithm>
#include <filesystem>
#include <string>
#include <vector>

using namespace sorter;

using SortFunc = void(*)(Patient a[], long);

/// @brief обертка для замера времени работы сортировок квадратичной сложности
/// @param times вектор для записи времени
/// @param sortFunc функция сортировки
/// @param n указатель на массив размерностей
void
quadSortWrap(std::vector<double> &times, SortFunc sortFunc, long n[]) {
  std::filesystem::path currentPath = std::filesystem::current_path();
  std::string dir = currentPath.string() + "/output/quad/";
  std::error_code ec;
  std::filesystem::create_directories(dir, ec);
  if (ec) {
      std::cerr << "Не удалось создать директорию: " << ec.message() << std::endl;
      return;
  }
  for (long i {0}; i < 10; ++i) {
    Patient patients[n[i]];

    std::string c = "/home/thunder9029/study/MP/data/" + std::to_string(n[i])
                  + ".txt";

    readPatientsFromFile(c, patients, n[i]);
    clock_t start = clock();
    sortFunc(patients, n[i]);
    clock_t end = clock();
    times.push_back((double)(end - start) / CLOCKS_PER_SEC);
    std::string out = dir + std::to_string(n[i]) + ".txt";
    writePatientsToFile(out, patients, n[i]);
  }
}

/// @brief обертка для замера времени работы сортировки слиянием
/// @param times вектор для записи времени
/// @param n указатель на массив размерностей
void
mergeSortWrap(std::vector<double> &times, long n[]) {
  std::filesystem::path currentPath = std::filesystem::current_path();
  std::string dir = currentPath.string() + "/output/merge/";
  std::error_code ec;
  std::filesystem::create_directories(dir, ec);
  if (ec) {
      std::cerr << "Не удалось создать директорию: " << ec.message() << std::endl;
      return;
  }
  for (long i {0}; i < 10; ++i) {
    Patient patients[n[i]];

    std::string c = "/home/thunder9029/study/MP/data/" + std::to_string(n[i])
                  + ".txt";

    readPatientsFromFile(c, patients, n[i]);
    clock_t start = clock();
    sorter::mergeSort(patients, 0, n[i]-1);
    clock_t end = clock();
    times.push_back((double)(end - start) / CLOCKS_PER_SEC);
    std::string out = dir + std::to_string(n[i]) + ".txt";
    writePatientsToFile(out, patients, n[i]);
  }
}

/// @brief обертка для замера времени работы std::sort
/// @param times вектор для записи времени
/// @param n указатель на массив размерностей
void
stdSortWrap(std::vector<double> &times, long n[]) {
  std::filesystem::path currentPath = std::filesystem::current_path();
  std::string dir = currentPath.string() + "/output/sort/";
  std::error_code ec;
  std::filesystem::create_directories(dir, ec);
  if (ec) {
      std::cerr << "Не удалось создать директорию: " << ec.message() << std::endl;
      return;
  }
  for (long i {0}; i < 10; ++i) {
    Patient patients[n[i]];

    std::string c = "/home/thunder9029/study/MP/data/" + std::to_string(n[i])
                  + ".txt";

    readPatientsFromFile(c, patients, n[i]);
    clock_t start = clock();
    std::sort(patients, patients+(n[i]-1),
              [&](const Patient& a, const Patient& b) {
                return a < b;
              });
    clock_t end = clock();
    times.push_back((double)(end - start) / CLOCKS_PER_SEC);
    std::string out = dir + std::to_string(n[i]) + ".txt";
    writePatientsToFile(out, patients, n[i]);
  }
}

int main() {
  srand(static_cast<unsigned int>(time(0)));
  std::vector<double> bubbleSortTimes;
  std::vector<double> insertSortTimes;
  std::vector<double> mergeSortTimes;
  std::vector<double> sortTimes;
  long n[] = {100, 250, 500, 750, 1000, 1500, 2000, 2250, 2500, 5000};

  quadSortWrap(bubbleSortTimes, sorter::bubleSort, n);
  quadSortWrap(insertSortTimes, sorter::insertSort, n);
  mergeSortWrap(mergeSortTimes, n);
  stdSortWrap(sortTimes, n);

  return 0;
}