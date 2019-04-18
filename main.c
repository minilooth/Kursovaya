#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include <stdbool.h>
#define KEY_UP 72
#define KEY_DOWN 80
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


//Ввод
char* stringInputCheck(int limit, const char* message);//функция ввода только букв
char* bufferedInput(int limit,const char* inputText);//функция ввода ограниченного кол-ва символов
int checkToEnterOnlyInt(int limit, const char *inputText);//функция ввода только целых
//Меню
void indicateCursor(int status);//функция показа/скрытия каретки ввода
int menu();//функция главного меню
int adminSubmenu();//функция подменю администраторов
int userSubmenu();//функция подменю пользователей
int userEditMenu(USER* user, int i);//функция меню редактирования пользователей
int memberEditMenu(INFORMATION* info, int i);//функция меню редактирования участников
int searchingAndFiltering(INFORMATION* info);//фукнция выбора функции меню поиска и фильтрации
int searchAndFilteringMenu();//функция меню поиска и фильтрации
USER* userManagement(USER* user);//функция выбора функции меню управления пользователями
int userManagementMenu();//фукнция меню управления пользователями
//Файлы
int countLines(const char* filename);//функция подсчёта строк в файле
bool checkFile(const char* filename);//функция проверка файла на существование
                                     //true - файл существует, false - файл не существует
bool createFile(const char* filename);//функция создания файла
void crypterTool(int status);//функция шифра Цезаря
//Пользователи
int adminLogin(USER* user);//функция входа администраторов
int userLogin(USER* user);//функция входа пользователей
void registration();//функция регистрации администратора
USER* usersInit(USER* user);//функция открытия файла с аккаунтами
USER* userAdd(USER* user);//функция добавления аккаунта
USER* userDelete(USER* user);//функция удаления аккаунта
USER* userEdit(USER* user);//функция редактирования аккаунта
void displayEditableUser(USER* user, int i);//функция вывода редактируемого аккаунта
void displayAllUsers(USER* user);//функция вывода всех аккаунтов
//Участники
INFORMATION* membersInit(INFORMATION* info);//функция открытия файла с участниками
INFORMATION* memberAdd(INFORMATION* info);//функция добавления участника
INFORMATION* memberEdit(INFORMATION* info);//функция редактирования участника
INFORMATION* memberDelete(INFORMATION *info);//функция удаления участника
void displayEditableMember(INFORMATION* info, int i);//функция вывода редактирумого участника
void displayAllMembers(INFORMATION* info);//функция вывода всех участников
//Фильтрация и поиск
void pointsFilter(INFORMATION* info);//функция фильтрации по очкам
void timeOfLapFilter(INFORMATION* info);//функция фильтрации по времени круга
void ageFilter(INFORMATION* info);//функция фильтрации по возрасту
void yearOfBirthFilter(INFORMATION* info);//функция фильтрации по году рождения
void timeOfLapSorting(INFORMATION* info);//функция сортировки по времени круга
void numberSearch(INFORMATION* info);//функция поиска по номеру
void surnameSearch(INFORMATION* info);//функция поиска по фамилии
void countrySearch(INFORMATION* info);//функция поиска по стране
void categorySearch(INFORMATION* info);//функция поиска по разряду
void displayTopMembers(INFORMATION* info);//функция вывода топ-3 лучших участников


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    system("color 0B");
    INFORMATION *info = NULL;
    USER *user = NULL;
    user = usersInit(user);
    bool adminSubMenuFlag = false, userSubMenuFlag = true;
    while (true) {
        system("cls");
        switch (menu()) {
            case 1: {
                if (adminLogin(user) == true) {
                    while (adminSubMenuFlag == false) {
                        system("cls");
                        switch (adminSubmenu()) {
                            case 1: {
                                system("cls");
                                if (checkFile("info.txt") == false) {
                                    printf("[Ошибка!]Открытие информации: Файл ещё не создан!\n");
                                    if ((createFile("info.txt")) != false) {
                                        printf("Открытие информации: Файл успешно создан!\n");
                                        info = membersInit(info);
                                    } else printf("[Ошибка!]Открытие информации: Не удалось создать файл!\n");
                                } else info = membersInit(info);
                                break;
                            }
                            case 2: info = memberAdd(info); break;
                            case 3: info = memberEdit(info); break;
                            case 4: info = memberDelete(info); break;
                            case 5: {
                                system("cls");
                                displayAllMembers(info);
                                system("pause");
                                break;
                            }
                            case 6: searchingAndFiltering(info); break;
                            case 7: user = userManagement(user); break;
                            case 8: adminSubMenuFlag = true; break;
                            default: break;
                        }
                        if (adminSubMenuFlag == true) break;
                    }
                    adminSubMenuFlag = false;
                }
                break;
            }
            case 2: {
                if (userLogin(user) == true) {
                    while (userSubMenuFlag == false) {
                        system("cls");
                        switch (userSubmenu()) {
                            case 1: {
                                system("cls");
                                if (checkFile("info.txt") == true) {
                                    info = membersInit(info);
                                } else {
                                    printf("[Ошибка!]Открытие информации: Файл ещё не создан!\n\n");
                                    system("pause");
                                }
                                break;
                            }
                            case 2: displayAllMembers(info); break;
                            case 3: displayTopMembers(info); break;
                            case 4: searchingAndFiltering(info); break;
                            case 5: userSubMenuFlag = true; break;
                            default: break;
                        }
                        if (userSubMenuFlag == true) break;
                    }
                    userSubMenuFlag = false;
                }
                break;
            }
            case 3: free(info); free(user); return 0;
            default: break;
        }
    }
}


//Всё что связано с вводом
char* stringInputCheck(int limit, const char* message){
    char *buffer = NULL;
    int i = 0, checkLetter = 0, checkSymbol = 0;
    bool isLetter = false;
    while (true) {
        i = 0;
        buffer = bufferedInput(limit, message);
        while (buffer[i] != '\0') {
            checkLetter = isdigit((unsigned char)buffer[i]);
            checkSymbol = isalnum((unsigned char)buffer[i]);
            if (checkLetter != 0 || checkSymbol == 0) {
                isLetter = false;
                break;
            }
            else isLetter = true;
            i++;
        }
        if (isLetter == true)
            return buffer;
        else {
            printf("[Ошибка!]Ошибочный ввод!\n");
        }
    }
}

char* bufferedInput(int limit,const char* inputText) {
    char ch, *buffer = NULL;
    int i = 0;
    buffer = (char*)realloc(NULL, sizeof(char)*(limit + 1));
    printf("%s", inputText);
    while (true) {
        ch = (char)_getch();
        if (ch != '\0') {
            if (ch == 13 || ch == 9) {
                if (i > 0){
                    buffer[i] = '\0';
                    putchar('\n');
                    break;
                } else {
                    printf("\n[Ошибка!]Введите хотябы один символ!\n");
                    printf("%s", inputText);
                }
            }
            else if (ch == 8 && i > 0) {
                i--;
                printf("\b \b");
            }
            else if (ch == 8 && i == 0)
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

int checkToEnterOnlyInt(int limit,const char *inputText) {
    char *buffer = NULL;
    int numberEntered = 0, i = 0, check = 0;
    bool isNumeral = false, flag = false;
    while (true) {
        i = 0;
        buffer = bufferedInput(limit, inputText);
        while (buffer[i] != '\0') {
            if (buffer[i] == '-' && flag == false) {
                i++;
                flag = true;
            }
            check = isdigit((unsigned char)buffer[i]);
            if (check == 0) {
                isNumeral = false;
                break;
            }
            else isNumeral = true;
            i++;
        }
        if (isNumeral == true) {
            numberEntered = strtol(buffer, NULL, 10);
            free(buffer);
            return numberEntered;
        }
        else printf("[Ошибка!]Не правильный ввод!\n");
    }
}


//Все что связано с меню
void indicateCursor(int status) {
    void* hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(hConsole, &structCursorInfo);
    structCursorInfo.bVisible = status;
    SetConsoleCursorInfo(hConsole, &structCursorInfo);
}

int menu(){
    int choice = 1, ch = ' ';
    char *line[] = {"Вход под администратором.", "Вход под пользователем.", "Выход.", NULL} , pointer = '>';
    indicateCursor(false);
    while(true){
        if (ch != 0){
            system("cls");
            if (ch == KEY_RETURN) {
                indicateCursor(true);
                return choice;
            }
            if (ch == KEY_UP) choice--;
            if (ch == KEY_DOWN) choice++;
            if (choice > 3) choice = 1;
            if (choice < 1) choice = 3;
            printf("Меню:\n");
            for(int i = 0; line[i]; i++) {
                if(choice == i + 1) {
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

int adminSubmenu(){
    int choice = 1, ch = ' ';
    char pointer = '>', *line[] = {"Создание/открытие файла.", "Добавление записи.", "Редактирование записи.",
                                   "Удаление записи.", "Просмотр всех данных в табличной форме.",
                                   "Различные процедуры поиска и фильтрации данных.", "Управление пользователями.",
                                   "Выход в меню.", NULL};
    indicateCursor(false);
    while(true){
        if (ch != 0){
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
            for(int i = 0; line[i]; i++){
                if(choice == i + 1) {
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

int userSubmenu(){
    int choice = 1, ch = ' ';
    char pointer = '>', *line[] = {"Открытие файла с данными.", "Просмотр всех данных в табличной форме.",
                                    "Просмотр топ-3 самых быстрых участников.", "Различные процедуры поиска и фильтрации данных.",
                                    "Выход в меню.", NULL};
    indicateCursor(false);
    while(true){
        if (ch != 0){
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
            for(int i = 0; line[i]; i++){
                if(choice == i + 1) {
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

int userEditMenu(USER* user, int i){
    int choice = 1, ch = ' ';
    char pointer = '>', *line[] = {"Изменить логин.", "Изменить пароль.", "Изменить права администратора.",
                                   "Выход из меню редактирования аккунтов.", NULL};
    while (true) {
        if (ch != 0) {
            displayEditableUser(user, i);
            indicateCursor(false);
            if (ch == KEY_RETURN) {
                indicateCursor(true);
                return choice;
            }
            if (ch == KEY_UP) choice--;
            if (ch == KEY_DOWN) choice++;
            if (choice > 4) choice = 1;
            if (choice < 1) choice = 4;
            printf("Меню редактирования аккаунтов:\n");
            for(int j = 0; line[j]; j++){
                if(choice == j + 1) {
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

int memberEditMenu(INFORMATION* info, int i){
    int choice = 1, ch = ' ';
    char pointer = '>', *line[] = {"Изменение номера участника.", "Изменение имени участника.",
                                   "Изменение фамилии участника.", "Изменение отчества участника.",
                                   "Изменение страны участника.", "Изменение дня рождения участника.",
                                   "Изменение месяца рождения участника.", "Изменение года рождения участника.",
                                   "Изменение разряда участника.", "Изменение модели коньков участника.",
                                   "Изменение количества очков участника.", "Изменение минут круга участника.",
                                   "Изменение секунд круга участника.", "Выход из меню редактирования участника.", NULL};
    while (true) {
        if (ch != 0) {
            displayEditableMember(info, i);
            indicateCursor(false);
            if (ch == KEY_RETURN) {
                indicateCursor(true);
                return choice;
            }
            if (ch == KEY_UP) choice--;
            if (ch == KEY_DOWN) choice++;
            if (choice > 14) choice = 1;
            if (choice < 1) choice = 14;
            printf("Меню редактирования учаcтника:\n");
            for(int j = 0; line[j]; j++){
                if(choice == j + 1) {
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

int searchingAndFiltering(INFORMATION* info){
    while (1) {
        system("cls");
        switch (searchAndFilteringMenu()) {
            case 1: pointsFilter(info); break;
            case 2: timeOfLapFilter(info); break;
            case 3: ageFilter(info); break;
            case 4: yearOfBirthFilter(info); break;
            case 5: numberSearch(info); break;
            case 6: surnameSearch(info); break;
            case 7: countrySearch(info); break;
            case 8: categorySearch(info); break;
            case 9: timeOfLapSorting(info); break;
            case 10: return 0;
            default: break;
        }
    }
}

int searchAndFilteringMenu(){
    int choice = 1, ch = ' ';
    char pointer = '>', *line[] = {"Фильтр по количеству очков.", "Фильтр по времени круга.",
                                   "Фильтр по возрасту.", "Фильтр по году рождения.", "Поиск по номеру.",
                                   "Поиск по фамилии.", "Поиск по стране.", "Поиск по разряду.",
                                   "Сортировка по времени круга.", "Выход из меню поиска и фильтрации.", NULL};
    while (true) {
        if (ch != 0) {
            system("cls");
            indicateCursor(false);
            if (ch == KEY_RETURN) {
                indicateCursor(true);
                return choice;
            }
            if (ch == KEY_UP) choice--;
            if (ch == KEY_DOWN) choice++;
            if (choice > 10) choice = 1;
            if (choice < 1) choice = 10;
            printf("Меню поиска и фильтрации:\n");
            for(int i = 0; line[i]; i++){
                if(choice == i + 1) {
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

USER* userManagement(USER* user) {
    while (1) {
        system("cls");
        switch (userManagementMenu()) {
            case 1: user = userAdd(user); break;
            case 2: user = userDelete(user); break;
            case 3: user = userEdit(user); break;
            case 4: {
                system("cls");
                displayAllUsers(user);
                system("pause");
                break;
            }
            case 5: return user;
            default: break;
        }
    }
}

int userManagementMenu(){
    int choice = 1, ch = ' ';
    char pointer = '>', *line[] = {"Добавить аккаунт.", "Удалить аккаунт.", "Редактировать аккаунт.",
                                   "Просмотр всех аккаунтов.", "Назад.", NULL};
    indicateCursor(false);
    while(1){
        if (ch != 0){
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
            for(int i = 0; line[i]; i++){
                if(choice == i + 1) {
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
int countLines(const char* filename) {
    FILE* file;
    int counter = 0;
    if ((file = fopen(filename, "r")) == NULL)
        return 0;
    while (!feof(file)) {
        fscanf(file, "%*[^\n]%*c");
        counter++;
    }
    fclose(file);
    return counter;
}

bool checkFile(const char* filename){
    FILE* file = NULL;
    if ((file = fopen(filename, "rt+")) == NULL) {
        return false;
    } else {
        fclose(file);
        return true;
    }
}

bool createFile(const char* filename){
    FILE* file = NULL;
    if ((file = fopen(filename, "wt")) != NULL) {
        fclose(file);
        return true;
    } else return false;
}

void crypterTool(int status){
    int ch, key = 0;
    if (status == ENCRYPT) key = 2;
    else if (status == DECRYPT) key = -2;
    FILE *input = NULL, *output = NULL;
    if ((input = fopen("db.txt", "r")) == NULL) {
        printf("[Ошибка!]Шифрование: Не удалось открыть файл с логинами/паролями!\n\n");
        system("pause");
        exit(0);
    }
    if ((output = fopen("tempdb.txt", "w")) == NULL) {
        printf("[Ошибка!]Шифрование: Не удалось создать временный файл с логинами/паролями!\n\n");
        system("pause");
        exit(0);
    }
    while ((ch = getc(input)) != EOF) {
        if(ch != '\n') {
            ch += key;
            putc(ch, output);
        } else putc(ch,output);
    }
    fclose(input);
    fclose(output);
    if ((input = fopen("db.txt", "w")) == NULL) {
        printf("[Ошибка!]Шифрование: Не удалось перезаписать файл с логинами/паролями!\n\n");
        system("pause");
        exit(0);
    }
    if ((output = fopen("tempdb.txt", "r")) == NULL) {
        printf("[Ошибка!]Шифрование: Не удалось открыть временный файл с логинами/паролями!\n\n");
        system("pause");
        exit(0);
    }
    while ((ch = getc(output)) != EOF)
        putc(ch, input);
    fclose(output);
    if ((remove("tempdb.txt")) != 0) {
        printf("[Ошибка!]Шифрование: Не удалось удалить временный файл с логинами/паролями!\n\n");
        system("pause");
        exit(0);
    }
    fclose(input);
}


//Всё что связано с пользователями
int adminLogin(USER *user) {
    system("cls");
    int i = 0, j = 0, counter = 0;
    bool isLoginRight = false, isPasswordRight = false;
    char *login = NULL, password[30], ch;
    do {
        login = bufferedInput(29, "Введите логин: ");
        for (i = 0; i < usersLinesCounter; i++)
            if (strcmp(login, (user + i)->login) == 0) {
                isLoginRight = true;
                break;
            }
        if (isLoginRight == false) {
            printf("[Ошибка!]Такого администратора не существует!\n\n");
            system("pause");
            return false;
        }
    } while (isLoginRight != true);
    do {
        j = 0;
        printf("Введите пароль: ");
        while (true) {
            ch = (char)_getch();
            if (ch != '\0') {
                if (ch == KEY_RETURN || ch == KEY_TAB) {
                    counter++;
                    password[j] = '\0';
                    break;
                }
                else if (ch == KEY_BKSP && j > 0) {
                    j--;
                    printf("\b \b");
                }
                else if (ch == KEY_BKSP && j == 0) {
                    continue;
                }
                else {
                    if (j < 29 && counter <= 5) {
                        password[j++] = ch;
                        putchar('*');
                    } else if(j < 29){
                        password[j++] = ch;
                        putchar(ch);
                    }
                }
            }
        }
        if (strcmp(password, (user + i)->password) == 0)
            isPasswordRight = true;
        else printf("\n[Ошибка!]Неверный пароль!\n");
    } while (isPasswordRight != true);
    if ((user + i)->isAdmin == true) {
        printf("\nВы успешно авторизовались.\n\n");
        free(login);
        system("pause");
        return true;
    }
    else {
        printf("\n[Ошибка!]Авторизация: Войдите через пользователя!\n\n");
        system("pause");
        free(login);
        return false;
    }
}

int userLogin(USER *user) {
    system("cls");
    int i = 0, j = 0, counter = 0;
    bool isLoginRight = false, isPasswordRight = false;
    char *login = NULL, password[30], ch;
    do {
        login = bufferedInput(29, "Введите логин: ");
        for (i = 0; i < usersLinesCounter; i++)
            if (strcmp(login, (user + i)->login) == 0) {
                isLoginRight = true;
                break;
            }
        if (isLoginRight == false) {
            printf("[Ошибка!]Такого пользователя не существует!\n\n");
            system("pause");
            free(login);
            return false;
        }
    } while (isLoginRight != true);
    do {
        j = 0;
        printf("Введите пароль: ");
        while (true) {
            ch = (char)_getch();
            if (ch != '\0') {
                if (ch == KEY_RETURN || ch == KEY_TAB) {
                    password[j] = '\0';
                    break;
                }
                else if (ch == KEY_BKSP && j > 0) {
                    j--;
                    printf("\b \b");
                }
                else if (ch == KEY_BKSP && j == 0) {
                    continue;
                }
                else {
                    if (j < 29 && counter <= 5) {
                        password[j++] = ch;
                        putchar('*');
                    } else if(j < 29){
                        password[j++] = ch;
                        putchar(ch);
                    }
                }
            }
        }
        if (strcmp(password, (user + i)->password) == 0)
            isPasswordRight = true;
        else printf("\n[Ошибка!]Неверный пароль!\n");
    } while (isPasswordRight != true);
    if ((user + i)->isAdmin == false) {
        printf("\nВы успешно авторизовались.\n\n");
        free(login);
        system("pause");
        return true;
    }
    else {
        printf("\n[Ошибка!]Авторизация! Войдите через администратора!\n\n");
        system("pause");
        free(login);
        return false;
    }
}

void registration(){
    FILE *file = NULL;
    char *login = NULL, password[30], ch;
    int i = 0;
    printf("Регистрация администратора.\n\n");
    login = bufferedInput(29,"Введите логин: ");
    printf("Введите пароль: ");
    while (1) {
        ch = (char) _getch();
        if (ch != '\0') {
            if (ch == KEY_RETURN || ch == KEY_TAB) {
                password[i] = '\0';
                break;
            } else if (ch == KEY_BKSP && i > 0) {
                i--;
                printf("\b \b");
            } else if (ch == KEY_BKSP && i == 0) {
                continue;
            } else if (i < 29) {
                password[i++] = ch;
                putchar('*');
            }
        }
    }
    if ((file = fopen("db.txt", "a+")) != NULL) {
        fprintf(file, "%s %s %i\n", login, password, 1);
        fclose(file);
        crypterTool(ENCRYPT);
    } else {
        printf("[Ошибка!]Регистрация: Не удалось открыть файл для добавления нового администратора!\n");
        exit(0);
    }
    system("cls");
}

USER* usersInit(USER* user) {
    FILE* file = NULL;
    if((checkFile("db.txt")) != false){
        //Если файл существует
        usersLinesCounter = countLines("db.txt") - 1;  //Посчитать кол-во строк в файле
        if(usersLinesCounter != 0){
            //Если есть хотябы одна строка
            crypterTool(DECRYPT); //Расшифровать файл
            if ((file = fopen("db.txt", "r")) != NULL) {
                //Если файл удалось открыть для чтения
                user = (USER *) malloc(usersLinesCounter * (sizeof(USER)));
                for (int i = 0; i < usersLinesCounter; i++)
                    fscanf(file, "%s %s %i", (user + i)->login, (user + i)->password, &((user + i)->isAdmin));
                fclose(file);
            } else {
                //Если файл не удалось открыть
                printf("[Ошибка!]Инициальзация пользователей: Не удалось открыть файл с логинами/паролями!\n");
                system("pause");
                exit(0);
            }
            crypterTool(ENCRYPT); //Зашифровать файл
        } else {
            //Если нет ни одной строки
            registration();
            user = usersInit(user);
        }
    } else if((createFile("db.txt")) != false){
        //Если файл не существует - создать
        registration();
        user = usersInit(user);
    } else{
        //Если файл не существует и его не удалось создать
        printf("[Ошибка!]Инициальзация пользователей: Не удалось создать файл с логинами/паролями!\n");
        system("pause");
        exit(0);
    }
    return user;
}

USER* userAdd(USER* user) {
    bool isLoginExist = false;
    char *login = NULL, *password = NULL;
    FILE* file = NULL;
    user = (USER*)realloc(user, (usersLinesCounter + 1) * sizeof(USER));
    printf("Добавить пользователя:\n");
    do {
        login = bufferedInput(29, "Введите логин: ");
        for (int i = 0; i < usersLinesCounter; i++) {
            if (strcmp((user + i)->login, login) == 0) {
                isLoginExist = true;
                break;
            } else isLoginExist = false;
        }
        if (isLoginExist == true) printf("[Ошибка!]Такой аккаунт уже существует!\n");
        else strcpy((user + usersLinesCounter)->login, login);
    } while (isLoginExist == true);
    free(login);
    password = bufferedInput(29, "Введите пароль: ");
    strcpy((user + usersLinesCounter)->password, password);
    free(password);
    do {
        (user + usersLinesCounter)->isAdmin = checkToEnterOnlyInt(1,"Администратор?(1 - Да|0 - Нет): ");
        if ((user + usersLinesCounter)->isAdmin < 0 || (user + usersLinesCounter)->isAdmin > 1)
            printf("[Ошибка!]Не правильный ввод! Введите число от 0 до 1!\n");
    } while ((user + usersLinesCounter)->isAdmin < 0 || (user + usersLinesCounter)->isAdmin > 1);
    if((checkFile("db.txt")) != false){
        //Если файл существует
        crypterTool(DECRYPT);//Расшифровать
        if((file = fopen("db.txt", "at+")) != NULL) {
            //Если файл удалось открыть
            fprintf(file, "%s %s %i\n", (user + usersLinesCounter)->login, (user + usersLinesCounter)->password,
                    (user + usersLinesCounter)->isAdmin);
            fclose(file);
            printf("\nАккаунт успешно добавлен!\n\n");
            _flushall();
            usersLinesCounter++;
        } else printf("[Ошибка!]Добавление пользователей: Ошибка открытия файла с логинами/паролями! Пользователь не добавлен!\n\n"); //Если файл не удалось открыть
        crypterTool(ENCRYPT);//Зашифровать
    } else printf("[Ошибка!]Добавление пользователей: Файл не существует!\n\n"); //Если файл не существует
    system("pause");
    return user;
}

USER* userDelete(USER* user) {
    char *login = NULL;
    int i = 0;
    bool isLoginExist = false;
    FILE* file = NULL;
    displayAllUsers(user);
    printf("Удаление аккаунта.\n");
    do {
        login = bufferedInput(29, "Введите логин аккаунта, который вы хотите удалить: ");
        for (i = 0; i < usersLinesCounter; i++) {
            if (strcmp((user + i)->login, login) == 0) {
                isLoginExist = true;
                break;
            }
        }
        if (isLoginExist == false)
            printf("[Ошибка!]Такого аккаунта не существует!\n");
    } while (isLoginExist != true);
    free(login);
    if((checkFile("db.txt")) != false){
        //Если файл существует
        crypterTool(DECRYPT);//Расшифровать
        if((file = fopen("db.txt", "w")) != NULL) {
            //Если файл удалось пересоздать
            for (int j = i; j < usersLinesCounter; j++)
                *(user + j) = *(user + (j + 1));
            user = (USER *) realloc(user, sizeof(USER) * usersLinesCounter);
            usersLinesCounter--;
            for (int j = 0; j < usersLinesCounter; j++)
                fprintf(file, "%s %s %i\n", (user + j)->login, (user + j)->password, (user + j)->isAdmin);
            fclose(file);
            printf("\nАккаунт успешно удалён!\n\n");
        } else printf("[Ошибка!]Удаление пользователей: Ошибка открытия файла с логинами/паролями! Файл отчищен!\n\n");//Если файл не удалось пересоздать
        crypterTool(ENCRYPT);//Зашифровать
    } else printf("[Ошибка!]Удаление пользователей: Ошибка открытия файла с логинами/паролями!\n\n"); //Если файл не существует
    system("pause");
    return user;
}

USER* userEdit(USER* user) {
    char *login = NULL, *newLogin = NULL, *newPassword = NULL;
    int i = 0;
    bool isLoginExist = false, isNewLoginExist = false, editFlag = false;
    FILE* file = NULL;
    displayAllUsers(user);
    do {
        login = bufferedInput(29, "Введите логин аккаунта, который вы хотите отредактировать: ");
        for (i = 0; i < usersLinesCounter; i++) {
            if (strcmp((user + i)->login, login) == 0) {
                isLoginExist = true;
                break;
            } else isLoginExist = false;
        }
        if (isLoginExist == false)
            printf("[Ошибка!]Такого аккаунта не существует!\n");
    } while (isLoginExist == false);
    free(login);
    while (editFlag == false) {
        switch (userEditMenu(user,i)) {
            case 1: {
                printf("Изменить логин.\n");
                do {
                    newLogin = bufferedInput(29, "Введите новый логин: ");
                    for (int j = 0; j < usersLinesCounter; j++) {
                        if (strcmp((user + j)->login, newLogin) == 0) {
                            isNewLoginExist = true;
                            break;
                        }
                        else isNewLoginExist = false;
                    }
                    if (isNewLoginExist == true) printf("[Ошибка!]Такой логин уже существует!\n");
                } while (isNewLoginExist == true);
                strcpy((user + i)->login, newLogin);
                displayEditableUser(user, i);
                printf("Логин успешно изменен!\n\n");
                free(newLogin);
                system("pause");
                break;
            }
            case 2: {
                printf("Изменение пароля.\n");
                newPassword = bufferedInput(29, "Введите новый пароль: ");
                strcpy((user + i)->password, newPassword);
                displayEditableUser(user, i);
                printf("Пароль успешно изменен!\n\n");
                free(newPassword);
                system("pause");
                break;
            }
            case 3: {
                if ((user + i)->isAdmin == true) {
                    (user + i)->isAdmin = false;
                    displayEditableUser(user, i);
                    printf("Права администратора успешно изменены.\n\n");
                    system("pause");
                    break;
                }
                else {
                    (user + i)->isAdmin = true;
                    displayEditableUser(user, i);
                    printf("Права администратора успешно изменены.\n\n");
                    system("pause");
                    break;
                }
            }
            case 4: editFlag = true; break;
            default: break;
        }
        if (editFlag == true) break;
    }
    if ((checkFile("db.txt")) != false){
        //Если файл существует
        crypterTool(DECRYPT);//Расшифровать
        if((file = fopen("db.txt", "w")) != NULL) {
            //Если файл удалось пересоздать
            for (i = 0; i < usersLinesCounter; i++)
                fprintf(file, "%s %s %i\n", (user + i)->login, (user + i)->password, (user + i)->isAdmin);
            fclose(file);
        } else printf("[Ошибка!]Редактирование пользователей: Не удалось открыть файл с логинами/паролями! Файл отчищен!\n\n");//Если файл не удалось пересоздать
        crypterTool(ENCRYPT);//Зашифровать
    } else printf("[Ошибка!]Редактирование пользователей: Не удалось открыть файл с логинами/паролями!\n\n");//Если файл не существует
    return user;
}

void displayEditableUser(USER* user, int i){
    char yes[] = "Да", no[] = "Нет";
    system("cls");
    printf("-----------------------------------------------------------------------------------------\n");
    printf("|ЛОГИН:                         |ПАРОЛЬ:                         |ПРАВА АДМИНИСТРАТОРА: |\n");
    printf("-----------------------------------------------------------------------------------------\n");
    printf("|%-31s|%-32s|%-22s|", (user + i)->login, (user + i)->password, (user + i)->isAdmin == 1 ? yes : no);
    printf("\n-----------------------------------------------------------------------------------------\n\n");
}

void displayAllUsers(USER* user) {
    char yes[] = "Да", no[] = "Нет";
    printf("------------------------------------------------------------------------------------------------\n");
    printf("|№    |ЛОГИН:                         |ПАРОЛЬ:                         |ПРАВА АДМИНИСТРАТОРА: |\n");
    printf("------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < usersLinesCounter; i++)
        printf("|%-5i|%-31s|%-32s|%-22s|\n", i + 1, (user + i)->login, (user + i)->password, (user + i)->isAdmin == 1 ? yes : no);
    printf("------------------------------------------------------------------------------------------------\n\n");
}


//Всё что связано с информацией
INFORMATION* membersInit(INFORMATION* info) {
    FILE *file = NULL;
    if(info != NULL)
        printf("[Ошибка!]Открытие информации: Файл уже открыт!\n\n");
    else {
        if ((file = fopen("info.txt", "rt+")) != NULL) {
            infoLinesCounter = countLines("info.txt") - 1;
            if (infoLinesCounter != -1) {
                info = (INFORMATION *) malloc(infoLinesCounter * sizeof(INFORMATION));
                for (int i = 0; i < infoLinesCounter; i++) {
                    fscanf(file, "%i %s %s %s %s %i %i %i %i %s %s %i %i %i", &((info + i)->number),
                           (info + i)->fullname.firstname, (info + i)->fullname.surname, (info + i)->fullname.lastname,
                           (info + i)->country, &((info + i)->dateOfBirth.day), &((info + i)->dateOfBirth.month),
                           &((info + i)->dateOfBirth.year), &((info + i)->dateOfBirth.age), (info + i)->category,
                           (info + i)->model, &((info + i)->points), &((info + i)->timeOfLap.minutes),
                           &((info + i)->timeOfLap.seconds));
                }
            }
            fclose(file);
            printf("Открытие информации: Файл успешно открыт!\n\n");
        }
    }
    system("pause");
    return info;
}

INFORMATION* memberAdd(INFORMATION* info) {
    FILE *file = NULL;
    time_t t = time(NULL);
    struct tm *aTm = localtime(&t);
    bool isMemberExist = false;
    char *firstname = NULL, *surname = NULL, *lastname = NULL, *country = NULL, *category = NULL, *model = NULL;
    if (info == NULL)
        printf("[Ошибка!]Добавление информации: Файл не открыт!\n\n");
    else if ((file = fopen("info.txt", "a+")) == NULL)
        printf("[Ошибка!]Добавление информации: Не удалось открыть файл для добавления!\n");
    else {
        info = (INFORMATION *) realloc(info, ((infoLinesCounter + 1) * sizeof(INFORMATION)));
        printf("Добавление участника.\n");
        do {
            do {
                (info + infoLinesCounter)->number = checkToEnterOnlyInt(3, "Введите номер участника: ");
                if ((info + infoLinesCounter)->number < 1)
                    printf("[Ошибка!]Введите число больше 0!\n");
            } while ((info + infoLinesCounter)->number < 1);
            for (int i = 0; i < infoLinesCounter; i++) {
                if ((info + i)->number == (info + infoLinesCounter)->number) {
                    isMemberExist = true;
                    break;
                } else isMemberExist = false;
            }
            if (isMemberExist == true) printf("Участник с таким номером уже существует!\n");
        } while (isMemberExist == true);
        firstname = stringInputCheck(49,"Введите имя участника: ");
        strcpy((info + infoLinesCounter)->fullname.firstname, firstname);
        free(firstname);
        surname = stringInputCheck(49, "Введите фамилию участника: ");
        strcpy((info + infoLinesCounter)->fullname.surname, surname);
        free(surname);
        lastname = stringInputCheck(49, "Введите отчество участника: ");
        strcpy((info + infoLinesCounter)->fullname.lastname, lastname);
        free(lastname);
        country = stringInputCheck(29, "Введите страну учатника: ");
        strcpy((info + infoLinesCounter)->country, country);
        free(country);
        do {
            (info + infoLinesCounter)->dateOfBirth.day = checkToEnterOnlyInt(2,"Введите день рождения участника: ");
            if ((info + infoLinesCounter)->dateOfBirth.day < 1 || (info + infoLinesCounter)->dateOfBirth.day > 31)
                printf("[Ошибка!]Введите число от 1 до 31!\n");
        } while ((info + infoLinesCounter)->dateOfBirth.day < 1 || (info + infoLinesCounter)->dateOfBirth.day > 31);
        do {
            (info + infoLinesCounter)->dateOfBirth.month = checkToEnterOnlyInt(2,"Введите месяц рождения участника(числом): ");
            if ((info + infoLinesCounter)->dateOfBirth.month < 1 || (info + infoLinesCounter)->dateOfBirth.month > 12)
                printf("[Ошибка!]Введите число от 1 до 12!\n");
        } while ((info + infoLinesCounter)->dateOfBirth.month < 1 || (info + infoLinesCounter)->dateOfBirth.month > 12);
        do {
            (info + infoLinesCounter)->dateOfBirth.year = checkToEnterOnlyInt(4,"Введите год рождения участника: ");
            if ((info + infoLinesCounter)->dateOfBirth.year < 1900 ||
                (info + infoLinesCounter)->dateOfBirth.year > 2019)
                printf("[Ошибка!]Введите число от 1900 до 2019!\n");
        } while ((info + infoLinesCounter)->dateOfBirth.year < 1900 ||
                 (info + infoLinesCounter)->dateOfBirth.year > 2019);
        if ((info + infoLinesCounter)->dateOfBirth.month > aTm->tm_mon + 1)
            (info + infoLinesCounter)->dateOfBirth.age = 2018 - (info + infoLinesCounter)->dateOfBirth.year;
        else (info + infoLinesCounter)->dateOfBirth.age = 2019 - (info + infoLinesCounter)->dateOfBirth.year;
        category = stringInputCheck(29, "Введите разряд участника: ");
        strcpy((info + infoLinesCounter)->category, category);
        free(category);
        model = stringInputCheck(29, "Введите модель коньков участника: ");
        strcpy((info + infoLinesCounter)->model, model);
        free(model);
        do {
            (info + infoLinesCounter)->points = checkToEnterOnlyInt(4,"Введите количество очков участника: ");
            if ((info + infoLinesCounter)->points < 0 || (info + infoLinesCounter)->points > 9999)
                printf("[Ошибка!]Введите число от 0 до 9999!\n");
        } while ((info + infoLinesCounter)->points < 0 || (info + infoLinesCounter)->points > 9999);
        do {
            (info + infoLinesCounter)->timeOfLap.minutes = checkToEnterOnlyInt(2,"Введите минуты круга участника: ");
            if ((info + infoLinesCounter)->timeOfLap.minutes < 0 || (info + infoLinesCounter)->timeOfLap.minutes > 59)
                printf("[Ошибка!]Введите число от 0 до 59!\n");
        } while ((info + infoLinesCounter)->timeOfLap.minutes < 0 || (info + infoLinesCounter)->timeOfLap.minutes > 59);
        do {
            (info + infoLinesCounter)->timeOfLap.seconds = checkToEnterOnlyInt(2,"Введите секунды круга участника: ");
            if ((info + infoLinesCounter)->timeOfLap.seconds < 0 || (info + infoLinesCounter)->timeOfLap.seconds > 59)
                printf("[Ошибка!]Введите число от 0 до 59!\n");
        } while ((info + infoLinesCounter)->timeOfLap.seconds < 0 || (info + infoLinesCounter)->timeOfLap.seconds > 59);
        fprintf(file, "%i %s %s %s %s %i %i %i %i %s %s %i %i %i\n", (info + infoLinesCounter)->number,
                (info + infoLinesCounter)->fullname.firstname, (info + infoLinesCounter)->fullname.surname,
                (info + infoLinesCounter)->fullname.lastname, (info + infoLinesCounter)->country,
                (info + infoLinesCounter)->dateOfBirth.day, (info + infoLinesCounter)->dateOfBirth.month,
                (info + infoLinesCounter)->dateOfBirth.year, (info + infoLinesCounter)->dateOfBirth.age,
                (info + infoLinesCounter)->model, (info + infoLinesCounter)->category,
                (info + infoLinesCounter)->points, (info + infoLinesCounter)->timeOfLap.minutes,
                (info + infoLinesCounter)->timeOfLap.seconds);
        _flushall();
        fclose(file);
        infoLinesCounter++;
        printf("Участник успешно добавлен!\n\n");
    }
    system("pause");
    return info;
}

INFORMATION* memberDelete(INFORMATION *info) {
    int delNumber = 0, i = 0;
    bool isNumberExist = false;
    FILE *file = NULL;
    if (info == NULL) {
        printf("[Ошибка!]Удаление информации: Файл не открыт!\n\n");
    } else if (infoLinesCounter == 0) {
        printf("[Ошибка!]Удаление информации: Файл пуст!\n\n");
    } else {
        displayAllMembers(info);
        printf("Удаление участника.\n");
        do {
            delNumber = checkToEnterOnlyInt(3,"Введите номер участника для удаления: ");
            for (i = 0; i < infoLinesCounter; i++) {
                if (delNumber == (info + i)->number) {
                    isNumberExist = true;
                    break;
                } else isNumberExist = false;
            }
            if (isNumberExist == false) printf("[Ошибка!]Участника с таким номером не существует!\n");
        } while (isNumberExist != true);
        for(int j = i; j < infoLinesCounter; j++)
            *(info + j) = *(info + (j + 1));
        info = (INFORMATION*)realloc(info,sizeof(INFORMATION)*infoLinesCounter);
        infoLinesCounter--;
        if((checkFile("info.txt")) != false) {
            if ((file = fopen("info.txt", "w")) != NULL) {
                for (int j = 0; j < infoLinesCounter; j++) {
                    fprintf(file, "%i %s %s %s %s %i %i %i %i %s %s %i %i %i\n", (info + j)->number,
                            (info + j)->fullname.firstname, (info + j)->fullname.surname, (info + j)->fullname.lastname,
                            (info + j)->country, (info + j)->dateOfBirth.day, (info + j)->dateOfBirth.month,
                            (info + j)->dateOfBirth.year, (info + j)->dateOfBirth.age, (info + j)->model,
                            (info + j)->category, (info + j)->points, (info + j)->timeOfLap.minutes,
                            (info + j)->timeOfLap.seconds);
                    _flushall();
                }
                fclose(file);
                printf("Участник успешно удалён!\n\n");
            } else printf("[Ошибка!]Удаление информации: Не удалось перезаписать файл! Файл отчищен!\n\n");
        } else printf("[Ошибка!]Удаление информации: Не удалось найти файл!\n\n");
    }
    system("pause");
    return info;
}

INFORMATION* memberEdit(INFORMATION* info) {
    time_t t = time(NULL);
    FILE *file = NULL;
    struct tm *aTm = localtime(&t);
    bool isMemberExist = false, isNumberExist = false, infoEditFlag = false;
    int number = 0, i = 0, j = 0, newNumber = 0, newBirthDay = 0, newBirthMonth = 0, newBirthYear = 0;
    char *firstname = NULL, *surname = NULL, *lastname = NULL, *country = NULL, *category = NULL, *model = NULL;
    if (info == NULL) {
        printf("[Ошибка!]Редактирование информации: Файл не открыт!\n\n");
        system("pause");
    }
    else if (infoLinesCounter == 0) {
        printf("[Ошибка!]Редактирование информации: Файл пуст!\n\n");
        system("pause");
    }
    else {
        displayAllMembers(info);
        do {
            number = checkToEnterOnlyInt(3,"Введите номер участника, которого нужно отредактировать: ");
            for (i = 0; i < infoLinesCounter; i++) {
                if ((info + i)->number == number) {
                    isMemberExist = true;
                    break;
                } else isMemberExist = false;
            }
            if (isMemberExist == false) printf("[Ошибка!]Участника с таким номером не существует!\n");
        } while (isMemberExist == false);
        while (infoEditFlag == false) {
            switch (memberEditMenu(info,i)) {
                case 1: {
                    printf("Изменеие номера участника.\n");
                    do {
                        do {
                            newNumber = checkToEnterOnlyInt(3,"Введите новый номер участника: ");
                            if (newNumber < 1)
                                printf("[Ошибка!]Введите число больше 0!\n");
                        } while (newNumber < 1);
                        for (j = 0; j < infoLinesCounter; j++) {
                            if ((info + j)->number == newNumber) {
                                isNumberExist = true;
                                break;
                            } else isNumberExist = false;
                        }
                        if (isNumberExist == true)
                            printf("[Ошибка!]Участник с таким номером уже существует!\n");
                    } while (isNumberExist == true);
                    (info + i)->number = newNumber;
                    displayEditableMember(info,i);
                    printf("Номер участника успешно изменен!\n\n");
                    system("pause");
                    break;
                }
                case 2: {
                    printf("Изменение имени участника.\n");
                    firstname = stringInputCheck(49, "Введите новое имя участника: ");
                    strcpy((info + i)->fullname.firstname, firstname);
                    free(firstname);
                    displayEditableMember(info,i);
                    printf("Имя участника успешно изменено!\n\n");
                    system("pause");
                    break;
                }
                case 3: {
                    printf("Изменение фамилии участника.\n");
                    surname = stringInputCheck(49, "Введите новую фамилию участника: ");
                    strcpy((info + i)->fullname.surname, surname);
                    free(surname);
                    displayEditableMember(info,i);
                    printf("Фамилия участника успешна изменена!\n\n");
                    system("pause");
                    break;
                }
                case 4: {
                    printf("Изменение отчества участника.\n");
                    lastname = stringInputCheck(49, "Введите новое отчество участника: ");
                    strcpy((info + i)->fullname.lastname, lastname);
                    free(lastname);
                    displayEditableMember(info,i);
                    printf("Отчество участника успешно изменено!\n\n");
                    system("pause");
                    break;
                }
                case 5: {
                    printf("Изменение страны участника.\n");
                    country = stringInputCheck(29, "Введите новую страну участника: ");
                    strcpy((info + i)->country, country);
                    free(country);
                    displayEditableMember(info,i);
                    printf("Страна участника успешно изменена.\n\n");
                    system("pause");
                    break;
                }
                case 6: {
                    printf("Изменение дня рождения участника.\n");
                    do {
                        newBirthDay = checkToEnterOnlyInt(2,"Введите новый день рождения участника: ");
                        scanf_s("%i", &newBirthDay);
                        if (newBirthDay < 1 || newBirthDay > 31)
                            printf("[Ошибка!]Введите число от 1 до 31!\n");
                    } while (newBirthDay < 1 || newBirthDay > 31);
                    (info + i)->dateOfBirth.day = newBirthDay;
                    displayEditableMember(info,i);
                    printf("День рождения участника успешно изменен!\n\n");
                    system("pause");
                    break;
                }
                case 7: {
                    printf("Изменение месяца рождения участника.\n");
                    do {
                        newBirthMonth = checkToEnterOnlyInt(2,"Введите новый месяц рождения участника(числом): ");
                        if (newBirthMonth < 1 || newBirthMonth > 12)
                            printf("[Ошибка!]Введите число от 1 до 12!\n\n");
                    } while (newBirthMonth < 1 || newBirthMonth > 12);
                    (info + i)->dateOfBirth.month = newBirthMonth;
                    displayEditableMember(info,i);
                    printf("Месяц рождения участника успешно изменен!\n\n");
                    system("pause");
                    break;
                }
                case 8: {
                    printf("Изменение года рождения участника.\n");
                    do {
                        newBirthYear = checkToEnterOnlyInt(4,"Введите новый год рождения участника: ");
                        if (newBirthYear < 1900 || newBirthYear > 2019)
                            printf("[Ошибка!]Введите число от 1900 до 2019!\n");
                    } while (newBirthYear < 1900 || newBirthYear > 2019);
                    (info + i)->dateOfBirth.year = newBirthYear;
                    if ((info + i)->dateOfBirth.month >= aTm->tm_mon + 1)
                        (info + i)->dateOfBirth.age = 2018 - (info + i)->dateOfBirth.year;
                    else
                        (info + i)->dateOfBirth.age = 2019 - (info + i)->dateOfBirth.year;
                    displayEditableMember(info,i);
                    printf("Год рождения участника успешно изменен!\n\n");
                    system("pause");
                    break;
                }
                case 9: {
                    printf("Изменение разряда участника.\n");
                    category = stringInputCheck(29, "Введите новый разряд участника: ");
                    strcpy((info + i)->category, category);
                    free(category);
                    displayEditableMember(info,i);
                    printf("Разряд участника успешно изменен!\n\n");
                    system("pause");
                    break;
                }
                case 10: {
                    printf("Изменение модели коньков участника.\n");
                    model = stringInputCheck(29, "Введите новую модель коньков участника: ");
                    strcpy((info + i)->model, model);
                    free(model);
                    displayEditableMember(info,i);
                    printf("Модель коньков участника успешно изменена!\n\n");
                    system("pause");
                    break;
                }
                case 11: {
                    printf("Изменение количества очков участника.\n");
                    do {
                        (info + i)->points = checkToEnterOnlyInt(4,"Введите новое количество очков участника: ");
                        if ((info + i)->points < 0 || (info + i)->points > 9999)
                            printf("[Ошибка!]Введите число от 0 до 9999!\n");
                    } while ((info + i)->points < 0 || (info + i)->points > 9999);
                    displayEditableMember(info,i);
                    printf("Количество очков участника успешно изменено!\n\n");
                    system("pause");
                    break;
                }
                case 12: {
                    printf("Изменение минут круга участника.\n");
                    do {
                        (info + i)->timeOfLap.minutes = checkToEnterOnlyInt(2,"Введите новые минуты круга участника: ");
                        if ((info + i)->timeOfLap.minutes < 0 ||
                            (info + i)->timeOfLap.minutes > 59)
                            printf("[Ошибка!]Введите число от 0 до 59!\n");
                    } while ((info + i)->timeOfLap.minutes < 0 ||
                             (info + i)->timeOfLap.minutes > 59);
                    displayEditableMember(info,i);
                    printf("Минуты круга участника успешно изменены!\n\n");
                    system("pause");
                    break;
                }
                case 13: {
                    printf("Изменение секунд круга участника.\n");
                    do {
                        (info + i)->timeOfLap.seconds = checkToEnterOnlyInt(2,"Введите новые секунды круга участника: ");
                        if ((info + i)->timeOfLap.seconds < 0 ||
                            (info + i)->timeOfLap.seconds > 59)
                            printf("[Ошибка!]Введите число от 0 до 59!\n");
                    } while ((info + i)->timeOfLap.seconds < 0 ||
                             (info + i)->timeOfLap.seconds > 59);
                    displayEditableMember(info,i);
                    printf("Секунды круга участника успешно изменены!\n\n");
                    system("pause");
                    break;
                }
                case 14:
                    infoEditFlag = true;
                    break;
                default:
                    break;
            }
            if (infoEditFlag == true) break;
        }
        if((checkFile("info.txt") != false)) {
            if ((file = fopen("info.txt", "w")) != NULL) {
                for (j = 0; j < infoLinesCounter; j++) {
                    fprintf(file, "%i %s %s %s %s %i %i %i %i %s %s %i %i %i\n", (info + j)->number,
                            (info + j)->fullname.firstname, (info + j)->fullname.surname, (info + j)->fullname.lastname,
                            (info + j)->country, (info + j)->dateOfBirth.day, (info + j)->dateOfBirth.month,
                            (info + j)->dateOfBirth.year, (info + j)->dateOfBirth.age, (info + j)->model,
                            (info + j)->category,
                            (info + j)->points, (info + j)->timeOfLap.minutes, (info + j)->timeOfLap.seconds);
                    _flushall();
                }
            } else printf("[Ошибка!]Редактирование информации: Не удалось перезаписать файл! Файл отчищен!\n");
        } else printf("[Ошибка!]Редактирование информации: Не удалось найти файл!\n");
    }
    return info;
}

void displayEditableMember(INFORMATION* info, int i){
    system("cls");
    printf("--------------------------------------------------------------------------------------------------------------------------------\n");
    printf("|НОМЕР|ИМЯ             ФАМИЛИЯ         ОТЧЕСТВО       |  СТРАНА  |ДАТА  РОЖДЕНИЯ|ВОЗРАСТ|  РАЗРЯД  |  МОДЕЛЬ  |ОЧКИ|ВРЕМЯ КРУГА|\n");
    printf("--------------------------------------------------------------------------------------------------------------------------------\n");
    printf("|%-3i  |%-15s %-15s %-15s|%-10s|  %02i/%02i/%04i  |  %-3i  |%-10s|%-10s|%-4i|   %02i:%02i   |\n",
           (info + i)->number, (info + i)->fullname.firstname, (info + i)->fullname.surname,
           (info + i)->fullname.lastname, (info + i)->country,
           (info + i)->dateOfBirth.day, (info + i)->dateOfBirth.month, (info + i)->dateOfBirth.year,
           (info + i)->dateOfBirth.age, (info + i)->category,
           (info + i)->model, (info + i)->points, (info + i)->timeOfLap.minutes, (info + i)->timeOfLap.seconds);
    printf("--------------------------------------------------------------------------------------------------------------------------------\n");
}

void displayAllMembers(INFORMATION* info) {
    if (info == NULL)
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
void pointsFilter(INFORMATION* info) {
    int points = 0;
    bool isAtLeastOneMember = false;
    if (info == NULL)
        printf("[Ошибка!]Поиск и фильтрация: Файл не открыт!\n\n");
    else if (infoLinesCounter == 0)
        printf("[Ошибка!]Поиск и фильтрация: Файл пуст!\n\n");
    else {
        do {
            points = checkToEnterOnlyInt(4,"Введите количество очков: ");
            if (points < 0 || points > 9999)
                printf("[Ошибка!]Введите число больше 0 и меньше 9999!\n");
        } while (points < 0 || points > 9999);
        system("cls");
        printf("Участники, у которых очков больше %i: ", points);
        for (int i = 0; i < infoLinesCounter; i++) {
            if ((info + i)->points > points) {
                if (isAtLeastOneMember == false) {
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
            if (isAtLeastOneMember == true && i == infoLinesCounter - 1)
                printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
        }
        if (isAtLeastOneMember == false)
            printf("[Ошибка!]Нет ни одного участника с очками больше %i.\n\n", points);
    }
    system("pause");
}

void timeOfLapFilter(INFORMATION* info) {
    int minutesOfLap = 0, secondsOfLap = 0;
    bool isAtLeastOneMember = false;
    if (info == NULL) {
        printf("[Ошибка!]Поиск и фильтрация: Файл не открыт!\n\n");
    } else if (infoLinesCounter == 0) {
        printf("[Ошибка!]Поиск и фильтрация: Файл пуст!\n\n");
    } else {
        do {
            minutesOfLap = checkToEnterOnlyInt(2,"Введите количество минут круга: ");
            if (minutesOfLap < 0 || minutesOfLap > 59)
                printf("[Ошибка!]Введите число больше 0 и меньше 59!\n");
        } while (minutesOfLap < 0 || minutesOfLap > 59);
        do {
            secondsOfLap = checkToEnterOnlyInt(2,"Введите количество секунд круга: ");
            if (secondsOfLap < 0 || secondsOfLap > 59)
                printf("[Ошибка!]Введите число больше 0 и меньше 59!\n");
        } while (secondsOfLap < 0 || secondsOfLap > 59);
        system("cls");
        printf("Участники, у которых время круга меньше %02i:%02i : ", minutesOfLap, secondsOfLap);
        for (int i = 0; i < infoLinesCounter; i++) {
            if ((info + i)->timeOfLap.minutes < minutesOfLap)
                if ((info + i)->timeOfLap.seconds <
                    ((info + i)->timeOfLap.minutes == minutesOfLap ? secondsOfLap : 60)) {
                    if (isAtLeastOneMember == false) {
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
            if (isAtLeastOneMember == true && i == infoLinesCounter - 1)
                printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
        }
        if (isAtLeastOneMember == false)
            printf("[Ошибка!]Нет ни одного участника с временем круга меньше %02i:%02i.\n\n", minutesOfLap,
                   secondsOfLap);
    }
    system("pause");
}

void ageFilter(INFORMATION* info) {
    int age = 0;
    bool isAtLeastOneMember = false;
    if (info == NULL)
        printf("[Ошибка!]Поиск и фильтрация: Файл не открыт!\n\n");
    else if (infoLinesCounter == 0)
        printf("[Ошибка!]Поиск и фильтрация: Файл пуст!\n\n");
    else {
        do {
            age = checkToEnterOnlyInt(3,"Введите возраст: ");
            if (age < 0 || age > 119)
                printf("[Ошибка!]Введите число больше 0 и меньше 119!\n");
        } while (age < 0 || age > 119);
        system("cls");
        printf("Участники, возраст которых больше %i: ", age);
        for (int i = 0; i < infoLinesCounter; i++) {
            if ((info + i)->dateOfBirth.age > age) {
                if (isAtLeastOneMember == false) {
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
            if (isAtLeastOneMember == true && i == infoLinesCounter - 1)
                printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
        }
        if (isAtLeastOneMember == false)
            printf("[Ошибка!]Нет ни одного участника с очками больше %i.\n\n", age);
    }
    system("pause");
}

void yearOfBirthFilter(INFORMATION* info) {
    int yearOfBirth = 0;
    bool isAtLeastOneMember = false;
    if (info == NULL)
        printf("[Ошибка!]Поиск и фильтрация: Файл не открыт!\n\n");
    else if (infoLinesCounter == 0)
        printf("[Ошибка!]Поиск и фильтрация: Файл пуст!\n\n");
    else {
        do {
            yearOfBirth = checkToEnterOnlyInt(4,"Введите год рождения: ");
            if (yearOfBirth < 1900 || yearOfBirth > 2019)
                printf("[Ошибка!]Введите число больше 1900 и меньше 2019!\n");
        } while (yearOfBirth < 1900 || yearOfBirth > 2019);
        system("cls");
        printf("Участники, год рождения у которых больше %i: ", yearOfBirth);
        for (int i = 0; i < infoLinesCounter; i++) {
            if ((info + i)->dateOfBirth.year > yearOfBirth) {
                if (isAtLeastOneMember == false) {
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
            if (isAtLeastOneMember == true && i == infoLinesCounter - 1) {
                printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
            }
        }
        if (isAtLeastOneMember == false)
            printf("[Ошибка!]Нет ни одного участника с годом рождения больше %i.\n\n", yearOfBirth);
    }
    system("pause");
}

void timeOfLapSorting(INFORMATION* info){
    FILE* file = NULL;
    INFORMATION tmp;
    if (info == NULL)
        printf("[Ошибка!]Сортировка: Файл не открыт!\n\n");
    else if (infoLinesCounter == 0)
        printf("[Ошибка!]Сортировка: Файл пуст!\n\n");
    else {
        if ((file = fopen("info.txt", "w")) != NULL) {
            for (int i = 1; i < infoLinesCounter; i++)
                for (int j = i; j > 0; j--)
                    if ((info + (j - 1))->timeOfLap.minutes == (info + j)->timeOfLap.minutes) {
                        if ((info + (j - 1))->timeOfLap.seconds > (info + j)->timeOfLap.seconds) {
                            tmp = *(info + (j - 1));
                            *(info + (j - 1)) = *(info + j);
                            *(info + j) = tmp;
                        }
                    } else if ((info + (j - 1))->timeOfLap.minutes > (info + j)->timeOfLap.minutes) {
                        tmp = *(info + (j - 1));
                        *(info + (j - 1)) = *(info + j);
                        *(info + j) = tmp;
                    }
            for (int j = 0; j < infoLinesCounter; j++) {
                fprintf(file, "%i %s %s %s %s %i %i %i %i %s %s %i %i %i\n", (info + j)->number,
                        (info + j)->fullname.firstname, (info + j)->fullname.surname, (info + j)->fullname.lastname,
                        (info + j)->country, (info + j)->dateOfBirth.day, (info + j)->dateOfBirth.month,
                        (info + j)->dateOfBirth.year, (info + j)->dateOfBirth.age, (info + j)->category,
                        (info + j)->model, (info + j)->points, (info + j)->timeOfLap.minutes,
                        (info + j)->timeOfLap.seconds);
                _flushall();
            }
            fclose(file);
            printf("Сортировка: Участники успешно отсортированы!\n\n");
        } else printf("[Ошибка!]Сортировка: Не удалось открыть файл! Файл отчищен!\n\n");
    }
    system("pause");
}

void numberSearch(INFORMATION* info) {
    int number = 0;
    bool isFounded = false;
    if (info == NULL)
        printf("[Ошибка!]Поиск и фильтрация: Файл не открыт!\n\n");
    else if (infoLinesCounter == 0)
        printf("[Ошибка!]Поиск и фильтрация: Файл пуст!\n\n");
    else {
        do {
            number = checkToEnterOnlyInt(3,"Введите номер: ");
            if (number < 0)
                printf("[Ошибка!]Введите число больше 0!\n");
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
        if (isFounded == false)
            printf("[Ошибка!]Нету участника с номером %i.\n\n", number);
    }
    system("pause");
}

void surnameSearch(INFORMATION* info) {
    bool isAtLeastOneMember = false;
    char *surname = NULL;
    if (info == NULL)
        printf("[Ошибка!]Поиск и фильтрация: Файл не открыт!\n\n");
    else if (infoLinesCounter == 0)
        printf("[Ошибка!]Поиск и фильтрация: Файл пуст!\n\n");
    else {
        surname = stringInputCheck(49, "Введите фамилию: ");
        system("cls");
        printf("Участники, с фамилией %s: ", surname);
        for (int i = 0; i < infoLinesCounter; i++) {
            if (strcmp((info + i)->fullname.surname, surname) == 0) {
                if (isAtLeastOneMember == false) {
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
            if (isAtLeastOneMember == true && i == infoLinesCounter - 1)
                printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
        }
        if (isAtLeastOneMember == false)
            printf("[Ошибка!]Нет ни одного участника с фамилией %s.\n\n", surname);
    }
    system("pause");
}

void countrySearch(INFORMATION* info){
    bool isAtLeastOneMember = false;
    char *country = NULL;
    if (info == NULL)
        printf("[Ошибка!]Поиск и фильтрация: Файл не открыт!\n\n");
    else if (infoLinesCounter == 0)
        printf("[Ошибка!]Поиск и фильтрация: Файл пуст!\n\n");
    else {
        country = stringInputCheck(49, "Введите страну: ");
        system("cls");
        printf("Участники, из страны %s: ", country);
        for (int i = 0; i < infoLinesCounter; i++) {
            if (strcmp((info + i)->country,country) == 0) {
                if (isAtLeastOneMember == false) {
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
            if (isAtLeastOneMember == true && i == infoLinesCounter - 1)
                printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
        }
        if (isAtLeastOneMember == false)
            printf("[Ошибка!]Нет ни одного участника из страны %s.\n\n", country);
    }
    system("pause");
}

void categorySearch(INFORMATION* info){
    bool isAtLeastOneMember = false;
    char *category = NULL;
    if (info == NULL)
        printf("[Ошибка!]Поиск и фильтрация: Файл не открыт!\n\n");
    else if (infoLinesCounter == 0)
        printf("[Ошибка!]Поиск и фильтрация: Файл пуст!\n\n");
    else {
        category = stringInputCheck(49, "Введите разряд: ");
        system("cls");
        printf("Участники, с разрядом %s: ", category);
        for (int i = 0; i < infoLinesCounter; i++) {
            if (strcmp((info + i)->category,category) == 0) {
                if (isAtLeastOneMember == false) {
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
            if (isAtLeastOneMember == true && i == infoLinesCounter - 1)
                printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
        }
        if (isAtLeastOneMember == false)
            printf("[Ошибка!]Нет ни одного участника с разрядом %s.\n\n", category);
    }
    system("pause");
}

void displayTopMembers(INFORMATION* info){
    INFORMATION *infoCopy = NULL, tmp;
    system("cls");
    if (info == NULL)
        printf("[Ошибка!]Поиск и фильтрация: Файл не открыт!\n\n");
    else if (infoLinesCounter == 0)
        printf("[Ошибка!]Поиск и фильтрация: Файл пуст!\n\n");
    else {
        infoCopy = (INFORMATION*)realloc(NULL,sizeof(INFORMATION)*infoLinesCounter);
        memcpy(infoCopy,info,sizeof(INFORMATION)*infoLinesCounter);
        if (infoLinesCounter != 1){
            for(int i = 1;i < infoLinesCounter; i++)
                for(int j = i; j > 0; j--)
                    if((infoCopy + (j-1))->timeOfLap.minutes == (infoCopy + j)->timeOfLap.minutes){
                        if((infoCopy + (j-1))->timeOfLap.seconds > (infoCopy + j)->timeOfLap.seconds){
                            tmp = *(infoCopy + (j - 1));
                            *(infoCopy + (j - 1)) = *(infoCopy + j);
                            *(infoCopy + j) = tmp;
                        }
                    } else if ((infoCopy + (j-1))->timeOfLap.minutes > (infoCopy + j)->timeOfLap.minutes){
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
    system("pause");
}