# Graphs (Графи)

## Какво е граф?

**Графът** е нелинейна структура от данни - формално наредена двойка \( G = (V, E) \), където:
- \( V \) е множество от върхове (vertices или nodes)
- \( E \) е множество от ребра (edges), които свързват върховете

За разлика от дърветата, графите могат да имат *цикли* - пътища, които се връщат към началния възел. Също така, между два върха може да има повече от един път.


## Основна терминология

- **Vertex/Node (Връх/Възел):** Елемент от множеството \( V \). Представлява обект или състояние.
- **Edge (Ребро):** Елемент от множеството \( E \). Представлява връзка между два върха.
- **Degree (Степен):** Броят на ребрата, свързани с даден връх.
- **Path (Път):** Последователност от върхове, където всеки два съседни върха са свързани с ребро.
- **Cycle (Цикъл):** Път, който започва и завършва в същия връх.
- **Connected Graph (Свързан граф):** Граф, в който има път между всяка двойка върхове.
- **Weighted Graph (Претеглен граф):** Граф, в който всяко ребро има асоциирана числова стойност (тегло).
- **Adjacent (Съседни):** Два върха са съседни, ако има ребро между тях.

![Graph Example](https://www.simplilearn.com/ice9/free_resources_article_thumb/Graph%20Data%20Structure%20-%20Soni/what-is-graphs-in-data-structure.png)

## Видове графи

### Directed Graph (Насочен граф)

Графът, в който ребрата имат посока. Ребро от връх A към връх B **не означава**, че има ребро от B към A.

**Примери за приложение:**
- Уеб страници и линкове
- Зависимости между задачи (task scheduling)
- Граф на извикванията между функции

![Directed Graph](https://miro.medium.com/v2/resize:fit:808/1*cG2UslJocpM6KCpTWDpr-A.gif)

### Undirected Graph (Ненасочен граф)

Графът, в който ребрата са двупосочни. Ако има ребро между A и B, можем да се движим и в двете посоки.

**Примери за приложение:**
- Социални мрежи (приятелство)
- Пътна карта между градове
- Компютърна мрежа

![Undirected Graph](https://study.com/cimages/multimages/16/undirected_graph7121133166907396118.png)

### Weighted Graph (Теглови граф)

Графът, в който всяко ребро има асоциирано тегло (цена, разстояние, време и т.н.). Може да бъде насочен или ненасочен.

**Примери за приложение:**
- Навигация (разстояния между градове)
- Мрежови протоколи (цена на трансфер)
- Игрови механики (cost на движение)

![Weighted Graph](https://media.geeksforgeeks.org/wp-content/uploads/graphhh.png)

## Репрезентиране на графи в C++

Има два основни начина за представяне на графи в паметта:

### 1. Adjacency Matrix (Матрица на съседство)

Използва двумерна матрица `matrix[i][j]`, където:
- За ненасочен граф: `matrix[i][j] = 1` ако има ребро между върхове `i` и `j`, иначе `0`
- За претеглен граф: `matrix[i][j]` съдържа теглото на реброто или специална стойност ако няма ребро

```cpp
class GraphMatrix {
private:
    std::vector<std::vector<int>> matrix;
    int vertices;
    bool directed;

public:
    GraphMatrix(int v, bool isDirected = false) 
        : vertices(v), directed(isDirected) {
        matrix.resize(v, std::vector<int>(v, 0));
    }

    void addEdge(int from, int to, int weight = 1) {
        matrix[from][to] = weight;
        if (!directed) {
            matrix[to][from] = weight;
        }
    }

    bool hasEdge(int from, int to) const {
        return matrix[from][to] != 0;
    }

    std::vector<int> getNeighbors(int vertex) const {
        std::vector<int> neighbors;
        for (int i = 0; i < vertices; ++i) {
            if (matrix[vertex][i] != 0) {
                neighbors.push_back(i);
            }
        }
        return neighbors;
    }
};
```

**Предимства:**
- Проверката дали има ребро между два върха е `O(1)`
- Добра за **плътни графи** (dense graphs) - когато има много ребра
- Лесна за имплементация

**Недостатъци:**
- Заема `O(V²)` памет, където `V` е броят върхове
- Намирането на всички съседи на връх е `O(V)`
- Неефективна за **разредени графи** - когато има малко ребра

![Adjacency Matrix](https://media.geeksforgeeks.org/wp-content/uploads/20200604170814/add-and-remove-edge-in-adjacency-matrix-representation-initial1.jpg)

### 2. Adjacency List (Списък на съседство)

Използва масив/вектор от списъци. За всеки връх се пази списък с неговите съседи.

```cpp
class GraphList {
private:
    std::vector<std::vector<int>> adjList;
    int vertices;
    bool directed;

public:
    GraphList(int v, bool isDirected = false) 
        : vertices(v), directed(isDirected) {
        adjList.resize(v);
    }

    void addEdge(int from, int to) {
        adjList[from].push_back(to);
        if (!directed) {
            adjList[to].push_back(from);
        }
    }

    const std::vector<int>& getNeighbors(int vertex) const {
        return adjList[vertex];
    }

    bool hasEdge(int from, int to) const {
        auto& neighbors = adjList[from];
        return std::find(neighbors.begin(), neighbors.end(), to) 
               != neighbors.end();
    }
};
```

**За теглови граф:**

```cpp
struct Edge {
    int to;
    int weight;
    
    Edge(int t, int w) : to(t), weight(w) {}
};

class WeightedGraphList {
private:
    std::vector<std::vector<Edge>> adjList;
    int vertices;
    bool directed;

public:
    WeightedGraphList(int v, bool isDirected = false) 
        : vertices(v), directed(isDirected) {
        adjList.resize(v);
    }

    void addEdge(int from, int to, int weight) {
        adjList[from].emplace_back(to, weight);
        if (!directed) {
            adjList[to].emplace_back(from, weight);
        }
    }

    const std::vector<Edge>& getNeighbors(int vertex) const {
        return adjList[vertex];
    }
};
```

**Предимства:**
- Заема `O(V + E)` памет, където `V` е броят върхове и `E` е броят ребра
- Отлична за **разредени графи** (sparse graphs)
- Намирането на всички съседи е `O(degree(v))` - много бързо
- Най-често използваният метод в практиката

**Недостатъци:**
- Проверката дали има ребро между два върха е `O(degree(v))`
- Леко по-сложна за имплементация

![Adjacency List](https://www.computersciencebytes.com/wp-content/uploads/2017/06/adjacency_list.png)

### Сравнение

| Операция | Adjacency Matrix | Adjacency List |
|----------|------------------|----------------|
| Памет | O(V²) | O(V + E) |
| Добавяне на ребро | O(1) | O(1) |
| Проверка за ребро | O(1) | O(degree(v)) |
| Намиране на съседи | O(V) | O(degree(v)) |
| Обхождане на графа | O(V²) | O(V + E) |

**Избор на репрезентация:**
- Матрица: за плътни графи или когато често проверяваме за конкретни ребра
- Списък: за разредени графи (най-честият случай) или когато често обхождаме графа

## Алгоритми за обхождане на графи

### Breadth-First Search (BFS) - Обхождане на ширина

BFS обхожда графа **ниво по ниво** - първо всички върхове на разстояние 1 от началния връх, после всички на разстояние 2 и т.н.

**Стъпки:**

1. Добави началния връх в опашката и го маркирай като посетен.
2. Докато опашката не е празна:
   - Извади връх от началото на опашката
   - Обработи върха
   - Добави всички негови непосетени съседи в опашката и ги маркирай като посетени

**Приложения:**
- Намиране на **най-късия път** в неутежнен граф
- Проверка дали граф е свързан
- Проверка дали граф е двуделен (bipartite)
- Намиране на всички върхове на дадено разстояние

**Сложност:** `O(V + E)` за списък на съседство, `O(V²)` за матрица

### Depth-First Search (DFS) - Обхождане на дълбочина

DFS обхожда графа, като следва един път възможно най-дълбоко, преди да се върне назад (backtracking).

**Стъпки (рекурсивна версия):**

1. Маркирай текущия връх като посетен
2. Обработи върха
3. За всеки непосетен съсед, извикай рекурсивно DFS

**Приложения:**
- Откриване на **цикли** в граф
- **Топологично сортиране** (за DAG)
- Намиране на **силно свързани компоненти**
- Решаване на лабиринти и пъзели
- Проверка на свързаност

**Сложност:** `O(V + E)` за списък на съседство, `O(V²)` за матрица

### BFS vs DFS

| Характеристика | BFS | DFS |
|----------------|-----|-----|
| Структура данни | Опашка (Queue) | Стек (Stack) / Рекурсия |
| Памет | O(V) | O(V) |
| Път | Най-къс | Не гарантира най-къс |
| Приложение | Най-къс път | Цикли, топологично сортиране |
| Имплементация | Итеративна | Рекурсивна или итеративна |

## Специализирани алгоритми (За любопитни)

### Най-късият път (Shortest Path)

[**Dijkstra's Algorithm:**](https://www.youtube.com/watch?v=_lHSawdgXpI) Намира най-късия път от даден връх до всички останали в **претеглен граф без отрицателни тегла**.

[**Bellman-Ford Algorithm:**](https://www.youtube.com/watch?v=obWXjtg0L64) Намира най-късия път дори когато има **отрицателни тегла** (но не отрицателни цикли).

[**Floyd-Warshall Algorithm:**](https://www.youtube.com/watch?v=sLg6Leb-xt0) Намира най-късите пътища между **всички двойки върхове**.

