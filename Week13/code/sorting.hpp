#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <list>
#include <cmath>
#include <functional>
#include <mutex>

namespace sorting_algos {

    // --- 1. Counting Sort ---
    void countingSort(std::vector<int>& arr) {
        if (arr.empty()) return;

        int maxVal = *std::max_element(arr.begin(), arr.end());
        int minVal = *std::min_element(arr.begin(), arr.end());
        
        // Handle negative numbers by shifting
        int range = maxVal - minVal + 1;
        
        std::vector<int> count(range, 0);
        std::vector<int> output(arr.size());

        for (int x : arr) {
            count[x - minVal]++;
        }

        for (int i = 1; i < range; i++) {
            count[i] += count[i - 1];
        }

        for (int i = arr.size() - 1; i >= 0; i--) {
            output[count[arr[i] - minVal] - 1] = arr[i];
            count[arr[i] - minVal]--;
        }

        for (size_t i = 0; i < arr.size(); i++) {
            arr[i] = output[i];
        }
    }

    // --- 2. Radix Sort ---
    void countingSortForRadix(std::vector<int>& arr, int exp) {
        int n = arr.size();
        std::vector<int> output(n);
        int count[10] = {0};

        for (int i = 0; i < n; i++)
            count[(arr[i] / exp) % 10]++;

        for (int i = 1; i < 10; i++)
            count[i] += count[i - 1];

        for (int i = n - 1; i >= 0; i--) {
            output[count[(arr[i] / exp) % 10] - 1] = arr[i];
            count[(arr[i] / exp) % 10]--;
        }

        for (int i = 0; i < n; i++)
            arr[i] = output[i];
    }

    void radixSort(std::vector<int>& arr) {
        if (arr.empty()) return;
        int maxVal = *std::max_element(arr.begin(), arr.end());

        // Do counting sort for every digit
        for (int exp = 1; maxVal / exp > 0; exp *= 10)
            countingSortForRadix(arr, exp);
    }

    // --- 3. Bucket Sort ---
    // Assumes uniform distribution, for float in [0, 1) or simplified for ints
    void bucketSort(std::vector<float>& arr) {
        int n = arr.size();
        if (n <= 0) return;

        std::vector<std::vector<float>> b(n);

        for (int i = 0; i < n; i++) {
            int bi = n * arr[i]; // Index in bucket
            if (bi >= n) bi = n - 1; 
            b[bi].push_back(arr[i]);
        }

        for (int i = 0; i < n; i++)
            std::sort(b[i].begin(), b[i].end());

        int index = 0;
        for (int i = 0; i < n; i++)
            for (float val : b[i])
                arr[index++] = val;
    }
    
    // --- 4. Heap Sort ---
    void heapify(std::vector<int>& arr, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left] > arr[largest])
            largest = left;

        if (right < n && arr[right] > arr[largest])
            largest = right;

        if (largest != i) {
            std::swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }

    void heapSort(std::vector<int>& arr) {
        int n = arr.size();
        // Build heap
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(arr, n, i);

        // Extract elements
        for (int i = n - 1; i > 0; i--) {
            std::swap(arr[0], arr[i]);
            heapify(arr, i, 0);
        }
    }

    // --- 5. Quick Sort ---
    int partition(std::vector<int>& arr, int low, int high) {
        int pivot = arr[high];
        int i = (low - 1);
        for (int j = low; j <= high - 1; j++) {
            if (arr[j] < pivot) {
                i++;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[high]);
        return (i + 1);
    }

    void quickSortRecursive(std::vector<int>& arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            quickSortRecursive(arr, low, pi - 1);
            quickSortRecursive(arr, pi + 1, high);
        }
    }

    void quickSort(std::vector<int>& arr) {
        if (arr.empty()) return;
        quickSortRecursive(arr, 0, arr.size() - 1);
    }

    // --- 6. Merge Sort ---
    void merge(std::vector<int>& arr, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        std::vector<int> L(n1), R(n2);

        for (int i = 0; i < n1; i++) L[i] = arr[left + i];
        for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
        }
        while (j < n2) {
            arr[k] = R[j];
            j++;
            k++;
        }
    }

    void mergeSortRecursive(std::vector<int>& arr, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSortRecursive(arr, left, mid);
            mergeSortRecursive(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    }

    void mergeSort(std::vector<int>& arr) {
        if (arr.empty()) return;
        mergeSortRecursive(arr, 0, arr.size() - 1);
    }

    // --- 7. Cocktail Sort (Shaker Sort) ---
    void cocktailSort(std::vector<int>& arr) {
        bool swapped = true;
        int start = 0;
        int end = arr.size() - 1;

        while (swapped) {
            swapped = false;
            for (int i = start; i < end; ++i) {
                if (arr[i] > arr[i + 1]) {
                    std::swap(arr[i], arr[i + 1]);
                    swapped = true;
                }
            }
            if (!swapped) break;
            swapped = false;
            --end;
            for (int i = end - 1; i >= start; --i) {
                if (arr[i] > arr[i + 1]) {
                    std::swap(arr[i], arr[i + 1]);
                    swapped = true;
                }
            }
            ++start;
        }
    }

    // --- 8. Shell Sort ---
    void shellSort(std::vector<int>& arr) {
        int n = arr.size();
        for (int gap = n / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < n; i += 1) {
                int temp = arr[i];
                int j;
                for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                    arr[j] = arr[j - gap];
                arr[j] = temp;
            }
        }
    }

    // --- 9. Intro Sort ---

    void insertionSortRange(std::vector<int>& arr, int low, int high) {
        for (int i = low + 1; i <= high; i++) {
            int key = arr[i];
            int j = i - 1;
            while (j >= low && arr[j] > key) {
                arr[j + 1] = arr[j];
                j = j - 1;
            }
            arr[j + 1] = key;
        }
    }

    void heapifyHelper(std::vector<int>& arr, int n, int i, int offset) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[offset + left] > arr[offset + largest])
            largest = left;

        if (right < n && arr[offset + right] > arr[offset + largest])
            largest = right;

        if (largest != i) {
            std::swap(arr[offset + i], arr[offset + largest]);
            heapifyHelper(arr, n, largest, offset);
        }
    }

    void heapSortRange(std::vector<int>& arr, int low, int high) {
        int n = high - low + 1;
        // Build heap
        for (int i = n / 2 - 1; i >= 0; i--)
            heapifyHelper(arr, n, i, low);

        // Extract elements
        for (int i = n - 1; i > 0; i--) {
            std::swap(arr[low], arr[low + i]);
            heapifyHelper(arr, i, 0, low);
        }
    }

    void introSort(std::vector<int>& arr) {
        if (arr.empty()) return;

        int n = arr.size();
        int maxDepth = 2 * std::log(n);

        struct Frame {
            int low;
            int high;
            int depth;
        };
        std::vector<Frame> stack;
        stack.push_back({0, n - 1, maxDepth});

        while (!stack.empty()) {
            Frame current = stack.back();
            stack.pop_back();

            int low = current.low;
            int high = current.high;
            int depth = current.depth;

            // Base case or fully processed
            if (low >= high) continue;

            int size = high - low + 1;

            if (size < 16) {
                insertionSortRange(arr, low, high);
            } else if (depth == 0) {
                heapSortRange(arr, low, high);
            } else {
                // Quicksort
                int pi = partition(arr, low, high);
                // Push right first (processed last)
                stack.push_back({pi + 1, high, depth - 1});
                // Push left second (processed first)
                stack.push_back({low, pi - 1, depth - 1});
            }
        }
    }

    // --------------------------------------------------------------

    // --- 10. Bogo Sort ---
    bool isSorted(const std::vector<int>& arr) {
        for (size_t i = 1; i < arr.size(); ++i)
            if (arr[i] < arr[i - 1]) return false;
        return true;
    }

    void bogoSort(std::vector<int>& arr) {
        std::random_device rd;
        std::mt19937 g(rd());
        while (!isSorted(arr)) {
            std::shuffle(arr.begin(), arr.end(), g);
        }
    }

    // --- 11. Sleep Sort ---
    // Works with positive integers. Uses threads.
    void sleepSort(std::vector<int>& arr) {
        std::vector<int> sortedArr;
        std::vector<std::thread> threads;
        std::mutex mtx;

        for (int num : arr) {
            threads.emplace_back([num, &sortedArr, &mtx]() {
                std::this_thread::sleep_for(std::chrono::milliseconds(num * 10)); // Scale factor
                std::lock_guard<std::mutex> lock(mtx);
                sortedArr.push_back(num);
            });
        }

        for (auto& t : threads) {
            t.join();
        }

        arr = sortedArr;
    }

}
