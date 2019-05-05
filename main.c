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


typedef struct {
    char login[30];
    char password[30];
    int isAdmin;
}USER;
typedef struct {
    char firstname[50];
    char surname[50];
    char lastname[50];
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
    char country[30];
    DATEOFBIRTH dateOfBirth;
    char category[30];
    char model[30];
    int points;
    LAP timeOfLap;
}INFORMATION;


int usersLinesCounter = 0;
int infoLinesCounter = 0;
USER *user = NULL;
INFORMATION *info = NULL;


//Ввод
char* stringInputCheck(int limit, const char* message);//функция ввода только букв
char* bufferedInput(int limit, const char* inputText);//функция ввода ограниченного кол-ва символов
int checkToEnterOnlyInt(int limit, const char *inputText);//функция ввода только целых
char* maskedPasswordInput(int limit, const char* message);
char* loginInput(int limit, const char* message);
char* categoryInput(int limit, const char* message);

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
int displayAllUsersMenu(bool showPass);

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
    setlocale(LC_ALL, "Rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    system("color 0B");
    system("mode con cols=128 lines=32");
    indicateCursor(false);
    printf("--------------------------------------------------------------------------------------------------------------------------------\n"
           "                            Программа учёта информации об участниках соревнования по бегу на коньках                            \n"
           "--------------------------------------------------------------------------------------------------------------------------------\n"
           "                                                                                                                  © by Minilooth");
    Sleep(3500);
    indicateCursor(true);
    usersInit();
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
        buffer = bufferedInput(limit, message);
        while (buffer[i] != '\0') {
            checkLetter = isdigit((unsigned char)buffer[i]);
            checkSymbol = isalnum((unsigned char)buffer[i]);
            if (checkLetter != 0 || !checkSymbol) {
                isLetter = false;
                break;
            }
            else isLetter = true;
            i++;
        }
        if (isLetter)
            return buffer;
        else {
            printf("[Ошибка!]Это поле не может содержать символ \"%c\"!", buffer[i]);
            Sleep(1000);
            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
        }
    }
}

char* bufferedInput(int limit, const char* inputText) {
    char ch, *buffer = NULL;
    int i = 0;
    buffer = (char*)realloc(NULL, sizeof(char)*(limit + 1));
    printf("%s", inputText);
    while (true) {
        ch = (char)_getch();
        if (ch != '\0') {
            if (ch == KEY_RETURN || ch == KEY_TAB) {
                if (i > 0) {
                    buffer[i] = '\0';
                    putchar('\n');
                    break;
                }
                else {
                    printf("\n[Ошибка!]Введите хотя бы один символ!");
                    Sleep(1000);
                    printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
                    printf("%s", inputText);
                }
            }
            else if (ch == KEY_BKSP && i > 0) {
                i--;
                printf("\b \b");
            }
            else if (ch == KEY_BKSP && !i)
                continue;
            else {
                if (i < limit) {
                    buffer[i++] = ch;
                    putchar(ch);
                }
            }
        }
    }
    return buffer;
}

int checkToEnterOnlyInt(int limit, const char *inputText) {
    char *buffer = NULL;
    int numberEntered = 0, i = 0, check = 0;
    bool isNumeral = false, flag = false;
    while (true) {
        i = 0;
        buffer = bufferedInput(limit, inputText);
        while (buffer[i] != '\0') {
            if (buffer[i] == '-' && !flag) {
                i++;
                flag = true;
            }
            check = isdigit((unsigned char)buffer[i]);
            if (!check) {
                isNumeral = false;
                break;
            }
            else isNumeral = true;
            i++;
        }
        if (isNumeral) {
            numberEntered = strtol(buffer, NULL, 10);
            free(buffer);
            return numberEntered;
        }
        else {
            printf("[Ошибка!]Не правильный ввод!");
            Sleep(1000);
            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
        }
    }
}

char* maskedPasswordInput(int limit, const char* message){
    char ch, *password = NULL;
    int i = 0;
    bool isSpaceEntered = false;
    password = (char*)realloc(NULL, sizeof(char)*(limit + 1));
    while(true) {
        i = 0;
        printf("%s", message);
        while (true) {
            ch = (char) _getch();
            if (ch != '\0') {
                if (ch == KEY_RETURN || ch == KEY_TAB) {
                    password[i] = '\0';
                    putchar('\n');
                    break;
                } else if (ch == KEY_BKSP && i > 0) {
                    i--;
                    printf("\b \b");
                } else if (ch == KEY_BKSP && i == 0) {
                    continue;
                } else if (i < limit) {
                    password[i++] = ch;
                    putchar('*');
                }
            }
        }
        if (i > 0) {
            for (int j = 0; password[j]; j++) {
                if (password[j] == ' ') {
                    isSpaceEntered = true;
                    break;
                } else isSpaceEntered = false;
            }
            if (isSpaceEntered) {
                printf("[Ошибка!]Пароль не может содержать символ \" \"!");
                Sleep(1000);
                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
            } else return password;
        } else {
            printf("[Ошибка!]Введите хотя бы один символ!");
            Sleep(1000);
            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
        }
    }
}

char* loginInput(int limit, const char* message){
    char *buffer = NULL;
    int i = 0, checkSymbol = 0;
    bool isLetter = false;
    while (true) {
        i = 0;
        buffer = bufferedInput(limit, message);
        while (buffer[i] != '\0') {
            checkSymbol = isalnum((unsigned char)buffer[i]);
            if (!checkSymbol) {
                isLetter = false;
                break;
            }
            else isLetter = true;
            i++;
        }
        if (isLetter)
            return buffer;
        else {
            printf("[Ошибка!]Логин не может содержать символ \"%c\"!", buffer[i]);
            Sleep(1000);
            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
        }
    }
}

char* categoryInput(int limit, const char* message){
    char *buffer = NULL;
    int i = 0, checkSymbol = 0;
    bool isLetter = false;
    while (true) {
        i = 0;
        buffer = bufferedInput(limit, message);
        while (buffer[i] != '\0') {
            if(buffer[i] != ' ' && buffer[i] != '.') {
                checkSymbol = isalnum((unsigned char) buffer[i]);
                if (!checkSymbol) {
                    isLetter = false;
                    break;
                } else isLetter = true;
            }
            i++;
        }
        if (isLetter)
            return buffer;
        else {
            printf("[Ошибка!]Разряд не может содержать символ \"%c\"!", buffer[i]);
            Sleep(1000);
            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
        }
    }
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
    indicateCursor(false);
    while (true) {
        if (ch == KEY_RETURN || ch == KEY_UP || ch == KEY_DOWN || !isShowed) {
            isShowed = true;
            system("cls");
            if (ch == KEY_RETURN) {
                indicateCursor(true);
                return choice;
            }
            if (ch == KEY_UP) choice--;
            else if (ch == KEY_DOWN) choice++;
            if (choice > 3) choice = 1;
            else if (choice < 1) choice = 3;
            printf("Меню:\n");
            for (int i = 0; line[i]; i++) {
                if (choice == i + 1) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                    printf("%c", pointer);
                }
                printf(i + 1 == choice ? "%s\n" : " %s\n", line[i]);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
            }
        }
        ch = _getch();
    }
}

int adminSubmenu() {
    int choice = 1, ch = (int)NULL;
    bool isShowed = false;
    const char pointer = '>', *line[] = { "Создание/открытие файла.", "Добавление записи.", "Редактирование записи.",
                                          "Удаление записи.", "Просмотр всех данных в табличной форме.",
                                          "Различные процедуры поиска и фильтрации данных.", "Управление пользователями.",
                                          "Выход в меню.", NULL };
    indicateCursor(false);
    while (true) {
        if (ch == KEY_RETURN || ch == KEY_UP || ch == KEY_DOWN || !isShowed) {
            isShowed = true;
            system("cls");
            if (ch == KEY_RETURN) {
                indicateCursor(true);
                return choice;
            }
            if (ch == KEY_UP) choice--;
            if (ch == KEY_DOWN) choice++;
            if (choice > 8) choice = 1;
            if (choice < 1) choice = 8;
            printf("Подменю(для администраторов):\n");
            for (int i = 0; line[i]; i++) {
                if (choice == i + 1) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                    printf("%c", pointer);
                }
                printf(i + 1 == choice ? "%s\n" : " %s\n", line[i]);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
            }
        }
        ch = _getch();
    }
}

int userSubmenu() {
    int choice = 1, ch = (int)NULL;
    bool isShowed = false;
    const char pointer = '>', *line[] = { "Открытие файла с данными.", "Просмотр всех данных в табличной форме.",
                                          "Просмотр топ-3 самых быстрых участников.", "Различные процедуры поиска и фильтрации данных.",
                                          "Выход в меню.", NULL };
    indicateCursor(false);
    while (true) {
        if (ch == KEY_RETURN || ch == KEY_UP || ch == KEY_DOWN || !isShowed) {
            isShowed = true;
            system("cls");
            if (ch == KEY_RETURN) {
                indicateCursor(true);
                return choice;
            }
            if (ch == KEY_UP) choice--;
            if (ch == KEY_DOWN) choice++;
            if (choice > 5) choice = 1;
            if (choice < 1) choice = 5;
            printf("Подменю(для пользователей):\n");
            for (int i = 0; line[i]; i++) {
                if (choice == i + 1) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                    printf("%c", pointer);
                }
                printf(i + 1 == choice ? "%s\n" : " %s\n", line[i]);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
            }
        }
        ch = _getch();
    }
}

int userEditMenu(int i, bool showPass) {
    int choice = 1, ch = (int)NULL;
    bool isShowed = false;
    const char pointer = '>', *line[] = { "Изменить логин.", "Изменить пароль.", "Изменить права администратора.", "Показать/скрыть пароль.",
                                          "Выход из меню редактирования аккунтов.", NULL };
    indicateCursor(false);
    while (true) {
        if (ch == KEY_RETURN || ch == KEY_UP || ch == KEY_DOWN || !isShowed) {
            isShowed = true;
            displayEditableUser(i, showPass);
            if (ch == KEY_RETURN) {
                indicateCursor(true);
                return choice;
            }
            if (ch == KEY_UP) choice--;
            if (ch == KEY_DOWN) choice++;
            if (choice > 5) choice = 1;
            if (choice < 1) choice = 5;
            printf("Меню редактирования аккаунтов:\n");
            for (int j = 0; line[j]; j++) {
                if (choice == j + 1) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                    printf("%c", pointer);
                }
                printf(j + 1 == choice ? "%s\n" : " %s\n", line[j]);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
            }
        }
        ch = _getch();
    }
}

int memberEditMenu(int i) {
    int choice = 1, ch = (int)NULL;
    bool isShowed = false;
    const char pointer = '>', *line[] = { "Изменение номера участника.", "Изменение имени участника.",
                                          "Изменение фамилии участника.", "Изменение отчества участника.",
                                          "Изменение страны участника.", "Изменение дня рождения участника.",
                                          "Изменение месяца рождения участника.", "Изменение года рождения участника.",
                                          "Изменение разряда участника.", "Изменение модели коньков участника.",
                                          "Изменение количества очков участника.", "Изменение минут круга участника.",
                                          "Изменение секунд круга участника.", "Выход из меню редактирования участника.", NULL };
    indicateCursor(false);
    displayEditableMember(i);
    while (true) {
        if (ch == KEY_RETURN || ch == KEY_UP || ch == KEY_DOWN || !isShowed) {
            if (ch == KEY_RETURN) {
                indicateCursor(true);
                displayEditableMember(i);
                return choice;
            }
            if (ch == KEY_UP) choice--;
            if (ch == KEY_DOWN) choice++;
            if (choice > 14) choice = 1;
            if (choice < 1) choice = 14;
            if(isShowed == true)
                for (int j = 0; j < 15; j++)
                    printf("%c[2K\r%c[A", 27, 27);
            isShowed = true;
            printf("Меню редактирования участника:\n");
            for (int j = 0; line[j]; j++) {
                if (choice == j + 1) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                    printf("%c", pointer);
                }
                printf(j + 1 == choice ? "%s\n" : " %s\n", line[j]);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
            }
        }
        ch = _getch();
    }
}

void searchingAndFiltering() {
    while (1) {
        system("cls");
        switch (searchAndFilteringMenu()) {
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
    indicateCursor(false);
    while (true) {
        if (ch == KEY_RETURN || ch == KEY_UP || ch == KEY_DOWN || !isShowed) {
            isShowed = true;
            system("cls");
            if (ch == KEY_RETURN) {
                indicateCursor(true);
                return choice;
            }
            if (ch == KEY_UP) choice--;
            if (ch == KEY_DOWN) choice++;
            if (choice > 10) choice = 1;
            if (choice < 1) choice = 10;
            printf("Меню поиска и фильтрации:\n");
            for (int i = 0; line[i]; i++) {
                if (choice == i + 1) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                    printf("%c", pointer);
                }
                printf(i + 1 == choice ? "%s\n" : " %s\n", line[i]);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
            }
        }
        ch = _getch();
    }
}

void userManagement() {
    bool showPass = false, displayAllUsersFlag = true;
    while (true) {
        system("cls");
        switch (userManagementMenu()) {
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
    indicateCursor(false);
    while (true) {
        if (ch == KEY_RETURN || ch == KEY_UP || ch == KEY_DOWN || !isShowed) {
            isShowed = true;
            system("cls");
            if (ch == KEY_RETURN) {
                indicateCursor(true);
                return choice;
            }
            if (ch == KEY_UP) choice--;
            if (ch == KEY_DOWN) choice++;
            if (choice > 5) choice = 1;
            if (choice < 1) choice = 5;
            printf("Меню управления пользователями/администраторами:\n");
            for (int i = 0; line[i]; i++) {
                if (choice == i + 1) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                    printf("%c", pointer);
                }
                printf(i + 1 == choice ? "%s\n" : " %s\n", line[i]);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
            }
        }
        ch = _getch();
    }
}

int userLoginOrRegMenu(){
    int choice = 1, ch = (int)NULL;
    bool isShowed = false;
    const char pointer = '>', *line[] = { "Войти.", "Зарегистрироваться.", "Вернутся в меню." , NULL };
    indicateCursor(false);
    while (true) {
        if (ch == KEY_RETURN || ch == KEY_UP || ch == KEY_DOWN || !isShowed) {
            isShowed = true;
            system("cls");
            if (ch == KEY_RETURN) {
                indicateCursor(true);
                return choice;
            }
            if (ch == KEY_UP) choice--;
            if (ch == KEY_DOWN) choice++;
            if (choice > 3) choice = 1;
            if (choice < 1) choice = 3;
            printf("Вход под пользователем:\n");
            for (int i = 0; line[i]; i++) {
                if (choice == i + 1) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                    printf("%c", pointer);
                }
                printf(i + 1 == choice ? "%s\n" : " %s\n", line[i]);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
            }
        }
        ch = _getch();
    }
}

int displayAllUsersMenu(bool showPass){
    int choice = 1, ch = (int)NULL;
    bool isShowed = false;
    const char pointer = '>', *line[] = { "Показать/скрыть пароли.", "Вернутся в меню." , NULL };
    indicateCursor(false);
    while (true) {
        if (ch == KEY_RETURN || ch == KEY_UP || ch == KEY_DOWN || !isShowed) {
            isShowed = true;
            system("cls");
            if (ch == KEY_RETURN) {
                indicateCursor(true);
                return choice;
            }
            if (ch == KEY_UP) choice--;
            if (ch == KEY_DOWN) choice++;
            if (choice > 2) choice = 1;
            if (choice < 1) choice = 2;
            displayAllUsers(showPass);
            printf("Меню просмотра всех пользователей:\n");
            for (int i = 0; line[i]; i++) {
                if (choice == i + 1) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                    printf("%c", pointer);
                }
                printf(i + 1 == choice ? "%s\n" : " %s\n", line[i]);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
            }
        }
        ch = _getch();
    }
}


//Всё что связано с файлами
bool checkFile(const char* filename) {
    FILE* file = NULL;
    if (!(file = fopen(filename, "rt+")))
        return false;
    else {
        fclose(file);
        return true;
    }
}

bool createFile(const char* filename) {
    FILE* file = NULL;
    if ((file = fopen(filename, "wt"))) {
        fclose(file);
        return true;
    }
    else return false;
}

void crypterTool(int status) {
    int ch, key = 0;
    if (status == ENCRYPT) key = 2;
    else if (status == DECRYPT) key = -2;
    FILE *input = NULL, *output = NULL;
    if (!(input = fopen("db.dat", "rb"))) {
        printf("[Ошибка!]Шифрование: Не удалось открыть файл с логинами/паролями!\n\n");
        system("pause");
        exit(0);
    }
    if (!(output = fopen("tempdb.dat", "wb"))) {
        printf("[Ошибка!]Шифрование: Не удалось создать временный файл с логинами/паролями!\n\n");
        system("pause");
        exit(0);
    }
    while (1) {
        fread(&ch, sizeof(char), 1, input);
        if (feof(input)) break;
        else {
            if (ch != '\n')
                ch += key;
            fwrite(&ch, sizeof(char), 1, output);
        }
    }
    fclose(input);
    fclose(output);
    if (!(input = fopen("db.dat", "wb"))) {
        printf("[Ошибка!]Шифрование: Не удалось перезаписать файл с логинами/паролями!\n\n");
        system("pause");
        exit(0);
    }
    if (!(output = fopen("tempdb.dat", "rb"))) {
        printf("[Ошибка!]Шифрование: Не удалось открыть временный файл с логинами/паролями!\n\n");
        system("pause");
        exit(0);
    }
    while (1) {
        fread(&ch, sizeof(char), 1, output);
        if (feof(output)) break;
        else fwrite(&ch, sizeof(char), 1, input);
    }

    fclose(output);
    if (remove("tempdb.dat")) {
        printf("\n[Ошибка!]Шифрование: Не удалось удалить временный файл с логинами/паролями!\n\n");
        system("pause");
        exit(0);
    }
    fclose(input);
}


//Всё что связано с пользователями
bool adminLogin() {
    system("cls");
    int i = 0, j = 0, attemptCounter = 0;
    bool isLoginRight = false, isPasswordRight = false;
    char *login = NULL, password[30], ch;
    do {
        login = bufferedInput(29, "Введите логин: ");
        for (i = 0; i < usersLinesCounter; i++)
            if (!strcmp(login, (user + i)->login) && (user + i)->isAdmin == true) {
                isLoginRight = true;
                break;
            }
        if (!isLoginRight) {
            printf("[Ошибка!]Такого администратора не существует!\n\n");
            system("pause");
            return false;
        }
    } while (!isLoginRight);
    do {
        j = 0;
        printf("Введите пароль: ");
        while (true) {
            ch = (char) _getch();
            if (ch != '\0') {
                if (ch == KEY_RETURN || ch == KEY_TAB) {
                    password[j] = '\0';
                    break;
                } else if (ch == KEY_BKSP && j > 0) {
                    j--;
                    printf("\b \b");
                } else if (ch == KEY_BKSP && j == 0) {
                    continue;
                } else {
                    if (j < 29 && attemptCounter < 5) {
                        password[j++] = ch;
                        putchar('*');
                    } else if (j < 29) {
                        password[j++] = ch;
                        putchar(ch);
                    }
                }
            }
        }
        if (!strcmp(password, (user + i)->password))
            isPasswordRight = true;
        else {
            if(attemptCounter < 10){
                printf("\n[Ошибка!]Неверный пароль!");
                Sleep(1000);
                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
                attemptCounter++;
            } else {
                printf("\n[Ошибка!]Неверный пароль!\n");
                printf("\nВы превысили максималальное число попыток ввода!\n\n");
                Sleep(1000);
                system("pause");
                return false;
            }
        }
    } while (!isPasswordRight);
    printf("\n\nВы успешно авторизовались!");
    Sleep(1000);
    printf("%c[2K\rДобро пожаловать, %s!\n\n", 27, (user + i)->login);
    free(login);
    system("pause");
    return true;
}

bool userLogin() {
    system("cls");
    int i = 0, j = 0, attemptCounter = 0;
    bool isLoginRight = false, isPasswordRight = false;
    char *login = NULL, password[30], ch;
    do {
        login = bufferedInput(29, "Введите логин: ");
        for (i = 0; i < usersLinesCounter; i++)
            if (!strcmp(login, (user + i)->login) && (user + i)->isAdmin == false) {
                isLoginRight = true;
                break;
            }
        if (!isLoginRight) {
            printf("[Ошибка!]Такого пользователя не существует!\n\n");
            system("pause");
            free(login);
            return false;
        }
    } while (!isLoginRight);
    do {
        j = 0;
        printf("Введите пароль: ");
        while (true) {
            ch = (char) _getch();
            if (ch != '\0') {
                if (ch == KEY_RETURN || ch == KEY_TAB) {
                    password[j] = '\0';
                    break;
                } else if (ch == KEY_BKSP && j > 0) {
                    j--;
                    printf("\b \b");
                } else if (ch == KEY_BKSP && j == 0) {
                    continue;
                } else {
                    if (j < 29 && attemptCounter < 5) {
                        password[j++] = ch;
                        putchar('*');
                    } else if (j < 29) {
                        password[j++] = ch;
                        putchar(ch);
                    }
                }
            }
        }
        if (!strcmp(password, (user + i)->password))
            isPasswordRight = true;
        else {
            if(attemptCounter < 10){
                printf("\n[Ошибка!]Неверный пароль!");
                Sleep(1000);
                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
                attemptCounter++;
            } else {
                printf("\n[Ошибка!]Неверный пароль!\n");
                printf("\nВы превысили максималальное число попыток ввода!\n\n");
                Sleep(1000);
                system("pause");
                return false;
            }
        }
    } while (!isPasswordRight);
    printf("\n\nВы успешно авторизовались!");
    Sleep(1000);
    printf("%c[2K\rДобро пожаловать, %s!\n\n", 27, (user + i)->login);
    free(login);
    system("pause");
    return true;
}

void firstStartAdminReg() {
    FILE *file = NULL;
    char *login = NULL, *password = NULL;
    USER newUser;
    system("cls");
    printf("--------------------------------------------------------------------------------------------------------------------------------\n"
           "            Вы зашли в программу в первый раз. Для корректной работы программы нужно зарегистрировать администратора!           \n"
           "--------------------------------------------------------------------------------------------------------------------------------\n");
    printf("Регистрация администратора.\n\n");
    login = loginInput(29, "Введите логин: ");
    strcpy(newUser.login,login);
    password = maskedPasswordInput(29, "Введите пароль: ");
    strcpy(newUser.password, password);
    newUser.isAdmin = 1;
    if ((file = fopen("db.dat", "ab+"))) {
        fwrite(&newUser, sizeof(USER), 1, file);
        fclose(file);
        crypterTool(ENCRYPT);
        printf("\nНовый администратор успешно зарегестрирован!\n\n");
        system("pause");
    }
    else {
        printf("\n[Ошибка!]Регистрация: Не удалось открыть файл для добавления нового администратора!\n");
        exit(0);
    }
    system("cls");
}

void usersInit() {
    FILE* file = NULL;
    long fsize = 0;
    if (checkFile("db.dat")) {               //Если файл существует
        if ((file = fopen("db.dat", "rb"))){                //Если файл удалось открыть для чтения


            fseek(file, 0, SEEK_END);               //Подсчёт кол-ва байт в файле
            fsize = ftell(file);
            usersLinesCounter = fsize/sizeof(USER);
            rewind(file);


            if (usersLinesCounter != 0) {               //Если есть хотябы одна строка
                crypterTool(DECRYPT);               //Расшифровать файл
                user = (USER *)malloc(usersLinesCounter * (sizeof(USER)));
                for (int i = 0; i < usersLinesCounter; i++)
                    fread((user + i), sizeof(USER), 1, file);
                fclose(file);
                crypterTool(ENCRYPT); //Зашифровать файл
            } else {
                //Если нет ни одной строки
                firstStartAdminReg();
                usersInit();
            }
        } else {
            //Если файл не удалось открыть
            printf("[Ошибка!]Инициальзация пользователей: Не удалось открыть файл с логинами/паролями!\n");
            system("pause");
            exit(0);
        }
    } else if (createFile("db.dat")) {
        //Если файл не существует - создать
        firstStartAdminReg();
        usersInit();
    } else {
        //Если файл не существует и его не удалось создать
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
    user = (USER*)realloc(user, (usersLinesCounter + 1) * sizeof(USER));
    printf("Добавить пользователя:\n");
    do {
        login = loginInput(29, "Введите логин: ");
        for (int i = 0; i < usersLinesCounter; i++) {
            if (strcmp((user + i)->login, login) == 0) {
                isLoginExist = true;
                break;
            }
            else isLoginExist = false;
        }
        if (isLoginExist) {
            printf("[Ошибка!]Такой аккаунт уже существует!");
            Sleep(1000);
            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
        }
        else strcpy((user + usersLinesCounter)->login, login);
    } while (isLoginExist);
    free(login);
    password = maskedPasswordInput(29, "Введите пароль: ");
    strcpy((user + usersLinesCounter)->password, password);
    free(password);
    indicateCursor(false);
    while (true) {
        if (ch == KEY_LEFT || ch == KEY_RIGHT || ch == KEY_RETURN || !isShowed) {
            isShowed = true;
            if (ch == KEY_RETURN) {
                printf("%c[2K\r", 27);
                printf("Администратор? ");
                for (int i = 0; line[i]; i++)
                    if (choice == i + 1)
                        printf("%s", line[i]);
                indicateCursor(true);
                break;
            }
            printf("%c[2K\r", 27);
            if (ch == KEY_LEFT) choice--;
            if (ch == KEY_RIGHT) choice++;
            if (choice > 2) choice = 2;
            if (choice < 1) choice = 1;
            printf("Администратор? ");
            for (int i = 0; line[i]; i++) {
                if (choice == i + 1) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                    printf("%c", pointer);
                }
                printf(i + 1 == choice ? "%s " : " %s ", line[i]);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
            }
        }
        ch = _getch();
    }
    if (choice == 1) (user + usersLinesCounter)->isAdmin = 1;
    else (user + usersLinesCounter)->isAdmin = 0;
    if (checkFile("db.dat")) {
        //Если файл существует
        crypterTool(DECRYPT);//Расшифровать
        if ((file = fopen("db.dat", "ab+"))) {
            //Если файл удалось открыть
            fwrite((user + usersLinesCounter), sizeof(USER), 1, file);
            fclose(file);
            printf("\nАккаунт успешно добавлен!\n\n");
            _flushall();
            usersLinesCounter++;
        }
        else printf("[Ошибка!]Добавление пользователей: Ошибка открытия файла с логинами/паролями! Пользователь не добавлен!\n\n"); //Если файл не удалось открыть
        crypterTool(ENCRYPT);//Зашифровать
    }
    else printf("[Ошибка!]Добавление пользователей: Файл не существует!\n\n"); //Если файл не существует
    system("pause");
}

void userDelete() {
    char *login = NULL;
    int i = 0, adminCounter = 0;
    bool isLoginExist = false;
    FILE* file = NULL;
    for(int j = 0; j < usersLinesCounter; j++) {
        if ((user + j)->isAdmin)
            adminCounter++;
    }
    displayAllUsers(false);
    printf("Удаление аккаунта.\n");
    do {
        login = bufferedInput(29, "Введите логин аккаунта, который вы хотите удалить: ");
        for (i = 0; i < usersLinesCounter; i++) {
            if (!strcmp((user + i)->login, login)) {
                isLoginExist = true;
                break;
            }
        }
        if (!isLoginExist) {
            printf("[Ошибка!]Такого аккаунта не существует!");
            Sleep(1000);
            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
        }
    } while (!isLoginExist);
    free(login);
    if(adminCounter == 1 && (user + i)->isAdmin) {
        system("cls");
        displayAllUsers(false);
        printf("[Ошибка!]Нельзя удалить последнего администратора!\n\n");
    }
    else {
        if (checkFile("db.dat")) {             //Если файл существует
            crypterTool(DECRYPT);               //Расшифровать
            if ((file = fopen("db.dat", "wb"))) {               //Если файл удалось пересоздать
                for (int j = i; j < usersLinesCounter; j++)
                    *(user + j) = *(user + (j + 1));
                user = (USER *) realloc(user, sizeof(USER) * usersLinesCounter);
                usersLinesCounter--;
                for (int j = 0; j < usersLinesCounter; j++)
                    fwrite((user + j), sizeof(USER), 1, file);
                fclose(file);
                system("cls");
                displayAllUsers(false);
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
    displayAllUsers(showPass);
    do {
        login = bufferedInput(29, "Введите логин аккаунта, который вы хотите отредактировать: ");
        for (i = 0; i < usersLinesCounter; i++) {
            if (!strcmp((user + i)->login, login)) {
                isLoginExist = true;
                break;
            }
            else isLoginExist = false;
        }
        if (!isLoginExist) {
            printf("[Ошибка!]Такого аккаунта не существует!");
            Sleep(1000);
            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
        }
    } while (!isLoginExist);
    free(login);
    while (!editFlag) {
        adminCounter = 0;
        for(int j = 0; j < usersLinesCounter; j++) {
            if ((user + j)->isAdmin)
                adminCounter++;
        }
        switch (userEditMenu(i, showPass)) {
            case 1: {
                printf("Изменить логин.\n");
                do {
                    newLogin = loginInput(29, "Введите новый логин: ");
                    for (int j = 0; j < usersLinesCounter; j++) {
                        if (strcmp((user + j)->login, newLogin) == 0) {
                            isNewLoginExist = true;
                            break;
                        }
                        else isNewLoginExist = false;
                    }
                    if (isNewLoginExist) {
                        printf("[Ошибка!]Такой логин уже существует!\n");
                        Sleep(1000);
                        printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
                    }
                } while (isNewLoginExist);
                strcpy((user + i)->login, newLogin);
                displayEditableUser(i, showPass);
                printf("Логин успешно изменен!\n\n");
                free(newLogin);
                system("pause");
                break;
            }
            case 2: {
                printf("Изменение пароля.\n");
                newPassword = maskedPasswordInput(29, "Введите новый пароль: ");
                strcpy((user + i)->password, newPassword);
                displayEditableUser(i, showPass);
                printf("Пароль успешно изменен!\n\n");
                free(newPassword);
                system("pause");
                break;
            }
            case 3: {
                if(adminCounter == 1 && (user + i)->isAdmin)
                    printf("[Ошибка!]Нельзя изменить права последнего администратора!\n\n");
                else {
                    if ((user + i)->isAdmin) {
                        (user + i)->isAdmin = false;
                        displayEditableUser(i, showPass);
                        printf("Права администратора успешно изменены.\n\n");
                    } else {
                        (user + i)->isAdmin = true;
                        displayEditableUser(i, showPass);
                        printf("Права администратора успешно изменены.\n\n");
                    }
                }
                system("pause");
                break;
            }
            case 4: showPass = showPass == true ? false : true; break;
            case 5: editFlag = true; break;
            default: break;
        }
        if (editFlag) break;
    }
    if (checkFile("db.dat")) {
        //Если файл существует
        crypterTool(DECRYPT);//Расшифровать
        if ((file = fopen("db.dat", "wb"))) {
            //Если файл удалось пересоздать
            for (i = 0; i < usersLinesCounter; i++)
                fwrite((user + i), sizeof(USER), 1, file);
            fclose(file);
        }
        else printf("[Ошибка!]Редактирование пользователей: Не удалось открыть файл с логинами/паролями! Файл отчищен!\n\n");//Если файл не удалось пересоздать
        crypterTool(ENCRYPT);//Зашифровать
    }
    else printf("[Ошибка!]Редактирование пользователей: Не удалось открыть файл с логинами/паролями!\n\n");//Если файл не существует
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
    user = (USER*)realloc(user, (usersLinesCounter + 1) * sizeof(USER));
    printf("Регистрация пользователя:\n");
    do {
        login = loginInput(29, "Введите логин: ");
        for (int i = 0; i < usersLinesCounter; i++) {
            if (strcmp((user + i)->login, login) == 0) {
                isLoginExist = true;
                break;
            }
            else isLoginExist = false;
        }
        if (isLoginExist) {
            printf("[Ошибка!]Такой аккаунт уже существует!");
            Sleep(1000);
            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
        }
        else strcpy((user + usersLinesCounter)->login, login);
    } while (isLoginExist);
    free(login);
    password = maskedPasswordInput(29, "Введите пароль: ");
    strcpy((user + usersLinesCounter)->password, password);
    free(password);
    (user + usersLinesCounter)->isAdmin = 0;
    if (checkFile("db.dat")) {
        //Если файл существует
        crypterTool(DECRYPT);//Расшифровать
        if ((file = fopen("db.dat", "ab+"))) {
            //Если файл удалось открыть
            fwrite((user + usersLinesCounter), sizeof(USER), 1, file);
            fclose(file);
            printf("\nВы успешно зарегистрировались!\n\n");
            _flushall();
            usersLinesCounter++;
        }
        else printf("[Ошибка!]Добавление пользователей: Ошибка открытия файла с логинами/паролями! Пользователь не добавлен!\n\n"); //Если файл не удалось открыть
        crypterTool(ENCRYPT);//Зашифровать
    }
    else printf("[Ошибка!]Добавление пользователей: Файл не существует!\n\n"); //Если файл не существует
    system("pause");
}


//Всё что связано с информацией
void membersOpenAdmin() {
    int choice = 1, ch = (int)NULL;
    bool isShowed = false;
    const char *line[] = { "Да", "Нет", NULL }, pointer = '>';
    if (!checkFile("info.dat")) {
        printf("[Ошибка!]Открытие информации: Файл ещё не создан!\n");
        indicateCursor(false);
        while (true) {
            if (ch == KEY_RETURN || ch == KEY_LEFT || ch == KEY_RIGHT || !isShowed) {
                isShowed = true;
                printf("%c[2K\r", 27);
                if (ch == KEY_RETURN) {
                    indicateCursor(true);
                    break;
                }
                if (ch == KEY_LEFT) choice--;
                if (ch == KEY_RIGHT) choice++;
                if (choice > 2) choice = 2;
                if (choice < 1) choice = 1;
                printf("Создать файл? ");
                for (int i = 0; line[i]; i++) {
                    if (choice == i + 1) {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                        printf("%c", pointer);
                    }
                    printf(i + 1 == choice ? "%s " : " %s ", line[i]);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
                }
            }
            ch = _getch();
        }
        if (choice == 1) {
            if (createFile("info.dat")) {
                printf("Открытие информации: Файл успешно создан!\n");
                membersInit();
                system("pause");
            }
            else printf("[Ошибка!]Открытие информации: Не удалось создать файл!\n");
        }
    }
    else {
        membersInit();
        system("pause");
    }
};

void membersOpenUser() {
    if (checkFile("info.dat"))
        membersInit();
    else
        printf("[Ошибка!]Открытие информации: Файл ещё не создан!\n\n");
}

void membersInit() {
    FILE *file = NULL;
    long fsize;
    if (info)
        printf("[Ошибка!]Открытие информации: Файл уже открыт!\n\n");
    else {
        if ((file = fopen("info.dat", "rb+"))) {
            fseek(file, 0, SEEK_END);     //Кол-ва байт
            fsize = ftell(file);          //В файле
            infoLinesCounter = fsize / sizeof(INFORMATION);
            rewind(file);


            if (infoLinesCounter != 0) {
                info = (INFORMATION *)malloc(infoLinesCounter * sizeof(INFORMATION));
                for (int i = 0; i < infoLinesCounter; i++)
                    fread((info + i), sizeof(INFORMATION), 1, file);
            }
            fclose(file);
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
    if (!info)
        printf("[Ошибка!]Добавление информации: Файл не открыт!\n\n");
    else if (!(file = fopen("info.dat", "ab+")))
        printf("[Ошибка!]Добавление информации: Не удалось открыть файл для добавления!\n");
    else {
        info = (INFORMATION *)realloc(info, (infoLinesCounter + 1) * sizeof(INFORMATION));
        printf("Добавление участника.\n");
        do {
            do {
                (info + infoLinesCounter)->number = checkToEnterOnlyInt(3, "Введите номер участника: ");
                if ((info + infoLinesCounter)->number < 1) {
                    printf("[Ошибка!]Введите число больше 0!");
                    Sleep(1000);
                    printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
                }
            } while ((info + infoLinesCounter)->number < 1);
            for (int i = 0; i < infoLinesCounter; i++) {
                if ((info + i)->number == (info + infoLinesCounter)->number) {
                    isMemberExist = true;
                    break;
                }
                else isMemberExist = false;
            }
            if (isMemberExist) {
                printf("[Ошибка!]Участник с таким номером уже существует!");
                Sleep(1000);
                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
            }
        } while (isMemberExist);
        firstname = stringInputCheck(49, "Введите имя участника: ");
        strcpy((info + infoLinesCounter)->fullname.firstname, firstname);
        free(firstname);
        surname = stringInputCheck(49, "Введите фамилию участника: ");
        strcpy((info + infoLinesCounter)->fullname.surname, surname);
        free(surname);
        lastname = stringInputCheck(49, "Введите отчество участника: ");
        strcpy((info + infoLinesCounter)->fullname.lastname, lastname);
        free(lastname);
        country = stringInputCheck(29, "Введите страну участника: ");
        strcpy((info + infoLinesCounter)->country, country);
        free(country);
        do {
            (info + infoLinesCounter)->dateOfBirth.day = checkToEnterOnlyInt(2, "Введите день рождения участника: ");
            if ((info + infoLinesCounter)->dateOfBirth.day < 1 || (info + infoLinesCounter)->dateOfBirth.day > 31) {
                printf("[Ошибка!]Введите число от 1 до 31!");
                Sleep(1000);
                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
            }
        } while ((info + infoLinesCounter)->dateOfBirth.day < 1 || (info + infoLinesCounter)->dateOfBirth.day > 31);
        do {
            (info + infoLinesCounter)->dateOfBirth.month = checkToEnterOnlyInt(2, "Введите месяц рождения участника(числом): ");
            if ((info + infoLinesCounter)->dateOfBirth.month < 1 || (info + infoLinesCounter)->dateOfBirth.month > 12) {
                printf("[Ошибка!]Введите число от 1 до 12!");
                Sleep(1000);
                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
            }
        } while ((info + infoLinesCounter)->dateOfBirth.month < 1 || (info + infoLinesCounter)->dateOfBirth.month > 12);
        do {
            (info + infoLinesCounter)->dateOfBirth.year = checkToEnterOnlyInt(4, "Введите год рождения участника: ");
            if ((info + infoLinesCounter)->dateOfBirth.year < 1900 || (info + infoLinesCounter)->dateOfBirth.year > 2019) {
                printf("[Ошибка!]Введите число от 1900 до 2019!");
                Sleep(1000);
                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
            }
        } while ((info + infoLinesCounter)->dateOfBirth.year < 1900 ||
                 (info + infoLinesCounter)->dateOfBirth.year > 2019);
        if ((info + infoLinesCounter)->dateOfBirth.month > aTm->tm_mon + 1)
            (info + infoLinesCounter)->dateOfBirth.age = 2018 - (info + infoLinesCounter)->dateOfBirth.year;
        else (info + infoLinesCounter)->dateOfBirth.age = 2019 - (info + infoLinesCounter)->dateOfBirth.year;
        category = categoryInput(29, "Введите разряд участника: ");
        strcpy((info + infoLinesCounter)->category, category);
        free(category);
        model = stringInputCheck(29, "Введите модель коньков участника: ");
        strcpy((info + infoLinesCounter)->model, model);
        free(model);
        do {
            (info + infoLinesCounter)->points = checkToEnterOnlyInt(4, "Введите количество очков участника: ");
            if ((info + infoLinesCounter)->points < 0 || (info + infoLinesCounter)->points > 9999) {
                printf("[Ошибка!]Введите число от 0 до 9999!");
                Sleep(1000);
                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
            }
        } while ((info + infoLinesCounter)->points < 0 || (info + infoLinesCounter)->points > 9999);
        do {
            (info + infoLinesCounter)->timeOfLap.minutes = checkToEnterOnlyInt(2, "Введите минуты круга участника: ");
            if ((info + infoLinesCounter)->timeOfLap.minutes < 0 || (info + infoLinesCounter)->timeOfLap.minutes > 59) {
                printf("[Ошибка!]Введите число от 0 до 59!");
                Sleep(1000);
                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
            }
        } while ((info + infoLinesCounter)->timeOfLap.minutes < 0 || (info + infoLinesCounter)->timeOfLap.minutes > 59);
        do {
            (info + infoLinesCounter)->timeOfLap.seconds = checkToEnterOnlyInt(2, "Введите секунды круга участника: ");
            if ((info + infoLinesCounter)->timeOfLap.seconds < 0 || (info + infoLinesCounter)->timeOfLap.seconds > 59) {
                printf("[Ошибка!]Введите число от 0 до 59!");
                Sleep(1000);
                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
            }
        } while ((info + infoLinesCounter)->timeOfLap.seconds < 0 || (info + infoLinesCounter)->timeOfLap.seconds > 59);
        fwrite((info + infoLinesCounter), sizeof(INFORMATION), 1, file);
        _flushall();
        fclose(file);
        infoLinesCounter++;
        printf("Участник успешно добавлен!\n\n");
    }
}

void memberDelete() {
    int delNumber = 0, i = 0;
    bool isNumberExist = false;
    FILE *file = NULL;
    if (info == NULL) {
        printf("[Ошибка!]Удаление информации: Файл не открыт!\n\n");
    }
    else if (infoLinesCounter == 0) {
        printf("[Ошибка!]Удаление информации: Файл пуст!\n\n");
    }
    else {
        displayAllMembers();
        printf("Удаление участника.\n");
        do {
            delNumber = checkToEnterOnlyInt(3, "Введите номер участника для удаления: ");
            for (i = 0; i < infoLinesCounter; i++) {
                if (delNumber == (info + i)->number) {
                    isNumberExist = true;
                    break;
                }
                else isNumberExist = false;
            }
            if (!isNumberExist) {
                printf("[Ошибка!]Участника с таким номером не существует!");
                Sleep(1000);
                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
            }
        } while (!isNumberExist);
        for (int j = i; j < infoLinesCounter; j++)
            *(info + j) = *(info + (j + 1));
        info = (INFORMATION*)realloc(info, sizeof(INFORMATION)*infoLinesCounter);
        infoLinesCounter--;
        if (checkFile("info.dat")) {
            if ((file = fopen("info.dat", "wb"))) {
                for (int j = 0; j < infoLinesCounter; j++)
                    fwrite((info + j), sizeof(INFORMATION), 1, file);
                fclose(file);
                printf("Участник успешно удалён!\n\n");
            }
            else printf("[Ошибка!]Удаление информации: Не удалось перезаписать файл! Файл отчищен!\n\n");
        }
        else printf("[Ошибка!]Удаление информации: Не удалось найти файл!\n\n");
    }
}

void memberEdit() {
    time_t t = time(NULL);
    FILE *file = NULL;
    struct tm *aTm = localtime(&t);
    bool isMemberExist = false, isNumberExist = false, infoEditFlag = false;
    int number = 0, i = 0, j = 0, newNumber = 0, newBirthDay = 0, newBirthMonth = 0, newBirthYear = 0;
    char *firstname = NULL, *surname = NULL, *lastname = NULL, *country = NULL, *category = NULL, *model = NULL;
    if (!info) {
        printf("[Ошибка!]Редактирование информации: Файл не открыт!\n\n");
        system("pause");
    }
    else if (infoLinesCounter == 0) {
        printf("[Ошибка!]Редактирование информации: Файл пуст!\n\n");
        system("pause");
    }
    else {
        displayAllMembers();
        do {
            number = checkToEnterOnlyInt(3, "Введите номер участника, которого нужно отредактировать: ");
            for (i = 0; i < infoLinesCounter; i++) {
                if ((info + i)->number == number) {
                    isMemberExist = true;
                    break;
                }
                else isMemberExist = false;
            }
            if (!isMemberExist) {
                printf("[Ошибка!]Участника с таким номером не существует!");
                Sleep(1000);
                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
            }
        } while (!isMemberExist);
        while (!infoEditFlag) {
            switch (memberEditMenu(i)) {
                case 1: {
                    printf("Изменеие номера участника.\n");
                    do {
                        do {
                            newNumber = checkToEnterOnlyInt(3, "Введите новый номер участника: ");
                            if (newNumber < 1) {
                                printf("[Ошибка!]Введите число больше 0!");
                                Sleep(1000);
                                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
                            }
                        } while (newNumber < 1);
                        for (j = 0; j < infoLinesCounter; j++) {
                            if ((info + j)->number == newNumber) {
                                isNumberExist = true;
                                break;
                            }
                            else isNumberExist = false;
                        }
                        if (isNumberExist) {
                            printf("[Ошибка!]Участник с таким номером уже существует!");
                            Sleep(1000);
                            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
                        }
                    } while (isNumberExist);
                    (info + i)->number = newNumber;
                    displayEditableMember(i);
                    printf("Номер участника успешно изменен!\n\n");
                    system("pause");
                    break;
                }
                case 2: {
                    printf("Изменение имени участника.\n");
                    firstname = stringInputCheck(49, "Введите новое имя участника: ");
                    strcpy((info + i)->fullname.firstname, firstname);
                    free(firstname);
                    displayEditableMember(i);
                    printf("Имя участника успешно изменено!\n\n");
                    system("pause");
                    break;
                }
                case 3: {
                    printf("Изменение фамилии участника.\n");
                    surname = stringInputCheck(49, "Введите новую фамилию участника: ");
                    strcpy((info + i)->fullname.surname, surname);
                    free(surname);
                    displayEditableMember(i);
                    printf("Фамилия участника успешна изменена!\n\n");
                    system("pause");
                    break;
                }
                case 4: {
                    printf("Изменение отчества участника.\n");
                    lastname = stringInputCheck(49, "Введите новое отчество участника: ");
                    strcpy((info + i)->fullname.lastname, lastname);
                    free(lastname);
                    displayEditableMember(i);
                    printf("Отчество участника успешно изменено!\n\n");
                    system("pause");
                    break;
                }
                case 5: {
                    printf("Изменение страны участника.\n");
                    country = stringInputCheck(29, "Введите новую страну участника: ");
                    strcpy((info + i)->country, country);
                    free(country);
                    displayEditableMember(i);
                    printf("Страна участника успешно изменена.\n\n");
                    system("pause");
                    break;
                }
                case 6: {
                    printf("Изменение дня рождения участника.\n");
                    do {
                        newBirthDay = checkToEnterOnlyInt(2, "Введите новый день рождения участника: ");
                        if (newBirthDay < 1 || newBirthDay > 31) {
                            printf("[Ошибка!]Введите число от 1 до 31!");
                            Sleep(1000);
                            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
                        }
                    } while (newBirthDay < 1 || newBirthDay > 31);
                    (info + i)->dateOfBirth.day = newBirthDay;
                    displayEditableMember(i);
                    printf("День рождения участника успешно изменен!\n\n");
                    system("pause");
                    break;
                }
                case 7: {
                    printf("Изменение месяца рождения участника.\n");
                    do {
                        newBirthMonth = checkToEnterOnlyInt(2, "Введите новый месяц рождения участника(числом): ");
                        if (newBirthMonth < 1 || newBirthMonth > 12) {
                            printf("[Ошибка!]Введите число от 1 до 12!");
                            Sleep(1000);
                            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
                        }
                    } while (newBirthMonth < 1 || newBirthMonth > 12);
                    (info + i)->dateOfBirth.month = newBirthMonth;
                    displayEditableMember(i);
                    printf("Месяц рождения участника успешно изменен!\n\n");
                    system("pause");
                    break;
                }
                case 8: {
                    printf("Изменение года рождения участника.\n");
                    do {
                        newBirthYear = checkToEnterOnlyInt(4, "Введите новый год рождения участника: ");
                        if (newBirthYear < 1900 || newBirthYear > 2019) {
                            printf("[Ошибка!]Введите число от 1900 до 2019!");
                            Sleep(1000);
                            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
                        }
                    } while (newBirthYear < 1900 || newBirthYear > 2019);
                    (info + i)->dateOfBirth.year = newBirthYear;
                    if ((info + i)->dateOfBirth.month >= aTm->tm_mon + 1)
                        (info + i)->dateOfBirth.age = 2018 - (info + i)->dateOfBirth.year;
                    else
                        (info + i)->dateOfBirth.age = 2019 - (info + i)->dateOfBirth.year;
                    displayEditableMember(i);
                    printf("Год рождения участника успешно изменен!\n\n");
                    system("pause");
                    break;
                }
                case 9: {
                    printf("Изменение разряда участника.\n");
                    category = categoryInput(29, "Введите новый разряд участника: ");
                    strcpy((info + i)->category, category);
                    free(category);
                    displayEditableMember(i);
                    printf("Разряд участника успешно изменен!\n\n");
                    system("pause");
                    break;
                }
                case 10: {
                    printf("Изменение модели коньков участника.\n");
                    model = stringInputCheck(29, "Введите новую модель коньков участника: ");
                    strcpy((info + i)->model, model);
                    free(model);
                    displayEditableMember(i);
                    printf("Модель коньков участника успешно изменена!\n\n");
                    system("pause");
                    break;
                }
                case 11: {
                    printf("Изменение количества очков участника.\n");
                    do {
                        (info + i)->points = checkToEnterOnlyInt(4, "Введите новое количество очков участника: ");
                        if ((info + i)->points < 0 || (info + i)->points > 9999) {
                            printf("[Ошибка!]Введите число от 0 до 9999!");
                            Sleep(1000);
                            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
                        }
                    } while ((info + i)->points < 0 || (info + i)->points > 9999);
                    displayEditableMember(i);
                    printf("Количество очков участника успешно изменено!\n\n");
                    system("pause");
                    break;
                }
                case 12: {
                    printf("Изменение минут круга участника.\n");
                    do {
                        (info + i)->timeOfLap.minutes = checkToEnterOnlyInt(2, "Введите новые минуты круга участника: ");
                        if ((info + i)->timeOfLap.minutes < 0 || (info + i)->timeOfLap.minutes > 59) {
                            printf("[Ошибка!]Введите число от 0 до 59!");
                            Sleep(1000);
                            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
                        }
                    } while ((info + i)->timeOfLap.minutes < 0 || (info + i)->timeOfLap.minutes > 59);
                    displayEditableMember(i);
                    printf("Минуты круга участника успешно изменены!\n\n");
                    system("pause");
                    break;
                }
                case 13: {
                    printf("Изменение секунд круга участника.\n");
                    do {
                        (info + i)->timeOfLap.seconds = checkToEnterOnlyInt(2, "Введите новые секунды круга участника: ");
                        if ((info + i)->timeOfLap.seconds < 0 || (info + i)->timeOfLap.seconds > 59) {
                            printf("[Ошибка!]Введите число от 0 до 59!");
                            Sleep(1000);
                            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
                        }
                    } while ((info + i)->timeOfLap.seconds < 0 || (info + i)->timeOfLap.seconds > 59);
                    displayEditableMember(i);
                    printf("Секунды круга участника успешно изменены!\n\n");
                    system("pause");
                    break;
                }
                case 14: infoEditFlag = true; break;
                default: break;
            }
        }
        if (checkFile("info.dat")) {
            if ((file = fopen("info.dat", "wb"))) {
                for (j = 0; j < infoLinesCounter; j++)
                    fwrite((info + j), sizeof(INFORMATION), 1, file);
            }
            else printf("[Ошибка!]Редактирование информации: Не удалось перезаписать файл! Файл отчищен!\n");
        }
        else printf("[Ошибка!]Редактирование информации: Не удалось найти файл!\n");
    }
}

void displayEditableMember(int i) {
    system("cls");
    printf("--------------------------------------------------------------------------------------------------------------------------------\n"
           "|НОМЕР|ИМЯ             ФАМИЛИЯ         ОТЧЕСТВО       |  СТРАНА  |ДАТА  РОЖДЕНИЯ|ВОЗРАСТ|  РАЗРЯД  |  МОДЕЛЬ  |ОЧКИ|ВРЕМЯ КРУГА|\n"
           "--------------------------------------------------------------------------------------------------------------------------------\n"
           "|%-3i  |%-15s %-15s %-15s|%-10s|  %02i/%02i/%04i  |  %-3i  |%-10s|%-10s|%-4i|   %02i:%02i   |\n",
           (info + i)->number, (info + i)->fullname.firstname, (info + i)->fullname.surname,
           (info + i)->fullname.lastname, (info + i)->country,
           (info + i)->dateOfBirth.day, (info + i)->dateOfBirth.month, (info + i)->dateOfBirth.year,
           (info + i)->dateOfBirth.age, (info + i)->category,
           (info + i)->model, (info + i)->points, (info + i)->timeOfLap.minutes, (info + i)->timeOfLap.seconds);
    printf("--------------------------------------------------------------------------------------------------------------------------------\n");
}

void displayAllMembers() {
    system("cls");
    if (!info)
        printf("[Ошибка!]Вывод информации: Файл еще не открыт!\n\n");
    else if (infoLinesCounter == 0)
        printf("[Ошибка!]Вывод информации: Файл пуст!\n\n");
    else {
        printf("--------------------------------------------------------------------------------------------------------------------------------\n");
        printf("|НОМЕР|ИМЯ             ФАМИЛИЯ         ОТЧЕСТВО       |  СТРАНА  |ДАТА  РОЖДЕНИЯ|ВОЗРАСТ|  РАЗРЯД  |  МОДЕЛЬ  |ОЧКИ|ВРЕМЯ КРУГА|\n");
        printf("--------------------------------------------------------------------------------------------------------------------------------\n");
        for (int i = 0; i < infoLinesCounter; i++) {
            printf("|%-3i  |%-15s %-15s %-15s|%-10s|  %02i/%02i/%04i  |  %-3i  |%-10s|%-10s|%-4i|   %02i:%02i   |\n",
                   (info + i)->number, (info + i)->fullname.firstname, (info + i)->fullname.surname, (info + i)->fullname.lastname, (info + i)->country,
                   (info + i)->dateOfBirth.day, (info + i)->dateOfBirth.month, (info + i)->dateOfBirth.year, (info + i)->dateOfBirth.age, (info + i)->category,
                   (info + i)->model, (info + i)->points, (info + i)->timeOfLap.minutes, (info + i)->timeOfLap.seconds);
        }
        printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
    };
}


//Всё что связано с фильтрацией и поиском
void pointsFilter() {
    int points = 0;
    bool isAtLeastOneMember = false;
    if (!info)
        printf("[Ошибка!]Поиск и фильтрация: Файл не открыт!\n\n");
    else if (infoLinesCounter == 0)
        printf("[Ошибка!]Поиск и фильтрация: Файл пуст!\n\n");
    else {
        do {
            points = checkToEnterOnlyInt(4, "Введите количество очков: ");
            if (points < 0 || points > 9999) {
                printf("[Ошибка!]Введите число больше 0 и меньше 9999!");
                Sleep(1000);
                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
            }
        } while (points < 0 || points > 9999);
        system("cls");
        printf("Участники, у которых очков больше %i: ", points);
        for (int i = 0; i < infoLinesCounter; i++) {
            if ((info + i)->points > points) {
                if (!isAtLeastOneMember) {
                    printf("\n--------------------------------------------------------------------------------------------------------------------------------\n");
                    printf("|НОМЕР|ИМЯ             ФАМИЛИЯ         ОТЧЕСТВО       |  СТРАНА  |ДАТА  РОЖДЕНИЯ|ВОЗРАСТ|  РАЗРЯД  |  МОДЕЛЬ  |ОЧКИ|ВРЕМЯ КРУГА|\n");
                    printf("--------------------------------------------------------------------------------------------------------------------------------\n");
                }
                printf("|%-3i  |%-15s %-15s %-15s|%-10s|  %-2i/%02i/%-4i  |  %-3i  |%-10s|%-10s|%-4i|   %02i:%02i   |\n",
                       (info + i)->number, (info + i)->fullname.firstname, (info + i)->fullname.surname,
                       (info + i)->fullname.lastname, (info + i)->country, (info + i)->dateOfBirth.day,
                       (info + i)->dateOfBirth.month, (info + i)->dateOfBirth.year, (info + i)->dateOfBirth.age,
                       (info + i)->category, (info + i)->model, (info + i)->points, (info + i)->timeOfLap.minutes,
                       (info + i)->timeOfLap.seconds);
                isAtLeastOneMember = true;
            }
            if (isAtLeastOneMember && i == infoLinesCounter - 1)
                printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
        }
        if (!isAtLeastOneMember)
            printf("[Ошибка!]Нет ни одного участника с очками больше %i.\n\n", points);
    }
}

void timeOfLapFilter() {
    int minutesOfLap = 0, secondsOfLap = 0;
    bool isAtLeastOneMember = false;
    if (!info) {
        printf("[Ошибка!]Поиск и фильтрация: Файл не открыт!\n\n");
    }
    else if (infoLinesCounter == 0) {
        printf("[Ошибка!]Поиск и фильтрация: Файл пуст!\n\n");
    }
    else {
        do {
            minutesOfLap = checkToEnterOnlyInt(2, "Введите количество минут круга: ");
            if (minutesOfLap < 0 || minutesOfLap > 59) {
                printf("[Ошибка!]Введите число больше 0 и меньше 59!\n");
                Sleep(1000);
                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
            }
        } while (minutesOfLap < 0 || minutesOfLap > 59);
        do {
            secondsOfLap = checkToEnterOnlyInt(2, "Введите количество секунд круга: ");
            if (secondsOfLap < 0 || secondsOfLap > 59) {
                printf("[Ошибка!]Введите число больше 0 и меньше 59!\n");
                Sleep(1000);
                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
            }
        } while (secondsOfLap < 0 || secondsOfLap > 59);
        system("cls");
        printf("Участники, у которых время круга меньше %02i:%02i : ", minutesOfLap, secondsOfLap);
        for (int i = 0; i < infoLinesCounter; i++) {
            if ((info + i)->timeOfLap.minutes < minutesOfLap)
                if ((info + i)->timeOfLap.seconds <
                    ((info + i)->timeOfLap.minutes == minutesOfLap ? secondsOfLap : 60)) {
                    if (!isAtLeastOneMember) {
                        printf("\n--------------------------------------------------------------------------------------------------------------------------------\n");
                        printf("|НОМЕР|ИМЯ             ФАМИЛИЯ         ОТЧЕСТВО       |  СТРАНА  |ДАТА  РОЖДЕНИЯ|ВОЗРАСТ|  РАЗРЯД  |  МОДЕЛЬ  |ОЧКИ|ВРЕМЯ КРУГА|\n");
                        printf("--------------------------------------------------------------------------------------------------------------------------------\n");
                    }
                    printf("|%-3i  |%-15s %-15s %-15s|%-10s|  %-2i/%02i/%-4i  |  %-3i  |%-10s|%-10s|%-4i|   %02i:%02i   |\n",
                           (info + i)->number, (info + i)->fullname.firstname, (info + i)->fullname.surname,
                           (info + i)->fullname.lastname, (info + i)->country, (info + i)->dateOfBirth.day,
                           (info + i)->dateOfBirth.month, (info + i)->dateOfBirth.year, (info + i)->dateOfBirth.age,
                           (info + i)->category, (info + i)->model, (info + i)->points, (info + i)->timeOfLap.minutes,
                           (info + i)->timeOfLap.seconds);
                    isAtLeastOneMember = true;
                }
            if (isAtLeastOneMember && i == infoLinesCounter - 1)
                printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
        }
        if (!isAtLeastOneMember)
            printf("[Ошибка!]Нет ни одного участника с временем круга меньше %02i:%02i.\n\n", minutesOfLap,
                   secondsOfLap);
    }
}

void ageFilter() {
    int age = 0;
    bool isAtLeastOneMember = false;
    if (!info)
        printf("[Ошибка!]Поиск и фильтрация: Файл не открыт!\n\n");
    else if (infoLinesCounter == 0)
        printf("[Ошибка!]Поиск и фильтрация: Файл пуст!\n\n");
    else {
        do {
            age = checkToEnterOnlyInt(3, "Введите возраст: ");
            if (age < 0 || age > 119) {
                printf("[Ошибка!]Введите число больше 0 и меньше 119!\n");
                Sleep(1000);
                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
            }
        } while (age < 0 || age > 119);
        system("cls");
        printf("Участники, возраст которых больше %i: ", age);
        for (int i = 0; i < infoLinesCounter; i++) {
            if ((info + i)->dateOfBirth.age > age) {
                if (!isAtLeastOneMember) {
                    printf("\n--------------------------------------------------------------------------------------------------------------------------------\n");
                    printf("|НОМЕР|ИМЯ             ФАМИЛИЯ         ОТЧЕСТВО       |  СТРАНА  |ДАТА  РОЖДЕНИЯ|ВОЗРАСТ|  РАЗРЯД  |  МОДЕЛЬ  |ОЧКИ|ВРЕМЯ КРУГА|\n");
                    printf("--------------------------------------------------------------------------------------------------------------------------------\n");
                }
                printf("|%-3i  |%-15s %-15s %-15s|%-10s|  %-2i/%02i/%-4i  |  %-3i  |%-10s|%-10s|%-4i|   %02i:%02i   |\n",
                       (info + i)->number, (info + i)->fullname.firstname, (info + i)->fullname.surname,
                       (info + i)->fullname.lastname, (info + i)->country, (info + i)->dateOfBirth.day,
                       (info + i)->dateOfBirth.month, (info + i)->dateOfBirth.year, (info + i)->dateOfBirth.age,
                       (info + i)->category, (info + i)->model, (info + i)->points, (info + i)->timeOfLap.minutes,
                       (info + i)->timeOfLap.seconds);
                isAtLeastOneMember = true;
            }
            if (isAtLeastOneMember && i == infoLinesCounter - 1)
                printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
        }
        if (!isAtLeastOneMember)
            printf("[Ошибка!]Нет ни одного участника с очками больше %i.\n\n", age);
    }
}

void yearOfBirthFilter() {
    int yearOfBirth = 0;
    bool isAtLeastOneMember = false;
    if (!info)
        printf("[Ошибка!]Поиск и фильтрация: Файл не открыт!\n\n");
    else if (infoLinesCounter == 0)
        printf("[Ошибка!]Поиск и фильтрация: Файл пуст!\n\n");
    else {
        do {
            yearOfBirth = checkToEnterOnlyInt(4, "Введите год рождения: ");
            if (yearOfBirth < 1900 || yearOfBirth > 2019) {
                printf("[Ошибка!]Введите число больше 1900 и меньше 2019!\n");
                Sleep(1000);
                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
            }
        } while (yearOfBirth < 1900 || yearOfBirth > 2019);
        system("cls");
        printf("Участники, год рождения у которых больше %i: ", yearOfBirth);
        for (int i = 0; i < infoLinesCounter; i++) {
            if ((info + i)->dateOfBirth.year > yearOfBirth) {
                if (!isAtLeastOneMember) {
                    printf("\n--------------------------------------------------------------------------------------------------------------------------------\n");
                    printf("|НОМЕР|ИМЯ             ФАМИЛИЯ         ОТЧЕСТВО       |  СТРАНА  |ДАТА  РОЖДЕНИЯ|ВОЗРАСТ|  РАЗРЯД  |  МОДЕЛЬ  |ОЧКИ|ВРЕМЯ КРУГА|\n");
                    printf("--------------------------------------------------------------------------------------------------------------------------------\n");
                }
                printf("|%-3i  |%-15s %-15s %-15s|%-10s|  %-2i/%02i/%-4i  |  %-3i  |%-10s|%-10s|%-4i|   %02i:%02i   |\n",
                       (info + i)->number, (info + i)->fullname.firstname, (info + i)->fullname.surname,
                       (info + i)->fullname.lastname, (info + i)->country, (info + i)->dateOfBirth.day,
                       (info + i)->dateOfBirth.month, (info + i)->dateOfBirth.year, (info + i)->dateOfBirth.age,
                       (info + i)->category, (info + i)->model, (info + i)->points, (info + i)->timeOfLap.minutes,
                       (info + i)->timeOfLap.seconds);
                isAtLeastOneMember = true;
            }
            if (isAtLeastOneMember && i == infoLinesCounter - 1) {
                printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
            }
        }
        if (!isAtLeastOneMember)
            printf("[Ошибка!]Нет ни одного участника с годом рождения больше %i.\n\n", yearOfBirth);
    }
}

void timeOfLapSorting() {
    FILE* file = NULL;
    INFORMATION tmp;
    if (!info)
        printf("[Ошибка!]Сортировка: Файл не открыт!\n\n");
    else if (infoLinesCounter == 0)
        printf("[Ошибка!]Сортировка: Файл пуст!\n\n");
    else {
        if ((file = fopen("info.dat", "wb"))) {
            for (int i = 1; i < infoLinesCounter; i++)
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
            for (int j = 0; j < infoLinesCounter; j++)
                fwrite((info + j), sizeof(INFORMATION), 1, file);
            fclose(file);
            printf("Сортировка: Участники успешно отсортированы!\n\n");
        }
        else printf("[Ошибка!]Сортировка: Не удалось открыть файл! Файл отчищен!\n\n");
    }
}

void numberSearch() {
    int number = 0;
    bool isFounded = false;
    if (!info)
        printf("[Ошибка!]Поиск и фильтрация: Файл не открыт!\n\n");
    else if (infoLinesCounter == 0)
        printf("[Ошибка!]Поиск и фильтрация: Файл пуст!\n\n");
    else {
        do {
            number = checkToEnterOnlyInt(3, "Введите номер: ");
            if (number < 0) {
                printf("[Ошибка!]Введите число больше 0!\n");
                Sleep(1000);
                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
            }
        } while (number < 0);
        system("cls");
        printf("Участник, номер которого %i: ", number);
        for (int i = 0; i < infoLinesCounter; i++) {
            if ((info + i)->number == number) {
                printf("\n--------------------------------------------------------------------------------------------------------------------------------\n");
                printf("|НОМЕР|ИМЯ             ФАМИЛИЯ         ОТЧЕСТВО       |  СТРАНА  |ДАТА  РОЖДЕНИЯ|ВОЗРАСТ|  РАЗРЯД  |  МОДЕЛЬ  |ОЧКИ|ВРЕМЯ КРУГА|\n");
                printf("--------------------------------------------------------------------------------------------------------------------------------\n");
                printf("|%-3i  |%-15s %-15s %-15s|%-10s|  %-2i/%02i/%-4i  |  %-3i  |%-10s|%-10s|%-4i|   %02i:%02i   |\n",
                       (info + i)->number, (info + i)->fullname.firstname, (info + i)->fullname.surname,
                       (info + i)->fullname.lastname, (info + i)->country, (info + i)->dateOfBirth.day,
                       (info + i)->dateOfBirth.month, (info + i)->dateOfBirth.year, (info + i)->dateOfBirth.age,
                       (info + i)->category, (info + i)->model, (info + i)->points, (info + i)->timeOfLap.minutes,
                       (info + i)->timeOfLap.seconds);
                printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
                isFounded = true;
                break;
            }
        }
        if (!isFounded)
            printf("Участник с номером %i не найден.\n\n", number);
    }
}

void surnameSearch() {
    bool isAtLeastOneMember = false;
    char *surname = NULL;
    if (!info)
        printf("[Ошибка!]Поиск и фильтрация: Файл не открыт!\n\n");
    else if (infoLinesCounter == 0)
        printf("[Ошибка!]Поиск и фильтрация: Файл пуст!\n\n");
    else {
        surname = stringInputCheck(49, "Введите фамилию: ");
        system("cls");
        printf("Участники, с фамилией %s: ", surname);
        for (int i = 0; i < infoLinesCounter; i++) {
            if (strcmp((info + i)->fullname.surname, surname) == 0) {
                if (!isAtLeastOneMember) {
                    printf("\n--------------------------------------------------------------------------------------------------------------------------------\n");
                    printf("|НОМЕР|ИМЯ             ФАМИЛИЯ         ОТЧЕСТВО       |  СТРАНА  |ДАТА  РОЖДЕНИЯ|ВОЗРАСТ|  РАЗРЯД  |  МОДЕЛЬ  |ОЧКИ|ВРЕМЯ КРУГА|\n");
                    printf("--------------------------------------------------------------------------------------------------------------------------------\n");
                }
                printf("|%-3i  |%-15s %-15s %-15s|%-10s|  %-2i/%02i/%-4i  |  %-3i  |%-10s|%-10s|%-4i|   %02i:%02i   |\n",
                       (info + i)->number, (info + i)->fullname.firstname, (info + i)->fullname.surname,
                       (info + i)->fullname.lastname, (info + i)->country, (info + i)->dateOfBirth.day,
                       (info + i)->dateOfBirth.month, (info + i)->dateOfBirth.year, (info + i)->dateOfBirth.age,
                       (info + i)->category, (info + i)->model, (info + i)->points, (info + i)->timeOfLap.minutes,
                       (info + i)->timeOfLap.seconds);
                isAtLeastOneMember = true;
            }
            if (isAtLeastOneMember && i == infoLinesCounter - 1)
                printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
        }
        if (!isAtLeastOneMember)
            printf("[Ошибка!]Нет ни одного участника с фамилией %s.\n\n", surname);
    }
}

void countrySearch() {
    bool isAtLeastOneMember = false;
    char *country = NULL;
    if (!info)
        printf("[Ошибка!]Поиск и фильтрация: Файл не открыт!\n\n");
    else if (infoLinesCounter == 0)
        printf("[Ошибка!]Поиск и фильтрация: Файл пуст!\n\n");
    else {
        country = stringInputCheck(49, "Введите страну: ");
        system("cls");
        printf("Участники, из страны %s: ", country);
        for (int i = 0; i < infoLinesCounter; i++) {
            if (strcmp((info + i)->country, country) == 0) {
                if (!isAtLeastOneMember) {
                    printf("\n--------------------------------------------------------------------------------------------------------------------------------\n");
                    printf("|НОМЕР|ИМЯ             ФАМИЛИЯ         ОТЧЕСТВО       |  СТРАНА  |ДАТА  РОЖДЕНИЯ|ВОЗРАСТ|  РАЗРЯД  |  МОДЕЛЬ  |ОЧКИ|ВРЕМЯ КРУГА|\n");
                    printf("--------------------------------------------------------------------------------------------------------------------------------\n");
                }
                printf("|%-3i  |%-15s %-15s %-15s|%-10s|  %-2i/%02i/%-4i  |  %-3i  |%-10s|%-10s|%-4i|   %02i:%02i   |\n",
                       (info + i)->number, (info + i)->fullname.firstname, (info + i)->fullname.surname,
                       (info + i)->fullname.lastname, (info + i)->country, (info + i)->dateOfBirth.day,
                       (info + i)->dateOfBirth.month, (info + i)->dateOfBirth.year, (info + i)->dateOfBirth.age,
                       (info + i)->category, (info + i)->model, (info + i)->points, (info + i)->timeOfLap.minutes,
                       (info + i)->timeOfLap.seconds);
                isAtLeastOneMember = true;
            }
            if (isAtLeastOneMember && i == infoLinesCounter - 1)
                printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
        }
        if (!isAtLeastOneMember)
            printf("[Ошибка!]Нет ни одного участника из страны %s.\n\n", country);
    }
}

void categorySearch() {
    bool isAtLeastOneMember = false;
    char *category = NULL;
    if (!info)
        printf("[Ошибка!]Поиск и фильтрация: Файл не открыт!\n\n");
    else if (infoLinesCounter == 0)
        printf("[Ошибка!]Поиск и фильтрация: Файл пуст!\n\n");
    else {
        category = categoryInput(49, "Введите разряд: ");
        system("cls");
        printf("Участники, с разрядом %s: ", category);
        for (int i = 0; i < infoLinesCounter; i++) {
            if (strcmp((info + i)->category, category) == 0) {
                if (!isAtLeastOneMember) {
                    printf("\n--------------------------------------------------------------------------------------------------------------------------------\n");
                    printf("|НОМЕР|ИМЯ             ФАМИЛИЯ         ОТЧЕСТВО       |  СТРАНА  |ДАТА  РОЖДЕНИЯ|ВОЗРАСТ|  РАЗРЯД  |  МОДЕЛЬ  |ОЧКИ|ВРЕМЯ КРУГА|\n");
                    printf("--------------------------------------------------------------------------------------------------------------------------------\n");
                }
                printf("|%-3i  |%-15s %-15s %-15s|%-10s|  %-2i/%02i/%-4i  |  %-3i  |%-10s|%-10s|%-4i|   %02i:%02i   |\n",
                       (info + i)->number, (info + i)->fullname.firstname, (info + i)->fullname.surname,
                       (info + i)->fullname.lastname, (info + i)->country, (info + i)->dateOfBirth.day,
                       (info + i)->dateOfBirth.month, (info + i)->dateOfBirth.year, (info + i)->dateOfBirth.age,
                       (info + i)->category, (info + i)->model, (info + i)->points, (info + i)->timeOfLap.minutes,
                       (info + i)->timeOfLap.seconds);
                isAtLeastOneMember = true;
            }
            if (isAtLeastOneMember && i == infoLinesCounter - 1)
                printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
        }
        if (!isAtLeastOneMember)
            printf("[Ошибка!]Нет ни одного участника с разрядом %s.\n\n", category);
    }
}

void displayTopMembers() {
    INFORMATION *infoCopy = NULL, tmp;
    system("cls");
    if (!info)
        printf("[Ошибка!]Поиск и фильтрация: Файл не открыт!\n\n");
    else if (infoLinesCounter == 0)
        printf("[Ошибка!]Поиск и фильтрация: Файл пуст!\n\n");
    else {
        infoCopy = (INFORMATION*)realloc(NULL, sizeof(INFORMATION)*infoLinesCounter);
        memcpy(infoCopy, info, sizeof(INFORMATION)*infoLinesCounter);
        if (infoLinesCounter != 1) {
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
        printf("--------------------------------------------------------------------------------------------------------------------------------\n");
        printf("|НОМЕР|ИМЯ             ФАМИЛИЯ         ОТЧЕСТВО       |  СТРАНА  |ДАТА  РОЖДЕНИЯ|ВОЗРАСТ|  РАЗРЯД  |  МОДЕЛЬ  |ОЧКИ|ВРЕМЯ КРУГА|\n");
        printf("--------------------------------------------------------------------------------------------------------------------------------\n");
        for (int i = 0; i < infoLinesCounter && i < 3; i++) {
            printf("|%-3i  |%-15s %-15s %-15s|%-10s|  %-2i/%02i/%-4i  |  %-3i  |%-10s|%-10s|%-4i|   %02i:%02i   |\n",
                   (infoCopy + i)->number, (infoCopy + i)->fullname.firstname, (infoCopy + i)->fullname.surname,
                   (infoCopy + i)->fullname.lastname, (infoCopy + i)->country, (infoCopy + i)->dateOfBirth.day,
                   (infoCopy + i)->dateOfBirth.month, (infoCopy + i)->dateOfBirth.year, (infoCopy + i)->dateOfBirth.age,
                   (infoCopy + i)->category, (infoCopy + i)->model, (infoCopy + i)->points, (infoCopy + i)->timeOfLap.minutes,
                   (infoCopy + i)->timeOfLap.seconds);
        }
        printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
    }
}