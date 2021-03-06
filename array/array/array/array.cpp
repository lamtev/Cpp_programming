#include "array.h"

// i -- не очень хорошее название.
// лучше -- initial capacity.
// size -- это то, сколько элементов В ДАННЫЙ МОМЕНТ в массиве.
// А при создании массива таким способом, в нём нет наших элементов. Есть мусор -- но это не в счет.
// size = 0;
// в конструкторах лучше пользоваться списками инициализации:
// array::array(int initial_capaity) : capacity(initial_capacity), size(0) {
//  arr = new int[capacity];
//}
array::array(int i) {
    size = memory = i;
    arr = new int[size];
}

array::~array() {
    delete[] arr;
    //это же для тестирования?
    //деструктор работает, можно убрать этот вывод
    std::cout << "The Array destroyed!";
}

void array::add(int add_element) {
    // size++; - более коротко и болеее распространено.
    // если больше нравится, как ты сделал -- оставляй.
    // но я просто проконтатировал как есть в реальности.
    size += 1;
    if(size == memory) { // if size == capacity
        int array[size*K];
        memory = memory * K; // короче и популярнее -- memory *= K;
        for(int i = 0; i < size; i++) {
            array[i] = *(arr+i);
        }
        array[size-1] = add_element;
        delete[] arr;
        // здесь ты делаешь лишние действия. ты уже выделил память для array.
        // достаточно, чтобы arr ссылался на память выделенную под array.
        // но в таком случае надо выделять память под array динамически (тут я не уверен).
        arr = new int[size];
        for(int i = 0; i < size; i++)
            *(arr+i) = array[i];
    } else {
        *(arr+size-1) = add_element;
        memory += 1;
    }
    // я если честно до конца и не понял, что означает у тебя size. Похоже что ты их путаешь с memory(capacity) переодически.
}

// Я бы сделал так:

//void array::add(int element) {
//   if (size == capacity) {
//       growUp();
//   }
//   //т.к. индексация в массиве с 0, то последний элемент всегда с индеком size - 1.
//   //добавили новый элемент и их стало size+1, индекс последнего -- size.
//   //строчкой ниже сначала происходит обращение к arr[size], а потом size инкрементится.
//   //на всякий случай прокомментировал. думаю, ты и так это знаешь скорее всего.
//   arr[size++] = element;
//}

// этот метод надо добавить как закрытый в объявление класса в хэдере.
//void array::growUp() {
//    capacity *= K;
//    int *newArray = new int[capacity];
//    for (int i = 0; i < size; ++i) {
//        newArray[i] = arr[i];
//    }
//    delete[] arr;
//    arr = newArray;
//}



// Тут плохо, что у тебя происходит input/output из и в стандартный поток ввода/вывода.
// если это тебе помогало отлаживать, тогда ладно. хотя отлаживать надо через дебаггер.

// Тут бесспорно должна быть проверка на  соответствие индекса размеру.
// но индекс не может быть еще и равен размеру. этот момент надо исправить.

//если индекс не соответствует размеру, то можно бросать исключение. про исключения могу потом рассказать.

//реализовать укорачивание массива:
// когда capacity больше чем size в 4 раза, она должна уменьшиться в 2 раза.
void array::remove(int i) {
    if(i > size) {
        while(i > size) {
            std::cout << "Please repeat! ERROR[" << i << " > " <<  size << "]!" << std::endl;
            std::cout << "Enter element wich you want to delete: ";
            std::cin >> i;
        }
    }
    size -= 1;
    for(int k = i; k < size; k++) {
        //лучше пользоваться оператором индексирования []. на 2 символа короче и труднее накосячить.
        *(arr+k) = *(arr+k+1);
    }
}

// Пока пусть будет так, а потом научишься перегружать потоки вывода так, чтобы cout << array мог нормально и красиво вывести массив.
void array::print() {
    for(int i = 0; i < size; i++)
        std::cout << " [" << i <<"] "<< "Adress: "<< arr+i << " | Value: " << *(arr+i)  << std::endl;
    std::cout << "" <<  std::endl;
}
