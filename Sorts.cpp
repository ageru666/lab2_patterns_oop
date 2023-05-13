#include <iostream>
#include <vector>

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

int main() {
    using T = double;
    std::vector<T> numbers = { 5.2, 2.1, 9.4, 1.7, 3.8 };

    
    SortStrategy<T>* strategy = new QuickSortStrategy<T>();
    strategy->sort(numbers);
    delete strategy;

    std::cout << "QuickSort: ";
    for (const auto& number : numbers) {
        std::cout << number << " ";
    }
    std::cout << std::endl;

    
    strategy = new BubbleSortStrategy<T>();
    strategy->sort(numbers);
    delete strategy;

    std::cout << "BubbleSort: ";
    for (const auto& number : numbers) {
        std::cout << number << " ";
    }
    std::cout << std::endl;

    return 0;
}
