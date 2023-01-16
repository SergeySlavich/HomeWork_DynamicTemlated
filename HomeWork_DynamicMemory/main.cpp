#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

//TODO:
//От ветки dynamic_templated создать ветку dynamic_templates_optimisation, и в этой ветке
//оптимизировать функции для двумерных массивов, используя функции для одномерных массивов.

#define tab "\t"
#define delimiter "\n-------------------------------------\n"

template<typename T>T** allocate(const int rows, const int cols);
template<typename T>void clear(T** arr, const int rows);

void FillRand(int arr[], const int n, int minRand = 0, int maxRand = 100);
void FillRand(double arr[], const int n, int minRand = 0, int maxRand = 100);
void FillRand(int** arr, const int rows, const int cols);
void FillRand(double** arr, const int rows, const int cols);

template<typename T>void Print(T* arr, const int n);
template<typename T>void Print(T** arr, const int rows, const int cols);

template<typename T>T* push_back(T* arr, int& n, T value);
template<typename T>T* push_front(T* arr, int& n, T value);
template<typename T>T* insert(T* arr, int& n, T value, int index);

template<typename T>T* pop_back(T* arr, int& n);
template<typename T>T* pop_front(T* arr, int& n);

template<typename T>T** push_row_back(T** arr, int& rows, const int cols);
template<typename T>T** push_row_front(T** arr, int& rows, const int cols);
template<typename T>T** insert_row(T** arr, int& rows, const int cols, const int index);

template<typename T>T** pop_row_back(T** arr, int& rows, const int cols);

template<typename T>void push_col_back(T** arr, const int rows, int& cols);

template<typename T>void do_back(T& buffer, T& arr, int& size);
template<typename T>void do_front(T& buffer, T& arr, int& size);

//#define DYNAMIC_MEMORY_1
#define DYNAMIC_MEMORY_2

void main()
{
	setlocale(LC_ALL, "");

#ifdef DYNAMIC_MEMORY_1
	int n;
	cout << "Введите количество элементов: "; cin >> n;
	int* arr = new int[n];

	FillRand(arr, n);
	Print(arr, n);

	int value;
	cout << "Введите добавляемое значение: "; cin >> value;
	arr = push_back(arr, n, value);
	Print(arr, n);

	cout << "Введите добавляемое значение: "; cin >> value;
	arr = push_front(arr, n, value);
	Print(arr, n);

	cout << "Введите добавляемое значение: "; cin >> value;
	int index;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	arr = insert(arr, n, value, index);
	Print(arr, n);

	arr = pop_back(arr, n);
	Print(arr, n);

	arr = pop_front(arr, n);
	Print(arr, n);

	delete[] arr;
	//Memory leak  
#endif // DYNAMIC_MEMORY_1

	int rows;	//количество строк
	int cols;	//количество столбцов (количество элементов строки)
	cout << "Введите количество строк: "; cin >> rows;
	cout << "Введите количество элементов строки: "; cin >> cols;

	double** arr = allocate<double>(rows, cols);

	FillRand(arr, rows, cols);
	Print(arr, rows, cols);

	cout << delimiter << endl;
	cout << "---Добавление строки в конец массива---" << endl;
	arr = push_row_back(arr, rows, cols);
	FillRand(arr[rows - 1], cols, 900, 1000);
	Print(arr, rows, cols);

	cout << delimiter << endl;
	cout << "---Добавление строки в начало массива---" << endl;
	arr = push_row_front(arr, rows, cols);
	FillRand(arr[0], cols, 100, 200);
	Print(arr, rows, cols);
	
	cout << delimiter << endl;
	cout << "---Добавление строки в указанном месте массива---" << endl;
	int index;
	cout << "Введите индекс добавляемой строки: "; cin >> index;
	arr = insert_row(arr, rows, cols, index);
	FillRand(arr[index], cols, 400, 500);
	Print(arr, rows, cols);

	cout << delimiter << endl;
	cout << "---Удаление строки в конце массива---" << endl;
	arr = pop_row_back(arr, rows, cols);
	Print(arr, rows, cols);

	cout << delimiter << endl;
	cout << "---Добавление столбика в конец массива---" << endl;
	push_col_back(arr, rows, cols);
	Print(arr, rows, cols);

	clear(arr, rows);
}

template<typename T>T** allocate(const int rows, const int cols)
{
	T** arr = new T* [rows];	//создаем массив указателей
	for (int i = 0; i < rows; i++)
	{
		//создаем строки двумерного массива:
		arr[i] = new T [cols];
	}
	return arr;
}
template<typename T>void clear(T** arr, const int rows)
{
	//1) удаляем строки двумерного массива:
	for (int i = 0; i < rows; i++)
	{
		delete[] arr[i];
	}
	//2) удаляем массив указателей:
	delete[] arr;
}

void FillRand(int arr[], const int n, int minRand, int maxRand)
{
	cout << typeid(arr).name() << endl;
	for (int i = 0; i < n; i++)
	{
		//Через арифметику указателей и оператор разыменования:
		*(arr + i) = rand() % (maxRand - minRand) + minRand;
	}
}
void FillRand(double arr[], const int n, int minRand, int maxRand)
{
	cout << typeid(arr).name() << endl;
	minRand *= 100;
	maxRand *= 100;
	for (int i = 0; i < n; i++)
	{
		//Через арифметику указателей и оператор разыменования:
		*(arr + i) = rand() % (maxRand - minRand) + minRand;
		*(arr + i) /= 100;
	}
}
void FillRand(int** arr, const int rows, const int cols)
{
	for (int i = 0; i < rows; i++)	//i - нумерует строки
	{
		for (int j = 0; j < cols; j++)	//j - нумерует элементы строки
		{
			arr[i][j] = rand() % 100;
		}
	}
}
void FillRand(double** arr, const int rows, const int cols)
{
	for (int i = 0; i < rows; i++)	//i - нумерует строки
	{
		for (int j = 0; j < cols; j++)	//j - нумерует элементы строки
		{
			arr[i][j] = rand() % 10000;
			arr[i][j] /= 100;
		}
	}
}

template<typename T>void Print(T* arr, const int n)
{
	//cout << typeid(arr).name() << endl;
	for (int i = 0; i < n; i++)
	{
		//Через оператор индексирования
		//[] - оператор индексирования (Subscript operator)
		cout << arr[i] << tab;
	}
	cout << endl;
}
template<typename T>void Print(T** arr, const int rows, const int cols)
{
	for (int i = 0; i < rows; i++) Print(arr[i], cols);
}

template<typename T> void do_back(T& buffer, T& arr, int& size)	// Вспомогательная универсальная функция, выполняющая п.п. 2, 3, 4.
{
	for (int i = 0; i < size; i++)	//2) Копируем все содержимое исходного массива в буферный.
	{
		buffer[i] = arr[i];
	}
	delete[] arr;					//3) Удаляем исходный массив.
	arr = buffer;					//4) Подменяем адрес в указателе 'arr' адресом нового массива.
}
template<typename T> void do_front(T& buffer, T& arr, int& size)	// Вспомогательная универсальная функция, выполняющая п.п. 2, 3, 4.
{
	for (int i = 0; i < size; i++)	//2) Копируем все содержимое исходного массива в буферный.
	{
		buffer[i + 1] = arr[i];
	}
	delete[] arr;					//3) Удаляем исходный массив.
	arr = buffer;					//4) Подменяем адрес в указателе 'arr' адресом нового массива.
}

template<typename T>T* push_back(T* arr, int& n, T value)
{
	T* buffer = new T[n + 1];		//1) Создаем новый массив нужного размера.
	do_back(buffer, arr, n);		// Вызываем вспомогательную универсальную функцию, выполняющую п.п. 2, 3, 4.
	arr[n] = value;					//5) Только после всего этого в конец массива 'arr' можно добавить значение.
	n++;							//6) После добавления в массив 'arr' элемента, количество его элементов увеличивается на 1.
	return arr;						//7) Mission complete - элемент добавлен!
}
template<typename T>T* push_front(T* arr, int& n, T value)
{
	T* buffer = new T[n + 1];
	do_front(buffer, arr, n);
	arr[0] = value;
	n++;
	return arr;
}
template<typename T>T* insert(T* arr, int& n, T value, int index)
{
	T* buffer = new T[n + 1];
	/*for (int i = 0; i < index; i++)buffer[i] = arr[i];
	for (int i = index; i < n; i++)buffer[i + 1] = arr[i];*/
	for (int i = 0; i < n; i++)
	{
		//if (i < index)buffer[i] = arr[i];
		//else buffer[i + 1] = arr[i];
		//(i < index ? buffer[i] : buffer[i + 1]) = arr[i];
		buffer[i < index ? i : i + 1] = arr[i];
	}
	buffer[index] = value;
	delete[] arr;
	arr = buffer;
	n++;
	return arr;
}

template<typename T>T* pop_back(T* arr, int& n)
{
	T* buffer = new T[--n];
	do_back(buffer, arr, n);
	return arr;
}
template<typename T>T* pop_front(T* arr, int& n)
{
	T* buffer = new T[--n];
	do_front(buffer, arr, n);
	return arr;
}

template<typename T>T** push_row_back(T** arr, int& rows, const int cols)
{
	T** buffer = new T* [rows + 1];	//1) Создаем буферный массив указателей.
	do_back(buffer, arr, rows);		// Вызываем вспомогательную универсальную функцию, выполняющую п.п. 2, 3, 4.
	arr[rows] = new T[cols] {};		//5) Создаем новую строку.
	rows++;							//6) После добавления строки, количество строк увеличивается на 1.
	return arr;						//7) Mission complete - строка добавлена. Возвращаем новый массив.
}
template<typename T>T** push_row_front(T** arr, int& rows, const int cols)
{
	T** buffer = new T* [rows + 1];
	do_front(buffer, arr, rows);
	arr[0] = new T[cols] {};
	rows++;
	return arr;
}
template<typename T>T** insert_row(T** arr, int& rows, const int cols, const int index)
{
	T** buffer = new T* [rows + 1];
	for (int i = 0; i < index; i++) buffer[i] = arr[i];
	for (int i = index; i < rows; i++) buffer[i + 1] = arr[i];
	delete[] arr;
	arr = buffer;
	arr[index] = new T[cols] {};
	rows++;
	return arr;
}

template<typename T>T** pop_row_back(T** arr, int& rows, const int cols)
{
	delete[] arr[rows - 1];								//1) Удаляем последнюю строку из памяти.
	T** buffer = new T* [--rows];						//2) Переопределяем массив указателей.
	do_back(buffer, arr, rows);
	return arr;
}

template<typename T>void push_col_back(T** arr, const int rows, int& cols)
{
	for (int i = 0; i < rows; i++)
	{
		T* buffer = new T[cols + 1] {};
		for (int j = 0; j < cols; j++)buffer[j] = arr[i][j];
		delete[] arr[i];
		arr[i] = buffer;
	}
	cols++;
}