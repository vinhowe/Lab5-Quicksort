
#include "QS.h"

#include <sstream>

QS::QS(){};

bool QS::createArray(int capacity) {
  clear();
  arrayCapacity = capacity;
  arraySize = 0;
  array = new int[capacity];
}

string QS::getArray() const {
  if (arraySize == 0 || array == nullptr) {
    return "";
  }

  ostringstream arrayStringStream;

  for (int i = 0; i < arraySize; i++) {
    arrayStringStream << array[i];
    if (i < arraySize - 1) {
      arrayStringStream << ",";
    }
  }

  return arrayStringStream.str();
}

bool QS::addToArray(int value) {
  if (arraySize == arrayCapacity) {
    return false;
  }

  array[arraySize] = value;
  arraySize++;
  return true;
}

int QS::getSize() const { return arraySize; }

void QS::clear() {
  if (array != nullptr) {
    arraySize = 0;
    arrayCapacity = 0;
    delete[] array;
    array = nullptr;
  }
}

int QS::partition(int left, int right, int pivotIndex) {
  if (right - left <= 0 || left < 0 || right >= arraySize ||
      pivotIndex > right) {
    return -1;
  }

  swap(pivotIndex, left);

  int up = left + 1;
  int down = right;

  do {
    while ((array[up] <= array[left]) && up < right) {
      up++;
    }
    while ((array[down] > array[left]) && (down > left)) {
      down--;
    }

    if (up < down) {
      swap(up, down);
    }
  } while (up < down);

  swap(left, down);

  return down;
}

int QS::medianOfThree(int left, int right) {
  if (right - left <= 0 || arraySize < 3 || right >= arraySize || left < 0) {
    return -1;
  }

  int middle = middleValue(left, right);

  bubbleSort3(left, right);

  return middle;
}

void QS::sortAll() { quicksort(0, arraySize - 1); }

void QS::swap(int first, int second) {
  int temp = array[first];
  array[first] = array[second];
  array[second] = temp;
}

void QS::quicksort(int left, int right) {
  if (right - left >= 1) {
    int pivot = medianOfThree(left, right);
    pivot = partition(left, right, pivot);

    quicksort(left, pivot - 1);
    quicksort(pivot + 1, right);
  }
}

void QS::bubbleSort3(int left, int right) {
  int middle = middleValue(left, right);
  if (array[left] > array[right]) {
    swap(left, right);
  }

  if (array[right] < array[middle]) {
    swap(right, middle);
  }

  if (array[middle] < array[left]) {
    swap(middle, left);
  }
}

int QS::middleValue(int left, int right) { return left + ((right - left) / 2); }
