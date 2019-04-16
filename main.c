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
    char *line[] = {"���� ��� ���������������.", "���� ��� �������������.", "�����.", NULL} , pointer = '>';
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
            printf("����:\n");
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
    char pointer = '>', *line[] = {"��������/�������� �����.", "���������� ������.", "�������������� ������.", "�������� ������.",
                     "�������� ���� ������ � ��������� �����.", "��������� ��������� ������ � ���������� ������.",
                     "���������� ��������������.", "����� � ����.", NULL};
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
            printf("�������(��� ���������������):\n");
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
    char pointer = '>', *line[] = {"�������� ����� � �������.", "�������� ���� ������ � ��������� �����.",
                                    "�������� ���-3 ����� ������� ����������.", "��������� ��������� ������ � ���������� ������.",
                                    "����� � ����.", NULL};
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
            printf("�������(��� �������������):\n");
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
        printf("������� �����: ");
        login = limitedStringInput(login, 29, "������� �����: ");
        for (i = 0; i < usersLinesCounter; i++)
            if (strcmp(login, (user + i)->login) == 0) {
                isLoginRight = TRUE;
                break;
            }
        if (isLoginRight == FALSE) {
            printf("[������!]������ �������������� �� ����������!\n\n");
            system("pause");
            return FALSE;
        }
    } while (isLoginRight != TRUE);
    do {
        j = 0;
        printf("������� ������: ");
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
        else printf("\n[������!]�������� ������!\n");
    } while (isPasswordRight != TRUE);
    if ((user + i)->isAdmin == 1) {
        printf("\n�� ������� ��������������.\n\n");
        free(login);
        system("pause");
        return TRUE;
    }
    else {
        printf("\n[������!]�����������: ������� ����� ������������!\n\n");
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
        printf("������� �����: ");
        login = limitedStringInput(login, 29, "������� �����: ");
        for (i = 0; i < usersLinesCounter; i++)
            if (strcmp(login, (user + i)->login) == 0) {
                isLoginRight = TRUE;
                break;
            }
        if (isLoginRight == FALSE) {
            printf("[������!]������ ������������ �� ����������!\n\n");
            system("pause");
            free(login);
            return FALSE;
        }
    } while (isLoginRight != TRUE);
    do {
        j = 0;
        printf("������� ������: ");
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
        else printf("\n[������!]�������� ������!\n");
    } while (isPasswordRight != TRUE);
    if ((user + i)->isAdmin == 0) {
        printf("\n�� ������� ��������������.\n\n");
        free(login);
        system("pause");
        return 1;
    }
    else {
        printf("\n[������!]�����������! ������� ����� ��������������!\n\n");
        system("pause");
        free(login);
        return 0;
    }
}

int userManagementMenu(){
    int choice = 1, ch = ' ';
    char pointer = '>', *line[] = {"�������� �������.", "������� �������.", "������������� �������.",
                                    "�������� ���� ���������.", "�����.", NULL};
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
            printf("���� ���������� ��������������/����������������:\n");
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
            printf("[������!]������������� �������������: �� ������� ������� ���� � ��������/��������!\n");
            system("pause");
            exit(0);
        }
    } else if (usersLinesCounter == 0) {
        printf("[������!]������������� �������������: ���� � ��������/������ ����!\n");
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
    printf("�������� ������������:\n");
    do {
        printf("������� �����: ");
        login = limitedStringInput(login, 29, "������� �����: ");
        strcpy((user + usersLinesCounter)->login, login);
        for (i = 0; i < usersLinesCounter; i++) {
            if (strcmp((user + i)->login, (user + usersLinesCounter)->login) == 0) {
                printf("[������!]���� ������� ��� ����������!\n");
                loginIsNotExist = FALSE;
                break;
            } else loginIsNotExist = TRUE;
        }
    } while ((loginIsNotExist != TRUE));
    free(login);
    printf("������� ������: ");
    password = limitedStringInput(password, 29, "������� ������: ");
    strcpy((user + usersLinesCounter)->password, password);
    free(password);
    do {
        (user + usersLinesCounter)->isAdmin = inputCheck("�������������?(1 - ��|0 - ���): ");
        if ((user + usersLinesCounter)->isAdmin < 0 || (user + usersLinesCounter)->isAdmin > 1) {
            printf("[������!]�� ���������� ����!\n");
        }
    } while ((user + usersLinesCounter)->isAdmin < 0 || (user + usersLinesCounter)->isAdmin > 1);
    if ((file = fopen("db.txt", "at+")) != NULL) {
        fprintf(file, "%s %s %i\n", (user + usersLinesCounter)->login, (user + usersLinesCounter)->password,
                (user + usersLinesCounter)->isAdmin);
        fclose(file);
        printf("������� ������� ��������!\n\n");
        _flushall();
        usersLinesCounter++;
    } else printf("[������!]���������� �������������: ������ �������� ����� � ��������/��������! ������������ �� ��������!\n\n");
    system("pause");
    return user;
}

void userPrint(USER* user) {
    system("cls");
    char yes[] = "��", no[] = "���";
    printf("------------------------------------------------------------------------------------------------\n");
    printf("|�    |�����:                         |������:                         |����� ��������������: |\n");
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
    printf("�������� ��������.\n");
    do {
        printf("������� ����� ��������, ������� �� ������ �������: ");
        login = limitedStringInput(login, 29, "������� ����� ��������, ������� �� ������ �������: ");
        for (i = 0; i < usersLinesCounter; i++) {
            if (strcmp((user + i)->login, login) == 0) {
                loginIsExist = TRUE;
                break;
            }
        }
        if (loginIsExist == FALSE)
            printf("[������!]������ �������� �� ����������!\n");
    } while (loginIsExist != TRUE);
    free(login);
    if ((file = fopen("db.txt", "w")) != NULL) {
        for(int j = i; j < usersLinesCounter; j++)
            *(user + j) = *(user + (j + 1));
        user = (USER*)realloc(user, sizeof(USER)*usersLinesCounter);
        usersLinesCounter--;
        for (int j = 0; j < usersLinesCounter; j++)
            fprintf(file, "%s %s %i\n", (user + j)->login, (user + j)->password, (user + j)->isAdmin);
        printf("������� ������� �����!\n\n");
        fclose(file);
    } else printf("[������!]�������� �������������: ������ �������� ����� � ��������/��������! ������������ �� ������! ���� �������!\n\n");
    system("pause");
    return user;
}

USER* userEdit(USER* user) {
    char *login = NULL, *newLogin = NULL, *newPassword = NULL, yes[] = "��", no[] = "���";
    int i = 0, loginIsExist = FALSE, isNewLoginNotExist = FALSE, editFlag = FALSE;
    FILE* file = NULL;
    printf("------------------------------------------------------------------------------------------------\n");
    printf("|�    |�����:                         |������:                         |����� ��������������: |\n");
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
        printf("������� ����� ��������, ������� �� ������ ���������������: ");
        login = limitedStringInput(login, 29, "������� ����� ��������, ������� �� ������ ���������������: ");
        for (i = 0; i < usersLinesCounter; i++) {
            if (strcmp((user + i)->login, login) == 0) {
                loginIsExist = TRUE;
                break;
            } else loginIsExist = FALSE;
        }
        if (loginIsExist == FALSE)
            printf("[������!]������ �������� �� ����������!\n");
    } while (loginIsExist != TRUE);
    free(login);
    while (editFlag == FALSE) {
        switch (userEditMenu(user,i)) {
            case 1: {
                printf("�������� �����.\n");
                do {
                    printf("������� ����� �����: ");
                    newLogin = limitedStringInput(newLogin, 29, "������� ����� �����: ");
                    for (int j = 0; j < usersLinesCounter; j++) {
                        if (strcmp((user + j)->login, newLogin) == 0) {
                            isNewLoginNotExist = FALSE;
                            break;
                        }
                        else isNewLoginNotExist = TRUE;
                    }
                    if (isNewLoginNotExist == FALSE)
                        printf("[������!]����� ����� ��� ����������!\n");
                } while (isNewLoginNotExist == FALSE);
                strcpy((user + i)->login, newLogin);
                printEditingUser(user, i);
                printf("����� ������� �������!\n\n");
                free(newLogin);
                system("pause");
                break;
            }
            case 2: {
                printf("��������� ������.\n");
                printf("������� ����� ������: ");
                newPassword = limitedStringInput(newPassword, 29, "������� ����� ������: ");
                strcpy((user + i)->password, newPassword);
                printEditingUser(user, i);
                printf("������ ������� �������!\n\n");
                free(newPassword);
                system("pause");
                break;
            }
            case 3: {
                if ((user + i)->isAdmin == 1) {
                    (user + i)->isAdmin = 0;
                    printEditingUser(user, i);
                    printf("����� �������������� ������� ��������.\n\n");
                    system("pause");
                    break;
                }
                else {
                    (user + i)->isAdmin = 1;
                    printEditingUser(user, i);
                    printf("����� �������������� ������� ��������.\n\n");
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
    else printf("[������!]�������������� �������������: �� ������� ������� ���� � ��������/��������! ������������ �� ��������������! ���� �������!\n\n");
    return user;
}

void printEditingUser(USER* user, int i){
    char yes[] = "��", no[] = "���";
    system("cls");
    printf("-----------------------------------------------------------------------------------------\n");
    printf("|�����:                         |������:                         |����� ��������������: |\n");
    printf("-----------------------------------------------------------------------------------------\n");
    printf("|%-31s|%-32s|", (user + i)->login, (user + i)->password);
    if ((user + i)->isAdmin == 1)
        printf("%-22s|", yes);
    else printf("%-22s|", no);
    printf("\n-----------------------------------------------------------------------------------------\n\n");
}

int userEditMenu(USER* user, int i){
    int choice = 1, ch = ' ';
    char pointer = '>', *line[] = {"�������� �����.", "�������� ������.", "�������� ����� ��������������.",
                                    "����� �� ���� �������������� ��������.", NULL};
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
            printf("���� �������������� ���������:\n");
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
        printf("[������!]�������� ����������: ���� ��� �� ������!\n\n");
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
            printf("�������� ����������: ���� ������� ������!\n");
    fclose(file);
}

INFORMATION* infoOpen(INFORMATION* info) {
    if(info != NULL)
        printf("[������!]�������� ����������: ���� ��� ������!\n\n");
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
            printf("�������� ����������: ���� ������� ������!\n\n");
        }
    }
    system("pause");
    return info;
}

void infoPrint(INFORMATION* info) {
    system("cls");
    if (info == NULL)
        printf("[������!]����� ����������: ���� ��� �� ������!\n\n");
    else if (infoLinesCounter == 0)
        printf("[������!]����� ����������: ���� ����!\n\n");
    else {
        printf("--------------------------------------------------------------------------------------------------------------------------------\n");
        printf("|�����|���             �������         ��������       |  ������  |����  ��������|�������|  ������  |  ������  |����|����� �����|\n");
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
        printf("[������!]���������� ����������: ���� �� ������!\n\n");
    else if ((file = fopen("info.txt", "a+")) == NULL)
        printf("[������!]���������� ����������: �� ������� ������� ���� ��� ����������!\n");
    else {
        info = (INFORMATION *) realloc(info, ((infoLinesCounter + 1) * sizeof(INFORMATION)));
        time_t t = time(NULL);
        struct tm *aTm = localtime(&t);
        int isExist = FALSE;
        char *firstname = NULL, *surname = NULL, *lastname = NULL, *country = NULL, *category = NULL, *model = NULL;
        printf("���������� ���������.\n");
        do {
            do {
                (info + infoLinesCounter)->number = inputCheck("������� ����� ���������: ");
                if ((info + infoLinesCounter)->number < 1)
                    printf("[������!]������� ����� ������ 0!\n");
            } while ((info + infoLinesCounter)->number < 1);
            for (int i = 0; i < infoLinesCounter; i++) {
                if ((info + i)->number == (info + infoLinesCounter)->number) {
                    isExist = TRUE;
                    break;
                } else isExist = FALSE;
            }
            if (isExist == TRUE) printf("�������� � ����� ������� ��� ����������!\n");
        } while (isExist == TRUE);
        printf("������� ��� ���������: ");
        firstname = limitedStringInput(firstname, 49, "������� ��� ���������: ");
        strcpy((info + infoLinesCounter)->fullname.firstname, firstname);
        free(firstname);
        printf("������� ������� ���������: ");
        surname = limitedStringInput(surname, 49, "������� ������� ���������: ");
        strcpy((info + infoLinesCounter)->fullname.surname, surname);
        free(surname);
        printf("������� �������� ���������: ");
        lastname = limitedStringInput(lastname, 49, "������� �������� ���������: ");
        strcpy((info + infoLinesCounter)->fullname.lastname, lastname);
        free(lastname);
        printf("������� ������ ��������: ");
        country = limitedStringInput(country, 29, "������� ������ ��������: ");
        strcpy((info + infoLinesCounter)->country, country);
        free(country);
        do {
            (info + infoLinesCounter)->dateOfBirth.day = inputCheck("������� ���� �������� ���������: ");
            if ((info + infoLinesCounter)->dateOfBirth.day < 1 || (info + infoLinesCounter)->dateOfBirth.day > 31)
                printf("[������!]������� ����� �� 1 �� 31!\n");
        } while ((info + infoLinesCounter)->dateOfBirth.day < 1 || (info + infoLinesCounter)->dateOfBirth.day > 31);
        do {
            (info + infoLinesCounter)->dateOfBirth.month = inputCheck("������� ����� �������� ���������(������): ");
            if ((info + infoLinesCounter)->dateOfBirth.month < 1 || (info + infoLinesCounter)->dateOfBirth.month > 12)
                printf("[������!]������� ����� �� 1 �� 12!\n");
        } while ((info + infoLinesCounter)->dateOfBirth.month < 1 || (info + infoLinesCounter)->dateOfBirth.month > 12);
        do {
            (info + infoLinesCounter)->dateOfBirth.year = inputCheck("������� ��� �������� ���������: ");
            if ((info + infoLinesCounter)->dateOfBirth.year < 1900 ||
                (info + infoLinesCounter)->dateOfBirth.year > 2019)
                printf("[������!]������� ����� �� 1900 �� 2019!\n");
        } while ((info + infoLinesCounter)->dateOfBirth.year < 1900 ||
                 (info + infoLinesCounter)->dateOfBirth.year > 2019);
        if ((info + infoLinesCounter)->dateOfBirth.month > aTm->tm_mon + 1)
            (info + infoLinesCounter)->dateOfBirth.age = 2018 - (info + infoLinesCounter)->dateOfBirth.year;
        else (info + infoLinesCounter)->dateOfBirth.age = 2019 - (info + infoLinesCounter)->dateOfBirth.year;
        printf("������� ������ ���������: ");
        category = limitedStringInput(category, 29, "������� ������ ���������: ");
        strcpy((info + infoLinesCounter)->category, category);
        free(category);
        printf("������� ������ ������� ���������: ");
        model = limitedStringInput(model, 29, "������� ������ ������� ���������: ");
        strcpy((info + infoLinesCounter)->model, model);
        free(model);
        do {
            (info + infoLinesCounter)->points = inputCheck("������� ���������� ����� ���������: ");
            if ((info + infoLinesCounter)->points < 0 || (info + infoLinesCounter)->points > 9999)
                printf("[������!]������� ����� �� 0 �� 9999!\n");
        } while ((info + infoLinesCounter)->points < 0 || (info + infoLinesCounter)->points > 9999);
        do {
            (info + infoLinesCounter)->timeOfLap.minutes = inputCheck("������� ������ ����� ���������: ");
            if ((info + infoLinesCounter)->timeOfLap.minutes < 0 || (info + infoLinesCounter)->timeOfLap.minutes > 59)
                printf("[������!]������� ����� �� 0 �� 59!\n");
        } while ((info + infoLinesCounter)->timeOfLap.minutes < 0 || (info + infoLinesCounter)->timeOfLap.minutes > 59);
        do {
            (info + infoLinesCounter)->timeOfLap.seconds = inputCheck("������� ������� ����� ���������: ");
            if ((info + infoLinesCounter)->timeOfLap.seconds < 0 || (info + infoLinesCounter)->timeOfLap.seconds > 59)
                printf("[������!]������� ����� �� 0 �� 59!\n");
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
        printf("�������� ������� ��������!\n\n");
    }
    system("pause");
    return info;
}

int infoEditMenu(INFORMATION* info, int i){
    int choice = 1, ch = ' ';
    char pointer = '>', *line[] = {"��������� ������ ���������.", "��������� ����� ���������.",
                                     "��������� ������� ���������.", "��������� �������� ���������.",
                                     "��������� ������ ���������.", "��������� ��� �������� ���������.",
                                     "��������� ������ �������� ���������.", "��������� ���� �������� ���������.",
                                     "��������� ������� ���������.", "��������� ������ ������� ���������.",
                                     "��������� ���������� ����� ���������.", "��������� ����� ����� ���������.",
                                     "��������� ������ ����� ���������.", "����� �� ���� �������������� ���������.", NULL};
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
            printf("���� �������������� ���c�����:\n");
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
    printf("|�����|���             �������         ��������       |  ������  |����  ��������|�������|  ������  |  ������  |����|����� �����|\n");
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
        printf("[������!]�������������� ����������: ���� �� ������!\n\n");
        system("pause");
    }
    else if (infoLinesCounter == 0) {
        printf("[������!]�������������� ����������: ���� ����!\n\n");
        system("pause");
    }
    else {
        time_t t = time(NULL);
        FILE *file = NULL;
        struct tm *aTm = localtime(&t);
        int number = 0, isExist = FALSE, i = 0, j = 0, isNumberExist = FALSE, infoEditFlag = FALSE;
        char *firstname = NULL, *surname = NULL, *lastname = NULL, *country = NULL, *category = NULL, *model = NULL;
        printf("--------------------------------------------------------------------------------------------------------------------------------\n");
        printf("|�����|���             �������         ��������       |  ������  |����  ��������|�������|  ������  |  ������  |����|����� �����|\n");
        printf("--------------------------------------------------------------------------------------------------------------------------------\n");
        for (j = 0; j < infoLinesCounter; j++) {
            printf("|%-3i  |%-15s %-15s %-15s|%-10s|  %02i/%02i/%04i  |  %-3i  |%-10s|%-10s|%-4i|   %02i:%02i   |\n",
                   (info + j)->number, (info + j)->fullname.firstname, (info + j)->fullname.surname, (info + j)->fullname.lastname, (info + j)->country,
                   (info + j)->dateOfBirth.day, (info + j)->dateOfBirth.month, (info + j)->dateOfBirth.year, (info + j)->dateOfBirth.age, (info + j)->category,
                   (info + j)->model, (info + j)->points, (info + j)->timeOfLap.minutes, (info + j)->timeOfLap.seconds);
        }
        printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
        do {
            number = inputCheck("������� ����� ���������, �������� ����� ���������������: ");
            for (i = 0; i < infoLinesCounter; i++) {
                if ((info + i)->number == number) {
                    isExist = TRUE;
                    break;
                } else isExist = FALSE;
            }
            if (isExist == FALSE) printf("[������!]��������� � ����� ������� �� ����������!\n");
        } while (isExist == FALSE);
        while (infoEditFlag == FALSE) {
            switch (infoEditMenu(info,i)) {
                case 1: {
                    int newNumber = 0;
                    printf("�������� ������ ���������.\n");
                    do {
                        do {
                            newNumber = inputCheck("������� ����� ����� ���������: ");
                            if (newNumber < 1)
                                printf("[������!]������� ����� ������ 0!\n");
                        } while (newNumber < 1);
                        for (j = 0; j < infoLinesCounter; j++) {
                            if ((info + j)->number == newNumber) {
                                isNumberExist = TRUE;
                                break;
                            } else isNumberExist = FALSE;
                        }
                        if (isNumberExist == TRUE)
                            printf("[������!]�������� � ����� ������� ��� ����������!\n");
                    } while (isNumberExist == TRUE);
                    (info + i)->number = newNumber;
                    printEditingInfo(info,i);
                    printf("����� ��������� ������� �������!\n\n");
                    system("pause");
                    break;
                }
                case 2: {
                    printf("��������� ����� ���������.\n");
                    printf("������� ����� ��� ���������: ");
                    firstname = limitedStringInput(firstname, 49, "������� ����� ��� ���������: ");
                    strcpy((info + i)->fullname.firstname, firstname);
                    free(firstname);
                    printEditingInfo(info,i);
                    printf("��� ��������� ������� ��������!\n\n");
                    system("pause");
                    break;
                }
                case 3: {
                    printf("��������� ������� ���������.\n");
                    printf("������� ����� ������� ���������: ");
                    surname = limitedStringInput(surname, 49, "������� ����� ������� ���������: ");
                    strcpy((info + i)->fullname.surname, surname);
                    free(surname);
                    printEditingInfo(info,i);
                    printf("������� ��������� ������� ��������!\n\n");
                    system("pause");
                    break;
                }
                case 4: {
                    printf("��������� �������� ���������.\n");
                    printf("������� ����� �������� ���������: ");
                    lastname = limitedStringInput(lastname, 49, "������� ����� �������� ���������: ");
                    strcpy((info + i)->fullname.lastname, lastname);
                    free(lastname);
                    printEditingInfo(info,i);
                    printf("�������� ��������� ������� ��������!\n\n");
                    system("pause");
                    break;
                }
                case 5: {
                    printf("��������� ������ ���������.\n");
                    printf("������� ����� ������ ���������: ");
                    country = limitedStringInput(country, 29, "������� ����� ������ ���������: ");
                    strcpy((info + i)->country, country);
                    free(country);
                    printEditingInfo(info,i);
                    printf("������ ��������� ������� ��������.\n\n");
                    system("pause");
                    break;
                }
                case 6: {
                    printf("��������� ��� �������� ���������.\n");
                    int newBirthDay = 0;
                    do {
                        printf("������� ����� ���� �������� ���������: ");
                        scanf_s("%i", &newBirthDay);
                        if (newBirthDay < 1 || newBirthDay > 31)
                            printf("[������!]������� ����� �� 1 �� 31!\n");
                    } while (newBirthDay < 1 || newBirthDay > 31);
                    (info + i)->dateOfBirth.day = newBirthDay;
                    printEditingInfo(info,i);
                    printf("���� �������� ��������� ������� �������!\n\n");
                    system("pause");
                    break;
                }
                case 7: {
                    printf("��������� ������ �������� ���������.\n");
                    int newBirthMonth = 0;
                    do {
                        newBirthMonth = inputCheck("������� ����� ����� �������� ���������(������): ");
                        if (newBirthMonth < 1 || newBirthMonth > 12)
                            printf("[������!]������� ����� �� 1 �� 12!\n\n");
                    } while (newBirthMonth < 1 || newBirthMonth > 12);
                    (info + i)->dateOfBirth.month = newBirthMonth;
                    printEditingInfo(info,i);
                    printf("����� �������� ��������� ������� �������!\n\n");
                    system("pause");
                    break;
                }
                case 8: {
                    printf("��������� ���� �������� ���������.\n");
                    int newBirthYear = 0;
                    do {
                        newBirthYear = inputCheck("������� ����� ��� �������� ���������: ");
                        if (newBirthYear < 1900 || newBirthYear > 2019)
                            printf("[������!]������� ����� �� 1900 �� 2019!\n");
                    } while (newBirthYear < 1900 || newBirthYear > 2019);
                    (info + i)->dateOfBirth.year = newBirthYear;
                    if ((info + i)->dateOfBirth.month >= aTm->tm_mon + 1)
                        (info + i)->dateOfBirth.age = 2018 - (info + i)->dateOfBirth.year;
                    else
                        (info + i)->dateOfBirth.age = 2019 - (info + i)->dateOfBirth.year;
                    printEditingInfo(info,i);
                    printf("��� �������� ��������� ������� �������!\n\n");
                    system("pause");
                    break;
                }
                case 9: {
                    printf("��������� ������� ���������.\n");
                    printf("������� ����� ������ ���������: ");
                    category = limitedStringInput(category, 29, "������� ����� ������ ���������: ");
                    strcpy((info + i)->category, category);
                    free(category);
                    printEditingInfo(info,i);
                    printf("������ ��������� ������� �������!\n\n");
                    system("pause");
                    break;
                }
                case 10: {
                    printf("��������� ������ ������� ���������.\n");
                    printf("������� ����� ������ ������� ���������: ");
                    model = limitedStringInput(model, 29, "������� ����� ������ ������� ���������: ");
                    strcpy((info + i)->model, model);
                    free(model);
                    printEditingInfo(info,i);
                    printf("������ ������� ��������� ������� ��������!\n\n");
                    system("pause");
                    break;
                }
                case 11: {
                    printf("��������� ���������� ����� ���������.\n");
                    do {
                        (info + i)->points = inputCheck("������� ����� ���������� ����� ���������: ");
                        if ((info + i)->points < 0 || (info + i)->points > 9999)
                            printf("[������!]������� ����� �� 0 �� 9999!\n");
                    } while ((info + i)->points < 0 || (info + i)->points > 9999);
                    printEditingInfo(info,i);
                    printf("���������� ����� ��������� ������� ��������!\n\n");
                    system("pause");
                    break;
                }
                case 12: {
                    printf("��������� ����� ����� ���������.\n");
                    do {
                        (info + i)->timeOfLap.minutes = inputCheck("������� ����� ������ ����� ���������: ");
                        if ((info + i)->timeOfLap.minutes < 0 ||
                            (info + i)->timeOfLap.minutes > 59)
                            printf("[������!]������� ����� �� 0 �� 59!\n");
                    } while ((info + i)->timeOfLap.minutes < 0 ||
                             (info + i)->timeOfLap.minutes > 59);
                    printEditingInfo(info,i);
                    printf("������ ����� ��������� ������� ��������!\n\n");
                    system("pause");
                    break;
                }
                case 13: {
                    printf("��������� ������ ����� ���������.\n");
                    do {
                        (info + i)->timeOfLap.seconds = inputCheck("������� ����� ������� ����� ���������: ");
                        if ((info + i)->timeOfLap.seconds < 0 ||
                            (info + i)->timeOfLap.seconds > 59)
                            printf("[������!]������� ����� �� 0 �� 59!\n");
                    } while ((info + i)->timeOfLap.seconds < 0 ||
                             (info + i)->timeOfLap.seconds > 59);
                    printEditingInfo(info,i);
                    printf("������� ����� ��������� ������� ��������!\n\n");
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
        } else printf("[������!]�������������� ����������: �� ������� ������������ ����! ���� �������!\n");
    }
    return info;
}

INFORMATION* infoDelete(INFORMATION *info) {
    if (info == NULL) {
        printf("[������!]�������� ����������: ���� �� ������!\n\n");
    } else if (infoLinesCounter == 0) {
        printf("[������!]�������� ����������: ���� ����!\n\n");
    } else {
        int delNumber = 0, isNumberExist = FALSE, i = 0;
        FILE *file = NULL;
        printf("�������� ���������.\n");
        do {
            delNumber = inputCheck("������� ����� ��������� ��� ��������: ");
            for (i = 0; i < infoLinesCounter; i++) {
                if (delNumber == (info + i)->number) {
                    isNumberExist = TRUE;
                    break;
                } else isNumberExist = FALSE;
            }
            if (isNumberExist == FALSE) printf("[������!]��������� � ����� ������� �� ����������!\n");
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
            printf("�������� ������� �����!\n\n");
        } else printf("[������!]�������� ����������: �� ������� ������������ ����! ���� �������!\n\n");
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
        else printf("[������!]�� ���������� ����!\n");
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
                    printf("\n[������!]������� ������ ���� ������!\n");
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
    char pointer = '>', *line[] = {"������ �� ���������� �����.", "������ �� ������� �����.",
                                     "������ �� ��������.", "������ �� ���� ��������.", "����� �� ������.",
                                     "����� �� �������.", "����� �� ������.", "����� �� �������.",
                                     "���������� �� ������� �����.", "�����.", NULL};
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
            printf("���� ������ � ����������:\n");
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
        printf("[������!]����� � ����������: ���� �� ������!\n\n");
    else if (infoLinesCounter == 0)
        printf("[������!]����� � ����������: ���� ����!\n\n");
    else {
        int points = 0, isAtLeastOneMember = FALSE;
        do {
            points = inputCheck("������� ���������� �����: ");
            if (points < 0 || points > 9999)
                printf("[������!]������� ����� ������ 0 � ������ 9999!\n");
        } while (points < 0 || points > 9999);
        system("cls");
        printf("���������, � ������� ����� ������ %i: ", points);
        for (int i = 0; i < infoLinesCounter; i++) {
            if ((info + i)->points > points) {
                if (isAtLeastOneMember == FALSE) {
                    printf("\n--------------------------------------------------------------------------------------------------------------------------------\n");
                    printf("|�����|���             �������         ��������       |  ������  |����  ��������|�������|  ������  |  ������  |����|����� �����|\n");
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
            printf("[������!]��� �� ������ ��������� � ������ ������ %i.\n\n", points);
    }
    system("pause");
}

void timeOfLapFilter(INFORMATION* info) {
    if (info == NULL) {
        printf("[������!]����� � ����������: ���� �� ������!\n\n");
    } else if (infoLinesCounter == 0) {
        printf("[������!]����� � ����������: ���� ����!\n\n");
    } else {
        int minutesOfLap = 0, secondsOfLap = 0, isAtLeastOneMember = FALSE;
        do {
            minutesOfLap = inputCheck("������� ���������� ����� �����: ");
            if (minutesOfLap < 0 || minutesOfLap > 59)
                printf("[������!]������� ����� ������ 0 � ������ 59!\n");
        } while (minutesOfLap < 0 || minutesOfLap > 59);
        do {
            secondsOfLap = inputCheck("������� ���������� ������ �����: ");
            if (secondsOfLap < 0 || secondsOfLap > 59)
                printf("[������!]������� ����� ������ 0 � ������ 59!\n");
        } while (secondsOfLap < 0 || secondsOfLap > 59);
        system("cls");
        printf("���������, � ������� ����� ����� ������ %02i:%02i : ", minutesOfLap, secondsOfLap);
        for (int i = 0; i < infoLinesCounter; i++) {
            if ((info + i)->timeOfLap.minutes < minutesOfLap)
                if ((info + i)->timeOfLap.seconds <
                    ((info + i)->timeOfLap.minutes == minutesOfLap ? secondsOfLap : 60)) {
                    if (isAtLeastOneMember == FALSE) {
                        printf("\n--------------------------------------------------------------------------------------------------------------------------------\n");
                        printf("|�����|���             �������         ��������       |  ������  |����  ��������|�������|  ������  |  ������  |����|����� �����|\n");
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
            printf("[������!]��� �� ������ ��������� � �������� ����� ������ %02i:%02i.\n\n", minutesOfLap,
                   secondsOfLap);
    }
    system("pause");
}

void ageFilter(INFORMATION* info) {
    if (info == NULL)
        printf("[������!]����� � ����������: ���� �� ������!\n\n");
    else if (infoLinesCounter == 0)
        printf("[������!]����� � ����������: ���� ����!\n\n");
    else {
        int age = 0, isAtLeastOneMember = FALSE;
        do {
            age = inputCheck("������� �������: ");
            if (age < 0 || age > 119)
                printf("[������!]������� ����� ������ 0 � ������ 119!\n");
        } while (age < 0 || age > 119);
        system("cls");
        printf("���������, ������� ������� ������ %i: ", age);
        for (int i = 0; i < infoLinesCounter; i++) {
            if ((info + i)->dateOfBirth.age > age) {
                if (isAtLeastOneMember == FALSE) {
                    printf("\n--------------------------------------------------------------------------------------------------------------------------------\n");
                    printf("|�����|���             �������         ��������       |  ������  |����  ��������|�������|  ������  |  ������  |����|����� �����|\n");
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
            printf("[������!]��� �� ������ ��������� � ������ ������ %i.\n\n", age);
    }
    system("pause");
}

void yearOfBirthFilter(INFORMATION* info) {
    if (info == NULL)
        printf("[������!]����� � ����������: ���� �� ������!\n\n");
    else if (infoLinesCounter == 0)
        printf("[������!]����� � ����������: ���� ����!\n\n");
    else {
        int yearOfBirth = 0, isAtLeastOneMember = FALSE;
        do {
            yearOfBirth = inputCheck("������� ��� ��������: ");
            if (yearOfBirth < 1900 || yearOfBirth > 2019)
                printf("[������!]������� ����� ������ 1900 � ������ 2019!\n");
        } while (yearOfBirth < 1900 || yearOfBirth > 2019);
        system("cls");
        printf("���������, ��� �������� � ������� ������ %i: ", yearOfBirth);
        for (int i = 0; i < infoLinesCounter; i++) {
            if ((info + i)->dateOfBirth.year > yearOfBirth) {
                if (isAtLeastOneMember == FALSE) {
                    printf("\n--------------------------------------------------------------------------------------------------------------------------------\n");
                    printf("|�����|���             �������         ��������       |  ������  |����  ��������|�������|  ������  |  ������  |����|����� �����|\n");
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
            printf("[������!]��� �� ������ ��������� � ����� �������� ������ %i.\n\n", yearOfBirth);
    }
    system("pause");
}

void timeOfLapSorting(INFORMATION* info){
    FILE* file = NULL;
    if (info == NULL)
        printf("[������!]����������: ���� �� ������!\n\n");
    else if (infoLinesCounter == 0)
        printf("[������!]����������: ���� ����!\n\n");
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
            printf("����������: ��������� ������� �������������!\n\n");
        } else printf("[������!]����������: �� ������� ������� ����! ���� �������!\n\n");
    }
    system("pause");
}

void numberSearch(INFORMATION* info) {
    if (info == NULL)
        printf("[������!]����� � ����������: ���� �� ������!\n\n");
    else if (infoLinesCounter == 0)
        printf("[������!]����� � ����������: ���� ����!\n\n");
    else {
        int number = 0, isFounded = FALSE;
        do {
            number = inputCheck("������� �����: ");
            if (number < 0)
                printf("[������!]������� ����� ������ 0!\n");
        } while (number < 0);
        system("cls");
        printf("��������, ����� �������� %i: ", number);
        for (int i = 0; i < infoLinesCounter; i++) {
            if ((info + i)->number == number) {
                printf("\n--------------------------------------------------------------------------------------------------------------------------------\n");
                printf("|�����|���             �������         ��������       |  ������  |����  ��������|�������|  ������  |  ������  |����|����� �����|\n");
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
            printf("[������!]���� ��������� � ������� %i.\n\n", number);
    }
    system("pause");
}

void surnameSearch(INFORMATION* info) {
    if (info == NULL)
        printf("[������!]����� � ����������: ���� �� ������!\n\n");
    else if (infoLinesCounter == 0)
        printf("[������!]����� � ����������: ���� ����!\n\n");
    else {
        int isAtLeastOneMember = FALSE;
        char *surname = NULL;
        printf("������� �������: ");
        surname = limitedStringInput(surname, 49, "������� �������: ");
        system("cls");
        printf("���������, � �������� %s: ", surname);
        for (int i = 0; i < infoLinesCounter; i++) {
            if (strcmp((info + i)->fullname.surname, surname) == 0) {
                if (isAtLeastOneMember == FALSE) {
                    printf("\n--------------------------------------------------------------------------------------------------------------------------------\n");
                    printf("|�����|���             �������         ��������       |  ������  |����  ��������|�������|  ������  |  ������  |����|����� �����|\n");
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
            printf("[������!]��� �� ������ ��������� � �������� %s.\n\n", surname);
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
        printf("[������!]����� � ����������: ���� �� ������!\n\n");
    else if (infoLinesCounter == 0)
        printf("[������!]����� � ����������: ���� ����!\n\n");
    else {
        int isAtLeastOneMember = FALSE;
        char *country = NULL;
        printf("������� ������: ");
        country = limitedStringInput(country, 49, "������� ������: ");
        system("cls");
        printf("���������, �� ������ %s: ", country);
        for (int i = 0; i < infoLinesCounter; i++) {
            if (strcmp((info + i)->country,country) == 0) {
                if (isAtLeastOneMember == FALSE) {
                    printf("\n--------------------------------------------------------------------------------------------------------------------------------\n");
                    printf("|�����|���             �������         ��������       |  ������  |����  ��������|�������|  ������  |  ������  |����|����� �����|\n");
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
            printf("[������!]��� �� ������ ��������� �� ������ %s.\n\n", country);
    }
    system("pause");
}

void categorySearch(INFORMATION* info){
    if (info == NULL)
        printf("[������!]����� � ����������: ���� �� ������!\n\n");
    else if (infoLinesCounter == 0)
        printf("[������!]����� � ����������: ���� ����!\n\n");
    else {
        int isAtLeastOneMember = FALSE;
        char *category = NULL;
        printf("������� ������: ");
        category = limitedStringInput(category, 49, "������� ������: ");
        system("cls");
        printf("���������, � �������� %s: ", category);
        for (int i = 0; i < infoLinesCounter; i++) {
            if (strcmp((info + i)->category,category) == 0) {
                if (isAtLeastOneMember == FALSE) {
                    printf("\n--------------------------------------------------------------------------------------------------------------------------------\n");
                    printf("|�����|���             �������         ��������       |  ������  |����  ��������|�������|  ������  |  ������  |����|����� �����|\n");
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
            printf("[������!]��� �� ������ ��������� � �������� %s.\n\n", category);
    }
    system("pause");
}

void printTop(INFORMATION* info){
    system("cls");
    if (info == NULL)
        printf("[������!]����� � ����������: ���� �� ������!\n\n");
    else if (infoLinesCounter == 0)
        printf("[������!]����� � ����������: ���� ����!\n\n");
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
        printf("|�����|���             �������         ��������       |  ������  |����  ��������|�������|  ������  |  ������  |����|����� �����|\n");
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