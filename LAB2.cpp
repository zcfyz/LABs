﻿#include "timsort.h"

int main() {
    DoubleLinkedList<int> arr;
    arr.append(5);
    arr.append(3);
    arr.append(8);
    arr.append(2);
    arr.append(1);
    arr.append(4);
    arr.append(6);
    arr.append(7);
    arr.append(13);
    arr.append(27);
    arr.append(100);

    timsort(arr);

    arr.display();

    return 0;
}
