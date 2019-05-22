#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include <stdbool.h>
#include <io.h>
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_RIGHT 77
#define KEY_LEFT 75
#define KEY_RETURN 13
#define KEY_TAB 9
#define KEY_BKSP 8
#define DECRYPT 1 //расшифровать
#define ENCRYPT 0 //зашифровать
#define infoFieldSize 16
#define categoryFieldSize 11
#define logAndPassSize 30


typedef struct {
    char login[logAndPassSize];
    char password[logAndPassSize];
    int isAdmin;
}USER;
typedef struct {
    char firstname[infoFieldSize];
    char surname[infoFieldSize];
    char lastname[infoFieldSize];
}FULLNAME;
typedef struct {
    int minutes;
    int seconds;
}LAP;
typedef struct {
    int day;
    int month;
    int year;
    int age;
}DATEOFBIRTH;
typedef struct {
    int number;
    FULLNAME fullname;
    char country[infoFieldSize];
    DATEOFBIRTH dateOfBirth;
    char category[categoryFieldSize];
    char model[infoFieldSize];
    int points;
    LAP timeOfLap;
}INFORMATION;


int usersLinesCounter = 0;              //счётчик количества пользователей
int infoLinesCounter = 0;               //счётчик количества участников
USER *user = NULL;              //массив структур пользователей
INFORMATION *info = NULL;               //массив структур участников


//Ввод
char* stringInputCheck(int limit, const char* message);//функция ввода только букв
char* bufferedInput(int limit, const char* message);//функция ввода ограниченного кол-ва символов
int checkToEnterOnlyInt(int limit, const char *message);//функция ввода только целых чисел
char* maskedPasswordInput(int limit, const char* message);//функция для ввода пароля
char* loginInput(int limit, const char* message);//функция для ввода логина
char* categoryInput(int limit, const char* message);//функция для ввода разряда
void dateOfBirthInput(int *day, int *month, int *year, const char* message);
void timeOfLapInput(int *minutes, int *seconds, const char* message);

//Меню
void indicateCursor(bool status);//функция показа/скрытия каретки ввода
int menu();//функция главного меню
int adminSubmenu();//функция подменю администраторов
int userSubmenu();//функция подменю пользователей
int userEditMenu(int i, bool showPass);//функция меню редактирования пользователей
int memberEditMenu(int i);//функция меню редактирования участников
void searchingAndFiltering();//фукнция выбора функции меню поиска и фильтрации
int searchAndFilteringMenu();//функция меню поиска и фильтрации
void userManagement();//функция выбора функции меню управления пользователями
int userManagementMenu();//фукнция меню управления пользователями
int userLoginOrRegMenu();//функция подменю входа для пользователей
int displayAllUsersMenu(bool showPass);//функция вывода меню показа всех пользователей

// Файлы
bool checkFile(const char* filename);//функция проверка файла на существование файла
//true - файл существует, false - файл не существует
bool createFile(const char* filename);//функция создания файла
void crypterTool(int status);//функция шифра Цезаря

//Пользователи
bool adminLogin();//функция входа администраторов
bool userLogin();//функция входа пользователей
void firstStartAdminReg();//функция регистрации администратора при первом запуске
void usersInit();//функция чтения аккаунтов из файла
void userAdd();//функция добавления аккаунта
void userDelete();//функция удаления аккаунта
void userEdit();//функция редактирования аккаунта
void displayEditableUser(int i, bool showPass);//функция вывода информации о редактируемом аккаунте
void displayAllUsers(bool showPass);//функция вывода информации о всех аккаунтах
void userReg();//функция регистрации пользователя

//Участники
void membersOpenAdmin();//функция открытия/создания файла для пользователей
void membersOpenUser();//функция открытия файла для пользователей
void membersInit();//функция чтения информации об участниках из файла
void memberAdd();//функция добавления участника
void memberEdit();//функция редактирования участника
void memberDelete();//функция удаления участника
void displayEditableMember(int i);//функция вывода информации об редактируемом участнике
void displayAllMembers();//функция вывода информации о всех участниках

//Фильтрация и поиск
void pointsFilter();//функция фильтрации участников по очкам
void timeOfLapFilter();//функция фильтрации участников по времени круга
void ageFilter();//функция фильтрации участников по возрасту
void yearOfBirthFilter();//функция фильтрации участников по году рождения
void timeOfLapSorting();//функция сортировки участников по времени круга
void numberSearch();//функция поиска участников по номеру
void surnameSearch();//функция поиска участников по фамилии
void countrySearch();//функция поиска учатстников по стране
void categorySearch();//функция поиска участников по разряду
void displayTopMembers();//функция вывода топ-3 лучших участников


int main() {
    setlocale(LC_ALL, "Rus");           //установка локали консоли
    SetConsoleCP(1251);         //установка кодировки консоли
    SetConsoleOutputCP(1251);           //установка кодировки текста консоли
    system("color 0B");             //изменение цвета текста консоли
    system("mode con cols=139 lines=32");               //установка размера окна консоли
    indicateCursor(false);          //скрытие каретки ввода
    printf("-------------------------------------------------------------------------------------------------------------------------------------------\n"
           "                                  Программа учёта информации об участниках соревнования по бегу на коньках                                 \n"
           "-------------------------------------------------------------------------------------------------------------------------------------------\n"
           "                                                                                                                             © by Minilooth");
    Sleep(3500);            //засыпание программы на 3.5 сек
    indicateCursor(true);               //показ каретки ввода
    usersInit();            //инициализация пользователей
    bool adminSubMenuFlag = false, userSubMenuFlag = false, userLogOrRegMenuFlag = false;
    while (true) {
        system("cls");
        switch (menu()) {
            case 1:
                if (adminLogin()) {
                    while (!adminSubMenuFlag) {
                        system("cls");
                        switch (adminSubmenu()) {
                            case 1:
                                membersOpenAdmin();
                                break;
                            case 2:
                                memberAdd();
                                system("pause");
                                break;
                            case 3:
                                memberEdit();
                                break;
                            case 4:
                                memberDelete();
                                system("pause");
                                break;
                            case 5:
                                displayAllMembers();
                                system("pause");
                                break;
                            case 6:
                                searchingAndFiltering();
                                break;
                            case 7:
                                userManagement();
                                break;
                            case 8:
                                info = NULL;
                                adminSubMenuFlag = true;
                                infoLinesCounter = 0;
                                break;
                            default:
                                break;
                        }
                    }
                    adminSubMenuFlag = false;
                }
                break;
            case 2:
                while (!userLogOrRegMenuFlag) {
                    switch (userLoginOrRegMenu()) {
                        case 1:
                            if (userLogin()) {
                                while (!userSubMenuFlag) {
                                    system("cls");
                                    switch (userSubmenu()) {
                                        case 1:
                                            membersOpenUser();
                                            system("pause");
                                            break;
                                        case 2:
                                            displayAllMembers();
                                            system("pause");
                                            break;
                                        case 3:
                                            displayTopMembers();
                                            system("pause");
                                            break;
                                        case 4:
                                            searchingAndFiltering();
                                            break;
                                        case 5:
                                            info = NULL;
                                            userSubMenuFlag = true;
                                            infoLinesCounter = 0;
                                            break;
                                        default:
                                            break;
                                    }
                                }
                                userSubMenuFlag = false;
                            }
                            break;
                        case 2:
                            userReg();
                            break;
                        case 3:
                            userLogOrRegMenuFlag = true;
                            break;
                        default:
                            break;
                    }
                }
                userLogOrRegMenuFlag = false;
                break;
            case 3:
                free(info);
                free(user);
                return 0;
            default:
                break;
        }
    }
}


//Всё что связано с вводом
char* stringInputCheck(int limit, const char* message) {
    char *buffer = NULL;
    int i = 0, checkLetter = 0, checkSymbol = 0;
    bool isLetter = false;
    while (true) {
        i = 0;
        buffer = bufferedInput(limit, message);         //Ввод строки с клавиатуры
        while (buffer[i] != '\0') {
            checkLetter = isdigit((unsigned char)buffer[i]);            //Проверка символа на цифру от 0 до 9
            checkSymbol = isalnum((unsigned char)buffer[i]);            //Проверка символа на букву или число
            if (checkLetter != 0 || !checkSymbol) {             //Если символ не буква и не цифра
                isLetter = false;
                break;              //Выход из цикла
            }
            else isLetter = true;
            i++;
        }
        if (isLetter) {             //Если массив содержит только буквы
            buffer[0] = (char)toupper((int)buffer[0]);              //Изменение первой буквы на эту же букву верхнего регистра
            return buffer;              //Возврат значения функции
        }
        else {          //Если массив содержит не только буквы
            printf("[Ошибка!]Это поле не может содержать символ \"%c\"!", buffer[i]);
            Sleep(1000);
            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);               //Стирание двух последних строк с экрана
        }
    }
}

char* bufferedInput(int limit, const char* message) {
    char ch, *buffer = NULL;
    int i = 0;
    buffer = (char*)realloc(NULL, sizeof(char)*(limit + 1));            //Выделение памяти под массив
    printf("%s", message);
    while (true) {
        ch = (char)_getch();                //Ввод символа с клавиатуры
        if (ch != '\0') {               //Если символ - не нуль-символ
            if (ch == KEY_RETURN || ch == KEY_TAB) {                //Если это символ ввода или табуляции
                if (i > 0) {            //Если счётчик символов больше 0
                    buffer[i] = '\0';               //Запись нуль-символа в i-ую ячейку
                    putchar('\n');
                    break;              //Выход из цикла
                }
                else {          //Если счётчик сиволов равен 0
                    printf("\n[Ошибка!]Введите хотя бы один символ!");
                    Sleep(1000);
                    printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);               //Стирание двух последних строк с экрана
                    printf("%s", message);
                }
            }
            else if (ch == KEY_BKSP && i > 0) {         //Если символ backspace и счётчик символов больше 0
                i--;
                printf("\b \b");                //Стереть символ с консоли
            }
            else if (ch == KEY_BKSP && !i)              //Если символ backspace и счётчик равен 0
                continue;               //Переход на следующую итерацию цикла
            else {
                if (i < limit) {            //Если счётчик меньше ограничителя
                    buffer[i++] = ch;           //Запись символа в массив
                    putchar(ch);                //Вывод символа на экран
                }
            }
        }
    }
    return buffer;              //Возврат значения функции
}

int checkToEnterOnlyInt(int limit, const char *message) {
    char *buffer = NULL;
    int numberEntered = 0, i = 0, check = 0;
    bool isNumeral = false, flag = false;
    while (true) {
        i = 0;
        buffer = bufferedInput(limit, message);         //Ввод строки с клавиатуры
        while (buffer[i] != '\0') {             //Пока i-ый символ не нуль-символ
            if (buffer[i] == '-' && !flag) {            //Если i-ый символ равен символу "-" и флаг = true
                i++;
                flag = true;
            }
            check = isdigit((unsigned char)buffer[i]);              //Проверить является ли i-ый символ цифрой
            if (!check) {           //Если i-ый символ не является цифрой
                isNumeral = false;
                break;
            }
            else isNumeral = true;            //Если i-ый символ является цифрой
            i++;
        }
        if (isNumeral) {                //Если строка содержит только цифры
            numberEntered = strtol(buffer, NULL, 10);               //Преобразование строки в целое число
            free(buffer);               //Освобождение памяти переменной
            return numberEntered;               //Возврат значения функции
        }
        else {                  //Если строка содержит не цифры
            printf("[Ошибка!]Не правильный ввод!");
            Sleep(1000);
            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);               //Стирание двух последних строк с экрана
        }
    }
}

char* maskedPasswordInput(int limit, const char* message){
    char ch, *password = NULL;
    int i = 0;
    bool isSpaceEntered = false;
    password = (char*)realloc(NULL, sizeof(char)*(limit + 1));          //Выделение памяти под массив
    while(true) {
        i = 0;
        printf("%s", message);
        while (true) {          //Посимвольная запись символов в массив
            ch = (char) _getch();               //Ввод символа
            if (ch != '\0') {
                if (ch == KEY_RETURN || ch == KEY_TAB) {            //Если символ - символ ввода или табуляции
                    password[i] = '\0';         //Запись нуль-символ в i-ую ячейку
                    putchar('\n');
                    break;              //Выход из цикла
                } else if (ch == KEY_BKSP && i > 0) {               //Если символ - backspace и счётчик символов > 0
                    i--;
                    printf("\b \b");               //Стереть символ с экрана
                } else if (ch == KEY_BKSP && i == 0) {              //Если символ - backspace и счётчик символов = 0
                    continue;               //Переход на следующую итерацию цикла
                } else if (i < limit) {                 //Если счётчик символов меньше ограничителя
                    password[i++] = ch;         //Запись символа в массив
                    putchar('*');               //Вывод на экран символ "*"
                }
            }
        }
        if (i > 0) {                //Если счётчик символов больше 0
            for (int j = 0; password[j]; j++) {             //Поиск символа "пробел" в массиве символа
                if (password[j] == ' ') {               //Если j-ый символ - пробел
                    isSpaceEntered = true;
                    break;              //Выход из цикла
                } else isSpaceEntered = false;
            }
            if (isSpaceEntered) {               //Если обнаружен символ "пробел"
                printf("[Ошибка!]Пароль не может содержать символ \" \"!");
                Sleep(1000);
                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);               //Стирание двух последних строк с экрана
            } else return password;         //Если "пробел" не обнаружен
        } else {            //Если счётчик символов равен 0
            printf("[Ошибка!]Введите хотя бы один символ!");
            Sleep(1000);
            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);               //Стирание двух последних строк
        }
    }
}

char* loginInput(int limit, const char* message){
    char *buffer = NULL;
    int i = 0, checkSymbol = 0;
    bool isLetter = false;
    while (true) {
        i = 0;
        buffer = bufferedInput(limit, message);             //Ввод строки
        while (buffer[i] != '\0') {             //Пока i-ый символ не нуль-символ
            checkSymbol = isalnum((unsigned char)buffer[i]);            //Проверка i-го символа на цифру или букву
            if (!checkSymbol) {             //Если i-ый символ - цифра или буква
                isLetter = false;
                break;              //Выход из цикла
            }
            else isLetter = true;           //Если i-ый символ - не буква или не цифра
            i++;
        }
        if (isLetter)               //Если строка содержит только буквы или цифры
            return buffer;              //Возврат значения функции
        else {          //Если не содержит не только буквы или цифры
            printf("[Ошибка!]Логин не может содержать символ \"%c\"!", buffer[i]);
            Sleep(1000);
            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);               //Стирание двух последних строк с экрана
        }
    }
}

char* categoryInput(int limit, const char* message){
    char *buffer = NULL;
    int i = 0, checkSymbol = 0, checkLetter = 0;
    bool isLetter = false;
    while (true) {
        i = 0;
        buffer = bufferedInput(limit, message);         //Ввод строки
        while (buffer[i] != '\0') {             //Пока i-ый символ не нуль-символ
            if(buffer[i] != ' ' && buffer[i] != '.') {          //Если i-ый символ не пробел и не точка
                checkLetter = isdigit((unsigned char)buffer[i]);            //Проверка символа на цифру от 0 до 9
                checkSymbol = isalnum((unsigned char) buffer[i]);           //Проверка i-го символа на букву
                if (!checkSymbol || checkLetter != 0) {             //Если i-ый символ не буква и не цифра
                    isLetter = false;
                    break;              //Выход из цикла
                } else isLetter = true;         //Если i-ый символ буква или цифра
            }
            i++;
        }
        if (isLetter) {                 //Если строка содержит только буквы или цифры
            buffer[0] = (char)toupper((int)buffer[0]);              //Перевод первого символа в верхний регистр
            return buffer;              //Возврат значения функции
        }
        else {              //Если строка содержит не только буквы или цифры
            printf("[Ошибка!]Разряд не может содержать символ \"%c\"!", buffer[i]);
            Sleep(1000);
            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);               //Стирание двух последних строк с экрана
        }
    }
}

void dateOfBirthInput(int *day, int *month, int *year, const char* message) {
    char *buffer = NULL;
    bool isDateInputtedCorrectly = false, isDayInputtedCorrectly = false, isMonthInputtedCorrectly = false, isYearInputtedCorrectly = false;
    do {
        isDayInputtedCorrectly = false;
        isMonthInputtedCorrectly = false;
        isYearInputtedCorrectly = false;
        buffer = bufferedInput(10, message);
        if (buffer[2] != '.' || buffer[5] != '.') {
            printf("[Ошибка!]Дата введена некорректно!");
            Sleep(1000);
            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
            continue;
        }


        *day = atoi(buffer);
        if (*day < 1 || *day > 31) {
            printf("[Ошибка!]День должен быть введен от 1 до 31!");
            Sleep(1000);
            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
            continue;
        }
        else isDayInputtedCorrectly = true;


        *month = atoi(buffer + 3);
        if (*month < 1 || *month > 12) {
            printf("[Ошибка!]Месяц должен быть введен от 1 до 12!");
            Sleep(1000);
            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
            continue;
        }
        else isMonthInputtedCorrectly = true;


        *year = atoi(buffer + 6);
        if (*year < 1900 || *year > 2019) {
            printf("[Ошибка!]Год должен быть введен от 1900 до 2019!");
            Sleep(1000);
            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
            continue;
        }
        else isYearInputtedCorrectly = true;


        if (isDayInputtedCorrectly == true && isMonthInputtedCorrectly == true && isYearInputtedCorrectly == true)
            isDateInputtedCorrectly = true;
    } while (isDateInputtedCorrectly == false);
}

void timeOfLapInput(int *minutes, int *seconds, const char* message) {
    char *buffer = NULL;
    bool isTimeInputtedCorrectly = false, isMinutesInputtedCorrectly = false, isSecondsInputtedCorrectly = false;
    do {
        isMinutesInputtedCorrectly = false;
        isSecondsInputtedCorrectly = false;
        buffer = bufferedInput(5, message);
        if (buffer[2] != ':') {
            printf("[Ошибка!]Время круга введено некорректно!");
            Sleep(1000);
            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
            continue;
        }
        *minutes = atoi(buffer);
        if (*minutes < 0 || *minutes > 59) {
            printf("[Ошибка!]Минуты должны быть введены от 0 до 59!");
            Sleep(1000);
            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
            continue;
        }
        else isMinutesInputtedCorrectly = true;
        *seconds = atoi(buffer + 3);
        if (*seconds < 0 || *seconds > 59) {
            printf("[Ошибка!]Секунды должны быть введены от 0 до 59!");
            Sleep(1000);
            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
            continue;
        }
        else isSecondsInputtedCorrectly = true;
        if (isMinutesInputtedCorrectly == true && isSecondsInputtedCorrectly == true)
            isTimeInputtedCorrectly = true;
    } while (isTimeInputtedCorrectly == false);
}


//Все что связано с меню
void indicateCursor(bool status) {
    void* hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(hConsole, &structCursorInfo);
    structCursorInfo.bVisible = status;
    SetConsoleCursorInfo(hConsole, &structCursorInfo);
}

int menu() {
    int choice = 1, ch = (int)NULL;
    bool isShowed = false;
    const char *line[] = { "Вход под администратором.", "Вход под пользователем.", "Выход.", NULL }, pointer = '>';
    indicateCursor(false);              //Скрытие каретки ввода
    while (true) {
        if (ch == KEY_RETURN || ch == KEY_UP || ch == KEY_DOWN || !isShowed) {              //Если введенный символ - символ ввода или символ стрелки вверх или вних или меню не было выведено
            isShowed = true;
            system("cls");              //Очистка экрана
            if (ch == KEY_RETURN) {             //Если был введен символ ввода
                indicateCursor(true);               //Показать каретку ввода
                return choice;
            }
            if (ch == KEY_UP) choice--;                 //Если был введен символ стрелки вверх
            else if (ch == KEY_DOWN) choice++;              //Если был введен символ стрелки вниз
            if (choice > 3) choice = 1;                 //Если указатель выбора больше 3 вернуть его в начальное положение
            else if (choice < 1) choice = 3;            //Если указатель выбора менбше 1 вернуть его в конечного положение
            printf("Меню:\n");
            for (int i = 0; line[i]; i++) {             //Вывод меню
                if (choice == i + 1) {                  //Если указатель равен (i + 1)-ой ячейке массива строк
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);               //Изменить цвет строки
                    printf("%c", pointer);              //Вывод указателя на экран
                }
                printf(i + 1 == choice ? "%s\n" : " %s\n", line[i]);                //Вывод строки из массива
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);               //Смена цвета строк
            }
        }
        ch = _getch();              //Ввод символа с клавиатуры
    }
}

int adminSubmenu() {
    int choice = 1, ch = (int)NULL;
    bool isShowed = false;
    const char pointer = '>', *line[] = { "Создание/открытие файла.", "Добавление записи.", "Редактирование записи.",
                                          "Удаление записи.", "Просмотр всех данных в табличной форме.",
                                          "Различные процедуры поиска и фильтрации данных.", "Управление пользователями.",
                                          "Выход в меню.", NULL };
    indicateCursor(false);                  //Скрытие каретки ввода
    while (true) {
        if (ch == KEY_RETURN || ch == KEY_UP || ch == KEY_DOWN || !isShowed) {                  //Если введенный символ - символ ввода или символ стрелки вверх или вних или меню не было выведено
            isShowed = true;
            system("cls");              //Очистка экрана
            if (ch == KEY_RETURN) {             //Если был введен символ ввода
                indicateCursor(true);               //Показать каретку ввода
                return choice;
            }
            if (ch == KEY_UP) choice--;                 //Если был введен символ стрелки вверх
            if (ch == KEY_DOWN) choice++;                 //Если был введен символ стрелки вниз
            if (choice > 8) choice = 1;                 //Если указатель выбора больше 8 вернуть его в начальное положение
            if (choice < 1) choice = 8;                 //Если указатель выбора менбше 1 вернуть его в конечного положение
            printf("Подменю(для администраторов):\n");
            for (int i = 0; line[i]; i++) {                 //Вывод меню
                if (choice == i + 1) {                  //Если указатель равен (i + 1)-ой ячейке массива строк
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);               //Изменить цвет строки
                    printf("%c", pointer);                  //Вывод указателя на экран
                }
                printf(i + 1 == choice ? "%s\n" : " %s\n", line[i]);                 //Вывод строки из массива
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);                   //Смена цвета строк
            }
        }
        ch = _getch();                  //Ввод символа с клавиатуры
    }
}

int userSubmenu() {
    int choice = 1, ch = (int)NULL;
    bool isShowed = false;
    const char pointer = '>', *line[] = { "Открытие файла с данными.", "Просмотр всех данных в табличной форме.",
                                          "Просмотр топ-3 самых быстрых участников.", "Различные процедуры поиска и фильтрации данных.",
                                          "Выход в меню.", NULL };
    indicateCursor(false);                  //Скрытие каретки ввода
    while (true) {
        if (ch == KEY_RETURN || ch == KEY_UP || ch == KEY_DOWN || !isShowed) {              //Если введенный символ - символ ввода или символ стрелки вверх или вних или меню не было выведено
            isShowed = true;
            system("cls");                  //Очистка экрана
            if (ch == KEY_RETURN) {             //Если был введен символ ввода
                indicateCursor(true);                   //Показать каретку ввода
                return choice;
            }
            if (ch == KEY_UP) choice--;                 //Если был введен символ стрелки вверх
            if (ch == KEY_DOWN) choice++;                   //Если был введен символ стрелки вниз
            if (choice > 5) choice = 1;                 //Если указатель выбора больше 5 вернуть его в начальное положение
            if (choice < 1) choice = 5;                 //Если указатель выбора менбше 1 вернуть его в конечного положение
            printf("Подменю(для пользователей):\n");
            for (int i = 0; line[i]; i++) {             //Вывод меню
                if (choice == i + 1) {                  //Если указатель равен (i + 1)-ой ячейке массива строк
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);               //Изменить цвет строки
                    printf("%c", pointer);              //Вывод указателя на экран
                }
                printf(i + 1 == choice ? "%s\n" : " %s\n", line[i]);            //Вывод строки из массива
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);           //Смена цвета строк
            }
        }
        ch = _getch();              //Ввод символа с клавиатуры
    }
}

int userEditMenu(int i, bool showPass) {
    int choice = 1, ch = (int)NULL;
    bool isShowed = false;
    const char pointer = '>', *line[] = { "Изменить логин.", "Изменить пароль.", "Изменить права администратора.", "Показать/скрыть пароль.",
                                          "Выход из меню редактирования аккунтов.", NULL };
    indicateCursor(false);              //Скрытие каретки ввода
    while (true) {
        if (ch == KEY_RETURN || ch == KEY_UP || ch == KEY_DOWN || !isShowed) {                  //Если введенный символ - символ ввода или символ стрелки вверх или вних или меню не было выведено
            isShowed = true;
            displayEditableUser(i, showPass);                   //Функция вывода ректируемого пользователя
            if (ch == KEY_RETURN) {                 //Если был введен символ ввода
                indicateCursor(true);                   //Показать каретку ввода
                return choice;
            }
            if (ch == KEY_UP) choice--;                 //Псли был введен символ стрелки вверх
            if (ch == KEY_DOWN) choice++;                   //Псли был введен символ стрелки вниз
            if (choice > 5) choice = 1;                 //Псли указатель выбора больше 5 вернуть его в начальное положение
            if (choice < 1) choice = 5;                 //Псли указатель выбора менбше 1 вернуть его в конечного положение
            printf("Меню редактирования аккаунтов:\n");
            for (int j = 0; line[j]; j++) {                 //Вывод меню
                if (choice == j + 1) {                  //Если указатель равен (j + 1)-ой ячейке массива строк
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);               //Изменить цвет строки
                    printf("%c", pointer);                      //Вывод указателя на экран
                }
                printf(j + 1 == choice ? "%s\n" : " %s\n", line[j]);                //Вывод строки из массива
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);               //Смена цвета строк
            }
        }
        ch = _getch();              //Ввод символа с клавиатуры
    }
}

int memberEditMenu(int i) {
    int choice = 1, ch = (int)NULL;
    bool isShowed = false;
    const char pointer = '>', *line[] = { "Изменение номера участника.", "Изменение имени участника.",
                                          "Изменение фамилии участника.", "Изменение отчества участника.",
                                          "Изменение страны участника.", "Изменение даты рождения участника.",
                                          "Изменение разряда участника.", "Изменение модели коньков участника.",
                                          "Изменение количества очков участника.", "Изменение времени круга участника.",
                                           "Выход из меню редактирования участника.", NULL };
    indicateCursor(false);              //Скрытие каретки ввода
    displayEditableMember(i);               //Вывод редактируемого участника
    while (true) {
        if (ch == KEY_RETURN || ch == KEY_UP || ch == KEY_DOWN || !isShowed) {              //Если введенный символ - символ ввода или символ стрелки вверх или вних или меню не было выведено
            if (ch == KEY_RETURN) {               //Если был введен символ ввода
                indicateCursor(true);               //Показывать каретку ввода
                displayEditableMember(i);               //Вывод редактируемого участника
                return choice;
            }
            if (ch == KEY_UP) choice--;                 //Если был введен символ стрелки вверх
            if (ch == KEY_DOWN) choice++;               //Если был введен символ стрелки вниз
            if (choice > 11) choice = 1;                //Если указатель выбора больше 14 вернуть его в начальное положение
            if (choice < 1) choice = 11;                //Если указатель выбора менбше 1 вернуть его в конечного положение
            if(isShowed == true)                //Если меню было выведено
                for (int j = 0; j < 12; j++)            //Построчное стирание меню с экрана
                    printf("%c[2K\r%c[A", 27, 27);
            isShowed = true;
            printf("Меню редактирования участника:\n");
            for (int j = 0; line[j]; j++) {             //Вывод меню
                if (choice == j + 1) {              //Если указатель равен (j + 1)-ой ячейке массива строк
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);               //Изменить цвет строки
                    printf("%c", pointer);              //Вывод указателя на экран
                }
                printf(j + 1 == choice ? "%s\n" : " %s\n", line[j]);                //Вывод строки
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);               //Измение цвета строк
            }
        }
        ch = _getch();          //Ввод символа с клавиатуры
    }
}

void searchingAndFiltering() {
    while (true) {
        system("cls");              //Очистка меню
        switch (searchAndFilteringMenu()) {             //Вывод и выбор пункта меню
            case 1: pointsFilter(); system("pause"); break;
            case 2: timeOfLapFilter(); system("pause"); break;
            case 3: ageFilter(); system("pause"); break;
            case 4: yearOfBirthFilter(); system("pause"); break;
            case 5: numberSearch(); system("pause"); break;
            case 6: surnameSearch(); system("pause"); break;
            case 7: countrySearch(); system("pause"); break;
            case 8: categorySearch(); system("pause"); break;
            case 9: timeOfLapSorting(); system("pause"); break;
            case 10: return;
            default: break;
        }
    }
}

int searchAndFilteringMenu() {
    int choice = 1, ch = (int)NULL;
    bool isShowed = false;
    const char pointer = '>', *line[] = { "Фильтр по количеству очков.", "Фильтр по времени круга.",
                                          "Фильтр по возрасту.", "Фильтр по году рождения.", "Поиск по номеру.",
                                          "Поиск по фамилии.", "Поиск по стране.", "Поиск по разряду.",
                                          "Сортировка по времени круга.", "Выход из меню поиска и фильтрации.", NULL };
    indicateCursor(false);              //Скрытие каретки ввода
    while (true) {
        if (ch == KEY_RETURN || ch == KEY_UP || ch == KEY_DOWN || !isShowed) {              //Если введенный символ - символ ввода или символ стрелки вверх или вних или меню не было выведено
            isShowed = true;
            system("cls");              //Очистка экрана
            if (ch == KEY_RETURN) {             //Если был введен символ ввода
                indicateCursor(true);               //Показывать каретку ввода
                return choice;
            }
            if (ch == KEY_UP) choice--;             //Если был введен символ стрелки вверх
            if (ch == KEY_DOWN) choice++;               //Если был введен символ стрелки вниз
            if (choice > 10) choice = 1;                //Если указатель выбора больше 10 вернуть его в начальное положение
            if (choice < 1) choice = 10;                //Если указатель выбора менбше 1 вернуть его в конечного положение
            printf("Меню поиска и фильтрации:\n");
            for (int i = 0; line[i]; i++) {             //Вывод меню
                if (choice == i + 1) {              //Если указатель равен (i + 1)-ой ячейке массива строк
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);               //Изменить цвет строки
                    printf("%c", pointer);              //Вывод указателя на экран
                }
                printf(i + 1 == choice ? "%s\n" : " %s\n", line[i]);                //Вывод строки
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);               //Измение цвета строк
            }
        }
        ch = _getch();              //Ввод символа с клавиатуры
    }
}

void userManagement() {
    bool showPass = false, displayAllUsersFlag = true;
    while (true) {
        system("cls");              //Очистка экрана
        switch (userManagementMenu()) {             //Вывод и выбор пункта меню
            case 1:
                userAdd();
                break;
            case 2:
                userDelete();
                break;
            case 3:
                userEdit();
                break;
            case 4:
                while(displayAllUsersFlag == true) {
                    switch(displayAllUsersMenu(showPass)) {
                        case 1: {
                            showPass = showPass == false ? true : false;
                            break;
                        }
                        case 2: displayAllUsersFlag = false; break;
                        default: break;
                    }
                }
                displayAllUsersFlag = true;
                break;
            case 5:
                return;
            default:
                break;
        }
    }
}

int userManagementMenu() {
    int choice = 1, ch = (int)NULL;
    bool isShowed = false;
    const char pointer = '>', *line[] = { "Добавить аккаунт.", "Удалить аккаунт.", "Редактировать аккаунт.",
                                          "Просмотр всех аккаунтов.", "Выход из меню управления пользователями/администраторами.", NULL };
    indicateCursor(false);                  //Скрытие каретки ввода
    while (true) {
        if (ch == KEY_RETURN || ch == KEY_UP || ch == KEY_DOWN || !isShowed) {                  //Если введенный символ - символ ввода или символ стрелки вверх или вних или меню не было выведено
            isShowed = true;
            system("cls");              //Очистка экрана
            if (ch == KEY_RETURN) {                 //Если был введен символ ввода
                indicateCursor(true);               //Показывать каретку ввода
                return choice;
            }
            if (ch == KEY_UP) choice--;                 //Если был введен символ стрелки вверх
            if (ch == KEY_DOWN) choice++;               //Если был введен символ стрелки вниз
            if (choice > 5) choice = 1;                 //Если указатель выбора больше 10 вернуть его в начальное положение
            if (choice < 1) choice = 5;                 //Если указатель выбора менбше 1 вернуть его в конечного положение
            printf("Меню управления пользователями/администраторами:\n");
            for (int i = 0; line[i]; i++) {                 //Вывод меню
                if (choice == i + 1) {              //Если указатель равен (i + 1)-ой ячейке массива строк
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);               //Изменить цвет строки
                    printf("%c", pointer);              //Вывод указателя на экран
                }
                printf(i + 1 == choice ? "%s\n" : " %s\n", line[i]);                //Вывод строки
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);               //Измение цвета строк
            }
        }
        ch = _getch();              //Ввод символа с клавиатуры
    }
}

int userLoginOrRegMenu(){
    int choice = 1, ch = (int)NULL;
    bool isShowed = false;
    const char pointer = '>', *line[] = { "Войти.", "Зарегистрироваться.", "Вернутся в меню." , NULL };
    indicateCursor(false);              //Скрытие каретки ввода
    while (true) {
        if (ch == KEY_RETURN || ch == KEY_UP || ch == KEY_DOWN || !isShowed) {                  //Если введенный символ - символ ввода или символ стрелки вверх или вних или меню не было выведено
            isShowed = true;
            system("cls");              //Очистка экрана
            if (ch == KEY_RETURN) {             //Если был введен символ ввода
                indicateCursor(true);               //Показывать каретку ввода
                return choice;
            }
            if (ch == KEY_UP) choice--;             //Если был введен символ стрелки вверх
            if (ch == KEY_DOWN) choice++;               //Если был введен символ стрелки вниз
            if (choice > 3) choice = 1;             //Если указатель выбора больше 10 вернуть его в начальное положение
            if (choice < 1) choice = 3;             //Если указатель выбора менбше 1 вернуть его в конечного положение
            printf("Вход под пользователем:\n");
            for (int i = 0; line[i]; i++) {             //Вывод меню
                if (choice == i + 1) {              //Если указатель равен (i + 1)-ой ячейке массива строк
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);               //Изменить цвет строки
                    printf("%c", pointer);              //Вывод указателя на экран
                }
                printf(i + 1 == choice ? "%s\n" : " %s\n", line[i]);                //Вывод строки
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);               //Измение цвета строк
            }
        }
        ch = _getch();              //Ввод символа с клавиатуры
    }
}

int displayAllUsersMenu(bool showPass){
    int choice = 1, ch = (int)NULL;
    bool isShowed = false;
    const char pointer = '>', *line[] = { "Показать/скрыть пароли.", "Вернутся в меню." , NULL };
    indicateCursor(false);
    while (true) {
        if (ch == KEY_RETURN || ch == KEY_UP || ch == KEY_DOWN || !isShowed) {                  //Если введенный символ - символ ввода или символ стрелки вверх или вних или меню не было выведено
            isShowed = true;
            system("cls");              //Очистка экрана
            if (ch == KEY_RETURN) {             //Если был введен символ ввода
                indicateCursor(true);               //Показывать каретку ввода
                return choice;
            }
            if (ch == KEY_UP) choice--;             //Если был введен символ стрелки вверх
            if (ch == KEY_DOWN) choice++;               //Если был введен символ стрелки вниз
            if (choice > 2) choice = 1;             //Если указатель выбора больше 10 вернуть его в начальное положение
            if (choice < 1) choice = 2;             //Если указатель выбора менбше 1 вернуть его в конечного положение
            displayAllUsers(showPass);
            printf("Меню просмотра всех пользователей:\n");
            for (int i = 0; line[i]; i++) {             //Вывод меню
                if (choice == i + 1) {              //Если указатель равен (i + 1)-ой ячейке массива строк
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);               //Изменить цвет строки
                    printf("%c", pointer);              //Вывод указателя на экран
                }
                printf(i + 1 == choice ? "%s\n" : " %s\n", line[i]);                //Вывод строки
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);               //Измение цвета строк
            }
        }
        ch = _getch();              //Ввод символа с клавиатуры
    }
}


//Всё что связано с файлами
bool checkFile(const char* filename) {
    FILE* file = NULL;
    if (!(file = fopen(filename, "rt+")))               //Если файл не открывается для чтения - вернуть false
        return false;
    else {                  //Если файл открытивается для чтения - закрыть его и вернуть true
        fclose(file);
        return true;
    }
}

bool createFile(const char* filename) {
    FILE* file = NULL;
    if ((file = fopen(filename, "wt"))) {               //Если файл создался то закрыть его и вернуть true
        fclose(file);
        return true;
    } else return false;                //Если не создался вернуть false
}

void crypterTool(int status) {
    int ch, key = 0;
    if (status == ENCRYPT) key = 2;         //key - ключ шифрования
    else if (status == DECRYPT) key = -2;
    FILE *input = NULL, *output = NULL;
    if (!(input = fopen("db.dat", "rb"))) {
        //Если файл с логинами/паролями не удалось открыть
        printf("[Ошибка!]Шифрование: Не удалось открыть файл с логинами/паролями!\n\n");
        system("pause");
        exit(0);
    }
    if (!(output = fopen("tempdb.dat", "wb"))) {
        //Если временный файл не удалось создать
        printf("[Ошибка!]Шифрование: Не удалось создать временный файл с логинами/паролями!\n\n");
        system("pause");
        exit(0);
    }
    while (1) {
        fread(&ch, sizeof(char), 1, input);         //Чтение символа из файла
        if (feof(input)) break;             //Если конец файла то выйти из цикла
        else {              //Если не конец файла
            if (ch != '\n')         //Если прочитанный символ не равен символу следующей строки
                ch += key;          //Прибавить к коду символа ключ
            fwrite(&ch, sizeof(char), 1, output);           //Записать измененный символ во временный файл
        }
    }
    fclose(input);          //Закрыть файл с логинами/пароля
    fclose(output);             //Закрыть временный файл
    if (!(input = fopen("db.dat", "wb"))) {
        //Если файл с логинами/паролями не удалось пересоздать
        printf("[Ошибка!]Шифрование: Не удалось перезаписать файл с логинами/паролями!\n\n");
        system("pause");
        exit(0);
    }
    if (!(output = fopen("tempdb.dat", "rb"))) {
        //Если временный файл не удалось открыть для чтения
        printf("[Ошибка!]Шифрование: Не удалось открыть временный файл с логинами/паролями!\n\n");
        system("pause");
        exit(0);
    }
    while (1) {
        fread(&ch, sizeof(char), 1, output);            //Чтение символа из временного файла
        if (feof(output)) break;                //Если конец файла выйти из цикла
        else fwrite(&ch, sizeof(char), 1, input);               //Записать прочитанный символ в файл с логинами/пароляит
    }
    fclose(output);             //Закрыть временный файл
    if (remove("tempdb.dat")) {
        //Если не удалось удалить временный файл
        printf("\n[Ошибка!]Шифрование: Не удалось удалить временный файл с логинами/паролями!\n\n");
        system("pause");
        exit(0);
    }
    fclose(input);              //Закрыть файл с логинами/паролями
}


//Всё что связано с пользователями
bool adminLogin() {
    system("cls");              //Очистка экрана
    int i = 0, j = 0, attemptCounter = 0;
    bool isLoginRight = false, isPasswordRight = false;
    char *login = NULL, password[30], ch;
    login = bufferedInput(29, "Введите логин: ");               //Ввод логина
    for (i = 0; i < usersLinesCounter; i++) {         //Поиск логина в массиве
        if (!strcmp(login, (user + i)->login) && (user + i)->isAdmin == true) {         //Если такой логин найден и он имеет права администратора
            isLoginRight = true;
            break;              //Выход из цикла
        }
    }
    if (!isLoginRight) {                //Если такой логин не найден
        printf("[Ошибка!]Такого администратора не существует!\n\n");
        system("pause");
        free(login);
        return false;
    }
    do {                //Ввод пароля
        j = 0;
        printf("Введите пароль: ");
        while (true) {
            ch = (char) _getch();               //Ввод символа
            if (ch != '\0') {               //Если это не нуль-символ
                if (ch == KEY_RETURN || ch == KEY_TAB) {            //Если символ ввода или символ табуляции
                    password[j] = '\0';             //Запись нуль-символа в j-ую ячейку
                    break;              //Выход из цикла
                } else if (ch == KEY_BKSP && j > 0) {           //Если символ backspace и счётчик символов > 0
                    j--;
                    printf("\b \b");                //Удаление символа с экрана
                } else if (ch == KEY_BKSP && j == 0) {          //Если символ backspace и счётчик символов = 0
                    continue;           //Переход на следующую итерацию цикла
                } else {
                    if (j < 29 && attemptCounter < 5) {         //Если счётчик символов < 29 и счётчик попыток < 5
                        password[j++] = ch;         //Запись символа в массив
                        putchar('*');               //Маскировка вводимого символа символов "*"
                    } else if (j < 29) {            //Если счётчик символов < 29 и счётчик попыток >= 5
                        password[j++] = ch;         //Запись символа в массив
                        putchar(ch);                //Вывод вводимого символа
                    }
                }
            }
        }
        if (!strcmp(password, (user + i)->password))            //Если введенный пароль совпадает с паролем логина
            isPasswordRight = true;
        else {              //Если не совпадает
            if(attemptCounter < 10){                //Если счётчик попыток меньше 10
                printf("\n[Ошибка!]Неверный пароль!");
                Sleep(1000);
                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);               //Стирание двух последних строк
                attemptCounter++;               //Счётчик попыток ++
            } else {                //Если счётчик попыток больше 10
                printf("\n[Ошибка!]Неверный пароль!\n");
                printf("\nВы превысили максималальное число попыток ввода!\n\n");
                Sleep(1000);
                system("pause");
                return false;           //Вернуть false
            }
        }
    } while (!isPasswordRight);             //Пока не будет введен верный пароль
    printf("\n\nВы успешно авторизовались!");
    Sleep(1000);
    printf("%c[2K\rДобро пожаловать, %s!\n\n", 27, (user + i)->login);
    free(login);
    system("pause");
    return true;            //Если авторизация прошла успешно вернуть true
}

bool userLogin() {
    system("cls");              //Очистка экрана
    int i = 0, j = 0, attemptCounter = 0;
    bool isLoginRight = false, isPasswordRight = false;
    char *login = NULL, password[30], ch;
    login = bufferedInput(29, "Введите логин: ");               //Ввод логина
    for (i = 0; i < usersLinesCounter; i++) {               //Поиск логина в массиве
        if (!strcmp(login, (user + i)->login) && (user + i)->isAdmin == false) {                //Если такой логин найден и он не имеет права администратора
            isLoginRight = true;
            break;              //Выход из цикла
        }
    }
    if (!isLoginRight) {                //Если такой логин не найден
        printf("[Ошибка!]Такого пользователя не существует!\n\n");
        system("pause");
        free(login);
        return false;
    }
    do {                //Ввод пароля
        j = 0;
        printf("Введите пароль: ");
        while (true) {
            ch = (char) _getch();               //Ввод символа
            if (ch != '\0') {               //Если это не нуль-символ
                if (ch == KEY_RETURN || ch == KEY_TAB) {                //Если символ ввода или символ табуляции
                    password[j] = '\0';             //Запись нуль-символа в j-ую ячейку
                    break;              //Выход из цикла
                } else if (ch == KEY_BKSP && j > 0) {               //Если символ backspace и счётчик символов > 0
                    j--;
                    printf("\b \b");                //Удаление символа с экрана
                } else if (ch == KEY_BKSP && j == 0) {              //Если символ backspace и счётчик символов = 0
                    continue;               //Переход на следующую итерацию цикла
                } else {
                    if (j < 29 && attemptCounter < 5) {             //Если счётчик символов < 29 и счётчик попыток < 5
                        password[j++] = ch;             //Запись символа в массив
                        putchar('*');               //Маскировка вводимого символа символов "*"
                    } else if (j < 29) {                //Если счётчик символов < 29 и счётчик попыток >= 5
                        password[j++] = ch;             //Запись символа в массив
                        putchar(ch);                //Вывод вводимого символа
                    }
                }
            }
        }
        if (!strcmp(password, (user + i)->password))                //Если введенный пароль совпадает с паролем логина
            isPasswordRight = true;
        else {              //Если не совпадает
            if(attemptCounter < 10){                //Если счётчик попыток меньше 10
                printf("\n[Ошибка!]Неверный пароль!");
                Sleep(1000);
                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);               //Стирание двух последних строк
                attemptCounter++;               //Счётчик попыток ++
            } else {                //Если счётчик попыток больше 10
                printf("\n[Ошибка!]Неверный пароль!\n");
                printf("\nВы превысили максималальное число попыток ввода!\n\n");
                Sleep(1000);
                system("pause");
                return false;               //Вернуть false
            }
        }
    } while (!isPasswordRight);             //Пока не будет введен верный пароль
    printf("\n\nВы успешно авторизовались!");
    Sleep(1000);
    printf("%c[2K\rДобро пожаловать, %s!\n\n", 27, (user + i)->login);
    free(login);
    system("pause");
    return true;                //Если авторизация прошла успешно вернуть true
}

void firstStartAdminReg() {
    FILE *file = NULL;
    char *login = NULL, *password = NULL;
    USER newUser;
    system("cls");          //Очистка экрана
    printf("-------------------------------------------------------------------------------------------------------------------------------------------\n"
           "                  Вы зашли в программу в первый раз. Для корректной работы программы нужно зарегистрировать администратора!                \n"
           "-------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("Регистрация администратора.\n\n");
    login = loginInput(29, "Введите логин: ");              //Ввод логина
    strcpy(newUser.login,login);                //Копирование логина в переменную типа USER
    password = maskedPasswordInput(29, "Введите пароль: ");             //Ввод пароля
    strcpy(newUser.password, password);             //Копирование пароля в переменную типа USER
    newUser.isAdmin = 1;                //Изменение прав администратора в переменной типа USER
    if ((file = fopen("db.dat", "ab+"))) {              //Если файл удалось открыть
        fwrite(&newUser, sizeof(USER), 1, file);                //Запись переменной типа USER в файл
        fclose(file);               //Закрытие файла
        crypterTool(ENCRYPT);               //Зашифровака файла
        printf("\nНовый администратор успешно зарегестрирован!\n\n");
        system("pause");
    }
    else {              //Если не удалось открыть файл
        printf("\n[Ошибка!]Регистрация: Не удалось открыть файл для добавления нового администратора!\n");
        exit(0);
    }
    system("cls");              //Очистка экрана
}

void usersInit() {
    FILE* file = NULL;
    long fsize = 0;
    if (checkFile("db.dat")) {               //Если файл существует
        if ((file = fopen("db.dat", "rb"))){                //Если файл удалось открыть для чтения
            fseek(file, 0, SEEK_END);               //Установка указателя в конец файла
            fsize = ftell(file);                //Чтение байт перед указателем
            usersLinesCounter = fsize/sizeof(USER);             //Расчёт количества пользователей
            rewind(file);               //Установка указателя на начало файла
            if (usersLinesCounter != 0) {               //Если есть хотябы один пользователь
                crypterTool(DECRYPT);               //Расшифровать файл
                user = (USER *)malloc(usersLinesCounter * (sizeof(USER)));          //Выделение памяти
                for (int i = 0; i < usersLinesCounter; i++)             //Чтение из файла и запись в массив
                    fread((user + i), sizeof(USER), 1, file);
                fclose(file);               //Закрытие файла
                crypterTool(ENCRYPT);               //Зашифровать файл
            } else {                //Если нет ни одной строки
                firstStartAdminReg();               //Функция регистрации пользователя при первом запуске программы
                usersInit();                //Инициализация пользователей
            }
        } else {                //Если файл не удалось открыть
            printf("[Ошибка!]Инициальзация пользователей: Не удалось открыть файл с логинами/паролями!\n");
            system("pause");
            exit(0);
        }
    } else if (createFile("db.dat")) {                  //Если файл не существует - создать
        firstStartAdminReg();
        usersInit();
    } else {                //Если файл не существует и его не удалось создать
        printf("[Ошибка!]Инициальзация пользователей: Не удалось создать файл с логинами/паролями!\n");
        system("pause");
        exit(0);
    }
}

void userAdd() {
    bool isLoginExist = false, isShowed = false;
    int choice = 1, ch = (int)NULL;
    char *login = NULL, *password = NULL;
    const char *line[] = { "Да", "Нет", NULL }, pointer = '>';
    FILE* file = NULL;
    user = (USER*)realloc(user, (usersLinesCounter + 1) * sizeof(USER));                //Перераспределение памяти
    printf("Добавить пользователя:\n");
    do {
        login = loginInput(29, "Введите логин: ");              //Ввод логина
        for (int i = 0; i < usersLinesCounter; i++) {           //Проверка на существование такого логина
            if (strcmp((user + i)->login, login) == 0) {                //Если i-ый логин совпадает с введенным
                isLoginExist = true;
                break;              //Выход из цикла
            }
            else isLoginExist = false;              //Если не совпадает
        }
        if (isLoginExist) {                 //Если такой логин найден
            printf("[Ошибка!]Такой аккаунт уже существует!");
            Sleep(1000);
            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);               //Очистка двух последних строк
        }
        else strcpy((user + usersLinesCounter)->login, login);              //Если не найден записать в выделенную ячейку массива структур этот логин
    } while (isLoginExist);             //Пока не будет введен не существующий логин
    free(login);                //Освобождение памяти для логина
    password = maskedPasswordInput(29, "Введите пароль: ");             //Ввод пароля
    strcpy((user + usersLinesCounter)->password, password);             //Копирование пароля в выделенную ячейеку массива структур
    free(password);             //Освобождение памяти для пароля
    indicateCursor(false);              //Скрытие каретки ввода
    while (true) {
        if (ch == KEY_LEFT || ch == KEY_RIGHT || ch == KEY_RETURN || !isShowed) {               //Если введенный символ - символ ввода или символ стрелки вверх или вних или меню не было выведено
            isShowed = true;
            if (ch == KEY_RETURN) {             //Если введенный символ символ ввода
                printf("%c[2K\r", 27);              //Стереть строку с экрана
                printf("Администратор? ");
                for (int i = 0; line[i]; i++)               //Вывод выбора на экран
                    if (choice == i + 1)                //Если выбор равен (i+1)-ой ячейке массива
                        printf("%s", line[i]);              //Вывод этой ячейки
                indicateCursor(true);               //Показывать каретку ввода
                break;              //Выход из цикла
            }
            printf("%c[2K\r", 27);              //Стереть строку с экрана
            if (ch == KEY_LEFT) choice--;               //Если символ стрелка влево
            if (ch == KEY_RIGHT) choice++;              //Если символ стрелка вправо
            if (choice > 2) choice = 2;             //Если указатель выбора больше 2 вернуть его в начальное положение
            if (choice < 1) choice = 1;             //если указатель выбора меньше 1 вернуть его в конечное положение
            printf("Администратор? ");
            for (int i = 0; line[i]; i++) {             //Вывод меню выбора
                if (choice == i + 1) {              //Если выбор равен (i+1) - ой ячейку массива
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);               //Изменение цвета строки
                    printf("%c", pointer);              //Вывод указателя
                }
                printf(i + 1 == choice ? "%s " : " %s ", line[i]);              //Вывод строк
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);               //Изменение цвета строк
            }
        }
        ch = _getch();              //Ввод символа
    }
    if (choice == 1) (user + usersLinesCounter)->isAdmin = 1;               //Если выбор равен 1 дать права администратора этому пользователю
    else (user + usersLinesCounter)->isAdmin = 0;               //В других случаях не давать права администратора
    if (checkFile("db.dat")) {              //Если файл существует
        crypterTool(DECRYPT);               //Расшифровать файл
        if ((file = fopen("db.dat", "ab+"))) {              //Если файл удалось открыть
            fwrite((user + usersLinesCounter), sizeof(USER), 1, file);              //Запись этой ячейки массива структур в файл
            fclose(file);               //Закрыть файл
            printf("\nАккаунт успешно добавлен!\n\n");
            _flushall();                //Перезагрузить все файлы
            usersLinesCounter++;
        }
        else printf("[Ошибка!]Добавление пользователей: Ошибка открытия файла с логинами/паролями! Пользователь не добавлен!\n\n");             //Если файл не удалось открыть
        crypterTool(ENCRYPT);               //Зашифровать файл
    }
    else printf("[Ошибка!]Добавление пользователей: Файл не существует!\n\n");              //Если файл не существует
    system("pause");
}

void userDelete() {
    char *login = NULL;
    int i = 0, adminCounter = 0;
    bool isLoginExist = false;
    FILE* file = NULL;
    for(int j = 0; j < usersLinesCounter; j++) {            //Счётчик количества администраторов
        if ((user + j)->isAdmin)                //Если j-ый пользователь имеет права админинстратора
            adminCounter++;             //Счётчик количества админинстраторов ++
    }
    displayAllUsers(false);             //Вывод всех пользователей на экран, не показывая их пароль
    printf("Удаление аккаунта.\n");
    login = bufferedInput(29, "Введите логин аккаунта, который вы хотите удалить: ");               //Ввод логина
    for (i = 0; i < usersLinesCounter; i++) {               //Поиск такого логина в массиве
        if (!strcmp((user + i)->login, login)) {                //Если i-ый логин совпадает с введенным
            isLoginExist = true;
            break;                  //Выход из цикла
        }
    }
    if (!isLoginExist) {                //Если такой логин не найден
        printf("[Ошибка!]Такого аккаунта не существует!\n\n");
        system("pause");
        return;                 //Выход из функции
    }
    free(login);                //Освобождение памяти для логина
    if(adminCounter == 1 && (user + i)->isAdmin) {              //Если удаляемый логин администратора и он последний
        system("cls");
        displayAllUsers(false);
        printf("[Ошибка!]Нельзя удалить последнего администратора!\n\n");
    }
    else {
        if (checkFile("db.dat")) {             //Если файл существует
            crypterTool(DECRYPT);               //Расшифровать
            if ((file = fopen("db.dat", "wb"))) {               //Если файл удалось пересоздать
                for (int j = i; j < usersLinesCounter; j++)             //Сдвинуть все ячейки влево после удаляемого пользователя
                    *(user + j) = *(user + (j + 1));
                user = (USER *) realloc(user, sizeof(USER) * usersLinesCounter);            //Перераспределить память
                usersLinesCounter--;
                for (int j = 0; j < usersLinesCounter; j++)             //Перезапись в файл
                    fwrite((user + j), sizeof(USER), 1, file);
                fclose(file);                   //Закрыть файл
                system("cls");              //Очистка экрана
                displayAllUsers(false);             //Показать всех пользователей, скрывая их пароль
                printf("Аккаунт успешно удалён!\n\n");
            } else
                printf("[Ошибка!]Удаление пользователей: Ошибка открытия файла с логинами/паролями! Файл отчищен!\n\n");               //Если файл не удалось пересоздать
            crypterTool(ENCRYPT);               //Зашифровать
        } else
            printf("[Ошибка!]Удаление пользователей: Ошибка открытия файла с логинами/паролями!\n\n");             //Если файл не существует
    }
    system("pause");
}

void userEdit() {
    char *login = NULL, *newLogin = NULL, *newPassword = NULL;
    int i = 0, adminCounter = 0;
    bool isLoginExist = false, isNewLoginExist = false, editFlag = false, showPass = false;
    FILE* file = NULL;
    displayAllUsers(showPass);              //Показать всех пользователей, скрывая их пароль
    login = loginInput(29, "Введите логин аккаунта, который вы хотите отредактировать: ");               //Ввод логина
    for (i = 0; i < usersLinesCounter; i++) {               //Поиск введенного логина в массиве
        if (!strcmp((user + i)->login, login)) {                //Если i-ый логин совпадает с введенным
            isLoginExist = true;
            break;              //Выход из цикла
        }
        else isLoginExist = false;
    }
    if (!isLoginExist) {                //Если такой логин не найден
        printf("[Ошибка!]Такого аккаунта не существует!\n\n");
        system("pause");
        return;
    }
    free(login);                //Освобождение памяти для логина
    while (!editFlag) {
        adminCounter = 0;               //Обнуление счётчика количества администраторов
        for(int j = 0; j < usersLinesCounter; j++) {                //Счётчик количества администраторов
            if ((user + j)->isAdmin)                //Если j-ый пользователей имеет права администратора
                adminCounter++;             //Счётчик администраторов ++
        }
        switch (userEditMenu(i, showPass)) {                //Вывод информации об редактируемом пользователе и меню редактирования
            case 1: {
                printf("Изменить логин.\n");
                do {
                    newLogin = loginInput(29, "Введите новый логин: ");                 //Ввод нового логина
                    for (int j = 0; j < usersLinesCounter; j++) {               //Поиск введенного логина в массиве
                        if (strcmp((user + j)->login, newLogin) == 0) {             //Если j-ый логин совпадает с введенным
                            isNewLoginExist = true;
                            break;              //Выход из цикла
                        }
                        else isNewLoginExist = false;
                    }
                    if (isNewLoginExist) {              //Если такой логин найден
                        printf("[Ошибка!]Такой логин уже существует!\n");
                        Sleep(1000);
                        printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
                    }
                } while (isNewLoginExist);              //Пока не будет найден такой логин в массиве
                strcpy((user + i)->login, newLogin);                //Копирование нового логина в редактируемую ячейку массива структур
                displayEditableUser(i, showPass);               //Вывод информации об редактируемом пользователе
                printf("Логин успешно изменен!\n\n");
                free(newLogin);             //Освобождение памяти для нового логина
                system("pause");
                break;              //Выход из switch
            }
            case 2: {
                printf("Изменение пароля.\n");
                newPassword = maskedPasswordInput(29, "Введите новый пароль: ");                    //Ввод нового пароля
                strcpy((user + i)->password, newPassword);              //Копирование нового пароля в редактируемую ячейку массива структур
                displayEditableUser(i, showPass);               //Вывод информации об редактируемом пользователе
                printf("Пароль успешно изменен!\n\n");
                free(newPassword);              //Освобождение памяти для нового пароля
                system("pause");
                break;              //Выход из switch
            }
            case 3: {
                if(adminCounter == 1 && (user + i)->isAdmin)                //Если пытаются редактировать права администратора последнего администратора
                    printf("[Ошибка!]Нельзя изменить права последнего администратора!\n\n");
                else {
                    if ((user + i)->isAdmin) {              //Если пользователь имеет права администратора убрать их
                        (user + i)->isAdmin = false;
                        displayEditableUser(i, showPass);               //Вывод информации об редактируемом пользователе
                        printf("Права администратора успешно изменены.\n\n");
                    } else {                    //Если пользователь не имеет права адмнистратора дать их
                        (user + i)->isAdmin = true;
                        displayEditableUser(i, showPass);               //Вывод информации об редактируемом пользователе
                        printf("Права администратора успешно изменены.\n\n");
                    }
                }
                system("pause");
                break;              //Выход из switch
            }
            case 4: showPass = showPass == true ? false : true; break;              //Изменение переменной которая показывает или скрывает пароль
            case 5: editFlag = true; break;
            default: break;
        }
        if (editFlag) break;
    }
    if (checkFile("db.dat")) {              //Если файл существует
        crypterTool(DECRYPT);               //Расшифровать
        if ((file = fopen("db.dat", "wb"))) {               //Если файл удалось пересоздать
            for (i = 0; i < usersLinesCounter; i++)             //Запись i-ого пользователя в файл
                fwrite((user + i), sizeof(USER), 1, file);
            fclose(file);               //Закрытие файла
        }
        else printf("[Ошибка!]Редактирование пользователей: Не удалось открыть файл с логинами/паролями! Файл отчищен!\n\n");               //Если файл не удалось пересоздать
        crypterTool(ENCRYPT);               //Зашифровать
    }
    else printf("[Ошибка!]Редактирование пользователей: Не удалось открыть файл с логинами/паролями!\n\n");             //Если файл не существует
}

void displayEditableUser(int i, bool showPass) {
    char yes[] = "Да", no[] = "Нет", mask[] = "**********";
    system("cls");
    printf("-----------------------------------------------------------------------------------\n");
    printf("|ЛОГИН:                       |ПАРОЛЬ:                      |ПРАВА АДМИНИСТРАТОРА:|\n");
    printf("-----------------------------------------------------------------------------------\n");
    printf("|%-29s|%-29s|%-21s|\n", (user + i)->login, showPass == true ? (user + i)->password : mask, (user + i)->isAdmin == 1 ? yes : no);
    printf("-----------------------------------------------------------------------------------\n\n");
}

void displayAllUsers(bool showPass) {
    char yes[] = "Да", no[] = "Нет", mask[] = "**********";
    printf("-----------------------------------------------------------------------------------------\n");
    printf("|№    |ЛОГИН:                       |ПАРОЛЬ:                      |ПРАВА АДМИНИСТРАТОРА:|\n");
    printf("-----------------------------------------------------------------------------------------\n");
    for (int i = 0; i < usersLinesCounter; i++)
        printf("|%-5i|%-29s|%-29s|%-21s|\n", i + 1, (user + i)->login, showPass == true ? (user + i)->password : mask, (user + i)->isAdmin == 1 ? yes : no);
    printf("-----------------------------------------------------------------------------------------\n\n");
}

void userReg(){
    bool isLoginExist = false;
    char *login = NULL, *password = NULL;
    FILE* file = NULL;
    user = (USER*)realloc(user, (usersLinesCounter + 1) * sizeof(USER));                    //Перераспределение памяти
    printf("Регистрация пользователя:\n");
    do {
        login = loginInput(29, "Введите логин: ");                  //Ввод логина
        for (int i = 0; i < usersLinesCounter; i++) {                   //Поиск введенного логина в массиве
            if (strcmp((user + i)->login, login) == 0) {                    //Если i-ый логин совпадает с введенным
                isLoginExist = true;
                break;              //Выход из цикла
            }
            else isLoginExist = false;
        }
        if (isLoginExist) {                 //Если такой логин найден
            printf("[Ошибка!]Такой аккаунт уже существует!");
            Sleep(1000);
            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);               //Стерание двух последних строк с экрана
        }
        else strcpy((user + usersLinesCounter)->login, login);              //Если такой логин не найден, скопировать в выделенную ячейку массива структур
    } while (isLoginExist);             //Пока такой логин будет не найден
    free(login);                //Освобождение переменной
    password = maskedPasswordInput(29, "Введите пароль: ");             //Ввод пароля
    strcpy((user + usersLinesCounter)->password, password);             //Копирование пароля в выделенную ячейку массива структур
    free(password);                 //Освобождение переменной
    (user + usersLinesCounter)->isAdmin = 0;                //Не давать права администратора
    if (checkFile("db.dat")) {              //Если файл существует
        crypterTool(DECRYPT);               //Расшифровать
        if ((file = fopen("db.dat", "ab+"))) {              //Если файл удалось открыть
            fwrite((user + usersLinesCounter), sizeof(USER), 1, file);              //Записать ячейку массива структур в файл
            fclose(file);               //Закрыть файл
            printf("\nВы успешно зарегистрировались!\n\n");
            _flushall();
            usersLinesCounter++;                //Счётчик пользователей ++
        }
        else printf("[Ошибка!]Добавление пользователей: Ошибка открытия файла с логинами/паролями! Пользователь не добавлен!\n\n");             //Если файл не удалось открыть
        crypterTool(ENCRYPT);               //Зашифровать
    }
    else printf("[Ошибка!]Добавление пользователей: Файл не существует!\n\n");              //Если файл не существует
    system("pause");
}


//Всё что связано с информацией
void membersOpenAdmin() {
    int choice = 1, ch = (int)NULL;
    bool isShowed = false;
    const char *line[] = { "Да", "Нет", NULL }, pointer = '>';
    if (!checkFile("info.dat")) {               //Если файл не существует
        printf("[Ошибка!]Открытие информации: Файл ещё не создан!\n");
        indicateCursor(false);              //Скрыть каретку ввода
        while (true) {
            if (ch == KEY_RETURN || ch == KEY_LEFT || ch == KEY_RIGHT || !isShowed) {               //Если введенный символ - символ ввода или символ стрелки вверх или вниз или меню не было выведено
                isShowed = true;
                printf("%c[2K\r", 27);              //Стереть строку с экрана
                if (ch == KEY_RETURN) {             //Если символ ввода
                    indicateCursor(true);               //Показывать каретку ввода
                    break;              //Выход их цикла
                }
                if (ch == KEY_LEFT) choice--;               //Если символ "стрелка влево"
                if (ch == KEY_RIGHT) choice++;              //Если символ "стрелка вправо"
                if (choice > 2) choice = 2;             //Если указатель выбора больше 2, вернуть его в конечное положение
                if (choice < 1) choice = 1;             //Если указатель выбора меньше 1, вернуть его в начальное положение
                printf("Создать файл? ");
                for (int i = 0; line[i]; i++) {             //Вывод меню выбора создания файла
                    if (choice == i + 1) {              //Если указатель выбора равен (i+1)-му индексу массива
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);               //Изменение цвета строки
                        printf("%c", pointer);              //Вывод указателя
                    }
                    printf(i + 1 == choice ? "%s " : " %s ", line[i]);              //Вывод строк меню
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);               //Изменение цвета строк
                }
            }
            ch = _getch();              //Ввод символа
        }
        if (choice == 1) {              //Если укзазатель равен 1
            if (createFile("info.dat")) {               //Если удалось создать файл
                printf("Открытие информации: Файл успешно создан!\n");
                membersInit();              //Инициализация участников
                system("pause");
            }               //Если файл не удалось создать
            else printf("[Ошибка!]Открытие информации: Не удалось создать файл!\n");
        }
    }
    else {              //Если файл существует
        membersInit();              //Инициализация участников
        system("pause");
    }
};

void membersOpenUser() {
    if (checkFile("info.dat"))              //Если файл существует
        membersInit();              //Инициализация участников
    else                //Если файл не существует
        printf("[Ошибка!]Открытие информации: Файл ещё не создан!\n\n");
}

void membersInit() {
    FILE *file = NULL;
    long fsize;
    if (info)               //Если указатель на массив структур не равен NULL
        printf("[Ошибка!]Открытие информации: Файл уже открыт!\n\n");
    else {              //Если указатель на массив структур равен NULL
        if ((file = fopen("info.dat", "rb+"))) {                //Если файл удалось открыть
            fseek(file, 0, SEEK_END);     //Установка указателя в файле на конец файла
            fsize = ftell(file);          //Подсчёт байтов в файле до указателя
            infoLinesCounter = fsize / sizeof(INFORMATION);             //Подсчёт количества участников
            rewind(file);               //Установка указателя на начало файла


            if (infoLinesCounter != 0) {                //Если в файле записан хотя бы один участник
                info = (INFORMATION *)malloc(infoLinesCounter * sizeof(INFORMATION));               //Выделение памяти
                for (int i = 0; i < infoLinesCounter; i++)              //Чтение информации из файла
                    fread((info + i), sizeof(INFORMATION), 1, file);
            }
            fclose(file);               //Закрыть файл
            printf("Открытие информации: Файл успешно открыт!\n\n");
        }
    }
}

void memberAdd() {
    FILE *file = NULL;
    time_t t = time(NULL);
    struct tm *aTm = localtime(&t);
    bool isMemberExist = false;
    char *firstname = NULL, *surname = NULL, *lastname = NULL, *country = NULL, *category = NULL, *model = NULL;
    if (!info)              //Если указатель на массив структур равен NULL
        printf("[Ошибка!]Добавление информации: Файл не открыт!\n\n");
    else if (!(file = fopen("info.dat", "ab+")))                //Если не удалось открыть файл для добавления
        printf("[Ошибка!]Добавление информации: Не удалось открыть файл для добавления!\n");
    else {              //Если удалось открыть файл для добавления
        info = (INFORMATION *)realloc(info, (infoLinesCounter + 1) * sizeof(INFORMATION));              //Перераспределение памяти
        printf("Добавление участника.\n");
        do {
            do {
                (info + infoLinesCounter)->number = checkToEnterOnlyInt(3, "Введите номер участника: ");                //Ввод номера участника
                if ((info + infoLinesCounter)->number < 1) {                //Если введенный номер < 1
                    printf("[Ошибка!]Введите число больше 0!");
                    Sleep(1000);
                    printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);               //Стирание двух последних строк с экрана
                }
            } while ((info + infoLinesCounter)->number < 1);                //Пока не будет введен номер > 0
            for (int i = 0; i < infoLinesCounter; i++) {                //Поиск участника с таким номером в массиве структур
                if ((info + i)->number == (info + infoLinesCounter)->number) {              //Если i-ый участник имеет такой номер
                    isMemberExist = true;
                    break;              //Выход из цикла
                }
                else isMemberExist = false;
            }
            if (isMemberExist) {                //Если такой участник был найден
                printf("[Ошибка!]Участник с таким номером уже существует!");
                Sleep(1000);
                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);               //Стирание двух последних строк с экрана
            }
        } while (isMemberExist);                //Пока участник с таким номером будет не найден
        firstname = stringInputCheck(15, "Введите имя участника: ");                //Ввод имени участника
        strcpy((info + infoLinesCounter)->fullname.firstname, firstname);               //Копирование имени участника в ячейку массива структур
        free(firstname);                //Освобождение памяти для переменной, содержащей имя участника
        surname = stringInputCheck(15, "Введите фамилию участника: ");              //Ввод фамилии участника
        strcpy((info + infoLinesCounter)->fullname.surname, surname);               //Копирование фамилии участника в ячейку массива структур
        free(surname);              //Освобождение памяти для переменной, содержащей фамилию участника
        lastname = stringInputCheck(15, "Введите отчество участника: ");                //Ввод отчества участника
        strcpy((info + infoLinesCounter)->fullname.lastname, lastname);             //Копирование отчества участника в ячейку массива структур
        free(lastname);             //Освобождение памяти для переменной, содержащей отчество участника
        country = stringInputCheck(15, "Введите страну участника: ");               //Ввод страны участника
        strcpy((info + infoLinesCounter)->country, country);                //Копирование отчества участника в ячейку массива структур
        free(country);              //Освобождение памяти для переменной, содержащей страну участника
        dateOfBirthInput(&((info + infoLinesCounter)->dateOfBirth.day), &((info + infoLinesCounter)->dateOfBirth.month), &((info + infoLinesCounter)->dateOfBirth.year), "Введите день рождения участника(в формате дд.мм.гггг): ");
        if ((info + infoLinesCounter)->dateOfBirth.month > aTm->tm_mon + 1)             //Если введенный месяц меньше текущего месяца
            (info + infoLinesCounter)->dateOfBirth.age = 2018 - (info + infoLinesCounter)->dateOfBirth.year;                //От 2018 отнимается введенный год и получается возраст
        else (info + infoLinesCounter)->dateOfBirth.age = 2019 - (info + infoLinesCounter)->dateOfBirth.year;               //От 2018 отнимается введенный год и получается возраст
        category = categoryInput(10, "Введите разряд участника: ");             //Ввод разряда участника
        strcpy((info + infoLinesCounter)->category, category);              //Копирование разряда участника в ячейку массива структур
        free(category);             //Освобождение памяти для переменной, содержащей страну участника
        model = stringInputCheck(15, "Введите модель коньков участника: ");             //Ввод модель коньков участника
        strcpy((info + infoLinesCounter)->model, model);                //Копирование модели коньков учатсника в ячейку массива структур
        free(model);                //Освобождение памяти для переменной, содержащей модель коньков участника
        do {
            (info + infoLinesCounter)->points = checkToEnterOnlyInt(4, "Введите количество очков участника: ");             //Ввод количества очков участника
            if ((info + infoLinesCounter)->points < 0 || (info + infoLinesCounter)->points > 9999) {                //Если введенное количество очков участника меньше 0 или больше 9999
                printf("[Ошибка!]Введите число от 0 до 9999!");
                Sleep(1000);
                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);               //Стирание двух последних строк участника
            }
        } while ((info + infoLinesCounter)->points < 0 || (info + infoLinesCounter)->points > 9999);                //Пока не будет введено количество очков участника больше 0 или меньше 9999
        timeOfLapInput(&((info + infoLinesCounter)->timeOfLap.minutes), &((info + infoLinesCounter)->timeOfLap.seconds), "Введите время круга участника(в формате мм:сс): ");
        fwrite((info + infoLinesCounter), sizeof(INFORMATION), 1, file);                //Запись ячейки массива структур в файл
        _flushall();
        fclose(file);               //Закрытие файла
        infoLinesCounter++;             //Счётчик количества учатсников ++
        printf("Участник успешно добавлен!\n\n");
    }
}

void memberDelete() {
    int delNumber = 0, i = 0;
    bool isNumberExist = false;
    FILE *file = NULL;
    if (!info) {                //Если указатель на массив структур равен NULL
        printf("[Ошибка!]Удаление информации: Файл не открыт!\n\n");
    }
    else if (infoLinesCounter == 0) {               //Если количество участников равно нулю
        printf("[Ошибка!]Удаление информации: Файл пуст!\n\n");
    }
    else {
        displayAllMembers();                //Вывод всех участников на экран
        printf("Удаление участника.\n");
        delNumber = checkToEnterOnlyInt(3, "Введите номер участника для удаления: ");               //Ввод номера участника для удаления
        for (i = 0; i < infoLinesCounter; i++) {                //Поиск участника в массиве структур с таким номером
            if (delNumber == (info + i)->number) {              //Если введённый номер равен номеру i-го участника
                isNumberExist = true;
                break;              //Выход из цикла
            }
            else isNumberExist = false;
        }
        if (!isNumberExist) {               //Если введенный номер не найден
            printf("[Ошибка!]Участника с таким номером не существует!\n\n");
            return;             //Выход из функции
        }
        for (int j = i; j < infoLinesCounter; j++)              //Сместить все ячейки после удаляемой влево на одну
            *(info + j) = *(info + (j + 1));
        info = (INFORMATION*)realloc(info, sizeof(INFORMATION)*infoLinesCounter);               //Перераспределение памяти
        infoLinesCounter--;             //Счётчик количества участников --
        if (checkFile("info.dat")) {                //Если файл существует
            if ((file = fopen("info.dat", "wb"))) {             //Если файл удалось пересоздать
                for (int j = 0; j < infoLinesCounter; j++)              //Запись ячеек массива структур в файл
                    fwrite((info + j), sizeof(INFORMATION), 1, file);
                fclose(file);               //Закрытие файла
                system("cls");
                displayAllMembers();
                printf("Участник успешно удалён!\n\n");
            }
            else printf("[Ошибка!]Удаление информации: Не удалось перезаписать файл! Файл отчищен!\n\n");               //Если файл не удалось пересоздать
        }
        else printf("[Ошибка!]Удаление информации: Не удалось найти файл!\n\n");                //Если файл не существует
    }
}

void memberEdit() {
    time_t t = time(NULL);
    FILE *file = NULL;
    struct tm *aTm = localtime(&t);
    bool isMemberExist = false, isNumberExist = false, infoEditFlag = false;
    int number = 0, i = 0, j = 0, newNumber = 0, newBirthDay = 0, newBirthMonth = 0, newBirthYear = 0;
    char *firstname = NULL, *surname = NULL, *lastname = NULL, *country = NULL, *category = NULL, *model = NULL;
    if (!info) {                //Если указатель на массив структур равен NULL
        printf("[Ошибка!]Редактирование информации: Файл не открыт!\n\n");
        system("pause");
    }
    else if (infoLinesCounter == 0) {               //Если счётчик участников равен нулю
        printf("[Ошибка!]Редактирование информации: Файл пуст!\n\n");
        system("pause");
    }
    else {
        displayAllMembers();                //Вывод всех участников на экран
        number = checkToEnterOnlyInt(3, "Введите номер участника, которого нужно отредактировать: ");               //Ввод номера участника
        for (i = 0; i < infoLinesCounter; i++) {                //Поиск участника с таким номером в массиве структур
            if ((info + i)->number == number) {             //Если i-ый участник имеет такой номер
                isMemberExist = true;
                break;              //Выход из цикла
            }
            else isMemberExist = false;
        }
        if (!isMemberExist) {               //Если участник с таким номером не найден
            printf("[Ошибка!]Участника с таким номером не существует!\n\n");
            system("pause");
            return;             //Выход из функции
        }
        while (!infoEditFlag) {
            switch (memberEditMenu(i)) {                //Вывод информации об редактируемом участнике и меню редактирования
                case 1: {
                    printf("Изменеие номера участника.\n");
                    do {
                        do {
                            newNumber = checkToEnterOnlyInt(3, "Введите новый номер участника: ");                  //Ввод нового номера участника
                            if (newNumber < 1) {                //Если введенный номер меньше 1
                                printf("[Ошибка!]Введите число больше 0!");
                                Sleep(1000);
                                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);               //Стирание двух полседних строк с экрана
                            }
                        } while (newNumber < 1);                //Пока не будет введен номер больше 0
                        for (j = 0; j < infoLinesCounter; j++) {                    //Поиск участника с таким номером в масмиве структур
                            if ((info + j)->number == newNumber) {              //Если j-ый участник имеет такой номер
                                isNumberExist = true;
                                break;              //Выход из цикла
                            }
                            else isNumberExist = false;
                        }
                        if (isNumberExist) {                //Если участник с таким номером найден
                            printf("[Ошибка!]Участник с таким номером уже существует!");
                            Sleep(1000);
                            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);               //Стирание двух последних строк
                        }
                    } while (isNumberExist);                //Пока не будет введен не существующий номер
                    (info + i)->number = newNumber;             //Изменение номера на введенный у j-ого участника
                    displayEditableMember(i);               //Вывод всей информации об редактируемом участнике
                    printf("Номер участника успешно изменен!\n\n");
                    system("pause");
                    break;              //Выход из switch
                }
                case 2: {
                    printf("Изменение имени участника.\n");
                    firstname = stringInputCheck(15, "Введите новое имя участника: ");              //Ввод новое имя участника
                    strcpy((info + i)->fullname.firstname, firstname);              //Копирование нового имени в редактируемую ячейку массива структур
                    free(firstname);                //Освобождение памяти для переменной, содержащей имя участника
                    displayEditableMember(i);               //Вывод всей информации об редактируемом участнике
                    printf("Имя участника успешно изменено!\n\n");
                    system("pause");
                    break;              //Выход из switch
                }
                case 3: {
                    printf("Изменение фамилии участника.\n");
                    surname = stringInputCheck(15, "Введите новую фамилию участника: ");                //Ввод новой фамилии участника
                    strcpy((info + i)->fullname.surname, surname);              //Копирование новой фамилии в редактируемую ячейку массива структур
                    free(surname);              //Освобождение памяти для переменной, содержащей фамилию участника
                    displayEditableMember(i);               //Вывод всей информации об редактируемом участнике
                    printf("Фамилия участника успешна изменена!\n\n");
                    system("pause");
                    break;              //Выход из switch
                }
                case 4: {
                    printf("Изменение отчества участника.\n");
                    lastname = stringInputCheck(15, "Введите новое отчество участника: ");              //Ввод нового отчества участника
                    strcpy((info + i)->fullname.lastname, lastname);                //Копирование нового отчества в редактируемую ячейку массива стурктур
                    free(lastname);             //Освобождение памяти для переменной, сожержащей отчество участника
                    displayEditableMember(i);               //Вывод всей информации об редактируемом участнике
                    printf("Отчество участника успешно изменено!\n\n");
                    system("pause");
                    break;                  //Выход из switch
                }
                case 5: {
                    printf("Изменение страны участника.\n");
                    country = stringInputCheck(15, "Введите новую страну участника: ");             //Ввод новой страны участника
                    strcpy((info + i)->country, country);               //Копирование новой страны в редактируемую ячейку массива структур
                    free(country);              //Освобождение памяти для переменной, содержащей страну участника
                    displayEditableMember(i);               //Вывод всей информации об редактируемом участнике
                    printf("Страна участника успешно изменена.\n\n");
                    system("pause");
                    break;              //Выход из switch
                }
                case 6: {
                    printf("Изменение даты рождения участника.\n");
                    dateOfBirthInput(&((info + i)->dateOfBirth.day), &((info + i)->dateOfBirth.month), &((info + i)->dateOfBirth.year), "Введите новую дату рождения(в формате дд.мм.гггг): ");
                    if ((info + i)->dateOfBirth.month >= aTm->tm_mon + 1)               //Если новый месяц меньше текущего месяца
                        (info + i)->dateOfBirth.age = 2018 - (info + i)->dateOfBirth.year;              //Вычисление возраста
                    else
                        (info + i)->dateOfBirth.age = 2019 - (info + i)->dateOfBirth.year;
                    displayEditableMember(i);               //Вывод всей информации об редактируемом участнике
                    printf("Дата рождения участника успешно изменена!\n\n");
                    system("pause");
                    break;              //Выход из switch
                }
                case 7: {
                    printf("Изменение разряда участника.\n");
                    category = categoryInput(10, "Введите новый разряд участника: ");               //Ввод нового разряда участника
                    strcpy((info + i)->category, category);                 //Копирование нового разряда в редактруемую ячейку массива структур
                    free(category);                 //Освобождение памяти для переменной, содержащей новый разряд
                    displayEditableMember(i);               //Вывод всей информации об редактируемом участнике
                    printf("Разряд участника успешно изменен!\n\n");
                    system("pause");
                    break;              //Выход из switch
                }
                case 8: {
                    printf("Изменение модели коньков участника.\n");
                    model = stringInputCheck(15, "Введите новую модель коньков участника: ");               //Ввод новой модели коньков участника
                    strcpy((info + i)->model, model);               //Копирование новой модели коньков участника в редактируемую ячейку
                    free(model);                //Освобождение памяти для переменной, содержащей новую модель коньков
                    displayEditableMember(i);               //Вывод всей информации об редактируемом участнике
                    printf("Модель коньков участника успешно изменена!\n\n");
                    system("pause");
                    break;              //Выход из switch
                }
                case 9: {
                    printf("Изменение количества очков участника.\n");
                    do {
                        (info + i)->points = checkToEnterOnlyInt(4, "Введите новое количество очков участника: ");              //Ввод нового количества очков участника
                        if ((info + i)->points < 0 || (info + i)->points > 9999) {              //Если введенное количество очков меньше 0 и больше 9999
                            printf("[Ошибка!]Введите число от 0 до 9999!");
                            Sleep(1000);
                            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);               //Стирание двух последних строк с экрана
                        }
                    } while ((info + i)->points < 0 || (info + i)->points > 9999);              //Пока не будут введены новые очки участника больше -1 или меньше 10000
                    displayEditableMember(i);               //Вывод всей информации об редактируемом участнике
                    printf("Количество очков участника успешно изменено!\n\n");
                    system("pause");
                    break;              //Выход из switch
                }
                case 10: {
                    printf("Изменение времени круга участника.\n");
                    timeOfLapInput(&((info + i)->timeOfLap.minutes), &((info + i)->timeOfLap.seconds), "Введите новое время круга участника(в формате мм:сс): ");
                    displayEditableMember(i);               //Вывод всей информации об редактируемом участнике
                    printf("Время круга участника успешно изменено!\n\n");
                    system("pause");
                    break;              //Выход из switch
                }
                case 11: infoEditFlag = true; break;
                default: break;
            }
        }
        if (checkFile("info.dat")) {                //Если файл существует
            if ((file = fopen("info.dat", "wb"))) {             //Если удалось пересоздать файл
                for (j = 0; j < infoLinesCounter; j++)              //Запись ячеек массива структур в файл
                    fwrite((info + j), sizeof(INFORMATION), 1, file);
                fclose(file);               //Закрытие файла
            }
            else printf("[Ошибка!]Редактирование информации: Не удалось перезаписать файл! Файл отчищен!\n");               //Если не удалось пересоздать файл
        }
        else printf("[Ошибка!]Редактирование информации: Не удалось найти файл!\n");                //Если файл не существует
    }
}

void displayEditableMember(int i) {
    system("cls");
    printf("-------------------------------------------------------------------------------------------------------------------------------------------\n"
           "|НОМЕР|ИМЯ             ФАМИЛИЯ         ОТЧЕСТВО       |    СТРАНА     |ДАТА  РОЖДЕНИЯ|ВОЗРАСТ|  РАЗРЯД  | МОДЕЛЬ КОНЬКОВ |ОЧКИ|ВРЕМЯ КРУГА|\n"
           "-------------------------------------------------------------------------------------------------------------------------------------------\n"
           "|%-3i  |%-15s %-15s %-15s|%-15s|  %02i/%02i/%04i  |  %-3i  |%-10s|%-16s|%-4i|   %02i:%02i   |\n",
           (info + i)->number, (info + i)->fullname.firstname, (info + i)->fullname.surname,
           (info + i)->fullname.lastname, (info + i)->country,
           (info + i)->dateOfBirth.day, (info + i)->dateOfBirth.month, (info + i)->dateOfBirth.year,
           (info + i)->dateOfBirth.age, (info + i)->category,
           (info + i)->model, (info + i)->points, (info + i)->timeOfLap.minutes, (info + i)->timeOfLap.seconds);
    printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");
}

void displayAllMembers() {
    system("cls");
    if (!info)              //Если указатель на массив структур равен NULL
        printf("[Ошибка!]Вывод информации: Файл еще не открыт!\n\n");
    else if (infoLinesCounter == 0)             //Если нет ни одного участника
        printf("[Ошибка!]Вывод информации: Файл пуст!\n\n");
    else {
        printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("|НОМЕР|ИМЯ             ФАМИЛИЯ         ОТЧЕСТВО       |    СТРАНА     |ДАТА  РОЖДЕНИЯ|ВОЗРАСТ|  РАЗРЯД  | МОДЕЛЬ КОНЬКОВ |ОЧКИ|ВРЕМЯ КРУГА|\n");
        printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");
        for (int i = 0; i < infoLinesCounter; i++) {
            printf("|%-3i  |%-15s %-15s %-15s|%-15s|  %02i/%02i/%04i  |  %-3i  |%-10s|%-16s|%-4i|   %02i:%02i   |\n",
                   (info + i)->number, (info + i)->fullname.firstname, (info + i)->fullname.surname, (info + i)->fullname.lastname, (info + i)->country,
                   (info + i)->dateOfBirth.day, (info + i)->dateOfBirth.month, (info + i)->dateOfBirth.year, (info + i)->dateOfBirth.age, (info + i)->category,
                   (info + i)->model, (info + i)->points, (info + i)->timeOfLap.minutes, (info + i)->timeOfLap.seconds);
        }
        printf("-------------------------------------------------------------------------------------------------------------------------------------------\n\n");
    };
}


//Всё что связано с фильтрацией и поиском
void pointsFilter() {
    int points = 0;
    bool isAtLeastOneMember = false;
    if (!info)              //Если указатель на массив структур равен NULL
        printf("[Ошибка!]Поиск и фильтрация: Файл не открыт!\n\n");
    else if (infoLinesCounter == 0)             //Если нет ни одного участника
        printf("[Ошибка!]Поиск и фильтрация: Файл пуст!\n\n");
    else {
        do {
            points = checkToEnterOnlyInt(4, "Введите количество очков: ");              //Ввод количества очков для фильтра
            if (points < 0 || points > 9999) {              //Если введенное количество очков меньше 0 или больше 9999
                printf("[Ошибка!]Введите число больше 0 и меньше 9999!");
                Sleep(1000);
                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);               //Стирание двух последних строк с экрана
            }
        } while (points < 0 || points > 9999);              //Пока не будут введено количетсво очков больше -1 или меньше 10000
        system("cls");              //Очистка экрана
        printf("Участники, у которых очков больше %i: ", points);
        for (int i = 0; i < infoLinesCounter; i++) {                //Поиск участников с количеством очков больше введенного
            if ((info + i)->points > points) {              //Если у i-го участнико количество очков больше введенного
                if (!isAtLeastOneMember) {              //Если найден хотя бы один такой участник
                    printf("\n-------------------------------------------------------------------------------------------------------------------------------------------\n");
                    printf("|НОМЕР|ИМЯ             ФАМИЛИЯ         ОТЧЕСТВО       |    СТРАНА     |ДАТА  РОЖДЕНИЯ|ВОЗРАСТ|  РАЗРЯД  | МОДЕЛЬ КОНЬКОВ |ОЧКИ|ВРЕМЯ КРУГА|\n");
                    printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");
                }
                printf("|%-3i  |%-15s %-15s %-15s|%-15s|  %02i/%02i/%-4i  |  %-3i  |%-10s|%-16s|%-4i|   %02i:%02i   |\n",
                       (info + i)->number, (info + i)->fullname.firstname, (info + i)->fullname.surname,
                       (info + i)->fullname.lastname, (info + i)->country, (info + i)->dateOfBirth.day,
                       (info + i)->dateOfBirth.month, (info + i)->dateOfBirth.year, (info + i)->dateOfBirth.age,
                       (info + i)->category, (info + i)->model, (info + i)->points, (info + i)->timeOfLap.minutes,
                       (info + i)->timeOfLap.seconds);
                isAtLeastOneMember = true;
            }
            if (isAtLeastOneMember && i == infoLinesCounter - 1)                //Если найден хотя бы один такой участник и массив полностю перебран
                printf("-------------------------------------------------------------------------------------------------------------------------------------------\n\n");
        }
        if (!isAtLeastOneMember)                //Если таких участников не найдено
            printf("Нет ни одного участника с очками больше %i.\n\n", points);
    }
}

void timeOfLapFilter() {
    int minutesOfLap = 0, secondsOfLap = 0;
    bool isAtLeastOneMember = false;
    if (!info)                //Если указатель на массив структур равен NULL
        printf("[Ошибка!]Поиск и фильтрация: Файл не открыт!\n\n");
    else if (infoLinesCounter == 0)             //Если нет ни одного участника
        printf("[Ошибка!]Поиск и фильтрация: Файл пуст!\n\n");
    else {
        timeOfLapInput(&minutesOfLap, &secondsOfLap, "Введите время круга для фильтра(в формате мм:сс): ");
        system("cls");              //Очистка экрана
        printf("Участники, у которых время круга меньше %02i:%02i : ", minutesOfLap, secondsOfLap);
        for (int i = 0; i < infoLinesCounter; i++) {                //Поиск участников, у которых время круга меньше введенного
            if ((info + i)->timeOfLap.minutes < minutesOfLap)               //Если у i-го учатсника минуты круга меньше введенных
                if ((info + i)->timeOfLap.seconds < ((info + i)->timeOfLap.minutes == minutesOfLap ? secondsOfLap : 60)) {              //Если введенные минуты равно минутам i-го учатсника то секунды сравниваются с введенными
                    if (!isAtLeastOneMember) {              //Если найден хотя бы один участник
                        printf("\n-------------------------------------------------------------------------------------------------------------------------------------------\n");
                        printf("|НОМЕР|ИМЯ             ФАМИЛИЯ         ОТЧЕСТВО       |    СТРАНА     |ДАТА  РОЖДЕНИЯ|ВОЗРАСТ|  РАЗРЯД  | МОДЕЛЬ КОНЬКОВ |ОЧКИ|ВРЕМЯ КРУГА|\n");
                        printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");
                    }
                    printf("|%-3i  |%-15s %-15s %-15s|%-15s|  %02i/%02i/%-4i  |  %-3i  |%-10s|%-16s|%-4i|   %02i:%02i   |\n",
                           (info + i)->number, (info + i)->fullname.firstname, (info + i)->fullname.surname,
                           (info + i)->fullname.lastname, (info + i)->country, (info + i)->dateOfBirth.day,
                           (info + i)->dateOfBirth.month, (info + i)->dateOfBirth.year, (info + i)->dateOfBirth.age,
                           (info + i)->category, (info + i)->model, (info + i)->points, (info + i)->timeOfLap.minutes,
                           (info + i)->timeOfLap.seconds);
                    isAtLeastOneMember = true;
                }
            if (isAtLeastOneMember && i == infoLinesCounter - 1)                //Если найден хотябы один участник и массив полностью перебран
                printf("-------------------------------------------------------------------------------------------------------------------------------------------\n\n");
        }
        if (!isAtLeastOneMember)                //Если не найдено ни одно участника
            printf("Нет ни одного участника с временем круга меньше %02i:%02i.\n\n", minutesOfLap, secondsOfLap);
    }
}

void ageFilter() {
    int age = 0;
    bool isAtLeastOneMember = false;
    if (!info)              //Если указатель на массив структур равен NULL
        printf("[Ошибка!]Поиск и фильтрация: Файл не открыт!\n\n");
    else if (infoLinesCounter == 0)             //Если нет ни одного участника
        printf("[Ошибка!]Поиск и фильтрация: Файл пуст!\n\n");
    else {
        do {
            age = checkToEnterOnlyInt(3, "Введите возраст: ");              //Ввод возраста для поиска
            if (age < 0 || age > 119) {             //Если введенный возраст меньше 0 или больше 119
                printf("[Ошибка!]Введите число больше 0 и меньше 119!\n");
                Sleep(1000);
                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);               //Стирание двух последних строк с экрана
            }
        } while (age < 0 || age > 119);             //Пока не будет введен возраст больше -1 или меньше 119
        system("cls");              //Очистка экрана
        printf("Участники, возраст которых больше %i: ", age);
        for (int i = 0; i < infoLinesCounter; i++) {                //Поиск участников
            if ((info + i)->dateOfBirth.age > age) {                //Если возраст i-го участника больше введенного
                if (!isAtLeastOneMember) {              //Если найден хотя бы один участник
                    printf("\n-------------------------------------------------------------------------------------------------------------------------------------------\n");
                    printf("|НОМЕР|ИМЯ             ФАМИЛИЯ         ОТЧЕСТВО       |    СТРАНА     |ДАТА  РОЖДЕНИЯ|ВОЗРАСТ|  РАЗРЯД  | МОДЕЛЬ КОНЬКОВ |ОЧКИ|ВРЕМЯ КРУГА|\n");
                    printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");
                }
                printf("|%-3i  |%-15s %-15s %-15s|%-15s|  %02i/%02i/%-4i  |  %-3i  |%-10s|%-16s|%-4i|   %02i:%02i   |\n",
                       (info + i)->number, (info + i)->fullname.firstname, (info + i)->fullname.surname,
                       (info + i)->fullname.lastname, (info + i)->country, (info + i)->dateOfBirth.day,
                       (info + i)->dateOfBirth.month, (info + i)->dateOfBirth.year, (info + i)->dateOfBirth.age,
                       (info + i)->category, (info + i)->model, (info + i)->points, (info + i)->timeOfLap.minutes,
                       (info + i)->timeOfLap.seconds);
                isAtLeastOneMember = true;
            }
            if (isAtLeastOneMember && i == infoLinesCounter - 1)                //Если найден хотя бы один участник и массив полностью перебран
                printf("-------------------------------------------------------------------------------------------------------------------------------------------\n\n");
        }
        if (!isAtLeastOneMember)                //Если не найден ни один участик
            printf("Нет ни одного участника с очками больше %i.\n\n", age);
    }
}

void yearOfBirthFilter() {
    int yearOfBirth = 0;
    bool isAtLeastOneMember = false;
    if (!info)              //Если указатель на массив структур равен NULL
        printf("[Ошибка!]Поиск и фильтрация: Файл не открыт!\n\n");
    else if (infoLinesCounter == 0)             //Если нет ни одного участника
        printf("[Ошибка!]Поиск и фильтрация: Файл пуст!\n\n");
    else {
        do {
            yearOfBirth = checkToEnterOnlyInt(4, "Введите год рождения: ");             //Ввод года рождения для фильтрации
            if (yearOfBirth < 1900 || yearOfBirth > 2019) {             //Если введенный год рождения меньше 1900 или больше 2019
                printf("[Ошибка!]Введите число больше 1900 и меньше 2019!\n");
                Sleep(1000);
                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);               //Стирание двух последних строк с экрана
            }
        } while (yearOfBirth < 1900 || yearOfBirth > 2019);             //Пока не будет введен год рождения больше 1899 или меньше 2020
        system("cls");              //Очистка экрана
        printf("Участники, год рождения у которых больше %i: ", yearOfBirth);
        for (int i = 0; i < infoLinesCounter; i++) {                //Поиск участников
            if ((info + i)->dateOfBirth.year > yearOfBirth) {               //Если у i-го участника возраст больше введенного
                if (!isAtLeastOneMember) {              //Если найден хотя бы один участник
                    printf("\n-------------------------------------------------------------------------------------------------------------------------------------------\n");
                    printf("|НОМЕР|ИМЯ             ФАМИЛИЯ         ОТЧЕСТВО       |    СТРАНА     |ДАТА  РОЖДЕНИЯ|ВОЗРАСТ|  РАЗРЯД  | МОДЕЛЬ КОНЬКОВ |ОЧКИ|ВРЕМЯ КРУГА|\n");
                    printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");
                }
                printf("|%-3i  |%-15s %-15s %-15s|%-15s|  %02i/%02i/%-4i  |  %-3i  |%-10s|%-16s|%-4i|   %02i:%02i   |\n",
                       (info + i)->number, (info + i)->fullname.firstname, (info + i)->fullname.surname,
                       (info + i)->fullname.lastname, (info + i)->country, (info + i)->dateOfBirth.day,
                       (info + i)->dateOfBirth.month, (info + i)->dateOfBirth.year, (info + i)->dateOfBirth.age,
                       (info + i)->category, (info + i)->model, (info + i)->points, (info + i)->timeOfLap.minutes,
                       (info + i)->timeOfLap.seconds);
                isAtLeastOneMember = true;
            }
            if (isAtLeastOneMember && i == infoLinesCounter - 1) {              //Если найден хотябы один участник и массив полностю перебран
                printf("-------------------------------------------------------------------------------------------------------------------------------------------\n\n");
            }
        }
        if (!isAtLeastOneMember)                //Если ни одного участника не найдено
            printf("Нет ни одного участника с годом рождения больше %i.\n\n", yearOfBirth);
    }
}

void timeOfLapSorting() {
    FILE* file = NULL;
    INFORMATION tmp;
    if (!info)              //Если указатель на массив структур равен NULL
        printf("[Ошибка!]Сортировка: Файл не открыт!\n\n");
    else if (infoLinesCounter == 0)             //Если нет ни одного участника
        printf("[Ошибка!]Сортировка: Файл пуст!\n\n");
    else {
        if ((file = fopen("info.dat", "wb"))) {             //Если удалось открыть файл для перезаписи
            for (int i = 1; i < infoLinesCounter; i++)              //Сортировка вставками
                for (int j = i; j > 0; j--)
                    if ((info + (j - 1))->timeOfLap.minutes == (info + j)->timeOfLap.minutes) {
                        if ((info + (j - 1))->timeOfLap.seconds > (info + j)->timeOfLap.seconds) {
                            tmp = *(info + (j - 1));
                            *(info + (j - 1)) = *(info + j);
                            *(info + j) = tmp;
                        }
                    }
                    else if ((info + (j - 1))->timeOfLap.minutes > (info + j)->timeOfLap.minutes) {
                        tmp = *(info + (j - 1));
                        *(info + (j - 1)) = *(info + j);
                        *(info + j) = tmp;
                    }
            for (int j = 0; j < infoLinesCounter; j++)              //Запись ячеек массива структур в файл
                fwrite((info + j), sizeof(INFORMATION), 1, file);
            fclose(file);               //Закрытие файла
            printf("Сортировка: Участники успешно отсортированы!\n\n");
        }               //Если не удалось открыть файл для перезаписи
        else printf("[Ошибка!]Сортировка: Не удалось открыть файл! Файл отчищен!\n\n");
    }
}

void numberSearch() {
    int number = 0;
    bool isFounded = false;
    if (!info)              //Если указатель на массив структур равен NULL
        printf("[Ошибка!]Поиск и фильтрация: Файл не открыт!\n\n");
    else if (infoLinesCounter == 0)             //Если нет ни одного участника
        printf("[Ошибка!]Поиск и фильтрация: Файл пуст!\n\n");
    else {
        do {
            number = checkToEnterOnlyInt(3, "Введите номер: ");             //Ввод номера для поиска
            if (number < 0) {               //Если введенный номер меньше 0
                printf("[Ошибка!]Введите число больше 0!\n");
                Sleep(1000);
                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);               //Стирание двух последних строк
            }
        } while (number < 0);               //Пока не будет введен номер больше -1
        system("cls");              //Очистка экрана
        printf("Участник, номер которого %i: ", number);
        for (int i = 0; i < infoLinesCounter; i++) {                //Поиск участников
            if ((info + i)->number == number) {             //Если номер i-го участника равен введенному
                printf("\n-------------------------------------------------------------------------------------------------------------------------------------------\n");
                printf("|НОМЕР|ИМЯ             ФАМИЛИЯ         ОТЧЕСТВО       |    СТРАНА     |ДАТА  РОЖДЕНИЯ|ВОЗРАСТ|  РАЗРЯД  | МОДЕЛЬ КОНЬКОВ |ОЧКИ|ВРЕМЯ КРУГА|\n");
                printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");
                printf("|%-3i  |%-15s %-15s %-15s|%-15s|  %02i/%02i/%-4i  |  %-3i  |%-10s|%-16s|%-4i|   %02i:%02i   |\n",
                       (info + i)->number, (info + i)->fullname.firstname, (info + i)->fullname.surname,
                       (info + i)->fullname.lastname, (info + i)->country, (info + i)->dateOfBirth.day,
                       (info + i)->dateOfBirth.month, (info + i)->dateOfBirth.year, (info + i)->dateOfBirth.age,
                       (info + i)->category, (info + i)->model, (info + i)->points, (info + i)->timeOfLap.minutes,
                       (info + i)->timeOfLap.seconds);
                printf("-------------------------------------------------------------------------------------------------------------------------------------------\n\n");
                isFounded = true;
                break;              //Выход из цикла
            }
        }
        if (!isFounded)             //Если такой участник не найден
            printf("Участник с номером %i не найден.\n\n", number);
    }
}

void surnameSearch() {
    bool isAtLeastOneMember = false;
    char *surname = NULL;
    if (!info)              //Если указатель на массив структур равен NULL
        printf("[Ошибка!]Поиск и фильтрация: Файл не открыт!\n\n");
    else if (infoLinesCounter == 0)             //Если нет ни одного участника
        printf("[Ошибка!]Поиск и фильтрация: Файл пуст!\n\n");
    else {
        surname = stringInputCheck(15, "Введите фамилию: ");                //Ввод фамилии для поиска
        system("cls");              //Очистка экрана
        printf("Участники, с фамилией %s: ", surname);
        for (int i = 0; i < infoLinesCounter; i++) {                //Поиск участников
            if (strcmp((info + i)->fullname.surname, surname) == 0) {               //Если фамилия i-го участника такая же как введенная
                if (!isAtLeastOneMember) {              //Если найден хотя бы один участник
                    printf("\n-------------------------------------------------------------------------------------------------------------------------------------------\n");
                    printf("|НОМЕР|ИМЯ             ФАМИЛИЯ         ОТЧЕСТВО       |    СТРАНА     |ДАТА  РОЖДЕНИЯ|ВОЗРАСТ|  РАЗРЯД  | МОДЕЛЬ КОНЬКОВ |ОЧКИ|ВРЕМЯ КРУГА|\n");
                    printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");
                }
                printf("|%-3i  |%-15s %-15s %-15s|%-15s|  %02i/%02i/%-4i  |  %-3i  |%-10s|%-16s|%-4i|   %02i:%02i   |\n",
                       (info + i)->number, (info + i)->fullname.firstname, (info + i)->fullname.surname,
                       (info + i)->fullname.lastname, (info + i)->country, (info + i)->dateOfBirth.day,
                       (info + i)->dateOfBirth.month, (info + i)->dateOfBirth.year, (info + i)->dateOfBirth.age,
                       (info + i)->category, (info + i)->model, (info + i)->points, (info + i)->timeOfLap.minutes,
                       (info + i)->timeOfLap.seconds);
                isAtLeastOneMember = true;
            }
            if (isAtLeastOneMember && i == infoLinesCounter - 1)                //Если хотя бы один участник найден и массив полностью перебран
                printf("-------------------------------------------------------------------------------------------------------------------------------------------\n\n");
        }
        if (!isAtLeastOneMember)                //Если ни один участник не найден
            printf("Нет ни одного участника с фамилией %s.\n\n", surname);
    }
}

void countrySearch() {
    bool isAtLeastOneMember = false;
    char *country = NULL;
    if (!info)              //Если указатель на массив структур равен NULL
        printf("[Ошибка!]Поиск и фильтрация: Файл не открыт!\n\n");
    else if (infoLinesCounter == 0)             //Если нет ни одного участника
        printf("[Ошибка!]Поиск и фильтрация: Файл пуст!\n\n");
    else {
        country = stringInputCheck(15, "Введите страну: ");             //Ввод страны
        system("cls");              //Очистка экрана
        printf("Участники, из страны %s: ", country);
        for (int i = 0; i < infoLinesCounter; i++) {                //Поиск учатсников
            if (strcmp((info + i)->country, country) == 0) {                //Если страна i-го участника совпадает с введенной
                if (!isAtLeastOneMember) {              //Если хотя бы один участник найден
                    printf("\n-------------------------------------------------------------------------------------------------------------------------------------------\n");
                    printf("|НОМЕР|ИМЯ             ФАМИЛИЯ         ОТЧЕСТВО       |    СТРАНА     |ДАТА  РОЖДЕНИЯ|ВОЗРАСТ|  РАЗРЯД  | МОДЕЛЬ КОНЬКОВ |ОЧКИ|ВРЕМЯ КРУГА|\n");
                    printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");
                }
                printf("|%-3i  |%-15s %-15s %-15s|%-15s|  %02i/%02i/%-4i  |  %-3i  |%-10s|%-16s|%-4i|   %02i:%02i   |\n",
                       (info + i)->number, (info + i)->fullname.firstname, (info + i)->fullname.surname,
                       (info + i)->fullname.lastname, (info + i)->country, (info + i)->dateOfBirth.day,
                       (info + i)->dateOfBirth.month, (info + i)->dateOfBirth.year, (info + i)->dateOfBirth.age,
                       (info + i)->category, (info + i)->model, (info + i)->points, (info + i)->timeOfLap.minutes,
                       (info + i)->timeOfLap.seconds);
                isAtLeastOneMember = true;
            }
            if (isAtLeastOneMember && i == infoLinesCounter - 1)                //Если хотя бы один участник найден и массив полностью перебран
                printf("-------------------------------------------------------------------------------------------------------------------------------------------\n\n");
        }
        if (!isAtLeastOneMember)                //Если хотя бы один участник найден
            printf("Нет ни одного участника из страны %s.\n\n", country);
    }
}

void categorySearch() {
    bool isAtLeastOneMember = false;
    char *category = NULL;
    if (!info)              //Если указатель на массив структур равен NULL
        printf("[Ошибка!]Поиск и фильтрация: Файл не открыт!\n\n");
    else if (infoLinesCounter == 0)             //Если нет ни одного участника
        printf("[Ошибка!]Поиск и фильтрация: Файл пуст!\n\n");
    else {
        category = categoryInput(10, "Введите разряд: ");               //Ввод разряда
        system("cls");              //Очистка экрана
        printf("Участники, с разрядом %s: ", category);
        for (int i = 0; i < infoLinesCounter; i++) {                //Поиск участников
            if (strcmp((info + i)->category, category) == 0) {              //Если разряд i-го участника совпадает с введенным
                if (!isAtLeastOneMember) {              //Если хотя бы один участник найден
                    printf("\n-------------------------------------------------------------------------------------------------------------------------------------------\n");
                    printf("|НОМЕР|ИМЯ             ФАМИЛИЯ         ОТЧЕСТВО       |    СТРАНА     |ДАТА  РОЖДЕНИЯ|ВОЗРАСТ|  РАЗРЯД  | МОДЕЛЬ КОНЬКОВ |ОЧКИ|ВРЕМЯ КРУГА|\n");
                    printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");
                }
                printf("|%-3i  |%-15s %-15s %-15s|%-15s|  %02i/%02i/%-4i  |  %-3i  |%-10s|%-16s|%-4i|   %02i:%02i   |\n",
                       (info + i)->number, (info + i)->fullname.firstname, (info + i)->fullname.surname,
                       (info + i)->fullname.lastname, (info + i)->country, (info + i)->dateOfBirth.day,
                       (info + i)->dateOfBirth.month, (info + i)->dateOfBirth.year, (info + i)->dateOfBirth.age,
                       (info + i)->category, (info + i)->model, (info + i)->points, (info + i)->timeOfLap.minutes,
                       (info + i)->timeOfLap.seconds);
                isAtLeastOneMember = true;
            }
            if (isAtLeastOneMember && i == infoLinesCounter - 1)                //Если хотя бы один участник найден и массив полностю перебран
                printf("-------------------------------------------------------------------------------------------------------------------------------------------\n\n");
        }
        if (!isAtLeastOneMember)                //Если не найден ни один участник
            printf("Нет ни одного участника с разрядом %s.\n\n", category);
    }
}

void displayTopMembers() {
    INFORMATION *infoCopy = NULL, tmp;
    system("cls");
    if (!info)              //Если указатель на массив структур равен NULL
        printf("[Ошибка!]Вывод топ-3 участников: Файл не открыт!\n\n");
    else if (infoLinesCounter == 0)             //Если нет ни одного участника
        printf("[Ошибка!]Вывод топ-3 участников: Файл пуст!\n\n");
    else {
        infoCopy = (INFORMATION*)realloc(NULL, sizeof(INFORMATION)*infoLinesCounter);               //Выделение памяти для копии массива
        memcpy(infoCopy, info, sizeof(INFORMATION)*infoLinesCounter);               //Копирование информации в копию массива
        if (infoLinesCounter != 1) {                //Если участников больше одного, то отсортировать копию массива
            for (int i = 1; i < infoLinesCounter; i++)
                for (int j = i; j > 0; j--)
                    if ((infoCopy + (j - 1))->timeOfLap.minutes == (infoCopy + j)->timeOfLap.minutes) {
                        if ((infoCopy + (j - 1))->timeOfLap.seconds > (infoCopy + j)->timeOfLap.seconds) {
                            tmp = *(infoCopy + (j - 1));
                            *(infoCopy + (j - 1)) = *(infoCopy + j);
                            *(infoCopy + j) = tmp;
                        }
                    }
                    else if ((infoCopy + (j - 1))->timeOfLap.minutes > (infoCopy + j)->timeOfLap.minutes) {
                        tmp = *(infoCopy + (j - 1));
                        *(infoCopy + (j - 1)) = *(infoCopy + j);
                        *(infoCopy + j) = tmp;
                    }
        }
        printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("|НОМЕР|ИМЯ             ФАМИЛИЯ         ОТЧЕСТВО       |    СТРАНА     |ДАТА  РОЖДЕНИЯ|ВОЗРАСТ|  РАЗРЯД  | МОДЕЛЬ КОНЬКОВ |ОЧКИ|ВРЕМЯ КРУГА|\n");
        printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");
        for (int i = 0; i < infoLinesCounter && i < 3; i++) {               //Вывод первых трех участников
            printf("|%-3i  |%-15s %-15s %-15s|%-15s|  %02i/%02i/%-4i  |  %-3i  |%-10s|%-16s|%-4i|   %02i:%02i   |\n",
                   (infoCopy + i)->number, (infoCopy + i)->fullname.firstname, (infoCopy + i)->fullname.surname,
                   (infoCopy + i)->fullname.lastname, (infoCopy + i)->country, (infoCopy + i)->dateOfBirth.day,
                   (infoCopy + i)->dateOfBirth.month, (infoCopy + i)->dateOfBirth.year, (infoCopy + i)->dateOfBirth.age,
                   (infoCopy + i)->category, (infoCopy + i)->model, (infoCopy + i)->points, (infoCopy + i)->timeOfLap.minutes,
                   (infoCopy + i)->timeOfLap.seconds);
        }
        printf("-------------------------------------------------------------------------------------------------------------------------------------------\n\n");
    }
}