#include <iostream>
#include "DoubleLinkedList.h"
#include <vector>
#include "Stack.h"

int getMinRun(size_t len);

template<typename T>
void upperBound(DoubleLinkedList<T>& list, int (*cmp)(const void*, const void*), int& count, int& step, T*& arr, T*& tmpPtr, T*& key);

template<typename T>
void reverseArr(DoubleLinkedList<T>& list, size_t len);

template<typename T>
void insertSort(DoubleLinkedList<T>& list, int (*cmp)(const void*, const void*));

template<typename T>
void partSort(DoubleLinkedList<T>& list, size_t len, int (*cmp)(const void*, const void*), int min_run = 0);

template<typename T>
std::vector<std::pair<int, int>> fillPartStack(DoubleLinkedList<T>& list, size_t len, int (*cmp)(const void*, const void*));

template<typename T>
void mergeLinkedListIndices(DoubleLinkedList<T>& list, int leftStart, int leftLen, int rightStart, int rightLen, int (*cmp)(const void*, const void*));

template<typename T>
void mergeLinkedList(DoubleLinkedList<T>& list, int start, int len1, int len2, int (*cmp)(const void*, const void*));

template<typename T>
void timSort(DoubleLinkedList<T>& list, int (*cmp)(const void*, const void*), int min_run = 0);

int getMinRun(size_t len)
{
    size_t r = 0;

    while (len >= 64)
    {
        r |= len & 1;
        len >>= 1;
    }

    return len + r;
}

template<typename T>
void upperBound(DoubleLinkedList<T>& list, int (*cmp)(const void*, const void*), int& count, int& step, T*& arr, T*& tmpPtr, T*& key)
{
    count = list.getLength();
    step = 0;

    while (count > 0)
    {
        step = count / 2;
        tmpPtr = &list.get(step);

        if (cmp(key, tmpPtr) > 0)
        {
            arr = tmpPtr + 1;
            count -= step + 1;
        }
        else
            count = step;
    }
}

template<typename T>
void reverseArr(DoubleLinkedList<T>& list, size_t len)
{
    for (size_t i = 0; i < len / 2; ++i)
    {
        T temp = list.get(i);
        list.set(i, list.get(len - i - 1));
        list.set(len - i - 1, temp);
    }
}

template<typename T>
void insertSort(DoubleLinkedList<T>& list, int (*cmp)(const void*, const void*))
{
    for (size_t i = 1; i < list.getLength(); ++i)
    {
        for (size_t j = i; j > 0 && cmp(&list.get(j - 1), &list.get(j)) > 0; --j)
        {
            T temp = list.get(j);
            list.set(j, list.get(j - 1));
            list.set(j - 1, temp);
        }
    }
}

template<typename T>
void partSort(DoubleLinkedList<T>& list, size_t len, int (*cmp)(const void*, const void*), int min_run)
{
    bool ascendSeq;
    size_t curLen;
    size_t minRun = min_run ? min_run : getMinRun(len);

    size_t curPtr = 0;
    while (curPtr < len - 1)
    {
        ascendSeq = cmp(&list.get(curPtr), &list.get(curPtr + 1)) <= 0;

        for (curLen = 2; curPtr + curLen < len && ascendSeq == (cmp(&list.get(curPtr + curLen - 1), &list.get(curPtr + curLen)) <= 0); ++curLen);

        if (!ascendSeq)
            reverseArr(list, curLen);

        if (curLen < minRun)
            curLen = std::min<size_t>(minRun, len - curPtr);

        insertSort(list, cmp);

        curPtr = curPtr + curLen;
    }
}

template<typename T>
std::vector<std::pair<int, int>> fillPartStack(DoubleLinkedList<T>& list, size_t len, int (*cmp)(const void*, const void*))
{
    int tmpStart = 0;
    std::vector<std::pair<int, int>> partStack;

    for (int i = 0; i + 1 < len; ++i)
    {
        if (cmp(&list.get(i), &list.get(i + 1)) > 0)
        {
            partStack.emplace_back(tmpStart, i - tmpStart + 1);
            tmpStart = i + 1;
        }
    }
    partStack.emplace_back(tmpStart, len - tmpStart);

    return partStack;
}

template<typename T>
void mergeLinkedListIndices(DoubleLinkedList<T>& list, int leftStart, int leftLen, int rightStart, int rightLen, int (*cmp)(const void*, const void*))
{
    Stack<std::pair<int, int>> mergeStack;
    mergeStack.push(std::make_pair(leftStart, leftLen));

    while (mergeStack.size() > 0)
    {
        auto left = mergeStack.pop();
        int len1 = left.second;
        int len2 = rightLen;

        int start = left.first;
        if (len1 + len2 <= 64)
        {
            mergeLinkedList(list, start, len1, len2, cmp);
        }
        else
        {
            int mid = len1 / 2;
            mergeStack.push(std::make_pair(start + mid, len1 - mid));
            mergeStack.push(std::make_pair(start, mid));
            mergeStack.push(std::make_pair(start + len1, len2));
        }
    }
}

template<typename T>
void mergeLinkedList(DoubleLinkedList<T>& list, int start, int len1, int len2, int (*cmp)(const void*, const void*))
{
    DoubleLinkedList<T> left;
    DoubleLinkedList<T> right;

    for (int i = 0; i < len1; ++i)
        left.append(list.get(start + i));

    for (int i = 0; i < len2; ++i)
        right.append(list.get(start + len1 + i));

    int i = 0, j = 0, k = start;

    while (i < len1 && j < len2)
    {
        if (cmp(&left.get(i), &right.get(j)) <= 0)
        {
            list.set(k++, left.get(i++));
        }
        else
        {
            list.set(k++, right.get(j++));
        }
    }

    while (i < len1)
    {
        list.set(k++, left.get(i++));
    }

    while (j < len2)
    {
        list.set(k++, right.get(j++));
    }
}

template<typename T>
void timSort(DoubleLinkedList<T>& list, int (*cmp)(const void*, const void*), int min_run)
{
    partSort(list, list.getLength(), cmp, min_run);
    auto partStack = fillPartStack(list, list.getLength(), cmp);


    unsigned int x;
    unsigned int y;
    unsigned int z;
    unsigned int head = 2;
    while (partStack.size() > 2)
    {
        x = partStack[head].second;
        y = partStack[head - 1].second;
        z = partStack[head - 2].second;

        if ((x > y + z && y > z) || x < z)
        {
            mergeLinkedListIndices(list, partStack[head - 1].first, y, partStack[head].first, x, cmp);
            partStack[head - 1].second += partStack[head].second;
            partStack.erase(partStack.begin() + head);
        }
        else
        {
            mergeLinkedListIndices(list, partStack[head - 2].first, z, partStack[head - 1].first, y, cmp);
            partStack[head - 2].second += partStack[head - 1].second;
            partStack.erase(partStack.begin() + head - 1);
        }
    }
    if (partStack.size() > 1)
    {
        mergeLinkedListIndices(list, 0, partStack[0].second, partStack[1].first, partStack[1].second, cmp);
    }
}
