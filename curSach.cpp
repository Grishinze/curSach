    #include <iostream>
    #include <fstream>
    #include <vector>
    #include <sstream>
    #include <iomanip>

    using namespace std;

    typedef vector<vector<int>> Matrix;  // Тип данных для матрицы (двумерный вектор целых чисел)

    // Функция для ввода матрицы вручную
    void inputMatrix(Matrix& matrix, int size) {
        matrix.resize(size, vector<int>(size));  // Резервируем память для матрицы размером size x size
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                cout << "Введите элемент матрицы [" << i << "][" << j << "]: ";
                cin >> matrix[i][j];
            }
        }
    }

    // Функция для вывода матрицы
    void printMatrix(const Matrix& matrix) {
        if (matrix.empty()) {  // Если матрица пустая
            cout << "Матрица пуста!\n" << endl;
            return;
        }
        for (const auto& row : matrix) {  // Проходим по всем строкам матрицы   
            for (int elem : row) {  // Проходим по элементам строки
                cout << setw(5) << elem;  // Выводим элемент с отступом
            }
            cout << "\n" << endl;  // Переводим строку после вывода всех элементов строки
        }
    }

    // Функция для записи матриц в файл
    void writeMatrix(const string& filename, const Matrix& A, const Matrix& B, const Matrix& C) {
        ofstream file(filename, ios::trunc);  // Открываем файл, старые файлы удаляются, новые записываются. If Файла нет, то создаем
        if (!file) {  // Проверяем, открылся ли файл
            cerr << "Ошибка при открытии файла!\n" << endl;
            return;
        }

        // Записываем матрицу A
        file << "Матрица A:\n";
        for (const auto& row : A) {  // Проходим по строкам матрицы A
            for (int elem : row) {  // Проходим по элементам строки
                file << elem << " ";  // Записываем элемент в файл
            }
            file << endl;  // Переводим строку
        }
        file << endl;  // Пустая строка для разделения матриц

        // Записываем матрицу B
        file << "Матрица B:\n";
        for (const auto& row : B) {  // Проходим по строкам матрицы B
            for (int elem : row) {  // Проходим по элементам строки
                file << elem << " ";  // Записываем элемент в файл
            }
            file << endl;  // Переводим строку
        }
        file << endl;  // Пустая строка для разделения матриц

        // Записываем матрицу C
        file << "Матрица C:\n";
        for (const auto& row : C) {  // Проходим по строкам матрицы C
            for (int elem : row) {  // Проходим по элементам строки
                file << elem << " ";  // Записываем элемент в файл
            }
            file << endl;  // Переводим строку
        }

        cout << "Матрицы успешно записаны в файл " << filename << endl << "\n";  // Сообщаем о успешной записи
    }
    // Проверочка для квадртаности матрицы, ю ноу
    void checkSquare(const Matrix& matrix, const string& name) {
        size_t rows = matrix.size();
        for (const auto& row : matrix) {
            if (row.size() != rows) {
                cout << "Ошибка: " << name << " не является квадратной матрицей." << endl;
                cout << "Количество строк: " << rows << ", количество столбцов в одной из строк: " << row.size() << endl;
                cout << "Проверьте содержимость матриц в файле!";
                exit(0);
            }
        }
    }
    // А тут проверочка на то что все матрицы одинаковые
    void checkSameSize(const Matrix& matrix1, const Matrix& matrix2, const Matrix& matrix3) {
        if (matrix1.size() != matrix2.size() || matrix1.size() != matrix3.size()) {
            cout << "Ошибка: Матрицы имеют разное количество строк!" << endl;
            exit(0);
        }

        for (size_t i = 0; i < matrix1.size(); ++i) {
            if (matrix1[i].size() != matrix2[i].size() || matrix1[i].size() != matrix3[i].size()) {
                cout << "Ошибка: Матрицы имеют разное количество столбцов в строках!" << endl;
                exit(0);
            }
        }
    }
    // Чтение матриц из файла
    void readMatrix(const string& filename, Matrix& A, Matrix& B, Matrix& C) {
        ifstream file(filename);  // Открываем файл для чтения
        if (!file) {  // Проверяем, открылся ли файл
            cerr << "Ошибка при открытии файла!" << endl;  // Если файл не открылся, выводим ошибку
            return;
        }

        string line;
        Matrix* currentMatrix = nullptr;  // Указатель на текущую матрицу

        // Очистка старых данных перед загрузкой
        A.clear();
        B.clear();
        C.clear();

        // Считываем строки из файла
        while (getline(file, line)) {
            if (line.find("Матрица A:") != string::npos) {  // Ищем начало матрицы A
                currentMatrix = &A;
                continue;
            }
            if (line.find("Матрица B:") != string::npos) {  // Ищем начало матрицы B
                currentMatrix = &B;
                continue;
            }
            if (line.find("Матрица C:") != string::npos) {  // Ищем начало матрицы C
                currentMatrix = &C;
                continue;
            }

            if (currentMatrix != nullptr && !line.empty()) {  // Если указатель на матрицу установлен и строка не пустая
                istringstream stream(line);  // Жеско создаем поток для чтения, чтобы могли извлечь числа и записать в вектор row
                vector<int> row;
                int value;
                while (stream >> value) {  // Читаем числа из строки
                    row.push_back(value);  // Добавляем число в строку
                }
                currentMatrix->push_back(row);  // Добавляем строку в текущую матрицу
            }
        }

        file.close();

        // Проверка квадратности для всех матриц
        checkSquare(A, "Матрица A");
        checkSquare(B, "Матрица B");
        checkSquare(C, "Матрица C");

        // Проверка, чтобы все матрицы имели одинаковый размер
        checkSameSize(A, B, C);

        cout << "Матрицы успешно загружены из файла.\n" << endl;  // Сообщаем об успешной загрузке
    }

    // Функция для редактирования элемента матрицы
    void editMatrix(Matrix& matrix) {
        int i, j, value;
        cout << "Введите номер строки и столбца элемента для редактирования: ";  // Запрашиваем индексы элемента
        cin >> i >> j;
        if (i >= 0 && i < matrix.size() && j >= 0 && j < matrix.size()) {  // Проверяем корректность индексов
            cout << "Введите новое значение: ";  // Запрашиваем новое значение
            cin >> value;
            matrix[i][j] = value;  // Заменяем старое значение на новое
        }
        else {
            cout << "Некорректные индексы!\n" << endl;  // Если индексы некорректны
        }
    }

    // Функция для вывода элементов матрицы C, равных сумме элементов A и B
    void printElementsMatrix_C(const Matrix& A, const Matrix& B, const Matrix& C) {
        cout << "Вывод элементов матрицы С:" << endl;
        bool flag = false; //Флажок для проверки вывода
        for (int i = 0; i < C.size(); ++i) {  // Проходим по строкам матрицы C
            for (int j = 0; j < C.size(); ++j) {  // Проходим по столбцам
                if (C[i][j] == A[i][j] + B[i][j]) {  // Если элемент матрицы C равен сумме соответствующих элементов матриц A и B

                    cout << "C[" << i << "][" << j << "] = " << C[i][j] << endl;  // Выводим элемент
                    flag = true;
                }     
            }
        }
        if(!flag)
            cout << "Нет элементов матрицы C равные сумме элементов матриц А и В\n" << endl;
    }

    int main() {

        setlocale(LC_ALL, "");
        Matrix A, B, C;
        int choice;
        string filename = "matrix.txt";  // Имя файла для работы с матрицами

        // Основной цикл программы
        while (true) {
            cout << "Меню:\n";
            cout << "1. Загрузить матрицы из файла\n";
            cout << "2. Создать матрицы вручную\n";
            cout << "3. Вывести матрицы\n";
            cout << "4. Редактировать матрицу\n";
            cout << "5. Сохранить матрицы в файл\n";
            cout << "6. Показать элементы матрицы C, равные сумме элементов A и B\n";
            cout << "0. Выйти\n";
            cout << "Выберите действие: ";
            cin >> choice;

            switch (choice) {
            case 1:
                readMatrix(filename, A, B, C);  // Загружаем матрицы из файла
                break;

            case 2:
                int size;
                cout << "Введите размер матриц: ";
                cin >> size;

                // Очистка старых данных
                A.clear();
                B.clear();
                C.clear();

                cout << "Ввод матрицы A:\n";
                inputMatrix(A, size);
                cout << "Ввод матрицы B:\n";
                inputMatrix(B, size);
                cout << "Ввод матрицы C:\n";
                inputMatrix(C, size);
                break;

            case 3:
                cout << "Матрица A:\n";
                printMatrix(A);
                cout << "Матрица B:\n";
                printMatrix(B);
                cout << "Матрица C:\n";
                printMatrix(C);
                break;

            case 4:
                cout << "Выберите матрицу для редактирования (1 - A, 2 - B, 3 - C): ";
                cin >> choice;
                if (choice == 1) {
                    editMatrix(A);
                }
                else if (choice == 2) {
                    editMatrix(B);
                }
                else if (choice == 3) {
                    editMatrix(C);
                }
                else {
                    cout << "Некорректный выбор!\n" << endl;
                }
                break;

            case 5:
                writeMatrix(filename, A, B, C);
                break;

            case 6:
                printElementsMatrix_C(A, B, C);
                break;

            case 0:
                cout << "Выход из программы..." << endl;
                return 0;
            default:
                cout << "Некорректный выбор!\n" << endl;
                break;
            }
        }

    }
