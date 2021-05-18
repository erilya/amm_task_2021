#include <iostream>
#include <vector>

using namespace std;

struct Edge;
struct State;

vector<Edge*> edges;    // список всех возможных состояний
vector<State*> states;  // список всех возможных переходов

const int KV = 5;   // число интервалов по оси скорости
const int KH = 4;   // число интервалов по оси высоты

// Вершина графа состояний, описывающее состояние
struct State
{
    int v;  // скорость
    int h;  // высота
    vector<Edge*> edges;    // возможные переходы в другие состояния

    State(int V, int H)
    {
        v = V;
        h = H;
    }
};

// Ребро графа, описывающее переход из одного состояния в другое
struct Edge
{
    int node1;  // номер первого состояния
    int node2;  // номер второго состояния
    int cost;   // затраты топлива на переход из одного состояния в другое

    Edge(int v1, int h1, int v2, int h2, int c)
    {
        node1 = v1 * (KH + 1) + h1;
        node2 = v2 * (KH + 1) + h2;
        cost = c;
        states[node1]->edges.push_back(this);
    }
};

// Последовательность точек лучшего маршрута
vector<State*> min_route;
// Затраты топлива (инициализируем большим числом)
int min_cost = 100000;

void min_route_rec(vector<State*> &route, int &cost, State* s1)
{
    State* s0 = route.back();   // текущее состояние - последнее в текущем маршруте
    // Если текущее состояние - заданное конечное (целевое)
    if (s0 == s1)
    {
        // запоминаем маршрут, если его стоимость меньше уже найденных
        if (cost < min_cost)
        {
            min_route = route;
            min_cost = cost;
        }
    }
    else
        // Иначе, начинаем перебор переходов из текущего состояния в следующее
        for (int i = 0; i < s0->edges.size(); i++)
        {
            // Добавляем к маршруту следующее состояние и стоимость перехода в него
            cost += s0->edges[i]->cost;
            route.push_back(states[s0->edges[i]->node2]);
            // Продолжаем поиск в глубину
            min_route_rec(route, cost, s1);
            // Перед переходом к следующему состоянию, удаляем добавленное состояние и стоимость перехода в него
            cost -= s0->edges[i]->cost;
            route.pop_back();
        }
}

// Поиск пути с наименьшими затратами горючего
// Перебор всех возможных маршрутов от начальной к конечной точке
// и выбор маршрута с наименьшей затратой топлива
void minRoute(State* s0, State* s1)
{
    // текущий маршрут (последовательность состояний, начиная с s0)
    vector<State*> route;
    route.push_back(s0);
    int cost = 0;   // стоимость текущего маршрута
    // вызов рекурсивной функции поиска следующей точки маршрута
    min_route_rec(route, cost, s1);
}

// Вывод на экран точек маршрута
void printRoute(vector<State*> route)
{
    for (int i = 0; i < route.size(); i++)
        cout << "v=" << route[i]->v << "\th=" << route[i]->h << endl;
}

int main()
{
    int a, b, c, d;
    // Вариант а
  //  a = 2; b = 5; c = -5; d = -3;
    // Вариант б
//    a = 5; b = 1; c = -5; d = 3;
    // Вариант в
//    a = 3; b = -2; c = 5; d = -3;
    // Вариант г
    a = 4; b = 2; c = 5; d = 3;

    // 1. Задаём сетку состояний (номера узлов)
    // 1.1. Задаем все возможные состояния
    for (int v = 0; v <= KV; v++)
        for (int h = 0; h <= KH; h++)
            states.push_back(new State(v, h));

    // 2.2. Задаем все возможные переходы между состояниями
    // Вертикальные переходы для v = 0
    edges.push_back(new Edge(0, 0, 0, 1, 18+c));
    edges.push_back(new Edge(0, 1, 0, 2, 22+d));
    edges.push_back(new Edge(0, 2, 0, 3, 25+c));
    edges.push_back(new Edge(0, 3, 0, 4, 18));
    // Диагональные переходы между v = 0 и v = 1
    edges.push_back(new Edge(0, 0, 1, 1, 17+a));
    edges.push_back(new Edge(0, 1, 1, 2, 21));
    edges.push_back(new Edge(0, 2, 1, 3, 17));
    edges.push_back(new Edge(0, 3, 1, 4, 14+a));
    // Горизонатльные переходы между v = 0 и v = 1
    edges.push_back(new Edge(0, 0, 1, 0, 21));
    edges.push_back(new Edge(0, 1, 1, 1, 23));
    edges.push_back(new Edge(0, 2, 1, 2, 13));
    edges.push_back(new Edge(0, 3, 1, 3, 13));
    edges.push_back(new Edge(0, 4, 1, 4, 12));

    // Вертикальные переходы для v = 1
    edges.push_back(new Edge(1, 0, 1, 1, 18));
    edges.push_back(new Edge(1, 1, 1, 2, 20));
    edges.push_back(new Edge(1, 2, 1, 3, 24));
    edges.push_back(new Edge(1, 3, 1, 4, 16));
    // Диагональные переходы между v = 1 и v = 2
    edges.push_back(new Edge(1, 0, 2, 1, 21));
    edges.push_back(new Edge(1, 1, 2, 2, 20));
    edges.push_back(new Edge(1, 2, 2, 3, 13+b));
    edges.push_back(new Edge(1, 3, 2, 4, 19));
    // Горизонатльные переходы между v = 1 и v = 2
    edges.push_back(new Edge(1, 0, 2, 0, 11));
    edges.push_back(new Edge(1, 1, 2, 1, 17));
    edges.push_back(new Edge(1, 2, 2, 2, 21));
    edges.push_back(new Edge(1, 3, 2, 3, 16));
    edges.push_back(new Edge(1, 4, 2, 4, 15));

    // Вертикальные переходы для v = 2
    edges.push_back(new Edge(2, 0, 2, 1, 20));
    edges.push_back(new Edge(2, 1, 2, 2, 16));
    edges.push_back(new Edge(2, 2, 2, 3, 12+b));
    edges.push_back(new Edge(2, 3, 2, 4, 21));
    // Диагональные переходы между v = 2 и v = 3
    edges.push_back(new Edge(2, 0, 3, 1, 16));
    edges.push_back(new Edge(2, 1, 3, 2, 14+a));
    edges.push_back(new Edge(2, 2, 3, 3, 17+b));
    edges.push_back(new Edge(2, 3, 3, 4, 10+a));
    // Горизонатльные переходы между v = 2 и v = 3
    edges.push_back(new Edge(2, 0, 3, 0, 23));
    edges.push_back(new Edge(2, 1, 3, 1, 15));
    edges.push_back(new Edge(2, 2, 3, 2, 22));
    edges.push_back(new Edge(2, 3, 3, 3, 12));
    edges.push_back(new Edge(2, 4, 3, 4, 12));

    // Вертикальные переходы для v = 3
    edges.push_back(new Edge(3, 0, 3, 1, 17));
    edges.push_back(new Edge(3, 1, 3, 2, 15));
    edges.push_back(new Edge(3, 2, 3, 3, 15));
    edges.push_back(new Edge(3, 3, 3, 4, 15));
    // Диагональные переходы между v = 3 и v = 4
    edges.push_back(new Edge(3, 0, 4, 1, 15));
    edges.push_back(new Edge(3, 1, 4, 2, 12));
    edges.push_back(new Edge(3, 2, 4, 3, 18));
    edges.push_back(new Edge(3, 3, 4, 4, 9+a));
    // Горизонатльные переходы между v = 3 и v = 4
    edges.push_back(new Edge(3, 0, 4, 0, 19));
    edges.push_back(new Edge(3, 1, 4, 1, 14));
    edges.push_back(new Edge(3, 2, 4, 2, 12));
    edges.push_back(new Edge(3, 3, 4, 3, 12));
    edges.push_back(new Edge(3, 4, 4, 4, 16));

    // Вертикальные переходы для v = 4
    edges.push_back(new Edge(4, 0, 4, 1, 12));
    edges.push_back(new Edge(4, 1, 4, 2, 20));
    edges.push_back(new Edge(4, 2, 4, 3, 15+b));
    edges.push_back(new Edge(4, 3, 4, 4, 21));
    // Диагональные переходы между v = 4 и v = 5
    edges.push_back(new Edge(4, 0, 5, 1, 15));
    edges.push_back(new Edge(4, 1, 5, 2, 12));
    edges.push_back(new Edge(4, 2, 5, 3, 18));
    edges.push_back(new Edge(4, 3, 5, 4, 19));
    // Горизонатльные переходы между v = 4 и v = 5
    edges.push_back(new Edge(4, 0, 5, 0, 19));
    edges.push_back(new Edge(4, 1, 5, 1, 14));
    edges.push_back(new Edge(4, 2, 5, 2, 12));
    edges.push_back(new Edge(4, 3, 5, 3, 12));
    edges.push_back(new Edge(4, 4, 5, 4, 16+d));

    // Вертикальные переходы для v = 5
    edges.push_back(new Edge(5, 0, 5, 1, 12));
    edges.push_back(new Edge(5, 1, 5, 2, 20));
    edges.push_back(new Edge(5, 2, 5, 3, 15+a));
    edges.push_back(new Edge(5, 3, 5, 4, 21+c));

    // Вызываем функцию поиска лучшего маршрута
    minRoute(states.front(), states.back());

    // Выводим затраты топлива и точки наилучшего маршрута
    std::cout << "Min route cost " << min_cost << endl;
    std::cout << "Min route is " << endl;
    printRoute(min_route);

    return 0;
}
