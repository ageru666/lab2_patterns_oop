#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <vector>
#include <algorithm>
#include <random>
#include "Sorts.cpp"

TEST_CASE("Sorting Algorithms") {
    std::random_device rd;
    std::mt19937 generator(rd());

    SUBCASE("QuickSort") {
        SortingFacade<float>::getInstance()->setSortStrategy("quicksort");

        std::cout << "QuickSort: ";
        std::vector<float> numbers(1000);
        std::uniform_real_distribution<float> distribution(1.0f, 1000.0f);
        for (int i = 0; i < 100; i++) {
            numbers[i] = distribution(generator);
        }

        SortingFacade<float>::getInstance()->sort(numbers);

        CHECK(std::is_sorted(numbers.begin(), numbers.end()));
    }

    SUBCASE("BubbleSort") {
        SortingFacade<int>::getInstance()->setSortStrategy("bubblesort");

        std::cout << "BubbleSort: ";
        std::vector<int> numbers(1000);
        std::uniform_int_distribution<int> distribution(1, 1000);
        for (int i = 0; i < 100; i++) {
            numbers[i] = distribution(generator);
        }

        SortingFacade<int>::getInstance()->sort(numbers);

        CHECK(std::is_sorted(numbers.begin(), numbers.end()));
    }

    SUBCASE("InsertionSort") {
        SortingFacade<char>::getInstance()->setSortStrategy("insertionsort");

        std::cout << "InsertionSort: ";
        std::vector<char> letters = { 'd', 'a', 'c', 'b', 'e' };
        SortingFacade<char>::getInstance()->sort(letters);

        CHECK(std::is_sorted(letters.begin(), letters.end()));
    }

    SUBCASE("HeapSort") {
        SortingFacade<double>::getInstance()->setSortStrategy("heapsort");

        std::cout << "HeapSort: ";
        std::vector<double> numbers(100);
        std::uniform_real_distribution<double> distribution(0.0, 1.0);
        for (int i = 0; i < 100; i++) {
            numbers[i] = distribution(generator);
        }

        SortingFacade<double>::getInstance()->sort(numbers);

        CHECK(std::is_sorted(numbers.begin(), numbers.end()));

    }
    SUBCASE("MergeSort") {
        SortingFacade<long>::getInstance()->setSortStrategy("mergesort");

        std::cout << "MergeSort: ";
        std::vector<long> numbers(1000000);
        std::uniform_int_distribution<long> distribution(1, 10000000);
        for (int i = 0; i < 100; i++) {
            numbers[i] = distribution(generator);
        }

        SortingFacade<long>::getInstance()->sort(numbers);

        CHECK(std::is_sorted(numbers.begin(), numbers.end()));
    }

    SUBCASE("MultiThreadMergeSort") {
        SortingFacade<long>::getInstance()->setSortStrategy("multithreadmergesort");

        std::cout << "MultiThreadMergeSort: ";
        std::vector<long> numbers(1000000);
        std::uniform_int_distribution<long> distribution(1, 10000000);
        for (int i = 0; i < 100; i++) {
            numbers[i] = distribution(generator);
        }

        SortingFacade<long>::getInstance()->sort(numbers);

        CHECK(std::is_sorted(numbers.begin(), numbers.end()));
    }
}