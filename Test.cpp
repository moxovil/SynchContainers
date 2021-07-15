// Тестовое задание TrueConf
// 1.заполнить случайными числами от 1 до 9 значения контейнеров vector[i] и map[i];
// 2.удалить случайное число элементов(не более 15) в каждом контейнере;
// 3.после этого провести синхронизацию, чтобы в vector и map остались только имеющиеся в обоих контейнерах элементы(дубликаты не удалять).

#include <iostream>
#include <vector>
#include <map>
#include <random>

//Объявление контейнеров vector[i] и map[i]
std::vector<int> v1;
std::map<int, int> c1;

//Задаем размер контейнеров
const int len = 20;

//Вспомогательная функция вывода значений контейнера std::vector<int>
void print_container(std::vector<int> v)
{
    std::cout << "vec[i]: ";

    for (auto& _v : v) {
        std::cout << _v << " ";
    }

    std::cout << std::endl;
}

//Вспомогательная функция вывода значений контейнера std::map<int,int>
void print_container(std::map<int,int> c)
{
    std::cout << "map[i]: ";

    auto _it = c.begin();

    for (; _it != c.end(); _it++) {
        std::cout << _it->second << " ";
    }

    std::cout << std::endl;
}

// Равномерное распределение в диапазоне [min,max]
std::random_device random_device;
std::mt19937 generator(random_device());
int getRandomNumber(int min, int max)
{ 
    std::uniform_int_distribution<> distribution(min, max);
    return distribution(generator);
}

//Cинхронизация элементов контейнеров vector[i] и map[i]
void synchronize(std::vector<int>& _vector, std::map<int,int>& _map)
{
    auto it = _map.begin();
    while (it != _map.end()) {
        auto c = it;
        it++;
        if (std::find(_vector.begin(), _vector.end(), c->second) == _vector.end()) {
            _map.erase(c);
        }
    }

    auto newEnd = std::remove_if(_vector.begin(), _vector.end(), [_map](int x) {
        auto it = _map.begin();
        for (; it != _map.end(); it++) {
            if (it->second == x) {
                return false;
            }
        }
        return true;
        });
    _vector.erase(newEnd, _vector.end());
}

int main()
{  
    //1.заполнить случайными числами от 1 до 9 значения контейнеров vector[i] и map[i];
    for (int i = 0; i < len; i++) {
        v1.push_back(getRandomNumber(1,9));
        c1[i] = getRandomNumber(1,9);
    }

    print_container(v1);
    print_container(c1);
    std::cout << std::endl;

    //2.удалить случайное число элементов(не более 15) в каждом контейнере;
    int a = getRandomNumber(1, 15);
    std::cout << "Delete " << a << " values" << std::endl;
    for (int i = 0; i < a; i++) {
        v1.erase(v1.begin() + getRandomNumber(0, v1.size()-1));
        auto it = c1.begin();
        std::advance(it, getRandomNumber(0, c1.size() - 1));
        c1.erase(it);
    }

    print_container(v1);
    print_container(c1);
    std::cout << std::endl;

    //3.после этого провести синхронизацию, чтобы в vector и map остались только имеющиеся в обоих контейнерах элементы(дубликаты не удалять).
    synchronize(v1, c1);

    print_container(v1);
    print_container(c1);
    std::cout << std::endl;
}