# Двусвързан списък (Doubly Linked List)

## Какво е Двусвързан списък?

**Двусвързан списък** е линейна структура от данни, подобна на едносвързания списък, но с една ключова разлика: всеки елемент (възел) съдържа указател не само към следващия елемент, но и към **предишния**.

Това позволява обхождане на списъка в **двете посоки** - напред и назад.

Всеки възел в двусвързания списък се състои от три части:
1.  **Data** - данните, които се съхраняват.
2.  **Next Pointer** (`next`) - указател към следващия възел в списъка.
3.  **Previous Pointer** (`prev`) - указател към предишния възел в списъка.

![Doubly Linked List Structure](https://media.geeksforgeeks.org/wp-content/cdn-uploads/gq/2014/03/DLL1.png)
## Структура на възела (Node)

```cpp
template <typename T>
struct Node {
    T data;
    Node* prev;
    Node* next;

    Node(const T& data) : data(data) {}
};
```

## Имплементация със Sentinel (пазещ) възел

За да се опрости кодът и да се премахнат специалните случаи (празен списък, добавяне/премахване в краищата), често се използва **sentinel** (или "dummy") възел.

**Концепция:**
1.  Създава се един специален възел (`sentinel`), който винаги съществува, дори когато списъкът е празен.
2.  В празен списък, `sentinel->next` и `sentinel->prev` сочат към самия него, образувайки кръг.
3.  `sentinel` възелът **не съхранява потребителски данни**. Той служи само като маркер за началото и края.
4.  Първият реален елемент е `sentinel->next`, а последният е `sentinel->prev`.

```cpp
struct DoublyLinkedList {
    Node sentinel;
    DoublyLinkedList() {
        sentinel.next = sentinel.prev = &sentinel;
    }
};
```


**Предимства:**
-   **Няма специален случай за празен списък.** Операциите `push_front` и `push_back` работят по един и същи начин, без проверки `if (head == nullptr)`.
-   **Всяко добавяне и премахване се случва между два съществуващи възела.** Например, `push_front` е просто `insert_after(sentinel, element)`.
-   Кодът става по-чист и по-къс.

```cpp
// With sentinel node
T List<T>::pop_at(iterator& it) {
    T data = *it;
    // Sentinel allows for such symmetrical solutions
    it.current->prev->next = it.current->next;
    it.current->next->prev = it.current->prev;
    delete it.current;
    return data;
}

// Without sentinel node
T List<T>::pop_at(iterator& it) {
    T data = *it;
    if (it.current == head) {
        head = head->next;
        if (head) head->prev = nullptr;
    } else {
        it.current->prev->next = it.current->next;
        if (it.current->next)
            it.current->next->prev = it.current->prev;
    }
    delete it.current;
    return data;
}
```

Не е нужно да пазим отделни указатели `head` и `tail`, защото те са винаги достъпни чрез `sentinel->next` и `sentinel->prev`.

![Doubly Linked List with Sentinel](https://www.cs.dartmouth.edu/~scot/cs10/lectures/6/insert-into-nonempty-DLL.gif)
## Сравнение: Едносвързан vs. Двусвързан списък

| Характеристика | Едносвързан списък (Singly Linked List) | Двусвързан списък (Doubly Linked List) |
| :--- | :--- | :--- |
| **Памет** | По-малко памет на възел (само `next` указател). | Повече памет на възел (`next` и `prev` указатели). |
| **Обхождане** | Само напред. | Напред и назад. |
| **`pop_back()`** | `O(n)` - изисква обхождане до предпоследния елемент. | `O(1)` - директно достъпваме последния и предпоследния. |
| **`insert_before(node)`** | `O(n)` - трябва да намерим възела преди `node`. | `O(1)` - използваме `node->prev`. |
| **Сложност на имплементация** | По-проста. | Малко по-сложна заради управлението на два указателя. |
| **Приложения** | Имплементация на стек, опашка; прости случаи. | LRU кеш, browser history, undo/redo, имплементация на deque. |

## Сложност на операциите

| Операция | Средна сложност | Най-лоша сложност |
| :--- | :--- | :--- |
| **Достъп (Access)** | `O(n)` | `O(n)` |
| **Търсене (Search)** | `O(n)` | `O(n)` |
| **Добавяне (Insertion)** | `O(1)`* | `O(1)`* |
| **Премахване (Deletion)** | `O(1)`* | `O(1)`* |

\*Операциите за добавяне и премахване са `O(1)`, ако имаме указател към възела, преди/след който искаме да извършим операцията. Намирането на този възел е `O(n)`.

## Приложения на Двусвързан списък

2.  **LRU (Least Recently Used) Cache** - двусвързан списък и хеш-таблица се комбинират, за да се преместват наскоро използвани елементи в началото на списъка за `O(1)`.
3.  **Undo/Redo функционалност** - всяко действие се добавя в списък. "Undo" връща `prev` елемента, а "Redo" отива към `next`.
4.  **Имплементация на други структури** - `Deque` може да се имплементира като адаптер на двусвързан списък.

## Задачи от LeetCode и Hackerrank


-   [**Reverse a Doubly Linked List**](https://www.hackerrank.com/challenges/reverse-a-doubly-linked-list/problem)
-   [**Design Browser History**](https://leetcode.com/problems/design-browser-history/)
-   [**Flatten a Multilevel Doubly Linked List**](https://leetcode.com/problems/flatten-a-multilevel-doubly-linked-list/)

## Полезни ресурси

-   [**For each generation in c++ (requested during class)**](https://stackoverflow.com/questions/8164567/how-to-make-my-custom-type-to-work-with-range-based-for-loops)
-   [**cppreference - std::forward_list**](https://en.cppreference.com/w/cpp/container/forward_list)
