#ifndef PATIENT_H
#define PATIENT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

/// @brief Структура Пациент
struct Patient final {
  std::string department;   // Отделение
  size_t ward;              // Номер палаты
  std::string diagnosis;    // Диагноз пациента
  std::string fullname;     // ФИО пациента

  /// @brief перегруженный оператор сравнения <
  /// (сравнение по полям – отделение, номер палаты, ФИО)
  /// @param other объект для сравнения
  bool operator<(const Patient& other) const {
    if (department != other.department) {
      return department < other.department;
    } else if (ward != other.ward) {
      return ward < other.ward;
    }
    return fullname < other.fullname;
  }

  bool operator>(const Patient& other) const {
    return other < *this;
  }

  bool operator<=(const Patient& other) const {
    return !(other < *this);
  }

  bool operator>=(const Patient& other) const {
    return !(*this < other);
  }

  friend std::ostream& operator<<(std::ostream& os, const Patient& patient) {
    os << patient.department << ", "
       << patient.ward << ", "
       << patient.fullname << ", "
       << patient.diagnosis;
    return os;
  }
};

/// @brief генерация ФИО пациента
/// @return ФИО пациента
std::string generateRandomName() {
  const std::string firstNames[] = {"Jack", "Jane", "Anthony", "Henry", "Violet",
                                    "Dean", "Sam", "Liam", "Olivia", "Noah",
                                    "Emma", "Oliver", "Ava", "Elijah",
                                    "Charlotte", "James", "Sophia"};
  const std::string lastNames[] = {"Doe", "Morgan", "Winchester", "Smith",
                                   "Johnson", "Williams", "Brown", "Jones",
                                   "Garcia", "Miller", "Davis", "Rodriguez",
                                   "Martinez"};

  return firstNames[rand() % (sizeof(firstNames) / sizeof(firstNames[0]))] + " " +
         lastNames[rand() % (sizeof(lastNames) / sizeof(lastNames[0]))];
}

/// @brief генерация отделения больницы
/// @return отделение больницы
std::string generateRandomDepartment() {
  const std::string departments[] = {"Therapy", "Surgery", "Cardiology",
                                     "Pediatrics", "Neurology"};
  return departments[rand() % (sizeof(departments) / sizeof(departments[0]))];
}

/// @brief генерация диагноза пациента
/// @return диагноз пациента
std::string generateRandomDiagnosis() {
  const std::string diagnoses[] = {"Flu", "Pneumonia", "Heart Failure",
                                   "Diabetes", "Asthma"};
  return diagnoses[rand() % (sizeof(diagnoses) / sizeof(diagnoses[0]))];
}

/// @brief генерация информации о пациентах больницы
/// @param patients массив пациентов для генерации
/// @param n размер массива пациентов
void generatePatients(Patient patients[], long n) {
  for (int i = 0; i < n; ++i) {
    Patient patient;
    patient.fullname = generateRandomName();
    patient.department = generateRandomDepartment();
    patient.diagnosis = generateRandomDiagnosis();
    patient.ward = rand() % 100 + 1; // Номер палаты от 1 до 100

    patients[i] = patient;
  }
}

/// @brief вывод массива пациентов
/// @param patients массив пациентов
/// @param n размер массива пациентов
void printPatients(Patient patients[], long n) {
  for (int i = 0; i < n; ++i) {
    std::cout << patients[i].department << ", "
              << patients[i].ward << ", "
              << patients[i].fullname << ", "
              << patients[i].diagnosis << std::endl;
  }
}

/// @brief заполнение массива пациентами из файла
/// @param filename содержит информацию о пациентах больницы
/// @param a массив для записи пациентов
/// @param n размер массива пациентов для записи
void readPatientsFromFile(const std::string& filename, Patient a[], long n) {
  std::ifstream file(filename);

  if (!file.is_open()) {
    std::cerr << "Ошибка открытия файла: " << filename << std::endl;
    return;
  }

  std::string line;
  long count = 0;

  while (count < n && std::getline(file, line)) {
    std::istringstream iss(line);
    Patient patient;

    std::getline(iss, patient.department, ',');
    std::string wardStr;
    std::getline(iss, wardStr, ',');
    std::getline(iss, patient.fullname, ',');
    std::getline(iss, patient.diagnosis, ',');

    patient.ward = std::stoul(wardStr);

    // Удаляем пробелы в начале и конце строк
    patient.fullname.erase(0, patient.fullname.find_first_not_of(" \t"));
    patient.fullname.erase(patient.fullname.find_last_not_of(" \t") + 1);
    patient.department.erase(0, patient.department.find_first_not_of(" \t"));
    patient.department.erase(patient.department.find_last_not_of(" \t") + 1);
    patient.diagnosis.erase(0, patient.diagnosis.find_first_not_of(" \t"));
    patient.diagnosis.erase(patient.diagnosis.find_last_not_of(" \t") + 1);

    a[count] = patient;
    count++;
  }

  file.close();
}

#endif // PATIENT_H
