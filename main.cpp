#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <array>
#include <ctime>
#include "Data.h"
using namespace std;

template<typename T>
void BubbleSort(vector <T>& arr, int size) {
    int i, j;
    bool swapped;
    for (i = 0; i < size - 1; i++) {
        swapped = false;
        for (j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
    }
}
template <typename T>
void MinSort(vector <T>& arr, int size) {
    int min;
    for (int i = 0; i < size - 1; ++i) {
        min = i;
        for (int j = i + 1; j < size; ++j) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        swap(arr[i], arr[min]);
    }
}

template<typename T>
int Partition(vector<T> &numbers, int i, int k) {
    int l;
    int h;
    int midpoint;
    T pivot;
    T temp;
    bool done;

    midpoint = i + (k - i) / 2;
    pivot = numbers.at(midpoint);

    done = false;
    l = i;
    h = k;

    while (!done) {
        while (numbers.at(l) < pivot) {
            ++l;
        }

        while (pivot < numbers.at(h)) {
            --h;
        }

        if (l >= h) {
            done = true;
        } else {
            temp = numbers.at(l);
            numbers.at(l) = numbers.at(h);
            numbers.at(h) = temp;

            ++l;
            --h;
        }
    }

    return h;
}
template<typename T>
void QuickSort(vector<T> &numbers, int i, int k) {
    int j;
    if (i >= k) {
        return;
    }

    j = Partition(numbers, i, k);

    QuickSort(numbers, i, j);
    QuickSort(numbers, j + 1, k);
}

template<typename T>
void Merge(vector<T> &numbers, int i, int j, int k) {

    int mergedSize;
    int mergePos;
    int leftPos;
    int rightPos;

    mergePos = 0;
    mergedSize = k - i + 1;
    leftPos = i;
    rightPos = j + 1;
    vector<T> mergedNumbers(mergedSize);

    while (leftPos <= j && rightPos <= k) {
        if (numbers[leftPos] < numbers[rightPos]) {
            mergedNumbers.at(mergePos) = numbers.at(leftPos);
            ++leftPos;
        } else {
            mergedNumbers.at(mergePos) = numbers.at(rightPos);
            ++rightPos;

        }
        ++mergePos;
    }

    while (leftPos <= j) {
        mergedNumbers[mergePos] = numbers[leftPos];
        ++leftPos;
        ++mergePos;
    }

    while (rightPos <= k) {
        mergedNumbers[mergePos] = numbers[rightPos];
        ++rightPos;
        ++mergePos;
    }

    for (mergePos = 0; mergePos < mergedSize; ++mergePos) {
        numbers[i + mergePos] = mergedNumbers[mergePos];
    }
}

template<typename T>
void MergeSort(vector<T> &numbers, int i, int k) {
    int j;

    if (i < k) {
        j = (i + k) / 2;
        MergeSort(numbers, i, j);
        MergeSort(numbers, j + 1, k);
        Merge(numbers, i, j, k);
    }
}

int main() {
    srand(time(NULL));
    vector<Data> dataV;
    vector<int> intV;
    ifstream in;
    ofstream out;

    out.open("SortingTimes.csv");
    in.open("...winemag-data_first150k.csv");

    if (!in.is_open()) {
        cout << "File was not opened correctly!" << endl;
        return 1;
    }
    cout << "Reading winemag-data_first150k.csv..." << endl;

    if (!out.is_open()) {
        cout << "File was not opened correctly!" << endl;
        return 1;
    }
    cout << "Writing in winemag-data_first150k.csv..." << endl;

    while (!in.eof()) {
        string crty, point, pric, prov, var;
        getline(in, crty, ',');
        getline(in, point, ',');
        getline(in, pric, ',');
        getline(in, prov, ',');
        getline(in, var, '\n');

        int points = 0;
        if (point != "") {
            points = stoi(point);
        }
        int price = 0;
        if (pric != "") {
            price = stoi(pric);
        }

        Data info = Data(crty, points, price, prov, var);
        dataV.push_back(info);
    }
    cout << "File has been read in.\n";
    for (int i = 0; i < dataV.size(); i++) {
        intV.push_back(rand() % 100);
    }
    out << " j , elapsed_dataV_B , elapsed_intV_B , elapsed_dataV_S , elapsed_intV_S , elapsed_dataV_Q , elapsed_intV_Q "
           ", elapsed_dataV_M , elapsed_intV_M , elapsed_dataV_B2 , elapsed_intV_B2 , elapsed_dataV_S2 , elapsed_intV_S2 "
           " , elapsed_dataV_Q2 , elapsed_intV_Q2 , elapsed_dataV_M2 , elapsed_intV_M2 " << '\n';


    for (int j = 100; j<=dataV.size(); j= j+3000) {
        vector<Data> dataV_B = dataV;
        vector<Data> dataV_S = dataV;
        vector<Data> dataV_Q = dataV;
        vector<Data> dataV_M = dataV;
        vector<int> intV_B = intV;
        vector<int> intV_S = intV;
        vector<int> intV_Q = intV;
        vector<int> intV_M = intV;

        cout << "Sorting using BubbleSort..." << endl;

        clock_t start_dataV_B = clock();
        BubbleSort(dataV_B, j);
        clock_t end_dataV_B = clock();
        double elapsed_dataV_B = double(end_dataV_B - start_dataV_B) / CLOCKS_PER_SEC;
        for (int i = 1; i < j - 1; i++) {
            assert(dataV_B.at(i - 1) <= dataV_B.at(i));
        }
        clock_t start_intV_B = clock();
        BubbleSort(intV_B, j);
        clock_t end_intV_B = clock();
        double elapsed_intV_B = double(end_intV_B - start_intV_B) / CLOCKS_PER_SEC;
        for (int i = 1; i < j - 1; i++) {
            assert(intV_B.at(i - 1) <= intV_B.at(i));
        }

        cout << "BubbleSort Complete!" << endl << "Sorting using SelectionSort..." << endl;

        clock_t start_dataV_S = clock();
        MinSort(dataV_S, j);
        clock_t end_dataV_S = clock();
        double elapsed_dataV_S = double(end_dataV_S - start_dataV_S) / CLOCKS_PER_SEC;
        for (int i = 1; i < j - 1; i++) {
            assert(dataV_S.at(i - 1) <= dataV_S.at(i));
        }

        clock_t start_intV_S = clock();
        MinSort(intV_S, j);
        clock_t end_intV_S = clock();
        double elapsed_intV_S = double(end_intV_S - start_intV_S) / CLOCKS_PER_SEC;
        for (int i = 1; i < j - 1; i++) {
            assert(intV_S.at(i - 1) <= intV_S.at(i));
        }
        cout << "SelectionSort Complete!" << endl << "Sorting using QuickSort..." << endl;
        clock_t start_dataV_Q = clock();
        QuickSort(dataV_Q, 0, j - 1);
        clock_t end_dataV_Q = clock();
        double elapsed_dataV_Q = double(end_dataV_Q - start_dataV_Q) / CLOCKS_PER_SEC;
        for (int i = 1; i < j - 1; i++) {
            assert(dataV_Q.at(i - 1) <= dataV_Q.at(i));
        }

        clock_t start_intV_Q = clock();
        QuickSort(intV_Q, 0, j - 1);
        clock_t end_intV_Q = clock();
        double elapsed_intV_Q = double(end_intV_Q - start_intV_Q) / CLOCKS_PER_SEC;

        for (int i = 1; i < j - 1; i++) {
            assert(intV_Q.at(i - 1) <= intV_Q.at(i));
        }

        cout << "QuickSort Complete!" << endl << "Sorting using MergeSort..." << endl;

        clock_t start_dataV_M = clock();
        MergeSort(dataV_M, 0, j - 1);
        clock_t end_dataV_M = clock(); //end clock
        double elapsed_dataV_M = double(end_dataV_M - start_dataV_M) / CLOCKS_PER_SEC;

        for (int i = 1; i < j - 1; i++) {
            assert(dataV_M.at(i - 1) <= dataV_M.at(i));
        }

        clock_t start_intV_M = clock();
        MergeSort(intV_M, 0, j - 1);
        clock_t end_intV_M = clock();
        double elapsed_intV_M = double(end_intV_M - start_intV_M) / CLOCKS_PER_SEC;

        for (int i = 1; i < j - 1; i++) {
            assert(intV_M.at(i - 1) <= intV_M.at(i));
        }

        cout << "QuickSort Complete!" << endl;

        cout << "All the vectors are completely sorted. They will now be sorted to see the best case." << endl;

        cout << "Sorting using BubbleSort..." << endl;

        clock_t start_dataV_B2 = clock();
        BubbleSort(dataV_B, j);
        clock_t end_dataV_B2 = clock();
        double elapsed_dataV_B2 = double(end_dataV_B2 - start_dataV_B2) / CLOCKS_PER_SEC;

        clock_t start_intV_B2 = clock();
        BubbleSort(intV_B, j);
        clock_t end_intV_B2 = clock();
        double elapsed_intV_B2 = double(end_intV_B2 - start_intV_B2) / CLOCKS_PER_SEC;


        cout << "BubbleSort Complete!" << endl << "Sorting using SelectionSort..." << endl;

        clock_t start_dataV_S2 = clock();
        MinSort(dataV_S, j);
        clock_t end_dataV_S2 = clock();
        double elapsed_dataV_S2 = double(end_dataV_S2 - start_dataV_S2) / CLOCKS_PER_SEC;

        clock_t start_intV_S2 = clock();
        MinSort(intV_S, j);
        clock_t end_intV_S2 = clock();
        double elapsed_intV_S2 = double(end_intV_S2 - start_intV_S2) / CLOCKS_PER_SEC;

        cout << "SelectionSort Complete!" << endl << "Sorting using QuickSort..." << endl;

        clock_t start_dataV_Q2 = clock();
        QuickSort(dataV_Q, 0, j - 1);
        clock_t end_dataV_Q2 = clock();
        double elapsed_dataV_Q2 = double(end_dataV_Q2 - start_dataV_Q2) / CLOCKS_PER_SEC;

        clock_t start_intV_Q2 = clock();
        QuickSort(intV_Q, 0, j - 1);
        clock_t end_intV_Q2 = clock();
        double elapsed_intV_Q2 = double(end_intV_Q2 - start_intV_Q2) / CLOCKS_PER_SEC;

        cout << "QuickSort Complete!" << endl << "Sorting using MergeSort..." << endl;

        clock_t start_dataV_M2 = clock();
        MergeSort(dataV_M, 0, j - 1);
        clock_t end_dataV_M2 = clock();
        double elapsed_dataV_M2 = double(end_dataV_M2 - start_dataV_M2) / CLOCKS_PER_SEC;

        clock_t start_intV_M2 = clock();
        MergeSort(intV_M, 0, j - 1);
        clock_t end_intV_M2 = clock();
        double elapsed_intV_M2 = double(end_intV_M2 - start_intV_M2) / CLOCKS_PER_SEC;

        cout << "QuickSort Complete!" << endl;

        cout << "Second round of sorting complete!" << endl;
        out << j << "," << elapsed_dataV_B << "," << elapsed_intV_B << "," << elapsed_dataV_S << "," << elapsed_intV_S
            << "," << elapsed_dataV_Q << "," << elapsed_intV_Q << "," << elapsed_dataV_M << "," << elapsed_intV_M
            << "," << elapsed_dataV_B2 << "," << elapsed_intV_B2 << "," << elapsed_dataV_S2 << "," << elapsed_intV_S2
            << "," << elapsed_dataV_Q2 << "," << elapsed_intV_Q2 << "," << elapsed_dataV_M2 << "," << elapsed_intV_M2
            << '\n';
        out.flush();
    }

    in.close();
    out.close();


    return 0;

}