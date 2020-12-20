#include <iostream>
#include <exception>  // logic_error
#include <cstring>    // memcpy
#include <ctime>      // clock
#include <cstdlib>    // rand
#include <string>    // rand
#include <fstream>    // files
#include <vector>    // vector

using namespace std;

inline void swap(int& a, int& b)
{
    int tmp = a; a = b; b = tmp;
}
//сортировка обменом
void sort_bubble(int* arr, size_t size)
{
    int dlina = size, ind{ 0 };

    while (ind < dlina - 1) {
        for (int i{ dlina - 1 }; i > ind; --i) {
            if (arr[i] < arr[i - 1]) {
                swap(arr[i], arr[i - 1]);
            }
        }
        ++ind;
    }
}
//шейкер-сортировка
void sort_shaker(int* arr, size_t size)
{
    int dlina = size, indLeft{ 0 }, indRight{dlina - 1};
    bool left{ true };

    while (!(indRight - indLeft == 1)) {
        //если идем слева
        if (left) {
            for (int i{ indLeft }; i < indRight; ++i) {
                if (arr[i] > arr[i + 1]) {
                    swap(arr[i], arr[i + 1]);
                }
            }
            left = false;
            --indRight;
        }
        //если идем справа
        else {
            for (int i{ indRight }; i > indLeft; --i) {
                if (arr[i] < arr[i - 1]) {
                    swap(arr[i], arr[i - 1]);
                }
            }
            left = true;
            ++indLeft;
        }
    }
}
//сортировка выбором
void sort_select(int* arr, size_t size)
{
    int dlina = size, ind{ 0 };
    
    while (ind < dlina - 1) {
        int min{INT16_MAX}, minInd{ 0 };

        for (int i{ind}; i < dlina; ++i) {
            if (arr[i] < min) {
                min = arr[i];
                minInd = i;
            }
        }
        swap(arr[ind], arr[minInd]);
        ++ind;
    }
}
//сортировка вставками
void sort_insert_lin(int* arr, size_t size)
{
    int dlina = size;

    for (int i{1}; i < dlina; ++i) {
        int ch = arr[i], ind{ i };
       
        for (int j{i - 1}; j >= 0; --j) {  
            //если число слева оказалось больше просматриваемого числа
            //то смещаю все до тех пор, пока число слева не будет меньше
            if (arr[j] > ch) {
                arr[ind] = arr[ind - 1];
                --ind;
            }  
        }
        //после всех перемещений вставляю на нужное место
        arr[ind] = ch;
    }
}
//сортировка Шелла (шаг = n / 2)
void sort_shell_div2(int* arr, size_t size)
{
    int dlina = size, step{ dlina / 2 };

    while (step >= 1) {
        for (int i{ 0 }; i < step; ++i) {
            int mainInd{ i }, ind{ mainInd + step };

            while (ind < dlina) {
                int ch = arr[ind];
                int prevInd = ind - step;

                //пока не дошли до начала отсортированной части и если
                //какой-то из предыдущих больше, то перезаписываем
                while ((prevInd >= mainInd) && (arr[prevInd] > ch)) {
                    arr[prevInd + step] = arr[prevInd];
                    prevInd -= step;
                }

                arr[prevInd + step] = ch;
                ind += step;
            }
        }
        step /= 2;
    }
}
//сортировка Шелла(шаг = n * 3 + 1)
void sort_shell_pow3(int* arr, size_t size)
{
    int dlina = size, step{1};
    //выбор шага
    while (step < dlina / 3) {
        step = 3 * step + 1;
    }
    
    while (step >= 1) {
        for (int i{0}; i < step; ++i) {
            int mainInd{ i }, ind{ mainInd + step };

            while (ind < dlina) {
                int ch = arr[ind];
                int prevInd = ind - step;
                
                //пока не дошли до начала отсортированной части и если
                //какой-то из предыдущих больше, то перезаписываем
                while ((prevInd >= mainInd) && (arr[prevInd] > ch)) {
                    arr[prevInd + step] = arr[prevInd];
                    prevInd -= step;
                }

                arr[prevInd + step] = ch;
                ind += step;
            }
        }
        step = (step - 1) / 3;
    }
}
//просеивание
void sift(int* arr, int indEl, int indLast) {
    while (indEl * 2 <= indLast) {
        //предполагаем, что сравнивать будем с левым потомком
        int ind{ indEl * 2 };
        //если левый потомок это не последний элемент (иначе выйдем за 
        //границы массива) и если левый потомок меньше правого потомка, 
        //то сравнивать будем с правым потомком
        if ((ind <= indLast - 1) && (arr[ind] < arr[ind + 1])) {
            ++ind;
        }
        //если элемент меньше того потомка, с которым сравниваем, меняем их
        if (arr[indEl] < arr[ind]) {
            swap(arr[indEl], arr[ind]);
            indEl = ind;
        }
        //если нет, остановить просеивание 
        else {
            return;
        }
    }
}
//пирамидальная сортировка
void sort_heap(int* arr, size_t size)
{
    int dlina = size, halfDlina{ (dlina / 2) - 1 }; 

    //просеивание от эл-та (dlina / 2) - 1 до начала массива
    while (halfDlina >= 0) {
        sift(arr, halfDlina, dlina - 1);
        --halfDlina;
    }

    int lastInd{ dlina - 1 };
    //идем до 1 элемента
    while (lastInd > 0) {
        swap(arr[0], arr[lastInd]);
        --lastInd;
        sift(arr, 0, lastInd);
    }
}
//быстрая сортировка(рекурсия)
void sort_quick_rec(int* arr, int size, int indLeft, int indRight)
{
    //допустим, пилотируемый элемент самый левый
    int left{indLeft}, right{indRight}, ch{ arr[left] };
    
    do {
        while (arr[left] < ch) {
            ++left;
        }

        while (arr[right] > ch) {
            --right;
        }

        if (left <= right) {
            if (left != right) {
                swap(arr[left], arr[right]);
            }
            ++left;
            --right;
        }
    } while (left <= right);
    //спуск
    if (left < indRight) {
        sort_quick_rec(arr, size, left, indRight);
    }   
    if (indLeft < right) {
        sort_quick_rec(arr, size, indLeft, right);
    }
}
//разделение и получение медианы
int separAndGetMed(int* arr, int indL, int indR) {
    int left = indL, right = indR, ch{ arr[left] };
    //допустим пилотируемый элемент самый левый
    //разделение
    while (left < right) {
        while ((arr[right] >= ch) && (left < right)) {
            right--;
        }
        if (left != right) {
            arr[left] = arr[right];
            left++;
        }
        while ((arr[left] <= ch) && (left < right)) {
            left++;
        }
        if (left != right) {
            arr[right] = arr[left];
            right--;
        }
    }
    //пилотируемый элемент вставляем на его место
    arr[left] = ch;
    //возвращаем медиану
    return left;
}
//быстрая сортировка(не рекурсия)
void sort_quick_nonrec(int* arr, size_t size)
{
    int dlina = size, ind{ 0 };
    //создаем вектор(чтобы сохранить нервы) медиан, 
    //по которому будем перемещаться и добавлять элементы
    vector<int> medians = { 0, dlina - 1 };

    while (ind < dlina) {
        //получаем медиану
        int left = medians[ind], right = medians[ind + 1],
            med = separAndGetMed(arr, left, right);
        if (med != left) {
          medians.emplace(medians.cbegin() + ind + 1, med);
        } //если медиана совпала с левым эл-ом значит он минимальный  
        else {
          //если это не соседние элементы
          if (left != right - 1) {
            ++med;
            //вставляем эту медиану
            medians.emplace(medians.cbegin() + ind + 1, med);
          } 
          //двигаемся к следующей медиане
          ++ind;
        }
    }
}
//сортировка просто многочисленным разделением
void separation_sort(int* arr, size_t size) {
    int dlina = size, ind{ 0 };

    while (ind != dlina - 1) {
        int left{ ind }, right{ dlina - 1 };
        //в результате самый наименьший элемент окажется слева
        while (left != right) {
            int med = separAndGetMed(arr, left, right);
            right = med;
        }
        //увеличиваем индекс, чтобы потом идти от минимального + 1
        ++ind;
    }
}
//слияние
void merge(int* arr1, size_t size1, int *arr2, size_t size2, int *arrRes)
{
    int dlina1 = size1, dlina2 = size2, ind1{ 0 }, ind2{ 0 }, indRez{0};
    //пока не вышли за границы одного из массивов
    while ((ind1 < dlina1) && (ind2 < dlina2))  {
        //если эл-т какого-то массива меньше эл-та другого массива, 
        //записываем его и сдвигаем границу этого же массива 
        if (arr1[ind1] <= arr2[ind2]) {
            arrRes[indRez] = arr1[ind1];
            ++ind1;
        }
        else {
            arrRes[indRez] = arr2[ind2];
            ++ind2;
        }
        ++indRez;
    }
    //если значения какого-то массива закончились, 
    //записываем хвост другого массива
    if (ind1 == dlina1) {
        for (int i{ind2}; i < dlina2; ++i) {
            arrRes[indRez] = arr2[i];
            ++indRez;
        }
    }
    if (ind2 == dlina2) {
        for (int i{ ind1 }; i < dlina1; ++i) {
            arrRes[indRez] = arr1[i];
            ++indRez;
        }
    }
}
//сортировка слиянием
void sort_merge(int* arr, int left, int right, int *arrZapas) {
    int M{ (left + right) / 2 };
    //спуск
    if (left < M) {
        sort_merge(arr, left, M, arrZapas);
    }
    if (M + 1 < right) {
        sort_merge(arr, M + 1, right, arrZapas);
    }
    //слияние
    merge(&arr[left], M - left + 1, &arr[M + 1], right - M, &arrZapas[left]);
    //копирование
    for (int i = left; i <= right; i++) {
        arr[i] = arrZapas[i];
    }
}

///////////////////////////////////////////////////////////////////////////////

static clock_t timer_start_time{ 0 }, timer_stop_time{ 0 };
void start_timer()
{
    timer_start_time = clock();
}
void stop_timer()
{
    timer_stop_time = clock();
    cout << double(timer_stop_time - timer_start_time) / CLOCKS_PER_SEC << " sec" << endl;
}

bool array_is_sorted(const int* arr, size_t size)
{
    for (size_t i{ 1 }; i < size; ++i) if (arr[i - 1] > arr[i]) return false;
    return true;
}

void exec_sort(const int* arr_unsorted, size_t size, void (*sort_function)(int*, size_t), const char* comment)
{
    cout << endl << comment << endl;
    int* arr = new int[size];
    memcpy(arr, arr_unsorted, size * sizeof(int));
    start_timer();
    sort_function(arr, size);
    stop_timer();
    if (!array_is_sorted(arr, size)) throw logic_error("FAILURE");
    delete[] arr;
}

int main() {
    try
    {
        size_t size{ 0 }; // size{ 5 };
        int* arr_unsorted{ nullptr };

        if (!size)
        {
            cout << "Array size?" << endl;
            if (!(cin >> size) || size <= 0 || size > 1000000000) throw logic_error("WRONG ARRAY SIZE");

            arr_unsorted = new int[size];
            srand(unsigned(time(nullptr)));

            for (size_t i = 0; i < size; arr_unsorted[i++] = rand() % size);
                        
            /*cout << "massiv: ";
            for (int i{0}; i < size; ++i) {
                cout << arr_unsorted[i] << " ";
            }
            cout << endl;*/
        }
        else
        {
            cout << "Array size:" << endl << size << endl;
            arr_unsorted = new int[5]{ 5, 4, 3, 2, 1 };
        }

        exec_sort(arr_unsorted, size, sort_bubble, "Bubble:");
        exec_sort(arr_unsorted, size, sort_shaker, "Shaker:");
        exec_sort(arr_unsorted, size, sort_select, "Select:");
        exec_sort( arr_unsorted, size, sort_insert_lin, "InsertLin:" );
        
        exec_sort(arr_unsorted, size, sort_shell_div2, "Shell/2:");
        exec_sort(arr_unsorted, size, sort_shell_pow3, "Shell^3:");
        exec_sort(arr_unsorted, size, sort_heap, "Heap:");
        exec_sort(arr_unsorted, size, sort_quick_nonrec, "Quick(nonrec):");
        exec_sort(arr_unsorted, size, separation_sort, "Separation:");
        
        cout << endl << "Quick(rec):" << endl;
        start_timer();
        sort_quick_rec(arr_unsorted, size, 0, size - 1);
        stop_timer();
        if (!array_is_sorted(arr_unsorted, size)) throw logic_error("FAILURE");

        cout << endl << "Merging:" << endl;
        int* masCopy = new int[size] {0};
        start_timer();
        sort_merge(arr_unsorted, 0, size - 1, masCopy);
        stop_timer();
        if (!array_is_sorted(arr_unsorted, size)) throw logic_error("FAILURE");

        //сортировка последовательностей из двух файлов и запись в один
        int mas1[13]{ 0 }, size1{13};
        fstream file1("file1.txt");
        string str{ "" };
        while (!file1.eof()) {
            string str1{ "" };
            file1 >> str1;
            str += str1 + ' ';
        }
        file1.close();
        int ind{ 0 }, indMas{ 0 };

        while (ind < str.size()) {
            string subStr{ "" };
            int step{ 1 };
            
            while (str[ind] != ' ') {
                subStr += str[ind];
                ++ind;
            }

            mas1[indMas] = stoi(subStr);
            ++indMas;
            ind += step;
        }
        
        int mas2[15]{ 0 }, size2{15};
        fstream file2("file2.txt");
        str = "";
        while (!file2.eof()) {
            string str1{ "" };
            file2 >> str1;
            str += str1 + ' ';
        }
        ind = 0, indMas = 0;

        while (ind < str.size()) {
            string subStr{ "" };
            int step{ 1 };

            while (str[ind] != ' ') {
                subStr += str[ind];
                ++ind;
            }

            mas2[indMas] = stoi(subStr);
            ++indMas;
            ind += step;
        }
        file2.close();
        
        int masResult[28]{ 0 };
        merge(mas1, size1, mas2, size2, masResult);
        if (array_is_sorted(masResult, 28)) {
            fstream file3("file3.txt", ios::app);
            for (int i{ 0 }; i < 28; ++i) {
                file3 << masResult[i];
                file3 << " ";
            }
            file3.close();
        }
        
        delete[] arr_unsorted;
    }
    catch (const logic_error & e)
    {
        cerr << e.what() << endl;
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
