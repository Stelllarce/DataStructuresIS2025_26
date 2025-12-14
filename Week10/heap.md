# Heap (Пирамида)

## Какво е Heap?

**Heap (Пирамида)** е специализирана дървовидна структура от данни, която удовлетворява свойството на пирамидата. Обикновено се реализира като **двоично дърво**, което е **почти пълно**.

В пирамидата, за всеки възел `P` и неговите деца `C`, е в сила едно от следните условия:

- **Max-Heap:** Стойността на `P` е по-голяма или равна на стойността на `C`. Най-големият елемент е в корена.
- **Min-Heap:** Стойността на `P` е по-малка или равна на стойността на `C`. Най-малкият елемент е в корена.

Тъй като пирамидата е почти пълно двоично дърво, тя може ефективно да се представи чрез **масив**.

![Heap array representation](https://ik.imagekit.io/upgrad1/abroad-images/imageCompo/images/H2_What_is_Heap_Sort_in_Data_StructuresBGXFFQ.png?pr-true)

## Представяне чрез масив

Ако индексираме възлите на дървото, започвайки от корена (индекс 0), за всеки възел на индекс `i`:

- **Ляво дете:** `2 * i + 1`
- **Дясно дете:** `2 * i + 2`
- **Родител:** `(i - 1) / 2`

![Heap Array Representation](https://media.geeksforgeeks.org/wp-content/uploads/20221126213302/MinHeapAndMaxHeap.png)

## Основни операции

Двете операции за поддържане на свойството на пирамидата са `heapifyUp` (изплуване) и `heapifyDown` (потъване).

### Heapify Up

Тази операция се използва при **добавяне (insert)** на нов елемент. Новият елемент се добавя в края на масива (като последно листо) и след това "изплува" нагоре, докато не заеме правилната си позиция, разменяйки се с родителя си, ако нарушава свойството на пирамидата.

```cpp
// Примерна имплементация за Max-Heap
void heapifyUp(std::vector<int>& heap, int index) {
    // Ако сме стигнали корена, спираме
    if (index == 0) return;

    int parentIndex = (index - 1) / 2;

    // Ако текущият елемент е по-голям от родителя си, разменяме ги
    if (heap[index] > heap[parentIndex]) {
        std::swap(heap[index], heap[parentIndex]);
        // Рекурсивно продължаваме нагоре
        heapifyUp(heap, parentIndex);
    }
}
```

### Heapify Down

Тази операция се използва при **премахване на корена (extract top)** или при построяване на пирамида (build heap). Коренът се премахва, а на негово място се слага последният елемент от масива. Този елемент след това "потъва" надолу, разменяйки се с по-голямото (при Max-Heap) или по-малкото (при Min-Heap) от децата си.

```cpp
// Примерна имплементация за Max-Heap
void heapifyDown(std::vector<int>& heap, int index) {
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;
    int largest = index;

    // Проверяваме дали лявото дете е по-голямо от текущия най-голям
    if (leftChild < heap.size() && heap[leftChild] > heap[largest]) {
        largest = leftChild;
    }

    // Проверяваме дали дясното дете е по-голямо от текущия най-голям
    if (rightChild < heap.size() && heap[rightChild] > heap[largest]) {
        largest = rightChild;
    }

    // Ако най-големият не е текущият възел, разменяме и продължаваме надолу
    if (largest != index) {
        std::swap(heap[index], heap[largest]);
        heapifyDown(heap, largest);
    }
}
```

## Сложност

| Операция | Сложност |
|----------|----------|
| Insert (Push) | `O(log n)` |
| Extract Top (Pop) | `O(log n)` |
| Peek (Top) | `O(1)` |
| Build Heap | `O(n)` |

## Задачи от LeetCode

- [**215. Kth Largest Element in an Array**](https://leetcode.com/problems/kth-largest-element-in-an-array/)
- [**347. Top K Frequent Elements**](https://leetcode.com/problems/top-k-frequent-elements/)
- [**621. Task Scheduler**](https://leetcode.com/problems/task-scheduler/description/?envType=problem-list-v2&envId=heap-priority-queue)
- [**703. Kth Largest Element in a Stream**](https://leetcode.com/problems/kth-largest-element-in-a-stream/)
- [**264. Ugly Number II**](https://leetcode.com/problems/ugly-number-ii/description/?envType=problem-list-v2&envId=heap-priority-queue)
