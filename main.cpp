#include <iostream>
#include <exception>  // logic_error
#include <cstring>    // memcpy
#include <ctime>      // clock
#include <cstdlib>    // rand

using namespace std;

inline void swap(int& a, int& b)
{
    int tmp = a; a = b; b = tmp;
}


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
    /*for (int i{ 0 }; i < dlina; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;*/
}

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
    /*for (int i{ 0 }; i < dlina; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;*/
}

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
    /*for (int i{ 0 }; i < dlina; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;*/
}

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
    /*for (int i{0}; i < dlina; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;*/
}

void sort_insert_bin(int* arr, size_t size)
{

}

void sort_shell_div2(int* arr, size_t size)
{

}

void sort_shell_pow3(int* arr, size_t size)
{

}

void sort_heap(int* arr, size_t size)
{

}

void sort_quick_rec(int* arr, size_t size)
{

}

void sort_quick_nonrec(int* arr, size_t size)
{

}

void sort_merge(int* arr, size_t size)
{

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
            if (!(cin >> size) || size <= 0 || size > 10000000) throw logic_error("WRONG ARRAY SIZE");

            arr_unsorted = new int[size];
            srand(unsigned(time(nullptr)));
            for (size_t i = 0; i < size; arr_unsorted[i++] = rand() % size);
            //
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


        //  exec_sort( "Quick nonrecursive:",  sort_quick_nonrec );
        //  exec_sort( "Quick:",  sort_quick_rec );
        //  exec_sort( "Heap:",   sort_heap );
        //  exec_sort( "Shell:",  sort_shell_div2 );
        //  exec_sort( "Shell:",  sort_shell_pow3 );
        //  exec_sort( "Merge:",  sort_merge );
          // exec_sort( arr_unsorted, size, sort_insert_bin, "InsertBin:" );
           exec_sort( arr_unsorted, size, sort_insert_lin, "InsertLin:" );
           exec_sort( arr_unsorted, size, sort_select, "Select:" );
           exec_sort( arr_unsorted, size, sort_shaker, "Shaker:" );
        exec_sort(arr_unsorted, size, sort_bubble, "Bubble:");
        
        delete[] arr_unsorted;
    }
    catch (const logic_error & e)
    {
        cerr << e.what() << endl;
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
