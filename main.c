#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#define TRUE 1
#define FALSE 0
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_RETURN 13
#define KEY_TAB 9
#define KEY_BKSP 8


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
int userEditMenu(USER* user, int i);
void printEditingUser(USER* user, int i);
void userPrint(USER* user);
INFORMATION* infoOpen(INFORMATION* info);
INFORMATION* infoAdd(INFORMATION* info);
INFORMATION* infoEdit(INFORMATION* info);
INFORMATION* infoDelete(INFORMATION *info);
int infoEditMenu(INFORMATION* info, int i);
void printEditingInfo(INFORMATION* info, int i);
void infoPrint(INFORMATION* info);
char* limitedStringInput(char* input, int limit,const char* inputText);
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
void indicateCursor(int status);


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    system("color 0B");
    INFORMATION *info = NULL;
    USER *user = NULL;
    user = userLoad(user);
    int adminSubMenuFlag = FALSE, userSubMenuFlag = FALSE;
    while (TRUE) {
        system("cls");
        switch (menu()) {
            case 1: {
                if (adminLogin(user) == TRUE) {
                    while (adminSubMenuFlag == FALSE) {
                        system("cls");
                        switch (adminSubmenu()) {
                            case 1: {
                                system("cls");
                                if (infoCheckFile() == FALSE) {
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
                            case 8: adminSubMenuFlag = TRUE; break;
                            default: break;
                        }
                        if (adminSubMenuFlag == TRUE) break;
                    }
                    adminSubMenuFlag = FALSE;
                }
                break;
            }
            case 2: {
                if (userLogin(user) == TRUE) {
                    while (userSubMenuFlag == FALSE) {
                        system("cls");
                        switch (userSubmenu()) {
                            case 1: {
                                system("cls");
                                if (infoCheckFile() == TRUE) {
                                    info = infoOpen(info);
                                }
                                break;
                            }
                            case 2: infoPrint(info); break;
                            case 3: printTop(info); break;
                            case 4: searchingAndFiltering(info); break;
                            case 5: userSubMenuFlag = TRUE; break;
                            default: break;
                        }
                        if (userSubMenuFlag == TRUE) break;
                    }
                    userSubMenuFlag = FALSE;
                }
                break;
            }
            case 3: free(info); free(user); return 0;
            default: break;
        }
    }
}

int menu(){
    int choice = 1, ch = ' ';
    char *line[] = {"Вход под администратором.", "Вход под пользователем.", "Выход.", NULL} , pointer = '>';
    indicateCursor(FALSE);
    while(1){
        if (ch != 0){
            system("cls");
            if (ch == KEY_RETURN) {
                indicateCursor(TRUE);
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
    char pointer = '>', *line[] = {"Создание/открытие файла.", "Добавление записи.", "Редактирование записи.", "Удаление записи.",
                     "Просмотр всех данных в табличной форме.", "Различные процедуры поиска и фильтрации данных.",
                     "Управление пользователями.", "Выход в меню.", NULL};
    indicateCursor(FALSE);
    while(1){
        if (ch != 0){
            system("cls");
            if (ch == KEY_RETURN) {
                indicateCursor(TRUE);
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
    indicateCursor(FALSE);
    while(1){
        if (ch != 0){
            system("cls");
            if (ch == KEY_RETURN) {
                indicateCursor(TRUE);
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
    int isLoginRight = FALSE, isPasswordRight = FALSE, i = 0, j = 0, counter = 0;
    char *login = NULL, password[30], ch;
    do {
        printf("Введите логин: ");
        login = limitedStringInput(login, 29, "Введите логин: ");
        for (i = 0; i < usersLinesCounter; i++)
            if (strcmp(login, (user + i)->login) == 0) {
                isLoginRight = TRUE;
                break;
            }
        if (isLoginRight == FALSE) {
            printf("[Ошибка!]Такого администратора не существует!\n\n");
            system("pause");
            return FALSE;
        }
    } while (isLoginRight != TRUE);
    do {
        j = 0;
        printf("Введите пароль: ");
        while (1) {
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
            isPasswordRight = TRUE;
        else printf("\n[Ошибка!]Неверный пароль!\n");
    } while (isPasswordRight != TRUE);
    if ((user + i)->isAdmin == 1) {
        printf("\nВы успешно авторизовались.\n\n");
        free(login);
        system("pause");
        return TRUE;
    }
    else {
        printf("\n[Ошибка!]Авторизация: Войдите через пользователя!\n\n");
        system("pause");
        free(login);
        return FALSE;
    }
}

int userLogin(USER *user) {
    system("cls");
    int isLoginRight = FALSE, isPasswordRight = FALSE, i = 0, j = 0, counter = 0;
    char *login = NULL, password[30], ch;
    do {
        printf("Введите логин: ");
        login = limitedStringInput(login, 29, "Введите логин: ");
        for (i = 0; i < usersLinesCounter; i++)
            if (strcmp(login, (user + i)->login) == 0) {
                isLoginRight = TRUE;
                break;
            }
        if (isLoginRight == FALSE) {
            printf("[Ошибка!]Такого пользователя не существует!\n\n");
            system("pause");
            free(login);
            return FALSE;
        }
    } while (isLoginRight != TRUE);
    do {
        j = 0;
        printf("Введите пароль: ");
        while (1) {
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
            isPasswordRight = TRUE;
        else printf("\n[Ошибка!]Неверный пароль!\n");
    } while (isPasswordRight != TRUE);
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

int userManagementMenu(){
    int choice = 1, ch = ' ';
    char pointer = '>', *line[] = {"Добавить аккаунт.", "Удалить аккаунт.", "Редактировать аккаунт.",
                                    "Просмотр всех аккаунтов.", "Назад.", NULL};
    indicateCursor(FALSE);
    while(1){
        if (ch != 0){
            system("cls");
            if (ch == KEY_RETURN) {
                indicateCursor(TRUE);
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
    } else if (usersLinesCounter == 0) {
        printf("[Ошибка!]Инициализация пользователей: Файл с логинами/пароля пуст!\n");
        system("pause");
        exit(0);
    } else {
        user = (USER*)malloc(usersLinesCounter*(sizeof(USER)));
        for (int i = 0; i < usersLinesCounter; i++)
            fscanf(file, "%s %s %i", (user + i)->login, (user + i)->password, &((user + i)->isAdmin));
        fclose(file);
    }
    return user;
}

USER* userAdd(USER* user) {
    user = (USER*)realloc(user, (usersLinesCounter + 1) * sizeof(USER));
    int loginIsNotExist = FALSE, i = 0;
    char *login = NULL, *password = NULL;
    FILE* file = NULL;
    printf("Добавить пользователя:\n");
    do {
        printf("Введите логин: ");
        login = limitedStringInput(login, 29, "Введите логин: ");
        strcpy((user + usersLinesCounter)->login, login);
        for (i = 0; i < usersLinesCounter; i++) {
            if (strcmp((user + i)->login, (user + usersLinesCounter)->login) == 0) {
                printf("[Ошибка!]Этот аккаунт уже существует!\n");
                loginIsNotExist = FALSE;
                break;
            } else loginIsNotExist = TRUE;
        }
    } while ((loginIsNotExist != TRUE));
    free(login);
    printf("Введите пароль: ");
    password = limitedStringInput(password, 29, "Введите пароль: ");
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
    printf("------------------------------------------------------------------------------------------------\n");
    printf("|№    |ЛОГИН:                         |ПАРОЛЬ:                         |ПРАВА АДМИНИСТРАТОРА: |\n");
    printf("------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < usersLinesCounter; i++) {
        printf("|%-5i|%-31s|%-32s|", i + 1, (user + i)->login, (user + i)->password);
        if ((user + i)->isAdmin == 1)
            printf("%-22s|", yes);
        else printf("%-22s|", no);
        printf("\n");
    }
    printf("------------------------------------------------------------------------------------------------\n\n");
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
    int i = 0, loginIsExist = FALSE;
    FILE* file = NULL;
    printf("Удаление аккаунта.\n");
    do {
        printf("Введите логин аккаунта, который вы хотите удалить: ");
        login = limitedStringInput(login, 29, "Введите логин аккаунта, который вы хотите удалить: ");
        for (i = 0; i < usersLinesCounter; i++) {
            if (strcmp((user + i)->login, login) == 0) {
                loginIsExist = TRUE;
                break;
            }
        }
        if (loginIsExist == FALSE)
            printf("[Ошибка!]Такого аккаунта не существует!\n");
    } while (loginIsExist != TRUE);
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
    int i = 0, loginIsExist = FALSE, isNewLoginNotExist = FALSE, editFlag = FALSE;
    FILE* file = NULL;
    printf("------------------------------------------------------------------------------------------------\n");
    printf("|№    |ЛОГИН:                         |ПАРОЛЬ:                         |ПРАВА АДМИНИСТРАТОРА: |\n");
    printf("------------------------------------------------------------------------------------------------\n");
    for (i = 0; i < usersLinesCounter; i++) {
        printf("|%-5i|%-31s|%-32s|", i + 1, (user + i)->login, (user + i)->password);
        if ((user + i)->isAdmin == 1)
            printf("%-22s|", yes);
        else printf("%-22s|", no);
        printf("\n");
    }
    printf("------------------------------------------------------------------------------------------------\n\n");
    do {
        printf("Введите логин аккаунта, который вы хотите отредактировать: ");
        login = limitedStringInput(login, 29, "Введите логин аккаунта, который вы хотите отредактировать: ");
        for (i = 0; i < usersLinesCounter; i++) {
            if (strcmp((user + i)->login, login) == 0) {
                loginIsExist = TRUE;
                break;
            } else loginIsExist = FALSE;
        }
        if (loginIsExist == FALSE)
            printf("[Ошибка!]Такого аккаунта не существует!\n");
    } while (loginIsExist != TRUE);
    free(login);
    while (editFlag == FALSE) {
        switch (userEditMenu(user,i)) {
            case 1: {
                printf("Изменить логин.\n");
                do {
                    printf("Введите новый логин: ");
                    newLogin = limitedStringInput(newLogin, 29, "Введите новый логин: ");
                    for (int j = 0; j < usersLinesCounter; j++) {
                        if (strcmp((user + j)->login, newLogin) == 0) {
                            isNewLoginNotExist = FALSE;
                            break;
                        }
                        else isNewLoginNotExist = TRUE;
                    }
                    if (isNewLoginNotExist == FALSE)
                        printf("[Ошибка!]Такой логин уже существует!\n");
                } while (isNewLoginNotExist == FALSE);
                strcpy((user + i)->login, newLogin);
                printEditingUser(user, i);
                printf("Логин успешно изменен!\n\n");
                free(newLogin);
                system("pause");
                break;
            }
            case 2: {
                printf("Изменение пароля.\n");
                printf("Введите новый пароль: ");
                newPassword = limitedStringInput(newPassword, 29, "Введите новый пароль: ");
                strcpy((user + i)->password, newPassword);
                printEditingUser(user, i);
                printf("Пароль успешно изменен!\n\n");
                free(newPassword);
                system("pause");
                break;
            }
            case 3: {
                if ((user + i)->isAdmin == 1) {
                    (user + i)->isAdmin = 0;
                    printEditingUser(user, i);
                    printf("Права администратора успешно изменены.\n\n");
                    system("pause");
                    break;
                }
                else {
                    (user + i)->isAdmin = 1;
                    printEditingUser(user, i);
                    printf("Права администратора успешно изменены.\n\n");
                    system("pause");
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
    }
    else printf("[Ошибка!]Редактирование пользователей: Не удалось открыть файл с логинами/паролями! Пользователь не отредактирован! Файл отчищен!\n\n");
    return user;
}

void printEditingUser(USER* user, int i){
    char yes[] = "Да", no[] = "Нет";
    system("cls");
    printf("-----------------------------------------------------------------------------------------\n");
    printf("|ЛОГИН:                         |ПАРОЛЬ:                         |ПРАВА АДМИНИСТРАТОРА: |\n");
    printf("-----------------------------------------------------------------------------------------\n");
    printf("|%-31s|%-32s|", (user + i)->login, (user + i)->password);
    if ((user + i)->isAdmin == 1)
        printf("%-22s|", yes);
    else printf("%-22s|", no);
    printf("\n-----------------------------------------------------------------------------------------\n\n");
}

int userEditMenu(USER* user, int i){
    int choice = 1, ch = ' ';
    char pointer = '>', *line[] = {"Изменить логин.", "Изменить пароль.", "Изменить права администратора.",
                                    "Выход из меню редактирования аккунтов.", NULL};
    while (TRUE) {
        if (ch != 0) {
            printEditingUser(user, i);
            indicateCursor(FALSE);
            if (ch == KEY_RETURN) {
                indicateCursor(TRUE);
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
            printf("|%-3i  |%-15s %-15s %-15s|%-10s|  %02i/%02i/%04i  |  %-3i  |%-10s|%-10s|%-4i|   %02i:%02i   |\n",
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
        int isExist = FALSE;
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
                    isExist = TRUE;
                    break;
                } else isExist = FALSE;
            }
            if (isExist == TRUE) printf("Участник с таким номером уже существует!\n");
        } while (isExist == TRUE);
        printf("Введите имя участника: ");
        firstname = limitedStringInput(firstname, 49, "Введите имя участника: ");
        strcpy((info + infoLinesCounter)->fullname.firstname, firstname);
        free(firstname);
        printf("Введите фамилию участника: ");
        surname = limitedStringInput(surname, 49, "Введите фамилию участника: ");
        strcpy((info + infoLinesCounter)->fullname.surname, surname);
        free(surname);
        printf("Введите отчество участника: ");
        lastname = limitedStringInput(lastname, 49, "Введите отчество участника: ");
        strcpy((info + infoLinesCounter)->fullname.lastname, lastname);
        free(lastname);
        printf("Введите страну учатника: ");
        country = limitedStringInput(country, 29, "Введите страну учатника: ");
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
        category = limitedStringInput(category, 29, "Введите разряд участника: ");
        strcpy((info + infoLinesCounter)->category, category);
        free(category);
        printf("Введите модель коньков участника: ");
        model = limitedStringInput(model, 29, "Введите модель коньков участника: ");
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

int infoEditMenu(INFORMATION* info, int i){
    int choice = 1, ch = ' ';
    char pointer = '>', *line[] = {"Изменение номера участника.", "Изменение имени участника.",
                                     "Изменение фамилии участника.", "Изменение отчества участника.",
                                     "Изменение страны участника.", "Изменение дня рождения участника.",
                                     "Изменение месяца рождения участника.", "Изменение года рождения участника.",
                                     "Изменение разряда участника.", "Изменение модели коньков участника.",
                                     "Изменение количества очков участника.", "Изменение минут круга участника.",
                                     "Изменение секунд круга участника.", "Выход из меню редактирования участника.", NULL};
    while (TRUE) {
        if (ch != 0) {
            printEditingInfo(info, i);
            indicateCursor(FALSE);
            if (ch == KEY_RETURN) {
                indicateCursor(TRUE);
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

void printEditingInfo(INFORMATION* info, int i){
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

INFORMATION* infoEdit(INFORMATION* info) {
    if (info == NULL) {
        printf("[Ошибка!]Редактирование информации: Файл не открыт!\n\n");
        system("pause");
    }
    else if (infoLinesCounter == 0) {
        printf("[Ошибка!]Редактирование информации: Файл пуст!\n\n");
        system("pause");
    }
    else {
        time_t t = time(NULL);
        FILE *file = NULL;
        struct tm *aTm = localtime(&t);
        int number = 0, isExist = FALSE, i = 0, j = 0, isNumberExist = FALSE, infoEditFlag = FALSE;
        char *firstname = NULL, *surname = NULL, *lastname = NULL, *country = NULL, *category = NULL, *model = NULL;
        printf("--------------------------------------------------------------------------------------------------------------------------------\n");
        printf("|НОМЕР|ИМЯ             ФАМИЛИЯ         ОТЧЕСТВО       |  СТРАНА  |ДАТА  РОЖДЕНИЯ|ВОЗРАСТ|  РАЗРЯД  |  МОДЕЛЬ  |ОЧКИ|ВРЕМЯ КРУГА|\n");
        printf("--------------------------------------------------------------------------------------------------------------------------------\n");
        for (j = 0; j < infoLinesCounter; j++) {
            printf("|%-3i  |%-15s %-15s %-15s|%-10s|  %02i/%02i/%04i  |  %-3i  |%-10s|%-10s|%-4i|   %02i:%02i   |\n",
                   (info + j)->number, (info + j)->fullname.firstname, (info + j)->fullname.surname, (info + j)->fullname.lastname, (info + j)->country,
                   (info + j)->dateOfBirth.day, (info + j)->dateOfBirth.month, (info + j)->dateOfBirth.year, (info + j)->dateOfBirth.age, (info + j)->category,
                   (info + j)->model, (info + j)->points, (info + j)->timeOfLap.minutes, (info + j)->timeOfLap.seconds);
        }
        printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
        do {
            number = inputCheck("Введите номер участника, которого нужно отредактировать: ");
            for (i = 0; i < infoLinesCounter; i++) {
                if ((info + i)->number == number) {
                    isExist = TRUE;
                    break;
                } else isExist = FALSE;
            }
            if (isExist == FALSE) printf("[Ошибка!]Участника с таким номером не существует!\n");
        } while (isExist == FALSE);
        while (infoEditFlag == FALSE) {
            switch (infoEditMenu(info,i)) {
                case 1: {
                    int newNumber = 0;
                    printf("Изменеие номера участника.\n");
                    do {
                        do {
                            newNumber = inputCheck("Введите новый номер участника: ");
                            if (newNumber < 1)
                                printf("[Ошибка!]Введите число больше 0!\n");
                        } while (newNumber < 1);
                        for (j = 0; j < infoLinesCounter; j++) {
                            if ((info + j)->number == newNumber) {
                                isNumberExist = TRUE;
                                break;
                            } else isNumberExist = FALSE;
                        }
                        if (isNumberExist == TRUE)
                            printf("[Ошибка!]Участник с таким номером уже существует!\n");
                    } while (isNumberExist == TRUE);
                    (info + i)->number = newNumber;
                    printEditingInfo(info,i);
                    printf("Номер участника успешно изменен!\n\n");
                    system("pause");
                    break;
                }
                case 2: {
                    printf("Изменение имени участника.\n");
                    printf("Введите новое имя участника: ");
                    firstname = limitedStringInput(firstname, 49, "Введите новое имя участника: ");
                    strcpy((info + i)->fullname.firstname, firstname);
                    free(firstname);
                    printEditingInfo(info,i);
                    printf("Имя участника успешно изменено!\n\n");
                    system("pause");
                    break;
                }
                case 3: {
                    printf("Изменение фамилии участника.\n");
                    printf("Введите новую фамилию участника: ");
                    surname = limitedStringInput(surname, 49, "Введите новую фамилию участника: ");
                    strcpy((info + i)->fullname.surname, surname);
                    free(surname);
                    printEditingInfo(info,i);
                    printf("Фамилия участника успешна изменена!\n\n");
                    system("pause");
                    break;
                }
                case 4: {
                    printf("Изменение отчества участника.\n");
                    printf("Введите новое отчество участника: ");
                    lastname = limitedStringInput(lastname, 49, "Введите новое отчество участника: ");
                    strcpy((info + i)->fullname.lastname, lastname);
                    free(lastname);
                    printEditingInfo(info,i);
                    printf("Отчество участника успешно изменено!\n\n");
                    system("pause");
                    break;
                }
                case 5: {
                    printf("Изменение страны участника.\n");
                    printf("Введите новую страну участника: ");
                    country = limitedStringInput(country, 29, "Введите новую страну участника: ");
                    strcpy((info + i)->country, country);
                    free(country);
                    printEditingInfo(info,i);
                    printf("Страна участника успешно изменена.\n\n");
                    system("pause");
                    break;
                }
                case 6: {
                    printf("Изменение дня рождения участника.\n");
                    int newBirthDay = 0;
                    do {
                        printf("Введите новый день рождения участника: ");
                        scanf_s("%i", &newBirthDay);
                        if (newBirthDay < 1 || newBirthDay > 31)
                            printf("[Ошибка!]Введите число от 1 до 31!\n");
                    } while (newBirthDay < 1 || newBirthDay > 31);
                    (info + i)->dateOfBirth.day = newBirthDay;
                    printEditingInfo(info,i);
                    printf("День рождения участника успешно изменен!\n\n");
                    system("pause");
                    break;
                }
                case 7: {
                    printf("Изменение месяца рождения участника.\n");
                    int newBirthMonth = 0;
                    do {
                        newBirthMonth = inputCheck("Введите новый месяц рождения участника(числом): ");
                        if (newBirthMonth < 1 || newBirthMonth > 12)
                            printf("[Ошибка!]Введите число от 1 до 12!\n\n");
                    } while (newBirthMonth < 1 || newBirthMonth > 12);
                    (info + i)->dateOfBirth.month = newBirthMonth;
                    printEditingInfo(info,i);
                    printf("Месяц рождения участника успешно изменен!\n\n");
                    system("pause");
                    break;
                }
                case 8: {
                    printf("Изменение года рождения участника.\n");
                    int newBirthYear = 0;
                    do {
                        newBirthYear = inputCheck("Введите новый год рождения участника: ");
                        if (newBirthYear < 1900 || newBirthYear > 2019)
                            printf("[Ошибка!]Введите число от 1900 до 2019!\n");
                    } while (newBirthYear < 1900 || newBirthYear > 2019);
                    (info + i)->dateOfBirth.year = newBirthYear;
                    if ((info + i)->dateOfBirth.month >= aTm->tm_mon + 1)
                        (info + i)->dateOfBirth.age = 2018 - (info + i)->dateOfBirth.year;
                    else
                        (info + i)->dateOfBirth.age = 2019 - (info + i)->dateOfBirth.year;
                    printEditingInfo(info,i);
                    printf("Год рождения участника успешно изменен!\n\n");
                    system("pause");
                    break;
                }
                case 9: {
                    printf("Изменение разряда участника.\n");
                    printf("Введите новый разряд участника: ");
                    category = limitedStringInput(category, 29, "Введите новый разряд участника: ");
                    strcpy((info + i)->category, category);
                    free(category);
                    printEditingInfo(info,i);
                    printf("Разряд участника успешно изменен!\n\n");
                    system("pause");
                    break;
                }
                case 10: {
                    printf("Изменение модели коньков участника.\n");
                    printf("Введите новую модель коньков участника: ");
                    model = limitedStringInput(model, 29, "Введите новую модель коньков участника: ");
                    strcpy((info + i)->model, model);
                    free(model);
                    printEditingInfo(info,i);
                    printf("Модель коньков участника успешно изменена!\n\n");
                    system("pause");
                    break;
                }
                case 11: {
                    printf("Изменение количества очков участника.\n");
                    do {
                        (info + i)->points = inputCheck("Введите новое количество очков участника: ");
                        if ((info + i)->points < 0 || (info + i)->points > 9999)
                            printf("[Ошибка!]Введите число от 0 до 9999!\n");
                    } while ((info + i)->points < 0 || (info + i)->points > 9999);
                    printEditingInfo(info,i);
                    printf("Количество очков участника успешно изменено!\n\n");
                    system("pause");
                    break;
                }
                case 12: {
                    printf("Изменение минут круга участника.\n");
                    do {
                        (info + i)->timeOfLap.minutes = inputCheck("Введите новые минуты круга участника: ");
                        if ((info + i)->timeOfLap.minutes < 0 ||
                            (info + i)->timeOfLap.minutes > 59)
                            printf("[Ошибка!]Введите число от 0 до 59!\n");
                    } while ((info + i)->timeOfLap.minutes < 0 ||
                             (info + i)->timeOfLap.minutes > 59);
                    printEditingInfo(info,i);
                    printf("Минуты круга участника успешно изменены!\n\n");
                    system("pause");
                    break;
                }
                case 13: {
                    printf("Изменение секунд круга участника.\n");
                    do {
                        (info + i)->timeOfLap.seconds = inputCheck("Введите новые секунды круга участника: ");
                        if ((info + i)->timeOfLap.seconds < 0 ||
                            (info + i)->timeOfLap.seconds > 59)
                            printf("[Ошибка!]Введите число от 0 до 59!\n");
                    } while ((info + i)->timeOfLap.seconds < 0 ||
                             (info + i)->timeOfLap.seconds > 59);
                    printEditingInfo(info,i);
                    printf("Секунды круга участника успешно изменены!\n\n");
                    system("pause");
                    break;
                }
                case 14:
                    infoEditFlag = TRUE;
                    break;
                default:
                    break;
            }
            if (infoEditFlag == TRUE) break;
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
    return info;
}

INFORMATION* infoDelete(INFORMATION *info) {
    if (info == NULL) {
        printf("[Ошибка!]Удаление информации: Файл не открыт!\n\n");
    } else if (infoLinesCounter == 0) {
        printf("[Ошибка!]Удаление информации: Файл пуст!\n\n");
    } else {
        int delNumber = 0, isNumberExist = FALSE, i = 0;
        FILE *file = NULL;
        printf("Удаление участника.\n");
        do {
            delNumber = inputCheck("Введите номер участника для удаления: ");
            for (i = 0; i < infoLinesCounter; i++) {
                if (delNumber == (info + i)->number) {
                    isNumberExist = TRUE;
                    break;
                } else isNumberExist = FALSE;
            }
            if (isNumberExist == FALSE) printf("[Ошибка!]Участника с таким номером не существует!\n");
        } while (isNumberExist != TRUE);
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
        char *buffer = NULL;
        int numberEntered = 0, i = 0, check = 0, isNumeral = FALSE, flag = FALSE;
        printf("%s", inputText);
        buffer = limitedStringInput(buffer, 99,"");
        while (buffer[i] != '\0') {
            if (buffer[i] == '-' && flag == FALSE) {
                i++;
                flag = TRUE;
            }
            check = isdigit((unsigned char)buffer[i]);
            if (check == 0) {
                isNumeral = FALSE;
                break;
            }
            else isNumeral = TRUE;
            i++;
        }
        if (isNumeral == TRUE) {
            numberEntered = strtol(buffer, NULL, 10);
            free(buffer);
            return numberEntered;
        }
        else printf("[Ошибка!]Не правильный ввод!\n");
    }
}

char* limitedStringInput(char* input, int limit,const char* inputText) {
    char ch;
    int i = 0;
    input = (char*)realloc(NULL, sizeof(char)*(limit + 1));
    while (TRUE) {
        ch = (char)_getch();
        if (ch != '\0') {
            if (ch == 13 || ch == 9) {
                if (i > 0){
                    input[i] = '\0';
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
                    input[i++] = ch;
                    putchar(ch);
                }
            }
        }
    }
    return input;
}

int searchAndFilteringMenu(){
    int choice = 1, ch = ' ';
    char pointer = '>', *line[] = {"Фильтр по количеству очков.", "Фильтр по времени круга.",
                                     "Фильтр по возрасту.", "Фильтр по году рождения.", "Поиск по номеру.",
                                     "Поиск по фамилии.", "Поиск по стране.", "Поиск по разряду.",
                                     "Сортировка по времени круга.", "Выход.", NULL};
    while (TRUE) {
        if (ch != 0) {
            system("cls");
            indicateCursor(FALSE);
            if (ch == KEY_RETURN) {
                indicateCursor(TRUE);
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

void pointsFilter(INFORMATION* info) {
    if (info == NULL)
        printf("[Ошибка!]Поиск и фильтрация: Файл не открыт!\n\n");
    else if (infoLinesCounter == 0)
        printf("[Ошибка!]Поиск и фильтрация: Файл пуст!\n\n");
    else {
        int points = 0, isAtLeastOneMember = FALSE;
        do {
            points = inputCheck("Введите количество очков: ");
            if (points < 0 || points > 9999)
                printf("[Ошибка!]Введите число больше 0 и меньше 9999!\n");
        } while (points < 0 || points > 9999);
        system("cls");
        printf("Участники, у которых очков больше %i: ", points);
        for (int i = 0; i < infoLinesCounter; i++) {
            if ((info + i)->points > points) {
                if (isAtLeastOneMember == FALSE) {
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
                isAtLeastOneMember = TRUE;
            }
            if (isAtLeastOneMember == TRUE && i == infoLinesCounter - 1)
                printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
        }
        if (isAtLeastOneMember == FALSE)
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
        int minutesOfLap = 0, secondsOfLap = 0, isAtLeastOneMember = FALSE;
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
        system("cls");
        printf("Участники, у которых время круга меньше %02i:%02i : ", minutesOfLap, secondsOfLap);
        for (int i = 0; i < infoLinesCounter; i++) {
            if ((info + i)->timeOfLap.minutes < minutesOfLap)
                if ((info + i)->timeOfLap.seconds <
                    ((info + i)->timeOfLap.minutes == minutesOfLap ? secondsOfLap : 60)) {
                    if (isAtLeastOneMember == FALSE) {
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
                    isAtLeastOneMember = TRUE;
                }
            if (isAtLeastOneMember == TRUE && i == infoLinesCounter - 1)
                printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
        }
        if (isAtLeastOneMember == FALSE)
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
        int age = 0, isAtLeastOneMember = FALSE;
        do {
            age = inputCheck("Введите возраст: ");
            if (age < 0 || age > 119)
                printf("[Ошибка!]Введите число больше 0 и меньше 119!\n");
        } while (age < 0 || age > 119);
        system("cls");
        printf("Участники, возраст которых больше %i: ", age);
        for (int i = 0; i < infoLinesCounter; i++) {
            if ((info + i)->dateOfBirth.age > age) {
                if (isAtLeastOneMember == FALSE) {
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
                isAtLeastOneMember = TRUE;
            }
            if (isAtLeastOneMember == TRUE && i == infoLinesCounter - 1)
                printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
        }
        if (isAtLeastOneMember == FALSE)
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
        int yearOfBirth = 0, isAtLeastOneMember = FALSE;
        do {
            yearOfBirth = inputCheck("Введите год рождения: ");
            if (yearOfBirth < 1900 || yearOfBirth > 2019)
                printf("[Ошибка!]Введите число больше 1900 и меньше 2019!\n");
        } while (yearOfBirth < 1900 || yearOfBirth > 2019);
        system("cls");
        printf("Участники, год рождения у которых больше %i: ", yearOfBirth);
        for (int i = 0; i < infoLinesCounter; i++) {
            if ((info + i)->dateOfBirth.year > yearOfBirth) {
                if (isAtLeastOneMember == FALSE) {
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
                isAtLeastOneMember = TRUE;
            }
            if (isAtLeastOneMember == TRUE && i == infoLinesCounter - 1) {
                printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
            }
        }
        if (isAtLeastOneMember == FALSE)
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
        int number = 0, isFounded = FALSE;
        do {
            number = inputCheck("Введите номер: ");
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
                isFounded = TRUE;
                break;
            }
        }
        if (isFounded == FALSE)
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
        int isAtLeastOneMember = FALSE;
        char *surname = NULL;
        printf("Введите фамилию: ");
        surname = limitedStringInput(surname, 49, "Введите фамилию: ");
        system("cls");
        printf("Участники, с фамилией %s: ", surname);
        for (int i = 0; i < infoLinesCounter; i++) {
            if (strcmp((info + i)->fullname.surname, surname) == 0) {
                if (isAtLeastOneMember == FALSE) {
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
                isAtLeastOneMember = TRUE;
            }
            if (isAtLeastOneMember == TRUE && i == infoLinesCounter - 1)
                printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
        }
        if (isAtLeastOneMember == FALSE)
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
        printf("[Ошибка!]Поиск и фильтрация: Файл не открыт!\n\n");
    else if (infoLinesCounter == 0)
        printf("[Ошибка!]Поиск и фильтрация: Файл пуст!\n\n");
    else {
        int isAtLeastOneMember = FALSE;
        char *country = NULL;
        printf("Введите страну: ");
        country = limitedStringInput(country, 49, "Введите страну: ");
        system("cls");
        printf("Участники, из страны %s: ", country);
        for (int i = 0; i < infoLinesCounter; i++) {
            if (strcmp((info + i)->country,country) == 0) {
                if (isAtLeastOneMember == FALSE) {
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
                isAtLeastOneMember = TRUE;
            }
            if (isAtLeastOneMember == TRUE && i == infoLinesCounter - 1)
                printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
        }
        if (isAtLeastOneMember == FALSE)
            printf("[Ошибка!]Нет ни одного участника из страны %s.\n\n", country);
    }
    system("pause");
}

void categorySearch(INFORMATION* info){
    if (info == NULL)
        printf("[Ошибка!]Поиск и фильтрация: Файл не открыт!\n\n");
    else if (infoLinesCounter == 0)
        printf("[Ошибка!]Поиск и фильтрация: Файл пуст!\n\n");
    else {
        int isAtLeastOneMember = FALSE;
        char *category = NULL;
        printf("Введите разряд: ");
        category = limitedStringInput(category, 49, "Введите разряд: ");
        system("cls");
        printf("Участники, с разрядом %s: ", category);
        for (int i = 0; i < infoLinesCounter; i++) {
            if (strcmp((info + i)->category,category) == 0) {
                if (isAtLeastOneMember == FALSE) {
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
                isAtLeastOneMember = TRUE;
            }
            if (isAtLeastOneMember == TRUE && i == infoLinesCounter - 1)
                printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
        }
        if (isAtLeastOneMember == FALSE)
            printf("[Ошибка!]Нет ни одного участника с разрядом %s.\n\n", category);
    }
    system("pause");
}

void printTop(INFORMATION* info){
    system("cls");
    if (info == NULL)
        printf("[Ошибка!]Поиск и фильтрация: Файл не открыт!\n\n");
    else if (infoLinesCounter == 0)
        printf("[Ошибка!]Поиск и фильтрация: Файл пуст!\n\n");
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

void indicateCursor(int status) {
    void* hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(hConsole, &structCursorInfo);
    structCursorInfo.bVisible = status;
    SetConsoleCursorInfo(hConsole, &structCursorInfo);
}