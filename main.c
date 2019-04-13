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
int userManagementMenu();
USER* userManagement(USER* user);
USER* userLoad(USER* user);
USER* userAdd(USER* user);
USER* userDelete(USER* user);
USER* userEdit(USER* user);
void userPrint(USER* user);
INFORMATION* infoOpen(INFORMATION* info);
INFORMATION* infoAdd(INFORMATION* info);
INFORMATION* infoEdit(INFORMATION* info);
INFORMATION* infoDelete(INFORMATION *info);
void infoPrint(INFORMATION* info);
char* limitedStringInput(char* input, int limit);
int infoCheckFile();
void infoCreateFile();
int searchAndFilteringMenu();
int searchingAndFiltering(INFORMATION* info);
void pointsFilter(INFORMATION* info);
void timeOfLapFilter(INFORMATION* info);
void ageFilter(INFORMATION* info);
void yearOfBirthFilter(INFORMATION* info);
void timeOfLapSorting(INFORMATION* info);
void numberSearch(INFORMATION* info);
void surnameSearch(INFORMATION* info);
void countrySearch(INFORMATION* info);
void categorySearch(INFORMATION* info);
void printTop(INFORMATION* info);


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    INFORMATION *info = NULL;
    USER *user = NULL;
    user = userLoad(user);
    int adminSubMenuFlag = 0, userSubMenuFlag = 0;
    if (user == NULL) {
        system("pause");
        return 0;
    }
    while (1) {
        system("cls");
        switch (menu()) {
            case 1: {
                if (adminLogin(user) == 1) {
                    while (adminSubMenuFlag == 0) {
                        system("cls");
                        switch (adminSubmenu()) {
                            case 1: {
                                system("cls");
                                if (infoCheckFile() == 0) {
                                    infoCreateFile();
                                    info = infoOpen(info);
                                } else info = infoOpen(info);
                                break;
                            }
                            case 2: info = infoAdd(info); break;
                            case 3: info = infoEdit(info); break;
                            case 4: info = infoDelete(info); break;
                            case 5: infoPrint(info); break;
                            case 6: searchingAndFiltering(info); break;
                            case 7: user = userManagement(user); break;
                            case 8: adminSubMenuFlag = 1; break;
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
                        system("cls");
                        switch (userSubmenu()) {
                            case 1: {
                                system("cls");
                                if (infoCheckFile() == 1) {
                                    info = infoOpen(info);
                                }
                                break;
                            }
                            case 2: infoPrint(info); break;
                            case 3: printTop(info); break;
                            case 4: searchingAndFiltering(info); break;
                            case 5: userSubMenuFlag = 1; break;
                            default: break;
                        }
                        if (userSubMenuFlag == 1) break;
                    }
                    userSubMenuFlag = 0;
                }
                break;
            }
            case 3: free(info); free(user); return 0;
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
    choice = inputCheck("Ваш выбор: ");
    printf("\n");
    return choice;
};

int userSubmenu() {
    int choice;
    printf("Подменю(для пользователей):\n");
    printf("1.Открытие файла с данными.\n");
    printf("2.Просмотр всех данных в табличной форме.\n");
    printf("3.Просмотреть топ-3 самых быстрых участников.\n");
    printf("4.Различные процедуры поиска и фильтрации данных.\n");
    printf("5.Выход в меню.\n");
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
    system("cls");
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
            system("pause");
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
        system("pause");
        return 1;
    }
    else {
        printf("\n[Ошибка!]Авторизация: Войдите через пользователя!\n\n");
        system("pause");
        free(login);
        return 0;
    }
}

int userLogin(USER *user) {
    system("cls");
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
            system("pause");
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
        system("pause");
        return 1;
    }
    else {
        printf("\n[Ошибка!]Авторизация! Войдите через администратора!\n\n");
        system("pause");
        free(login);
        return 0;
    }
}

int userManagementMenu() {
    int choice;
    printf("Управление пользователями:\n");
    printf("1.Добавить аккаунт.\n");
    printf("2.Удалить аккаунт.\n");
    printf("3.Редактировать аккаунт.\n");
    printf("4.Просмотр всех аккаунтов.\n");
    printf("5.Назад.\n");
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
        } else {
            printf("[Ошибка!]Инициальзация пользователей: Не удалось создать файл с логинами/паролями!\n");
            system("pause");
            exit(0);
        }
    } else if (usersLinesCounter != 0) {
        user = (USER*)malloc(usersLinesCounter*(sizeof(USER)));
        for (int i = 0; i < usersLinesCounter; i++)
            fscanf(file, "%s %s %i", (user + i)->login, (user + i)->password, &((user + i)->isAdmin));
        fclose(file);
    }
    return user;
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
        (user + usersLinesCounter)->isAdmin = inputCheck("Администратор?(1 - Да|0 - Нет): ");
        if ((user + usersLinesCounter)->isAdmin < 0 || (user + usersLinesCounter)->isAdmin > 1) {
            printf("[Ошибка!]Не правильный ввод!\n");
        }
    } while ((user + usersLinesCounter)->isAdmin < 0 || (user + usersLinesCounter)->isAdmin > 1);
    if ((file = fopen("db.txt", "at+")) != NULL) {
        fprintf(file, "%s %s %i\n", (user + usersLinesCounter)->login, (user + usersLinesCounter)->password,
                (user + usersLinesCounter)->isAdmin);
        fclose(file);
        printf("Аккаунт успешно добавлен!\n\n");
        _flushall();
        usersLinesCounter++;
    } else printf("[Ошибка!]Добавление пользователей: Ошибка открытия файла с логинами/паролями! Пользователь не добавлен!\n\n");
    system("pause");
    return user;
}

void userPrint(USER* user) {
    system("cls");
    char yes[] = "Да", no[] = "Нет";
    printf("-----------------------------------------------------------------------------------------------\n");
    printf("|№    |ЛОГИН:                         |ПАРОЛЬ:                         |ПРАВА АДМИНИСТРАТОРА: |\n");
    printf("-----------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < usersLinesCounter; i++) {
        printf("|%-5i|%-31s|%-32s|", i + 1, (user + i)->login, (user + i)->password);
        if ((user + i)->isAdmin == 1)
            printf("%-22s|", yes);
        else printf("%-22s|", no);
        printf("\n");
    }
    printf("-----------------------------------------------------------------------------------------------\n\n");
    system("pause");
}

USER* userManagement(USER* user) {
    while (1) {
        system("cls");
        switch (userManagementMenu()) {
            case 1: user = userAdd(user); break;
            case 2: user = userDelete(user); break;
            case 3: user = userEdit(user); break;
            case 4: userPrint(user); break;
            case 5: return user;
            default: break;
        }
    }
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
    if ((file = fopen("db.txt", "w")) != NULL) {
        for(int j = i; j < usersLinesCounter; j++)
            *(user + j) = *(user + (j + 1));
        user = (USER*)realloc(user, sizeof(USER)*usersLinesCounter);
        usersLinesCounter--;
        for (int j = 0; j < usersLinesCounter; j++)
            fprintf(file, "%s %s %i\n", (user + j)->login, (user + j)->password, (user + j)->isAdmin);
        printf("Аккаунт успешно удалён!\n\n");
        fclose(file);
    } else printf("[Ошибка!]Удаление пользователей: Ошибка открытия файла с логинами/паролями! Пользователь не удален! Файл отчищен!\n\n");
    system("pause");
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
    while (editFlag == 0) {
        system("cls");
        printf("-----------------------------------------------------------------------------------------\n");
        printf("|ЛОГИН:                         |ПАРОЛЬ:                         |ПРАВА АДМИНИСТРАТОРА: |\n");
        printf("-----------------------------------------------------------------------------------------\n");
        printf("|%-31s|%-32s|", (user + i)->login, (user + i)->password);
        if ((user + i)->isAdmin == 1)
            printf("%-22s|", yes);
        else printf("%-22s|", no);
        printf("\n-----------------------------------------------------------------------------------------\n\n");
        printf("Что отредактировать?\n");
        printf("1.Логин.\n");
        printf("2.Пароль.\n");
        printf("3.Права администратора.\n");
        printf("4.Назад.\n");
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
    if ((file = fopen("db.txt", "w")) != NULL) {
        for (i = 0; i < usersLinesCounter; i++)
            fprintf(file, "%s %s %i\n", (user + i)->login, (user + i)->password, (user + i)->isAdmin);
        fclose(file);
    } else printf("[Ошибка!]Редактирование пользователей: Не удалось открыть файл с логинами/паролями! Пользователь не отредактирован! Файл отчищен!\n\n");
    system("pause");
    return user;
}

int infoCheckFile() {
    FILE* file = NULL;
    if ((file = fopen("info.txt", "rt+")) == NULL) {
        printf("[Ошибка!]Открытие информации: Файл ещё не создан!\n\n");
        return 0;
    } else {
        fclose(file);
        return 1;
    }
}

void infoCreateFile() {
    FILE* file = NULL;
    if (!file)
        if ((file = fopen("info.txt", "wt+")) != NULL)
            printf("Открытие информации: Файл успешно создан!\n");
    fclose(file);
}

INFORMATION* infoOpen(INFORMATION* info) {
    if(info != NULL)
        printf("[Ошибка!]Открытие информации: Файл уже открыт!\n\n");
    else {
        FILE *file = NULL;
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

void infoPrint(INFORMATION* info) {
    system("cls");
    if (info == NULL)
        printf("[Ошибка!]Вывод информации: Файл еще не открыт!\n\n");
    else if (infoLinesCounter == 0)
        printf("[Ошибка!]Вывод информации: Файл пуст!\n\n");
    else {
        printf("--------------------------------------------------------------------------------------------------------------------------------\n");
        printf("|НОМЕР|ИМЯ             ФАМИЛИЯ         ОТЧЕСТВО       |  СТРАНА  |ДАТА  РОЖДЕНИЯ|ВОЗРАСТ|  РАЗРЯД  |  МОДЕЛЬ  |ОЧКИ|ВРЕМЯ КРУГА|\n");
        printf("--------------------------------------------------------------------------------------------------------------------------------\n");
        for (int i = 0; i < infoLinesCounter; i++) {
            printf("|%-3i  |%-15s %-15s %-15s|%-10s|  %-2i/%02i/%-4i  |  %-3i  |%-10s|%-10s|%-4i|   %02i:%02i   |\n",
                    (info + i)->number, (info + i)->fullname.firstname, (info + i)->fullname.surname, (info + i)->fullname.lastname, (info + i)->country,
                    (info + i)->dateOfBirth.day, (info + i)->dateOfBirth.month, (info + i)->dateOfBirth.year, (info + i)->dateOfBirth.age, (info + i)->category,
                    (info + i)->model, (info + i)->points, (info + i)->timeOfLap.minutes, (info + i)->timeOfLap.seconds);
        }
        printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
    };
    system("pause");
}

INFORMATION* infoAdd(INFORMATION* info) {
    FILE *file = NULL;
    if (info == NULL)
        printf("[Ошибка!]Добавление информации: Файл не открыт!\n\n");
    else if ((file = fopen("info.txt", "a+")) == NULL)
        printf("[Ошибка!]Добавление информации: Не удалось открыть файл для добавления!\n");
    else {
        info = (INFORMATION *) realloc(info, ((infoLinesCounter + 1) * sizeof(INFORMATION)));
        time_t t = time(NULL);
        struct tm *aTm = localtime(&t);
        int isExist = 0;
        char *firstname = NULL, *surname = NULL, *lastname = NULL, *country = NULL, *category = NULL, *model = NULL;
        printf("Добавление участника.\n");
        do {
            do {
                (info + infoLinesCounter)->number = inputCheck("Введите номер участника: ");
                if ((info + infoLinesCounter)->number < 1)
                    printf("[Ошибка!]Введите число больше 0!\n");
            } while ((info + infoLinesCounter)->number < 1);
            for (int i = 0; i < infoLinesCounter; i++) {
                if ((info + i)->number == (info + infoLinesCounter)->number) {
                    isExist = 1;
                    break;
                } else isExist = 0;
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
            (info + infoLinesCounter)->dateOfBirth.day = inputCheck("Введите день рождения участника: ");
            if ((info + infoLinesCounter)->dateOfBirth.day < 1 || (info + infoLinesCounter)->dateOfBirth.day > 31)
                printf("[Ошибка!]Введите число от 1 до 31!\n");
        } while ((info + infoLinesCounter)->dateOfBirth.day < 1 || (info + infoLinesCounter)->dateOfBirth.day > 31);
        do {
            (info + infoLinesCounter)->dateOfBirth.month = inputCheck("Введите месяц рождения участника(числом): ");
            if ((info + infoLinesCounter)->dateOfBirth.month < 1 || (info + infoLinesCounter)->dateOfBirth.month > 12)
                printf("[Ошибка!]Введите число от 1 до 12!\n");
        } while ((info + infoLinesCounter)->dateOfBirth.month < 1 || (info + infoLinesCounter)->dateOfBirth.month > 12);
        do {
            (info + infoLinesCounter)->dateOfBirth.year = inputCheck("Введите год рождения участника: ");
            if ((info + infoLinesCounter)->dateOfBirth.year < 1900 ||
                (info + infoLinesCounter)->dateOfBirth.year > 2019)
                printf("[Ошибка!]Введите число от 1900 до 2019!\n");
        } while ((info + infoLinesCounter)->dateOfBirth.year < 1900 ||
                 (info + infoLinesCounter)->dateOfBirth.year > 2019);
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
            (info + infoLinesCounter)->points = inputCheck("Введите количество очков участника: ");
            if ((info + infoLinesCounter)->points < 0 || (info + infoLinesCounter)->points > 9999)
                printf("[Ошибка!]Введите число от 0 до 9999!\n");
        } while ((info + infoLinesCounter)->points < 0 || (info + infoLinesCounter)->points > 9999);
        do {
            (info + infoLinesCounter)->timeOfLap.minutes = inputCheck("Введите минуты круга участника: ");
            if ((info + infoLinesCounter)->timeOfLap.minutes < 0 || (info + infoLinesCounter)->timeOfLap.minutes > 59)
                printf("[Ошибка!]Введите число от 0 до 59!\n");
        } while ((info + infoLinesCounter)->timeOfLap.minutes < 0 || (info + infoLinesCounter)->timeOfLap.minutes > 59);
        do {
            (info + infoLinesCounter)->timeOfLap.seconds = inputCheck("Введите секунды круга участника: ");
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

INFORMATION* infoEdit(INFORMATION* info) {
    if (info == NULL)
        printf("[Ошибка!]Редактирование информации: Файл не открыт!\n\n");
    else if (infoLinesCounter == 0)
        printf("[Ошибка!]Редактирование информации: Файл пуст!\n\n");
    else {
        time_t t = time(NULL);
        FILE *file = NULL;
        struct tm *aTm = localtime(&t);
        int number = 0, isExist = 0, i = 0, j = 0, isNumberExist = 0, choice = 0, infoEditFlag = 0;
        char *firstname = NULL, *surname = NULL, *lastname = NULL, *country = NULL, *category = NULL, *model = NULL;
        do {
            number = inputCheck("Введите номер участника, которого нужно отредактировать: ");
            for (i = 0; i < infoLinesCounter; i++) {
                if ((info + i)->number == number) {
                    isExist = 1;
                    break;
                } else isExist = 0;
            }
            if (isExist == 0) printf("[Ошибка!]Участника с таким номером не существует!\n");
        } while (isExist == 0);
        while (infoEditFlag == 0) {
            system("cls");
            printf("--------------------------------------------------------------------------------------------------------------------------------\n");
            printf("|НОМЕР|ИМЯ             ФАМИЛИЯ         ОТЧЕСТВО       |  СТРАНА  |ДАТА  РОЖДЕНИЯ|ВОЗРАСТ|  РАЗРЯД  |  МОДЕЛЬ  |ОЧКИ|ВРЕМЯ КРУГА|\n");
            printf("--------------------------------------------------------------------------------------------------------------------------------\n");
            printf("|%-3i  |%-15s %-15s %-15s|%-10s|  %-2i/%02i/%-4i  |  %-3i  |%-10s|%-10s|%-4i|   %02i:%02i   |\n",
                   (info + i)->number, (info + i)->fullname.firstname, (info + i)->fullname.surname,
                   (info + i)->fullname.lastname, (info + i)->country,
                   (info + i)->dateOfBirth.day, (info + i)->dateOfBirth.month, (info + i)->dateOfBirth.year,
                   (info + i)->dateOfBirth.age, (info + i)->category,
                   (info + i)->model, (info + i)->points, (info + i)->timeOfLap.minutes, (info + i)->timeOfLap.seconds);
            printf("--------------------------------------------------------------------------------------------------------------------------------\n");
            printf("Что изменить?\n");
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
            choice = inputCheck("Ваш выбор: ");
            printf("\n");
            switch (choice) {
                case 1: {
                    int newNumber = 0;
                    printf("Изменеие номера.\n");
                    do {
                        do {
                            newNumber = inputCheck("Введите новый номер: ");
                            if (newNumber < 1)
                                printf("[Ошибка!]Введите число больше 0!\n");
                        } while (newNumber < 1);
                        for (j = 0; j < infoLinesCounter; j++) {
                            if ((info + j)->number == newNumber) {
                                isNumberExist = 1;
                                break;
                            } else isNumberExist = 0;
                        }
                        if (isNumberExist == 1)
                            printf("[Ошибка!]Участник с таким номером уже существует!\n");
                    } while (isNumberExist == 1);
                    (info + i)->number = newNumber;
                    printf("Номер успешно изменен!\n\n");
                    break;
                }
                case 2: {
                    printf("Изменение имени.\n");
                    printf("Введите новое имя: ");
                    firstname = limitedStringInput(firstname, 49);
                    strcpy((info + i)->fullname.firstname, firstname);
                    free(firstname);
                    printf("Имя успешно изменено!\n\n");
                    break;
                }
                case 3: {
                    printf("Изменение фамилии.\n");
                    printf("Введите новую фамилию: ");
                    surname = limitedStringInput(surname, 49);
                    strcpy((info + i)->fullname.surname, surname);
                    free(surname);
                    printf("Фамилия успешна изменена!\n\n");
                    break;
                }
                case 4: {
                    printf("Изменение отчества.\n");
                    printf("Введите новое отчество: ");
                    lastname = limitedStringInput(lastname, 49);
                    strcpy((info + i)->fullname.lastname, lastname);
                    free(lastname);
                    printf("Отчество успешно изменено!\n\n");
                    break;
                }
                case 5: {
                    printf("Изменение страны.\n");
                    printf("Введите новую страну: ");
                    country = limitedStringInput(country, 29);
                    strcpy((info + i)->country, country);
                    free(country);
                    printf("Страна успешно изменена.\n\n");
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
                    printf("День рождения успешно изменен!\n\n");
                    break;
                }
                case 7: {
                    printf("Изменение месяца рождения.\n");
                    int newBirthMonth = 0;
                    do {
                        newBirthMonth = inputCheck("Введите новый номер: ");
                        if (newBirthMonth < 1 || newBirthMonth > 12)
                            printf("[Ошибка!]Введите число от 1 до 12!\n\n");
                    } while (newBirthMonth < 1 || newBirthMonth > 12);
                    (info + i)->dateOfBirth.month = newBirthMonth;
                    printf("Месяц рождения успешно изменен!\n\n");
                    break;
                }
                case 8: {
                    printf("Изменение года рождения.\n");
                    int newBirthYear = 0;
                    do {
                        newBirthYear = inputCheck("Введите новый год рождения: ");
                        if (newBirthYear < 1900 || newBirthYear > 2019)
                            printf("[Ошибка!]Введите число от 1900 до 2019!\n");
                    } while (newBirthYear < 1900 || newBirthYear > 2019);
                    if ((info + infoLinesCounter)->dateOfBirth.month > aTm->tm_mon + 1)
                        (info + infoLinesCounter)->dateOfBirth.age = 2018 - (info + infoLinesCounter)->dateOfBirth.year;
                    else
                        (info + infoLinesCounter)->dateOfBirth.age = 2019 - (info + infoLinesCounter)->dateOfBirth.year;
                    printf("Год рождения успешно изменен!\n\n");
                    break;
                }
                case 9: {
                    printf("Изменение разряда.\n");
                    printf("Введите новый разряд: ");
                    category = limitedStringInput(category, 29);
                    strcpy((info + i)->category, category);
                    free(category);
                    printf("Разряд успешно изменен!\n\n");
                    break;
                }
                case 10: {
                    printf("Изменение модели коньков.\n");
                    printf("Введите новую модель коньков: ");
                    model = limitedStringInput(model, 29);
                    strcpy((info + i)->model, model);
                    free(model);
                    printf("Модель коньков успешно изменена!\n\n");
                    break;
                }
                case 11: {
                    printf("Изменение количества очков.\n");
                    do {
                        (info + infoLinesCounter)->points = inputCheck("Введите новое количество очков: ");
                        if ((info + infoLinesCounter)->points < 0 || (info + infoLinesCounter)->points > 9999)
                            printf("[Ошибка!]Введите число от 0 до 9999!\n");
                    } while ((info + infoLinesCounter)->points < 0 || (info + infoLinesCounter)->points > 9999);
                    printf("Количество очков успешно изменено!\n\n");
                }
                case 12: {
                    printf("Изменение минут круга.\n");
                    do {
                        (info + infoLinesCounter)->timeOfLap.minutes = inputCheck("Введите новые минуты круга: ");
                        if ((info + infoLinesCounter)->timeOfLap.minutes < 0 ||
                            (info + infoLinesCounter)->timeOfLap.minutes > 59)
                            printf("[Ошибка!]Введите число от 0 до 59!\n");
                    } while ((info + infoLinesCounter)->timeOfLap.minutes < 0 ||
                             (info + infoLinesCounter)->timeOfLap.minutes > 59);
                    printf("Минуты круга успешно изменены!\n\n");
                    break;
                }
                case 13: {
                    printf("Изменение секунд круга.\n");
                    do {
                        (info + infoLinesCounter)->timeOfLap.seconds = inputCheck("Введите новые секунды круга: ");
                        if ((info + infoLinesCounter)->timeOfLap.seconds < 0 ||
                            (info + infoLinesCounter)->timeOfLap.seconds > 59)
                            printf("[Ошибка!]Введите число от 0 до 59!\n");
                    } while ((info + infoLinesCounter)->timeOfLap.seconds < 0 ||
                             (info + infoLinesCounter)->timeOfLap.seconds > 59);
                    printf("Секунды круга успешно изменены!\n\n");
                    break;
                }
                case 14:
                    infoEditFlag = 1;
                    break;
                default:
                    break;
            }
            if (infoEditFlag == 1) break;
        }
        if ((file = fopen("info.txt", "w")) != NULL) {
            for (j = 0; j < infoLinesCounter; j++) {
                fprintf(file, "%i %s %s %s %s %i %i %i %i %s %s %i %i %i\n", (info + j)->number,
                        (info + j)->fullname.firstname, (info + j)->fullname.surname, (info + j)->fullname.lastname,
                        (info + j)->country, (info + j)->dateOfBirth.day, (info + j)->dateOfBirth.month,
                        (info + j)->dateOfBirth.year, (info + j)->dateOfBirth.age, (info + j)->model, (info + j)->category,
                        (info + j)->points, (info + j)->timeOfLap.minutes, (info + j)->timeOfLap.seconds);
                _flushall();
            }
        } else printf("[Ошибка!]Редактирование информации: Не удалось перезаписать файл! Файл отчищен!\n");
    }
    system("pause");
    return info;
}

INFORMATION* infoDelete(INFORMATION *info) {
    if (info == NULL) {
        printf("[Ошибка!]Удаление информации: Файл не открыт!\n\n");
    } else if (infoLinesCounter == 0) {
        printf("[Ошибка!]Удаление информации: Файл пуст!\n\n");
    } else {
        int delNumber = 0, isNumberExist = 0, i = 0;
        FILE *file = NULL;
        printf("Удаление участника.\n");
        do {
            delNumber = inputCheck("Введите номер участника для удаления: ");
            for (i = 0; i < infoLinesCounter; i++) {
                if (delNumber == (info + i)->number) {
                    isNumberExist = 1;
                    break;
                } else isNumberExist = 0;
            }
            if (isNumberExist == 0) printf("[Ошибка!]Участника с таким номером не существует!\n");
        } while (isNumberExist != 1);
        for(int j = i; j < infoLinesCounter; j++)
            *(info + j) = *(info + (j + 1));
        info = (INFORMATION*)realloc(info,sizeof(INFORMATION)*infoLinesCounter);
        infoLinesCounter--;
        if((file = fopen("info.txt", "w")) != NULL) {
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
    }
    system("pause");
    return info;
}

int inputCheck(const char *inputText) {
    while (1) {
        printf("%s", inputText);
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
    printf("Меню поиска и фильтрации:\n");
    printf("1.Фильтр по количеству очков.\n");
    printf("2.Фильтр по времени круга.\n");
    printf("3.Фильтр по возрасту.\n");
    printf("4.Фильтр по году рождения.\n");
    printf("5.Поиск по номеру.\n");
    printf("6.Поиск по фамилии.\n");
    printf("7.Поиск по стране.\n");
    printf("9.Поиск по разряду.\n");
    printf("9.Сортировка по времени круга.\n");
    printf("10.Выход.\n");
    choice = inputCheck("Ваш выбор: ");
    printf("\n");
    return choice;
}

void pointsFilter(INFORMATION* info) {
    if (info == NULL)
        printf("[Ошибка!]Поиск и фильтрация: Файл не открыт!\n\n");
    else if (infoLinesCounter == 0)
        printf("[Ошибка!]Поиск и фильтрация: Файл пуст!\n\n");
    else {
        int points = 0, isAtLeastOneMember = 0;
        do {
            points = inputCheck("Введите количество очков: ");
            if (points < 0 || points > 9999)
                printf("[Ошибка!]Введите число больше 0 и меньше 9999!\n");
        } while (points < 0 || points > 9999);
        printf("Участники, у которых очков больше %i: ", points);
        for (int i = 0; i < infoLinesCounter; i++) {
            if ((info + i)->points > points) {
                if (isAtLeastOneMember == 0) {
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
                isAtLeastOneMember = 1;
            }
            if (isAtLeastOneMember == 1 && i == infoLinesCounter - 1)
                printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
        }
        if (isAtLeastOneMember == 0)
            printf("[Ошибка!]Нет ни одного участника с очками больше %i.\n\n", points);
    }
    system("pause");
}

void timeOfLapFilter(INFORMATION* info) {
    if (info == NULL) {
        printf("[Ошибка!]Поиск и фильтрация: Файл не открыт!\n\n");
    } else if (infoLinesCounter == 0) {
        printf("[Ошибка!]Поиск и фильтрация: Файл пуст!\n\n");
    } else {
        int minutesOfLap = 0, secondsOfLap = 0, isAtLeastOneMember = 0;
        do {
            minutesOfLap = inputCheck("Введите количество минут круга: ");
            if (minutesOfLap < 0 || minutesOfLap > 59)
                printf("[Ошибка!]Введите число больше 0 и меньше 59!\n");
        } while (minutesOfLap < 0 || minutesOfLap > 59);
        do {
            secondsOfLap = inputCheck("Введите количество секунд круга: ");
            if (secondsOfLap < 0 || secondsOfLap > 59)
                printf("[Ошибка!]Введите число больше 0 и меньше 59!\n");
        } while (secondsOfLap < 0 || secondsOfLap > 59);
        printf("Участники, у которых время круга меньше %02i:%02i : ", minutesOfLap, secondsOfLap);
        for (int i = 0; i < infoLinesCounter; i++) {
            if ((info + i)->timeOfLap.minutes < minutesOfLap)
                if ((info + i)->timeOfLap.seconds <
                    ((info + i)->timeOfLap.minutes == minutesOfLap ? secondsOfLap : 60)) {
                    if (isAtLeastOneMember == 0) {
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
                    isAtLeastOneMember = 1;
                }
            if (isAtLeastOneMember == 1 && i == infoLinesCounter - 1)
                printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
        }
        if (isAtLeastOneMember == 0)
            printf("[Ошибка!]Нет ни одного участника с временем круга меньше %02i:%02i.\n\n", minutesOfLap,
                   secondsOfLap);
    }
    system("pause");
}

void ageFilter(INFORMATION* info) {
    if (info == NULL)
        printf("[Ошибка!]Поиск и фильтрация: Файл не открыт!\n\n");
    else if (infoLinesCounter == 0)
        printf("[Ошибка!]Поиск и фильтрация: Файл пуст!\n\n");
    else {
        int age = 0, isAtLeastOneMember = 0;
        do {
            age = inputCheck("Введите возраст: ");
            if (age < 0 || age > 119)
                printf("[Ошибка!]Введите число больше 0 и меньше 119!\n");
        } while (age < 0 || age > 119);
        printf("Участники, возраст которых больше %i: ", age);
        for (int i = 0; i < infoLinesCounter; i++) {
            if ((info + i)->dateOfBirth.age > age) {
                if (isAtLeastOneMember == 0) {
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
                isAtLeastOneMember = 1;
            }
            if (isAtLeastOneMember == 1 && i == infoLinesCounter - 1)
                printf("================================================================================================================================\n\n");
        }
        if (isAtLeastOneMember == 0)
            printf("[Ошибка!]Нет ни одного участника с очками больше %i.\n\n", age);
    }
    system("pause");
}

void yearOfBirthFilter(INFORMATION* info) {
    if (info == NULL)
        printf("[Ошибка!]Поиск и фильтрация: Файл не открыт!\n\n");
    else if (infoLinesCounter == 0)
        printf("[Ошибка!]Поиск и фильтрация: Файл пуст!\n\n");
    else {
        int yearOfBirth = 0, isAtLeastOneMember = 0;
        do {
            yearOfBirth = inputCheck("Введите год рождения: ");
            if (yearOfBirth < 1900 || yearOfBirth > 2019)
                printf("[Ошибка!]Введите число больше 1900 и меньше 2019!\n");
        } while (yearOfBirth < 1900 || yearOfBirth > 2019);
        printf("Участники, год рождения у которых больше %i: ", yearOfBirth);
        for (int i = 0; i < infoLinesCounter; i++) {
            if ((info + i)->dateOfBirth.year > yearOfBirth) {
                if (isAtLeastOneMember == 0) {
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
                isAtLeastOneMember = 1;
            }
            if (isAtLeastOneMember == 1 && i == infoLinesCounter - 1) {
                printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
            }
        }
        if (isAtLeastOneMember == 0)
            printf("[Ошибка!]Нет ни одного участника с годом рождения больше %i.\n\n", yearOfBirth);
    }
    system("pause");
}

void timeOfLapSorting(INFORMATION* info){
    FILE* file = NULL;
    if (info == NULL)
        printf("[Ошибка!]Сортировка: Файл не открыт!\n\n");
    else if (infoLinesCounter == 0)
        printf("[Ошибка!]Сортировка: Файл пуст!\n\n");
    else {
        if ((file = fopen("info.txt", "w")) != NULL) {
            INFORMATION tmp;
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
    if (info == NULL)
        printf("[Ошибка!]Поиск и фильтрация: Файл не открыт!\n\n");
    else if (infoLinesCounter == 0)
        printf("[Ошибка!]Поиск и фильтрация: Файл пуст!\n\n");
    else {
        int number = 0, isFounded = 0;
        do {
            number = inputCheck("Введите номер: ");
            if (number < 0)
                printf("[Ошибка!]Введите число больше 0!\n");
        } while (number < 0);
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
                isFounded = 1;
                break;
            }
        }
        if (isFounded == 0)
            printf("[Ошибка!]Нету участника с номером %i.\n\n", number);
    }
    system("pause");
}

void surnameSearch(INFORMATION* info) {
    if (info == NULL)
        printf("[Ошибка!]Поиск и фильтрация: Файл не открыт!\n\n");
    else if (infoLinesCounter == 0)
        printf("[Ошибка!]Поиск и фильтрация: Файл пуст!\n\n");
    else {
        int isAtLeastOneMember = 0;
        char *surname;
        printf("Введите фамилию: ");
        surname = limitedStringInput("Введите фамилию: ", 49);
        printf("Участники, с фамилией %s: ", surname);
        for (int i = 0; i < infoLinesCounter; i++) {
            if (strcmp((info + i)->fullname.surname, surname) == 0) {
                if (isAtLeastOneMember == 0) {
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
                isAtLeastOneMember = 1;
            }
            if (isAtLeastOneMember == 1 && i == infoLinesCounter - 1)
                printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
        }
        if (isAtLeastOneMember == 0)
            printf("[Ошибка!]Нет ни одного участника с фамилией %s.\n\n", surname);
    }
    system("pause");
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

void countrySearch(INFORMATION* info){
    if (info == NULL)
        printf("[Ошибка!]Файл не открыт!\n\n");
    else if (infoLinesCounter == 0)
        printf("[Ошибка!]Файл пуст!\n\n");
    else {
        int isAtLeastOneMember = 0;
        char *country;
        printf("Введите страну: ");
        country = limitedStringInput("Введите страну: ", 49);
        printf("Участники, из страны %s: ", country);
        for (int i = 0; i < infoLinesCounter; i++) {
            if (strcmp((info + i)->country,country) == 0) {
                if (isAtLeastOneMember == 0) {
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
                isAtLeastOneMember = 1;
            }
            if (isAtLeastOneMember == 1 && i == infoLinesCounter - 1)
                printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
        }
        if (isAtLeastOneMember == 0)
            printf("[Ошибка!]Нет ни одного участника из страны %s.\n\n", country);
    }
    system("pause");
}

void categorySearch(INFORMATION* info){
    if (info == NULL)
        printf("[Ошибка!]Файл не открыт!\n\n");
    else if (infoLinesCounter == 0)
        printf("[Ошибка!]Файл пуст!\n\n");
    else {
        int isAtLeastOneMember = 0;
        char *category;
        printf("Введите разряд: ");
        category = limitedStringInput("Введите разряд: ", 49);
        printf("Участники, с разрядом %s: ", category);
        for (int i = 0; i < infoLinesCounter; i++) {
            if (strcmp((info + i)->category,category) == 0) {
                if (isAtLeastOneMember == 0) {
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
                isAtLeastOneMember = 1;
            }
            if (isAtLeastOneMember == 1 && i == infoLinesCounter - 1)
                printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
        }
        if (isAtLeastOneMember == 0)
            printf("[Ошибка!]Нет ни одного участника с разрядом %s.\n\n", category);
    }
    system("pause");
}

void printTop(INFORMATION* info){
    system("cls");
    if (info == NULL)
        printf("[Ошибка!]Файл не открыт!\n\n");
    else if (infoLinesCounter == 0)
        printf("[Ошибка!]Файл пуст!\n\n");
    else {
        INFORMATION* infoCopy = NULL;
        infoCopy = (INFORMATION*)realloc(NULL,sizeof(INFORMATION)*infoLinesCounter);
        memcpy(infoCopy,info,sizeof(INFORMATION)*infoLinesCounter);
        INFORMATION tmp;
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