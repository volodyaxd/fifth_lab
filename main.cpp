#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <cctype>
#include <windows.h>

const int ARRAY_SIZE = 100; // Размер массива

// Метод для заполнения файла случайными числами
void fillBinaryFileWithRandomNumbers(const std::string& filename) {
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile) {
        std::cerr << "Ошибка открытия бинарного файла для записи!" << std::endl;
        return;
    }

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    for (int i = 0; i < ARRAY_SIZE; ++i) {
        int num = std::rand() % 1000; // Случайные числа от 0 до 999
        outFile.write(reinterpret_cast<const char*>(&num), sizeof(num));
    }

    outFile.close();
}

// Метод для вывода содержимого бинарного файла
void fillTextFileWithRandomNumbers(const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Ошибка открытия текстового файла для записи!" << std::endl;
        return;
    }

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    for (int i = 0; i < ARRAY_SIZE; ++i) {
        int num = std::rand() % 1000; // Случайные числа от 0 до 999
        outFile << num << std::endl; // Запись числа в файл
    }

    outFile.close();
}

void printBinaryFileContents(const std::string& filename) {
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        std::cerr << "Ошибка открытия бинарного файла для чтения!" << std::endl;
        return;
    }

    std::cout << "Содержимое бинарного файла:" << std::endl;
    int currentElement;
    while (inFile.read(reinterpret_cast<char*>(&currentElement), sizeof(currentElement))) {
        std::cout << currentElement << " ";
    }
    std::cout << std::endl;

    inFile.close();
}

void printTextFileContents(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Ошибка открытия текстового файла для чтения!" << std::endl;
        return;
    }

    std::cout << "Содержимое текстового файла:" << std::endl;
    int currentElement;
    while (inFile >> currentElement) {
        std::cout << currentElement << " ";
    }
    std::cout << std::endl;

    inFile.close();
}

// Метод для нахождения разности первого и максимального элемента
int findDifference(const std::string& filename) {
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        std::cerr << "Ошибка открытия бинарного файла для чтения!" << std::endl;
        return 0;
    }

    int firstElement;
    inFile.read(reinterpret_cast<char*>(&firstElement), sizeof(firstElement));

    int maxElement = firstElement;
    int currentElement;

    while (inFile.read(reinterpret_cast<char*>(&currentElement), sizeof(currentElement))) {
        if (currentElement > maxElement) {
            maxElement = currentElement;
        }
    }

    inFile.close();
    return firstElement - maxElement;
}
// Метод для копирования элементов в матрицу и замены кратных сумме индексов
void copyToMatrix(const std::string& filename, int n) {
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        std::cerr << "Ошибка открытия бинарного файла для чтения!" << std::endl;
        return;
    }

    std::vector<std::vector<int>> matrix(n, std::vector<int>(n, 0));
    int currentElement;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (inFile.read(reinterpret_cast<char*>(&currentElement), sizeof(currentElement))) {
                matrix[i][j] = currentElement;
            } else {
                matrix[i][j] = 0; // Заполнение нулями, если элементов недостаточно
            }
        }
    }

    inFile.close();

    // Замена элементов, кратных сумме индексов
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int sumIndices = i + j;
            if (sumIndices != 0 && matrix[i][j] % sumIndices == 0) {
                matrix[i][j] = matrix[i][j] / sumIndices; // Заменяем на частное
            }
        }
    }

    // Вывод матрицы
    std::cout << "Матрица:" << std::endl;
    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
}

void first_second() {
    const std::string filename = "data.bin";

    // Заполнение бинарного файла случайными числами
    fillBinaryFileWithRandomNumbers(filename);

    // Вывод содержимого бинарного файла
    printBinaryFileContents(filename);

    // Нахождение разности первого и максимального элемента
    int difference = findDifference(filename);
    std::cout << "Разность первого и максимального элемента: " << difference << std::endl;

    // Копирование в матрицу и обработка
    int n;
    std::cout << "Введите размер матрицы n (n x n): ";
    std::cin >> n;
    copyToMatrix(filename, n);
}
struct Toy {
    char name[50]; // Название игрушки
    float price;   // Стоимость в рублях
    int ageFrom;   // Возрастная граница от
    int ageTo;     // Возрастная граница до
};

// Метод для заполнения файла данными об игрушках через ввод с клавиатуры
void fillFileWithToys(const std::string& filename) {
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile) {
        std::cerr << "Ошибка открытия файла для записи!" << std::endl;
        return;
    }

    char continueInput;
    do {
        Toy toy;
        std::cout << "Введите название игрушки: ";
        std::cin.ignore(); // Игнорируем предыдущий ввод
        std::cin.getline(toy.name, sizeof(toy.name)); // Вводим название игрушки
        std::cout << "Введите стоимость игрушки (в рублях): ";
        std::cin >> toy.price;
        std::cout << "Введите возрастную границу (от): ";
        std::cin >> toy.ageFrom;
        std::cout << "Введите возрастную границу (до): ";
        std::cin >> toy.ageTo;

        outFile.write(reinterpret_cast<const char*>(&toy), sizeof(Toy));

        std::cout << "Хотите ввести еще одну игрушку? (y/n): ";
        std::cin >> continueInput;

    } while (continueInput == 'y' || continueInput == 'Y');

    outFile.close();
}

// Метод для вывода содержимого файла
void printToyContents(const std::string& filename) {
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        std::cerr << "Ошибка открытия файла для чтения!" << std::endl;
        return;
    }

    std::cout << "Содержимое файла:" << std::endl;
    Toy toy;
    while (inFile.read(reinterpret_cast<char*>(&toy), sizeof(Toy))) {
        std::cout << "Название: " << toy.name 
                  << ", Стоимость: " << toy.price 
                  << " руб., Возраст: от " << toy.ageFrom 
                  << " до " << toy.ageTo << " лет" << std::endl;
    }

    inFile.close();
}
// Метод для определения стоимости кукол для детей шести лет
void findDollPricesForSixYearOlds(const std::string& filename) {
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        std::cerr << "Ошибка открытия файла для чтения!" << std::endl;
        return;
    }

    std::cout << "Стоимость кукол для детей шести лет:" << std::endl;
    Toy toy;
    bool found = false;
    while (inFile.read(reinterpret_cast<char*>(&toy), sizeof(Toy))) {
        if (toy.ageFrom <= 6 && toy.ageTo >= 6 && std::string(toy.name).find("Кукла") || std::string(toy.name).find("кукла") != std::string::npos) {
            std::cout << "Название: " << toy.name << ", Стоимость: " << toy.price << " руб." << std::endl;
            found = true;
        }
    }

    if (!found) {
        std::cout << "Куклы для детей шести лет не найдены." << std::endl;
    }

    inFile.close();
}

void third() {
    const std::string filename = "toys.dat";

    // Заполнение файла данными об игрушках через ввод с клавиатуры
    fillFileWithToys(filename);

    // Вывод содержимого файла
    printToyContents(filename);

    // Определение стоимости кукол для детей шести лет
    findDollPricesForSixYearOlds(filename);
}

void createReducedFile(const std::string& inputFilename, const std::string& outputFilename) {
    std::ifstream inFile(inputFilename);
    if (!inFile) {
        std::cerr << "Ошибка открытия файла для чтения!" << std::endl;
        return;
    }

    std::ofstream outFile(outputFilename);
    if (!outFile) {
        std::cerr << "Ошибка открытия файла для записи!" << std::endl;
        return;
    }

    int num;
    while (inFile >> num) {
        outFile << (num - 1) << std::endl; // Уменьшаем на 1 и записываем в новый файл
    }

    inFile.close();
    outFile.close();
}
void fourth() {
    const std::string inputFilename = "original.txt";
    const std::string outputFilename = "reduced.txt";

    // Заполнение текстового файла случайными числами
    fillTextFileWithRandomNumbers(inputFilename);

    // Вывод содержимого текстового файла
    std::cout << "Содержимое текстового файла:" << std::endl;
    printTextFileContents(inputFilename); 

    // Создание нового файла с уменьшенными значениями
    createReducedFile(inputFilename, outputFilename);

    // Вывод содержимого нового файла
    std::cout << "Содержимое файла с уменьшенными значениями:" << std::endl;
    printTextFileContents(outputFilename); 
}

void fifth() {
    const std::string filename = "numbers.txt";

    // Заполнение текстового файла случайными числами
    fillTextFileWithRandomNumbers(filename);

    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Не удалось открыть текстовый файл для чтения." << std::endl;
        return;
    }

    std::vector<int> numbers;
    int number;

    // Чтение чисел из файла
    while (inFile >> number) {
        numbers.push_back(number);
    }

    inFile.close();

    if (numbers.empty()) {
        std::cerr << "Файл пуст." << std::endl;
        return;
    }

    // Находим первый и максимальный элементы
    int firstElement = numbers[0];
    int maxElement = *std::max_element(numbers.begin(), numbers.end());

    // Вычисляем разность
    int difference = firstElement - maxElement;

    std::cout << "Первый элемент: " << firstElement << std::endl;
    std::cout << "Максимальный элемент: " << maxElement << std::endl;
    std::cout << "Разность первого и максимального элементов: " << difference << std::endl;
}

void createSampleFile(const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Не удалось открыть файл для записи." << std::endl;
        return;
    }

    // Пример текста
    outFile << "Это первая строка.\n";
    outFile << "Вторая строка начинается с буквы В.\n";
    outFile << "Третья строка.\n";
    outFile << "Четвертая строка начинается с буквы Ч.\n";
    outFile << "Пятая строка начинается с буквы П.\n";

    outFile.close();
}
void copyLinesStartingWith(const std::string& inputFile, const std::string& outputFile, char letter) {
    std::ifstream inFile(inputFile);
    if (!inFile) {
        std::cerr << "Не удалось открыть файл для чтения." << std::endl;
        return;
    }

    std::ofstream outFile(outputFile);
    if (!outFile) {
        std::cerr << "Не удалось открыть файл для записи." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        if (!line.empty() && std::tolower(line[0]) == std::tolower(letter)) {
            outFile << line << std::endl;
        }
    }

    inFile.close();
    outFile.close();
}

void sixth() {
    const std::string inputFilename = "sample.txt";
    const std::string outputFilename = "filtered_lines.txt";

    // Создаем файл с примером текста
    createSampleFile(inputFilename);

    // Читаем и выводим оригинальный текст
    std::ifstream inFile(inputFilename);
    if (!inFile) {
        std::cerr << "Не удалось открыть файл для чтения." << std::endl;
        return;
    }

    std::cout << "Оригинальный текст:\n";
    std::string line;
    while (std::getline(inFile, line)) {
        std::cout << line << std::endl;
    }
    inFile.close();

    // Запрашиваем букву у пользователя
    char letter;
    std::cout << "Введите букву: ";
    std::cin >> letter;

    // Копируем строки, начинающиеся с указанной буквы
    copyLinesStartingWith(inputFilename, outputFilename, letter);

    std::cout << "Строки, начинающиеся с буквы '" << letter << "', записаны в файл " << outputFilename << "." << std::endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int choice;

    do {
        std::cout << "\nВыберите действие:\n";
        std::cout << "1. first-second\n";
        std::cout << "2. third\n"; 
        std::cout << "3. fourth\n";
        std::cout << "4. fifth\n";
        std::cout << "5. sixth\n"; 
        std::cout << "0. Выход\n";
        std::cout << "Ваш выбор: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                first_second();
                break;
            case 2:
                third();
                break;
            case 3:
                fourth();
                break;
            case 4:
                fifth();
                break;
            case 5:
                sixth();
                break;
            case 0:
                std::cout << "Выход из программы." << std::endl;
                break;
            default:
                std::cout << "Неверный выбор, попробуйте снова." << std::endl;
                break;
        }
    } while (choice != 0);
    return 0;
}
