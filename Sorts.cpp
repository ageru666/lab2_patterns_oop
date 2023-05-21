#include <iostream>
#include <vector>
#include <ctime>
#include <thread>

/**
    * @brief SortStrategy template.
    *
    * This template defines the interface for different sorting strategies.
    * Subclasses must implement the sort() function to provide their specific sorting algorithm.
    */
template <typename T>
class SortStrategy {
public:
     /**
     * @brief Sorts the given vector in a specific way.
     * @param array The vector to be sorted.
     */
    virtual void sort(std::vector<T>& array) = 0;
};

template <typename T>
class QuickSortStrategy : public SortStrategy<T> {
public:
    /**
    * @brief Sorts the given vector using the QuickSort algorithm.
    * @param array The vector to be sorted.
    */
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
    /**
    * @brief Sorts the given vector using the BubbleSort algorithm.
    * @param array The vector to be sorted.
    */
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
    /**
    * @brief Sorts the given vector using the MergeSort algorithm.
    * @param array The vector to be sorted.
    */
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
    /**
    * @brief Sorts the given vector using the InsertionSort algorithm.
    * @param array The vector to be sorted.
    */
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
    /**
    * @brief Sorts the given vector using the HeapSort algorithm.
    * @param array The vector to be sorted.
    */
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
class MultiThreadMergeSortStrategy : public SortStrategy<T> {
public:
    /**
     * @brief Sorts the given vector using the Multi-Threaded MergeSort algorithm.
     * @param array The vector to be sorted.
     */
    void sort(std::vector<T>& array) override {
        multiThreadMergeSort(array, 0, array.size() - 1);
    }

private:
    void multiThreadMergeSort(std::vector<T>& array, int low, int high) {
        if (low < high) {
            if (high - low < 10000) {
                mergesort(array, low, high);
            }
            else {
                int middle = low + (high - low) / 2;

                std::thread leftThread(&MultiThreadMergeSortStrategy<T>::multiThreadMergeSort, this, std::ref(array), low, middle);
                std::thread rightThread(&MultiThreadMergeSortStrategy<T>::multiThreadMergeSort, this, std::ref(array), middle + 1, high);

                leftThread.join();
                rightThread.join();

                merge(array, low, middle, high);
            }
        }
    }

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
class SortStrategyFactory {
public:
    /**
    * @brief Creates a specific sorting strategy based on the provided algorithm.
    * @param algorithm The algorithm name.
    * @return A pointer to the created SortStrategy object, or nullptr if the algorithm is not supported.
    */
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
        else if (algorithm == "multithreadmergesort") {
            return new MultiThreadMergeSortStrategy<T>();
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
    /**
    * @brief Constructs a SortingTimerDecorator object.
    * @param strategy The underlying sorting strategy to be decorated.
    */
    SortingTimerDecorator(SortStrategy<T>* strategy) : strategy(strategy) {}

    /**
    * @brief Sorts the given vector using the decorated strategy and measures the sorting time.
    * @param array The vector to be sorted.
    */
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
    /**
    * @brief Returns the singleton instance of SortingFacade.
    * @return The singleton instance.
    */
    static SortingFacade<T>* getInstance() {
        if (instance == nullptr) {
            instance = new SortingFacade<T>();
        }
        return instance;
    }

    /**
    * @brief Destructor. Cleans up allocated memory.
    */
    ~SortingFacade() {
        delete sortStrategy;
        delete timerDecorator;
    }

    /**
    * @brief Sets the sorting strategy based on the provided algorithm name.
    * @param algorithm The algorithm name.
    */
    void setSortStrategy(const std::string& algorithm) {
        if (sortStrategy) {
            delete sortStrategy;
        }

        sortStrategy = SortStrategyFactory<T>::createSortStrategy(algorithm);
    }
    /**
    * @brief Sorts the given vector using the currently set sorting strategy.
    * @param array The vector to be sorted.
    * @note If no sorting strategy is set, an error message will be displayed.
    */
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




