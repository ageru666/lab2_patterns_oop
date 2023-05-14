﻿#include <iostream>
#include <vector>
#include <ctime>



template <typename T>
class SortStrategy {
public:
   
    virtual void sort(std::vector<T>& array) = 0;
};

template <typename T>
class QuickSortStrategy : public SortStrategy<T> {
public:
  
    void sort(std::vector<T>& array) override {
        quicksort(array, 0, array.size() - 1);
    }

private:
    void quicksort(std::vector<T>& array, int low, int high) {
        if (low < high) {
            int pivotIndex = partition(array, low, high);
            quicksort(array, low, pivotIndex - 1);
            quicksort(array, pivotIndex + 1, high);
        }
    }

    int partition(std::vector<T>& array, int low, int high) {
        T pivot = array[high];
        int i = low - 1;

        for (int j = low; j <= high - 1; j++) {
            if (array[j] < pivot) {
                i++;
                std::swap(array[i], array[j]);
            }
        }

        std::swap(array[i + 1], array[high]);
        return i + 1;
    }
};

template <typename T>
class BubbleSortStrategy : public SortStrategy<T> {
public:
    void sort(std::vector<T>& array) override {
        int size = array.size();

        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (array[j] > array[j + 1]) {
                    std::swap(array[j], array[j + 1]);
                }
            }
        }
    }
};

template <typename T>
class MergeSortStrategy : public SortStrategy<T> {
public:
    void sort(std::vector<T>& array) override {
        mergesort(array, 0, array.size() - 1);
    }

private:
    void mergesort(std::vector<T>& array, int low, int high) {
        if (low < high) {
            int middle = low + (high - low) / 2;
            mergesort(array, low, middle);
            mergesort(array, middle + 1, high);
            merge(array, low, middle, high);
        }
    }

    void merge(std::vector<T>& array, int low, int middle, int high) {
        int leftSize = middle - low + 1;
        int rightSize = high - middle;

        std::vector<T> leftArray(leftSize);
        std::vector<T> rightArray(rightSize);

        for (int i = 0; i < leftSize; i++) {
            leftArray[i] = array[low + i];
        }

        for (int j = 0; j < rightSize; j++) {
            rightArray[j] = array[middle + 1 + j];
        }

        int i = 0;
        int j = 0;
        int k = low;

        while (i < leftSize && j < rightSize) {
            if (leftArray[i] <= rightArray[j]) {
                array[k] = leftArray[i];
                i++;
            }
            else {
                array[k] = rightArray[j];
                j++;
            }
            k++;
        }

        while (i < leftSize) {
            array[k] = leftArray[i];
            i++;
            k++;
        }

        while (j < rightSize) {
            array[k] = rightArray[j];
            j++;
            k++;
        }
    }
};

template <typename T>
class InsertionSortStrategy : public SortStrategy<T> {
public:
    void sort(std::vector<T>& array) override {
        int size = array.size();

        for (int i = 1; i < size; i++) {
            T key = array[i];
            int j = i - 1;

            while (j >= 0 && array[j] > key) {
                array[j + 1] = array[j];
                j--;
            }

            array[j + 1] = key;
        }
    }
};

template <typename T>
class HeapSortStrategy : public SortStrategy<T> {
public:
    void sort(std::vector<T>& array) override {
        int size = array.size();

        for (int i = size / 2 - 1; i >= 0; i--)
            heapify(array, size, i);

        for (int i = size - 1; i >= 0; i--) {

            std::swap(array[0], array[i]);

            heapify(array, i, 0);
        }
    }

private:
    void heapify(std::vector<T>& array, int size, int rootIndex) {
        int largest = rootIndex;
        int left = 2 * rootIndex + 1;
        int right = 2 * rootIndex + 2;

        if (left < size && array[left] > array[largest])
            largest = left;

        if (right < size && array[right] > array[largest])
            largest = right;

        if (largest != rootIndex) {
            std::swap(array[rootIndex], array[largest]);
            heapify(array, size, largest);
        }
    }
};

template <typename T>
class SortStrategyFactory {
public:
    static SortStrategy<T>* createSortStrategy(const std::string& algorithm) {
        if (algorithm == "quicksort") {
            return new QuickSortStrategy<T>();
        }
        else if (algorithm == "mergesort") {
            return new MergeSortStrategy<T>();
        }
        else if (algorithm == "bubblesort") {
            return new BubbleSortStrategy<T>();
        }
        else if (algorithm == "insertionsort") {
            return new InsertionSortStrategy<T>();
        }

        else if (algorithm == "heapsort") {
            return new HeapSortStrategy<T>();
        }

        else {
            std::cout << "Invalid sorting algorithm." << std::endl;
        }

        return nullptr;
    }
};

template <typename T>
class SortingTimerDecorator : public SortStrategy<T> {
private:
    SortStrategy<T>* strategy;

public:
  
    SortingTimerDecorator(SortStrategy<T>* strategy) : strategy(strategy) {}

    void sort(std::vector<T>& array) override {
        clock_t startTime = clock();
        strategy->sort(array);
        clock_t endTime = clock();

        double timeTaken = double(endTime - startTime) / CLOCKS_PER_SEC;
        std::cout << "Sorting time: " << timeTaken << " seconds" << std::endl;
    }
};

template <typename T>
class SortingFacade {
private:
    static SortingFacade<T>* instance;
    SortStrategy<T>* sortStrategy;
    SortingTimerDecorator<T>* timerDecorator;

    SortingFacade() : sortStrategy(nullptr), timerDecorator(nullptr) {}

public:

    static SortingFacade<T>* getInstance() {
        if (instance == nullptr) {
            instance = new SortingFacade<T>();
        }
        return instance;
    }


    ~SortingFacade() {
        delete sortStrategy;
        delete timerDecorator;
    }


    void setSortStrategy(const std::string& algorithm) {
        if (sortStrategy) {
            delete sortStrategy;
        }

        sortStrategy = SortStrategyFactory<T>::createSortStrategy(algorithm);
    }

    void sort(std::vector<T>& array) {
        if (!sortStrategy) {
            std::cout << "Need to set Sorting Strategy." << std::endl;
            return;
        }

        if (timerDecorator) {
            delete timerDecorator;
        }

        timerDecorator = new SortingTimerDecorator<T>(sortStrategy);
        timerDecorator->sort(array);
    }
};

template <typename T>
SortingFacade<T>* SortingFacade<T>::instance = nullptr;


int main() {
    using T = double;
    std::vector<T> numbers = { 5.2, 2.1, 9.4, 1.7, 3.8 };

    SortingFacade<T>* facade = SortingFacade<T>::getInstance();

    facade->setSortStrategy("quicksort");
    facade->sort(numbers);
    std::cout << "QuickSort: ";
    for (const auto& number : numbers) {
        std::cout << number << " ";
    }
    std::cout << std::endl;

    facade->setSortStrategy("bubblesort");
    facade->sort(numbers);
    std::cout << "BubbleSort: ";
    for (const auto& number : numbers) {
        std::cout << number << " ";
    }
    std::cout << std::endl;

    facade->setSortStrategy("mergesort");
    facade->sort(numbers);
    std::cout << "MergeSortStrategy: ";
    for (const auto& number : numbers) {
        std::cout << number << " ";
    }
    std::cout << std::endl;

    facade->setSortStrategy("insertionsort");
    facade->sort(numbers);
    std::cout << "InsertionSortStrategy: ";
    for (const auto& number : numbers) {
        std::cout << number << " ";
    }
    std::cout << std::endl;

    facade->setSortStrategy("heapsort");
    facade->sort(numbers);
    std::cout << "HeapSortStrategy: ";
    for (const auto& number : numbers) {
        std::cout << number << " ";
    }
    std::cout << std::endl;

    return 0;
}



