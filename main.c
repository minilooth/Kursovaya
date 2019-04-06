#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>


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


int menu();
int inputCheck(const char *inputText);
int adminSubmenu();
int userSubmenu();
int adminLogin(USER* user);
int userLogin(USER* user);
int countLines(const char* filename);
int userManagement();
USER* userLoad(USER* user);
USER* userAdd(USER* user);
USER* userDelete(USER* user);
USER* userEdit(USER* user);
void userPrint(USER* user);
INFORMATION* infoOpen(INFORMATION* info);
INFORMATION* infoAdd(INFORMATION* info);
INFORMATION* infoEdit(INFORMATION* info);
INFORMATION* infoDelete(INFORMATION *info);
int infoPrint(INFORMATION* info);
char* limitedStringInput(char* input, int limit);
int infoCheckFile();
void infoCreateFile();
int searchAndFilteringMenu();
int pointsFilter(INFORMATION* info);
int timeOfLapFilter(INFORMATION* info);
int ageFilter(INFORMATION* info);
int yearOfBirthFilter(INFORMATION* info);


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    INFORMATION *info = NULL;
    USER *user = NULL;
    user = userLoad(user);
    int adminSubMenuFlag = 0, userManagementFlag = 0, userSubMenuFlag = 0, searchAndFilteringFlag = 0;
    if (user == NULL) {
        system("pause");
        return 0;
    }
    while (1) {
        switch (menu()) {
            case 1: {
                if (adminLogin(user) == 1) {
                    while (adminSubMenuFlag == 0) {
                        switch (adminSubmenu()) {
                            case 1: {
                                if (info == NULL) {
                                    if (infoCheckFile() == 0)
                                        infoCreateFile();
                                    info = infoOpen(info);
                                    printf("Открытие информации: Файл успешно открыт!\n\n");
                                }
                                else printf("[Ошибка!]Открытие информации: Файл уже открыт!\n\n");
                                break;
                            }
                            case 2: info = infoAdd(info); break;
                            case 3: info = infoEdit(info); break;
                            case 4: info = infoDelete(info); break;
                            case 5: infoPrint(info); break;
                            case 6: {
                                while (searchAndFilteringFlag == 0) {
                                    switch (searchAndFilteringMenu()) {
                                        case 1: pointsFilter(info); break;
                                        case 2: timeOfLapFilter(info); break;
                                        case 3: ageFilter(info); break;
                                        case 4: yearOfBirthFilter(info); break;
                                        case 5: break;
                                        case 6: break;
                                        case 7: break;
                                        case 8: break;
                                        case 9: break;
                                        case 10: searchAndFilteringFlag = 1; break;
                                        default: break;
                                    }
                                    if (searchAndFilteringFlag == 1) break;
                                }
                                searchAndFilteringFlag = 0;
                                break;
                            }
                            case 7: {
                                while (userManagementFlag == 0) {
                                    switch (userManagement()) {
                                        case 1: user = userAdd(user); break;
                                        case 2: user = userDelete(user); break;
                                        case 3: user = userEdit(user); break;
                                        case 4: userPrint(user); break;
                                        case 5: userManagementFlag = 1; break;
                                        default: break;
                                    }
                                    if (userManagementFlag == 1) break;
                                }
                                userManagementFlag = 0;
                                break;
                            }
                            case 8: free(info); adminSubMenuFlag = 1; break;
                            default: break;
                        }
                        if (adminSubMenuFlag == 1) break;
                    }
                    adminSubMenuFlag = 0;
                }
                break;
            }
            case 2: {
                if (userLogin(user) == 1) {
                    while (userSubMenuFlag == 0) {
                        switch (userSubmenu()) {
                            case 1: {
                                if (infoCheckFile() == 1) {
                                    info = infoOpen(info);
                                    printf("Открытие информации: Файл успешно открыт!\n\n");
                                }
                                else printf("[Ошибка!]Открытие информации: Файл ещё не создан!\n\n");
                                break;
                            }
                            case 2: infoPrint(info); break;
                            case 3: break;
                            case 4: break;
                            case 5: free(info); userSubMenuFlag = 1; break;
                            default: break;
                        }
                        if (userSubMenuFlag == 1) break;
                    }
                    userSubMenuFlag = 0;
                }
                break;
            }
            case 3: free(user); return 0;
            default: break;
        }
    }
}

int menu() {
    int choice;
    printf("Меню: \n");
    printf("1.Вход под администратором.\n");
    printf("2.Вход под пользователем.\n");
    printf("3.Выход.\n");
    printf("Ваш выбор: ");
    choice = inputCheck("Ваш выбор: ");
    printf("\n");
    return choice;
}

int adminSubmenu() {
    int choice;
    printf("Подменю(для администраторов):\n");
    printf("1.Создание/открытие файла.\n");
    printf("2.Добавление записи.\n");
    printf("3.Редактирование записи.\n");
    printf("4.Удаление записи.\n");
    printf("5.Просмотр всех данных в табличной форме.\n");
    printf("6.Различные процедуры поиска и фильтрации данных.\n");
    printf("7.Управление пользователями.\n");
    printf("8.Выход в меню.\n");
    printf("Ваш выбор: ");
    choice = inputCheck("Ваш выбор: ");
    printf("\n");
    return choice;
};

int userSubmenu() {
    int choice;
    printf("Подменю(для пользователей):\n");
    printf("1.Открытие файла с данными.\n");
    printf("2.Просмотр всех данных в табличной форме.\n");
    printf("3.Выполнение задачи.\n");
    printf("4.Различные процедуры поиска и фильтрации данных.\n");
    printf("5.Выход в меню.\n");
    printf("Ваш выбор: ");
    choice = inputCheck("Ваш выбор: ");
    printf("\n");
    return choice;
};

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

int adminLogin(USER *user) {
    int isLoginRight = 0, isPasswordRight = 0, i = 0, j = 0, counter = 0;
    char *login = NULL, password[30], ch;
    do {
        printf("Введите логин: ");
        login = limitedStringInput(login, 29);
        for (i = 0; i < usersLinesCounter; i++)
            if (strcmp(login, (user + i)->login) == 0) {
                isLoginRight = 1;
                break;
            }
        if (isLoginRight == 0) {
            printf("[Ошибка!]Такого администратора не существует!\n\n");
            return 0;
        }
    } while (isLoginRight != 1);
    do {
        j = 0;
        printf("Введите пароль: ");
        while (1) {
            ch = (char)_getch();
            if (ch != '\0') {
                if (ch == 13 || ch == 9) {
                    counter++;
                    password[j] = '\0';
                    break;
                }
                else if (ch == 8 && j > 0) {
                    j--;
                    printf("\b \b");
                }
                else if (ch == 8 && j == 0) {
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
            isPasswordRight = 1;
        else printf("\n[Ошибка!]Неверный пароль!\n");
    } while (isPasswordRight != 1);
    if ((user + i)->isAdmin == 1) {
        printf("\nВы успешно авторизовались.\n\n");
        free(login);
        return 1;
    }
    else {
        printf("\n[Ошибка!]Авторизация: Войдите через пользователя!\n\n");
        free(login);
        return 0;
    }
}

int userLogin(USER *user) {
    int isLoginRight = 0, isPasswordRight = 0, i = 0, j = 0, counter = 0;
    char *login = NULL, password[30], ch;
    do {
        printf("Введите логин: ");
        login = limitedStringInput(login, 29);
        for (i = 0; i < usersLinesCounter; i++)
            if (strcmp(login, (user + i)->login) == 0) {
                isLoginRight = 1;
                break;
            }
        if (isLoginRight == 0) {
            printf("[Ошибка!]Такого пользователя не существует!\n\n");
            free(login);
            return 0;
        }
    } while (isLoginRight != 1);
    do {
        j = 0;
        printf("Введите пароль: ");
        while (1) {
            ch = (char)_getch();
            if (ch != '\0') {
                if (ch == 13 || ch == 9) {
                    password[j] = '\0';
                    break;
                }
                else if (ch == 8 && j > 0) {
                    j--;
                    printf("\b \b");
                }
                else if (ch == 8 && j == 0) {
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
            isPasswordRight = 1;
        else printf("\n[Ошибка!]Неверный пароль!\n");
    } while (isPasswordRight != 1);
    if ((user + i)->isAdmin == 0) {
        printf("\nВы успешно авторизовались.\n\n");
        free(login);
        return 1;
    }
    else {
        printf("\n[Ошибка!]Авторизация! Войдите через администратора!\n\n");
        free(login);
        return 0;
    }
}

int userManagement() {
    int choice;
    printf("Управление пользователями:\n");
    printf("1.Добавить аккаунт.\n");
    printf("2.Удалить аккаунт.\n");
    printf("3.Редактировать аккаунт.\n");
    printf("4.Просмотр всех аккаунтов.\n");
    printf("5.Назад.\n");
    printf("Ваш выбор: ");
    choice = inputCheck("Ваш выбор: ");
    printf("\n");
    return choice;
}

USER* userLoad(USER* user) {
    FILE* file = NULL;
    usersLinesCounter = countLines("db.txt") - 1;
    if ((file = fopen("db.txt", "r")) == NULL) {
        if ((file = fopen("db.txt", "w")) != NULL){
            fprintf(file, "%s %s %i\n", "admin", "admin", 1);
            fclose(file);
            user = userLoad(user);
            return user;
        } else {
            printf("[Ошибка!]Инициальзация пользователей: Не удалось создать файл с логинами/паролями!\n");
            system("pause");
            exit(0);
        }
    }
    if (usersLinesCounter != 0) {
        user = (USER*)malloc(usersLinesCounter*(sizeof(USER)));
        for (int i = 0; i < usersLinesCounter; i++)
            fscanf(file, "%s %s %i", (user + i)->login, (user + i)->password, &((user + i)->isAdmin));
        fclose(file);
        return user;
    }
    else {
        printf("[Ошибка!]Инициализация пользователей: Файл с логинами/паролями пуст!\n\n");
        return NULL;
    }
}

USER* userAdd(USER* user) {
    user = (USER*)realloc(user, (usersLinesCounter + 1) * sizeof(USER));
    int loginIsNotExist = 0, i = 0;
    char *login = NULL, *password = NULL;
    FILE* file = NULL;
    printf("Добавить пользователя:\n");
    do {
        loginIsNotExist = 0;
        printf("Введите логин: ");
        login = limitedStringInput(login, 29);
        strcpy((user + usersLinesCounter)->login, login);
        for (i = 0; i < usersLinesCounter; i++) {
            if (strcmp((user + i)->login, (user + usersLinesCounter)->login) == 0) {
                printf("[Ошибка!]Этот аккаунт уже существует!\n");
                loginIsNotExist = 0;
                break;
            }
            else loginIsNotExist = 1;
        }
    } while ((loginIsNotExist != 1));
    free(login);
    printf("Введите пароль: ");
    password = limitedStringInput(password, 29);
    strcpy((user + usersLinesCounter)->password, password);
    free(password);
    do {
        printf("Администратор?(1 - Да|0 - Нет): ");
        (user + usersLinesCounter)->isAdmin = inputCheck("Администратор?(1 - Да|0 - Нет): ");
        if ((user + usersLinesCounter)->isAdmin < 0 || (user + usersLinesCounter)->isAdmin > 1) {
            printf("[Ошибка!]Не правильный ввод!\n");
        }
    } while ((user + usersLinesCounter)->isAdmin < 0 || (user + usersLinesCounter)->isAdmin > 1);
    if ((file = fopen("db.txt", "at+")) == NULL) {
        printf("[Ошибка!]Добавление пользователей: Ошибка открытия файла с логинами/паролями! Пользователь не добавлен!\n\n");
        free(login);
        free(password);
        return user;
    }
    fprintf(file, "%s %s %i\n", (user + usersLinesCounter)->login, (user + usersLinesCounter)->password, (user + usersLinesCounter)->isAdmin);
    fclose(file);
    printf("Аккаунт успешно добавлен!\n\n");
    _flushall();
    usersLinesCounter++;
    return user;
}

void userPrint(USER* user) {
    char yes[] = "Да", no[] = "Нет";
    printf("===============================================================================================\n");
    printf("|№    |ЛОГИН:                         |ПАРОЛЬ:                         |ПРАВА АДМИНИСТРАТОРА: |\n");
    printf("===============================================================================================\n");
    for (int i = 0; i < usersLinesCounter; i++) {
        printf("|%-5i|%-31s|%-32s|", i + 1, (user + i)->login, (user + i)->password);
        if ((user + i)->isAdmin == 1)
            printf("%-22s|", yes);
        else printf("%-22s|", no);
        printf("\n");
    }
    printf("===============================================================================================\n\n");
}

USER* userDelete(USER* user) {
    char *login = NULL;
    int i = 0, loginIsExist = 0;
    FILE* file = NULL;
    printf("Удаление аккаунта.\n");
    do {
        printf("Введите логин аккаунта, который вы хотите удалить: ");
        login = limitedStringInput(login, 29);
        for (i = 0; i < usersLinesCounter; i++) {
            if (strcmp((user + i)->login, login) == 0) {
                loginIsExist = 1;
                break;
            }
        }
        if (loginIsExist == 0)
            printf("[Ошибка!]Такого аккаунта не существует!\n");
    } while (loginIsExist != 1);
    free(login);
    if ((file = fopen("db.txt", "w")) == NULL) {
        printf("[Ошибка!]Удаление пользователей: Ошибка открытия файла с логинами/паролями! Пользователь не удален! Файл отчищен!\n\n");
        free(login);
        return user;
    }
    for (int j = 0; j < usersLinesCounter; j++)
        if (j != i)
            fprintf(file, "%s %s %i\n", (user + j)->login, (user + j)->password, (user + j)->isAdmin);
    printf("Аккаунт успешно удалён!\n\n");
    fclose(file);
    usersLinesCounter--;
    free(user);
    user = userLoad(user);
    return user;
}

USER* userEdit(USER* user) {
    char *login = NULL, *newLogin = NULL, *newPassword = NULL, yes[] = "Да", no[] = "Нет";
    int i = 0, loginIsExist = 0, isNewLoginNotExist = 0, choice = 0, editFlag = 0;
    FILE* file = NULL;
    do {
        loginIsExist = 0;
        printf("Введите логин аккаунта, который вы хотите отредактировать: ");
        login = limitedStringInput(login, 29);
        for (i = 0; i < usersLinesCounter; i++) {
            if (strcmp((user + i)->login, login) == 0) {
                loginIsExist = 1;
                break;
            }
        }
        if (loginIsExist == 0)
            printf("[Ошибка!]Такого аккаунта не существует!\n");
    } while (loginIsExist != 1);
    free(login);
    printf("=========================================================================================\n");
    printf("|ЛОГИН:                         |ПАРОЛЬ:                         |ПРАВА АДМИНИСТРАТОРА: |\n");
    printf("=========================================================================================\n");
    printf("|%-31s|%-32s|", (user + i)->login, (user + i)->password);
    if ((user + i)->isAdmin == 1)
        printf("%-22s|", yes);
    else printf("%-22s|", no);
    printf("\n=========================================================================================\n\n");
    while (editFlag == 0) {
        printf("Что отредактировать?\n");
        printf("1.Логин.\n");
        printf("2.Пароль.\n");
        printf("3.Права администратора.\n");
        printf("4.Назад.\n");
        printf("Ваш выбор: ");
        choice = inputCheck("Ваш выбор: ");
        printf("\n");
        switch (choice) {
            case 1: {
                printf("Изменить логин.\n");
                do {
                    printf("Введите новый логин: ");
                    newLogin = limitedStringInput(newLogin, 29);
                    for (int j = 0; j < usersLinesCounter; j++) {
                        if (strcmp((user + j)->login, newLogin) == 0) {
                            isNewLoginNotExist = 0;
                            break;
                        }
                        else isNewLoginNotExist = 1;
                    }
                    if (isNewLoginNotExist == 0)
                        printf("[Ошибка!]Такой логин уже существует!\n");
                } while (isNewLoginNotExist == 0);
                strcpy((user + i)->login, newLogin);
                printf("Логин успешно изменен!\n\n");
                free(newLogin);
                break;
            }
            case 2: {
                printf("Изменение пароля.\n");
                printf("Введите новый пароль: ");
                newPassword = limitedStringInput(newPassword, 29);
                strcpy((user + i)->password, newPassword);
                printf("Пароль успешно изменен!\n\n");
                free(newPassword);
                break;
            }
            case 3: {
                if ((user + i)->isAdmin == 1) {
                    (user + i)->isAdmin = 0;
                    printf("Права администратора успешно изменены.\n\n");
                    break;
                }
                else {
                    (user + i)->isAdmin = 1;
                    printf("Права администратора успешно изменены.\n\n");
                    break;
                }
            }
            case 4: editFlag = 1; break;
            default: break;
        }
        if (editFlag == 1) break;
    }
    if ((file = fopen("db.txt", "w")) == NULL) {
        printf("[Ошибка!]Редактирование пользователей: Не удалось открыть файл с логинами/паролями! Пользователь не отредактирован! Файл отчищен!\n\n");
        return user;
    }
    for (i = 0; i < usersLinesCounter; i++)
        fprintf(file, "%s %s %i\n", (user + i)->login, (user + i)->password, (user + i)->isAdmin);
    fclose(file);
    return user;
}

int infoCheckFile() {
    FILE* file = NULL;
    if ((file = fopen("info.txt", "rt+")) == NULL)
        return 0;
    else {
        fclose(file);
        return 1;
    }
}

void infoCreateFile() {
    FILE* file = NULL;
    if ((file = fopen("info.txt", "rt+")) == NULL)
        printf("Открытие информации: Файл не существует! Создаю файл...\n");
    if (!file)
        if ((file = fopen("info.txt", "wt+")) != NULL)
            printf("Открытие информации: Файл успешно создан!\n");
    fclose(file);
}

INFORMATION* infoOpen(INFORMATION* info) {
    FILE* file = NULL;
    if ((file = fopen("info.txt", "rt+")) != NULL) {
        infoLinesCounter = countLines("info.txt") - 1;
        if (infoLinesCounter != -1) {
            info = (INFORMATION*)malloc(infoLinesCounter * sizeof(INFORMATION));
            for (int i = 0; i < infoLinesCounter; i++) {
                fscanf(file, "%i %s %s %s %s %i %i %i %i %s %s %i %i %i", &((info + i)->number), (info + i)->fullname.firstname, (info + i)->fullname.surname, (info + i)->fullname.lastname, (info + i)->country, &((info + i)->dateOfBirth.day), &((info + i)->dateOfBirth.month), &((info + i)->dateOfBirth.year), &((info + i)->dateOfBirth.age), (info + i)->category, (info + i)->model, &((info + i)->points), &((info + i)->timeOfLap.minutes), &((info + i)->timeOfLap.seconds));
            }
        }
        fclose(file);
    }
    return info;
}

int infoPrint(INFORMATION* info) {
    if (info == NULL) {
        printf("[Ошибка!]Вывод информации: Файл пуст!\n\n");
        return 0;
    }
    if (infoLinesCounter != 0) {
        printf("================================================================================================================================\n");
        printf("|НОМЕР|ИМЯ             ФАМИЛИЯ         ОТЧЕСТВО       |  СТРАНА  |ДАТА  РОЖДЕНИЯ|ВОЗРАСТ|  РАЗРЯД  |  МОДЕЛЬ  |ОЧКИ|ВРЕМЯ КРУГА|\n");
        printf("================================================================================================================================\n");
        for (int i = 0; i < infoLinesCounter; i++) {
            printf("|%-3i  |%-15s %-15s %-15s|%-10s|  %-2i/%02i/%-4i  |  %-3i  |%-10s|%-10s|%-4i|   %02i:%02i   |", (info + i)->number, (info + i)->fullname.firstname, (info + i)->fullname.surname, (info + i)->fullname.lastname, (info + i)->country, (info + i)->dateOfBirth.day, (info + i)->dateOfBirth.month, (info + i)->dateOfBirth.year, (info + i)->dateOfBirth.age, (info + i)->model, (info + i)->category, (info + i)->points, (info + i)->timeOfLap.minutes, (info + i)->timeOfLap.seconds);
            printf("\n");
        }
        printf("================================================================================================================================\n\n");
        return 0;
    }
    else {
        printf("[Ошибка!]Вывод информации: Файл пуст!\n\n");
        return 0;
    };
}

INFORMATION* infoAdd(INFORMATION* info) {
    if (info == NULL) {
        printf("[Ошибка!]Добавление информации: Файл не открыт!\n\n");
        return NULL;
    }
    time_t t = time(NULL);
    struct tm* aTm = localtime(&t);
    int isExist = 0;
    char *firstname = NULL, *surname = NULL, *lastname = NULL, *country = NULL, *category = NULL, *model = NULL;
    FILE *file = NULL;
    if ((file = fopen("info.txt", "a+")) == NULL) {
        printf("[Ошибка!]Добавление информации: Не удалось открыть файл для добавления!\n");
        return info;
    }
    if (infoLinesCounter != -1)
        info = (INFORMATION*)realloc(info, ((infoLinesCounter + 1) * sizeof(INFORMATION)));
    else {
        printf("[Ошибка!]Добавление информации: Не удалось открыть файл(файл не существует)!\n\n");
        return info;
    }
    printf("Добавление участника.\n");
    do {
        printf("Введите номер участника: ");
        do {
            (info + infoLinesCounter)->number = inputCheck("Введите номер участника: ");
            if ((info + infoLinesCounter)->number < 1)
                printf("[Ошибка!]Введите число больше 0!\n");
        } while ((info + infoLinesCounter)->number < 1);
        for (int i = 0; i < infoLinesCounter; i++) {
            if ((info + i)->number == (info + infoLinesCounter)->number) {
                isExist = 1;
                break;
            }
            else isExist = 0;
        }
        if (isExist == 1) printf("Участник с таким номером уже существует!\n");
    } while (isExist == 1);
    printf("Введите имя участника: ");
    firstname = limitedStringInput(firstname, 49);
    strcpy((info + infoLinesCounter)->fullname.firstname, firstname);
    free(firstname);
    printf("Введите фамилию участника: ");
    surname = limitedStringInput(surname, 49);
    strcpy((info + infoLinesCounter)->fullname.surname, surname);
    free(surname);
    printf("Введите отчество участника: ");
    lastname = limitedStringInput(lastname, 49);
    strcpy((info + infoLinesCounter)->fullname.lastname, lastname);
    free(lastname);
    printf("Введите страну учатника: ");
    country = limitedStringInput(country, 29);
    strcpy((info + infoLinesCounter)->country, country);
    free(country);
    do {
        printf("Введите день рождения участника: ");
        (info + infoLinesCounter)->dateOfBirth.day = inputCheck("Введите день рождения участника: ");
        if ((info + infoLinesCounter)->dateOfBirth.day < 1 || (info + infoLinesCounter)->dateOfBirth.day > 31)
            printf("[Ошибка!]Введите число от 1 до 31!\n");
    } while ((info + infoLinesCounter)->dateOfBirth.day < 1 || (info + infoLinesCounter)->dateOfBirth.day > 31);
    do {
        printf("Введите месяц рождения участника(числом): ");
        (info + infoLinesCounter)->dateOfBirth.month = inputCheck("Введите месяц рождения участника(числом): ");
        if ((info + infoLinesCounter)->dateOfBirth.month < 1 || (info + infoLinesCounter)->dateOfBirth.month > 12)
            printf("[Ошибка!]Введите число от 1 до 12!\n");
    } while ((info + infoLinesCounter)->dateOfBirth.month < 1 || (info + infoLinesCounter)->dateOfBirth.month > 12);
    do {
        printf("Введите год рождения участника: ");
        (info + infoLinesCounter)->dateOfBirth.year = inputCheck("Введите год рождения участника: ");
        if ((info + infoLinesCounter)->dateOfBirth.year < 1900 || (info + infoLinesCounter)->dateOfBirth.year > 2019)
            printf("[Ошибка!]Введите число от 1900 до 2019!\n");
    } while ((info + infoLinesCounter)->dateOfBirth.year < 1900 || (info + infoLinesCounter)->dateOfBirth.year > 2019);
    if ((info + infoLinesCounter)->dateOfBirth.month > aTm->tm_mon + 1)
        (info + infoLinesCounter)->dateOfBirth.age = 2018 - (info + infoLinesCounter)->dateOfBirth.year;
    else (info + infoLinesCounter)->dateOfBirth.age = 2019 - (info + infoLinesCounter)->dateOfBirth.year;
    printf("Введите разряд участника: ");
    category = limitedStringInput(category, 29);
    strcpy((info + infoLinesCounter)->category, category);
    free(category);
    printf("Введите модель коньков участника: ");
    model = limitedStringInput(model, 29);
    strcpy((info + infoLinesCounter)->model, model);
    free(model);
    do {
        printf("Введите количество очков участника: ");
        (info + infoLinesCounter)->points = inputCheck("Введите количество очков участника: ");
        if ((info + infoLinesCounter)->points < 0 || (info + infoLinesCounter)->points > 9999)
            printf("[Ошибка!]Введите число от 0 до 9999!\n");
    } while ((info + infoLinesCounter)->points < 0 || (info + infoLinesCounter)->points > 9999);
    do {
        printf("Введите минуты круга учатсника: ");
        (info + infoLinesCounter)->timeOfLap.minutes = inputCheck("Введите минуты круга участника: ");
        if ((info + infoLinesCounter)->timeOfLap.minutes < 0 || (info + infoLinesCounter)->timeOfLap.minutes > 59)
            printf("[Ошибка!]Введите число от 0 до 59!\n");
    } while ((info + infoLinesCounter)->timeOfLap.minutes < 0 || (info + infoLinesCounter)->timeOfLap.minutes > 59);
    do {
        printf("Введите секунды круга участника: ");
        (info + infoLinesCounter)->timeOfLap.seconds = inputCheck("Введите секунды круга участника: ");
        if ((info + infoLinesCounter)->timeOfLap.seconds < 0 || (info + infoLinesCounter)->timeOfLap.seconds > 59)
            printf("[Ошибка!]Введите число от 0 до 59!\n");
    } while ((info + infoLinesCounter)->timeOfLap.seconds < 0 || (info + infoLinesCounter)->timeOfLap.seconds > 59);
    fprintf(file, "%i %s %s %s %s %i %i %i %i %s %s %i %i %i\n", (info + infoLinesCounter)->number, (info + infoLinesCounter)->fullname.firstname, (info + infoLinesCounter)->fullname.surname, (info + infoLinesCounter)->fullname.lastname, (info + infoLinesCounter)->country, (info + infoLinesCounter)->dateOfBirth.day, (info + infoLinesCounter)->dateOfBirth.month, (info + infoLinesCounter)->dateOfBirth.year, (info + infoLinesCounter)->dateOfBirth.age, (info + infoLinesCounter)->model, (info + infoLinesCounter)->category, (info + infoLinesCounter)->points, (info + infoLinesCounter)->timeOfLap.minutes, (info + infoLinesCounter)->timeOfLap.seconds);
    _flushall();
    fclose(file);
    infoLinesCounter++;
    printf("Участник успешно добавлен!\n\n");
    return info;
}

INFORMATION* infoEdit(INFORMATION* info) {
    if (info == NULL) {
        printf("[Ошибка!]Редактирование информации: Файл не открыт!\n\n");
        return NULL;
    }
    time_t t = time(NULL);
    FILE *file = NULL;
    struct tm* aTm = localtime(&t);
    int number = 0, isExist = 0, i = 0, j = 0, isNumberExist = 0, choice = 0, infoEditFlag = 0;
    char *firstname = NULL, *surname = NULL, *lastname = NULL, *country = NULL, *category = NULL, *model = NULL;
    if (infoLinesCounter == 0) {
        printf("[Ошибка!]Редактирование информации: Файл пуст!\n\n");
        return info;
    }
    do {
        printf("Введите номер участника, которого нужно отредактировать: ");
        number = inputCheck("Введите номер участника, которого нужно отредактировать: ");
        for (i = 0; i < infoLinesCounter; i++) {
            if ((info + i)->number == number) {
                isExist = 1;
                break;
            }
            else isExist = 0;
        }
        if (isExist == 0) printf("[Ошибка!]Участника с таким номером не существует!\n");
    } while (isExist == 0);
    while (infoEditFlag == 0) {
        printf("\nЧто изменить?\n");
        printf("1.Номер.\n");
        printf("2.Имя.\n");
        printf("3.Фамилию.\n");
        printf("4.Отчество.\n");
        printf("5.Страну.\n");
        printf("6.День рождения.\n");
        printf("7.Месяц рождения.\n");
        printf("8.Год рождения.\n");
        printf("9.Разряд.\n");
        printf("10.Модель коньков.\n");
        printf("11.Количество очков.\n");
        printf("12.Минуты круга.\n");
        printf("13.Секунды круга.\n");
        printf("14.Назад.\n");
        printf("Ваш выбор: ");
        choice = inputCheck("Ваш выбор: ");
        printf("\n");
        switch (choice) {
            case 1: {
                int newNumber = 0;
                printf("Изменеие номера.\n");
                do {
                    do {
                        printf("Введите новый номер: ");
                        newNumber = inputCheck("Введите новый номер: ");
                        if (newNumber < 1) printf("[Ошибка!]Введите число больше 0!\n");
                    } while (newNumber < 1);
                    for (j = 0; j < infoLinesCounter; j++) {
                        if ((info + j)->number == newNumber) {
                            isNumberExist = 1;
                            break;
                        }
                        else isNumberExist = 0;
                    }
                    if (isNumberExist == 1) printf("[Ошибка!]Участник с таким номером уже существует!\n");
                } while (isNumberExist == 1);
                (info + i)->number = newNumber;
                printf("Номер успешно изменен!\n");
                break;
            }
            case 2: {
                printf("Изменение имени.\n");
                printf("Введите новое имя: ");
                firstname = limitedStringInput(firstname, 49);
                strcpy((info + i)->fullname.firstname, firstname);
                free(firstname);
                printf("Имя успешно изменено!\n");
                break;
            }
            case 3: {
                printf("Изменение фамилии.\n");
                printf("Введите новую фамилию: ");
                surname = limitedStringInput(surname, 49);
                strcpy((info + i)->fullname.surname, surname);
                free(surname);
                printf("Фамилия успешна изменена!\n");
                break;
            }
            case 4: {
                printf("Изменение отчества.\n");
                printf("Введите новое отчество: ");
                lastname = limitedStringInput(lastname, 49);
                strcpy((info + i)->fullname.lastname, lastname);
                free(lastname);
                printf("Отчество успешно изменено!\n");
                break;
            }
            case 5: {
                printf("Изменение страны.\n");
                printf("Введите новую страну: ");
                country = limitedStringInput(country, 29);
                strcpy((info + i)->country, country);
                free(country);
                printf("Страна успешно изменена.\n");
                break;
            }
            case 6: {
                printf("Изменение дня рождения.\n");
                int newBirthDay = 0;
                do {
                    printf("Введите новый день рождения: ");
                    scanf_s("%i", &newBirthDay);
                    if (newBirthDay < 1 || newBirthDay > 31)
                        printf("[Ошибка!]Введите число от 1 до 31!\n");
                } while (newBirthDay < 1 || newBirthDay > 31);
                (info + i)->dateOfBirth.day = newBirthDay;
                printf("День рождения успешно изменен!\n");
                break;
            }
            case 7: {
                printf("Изменение месяца рождения.\n");
                int newBirthMonth = 0;
                do {
                    printf("Введите новый месяц рождения(числом): ");
                    newBirthMonth = inputCheck("Введите новый номер: ");
                    if (newBirthMonth < 1 || newBirthMonth > 12)
                        printf("[Ошибка!]Введите число от 1 до 12!\n\n");
                } while (newBirthMonth < 1 || newBirthMonth > 12);
                (info + i)->dateOfBirth.month = newBirthMonth;
                printf("Месяц рождения успешно изменен!\n");
                break;
            }
            case 8: {
                printf("Изменение года рождения.\n");
                int newBirthYear = 0;
                do {
                    printf("Введите новый год рождения: ");
                    newBirthYear = inputCheck("Введите новый год рождения: ");
                    if (newBirthYear < 1900 || newBirthYear > 2019)
                        printf("[Ошибка!]Введите число от 1900 до 2019!\n");
                } while (newBirthYear < 1900 || newBirthYear > 2019);
                if ((info + infoLinesCounter)->dateOfBirth.month > aTm->tm_mon + 1)
                    (info + infoLinesCounter)->dateOfBirth.age = 2018 - (info + infoLinesCounter)->dateOfBirth.year;
                else (info + infoLinesCounter)->dateOfBirth.age = 2019 - (info + infoLinesCounter)->dateOfBirth.year;
                printf("Год рождения успешно изменен!\n");
                break;
            }
            case 9: {
                printf("Изменение разряда.\n");
                printf("Введите новый разряд: ");
                category = limitedStringInput(category, 29);
                strcpy((info + i)->category, category);
                free(category);
                printf("Разряд успешно изменен!\n");
                break;
            }
            case 10: {
                printf("Изменение модели коньков.\n");
                printf("Введите новую модель коньков: ");
                model = limitedStringInput(model, 29);
                strcpy((info + i)->model, model);
                free(model);
                printf("Модель коньков успешно изменена!\n");
                break;
            }
            case 11: {
                printf("Изменение количества очков.\n");
                do {
                    printf("Введите новое количество очков: ");
                    (info + infoLinesCounter)->points = inputCheck("Введите новое количество очков: ");
                    if ((info + infoLinesCounter)->points < 0 || (info + infoLinesCounter)->points > 9999)
                        printf("[Ошибка!]Введите число от 0 до 9999!\n");
                } while ((info + infoLinesCounter)->points < 0 || (info + infoLinesCounter)->points > 9999);
            }
            case 12: {
                printf("Изменение минут круга.\n");
                do {
                    printf("Введите новые минуты круга: ");
                    (info + infoLinesCounter)->timeOfLap.minutes = inputCheck("Введите новые минуты круга: ");
                    if ((info + infoLinesCounter)->timeOfLap.minutes < 0 || (info + infoLinesCounter)->timeOfLap.minutes > 59)
                        printf("[Ошибка!]Введите число от 0 до 59!\n");
                } while ((info + infoLinesCounter)->timeOfLap.minutes < 0 || (info + infoLinesCounter)->timeOfLap.minutes > 59);
                printf("Минуты круга успешно изменены!\n");
                break;
            }
            case 13: {
                printf("Изменение секунд круга.\n");
                do {
                    printf("Введите новые секунды круга: ");
                    (info + infoLinesCounter)->timeOfLap.seconds = inputCheck("Введите новые секунды круга: ");
                    if ((info + infoLinesCounter)->timeOfLap.seconds < 0 || (info + infoLinesCounter)->timeOfLap.seconds > 59)
                        printf("[Ошибка!]Введите число от 0 до 59!\n");
                } while ((info + infoLinesCounter)->timeOfLap.seconds < 0 || (info + infoLinesCounter)->timeOfLap.seconds > 59);
                printf("Секунды круга успешно изменены!\n");
                break;
            }
            case 14: infoEditFlag = 1; break;
            default: break;
        }
        if (infoEditFlag == 1) break;
    }
    if ((file = fopen("info.txt", "w")) == NULL) {
        printf("[Ошибка!]Редактирование информации: Не удалось открыть файл! Файл отчищен!\n");
        return info;
    }
    for (j = 0; j < infoLinesCounter; j++) {
        fprintf(file, "%i %s %s %s %s %i %i %i %i %s %s %i %i %i\n", (info + j)->number, (info + j)->fullname.firstname, (info + j)->fullname.surname, (info + j)->fullname.lastname, (info + j)->country, (info + j)->dateOfBirth.day, (info + j)->dateOfBirth.month, (info + j)->dateOfBirth.year, (info + j)->dateOfBirth.age, (info + j)->model, (info + j)->category, (info + j)->points, (info + j)->timeOfLap.minutes, (info + j)->timeOfLap.seconds);
        _flushall();
    }
    fclose(file);
    return info;
}

INFORMATION* infoDelete(INFORMATION *info) {
    int delNumber = 0, isNumberExist = 0, i = 0;
    FILE *file = NULL;
    if (info == NULL) {
        printf("[Ошибка!]Удаление информации: Файл не открыт!\n\n");
        return info;
    }
    if (infoLinesCounter == 0) {
        printf("[Ошибка!]Удаление информации: Файл пуст!\n\n");
        return 0;
    }
    printf("Удаление участника.\n");
    do {
        printf("Введите номер участника для удаления: ");
        delNumber = inputCheck("Введите номер участника для удаления: ");
        for (i = 0; i < infoLinesCounter; i++) {
            if (delNumber == (info + i)->number) {
                isNumberExist = 1;
                break;
            }
            else isNumberExist = 0;
        }
        if (isNumberExist == 0) printf("[Ошибка!]Участника с таким номером не существует!\n");
    } while (isNumberExist != 1);
    if ((file = fopen("info.txt", "w")) == NULL) {
        printf("[Ошибка!]Удаление информации: Не удалось открыть файл! Файл отчищен!\n\n");
        return info;
    }
    for (int j = 0; j < infoLinesCounter; j++) {
        if (j != i) {
            fprintf(file, "%i %s %s %s %s %i %i %i %i %s %s %i %i %i\n", (info + j)->number, (info + j)->fullname.firstname, (info + j)->fullname.surname, (info + j)->fullname.lastname, (info + j)->country, (info + j)->dateOfBirth.day, (info + j)->dateOfBirth.month, (info + j)->dateOfBirth.year, (info + j)->dateOfBirth.age, (info + j)->model, (info + j)->category, (info + j)->points, (info + j)->timeOfLap.minutes, (info + j)->timeOfLap.seconds);
            _flushall();
        }
    }
    fclose(file);
    infoLinesCounter--;
    free(info);
    printf("Участник успешно удалён!\n\n");
    info = infoOpen(info);
    return info;
}

int inputCheck(const char *inputText) {
    while (1) {
        char *buffer = NULL;
        int numberEntered = 0, i = 0, check = 0, isNumeral = 0, flag = 0;
        buffer = limitedStringInput(buffer, 99);
        while (buffer[i] != '\0') {
            if (buffer[i] == '-' && flag == 0) {
                i++;
                flag = 1;
            }
            check = isdigit((unsigned char)buffer[i]);
            if (check == 0) {
                isNumeral = 0;
                break;
            }
            else isNumeral = 1;
            i++;
        }
        if (isNumeral == 1) {
            numberEntered = strtol(buffer, NULL, 10);
            free(buffer);
            return numberEntered;
        }
        else {
            printf("[Ошибка!]Не правильный ввод!\n");
            printf("%s", inputText);
        }
    }
}

char* limitedStringInput(char* input, int limit) {
    char ch;
    int i = 0;
    input = (char*)realloc(NULL, sizeof(char)*(limit + 1));
    while (1) {
        ch = (char)_getch();
        if (ch != '\0') {
            if (ch == 13 || ch == 9) {
                input[i] = '\0';
                putchar('\n');
                break;
            }
            else if (ch == 8 && i > 0) {
                i--;
                printf("\b \b");
            }
            else if (ch == 8 && i == 0)
                continue;
            else {
                if (i < limit) {
                    input[i++] = ch;
                    putchar(ch);
                }
            }
        }
    }
    return input;
}

int searchAndFilteringMenu() {
    int choice;
    printf("Меню поиска и фильтрации.\n");
    printf("1.Фильтр по количеству очков.\n");
    printf("2.Фильтр по времени круга.\n");
    printf("3.Фильтр по возрасту.\n");
    printf("4.Фильтр по году рождения.\n");
    printf("5.Поиск по номеру.\n");
    printf("6.Поиск по фамилии.\n");
    printf("7.Поиск по стране.\n");
    printf("8.Поиск по модели коньков.\n");
    printf("9.Поиск по разряду.\n");
    printf("10.Выход.\n");
    printf("Ваш выбор: ");
    choice = inputCheck("Ваш выбор: ");
    printf("\n");
    return choice;
}

int pointsFilter(INFORMATION* info) {
    int points = 0, isAtLeastOneMember = 0;
    if (info == NULL) {
        printf("[Ошибка!]Поиск и фильтрация: Файл не открыт!\n\n");
        return 0;
    }
    if (infoLinesCounter == 0) {
        printf("[Ошибка!]Поиск и фильтрация: Файл пуст!\n\n");
        return 0;
    }
    do {
        printf("Введите количество очков: ");
        points = inputCheck("Введите количество очков: ");
        if (points < 0 || points > 9999)
            printf("[Ошибка!]Введите число больше 0 и меньше 9999!\n");
    } while (points < 0 || points > 9999);
    printf("Участники, у которых очков больше %i: ", points);
    for (int i = 0; i < infoLinesCounter; i++) {
        if ((info + i)->points > points) {
            if (isAtLeastOneMember == 0) {
                printf("\n================================================================================================================================\n");
                printf("|НОМЕР|ИМЯ             ФАМИЛИЯ         ОТЧЕСТВО       |  СТРАНА  |ДАТА  РОЖДЕНИЯ|ВОЗРАСТ|  РАЗРЯД  |  МОДЕЛЬ  |ОЧКИ|ВРЕМЯ КРУГА|\n");
                printf("================================================================================================================================\n");
            }
            printf("|%-3i  |%-15s %-15s %-15s|%-10s|  %-2i/%02i/%-4i  |  %-3i  |%-10s|%-10s|%-4i|   %02i:%02i   |",
                   (info + i)->number, (info + i)->fullname.firstname, (info + i)->fullname.surname,
                   (info + i)->fullname.lastname, (info + i)->country, (info + i)->dateOfBirth.day,
                   (info + i)->dateOfBirth.month, (info + i)->dateOfBirth.year, (info + i)->dateOfBirth.age,
                   (info + i)->model, (info + i)->category, (info + i)->points, (info + i)->timeOfLap.minutes,
                   (info + i)->timeOfLap.seconds);
            printf("\n");
            isAtLeastOneMember = 1;
        }
        if (isAtLeastOneMember == 1 && i == infoLinesCounter - 1)
            printf("================================================================================================================================\n\n");
    }
    if (isAtLeastOneMember == 0)
        printf("[Ошибка!]Нет ни одного участника с очками больше %i.\n\n", points);
    return 0;
}

int timeOfLapFilter(INFORMATION* info) {
    int minutesOfLap = 0, secondsOfLap = 0, isAtLeastOneMember = 0;
    if (info == NULL) {
        printf("[Ошибка!]Поиск и фильтрация: Файл не открыт!\n\n");
        return 0;
    }
    if (infoLinesCounter == 0) {
        printf("[Ошибка!]Поиск и фильтрация: Файл пуст!\n\n");
        return 0;
    }
    do {
        printf("Введите количество минут круга: ");
        minutesOfLap = inputCheck("Введите количество минут круга: ");
        if (minutesOfLap < 0 || minutesOfLap > 59)
            printf("[Ошибка!]Введите число больше 0 и меньше 59!\n");
    } while (minutesOfLap < 0 || minutesOfLap > 59);
    do {
        printf("Введите количество секунд круга: ");
        secondsOfLap = inputCheck("Введите количество секунд круга: ");
        if (secondsOfLap < 0 || secondsOfLap > 59)
            printf("[Ошибка!]Введите число больше 0 и меньше 59!\n");
    } while (secondsOfLap < 0 || secondsOfLap > 59);
    printf("Участники, у которых время круга меньше %02i:%02i : ", minutesOfLap, secondsOfLap);
    for (int i = 0; i < infoLinesCounter; i++) {
        if ((info + i)->timeOfLap.minutes < minutesOfLap)
            if ((info + i)->timeOfLap.seconds < ((info + i)->timeOfLap.minutes == minutesOfLap ? secondsOfLap : 60)) {
                if (isAtLeastOneMember == 0) {
                    printf("\n================================================================================================================================\n");
                    printf("|НОМЕР|ИМЯ             ФАМИЛИЯ         ОТЧЕСТВО       |  СТРАНА  |ДАТА  РОЖДЕНИЯ|ВОЗРАСТ|  РАЗРЯД  |  МОДЕЛЬ  |ОЧКИ|ВРЕМЯ КРУГА|\n");
                    printf("================================================================================================================================\n");
                }
                printf("|%-3i  |%-15s %-15s %-15s|%-10s|  %-2i/%02i/%-4i  |  %-3i  |%-10s|%-10s|%-4i|   %02i:%02i   |",
                       (info + i)->number, (info + i)->fullname.firstname, (info + i)->fullname.surname,
                       (info + i)->fullname.lastname, (info + i)->country, (info + i)->dateOfBirth.day,
                       (info + i)->dateOfBirth.month, (info + i)->dateOfBirth.year, (info + i)->dateOfBirth.age,
                       (info + i)->model, (info + i)->category, (info + i)->points, (info + i)->timeOfLap.minutes,
                       (info + i)->timeOfLap.seconds);
                printf("\n");
                isAtLeastOneMember = 1;
            }
        if (isAtLeastOneMember == 1 && i == infoLinesCounter - 1)
            printf("================================================================================================================================\n\n");
    }
    if (isAtLeastOneMember == 0)
        printf("[Ошибка!]Нет ни одного участника с временем круга меньше %02i:%02i.\n\n", minutesOfLap, secondsOfLap);
    return 0;
}

int ageFilter(INFORMATION* info) {
    int age = 0, isAtLeastOneMember = 0;
    if (info == NULL) {
        printf("[Ошибка!]Поиск и фильтрация: Файл не открыт!\n\n");
        return 0;
    }
    if (infoLinesCounter == 0) {
        printf("[Ошибка!]Поиск и фильтрация: Файл пуст!\n\n");
        return 0;
    }
    do {
        printf("Введите возраст: ");
        age = inputCheck("Введите количество очков: ");
        if (age < 0 || age > 119)
            printf("[Ошибка!]Введите число больше 0 и меньше 119!\n");
    } while (age < 0 || age > 119);
    printf("Участники, возраст которых больше %i: ", age);
    for (int i = 0; i < infoLinesCounter; i++) {
        if ((info + i)->dateOfBirth.age > age) {
            if (isAtLeastOneMember == 0) {
                printf("\n================================================================================================================================\n");
                printf("|НОМЕР|ИМЯ             ФАМИЛИЯ         ОТЧЕСТВО       |  СТРАНА  |ДАТА  РОЖДЕНИЯ|ВОЗРАСТ|  РАЗРЯД  |  МОДЕЛЬ  |ОЧКИ|ВРЕМЯ КРУГА|\n");
                printf("================================================================================================================================\n");
            }
            printf("|%-3i  |%-15s %-15s %-15s|%-10s|  %-2i/%02i/%-4i  |  %-3i  |%-10s|%-10s|%-4i|   %02i:%02i   |",
                   (info + i)->number, (info + i)->fullname.firstname, (info + i)->fullname.surname,
                   (info + i)->fullname.lastname, (info + i)->country, (info + i)->dateOfBirth.day,
                   (info + i)->dateOfBirth.month, (info + i)->dateOfBirth.year, (info + i)->dateOfBirth.age,
                   (info + i)->model, (info + i)->category, (info + i)->points, (info + i)->timeOfLap.minutes,
                   (info + i)->timeOfLap.seconds);
            printf("\n");
            isAtLeastOneMember = 1;
        }
        if (isAtLeastOneMember == 1 && i == infoLinesCounter - 1)
            printf("================================================================================================================================\n\n");
    }
    if (isAtLeastOneMember == 0)
        printf("[Ошибка!]Нет ни одного участника с очками больше %i.\n\n", age);
    return 0;
}

int yearOfBirthFilter(INFORMATION* info) {
    int yearOfBirth = 0, isAtLeastOneMember = 0;
    if (info == NULL) {
        printf("[Ошибка!]Поиск и фильтрация: Файл не открыт!\n\n");
        return 0;
    }
    if (infoLinesCounter == 0) {
        printf("[Ошибка!]Поиск и фильтрация: Файл пуст!\n\n");
        return 0;
    }
    do {
        printf("Введите год рождения: ");
        yearOfBirth = inputCheck("Введите год рождения: ");
        if (yearOfBirth < 1900 || yearOfBirth > 2019)
            printf("[Ошибка!]Введите число больше 1900 и меньше 2019!\n");
    } while (yearOfBirth < 1900 || yearOfBirth > 2019);
    printf("Участники, год рождения у которых больше %i: ", yearOfBirth);
    for (int i = 0; i < infoLinesCounter; i++) {
        if ((info + i)->dateOfBirth.year > yearOfBirth) {
            if (isAtLeastOneMember == 0) {
                printf("\n================================================================================================================================\n");
                printf("|НОМЕР|ИМЯ             ФАМИЛИЯ         ОТЧЕСТВО       |  СТРАНА  |ДАТА  РОЖДЕНИЯ|ВОЗРАСТ|  РАЗРЯД  |  МОДЕЛЬ  |ОЧКИ|ВРЕМЯ КРУГА|\n");
                printf("================================================================================================================================\n");
            }
            printf("|%-3i  |%-15s %-15s %-15s|%-10s|  %-2i/%02i/%-4i  |  %-3i  |%-10s|%-10s|%-4i|   %02i:%02i   |",
                   (info + i)->number, (info + i)->fullname.firstname, (info + i)->fullname.surname,
                   (info + i)->fullname.lastname, (info + i)->country, (info + i)->dateOfBirth.day,
                   (info + i)->dateOfBirth.month, (info + i)->dateOfBirth.year, (info + i)->dateOfBirth.age,
                   (info + i)->model, (info + i)->category, (info + i)->points, (info + i)->timeOfLap.minutes,
                   (info + i)->timeOfLap.seconds);
            printf("\n");
            isAtLeastOneMember = 1;
        }
        if (isAtLeastOneMember == 1 && i == infoLinesCounter - 1)
            printf("================================================================================================================================\n\n");
    }
    if (isAtLeastOneMember == 0)
        printf("[Ошибка!]Нет ни одного участника с годом рождения больше %i.\n\n", yearOfBirth);
    return 0;
}