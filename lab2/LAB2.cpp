#include "timsort.h"
#include <cstdlib>
#include <ctime>

int intSqrCmp(const void* a, const void* b)
{
    const int first = *static_cast<const int*>(a);
    const int second = *static_cast<const int*>(b);

    return second * second != first * first ? first * first - second * second : second - first;
}

int main() {
    std::srand(static_cast<unsigned>(std::time(0)));

    DoubleLinkedList<int> list;
    for (int i = 0; i < 300; ++i) {
        list.append(std::rand() % 10000);
    }

    std::cout << "Original List: ";
    list.display();

    timSort(list, intSqrCmp);
    
    std::cout << std::endl << "Sorted List: ";
    list.display();

    return 0;
}
