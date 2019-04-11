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
int timeOfLapSorting(INFORMATION* info);
int numberSearch(INFORMATION* info);
int surnameSearch(INFORMATION* info);
int searchingAndFiltering(INFORMATION* info);
int countrySearch(INFORMATION* info);
int categorySearch(INFORMATION* info);


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    INFORMATION *info = NULL;
    USER *user = NULL;
    user = userLoad(user);
    int adminSubMenuFlag = 0, userManagementFlag = 0, userSubMenuFlag = 0, isInfoSorted = 0;
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
                                    printf("�������� ����������: ���� ������� ������!\n\n");
                                }
                                else printf("[������!]�������� ����������: ���� ��� ������!\n\n");
                                break;
                            }
                            case 2: info = infoAdd(info); isInfoSorted = 0; break;
                            case 3: info = infoEdit(info); isInfoSorted = 0; break;
                            case 4: info = infoDelete(info); isInfoSorted = 0; break;
                            case 5: infoPrint(info); break;
                            case 6: isInfoSorted = searchingAndFiltering(info); break;
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
                                    printf("�������� ����������: ���� ������� ������!\n\n");
                                }
                                else printf("[������!]�������� ����������: ���� ��� �� ������!\n\n");
                                break;
                            }
                            case 2: infoPrint(info); break;
                            case 3: {
                                if (isInfoSorted == 1){

                                } else printf("[������!]��������� �������������!");
                                break;
                            }
                            case 4: isInfoSorted = searchingAndFiltering(info); break;
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
    printf("����: \n");
    printf("1.���� ��� ���������������.\n");
    printf("2.���� ��� �������������.\n");
    printf("3.�����.\n");
    printf("��� �����: ");
    choice = inputCheck("��� �����: ");
    printf("\n");
    return choice;
}

int adminSubmenu() {
    int choice;
    printf("�������(��� ���������������):\n");
    printf("1.��������/�������� �����.\n");
    printf("2.���������� ������.\n");
    printf("3.�������������� ������.\n");
    printf("4.�������� ������.\n");
    printf("5.�������� ���� ������ � ��������� �����.\n");
    printf("6.��������� ��������� ������ � ���������� ������.\n");
    printf("7.���������� ��������������.\n");
    printf("8.����� � ����.\n");
    printf("��� �����: ");
    choice = inputCheck("��� �����: ");
    printf("\n");
    return choice;
};

int userSubmenu() {
    int choice;
    printf("�������(��� �������������):\n");
    printf("1.�������� ����� � �������.\n");
    printf("2.�������� ���� ������ � ��������� �����.\n");
    printf("3.���������� ������.\n");
    printf("4.��������� ��������� ������ � ���������� ������.\n");
    printf("5.����� � ����.\n");
    printf("��� �����: ");
    choice = inputCheck("��� �����: ");
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
        printf("������� �����: ");
        login = limitedStringInput(login, 29);
        for (i = 0; i < usersLinesCounter; i++)
            if (strcmp(login, (user + i)->login) == 0) {
                isLoginRight = 1;
                break;
            }
        if (isLoginRight == 0) {
            printf("[������!]������ �������������� �� ����������!\n\n");
            return 0;
        }
    } while (isLoginRight != 1);
    do {
        j = 0;
        printf("������� ������: ");
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
        else printf("\n[������!]�������� ������!\n");
    } while (isPasswordRight != 1);
    if ((user + i)->isAdmin == 1) {
        printf("\n�� ������� ��������������.\n\n");
        free(login);
        return 1;
    }
    else {
        printf("\n[������!]�����������: ������� ����� ������������!\n\n");
        free(login);
        return 0;
    }
}

int userLogin(USER *user) {
    int isLoginRight = 0, isPasswordRight = 0, i = 0, j = 0, counter = 0;
    char *login = NULL, password[30], ch;
    do {
        printf("������� �����: ");
        login = limitedStringInput(login, 29);
        for (i = 0; i < usersLinesCounter; i++)
            if (strcmp(login, (user + i)->login) == 0) {
                isLoginRight = 1;
                break;
            }
        if (isLoginRight == 0) {
            printf("[������!]������ ������������ �� ����������!\n\n");
            free(login);
            return 0;
        }
    } while (isLoginRight != 1);
    do {
        j = 0;
        printf("������� ������: ");
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
        else printf("\n[������!]�������� ������!\n");
    } while (isPasswordRight != 1);
    if ((user + i)->isAdmin == 0) {
        printf("\n�� ������� ��������������.\n\n");
        free(login);
        return 1;
    }
    else {
        printf("\n[������!]�����������! ������� ����� ��������������!\n\n");
        free(login);
        return 0;
    }
}

int userManagement() {
    int choice;
    printf("���������� ��������������:\n");
    printf("1.�������� �������.\n");
    printf("2.������� �������.\n");
    printf("3.������������� �������.\n");
    printf("4.�������� ���� ���������.\n");
    printf("5.�����.\n");
    printf("��� �����: ");
    choice = inputCheck("��� �����: ");
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
            printf("[������!]������������� �������������: �� ������� ������� ���� � ��������/��������!\n");
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
        printf("[������!]������������� �������������: ���� � ��������/�������� ����!\n\n");
        return NULL;
    }
}

USER* userAdd(USER* user) {
    user = (USER*)realloc(user, (usersLinesCounter + 1) * sizeof(USER));
    int loginIsNotExist = 0, i = 0;
    char *login = NULL, *password = NULL;
    FILE* file = NULL;
    printf("�������� ������������:\n");
    do {
        loginIsNotExist = 0;
        printf("������� �����: ");
        login = limitedStringInput(login, 29);
        strcpy((user + usersLinesCounter)->login, login);
        for (i = 0; i < usersLinesCounter; i++) {
            if (strcmp((user + i)->login, (user + usersLinesCounter)->login) == 0) {
                printf("[������!]���� ������� ��� ����������!\n");
                loginIsNotExist = 0;
                break;
            }
            else loginIsNotExist = 1;
        }
    } while ((loginIsNotExist != 1));
    free(login);
    printf("������� ������: ");
    password = limitedStringInput(password, 29);
    strcpy((user + usersLinesCounter)->password, password);
    free(password);
    do {
        printf("�������������?(1 - ��|0 - ���): ");
        (user + usersLinesCounter)->isAdmin = inputCheck("�������������?(1 - ��|0 - ���): ");
        if ((user + usersLinesCounter)->isAdmin < 0 || (user + usersLinesCounter)->isAdmin > 1) {
            printf("[������!]�� ���������� ����!\n");
        }
    } while ((user + usersLinesCounter)->isAdmin < 0 || (user + usersLinesCounter)->isAdmin > 1);
    if ((file = fopen("db.txt", "at+")) == NULL) {
        printf("[������!]���������� �������������: ������ �������� ����� � ��������/��������! ������������ �� ��������!\n\n");
        free(login);
        free(password);
        return user;
    }
    fprintf(file, "%s %s %i\n", (user + usersLinesCounter)->login, (user + usersLinesCounter)->password, (user + usersLinesCounter)->isAdmin);
    fclose(file);
    printf("������� ������� ��������!\n\n");
    _flushall();
    usersLinesCounter++;
    return user;
}

void userPrint(USER* user) {
    system("cls");
    char yes[] = "��", no[] = "���";
    printf("-----------------------------------------------------------------------------------------------\n");
    printf("|�    |�����:                         |������:                         |����� ��������������: |\n");
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
    system("cls");
}

USER* userDelete(USER* user) {
    char *login = NULL;
    int i = 0, loginIsExist = 0;
    FILE* file = NULL;
    printf("�������� ��������.\n");
    do {
        printf("������� ����� ��������, ������� �� ������ �������: ");
        login = limitedStringInput(login, 29);
        for (i = 0; i < usersLinesCounter; i++) {
            if (strcmp((user + i)->login, login) == 0) {
                loginIsExist = 1;
                break;
            }
        }
        if (loginIsExist == 0)
            printf("[������!]������ �������� �� ����������!\n");
    } while (loginIsExist != 1);
    free(login);
    if ((file = fopen("db.txt", "w")) == NULL) {
        printf("[������!]�������� �������������: ������ �������� ����� � ��������/��������! ������������ �� ������! ���� �������!\n\n");
        free(login);
        return user;
    }
    for (int j = 0; j < usersLinesCounter; j++)
        if (j != i)
            fprintf(file, "%s %s %i\n", (user + j)->login, (user + j)->password, (user + j)->isAdmin);
    printf("������� ������� �����!\n\n");
    fclose(file);
    usersLinesCounter--;
    free(user);
    user = userLoad(user);
    return user;
}

USER* userEdit(USER* user) {
    char *login = NULL, *newLogin = NULL, *newPassword = NULL, yes[] = "��", no[] = "���";
    int i = 0, loginIsExist = 0, isNewLoginNotExist = 0, choice = 0, editFlag = 0;
    FILE* file = NULL;
    do {
        loginIsExist = 0;
        printf("������� ����� ��������, ������� �� ������ ���������������: ");
        login = limitedStringInput(login, 29);
        for (i = 0; i < usersLinesCounter; i++) {
            if (strcmp((user + i)->login, login) == 0) {
                loginIsExist = 1;
                break;
            }
        }
        if (loginIsExist == 0)
            printf("[������!]������ �������� �� ����������!\n");
    } while (loginIsExist != 1);
    free(login);
    printf("-----------------------------------------------------------------------------------------\n");
    printf("|�����:                         |������:                         |����� ��������������: |\n");
    printf("-----------------------------------------------------------------------------------------\n");
    printf("|%-31s|%-32s|", (user + i)->login, (user + i)->password);
    if ((user + i)->isAdmin == 1)
        printf("%-22s|", yes);
    else printf("%-22s|", no);
    printf("\n-----------------------------------------------------------------------------------------\n\n");
    while (editFlag == 0) {
        printf("��� ���������������?\n");
        printf("1.�����.\n");
        printf("2.������.\n");
        printf("3.����� ��������������.\n");
        printf("4.�����.\n");
        printf("��� �����: ");
        choice = inputCheck("��� �����: ");
        printf("\n");
        switch (choice) {
            case 1: {
                printf("�������� �����.\n");
                do {
                    printf("������� ����� �����: ");
                    newLogin = limitedStringInput(newLogin, 29);
                    for (int j = 0; j < usersLinesCounter; j++) {
                        if (strcmp((user + j)->login, newLogin) == 0) {
                            isNewLoginNotExist = 0;
                            break;
                        }
                        else isNewLoginNotExist = 1;
                    }
                    if (isNewLoginNotExist == 0)
                        printf("[������!]����� ����� ��� ����������!\n");
                } while (isNewLoginNotExist == 0);
                strcpy((user + i)->login, newLogin);
                printf("����� ������� �������!\n\n");
                free(newLogin);
                break;
            }
            case 2: {
                printf("��������� ������.\n");
                printf("������� ����� ������: ");
                newPassword = limitedStringInput(newPassword, 29);
                strcpy((user + i)->password, newPassword);
                printf("������ ������� �������!\n\n");
                free(newPassword);
                break;
            }
            case 3: {
                if ((user + i)->isAdmin == 1) {
                    (user + i)->isAdmin = 0;
                    printf("����� �������������� ������� ��������.\n\n");
                    break;
                }
                else {
                    (user + i)->isAdmin = 1;
                    printf("����� �������������� ������� ��������.\n\n");
                    break;
                }
            }
            case 4: editFlag = 1; break;
            default: break;
        }
        if (editFlag == 1) break;
    }
    if ((file = fopen("db.txt", "w")) == NULL) {
        printf("[������!]�������������� �������������: �� ������� ������� ���� � ��������/��������! ������������ �� ��������������! ���� �������!\n\n");
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
        printf("�������� ����������: ���� �� ����������! ������ ����...\n");
    if (!file)
        if ((file = fopen("info.txt", "wt+")) != NULL)
            printf("�������� ����������: ���� ������� ������!\n");
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
        printf("[������!]����� ����������: ���� ����!\n\n");
        return 0;
    }
    if (infoLinesCounter != 0) {
        system("cls");
        printf("--------------------------------------------------------------------------------------------------------------------------------\n");
        printf("|�����|���             �������         ��������       |  ������  |����  ��������|�������|  ������  |  ������  |����|����� �����|\n");
        printf("--------------------------------------------------------------------------------------------------------------------------------\n");
        for (int i = 0; i < infoLinesCounter; i++) {
            printf("|%-3i  |%-15s %-15s %-15s|%-10s|  %-2i/%02i/%-4i  |  %-3i  |%-10s|%-10s|%-4i|   %02i:%02i   |", (info + i)->number, (info + i)->fullname.firstname, (info + i)->fullname.surname, (info + i)->fullname.lastname, (info + i)->country, (info + i)->dateOfBirth.day, (info + i)->dateOfBirth.month, (info + i)->dateOfBirth.year, (info + i)->dateOfBirth.age, (info + i)->category, (info + i)->model, (info + i)->points, (info + i)->timeOfLap.minutes, (info + i)->timeOfLap.seconds);
            printf("\n");
        }
        printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
        system("pause");
        system("cls");
        return 0;
    }
    else {
        printf("[������!]����� ����������: ���� ����!\n\n");
        return 0;
    };
}

INFORMATION* infoAdd(INFORMATION* info) {
    if (info == NULL) {
        printf("[������!]���������� ����������: ���� �� ������!\n\n");
        return NULL;
    }
    time_t t = time(NULL);
    struct tm* aTm = localtime(&t);
    int isExist = 0;
    char *firstname = NULL, *surname = NULL, *lastname = NULL, *country = NULL, *category = NULL, *model = NULL;
    FILE *file = NULL;
    if ((file = fopen("info.txt", "a+")) == NULL) {
        printf("[������!]���������� ����������: �� ������� ������� ���� ��� ����������!\n");
        return info;
    }
    if (infoLinesCounter != -1)
        info = (INFORMATION*)realloc(info, ((infoLinesCounter + 1) * sizeof(INFORMATION)));
    else {
        printf("[������!]���������� ����������: �� ������� ������� ����(���� �� ����������)!\n\n");
        return info;
    }
    printf("���������� ���������.\n");
    do {
        printf("������� ����� ���������: ");
        do {
            (info + infoLinesCounter)->number = inputCheck("������� ����� ���������: ");
            if ((info + infoLinesCounter)->number < 1)
                printf("[������!]������� ����� ������ 0!\n");
        } while ((info + infoLinesCounter)->number < 1);
        for (int i = 0; i < infoLinesCounter; i++) {
            if ((info + i)->number == (info + infoLinesCounter)->number) {
                isExist = 1;
                break;
            }
            else isExist = 0;
        }
        if (isExist == 1) printf("�������� � ����� ������� ��� ����������!\n");
    } while (isExist == 1);
    printf("������� ��� ���������: ");
    firstname = limitedStringInput(firstname, 49);
    strcpy((info + infoLinesCounter)->fullname.firstname, firstname);
    free(firstname);
    printf("������� ������� ���������: ");
    surname = limitedStringInput(surname, 49);
    strcpy((info + infoLinesCounter)->fullname.surname, surname);
    free(surname);
    printf("������� �������� ���������: ");
    lastname = limitedStringInput(lastname, 49);
    strcpy((info + infoLinesCounter)->fullname.lastname, lastname);
    free(lastname);
    printf("������� ������ ��������: ");
    country = limitedStringInput(country, 29);
    strcpy((info + infoLinesCounter)->country, country);
    free(country);
    do {
        printf("������� ���� �������� ���������: ");
        (info + infoLinesCounter)->dateOfBirth.day = inputCheck("������� ���� �������� ���������: ");
        if ((info + infoLinesCounter)->dateOfBirth.day < 1 || (info + infoLinesCounter)->dateOfBirth.day > 31)
            printf("[������!]������� ����� �� 1 �� 31!\n");
    } while ((info + infoLinesCounter)->dateOfBirth.day < 1 || (info + infoLinesCounter)->dateOfBirth.day > 31);
    do {
        printf("������� ����� �������� ���������(������): ");
        (info + infoLinesCounter)->dateOfBirth.month = inputCheck("������� ����� �������� ���������(������): ");
        if ((info + infoLinesCounter)->dateOfBirth.month < 1 || (info + infoLinesCounter)->dateOfBirth.month > 12)
            printf("[������!]������� ����� �� 1 �� 12!\n");
    } while ((info + infoLinesCounter)->dateOfBirth.month < 1 || (info + infoLinesCounter)->dateOfBirth.month > 12);
    do {
        printf("������� ��� �������� ���������: ");
        (info + infoLinesCounter)->dateOfBirth.year = inputCheck("������� ��� �������� ���������: ");
        if ((info + infoLinesCounter)->dateOfBirth.year < 1900 || (info + infoLinesCounter)->dateOfBirth.year > 2019)
            printf("[������!]������� ����� �� 1900 �� 2019!\n");
    } while ((info + infoLinesCounter)->dateOfBirth.year < 1900 || (info + infoLinesCounter)->dateOfBirth.year > 2019);
    if ((info + infoLinesCounter)->dateOfBirth.month > aTm->tm_mon + 1)
        (info + infoLinesCounter)->dateOfBirth.age = 2018 - (info + infoLinesCounter)->dateOfBirth.year;
    else (info + infoLinesCounter)->dateOfBirth.age = 2019 - (info + infoLinesCounter)->dateOfBirth.year;
    printf("������� ������ ���������: ");
    category = limitedStringInput(category, 29);
    strcpy((info + infoLinesCounter)->category, category);
    free(category);
    printf("������� ������ ������� ���������: ");
    model = limitedStringInput(model, 29);
    strcpy((info + infoLinesCounter)->model, model);
    free(model);
    do {
        printf("������� ���������� ����� ���������: ");
        (info + infoLinesCounter)->points = inputCheck("������� ���������� ����� ���������: ");
        if ((info + infoLinesCounter)->points < 0 || (info + infoLinesCounter)->points > 9999)
            printf("[������!]������� ����� �� 0 �� 9999!\n");
    } while ((info + infoLinesCounter)->points < 0 || (info + infoLinesCounter)->points > 9999);
    do {
        printf("������� ������ ����� ���������: ");
        (info + infoLinesCounter)->timeOfLap.minutes = inputCheck("������� ������ ����� ���������: ");
        if ((info + infoLinesCounter)->timeOfLap.minutes < 0 || (info + infoLinesCounter)->timeOfLap.minutes > 59)
            printf("[������!]������� ����� �� 0 �� 59!\n");
    } while ((info + infoLinesCounter)->timeOfLap.minutes < 0 || (info + infoLinesCounter)->timeOfLap.minutes > 59);
    do {
        printf("������� ������� ����� ���������: ");
        (info + infoLinesCounter)->timeOfLap.seconds = inputCheck("������� ������� ����� ���������: ");
        if ((info + infoLinesCounter)->timeOfLap.seconds < 0 || (info + infoLinesCounter)->timeOfLap.seconds > 59)
            printf("[������!]������� ����� �� 0 �� 59!\n");
    } while ((info + infoLinesCounter)->timeOfLap.seconds < 0 || (info + infoLinesCounter)->timeOfLap.seconds > 59);
    fprintf(file, "%i %s %s %s %s %i %i %i %i %s %s %i %i %i\n", (info + infoLinesCounter)->number, (info + infoLinesCounter)->fullname.firstname, (info + infoLinesCounter)->fullname.surname, (info + infoLinesCounter)->fullname.lastname, (info + infoLinesCounter)->country, (info + infoLinesCounter)->dateOfBirth.day, (info + infoLinesCounter)->dateOfBirth.month, (info + infoLinesCounter)->dateOfBirth.year, (info + infoLinesCounter)->dateOfBirth.age, (info + infoLinesCounter)->model, (info + infoLinesCounter)->category, (info + infoLinesCounter)->points, (info + infoLinesCounter)->timeOfLap.minutes, (info + infoLinesCounter)->timeOfLap.seconds);
    _flushall();
    fclose(file);
    infoLinesCounter++;
    printf("�������� ������� ��������!\n\n");
    return info;
}

INFORMATION* infoEdit(INFORMATION* info) {
    if (info == NULL) {
        printf("[������!]�������������� ����������: ���� �� ������!\n\n");
        return NULL;
    }
    time_t t = time(NULL);
    FILE *file = NULL;
    struct tm* aTm = localtime(&t);
    int number = 0, isExist = 0, i = 0, j = 0, isNumberExist = 0, choice = 0, infoEditFlag = 0;
    char *firstname = NULL, *surname = NULL, *lastname = NULL, *country = NULL, *category = NULL, *model = NULL;
    if (infoLinesCounter == 0) {
        printf("[������!]�������������� ����������: ���� ����!\n\n");
        return info;
    }
    do {
        printf("������� ����� ���������, �������� ����� ���������������: ");
        number = inputCheck("������� ����� ���������, �������� ����� ���������������: ");
        for (i = 0; i < infoLinesCounter; i++) {
            if ((info + i)->number == number) {
                isExist = 1;
                break;
            }
            else isExist = 0;
        }
        if (isExist == 0) printf("[������!]��������� � ����� ������� �� ����������!\n");
    } while (isExist == 0);
    system("cls");
    printf("--------------------------------------------------------------------------------------------------------------------------------\n");
    printf("|�����|���             �������         ��������       |  ������  |����  ��������|�������|  ������  |  ������  |����|����� �����|\n");
    printf("--------------------------------------------------------------------------------------------------------------------------------\n");
    printf("|%-3i  |%-15s %-15s %-15s|%-10s|  %-2i/%02i/%-4i  |  %-3i  |%-10s|%-10s|%-4i|   %02i:%02i   |",
            (info + i)->number, (info + i)->fullname.firstname, (info + i)->fullname.surname, (info + i)->fullname.lastname, (info + i)->country,
            (info + i)->dateOfBirth.day, (info + i)->dateOfBirth.month, (info + i)->dateOfBirth.year, (info + i)->dateOfBirth.age, (info + i)->category,
            (info + i)->model, (info + i)->points, (info + i)->timeOfLap.minutes, (info + i)->timeOfLap.seconds);
    printf("\n");
    printf("--------------------------------------------------------------------------------------------------------------------------------\n");
    while (infoEditFlag == 0) {
        printf("��� ��������?\n");
        printf("1.�����.\n");
        printf("2.���.\n");
        printf("3.�������.\n");
        printf("4.��������.\n");
        printf("5.������.\n");
        printf("6.���� ��������.\n");
        printf("7.����� ��������.\n");
        printf("8.��� ��������.\n");
        printf("9.������.\n");
        printf("10.������ �������.\n");
        printf("11.���������� �����.\n");
        printf("12.������ �����.\n");
        printf("13.������� �����.\n");
        printf("14.�����.\n");
        printf("��� �����: ");
        choice = inputCheck("��� �����: ");
        printf("\n");
        switch (choice) {
            case 1: {
                int newNumber = 0;
                printf("�������� ������.\n");
                do {
                    do {
                        printf("������� ����� �����: ");
                        newNumber = inputCheck("������� ����� �����: ");
                        if (newNumber < 1) printf("[������!]������� ����� ������ 0!\n");
                    } while (newNumber < 1);
                    for (j = 0; j < infoLinesCounter; j++) {
                        if ((info + j)->number == newNumber) {
                            isNumberExist = 1;
                            break;
                        }
                        else isNumberExist = 0;
                    }
                    if (isNumberExist == 1) printf("[������!]�������� � ����� ������� ��� ����������!\n");
                } while (isNumberExist == 1);
                (info + i)->number = newNumber;
                printf("����� ������� �������!\n\n");
                break;
            }
            case 2: {
                printf("��������� �����.\n");
                printf("������� ����� ���: ");
                firstname = limitedStringInput(firstname, 49);
                strcpy((info + i)->fullname.firstname, firstname);
                free(firstname);
                printf("��� ������� ��������!\n\n");
                break;
            }
            case 3: {
                printf("��������� �������.\n");
                printf("������� ����� �������: ");
                surname = limitedStringInput(surname, 49);
                strcpy((info + i)->fullname.surname, surname);
                free(surname);
                printf("������� ������� ��������!\n\n");
                break;
            }
            case 4: {
                printf("��������� ��������.\n");
                printf("������� ����� ��������: ");
                lastname = limitedStringInput(lastname, 49);
                strcpy((info + i)->fullname.lastname, lastname);
                free(lastname);
                printf("�������� ������� ��������!\n\n");
                break;
            }
            case 5: {
                printf("��������� ������.\n");
                printf("������� ����� ������: ");
                country = limitedStringInput(country, 29);
                strcpy((info + i)->country, country);
                free(country);
                printf("������ ������� ��������.\n\n");
                break;
            }
            case 6: {
                printf("��������� ��� ��������.\n");
                int newBirthDay = 0;
                do {
                    printf("������� ����� ���� ��������: ");
                    scanf_s("%i", &newBirthDay);
                    if (newBirthDay < 1 || newBirthDay > 31)
                        printf("[������!]������� ����� �� 1 �� 31!\n");
                } while (newBirthDay < 1 || newBirthDay > 31);
                (info + i)->dateOfBirth.day = newBirthDay;
                printf("���� �������� ������� �������!\n\n");
                break;
            }
            case 7: {
                printf("��������� ������ ��������.\n");
                int newBirthMonth = 0;
                do {
                    printf("������� ����� ����� ��������(������): ");
                    newBirthMonth = inputCheck("������� ����� �����: ");
                    if (newBirthMonth < 1 || newBirthMonth > 12)
                        printf("[������!]������� ����� �� 1 �� 12!\n\n");
                } while (newBirthMonth < 1 || newBirthMonth > 12);
                (info + i)->dateOfBirth.month = newBirthMonth;
                printf("����� �������� ������� �������!\n\n");
                break;
            }
            case 8: {
                printf("��������� ���� ��������.\n");
                int newBirthYear = 0;
                do {
                    printf("������� ����� ��� ��������: ");
                    newBirthYear = inputCheck("������� ����� ��� ��������: ");
                    if (newBirthYear < 1900 || newBirthYear > 2019)
                        printf("[������!]������� ����� �� 1900 �� 2019!\n");
                } while (newBirthYear < 1900 || newBirthYear > 2019);
                if ((info + infoLinesCounter)->dateOfBirth.month > aTm->tm_mon + 1)
                    (info + infoLinesCounter)->dateOfBirth.age = 2018 - (info + infoLinesCounter)->dateOfBirth.year;
                else (info + infoLinesCounter)->dateOfBirth.age = 2019 - (info + infoLinesCounter)->dateOfBirth.year;
                printf("��� �������� ������� �������!\n\n");
                break;
            }
            case 9: {
                printf("��������� �������.\n");
                printf("������� ����� ������: ");
                category = limitedStringInput(category, 29);
                strcpy((info + i)->category, category);
                free(category);
                printf("������ ������� �������!\n\n");
                break;
            }
            case 10: {
                printf("��������� ������ �������.\n");
                printf("������� ����� ������ �������: ");
                model = limitedStringInput(model, 29);
                strcpy((info + i)->model, model);
                free(model);
                printf("������ ������� ������� ��������!\n\n");
                break;
            }
            case 11: {
                printf("��������� ���������� �����.\n");
                do {
                    printf("������� ����� ���������� �����: ");
                    (info + infoLinesCounter)->points = inputCheck("������� ����� ���������� �����: ");
                    if ((info + infoLinesCounter)->points < 0 || (info + infoLinesCounter)->points > 9999)
                        printf("[������!]������� ����� �� 0 �� 9999!\n");
                } while ((info + infoLinesCounter)->points < 0 || (info + infoLinesCounter)->points > 9999);
                printf("���������� ����� ������� ��������!\n\n");
            }
            case 12: {
                printf("��������� ����� �����.\n");
                do {
                    printf("������� ����� ������ �����: ");
                    (info + infoLinesCounter)->timeOfLap.minutes = inputCheck("������� ����� ������ �����: ");
                    if ((info + infoLinesCounter)->timeOfLap.minutes < 0 || (info + infoLinesCounter)->timeOfLap.minutes > 59)
                        printf("[������!]������� ����� �� 0 �� 59!\n");
                } while ((info + infoLinesCounter)->timeOfLap.minutes < 0 || (info + infoLinesCounter)->timeOfLap.minutes > 59);
                printf("������ ����� ������� ��������!\n\n");
                break;
            }
            case 13: {
                printf("��������� ������ �����.\n");
                do {
                    printf("������� ����� ������� �����: ");
                    (info + infoLinesCounter)->timeOfLap.seconds = inputCheck("������� ����� ������� �����: ");
                    if ((info + infoLinesCounter)->timeOfLap.seconds < 0 || (info + infoLinesCounter)->timeOfLap.seconds > 59)
                        printf("[������!]������� ����� �� 0 �� 59!\n");
                } while ((info + infoLinesCounter)->timeOfLap.seconds < 0 || (info + infoLinesCounter)->timeOfLap.seconds > 59);
                printf("������� ����� ������� ��������!\n\n");
                break;
            }
            case 14: infoEditFlag = 1; break;
            default: break;
        }
        if (infoEditFlag == 1) break;
    }
    if ((file = fopen("info.txt", "w")) == NULL) {
        printf("[������!]�������������� ����������: �� ������� ������� ����! ���� �������!\n");
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
        printf("[������!]�������� ����������: ���� �� ������!\n\n");
        return info;
    }
    if (infoLinesCounter == 0) {
        printf("[������!]�������� ����������: ���� ����!\n\n");
        return 0;
    }
    printf("�������� ���������.\n");
    do {
        printf("������� ����� ��������� ��� ��������: ");
        delNumber = inputCheck("������� ����� ��������� ��� ��������: ");
        for (i = 0; i < infoLinesCounter; i++) {
            if (delNumber == (info + i)->number) {
                isNumberExist = 1;
                break;
            }
            else isNumberExist = 0;
        }
        if (isNumberExist == 0) printf("[������!]��������� � ����� ������� �� ����������!\n");
    } while (isNumberExist != 1);
    if ((file = fopen("info.txt", "w")) == NULL) {
        printf("[������!]�������� ����������: �� ������� ������� ����! ���� �������!\n\n");
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
    printf("�������� ������� �����!\n\n");
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
            printf("[������!]�� ���������� ����!\n");
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
    printf("���� ������ � ����������.\n");
    printf("1.������ �� ���������� �����.\n");
    printf("2.������ �� ������� �����.\n");
    printf("3.������ �� ��������.\n");
    printf("4.������ �� ���� ��������.\n");
    printf("5.����� �� ������.\n");
    printf("6.����� �� �������.\n");
    printf("7.����� �� ������.\n");
    printf("9.����� �� �������.\n");
    printf("9.���������� �� ������� �����.\n");
    printf("10.�����.\n");
    printf("��� �����: ");
    choice = inputCheck("��� �����: ");
    printf("\n");
    return choice;
}

int pointsFilter(INFORMATION* info) {
    int points = 0, isAtLeastOneMember = 0;
    if (info == NULL) {
        printf("[������!]����� � ����������: ���� �� ������!\n\n");
        return 0;
    }
    if (infoLinesCounter == 0) {
        printf("[������!]����� � ����������: ���� ����!\n\n");
        return 0;
    }
    do {
        printf("������� ���������� �����: ");
        points = inputCheck("������� ���������� �����: ");
        if (points < 0 || points > 9999)
            printf("[������!]������� ����� ������ 0 � ������ 9999!\n");
    } while (points < 0 || points > 9999);
    printf("���������, � ������� ����� ������ %i: ", points);
    for (int i = 0; i < infoLinesCounter; i++) {
        if ((info + i)->points > points) {
            if (isAtLeastOneMember == 0) {
                printf("\n--------------------------------------------------------------------------------------------------------------------------------\n");
                printf("|�����|���             �������         ��������       |  ������  |����  ��������|�������|  ������  |  ������  |����|����� �����|\n");
                printf("--------------------------------------------------------------------------------------------------------------------------------\n");
            }
            printf("|%-3i  |%-15s %-15s %-15s|%-10s|  %-2i/%02i/%-4i  |  %-3i  |%-10s|%-10s|%-4i|   %02i:%02i   |",
                   (info + i)->number, (info + i)->fullname.firstname, (info + i)->fullname.surname,
                   (info + i)->fullname.lastname, (info + i)->country, (info + i)->dateOfBirth.day,
                   (info + i)->dateOfBirth.month, (info + i)->dateOfBirth.year, (info + i)->dateOfBirth.age,
                   (info + i)->category, (info + i)->model, (info + i)->points, (info + i)->timeOfLap.minutes,
                   (info + i)->timeOfLap.seconds);
            printf("\n");
            isAtLeastOneMember = 1;
        }
        if (isAtLeastOneMember == 1 && i == infoLinesCounter - 1)
            printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
    }
    if (isAtLeastOneMember == 0)
        printf("[������!]��� �� ������ ��������� � ������ ������ %i.\n\n", points);
    return 0;
}

int timeOfLapFilter(INFORMATION* info) {
    int minutesOfLap = 0, secondsOfLap = 0, isAtLeastOneMember = 0;
    if (info == NULL) {
        printf("[������!]����� � ����������: ���� �� ������!\n\n");
        return 0;
    }
    if (infoLinesCounter == 0) {
        printf("[������!]����� � ����������: ���� ����!\n\n");
        return 0;
    }
    do {
        printf("������� ���������� ����� �����: ");
        minutesOfLap = inputCheck("������� ���������� ����� �����: ");
        if (minutesOfLap < 0 || minutesOfLap > 59)
            printf("[������!]������� ����� ������ 0 � ������ 59!\n");
    } while (minutesOfLap < 0 || minutesOfLap > 59);
    do {
        printf("������� ���������� ������ �����: ");
        secondsOfLap = inputCheck("������� ���������� ������ �����: ");
        if (secondsOfLap < 0 || secondsOfLap > 59)
            printf("[������!]������� ����� ������ 0 � ������ 59!\n");
    } while (secondsOfLap < 0 || secondsOfLap > 59);
    printf("���������, � ������� ����� ����� ������ %02i:%02i : ", minutesOfLap, secondsOfLap);
    for (int i = 0; i < infoLinesCounter; i++) {
        if ((info + i)->timeOfLap.minutes < minutesOfLap)
            if ((info + i)->timeOfLap.seconds < ((info + i)->timeOfLap.minutes == minutesOfLap ? secondsOfLap : 60)) {
                if (isAtLeastOneMember == 0) {
                    printf("\n--------------------------------------------------------------------------------------------------------------------------------\n");
                    printf("|�����|���             �������         ��������       |  ������  |����  ��������|�������|  ������  |  ������  |����|����� �����|\n");
                    printf("--------------------------------------------------------------------------------------------------------------------------------\n");
                }
                printf("|%-3i  |%-15s %-15s %-15s|%-10s|  %-2i/%02i/%-4i  |  %-3i  |%-10s|%-10s|%-4i|   %02i:%02i   |",
                       (info + i)->number, (info + i)->fullname.firstname, (info + i)->fullname.surname,
                       (info + i)->fullname.lastname, (info + i)->country, (info + i)->dateOfBirth.day,
                       (info + i)->dateOfBirth.month, (info + i)->dateOfBirth.year, (info + i)->dateOfBirth.age,
                       (info + i)->category, (info + i)->model, (info + i)->points, (info + i)->timeOfLap.minutes,
                       (info + i)->timeOfLap.seconds);
                printf("\n");
                isAtLeastOneMember = 1;
            }
        if (isAtLeastOneMember == 1 && i == infoLinesCounter - 1)
            printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
    }
    if (isAtLeastOneMember == 0)
        printf("[������!]��� �� ������ ��������� � �������� ����� ������ %02i:%02i.\n\n", minutesOfLap, secondsOfLap);
    return 0;
}

int ageFilter(INFORMATION* info) {
    int age = 0, isAtLeastOneMember = 0;
    if (info == NULL) {
        printf("[������!]����� � ����������: ���� �� ������!\n\n");
        return 0;
    }
    if (infoLinesCounter == 0) {
        printf("[������!]����� � ����������: ���� ����!\n\n");
        return 0;
    }
    do {
        printf("������� �������: ");
        age = inputCheck("������� ���������� �����: ");
        if (age < 0 || age > 119)
            printf("[������!]������� ����� ������ 0 � ������ 119!\n");
    } while (age < 0 || age > 119);
    printf("���������, ������� ������� ������ %i: ", age);
    for (int i = 0; i < infoLinesCounter; i++) {
        if ((info + i)->dateOfBirth.age > age) {
            if (isAtLeastOneMember == 0) {
                printf("\n--------------------------------------------------------------------------------------------------------------------------------\n");
                printf("|�����|���             �������         ��������       |  ������  |����  ��������|�������|  ������  |  ������  |����|����� �����|\n");
                printf("--------------------------------------------------------------------------------------------------------------------------------\n");
            }
            printf("|%-3i  |%-15s %-15s %-15s|%-10s|  %-2i/%02i/%-4i  |  %-3i  |%-10s|%-10s|%-4i|   %02i:%02i   |",
                   (info + i)->number, (info + i)->fullname.firstname, (info + i)->fullname.surname,
                   (info + i)->fullname.lastname, (info + i)->country, (info + i)->dateOfBirth.day,
                   (info + i)->dateOfBirth.month, (info + i)->dateOfBirth.year, (info + i)->dateOfBirth.age,
                   (info + i)->category, (info + i)->model, (info + i)->points, (info + i)->timeOfLap.minutes,
                   (info + i)->timeOfLap.seconds);
            printf("\n");
            isAtLeastOneMember = 1;
        }
        if (isAtLeastOneMember == 1 && i == infoLinesCounter - 1)
            printf("================================================================================================================================\n\n");
    }
    if (isAtLeastOneMember == 0)
        printf("[������!]��� �� ������ ��������� � ������ ������ %i.\n\n", age);
    return 0;
}

int yearOfBirthFilter(INFORMATION* info) {
    int yearOfBirth = 0, isAtLeastOneMember = 0;
    if (info == NULL) {
        printf("[������!]����� � ����������: ���� �� ������!\n\n");
        return 0;
    }
    if (infoLinesCounter == 0) {
        printf("[������!]����� � ����������: ���� ����!\n\n");
        return 0;
    }
    do {
        printf("������� ��� ��������: ");
        yearOfBirth = inputCheck("������� ��� ��������: ");
        if (yearOfBirth < 1900 || yearOfBirth > 2019)
            printf("[������!]������� ����� ������ 1900 � ������ 2019!\n");
    } while (yearOfBirth < 1900 || yearOfBirth > 2019);
    printf("���������, ��� �������� � ������� ������ %i: ", yearOfBirth);
    for (int i = 0; i < infoLinesCounter; i++) {
        if ((info + i)->dateOfBirth.year > yearOfBirth) {
            if (isAtLeastOneMember == 0) {
                printf("\n--------------------------------------------------------------------------------------------------------------------------------\n");
                printf("|�����|���             �������         ��������       |  ������  |����  ��������|�������|  ������  |  ������  |����|����� �����|\n");
                printf("--------------------------------------------------------------------------------------------------------------------------------\n");
            }
            printf("|%-3i  |%-15s %-15s %-15s|%-10s|  %-2i/%02i/%-4i  |  %-3i  |%-10s|%-10s|%-4i|   %02i:%02i   |",
                   (info + i)->number, (info + i)->fullname.firstname, (info + i)->fullname.surname,
                   (info + i)->fullname.lastname, (info + i)->country, (info + i)->dateOfBirth.day,
                   (info + i)->dateOfBirth.month, (info + i)->dateOfBirth.year, (info + i)->dateOfBirth.age,
                   (info + i)->category, (info + i)->model, (info + i)->points, (info + i)->timeOfLap.minutes,
                   (info + i)->timeOfLap.seconds);
            printf("\n");
            isAtLeastOneMember = 1;
        }
        if (isAtLeastOneMember == 1 && i == infoLinesCounter - 1)
            printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
    }
    if (isAtLeastOneMember == 0)
        printf("[������!]��� �� ������ ��������� � ����� �������� ������ %i.\n\n", yearOfBirth);
    return 0;
}

int timeOfLapSorting(INFORMATION* info){
    INFORMATION tmp;
    FILE* file = NULL;
    if (info == NULL) {
        printf("[������!]����������: ���� �� ������!\n\n");
        return 0;
    }
    if (infoLinesCounter == 0) {
        printf("[������!]����������: ���� ����!\n\n");
        return 0;
    }
    if (infoLinesCounter != 1){
        for(int i = 1;i < infoLinesCounter; i++)
            for(int j = i; j > 0; j--)
                if((info + (j-1))->timeOfLap.minutes == (info + j)->timeOfLap.minutes){
                    if((info + (j-1))->timeOfLap.seconds > (info + j)->timeOfLap.seconds){
                        tmp = *(info + (j - 1));
                        *(info + (j - 1)) = *(info + j);
                        *(info + j) = tmp;
                    }
                } else if ((info + (j-1))->timeOfLap.minutes > (info + j)->timeOfLap.minutes){
                    tmp = *(info + (j - 1));
                    *(info + (j - 1)) = *(info + j);
                    *(info + j) = tmp;
                }
        if ((file = fopen("info.txt", "w")) == NULL) {
            printf("[������!]����������: �� ������� ������� ����! ���� �������!\n\n");
            return 0;
        }
        for (int j = 0; j < infoLinesCounter; j++) {
            fprintf(file, "%i %s %s %s %s %i %i %i %i %s %s %i %i %i\n", (info + j)->number, (info + j)->fullname.firstname, (info + j)->fullname.surname, (info + j)->fullname.lastname, (info + j)->country, (info + j)->dateOfBirth.day, (info + j)->dateOfBirth.month, (info + j)->dateOfBirth.year, (info + j)->dateOfBirth.age, (info + j)->category, (info + j)->model, (info + j)->points, (info + j)->timeOfLap.minutes, (info + j)->timeOfLap.seconds);
            _flushall();
        }
        fclose(file);
    }
    printf("����������: ������ ������� ������������!\n\n");
    return 0;
}

int numberSearch(INFORMATION* info) {
    int number = 0, isFounded = 0;
    if (info == NULL) {
        printf("[������!]����� � ����������: ���� �� ������!\n\n");
        return 0;
    }
    if (infoLinesCounter == 0) {
        printf("[������!]����� � ����������: ���� ����!\n\n");
        return 0;
    }
    do {
        printf("������� �����: ");
        number = inputCheck("������� �����: ");
        if (number < 0)
            printf("[������!]������� ����� ������ 0!\n");
    } while (number < 0 );
    printf("��������, ����� �������� %i: ", number);
    for (int i = 0; i < infoLinesCounter; i++) {
        if ((info + i)->number == number) {
            printf("\n--------------------------------------------------------------------------------------------------------------------------------\n");
            printf("|�����|���             �������         ��������       |  ������  |����  ��������|�������|  ������  |  ������  |����|����� �����|\n");
            printf("--------------------------------------------------------------------------------------------------------------------------------\n");
            printf("|%-3i  |%-15s %-15s %-15s|%-10s|  %-2i/%02i/%-4i  |  %-3i  |%-10s|%-10s|%-4i|   %02i:%02i   |",
                    (info + i)->number, (info + i)->fullname.firstname, (info + i)->fullname.surname,
                    (info + i)->fullname.lastname, (info + i)->country, (info + i)->dateOfBirth.day,
                    (info + i)->dateOfBirth.month, (info + i)->dateOfBirth.year, (info + i)->dateOfBirth.age,
                    (info + i)->category, (info + i)->model, (info + i)->points, (info + i)->timeOfLap.minutes,
                    (info + i)->timeOfLap.seconds);
            printf("\n");
            printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
            isFounded = 1;
            break;
        }
    }
    if (isFounded == 0)
        printf("[������!]���� ��������� � ������� %i.\n\n", number);

    return 0;
}

int surnameSearch(INFORMATION* info) {
    system("cls");
    int isAtLeastOneMember = 0;
    char *surname;
    if (info == NULL) {
        printf("[������!]����� � ����������: ���� �� ������!\n\n");
        return 0;
    }
    if (infoLinesCounter == 0) {
        printf("[������!]����� � ����������: ���� ����!\n\n");
        return 0;
    }
    printf("������� �������: ");
    surname = limitedStringInput("������� �������: ", 49);
    printf("���������, � �������� %s: ", surname);
    for (int i = 0; i < infoLinesCounter; i++) {
        if (strcmp((info + i)->fullname.surname,surname) == 0) {
            if (isAtLeastOneMember == 0) {
                printf("\n--------------------------------------------------------------------------------------------------------------------------------\n");
                printf("|�����|���             �������         ��������       |  ������  |����  ��������|�������|  ������  |  ������  |����|����� �����|\n");
                printf("--------------------------------------------------------------------------------------------------------------------------------\n");
            }
            printf("|%-3i  |%-15s %-15s %-15s|%-10s|  %-2i/%02i/%-4i  |  %-3i  |%-10s|%-10s|%-4i|   %02i:%02i   |",
                   (info + i)->number, (info + i)->fullname.firstname, (info + i)->fullname.surname,
                   (info + i)->fullname.lastname, (info + i)->country, (info + i)->dateOfBirth.day,
                   (info + i)->dateOfBirth.month, (info + i)->dateOfBirth.year, (info + i)->dateOfBirth.age,
                   (info + i)->category, (info + i)->model, (info + i)->points, (info + i)->timeOfLap.minutes,
                   (info + i)->timeOfLap.seconds);
            printf("\n");
            isAtLeastOneMember = 1;
        }
        if (isAtLeastOneMember == 1 && i == infoLinesCounter - 1)
            printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
    }
    if (isAtLeastOneMember == 0)
        printf("[������!]��� �� ������ ��������� � �������� %s.\n\n", surname);
    system("pause");
    return 0;
}

int searchingAndFiltering(INFORMATION* info){
    system("cls");
    int isInfoSorted = 0;
    while (1) {
        switch (searchAndFilteringMenu()) {
            case 1: pointsFilter(info); break;
            case 2: timeOfLapFilter(info); break;
            case 3: ageFilter(info); break;
            case 4: yearOfBirthFilter(info); break;
            case 5: numberSearch(info); break;
            case 6: surnameSearch(info); break;
            case 7: countrySearch(info); break;
            case 8: categorySearch(info); break;
            case 9: timeOfLapSorting(info); isInfoSorted = 1; break;
            case 10: return isInfoSorted;
            default: break;
        }
    }
}

int countrySearch(INFORMATION* info){
    int isAtLeastOneMember = 0;
    char *country;
    if (info == NULL) {
        printf("[������!]����� � ����������: ���� �� ������!\n\n");
        return 0;
    }
    if (infoLinesCounter == 0) {
        printf("[������!]����� � ����������: ���� ����!\n\n");
        return 0;
    }
    printf("������� ������: ");
    country = limitedStringInput("������� ������: ", 49);
    system("cls");
    printf("���������, �� ������ %s: ", country);
    for (int i = 0; i < infoLinesCounter; i++) {
        if (strcmp((info + i)->country,country) == 0) {
            if (isAtLeastOneMember == 0) {
                printf("\n--------------------------------------------------------------------------------------------------------------------------------\n");
                printf("|�����|���             �������         ��������       |  ������  |����  ��������|�������|  ������  |  ������  |����|����� �����|\n");
                printf("--------------------------------------------------------------------------------------------------------------------------------\n");
            }
            printf("|%-3i  |%-15s %-15s %-15s|%-10s|  %-2i/%02i/%-4i  |  %-3i  |%-10s|%-10s|%-4i|   %02i:%02i   |",
                   (info + i)->number, (info + i)->fullname.firstname, (info + i)->fullname.surname,
                   (info + i)->fullname.lastname, (info + i)->country, (info + i)->dateOfBirth.day,
                   (info + i)->dateOfBirth.month, (info + i)->dateOfBirth.year, (info + i)->dateOfBirth.age,
                   (info + i)->category, (info + i)->model, (info + i)->points, (info + i)->timeOfLap.minutes,
                   (info + i)->timeOfLap.seconds);
            printf("\n");
            isAtLeastOneMember = 1;
        }
        if (isAtLeastOneMember == 1 && i == infoLinesCounter - 1)
            printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
    }
    if (isAtLeastOneMember == 0)
        printf("[������!]��� �� ������ ��������� �� ������ %s.\n\n", country);
    else system("pause");
    return 0;
}

int categorySearch(INFORMATION* info){
    int isAtLeastOneMember = 0;
    char *category;
    if (info == NULL) {
        printf("[������!]����� � ����������: ���� �� ������!\n\n");
        return 0;
    }
    if (infoLinesCounter == 0) {
        printf("[������!]����� � ����������: ���� ����!\n\n");
        return 0;
    }
    printf("������� ������: ");
    category = limitedStringInput("������� ������: ", 49);
    system("cls");
    printf("���������, � �������� %s: ", category);
    for (int i = 0; i < infoLinesCounter; i++) {
        if (strcmp((info + i)->category,category) == 0) {
            if (isAtLeastOneMember == 0) {
                printf("\n--------------------------------------------------------------------------------------------------------------------------------\n");
                printf("|�����|���             �������         ��������       |  ������  |����  ��������|�������|  ������  |  ������  |����|����� �����|\n");
                printf("--------------------------------------------------------------------------------------------------------------------------------\n");
            }
            printf("|%-3i  |%-15s %-15s %-15s|%-10s|  %-2i/%02i/%-4i  |  %-3i  |%-10s|%-10s|%-4i|   %02i:%02i   |",
                   (info + i)->number, (info + i)->fullname.firstname, (info + i)->fullname.surname,
                   (info + i)->fullname.lastname, (info + i)->country, (info + i)->dateOfBirth.day,
                   (info + i)->dateOfBirth.month, (info + i)->dateOfBirth.year, (info + i)->dateOfBirth.age,
                   (info + i)->category, (info + i)->model, (info + i)->points, (info + i)->timeOfLap.minutes,
                   (info + i)->timeOfLap.seconds);
            printf("\n");
            isAtLeastOneMember = 1;
        }
        if (isAtLeastOneMember == 1 && i == infoLinesCounter - 1)
            printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
    }
    if (isAtLeastOneMember == 0)
        printf("[������!]��� �� ������ ��������� � �������� %s.\n\n", category);
    else system("pause");
    return 0;
}