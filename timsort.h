#pragma once

#include "DoubleLinkedList.h"
#include "Stack.h"


const int MIN_RUN = 32;
const int MIN_MERGE = 64;
const int MIN_GALLOP = 7;

template <typename T>
void insertionSort(DoubleLinkedList<T>& run) {
    int length = run.getLength();
    for (int i = 1; i < length; i++) {
        T key = run.get(i);
        int j = i - 1;

        while (j >= 0 && run.get(j) > key) {
            run.set(j + 1, run.get(j));
            j--;
        }
        run.set(j + 1, key);
    }
}

template <typename T>
void merge(DoubleLinkedList<T>& arr, int left, int mid, int right) {
    int leftLen = mid - left + 1;
    int rightLen = right - mid;
    DoubleLinkedList<T> leftRun;
    DoubleLinkedList<T> rightRun;

    for (int i = 0; i < leftLen; i++) {
        leftRun.append(arr.get(left + i));
    }
    for (int i = 0; i < rightLen; i++) {
        rightRun.append(arr.get(mid + 1 + i));
    }

    int i = 0, j = 0, k = left;

    bool galloping = true;
    int gallopCount = 0;

    while (i < leftLen && j < rightLen) {
        if (galloping) {
            gallopCount = 0;
            while (i < leftLen && j < rightLen && leftRun.get(i) <= rightRun.get(j)) {
                arr.set(k, leftRun.get(i));
                i++;
                k++;
            }
            while (i < leftLen && j < rightLen && leftRun.get(i) > rightRun.get(j)) {
                arr.set(k, rightRun.get(j));
                j++;
                k++;
            }
            gallopCount++;

            if (gallopCount >= MIN_GALLOP) {
                galloping = false;
            }
        }
        else {
            if (leftRun.get(i) <= rightRun.get(j)) {
                arr.set(k, leftRun.get(i));
                i++;
            }
            else {
                arr.set(k, rightRun.get(j));
                j++;
            }
            k++;
        }
    }

    while (i < leftLen) {
        arr.set(k, leftRun.get(i));
        i++;
        k++;
    }

    while (j < rightLen) {
        arr.set(k, rightRun.get(j));
        j++;
        k++;
    }
}

template <typename T>
void timsort(DoubleLinkedList<T>& arr) {
    int n = arr.getLength();
    Stack<DoubleLinkedList<T>*> runStack;

    int i = 0;
    while (i < n) {
        int runSize = MIN_RUN;
        if (n - i <= MIN_RUN) {
            runSize = n - i;
        }

        DoubleLinkedList<T>* run = new DoubleLinkedList<T>();
        for (int j = 0; j < runSize; j++) {
            run->append(arr.get(i));
            i++;
        }

        if (run->getLength() >= MIN_MERGE) {
            while (!runStack.isEmpty() && runStack.top()->getLength() >= MIN_MERGE) {
                DoubleLinkedList<T>* topRun = runStack.pop();
                if (topRun->getLength() < run->getLength()) {
                    merge(*run, 0, topRun->getLength() - 1, run->getLength() - 1);
                    delete topRun;
                }
                else {
                    merge(*run, 0, run->getLength() - 1, topRun->getLength() - 1);
                }
            }
        }
        else {
            insertionSort(*run);
        }
        runStack.push(run);
    }

    i = 0;
    while (!runStack.isEmpty()) {
        DoubleLinkedList<T>* topRun = runStack.pop();
        for (int j = 0; j < topRun->getLength(); j++) {
            arr.set(i, topRun->get(j));
            i++;
        }
        delete topRun;
    }
}