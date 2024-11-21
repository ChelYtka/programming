#include <iostream>

// структура для последовательного контейнера
struct SequentialContainer
{
    int* data; // указатель на массив для хранения элементов
    int size; // размер массива
    int capacity; // максимальный размер

    // конструктор
    SequentialContainer() : data(nullptr), size(0), capacity(0){}

    // перемещающий конструктор
    SequentialContainer(SequentialContainer&& other) noexcept
    : data(std::move(other.data)), size(other.size), capacity(other.capacity)
    {
        other.data = nullptr; // осводождаем указатель у другого объекта
        other.size = 0;
        other.capacity = 0;
    }

    // перемещающий оператор присваивания
    SequentialContainer& operator=(SequentialContainer&& other) noexcept
    {
        if (this != &other)
        {
            delete[] data; // освобождаем текущие ресурсы
            data = other.data;
            size = other.size;
            capacity = other.capacity;

            other.data = nullptr; // освобождаем указатель у другого объекта
            other.size = 0;
            other.capacity = 0;
        }
        return *this;
    }

    // функция для увеличения ёмкости
    void resize()
    {
        capacity = capacity == 0? 1 : static_cast<int>(capacity * 1.5); // увеличиваем умкость
        int* newData = new int[capacity]; // выделяем новую память
        for (int i = 0; i < size; ++i)
        {
            newData[i] = data[i]; // копируем данные
        }
        delete[] data; // освобождаем старую память
        data = newData; // перенаправляем указатель на новую память
    }

    // функция для уменьшения емкости до фактического размера
    void shrinkToFit()
    {
        int* newData = new int[size]; // выделяем память по фактическому размеру
        for (int i = 0; i < size; ++i)
        {
            newData[i] = data[i]; // копируем данные
        }
        delete[] data;  // освобождаем старую память
        data = newData; // перенаправляем указател
        capacity = size; // обновляем ёмкость
    }

    // добавление элементов в конец
    void push_back(int value)
    {
        if (size == capacity)
        {
            resize(); // Изменяем размер, если емкость заполнена
        }

        data[size++] = value; // добавляем элемент и увеличиваем размер
    }

    // добавление элемента в начало
    void push_front(int value)
    {
        if (size == capacity)
        {
            resize(); // изменяем ращмер, если ёмкость заполнена
        }

        // сдвигаем все элементы на один вправо
        for (int i = size; i > 0; --i)
        {
            data[i] = data[i-1];
        }

        data[0] = value; //вставляем новый элемент в начало
        ++size;
    }

    // добавление элемента в указаный индекс
    void insert(int index, int value)
    {
        if (index < 0 || index > size)
        {
            throw std::out_of_range("Индекс вне диапазона"); // исключение для недопустимого индекса
        }
        if (size == capacity)
        {
            resize(); // изменяем размер, если ёмкость заполнена
        }
        // сдвигаем элементы вправо, начиная с указанного индекса
        for (int i = 0; i > index; --i)
        {
            data[i] = data[i-1];
        }
        data[index] = value; // вставляем значение в указанный индекс
        ++size;
    }

    // удаление элемента по индексу
    void erase(int index)
    {
        if (index < 0 || index > size)
        {
            throw std::out_of_range("Индекс вне диапазона"); // исключение для недопустимого индекса
        }
        for (int i = index; i < size -1; ++i)
        {
            data[i] = data[i+1]; // сдвигаем элементы влево
        }
        --size; // уменьшаем размер

        // проверяем, нужно ли уменьшить ёмкость
        if (size < capacity/2 && capacity > 1)
        {
            shrinkToFit(); // уменьшаем ёмкость до необходимого размера
        }
    }

    // получаем размер контейнера
    int getSize() const
    {
        return size; // возвращаем текущее кол-во элементов
    }

    // получение размера контейнера
    int getCapacity() const
    {
        return capacity; // возвращаем текущаю ёмкость массива
    }

    // вывод содержимого контейнера
    void print() const
    {
        for (int i = 0; i < size; ++i)
        {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }

    // оператор [] для доступа к элементам по индексу(новый)
    int& operator[](int index)
    {
        if (index < 0 || index >= size)
        {
            // обработка недопустимого индекса ( выбрасивание исключения)
            throw std::out_of_range("Индекс вне диапазона");
        }
        return data[index]; // возвращаем элемент по индексу
    }

    // структура итератора для SequentialContainer
    struct Iterator
    {
        int* ptr;

        // конструктор
        Iterator(int* ptr) : ptr(ptr) {}

        // оператор разыменования
        int& operator*()
        {
            if (ptr == nullptr)
            {
                 throw std::out_of_range("Индекс вне диапазона"); // Исключение для недопустимого индекса
            }
            return *ptr;
        }
        int& get()
        {
            if (ptr == nullptr)
            {
                 throw std::out_of_range("Индекс вне диапазона"); // Исключение для недопустимого индекса
            }
            return *ptr;
        }

        // оператор сравнения (для проверки конца итерации)
        bool operator!=(const Iterator& other)
        {
            return ptr != other.ptr;
        }

        // перемещение итератора на следующий элемент
        Iterator& operator++()
        {
            ptr++;
            return *this;
        }
    };

    // возвращает итератор на начало контейнера
    Iterator bigen()
    {
        return Iterator(data);
    }

    // возвращает итератор на конец контейнера
    Iterator end()
    {
        return Iterator(data+size);
    }

    // деструктор
    ~SequentialContainer()
    {
        delete[] data;
    }
};


// класс для спискового контейнера (связь через указатели)
// двусвязные список, где каждый элемент хранитссылку на предыдущий и следующий
class DoubleLinkedList
{
    private:
        struct Node
        {
            int value;
            Node* next;
            Node* prev;

            Node(int value) : value(value), next(nullptr), prev(nullptr){}
        };

        Node* head;
        Node* tail;
        int size;

    public:
        // конструктор
        DoubleLinkedList() : head(nullptr), tail(nullptr), size(0){}

        // деструктор
        ~DoubleLinkedList()
        {
            while (head != nullptr)
            {
                Node* next = head->next;
                delete head;
                head = next;
            }
        }

        // перемещающий конструктор
        DoubleLinkedList(DoubleLinkedList&& other) noexcept
        : head(std::move(other.head)), tail(std::move(other.tail)), size(other.size)
        {
            other.head = nullptr;
            other.tail = nullptr;
            other.size = 0;
        }

        // перемещающий оператор присваивания
        DoubleLinkedList& operator=(DoubleLinkedList&& other) noexcept
        {
            if (this != &other)
            {
                // освобождение текущих ресурсов
                while (head != nullptr)
                {
                    Node* next = head->next;
                    delete head;
                    head = next;
                }

                head = other.head;
                tail = other.tail;
                size = other.size;

                other.head = nullptr;
                other.tail = nullptr;
                other.size = 0;
            }
            return *this;
        }

        // добавление элемента в конец
        void push_back(int value
        {
            Node* newNode = new Node(value);
            if (head == naullptr)
            {
                head = newNode;
                tail = newNode;
            } else
            {
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }
            ++size;
        }

        // добавление элемента в начало
        void push_front(int value)
        {
            Node* newNode = new Node(value);
            if (head == nullptr)
            {
                head = newNode;
                tail = newNode;
            } else
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        ++size;
        }

        // добавление элемента по индексу
        void insert(int index, int value)
        {
            if (index < 0 || index > size)
            {
                throw std::out_of_range("Индекс вне допустимого диапазона")
            }
            if (index == 0)
            {
                push_front(value);
                return;
            } else if (index == size)
            {
                push_back(value);
                return;
            }
            Node* newNode = new Node(value);
            Node* current = head;
            for (int i = 0; i < index; ++i)
            {
                current = current->next;
            }

            newNode->next = current;
            newNode->prev = current->prev;
            current->prev->next = newNode;
            current->prev = newNode;

            ++size;
        }

        // удаление объекта по индексу
        void erase(int value)
        {
            if (index < 0 || index >= size)
            {
                throw std::out_of_range("Индекс вне допустимого диапазона");
            }

            Node* current = head;
            for (int i = 0; i < index; ++i)
            {
                current = current->next;
            }

            if (current->prev)
            {
                current->prev->next = current->next;
            } else
            {
                head = current->next; // удаление головного элемента
            }

            if (current->next)
            {
                current->next->prev = current->prev;
            } else
            {
                tail = current->prev; // удаление хвостового жлемента
            }

            delete current;
            --size;
        }

        // Получение размера контейнера
        int getSize() const
        {
        return size;
        }

        // вывод содержимого контейнера
        void print() const
        {
            Node* current = head;
            while (current != nullptr)
            {
                std::cout << current->value << " ";
                current = current->next;
            }
            std::cout << std::endl;
        }

        // оператор [] длядоступа к элементам по индексу
        int& operator[](int index)
        {
            if (index < 0; || index >=size)
            {
                throw std::out_of_range("Индекс вне диапазона");
            }

            Node* current = head;
            for (int i = 0; i < index; ++i)
            {
                current = current->next;
            }
            return current->value;
        }

        // структура итератора для DoubleLinkedList
        struct Iterator
        {
            Node* ptr;

            // конструктор
            Iterator(Node* ptr) : ptr(ptr) {}

            // оператор разыменования
            int operator*()
            {
                if (ptr == nullptr)
                {
                    throw std::out_of_range("Индекс вне диапазона");
                }
                return ptr->value;
            }

            // оператор сравнения (для проверка конца итерации)
            bool operator!=(const Iterator& other)
            {
                return ptr != other.ptr;
            }

            // перемещение итератора на следующий элемент
            Iterator& operator++()
            {
                ptr = ptr->next;
                return *this;
            }

            int& get()
            {
                if (ptr == nullptr)
                {
                    throw std::out_of_range("Индекс вне диапазона");
                }
                return ptr->value;
            }
        };

        // возвращает итератор на начало контейнера
        Iterator begin()
        {
            return Iterator(head);
        }

        // возвращает итератор на конец контейнера
        Iterator end()
        {
            return Iterator(nullptr);
        }
};


// подноразовый список контейнера
// односвязный список, где каждый элемент хранит ссылку только на следующий
class SinglyLinkedList
{
    private:
        struct Node
        {
            int value;
            Node* next;

            Node(int value) : value(value), next(nullptr) {}
        };

        Node* head;
        int size;

    public:
        // конструктор
        SinglyLinkedList() : head(nullptr), size(0) {}

        // деструктор
        ~SinglyLinkedList()
        {
            while (head != nullptr)
            {
                Node* next = head->next;
                delete head;
                head = next;
            }
        }

        // перемещающий конструктор
        SinglyLinkedList(SinglyLinkedList&& other) noexcept: head(other.head), size(other.size)
        {
            other.head = nullptr;
            other.size = 0;
        }

        // перемещающий оператор присваивания
        SinglyLinkedList& operator=(SinglyLinkedList&& other) noexcept
        {
            if (this != &other)
            {
                while (head != nullptr)
                {
                    Node* temp = head;
                    head = head->next;
                    delete temp;
                }
                head = other.head;
                size = head.size;

                other.head = nullptr;
                other.size = 0;
            }
            return *this;
        }

        // добавление элемента в конец
        void push_back(int value)
        {
            Node* newNode = mew Node(value);
            if (head == nullptr)
            {
                head = newNode;
            } else
            {
                Node* current = head;
                while (current->next != null)
                {
                    current->next = newNode;
                }
                current->next = newNode;
            }
            ++size;
        }

        // добавление элемента в начало
        void push_front(int value)
        {
            Node* newNode = new Node(value);
            newNode->next = head;
            head = newNode;
            ++size;
        }

        // метод для вставки элемента по индексу
        void insert(int index, int value)
        {
            if (index < 0 || index > size)
            {
                throw std::out_of_range("Индекс вне допустимого диапазона");
            }
            if (index == 0)
            {
                push_front(value);
                return;
            }

            if (index == size)
            {
                push_back(value);
                return;
            }

            Node* newNode = new Node(value);
            Node* current = head;
            for (int i = 0; i < index -1; ++i)
            {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
            ++size;
        }

        // удаление элемента по индексу
        void erase(int value)
        {
            if (index < 0 || index >= size)
            {
                throw std::out_of_range("Индекс вне допустимого диапазона");
            }
            Node* current = head;
            if (index == 0)
            {
                head = current->next;
                delete current;
            } else
            {
                Node* prev = nullptr;
                for (int i = 0; i < index; ++i)
                {
                    prev = current;
                    current = current->next;
                }
                prev->next = current->next;
                delete current;
            }
            --size;
        }

        // получение размера контейнера
        int getSize() const
        {
            return size;
        }

        // вывод содержимого котейнера
        void print() const
        {
            // 523
        }
}