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
#define DECRYPT 1 //������������
#define ENCRYPT 0 //�����������


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


//����
char* stringInputCheck(int limit, const char* message);//������� ����� ������ ����
char* bufferedInput(int limit, const char* inputText);//������� ����� ������������� ���-�� ��������
int checkToEnterOnlyInt(int limit, const char *inputText);//������� ����� ������ �����

//����
void indicateCursor(bool status);//������� ������/������� ������� �����
int menu();//������� �������� ����
int adminSubmenu();//������� ������� ���������������
int userSubmenu();//������� ������� �������������
int userEditMenu(USER* user, int i);//������� ���� �������������� �������������
int memberEditMenu(INFORMATION* info, int i);//������� ���� �������������� ����������
int searchingAndFiltering(INFORMATION* info);//������� ������ ������� ���� ������ � ����������
int searchAndFilteringMenu();//������� ���� ������ � ����������
USER* userManagement(USER* user);//������� ������ ������� ���� ���������� ��������������
int userManagementMenu();//������� ���� ���������� ��������������

// �����
int countLines(const char* filename);//������� �������� ����� � �����
bool checkFile(const char* filename);//������� �������� ����� �� �������������
//true - ���� ����������, false - ���� �� ����������
bool createFile(const char* filename);//������� �������� �����
void crypterTool(int status);//������� ����� ������

//������������
bool adminLogin(USER* user);//������� ����� ���������������
bool userLogin(USER* user);//������� ����� �������������
void registration();//������� ����������� ��������������
USER* usersInit(USER* user);//������� �������� ����� � ����������
USER* userAdd(USER* user);//������� ���������� ��������
USER* userDelete(USER* user);//������� �������� ��������
USER* userEdit(USER* user);//������� �������������� ��������
void displayEditableUser(USER* user, int i);//������� ������ �������������� ��������
void displayAllUsers(USER* user);//������� ������ ���� ���������

//���������
INFORMATION* membersInit(INFORMATION* info);//������� �������� ����� � �����������
INFORMATION* memberAdd(INFORMATION* info);//������� ���������� ���������
INFORMATION* memberEdit(INFORMATION* info);//������� �������������� ���������
INFORMATION* memberDelete(INFORMATION *info);//������� �������� ���������
void displayEditableMember(INFORMATION* info, int i);//������� ������ ������������� ���������
void displayAllMembers(INFORMATION* info);//������� ������ ���� ����������

//���������� � �����
void pointsFilter(INFORMATION* info);//������� ���������� �� �����
void timeOfLapFilter(INFORMATION* info);//������� ���������� �� ������� �����
void ageFilter(INFORMATION* info);//������� ���������� �� ��������
void yearOfBirthFilter(INFORMATION* info);//������� ���������� �� ���� ��������
void timeOfLapSorting(INFORMATION* info);//������� ���������� �� ������� �����
void numberSearch(INFORMATION* info);//������� ������ �� ������
void surnameSearch(INFORMATION* info);//������� ������ �� �������
void countrySearch(INFORMATION* info);//������� ������ �� ������
void categorySearch(INFORMATION* info);//������� ������ �� �������
void displayTopMembers(INFORMATION* info);//������� ������ ���-3 ������ ����������


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    system("color 0B");
    INFORMATION *info = NULL;
    USER *user = NULL;
    user = usersInit(user);
    bool adminSubMenuFlag = false, userSubMenuFlag = false;
    while (true) {
        system("cls");
        switch (menu()) {
            case 1: {
                if (adminLogin(user) == true) {
                    while (adminSubMenuFlag == false) {
                        system("cls");
                        switch (adminSubmenu()) {
                            case 1: {
                                if (checkFile("info.txt") == false) {
                                    printf("[������!]�������� ����������: ���� ��� �� ������!\n");
                                    if ((createFile("info.txt")) != false) {
                                        printf("�������� ����������: ���� ������� ������!\n");
                                        info = membersInit(info);
                                    }
                                    else printf("[������!]�������� ����������: �� ������� ������� ����!\n");
                                } else info = membersInit(info);
                                system("pause");
                                break;
                            }
                            case 2: info = memberAdd(info); system("pause"); break;
                            case 3: info = memberEdit(info); break;
                            case 4: info = memberDelete(info); system("pause"); break;
                            case 5: displayAllMembers(info); system("pause"); break;
                            case 6: searchingAndFiltering(info); break;
                            case 7: user = userManagement(user); break;
                            case 8: adminSubMenuFlag = true; break;
                            default: break;
                        }
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
                                if (checkFile("info.txt") == true) info = membersInit(info);
                                else printf("[������!]�������� ����������: ���� ��� �� ������!\n\n");
                                system("pause");
                                break;
                            }
                            case 2: displayAllMembers(info); system("pause"); break;
                            case 3: displayTopMembers(info); system("pause"); break;
                            case 4: searchingAndFiltering(info); break;
                            case 5: userSubMenuFlag = true; break;
                            default: break;
                        }
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


//�� ��� ������� � ������
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
            printf("[������!]��������� ����!\n");
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
            if (ch == 13 || ch == 9) {
                if (i > 0) {
                    buffer[i] = '\0';
                    putchar('\n');
                    break;
                }
                else {
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
        else printf("[������!]�� ���������� ����!\n");
    }
}


//��� ��� ������� � ����
void indicateCursor(bool status) {
    void* hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(hConsole, &structCursorInfo);
    structCursorInfo.bVisible = status;
    SetConsoleCursorInfo(hConsole, &structCursorInfo);
}

int menu() {
    int choice = 1, ch = ' ';
    char *line[] = { "���� ��� ���������������.", "���� ��� �������������.", "�����.", NULL }, pointer = '>';
    indicateCursor(false);
    while (true) {
        if (ch != 0) {
            system("cls");
            if (ch == KEY_RETURN) {
                indicateCursor(true);
                return choice;
            }
            if (ch == KEY_UP) choice--;
            if (ch == KEY_DOWN) choice++;
            if (choice > 3) choice = 1;
            if (choice < 1) choice = 3;
            printf("����:\n");
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
    int choice = 1, ch = ' ';
    char pointer = '>', *line[] = { "��������/�������� �����.", "���������� ������.", "�������������� ������.",
                                    "�������� ������.", "�������� ���� ������ � ��������� �����.",
                                    "��������� ��������� ������ � ���������� ������.", "���������� ��������������.",
                                    "����� � ����.", NULL };
    indicateCursor(false);
    while (true) {
        if (ch != 0) {
            system("cls");
            if (ch == KEY_RETURN) {
                indicateCursor(true);
                return choice;
            }
            if (ch == KEY_UP) choice--;
            if (ch == KEY_DOWN) choice++;
            if (choice > 8) choice = 1;
            if (choice < 1) choice = 8;
            printf("�������(��� ���������������):\n");
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
    int choice = 1, ch = ' ';
    char pointer = '>', *line[] = { "�������� ����� � �������.", "�������� ���� ������ � ��������� �����.",
                                    "�������� ���-3 ����� ������� ����������.", "��������� ��������� ������ � ���������� ������.",
                                    "����� � ����.", NULL };
    indicateCursor(false);
    while (true) {
        if (ch != 0) {
            system("cls");
            if (ch == KEY_RETURN) {
                indicateCursor(true);
                return choice;
            }
            if (ch == KEY_UP) choice--;
            if (ch == KEY_DOWN) choice++;
            if (choice > 5) choice = 1;
            if (choice < 1) choice = 5;
            printf("�������(��� �������������):\n");
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

int userEditMenu(USER* user, int i) {
    int choice = 1, ch = ' ';
    char pointer = '>', *line[] = { "�������� �����.", "�������� ������.", "�������� ����� ��������������.",
                                    "����� �� ���� �������������� ��������.", NULL };
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
            printf("���� �������������� ���������:\n");
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

int memberEditMenu(INFORMATION* info, int i) {
    int choice = 1, ch = ' ';
    char pointer = '>', *line[] = { "��������� ������ ���������.", "��������� ����� ���������.",
                                    "��������� ������� ���������.", "��������� �������� ���������.",
                                    "��������� ������ ���������.", "��������� ��� �������� ���������.",
                                    "��������� ������ �������� ���������.", "��������� ���� �������� ���������.",
                                    "��������� ������� ���������.", "��������� ������ ������� ���������.",
                                    "��������� ���������� ����� ���������.", "��������� ����� ����� ���������.",
                                    "��������� ������ ����� ���������.", "����� �� ���� �������������� ���������.", NULL };
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
            printf("���� �������������� ���c�����:\n");
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

int searchingAndFiltering(INFORMATION* info) {
    while (1) {
        system("cls");
        switch (searchAndFilteringMenu()) {
            case 1: pointsFilter(info); system("pause"); break;
            case 2: timeOfLapFilter(info); system("pause"); break;
            case 3: ageFilter(info); system("pause"); break;
            case 4: yearOfBirthFilter(info); system("pause"); break;
            case 5: numberSearch(info); system("pause"); break;
            case 6: surnameSearch(info); system("pause"); break;
            case 7: countrySearch(info); system("pause"); break;
            case 8: categorySearch(info); system("pause"); break;
            case 9: timeOfLapSorting(info); system("pause"); break;
            case 10: return 0;
            default: break;
        }
    }
}

int searchAndFilteringMenu() {
    int choice = 1, ch = ' ';
    char pointer = '>', *line[] = { "������ �� ���������� �����.", "������ �� ������� �����.",
                                    "������ �� ��������.", "������ �� ���� ��������.", "����� �� ������.",
                                    "����� �� �������.", "����� �� ������.", "����� �� �������.",
                                    "���������� �� ������� �����.", "����� �� ���� ������ � ����������.", NULL };
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
            printf("���� ������ � ����������:\n");
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

int userManagementMenu() {
    int choice = 1, ch = ' ';
    char pointer = '>', *line[] = { "�������� �������.", "������� �������.", "������������� �������.",
                                    "�������� ���� ���������.", "�����.", NULL };
    indicateCursor(false);
    while (1) {
        if (ch != 0) {
            system("cls");
            if (ch == KEY_RETURN) {
                indicateCursor(true);
                return choice;
            }
            if (ch == KEY_UP) choice--;
            if (ch == KEY_DOWN) choice++;
            if (choice > 5) choice = 1;
            if (choice < 1) choice = 5;
            printf("���� ���������� ��������������/����������������:\n");
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


//�� ��� ������� � �������
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

bool checkFile(const char* filename) {
    FILE* file = NULL;
    if ((file = fopen(filename, "rt+")) == NULL) {
        return false;
    }
    else {
        fclose(file);
        return true;
    }
}

bool createFile(const char* filename) {
    FILE* file = NULL;
    if ((file = fopen(filename, "wt")) != NULL) {
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
    if ((input = fopen("db.txt", "r")) == NULL) {
        printf("[������!]����������: �� ������� ������� ���� � ��������/��������!\n\n");
        system("pause");
        exit(0);
    }
    if ((output = fopen("tempdb.txt", "w")) == NULL) {
        printf("[������!]����������: �� ������� ������� ��������� ���� � ��������/��������!\n\n");
        system("pause");
        exit(0);
    }
    while ((ch = getc(input)) != EOF) {
        if (ch != '\n') {
            ch += key;
            putc(ch, output);
        }
        else putc(ch, output);
    }
    fclose(input);
    fclose(output);
    if ((input = fopen("db.txt", "w")) == NULL) {
        printf("[������!]����������: �� ������� ������������ ���� � ��������/��������!\n\n");
        system("pause");
        exit(0);
    }
    if ((output = fopen("tempdb.txt", "r")) == NULL) {
        printf("[������!]����������: �� ������� ������� ��������� ���� � ��������/��������!\n\n");
        system("pause");
        exit(0);
    }
    while ((ch = getc(output)) != EOF)
        putc(ch, input);
    fclose(output);
    if ((remove("tempdb.txt")) != 0) {
        printf("[������!]����������: �� ������� ������� ��������� ���� � ��������/��������!\n\n");
        system("pause");
        exit(0);
    }
    fclose(input);
}


//�� ��� ������� � ��������������
bool adminLogin(USER *user) {
    system("cls");
    int i = 0, j = 0, counter = 0;
    bool isLoginRight = false, isPasswordRight = false;
    char *login = NULL, password[30], ch;
    do {
        login = bufferedInput(29, "������� �����: ");
        for (i = 0; i < usersLinesCounter; i++)
            if (strcmp(login, (user + i)->login) == 0) {
                isLoginRight = true;
                break;
            }
        if (isLoginRight == false) {
            printf("[������!]������ �������������� �� ����������!\n\n");
            system("pause");
            return false;
        }
    } while (isLoginRight != true);
    do {
        j = 0;
        printf("������� ������: ");
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
                    }
                    else if (j < 29) {
                        password[j++] = ch;
                        putchar(ch);
                    }
                }
            }
        }
        if (strcmp(password, (user + i)->password) == 0)
            isPasswordRight = true;
        else printf("\n[������!]�������� ������!\n");
    } while (isPasswordRight != true);
    if ((user + i)->isAdmin == true) {
        printf("\n�� ������� ��������������.\n\n");
        free(login);
        system("pause");
        return true;
    }
    else {
        printf("\n[������!]�����������: ������� ����� ������������!\n\n");
        system("pause");
        free(login);
        return false;
    }
}

bool userLogin(USER *user) {
    system("cls");
    int i = 0, j = 0, counter = 0;
    bool isLoginRight = false, isPasswordRight = false;
    char *login = NULL, password[30], ch;
    do {
        login = bufferedInput(29, "������� �����: ");
        for (i = 0; i < usersLinesCounter; i++)
            if (strcmp(login, (user + i)->login) == 0) {
                isLoginRight = true;
                break;
            }
        if (isLoginRight == false) {
            printf("[������!]������ ������������ �� ����������!\n\n");
            system("pause");
            free(login);
            return false;
        }
    } while (isLoginRight != true);
    do {
        j = 0;
        printf("������� ������: ");
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
                    }
                    else if (j < 29) {
                        password[j++] = ch;
                        putchar(ch);
                    }
                }
            }
        }
        if (strcmp(password, (user + i)->password) == 0)
            isPasswordRight = true;
        else printf("\n[������!]�������� ������!\n");
    } while (isPasswordRight != true);
    if ((user + i)->isAdmin == false) {
        printf("\n�� ������� ��������������.\n\n");
        free(login);
        system("pause");
        return true;
    }
    else {
        printf("\n[������!]�����������! ������� ����� ��������������!\n\n");
        system("pause");
        free(login);
        return false;
    }
}

void registration() {
    FILE *file = NULL;
    char *login = NULL, password[30], ch;
    int i = 0;
    printf("����������� ��������������.\n\n");
    login = bufferedInput(29, "������� �����: ");
    printf("������� ������: ");
    while (1) {
        ch = (char)_getch();
        if (ch != '\0') {
            if (ch == KEY_RETURN || ch == KEY_TAB) {
                password[i] = '\0';
                break;
            }
            else if (ch == KEY_BKSP && i > 0) {
                i--;
                printf("\b \b");
            }
            else if (ch == KEY_BKSP && i == 0) {
                continue;
            }
            else if (i < 29) {
                password[i++] = ch;
                putchar('*');
            }
        }
    }
    if ((file = fopen("db.txt", "a+")) != NULL) {
        fprintf(file, "%s %s %i\n", login, password, 1);
        fclose(file);
        crypterTool(ENCRYPT);
        printf("\n����� ������������� ������� ���������������!\n\n");
        system("pause");
    } else {
        printf("\n[������!]�����������: �� ������� ������� ���� ��� ���������� ������ ��������������!\n");
        exit(0);
    }
    system("cls");
}

USER* usersInit(USER* user) {
    FILE* file = NULL;
    if ((checkFile("db.txt")) != false) {
        //���� ���� ����������
        usersLinesCounter = countLines("db.txt") - 1;  //��������� ���-�� ����� � �����
        if (usersLinesCounter != 0) {
            //���� ���� ������ ���� ������
            crypterTool(DECRYPT); //������������ ����
            if ((file = fopen("db.txt", "r")) != NULL) {
                //���� ���� ������� ������� ��� ������
                user = (USER *)malloc(usersLinesCounter * (sizeof(USER)));
                for (int i = 0; i < usersLinesCounter; i++)
                    fscanf(file, "%s %s %i", (user + i)->login, (user + i)->password, &((user + i)->isAdmin));
                fclose(file);
            }
            else {
                //���� ���� �� ������� �������
                printf("[������!]������������� �������������: �� ������� ������� ���� � ��������/��������!\n");
                system("pause");
                exit(0);
            }
            crypterTool(ENCRYPT); //����������� ����
        }
        else {
            //���� ��� �� ����� ������
            registration();
            user = usersInit(user);
        }
    }
    else if ((createFile("db.txt")) != false) {
        //���� ���� �� ���������� - �������
        registration();
        user = usersInit(user);
    }
    else {
        //���� ���� �� ���������� � ��� �� ������� �������
        printf("[������!]������������� �������������: �� ������� ������� ���� � ��������/��������!\n");
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
    printf("�������� ������������:\n");
    do {
        login = bufferedInput(29, "������� �����: ");
        for (int i = 0; i < usersLinesCounter; i++) {
            if (strcmp((user + i)->login, login) == 0) {
                isLoginExist = true;
                break;
            }
            else isLoginExist = false;
        }
        if (isLoginExist == true) printf("[������!]����� ������� ��� ����������!\n");
        else strcpy((user + usersLinesCounter)->login, login);
    } while (isLoginExist == true);
    free(login);
    password = bufferedInput(29, "������� ������: ");
    strcpy((user + usersLinesCounter)->password, password);
    free(password);
    do {
        (user + usersLinesCounter)->isAdmin = checkToEnterOnlyInt(1, "�������������?(1 - ��|0 - ���): ");
        if ((user + usersLinesCounter)->isAdmin < 0 || (user + usersLinesCounter)->isAdmin > 1)
            printf("[������!]�� ���������� ����! ������� ����� �� 0 �� 1!\n");
    } while ((user + usersLinesCounter)->isAdmin < 0 || (user + usersLinesCounter)->isAdmin > 1);
    if ((checkFile("db.txt")) != false) {
        //���� ���� ����������
        crypterTool(DECRYPT);//������������
        if ((file = fopen("db.txt", "at+")) != NULL) {
            //���� ���� ������� �������
            fprintf(file, "%s %s %i\n", (user + usersLinesCounter)->login, (user + usersLinesCounter)->password,
                    (user + usersLinesCounter)->isAdmin);
            fclose(file);
            printf("\n������� ������� ��������!\n\n");
            _flushall();
            usersLinesCounter++;
        }
        else printf("[������!]���������� �������������: ������ �������� ����� � ��������/��������! ������������ �� ��������!\n\n"); //���� ���� �� ������� �������
        crypterTool(ENCRYPT);//�����������
    }
    else printf("[������!]���������� �������������: ���� �� ����������!\n\n"); //���� ���� �� ����������
    system("pause");
    return user;
}

USER* userDelete(USER* user) {
    char *login = NULL;
    int i = 0;
    bool isLoginExist = false;
    FILE* file = NULL;
    displayAllUsers(user);
    printf("�������� ��������.\n");
    do {
        login = bufferedInput(29, "������� ����� ��������, ������� �� ������ �������: ");
        for (i = 0; i < usersLinesCounter; i++) {
            if (strcmp((user + i)->login, login) == 0) {
                isLoginExist = true;
                break;
            }
        }
        if (isLoginExist == false)
            printf("[������!]������ �������� �� ����������!\n");
    } while (isLoginExist != true);
    free(login);
    if ((checkFile("db.txt")) != false) {
        //���� ���� ����������
        crypterTool(DECRYPT);//������������
        if ((file = fopen("db.txt", "w")) != NULL) {
            //���� ���� ������� �����������
            for (int j = i; j < usersLinesCounter; j++)
                *(user + j) = *(user + (j + 1));
            user = (USER *)realloc(user, sizeof(USER) * usersLinesCounter);
            usersLinesCounter--;
            for (int j = 0; j < usersLinesCounter; j++)
                fprintf(file, "%s %s %i\n", (user + j)->login, (user + j)->password, (user + j)->isAdmin);
            fclose(file);
            system("cls");
            displayAllUsers(user);
            printf("\n������� ������� �����!\n\n");
        }
        else printf("[������!]�������� �������������: ������ �������� ����� � ��������/��������! ���� �������!\n\n");//���� ���� �� ������� �����������
        crypterTool(ENCRYPT);//�����������
    }
    else printf("[������!]�������� �������������: ������ �������� ����� � ��������/��������!\n\n"); //���� ���� �� ����������
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
        login = bufferedInput(29, "������� ����� ��������, ������� �� ������ ���������������: ");
        for (i = 0; i < usersLinesCounter; i++) {
            if (strcmp((user + i)->login, login) == 0) {
                isLoginExist = true;
                break;
            }
            else isLoginExist = false;
        }
        if (isLoginExist == false)
            printf("[������!]������ �������� �� ����������!\n");
    } while (isLoginExist == false);
    free(login);
    while (editFlag == false) {
        switch (userEditMenu(user, i)) {
            case 1: {
                printf("�������� �����.\n");
                do {
                    newLogin = bufferedInput(29, "������� ����� �����: ");
                    for (int j = 0; j < usersLinesCounter; j++) {
                        if (strcmp((user + j)->login, newLogin) == 0) {
                            isNewLoginExist = true;
                            break;
                        }
                        else isNewLoginExist = false;
                    }
                    if (isNewLoginExist == true) printf("[������!]����� ����� ��� ����������!\n");
                } while (isNewLoginExist == true);
                strcpy((user + i)->login, newLogin);
                displayEditableUser(user, i);
                printf("����� ������� �������!\n\n");
                free(newLogin);
                system("pause");
                break;
            }
            case 2: {
                printf("��������� ������.\n");
                newPassword = bufferedInput(29, "������� ����� ������: ");
                strcpy((user + i)->password, newPassword);
                displayEditableUser(user, i);
                printf("������ ������� �������!\n\n");
                free(newPassword);
                system("pause");
                break;
            }
            case 3: {
                if ((user + i)->isAdmin == true) {
                    (user + i)->isAdmin = false;
                    displayEditableUser(user, i);
                    printf("����� �������������� ������� ��������.\n\n");
                    system("pause");
                    break;
                }
                else {
                    (user + i)->isAdmin = true;
                    displayEditableUser(user, i);
                    printf("����� �������������� ������� ��������.\n\n");
                    system("pause");
                    break;
                }
            }
            case 4: editFlag = true; break;
            default: break;
        }
        if (editFlag == true) break;
    }
    if ((checkFile("db.txt")) != false) {
        //���� ���� ����������
        crypterTool(DECRYPT);//������������
        if ((file = fopen("db.txt", "w")) != NULL) {
            //���� ���� ������� �����������
            for (i = 0; i < usersLinesCounter; i++)
                fprintf(file, "%s %s %i\n", (user + i)->login, (user + i)->password, (user + i)->isAdmin);
            fclose(file);
        }
        else printf("[������!]�������������� �������������: �� ������� ������� ���� � ��������/��������! ���� �������!\n\n");//���� ���� �� ������� �����������
        crypterTool(ENCRYPT);//�����������
    }
    else printf("[������!]�������������� �������������: �� ������� ������� ���� � ��������/��������!\n\n");//���� ���� �� ����������
    return user;
}

void displayEditableUser(USER* user, int i) {
    char yes[] = "��", no[] = "���";
    system("cls");
    printf("-----------------------------------------------------------------------------------------\n");
    printf("|�����:                         |������:                         |����� ��������������: |\n");
    printf("-----------------------------------------------------------------------------------------\n");
    printf("|%-31s|%-32s|%-22s|", (user + i)->login, (user + i)->password, (user + i)->isAdmin == 1 ? yes : no);
    printf("\n-----------------------------------------------------------------------------------------\n\n");
}

void displayAllUsers(USER* user) {
    char yes[] = "��", no[] = "���";
    printf("------------------------------------------------------------------------------------------------\n");
    printf("|�    |�����:                         |������:                         |����� ��������������: |\n");
    printf("------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < usersLinesCounter; i++)
        printf("|%-5i|%-31s|%-32s|%-22s|\n", i + 1, (user + i)->login, (user + i)->password, (user + i)->isAdmin == 1 ? yes : no);
    printf("------------------------------------------------------------------------------------------------\n\n");
}


//�� ��� ������� � �����������
INFORMATION* membersInit(INFORMATION* info) {
    FILE *file = NULL;
    if (info != NULL)
        printf("[������!]�������� ����������: ���� ��� ������!\n\n");
    else {
        if ((file = fopen("info.txt", "rt+")) != NULL) {
            infoLinesCounter = countLines("info.txt") - 1;
            if (infoLinesCounter != -1) {
                info = (INFORMATION *)malloc(infoLinesCounter * sizeof(INFORMATION));
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
    //system("pause");
    return info;
}

INFORMATION* memberAdd(INFORMATION* info) {
    FILE *file = NULL;
    time_t t = time(NULL);
    struct tm *aTm = localtime(&t);
    bool isMemberExist = false;
    char *firstname = NULL, *surname = NULL, *lastname = NULL, *country = NULL, *category = NULL, *model = NULL;
    if (info == NULL)
        printf("[������!]���������� ����������: ���� �� ������!\n\n");
    else if ((file = fopen("info.txt", "a+")) == NULL)
        printf("[������!]���������� ����������: �� ������� ������� ���� ��� ����������!\n");
    else {
        info = (INFORMATION *)realloc(info, ((infoLinesCounter + 1) * sizeof(INFORMATION)));
        printf("���������� ���������.\n");
        do {
            do {
                (info + infoLinesCounter)->number = checkToEnterOnlyInt(3, "������� ����� ���������: ");
                if ((info + infoLinesCounter)->number < 1)
                    printf("[������!]������� ����� ������ 0!\n");
            } while ((info + infoLinesCounter)->number < 1);
            for (int i = 0; i < infoLinesCounter; i++) {
                if ((info + i)->number == (info + infoLinesCounter)->number) {
                    isMemberExist = true;
                    break;
                }
                else isMemberExist = false;
            }
            if (isMemberExist == true) printf("�������� � ����� ������� ��� ����������!\n");
        } while (isMemberExist == true);
        firstname = stringInputCheck(49, "������� ��� ���������: ");
        strcpy((info + infoLinesCounter)->fullname.firstname, firstname);
        free(firstname);
        surname = stringInputCheck(49, "������� ������� ���������: ");
        strcpy((info + infoLinesCounter)->fullname.surname, surname);
        free(surname);
        lastname = stringInputCheck(49, "������� �������� ���������: ");
        strcpy((info + infoLinesCounter)->fullname.lastname, lastname);
        free(lastname);
        country = stringInputCheck(29, "������� ������ ��������: ");
        strcpy((info + infoLinesCounter)->country, country);
        free(country);
        do {
            (info + infoLinesCounter)->dateOfBirth.day = checkToEnterOnlyInt(2, "������� ���� �������� ���������: ");
            if ((info + infoLinesCounter)->dateOfBirth.day < 1 || (info + infoLinesCounter)->dateOfBirth.day > 31)
                printf("[������!]������� ����� �� 1 �� 31!\n");
        } while ((info + infoLinesCounter)->dateOfBirth.day < 1 || (info + infoLinesCounter)->dateOfBirth.day > 31);
        do {
            (info + infoLinesCounter)->dateOfBirth.month = checkToEnterOnlyInt(2, "������� ����� �������� ���������(������): ");
            if ((info + infoLinesCounter)->dateOfBirth.month < 1 || (info + infoLinesCounter)->dateOfBirth.month > 12)
                printf("[������!]������� ����� �� 1 �� 12!\n");
        } while ((info + infoLinesCounter)->dateOfBirth.month < 1 || (info + infoLinesCounter)->dateOfBirth.month > 12);
        do {
            (info + infoLinesCounter)->dateOfBirth.year = checkToEnterOnlyInt(4, "������� ��� �������� ���������: ");
            if ((info + infoLinesCounter)->dateOfBirth.year < 1900 ||
                (info + infoLinesCounter)->dateOfBirth.year > 2019)
                printf("[������!]������� ����� �� 1900 �� 2019!\n");
        } while ((info + infoLinesCounter)->dateOfBirth.year < 1900 ||
                 (info + infoLinesCounter)->dateOfBirth.year > 2019);
        if ((info + infoLinesCounter)->dateOfBirth.month > aTm->tm_mon + 1)
            (info + infoLinesCounter)->dateOfBirth.age = 2018 - (info + infoLinesCounter)->dateOfBirth.year;
        else (info + infoLinesCounter)->dateOfBirth.age = 2019 - (info + infoLinesCounter)->dateOfBirth.year;
        category = stringInputCheck(29, "������� ������ ���������: ");
        strcpy((info + infoLinesCounter)->category, category);
        free(category);
        model = stringInputCheck(29, "������� ������ ������� ���������: ");
        strcpy((info + infoLinesCounter)->model, model);
        free(model);
        do {
            (info + infoLinesCounter)->points = checkToEnterOnlyInt(4, "������� ���������� ����� ���������: ");
            if ((info + infoLinesCounter)->points < 0 || (info + infoLinesCounter)->points > 9999)
                printf("[������!]������� ����� �� 0 �� 9999!\n");
        } while ((info + infoLinesCounter)->points < 0 || (info + infoLinesCounter)->points > 9999);
        do {
            (info + infoLinesCounter)->timeOfLap.minutes = checkToEnterOnlyInt(2, "������� ������ ����� ���������: ");
            if ((info + infoLinesCounter)->timeOfLap.minutes < 0 || (info + infoLinesCounter)->timeOfLap.minutes > 59)
                printf("[������!]������� ����� �� 0 �� 59!\n");
        } while ((info + infoLinesCounter)->timeOfLap.minutes < 0 || (info + infoLinesCounter)->timeOfLap.minutes > 59);
        do {
            (info + infoLinesCounter)->timeOfLap.seconds = checkToEnterOnlyInt(2, "������� ������� ����� ���������: ");
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
    return info;
}

INFORMATION* memberDelete(INFORMATION *info) {
    int delNumber = 0, i = 0;
    bool isNumberExist = false;
    FILE *file = NULL;
    if (info == NULL) {
        printf("[������!]�������� ����������: ���� �� ������!\n\n");
    }
    else if (infoLinesCounter == 0) {
        printf("[������!]�������� ����������: ���� ����!\n\n");
    }
    else {
        displayAllMembers(info);
        printf("�������� ���������.\n");
        do {
            delNumber = checkToEnterOnlyInt(3, "������� ����� ��������� ��� ��������: ");
            for (i = 0; i < infoLinesCounter; i++) {
                if (delNumber == (info + i)->number) {
                    isNumberExist = true;
                    break;
                }
                else isNumberExist = false;
            }
            if (isNumberExist == false) printf("[������!]��������� � ����� ������� �� ����������!\n");
        } while (isNumberExist != true);
        for (int j = i; j < infoLinesCounter; j++)
            *(info + j) = *(info + (j + 1));
        info = (INFORMATION*)realloc(info, sizeof(INFORMATION)*infoLinesCounter);
        infoLinesCounter--;
        if ((checkFile("info.txt")) != false) {
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
                printf("�������� ������� �����!\n\n");
            }
            else printf("[������!]�������� ����������: �� ������� ������������ ����! ���� �������!\n\n");
        }
        else printf("[������!]�������� ����������: �� ������� ����� ����!\n\n");
    }
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
        printf("[������!]�������������� ����������: ���� �� ������!\n\n");
        system("pause");
    }
    else if (infoLinesCounter == 0) {
        printf("[������!]�������������� ����������: ���� ����!\n\n");
        system("pause");
    }
    else {
        displayAllMembers(info);
        do {
            number = checkToEnterOnlyInt(3, "������� ����� ���������, �������� ����� ���������������: ");
            for (i = 0; i < infoLinesCounter; i++) {
                if ((info + i)->number == number) {
                    isMemberExist = true;
                    break;
                }
                else isMemberExist = false;
            }
            if (isMemberExist == false) printf("[������!]��������� � ����� ������� �� ����������!\n");
        } while (isMemberExist == false);
        while (infoEditFlag == false) {
            switch (memberEditMenu(info, i)) {
                case 1: {
                    printf("�������� ������ ���������.\n");
                    do {
                        do {
                            newNumber = checkToEnterOnlyInt(3, "������� ����� ����� ���������: ");
                            if (newNumber < 1)
                                printf("[������!]������� ����� ������ 0!\n");
                        } while (newNumber < 1);
                        for (j = 0; j < infoLinesCounter; j++) {
                            if ((info + j)->number == newNumber) {
                                isNumberExist = true;
                                break;
                            }
                            else isNumberExist = false;
                        }
                        if (isNumberExist == true)
                            printf("[������!]�������� � ����� ������� ��� ����������!\n");
                    } while (isNumberExist == true);
                    (info + i)->number = newNumber;
                    displayEditableMember(info, i);
                    printf("����� ��������� ������� �������!\n\n");
                    system("pause");
                    break;
                }
                case 2: {
                    printf("��������� ����� ���������.\n");
                    firstname = stringInputCheck(49, "������� ����� ��� ���������: ");
                    strcpy((info + i)->fullname.firstname, firstname);
                    free(firstname);
                    displayEditableMember(info, i);
                    printf("��� ��������� ������� ��������!\n\n");
                    system("pause");
                    break;
                }
                case 3: {
                    printf("��������� ������� ���������.\n");
                    surname = stringInputCheck(49, "������� ����� ������� ���������: ");
                    strcpy((info + i)->fullname.surname, surname);
                    free(surname);
                    displayEditableMember(info, i);
                    printf("������� ��������� ������� ��������!\n\n");
                    system("pause");
                    break;
                }
                case 4: {
                    printf("��������� �������� ���������.\n");
                    lastname = stringInputCheck(49, "������� ����� �������� ���������: ");
                    strcpy((info + i)->fullname.lastname, lastname);
                    free(lastname);
                    displayEditableMember(info, i);
                    printf("�������� ��������� ������� ��������!\n\n");
                    system("pause");
                    break;
                }
                case 5: {
                    printf("��������� ������ ���������.\n");
                    country = stringInputCheck(29, "������� ����� ������ ���������: ");
                    strcpy((info + i)->country, country);
                    free(country);
                    displayEditableMember(info, i);
                    printf("������ ��������� ������� ��������.\n\n");
                    system("pause");
                    break;
                }
                case 6: {
                    printf("��������� ��� �������� ���������.\n");
                    do {
                        newBirthDay = checkToEnterOnlyInt(2, "������� ����� ���� �������� ���������: ");
                        if (newBirthDay < 1 || newBirthDay > 31)
                            printf("[������!]������� ����� �� 1 �� 31!\n");
                    } while (newBirthDay < 1 || newBirthDay > 31);
                    (info + i)->dateOfBirth.day = newBirthDay;
                    displayEditableMember(info, i);
                    printf("���� �������� ��������� ������� �������!\n\n");
                    system("pause");
                    break;
                }
                case 7: {
                    printf("��������� ������ �������� ���������.\n");
                    do {
                        newBirthMonth = checkToEnterOnlyInt(2, "������� ����� ����� �������� ���������(������): ");
                        if (newBirthMonth < 1 || newBirthMonth > 12)
                            printf("[������!]������� ����� �� 1 �� 12!\n\n");
                    } while (newBirthMonth < 1 || newBirthMonth > 12);
                    (info + i)->dateOfBirth.month = newBirthMonth;
                    displayEditableMember(info, i);
                    printf("����� �������� ��������� ������� �������!\n\n");
                    system("pause");
                    break;
                }
                case 8: {
                    printf("��������� ���� �������� ���������.\n");
                    do {
                        newBirthYear = checkToEnterOnlyInt(4, "������� ����� ��� �������� ���������: ");
                        if (newBirthYear < 1900 || newBirthYear > 2019)
                            printf("[������!]������� ����� �� 1900 �� 2019!\n");
                    } while (newBirthYear < 1900 || newBirthYear > 2019);
                    (info + i)->dateOfBirth.year = newBirthYear;
                    if ((info + i)->dateOfBirth.month >= aTm->tm_mon + 1)
                        (info + i)->dateOfBirth.age = 2018 - (info + i)->dateOfBirth.year;
                    else
                        (info + i)->dateOfBirth.age = 2019 - (info + i)->dateOfBirth.year;
                    displayEditableMember(info, i);
                    printf("��� �������� ��������� ������� �������!\n\n");
                    system("pause");
                    break;
                }
                case 9: {
                    printf("��������� ������� ���������.\n");
                    category = stringInputCheck(29, "������� ����� ������ ���������: ");
                    strcpy((info + i)->category, category);
                    free(category);
                    displayEditableMember(info, i);
                    printf("������ ��������� ������� �������!\n\n");
                    system("pause");
                    break;
                }
                case 10: {
                    printf("��������� ������ ������� ���������.\n");
                    model = stringInputCheck(29, "������� ����� ������ ������� ���������: ");
                    strcpy((info + i)->model, model);
                    free(model);
                    displayEditableMember(info, i);
                    printf("������ ������� ��������� ������� ��������!\n\n");
                    system("pause");
                    break;
                }
                case 11: {
                    printf("��������� ���������� ����� ���������.\n");
                    do {
                        (info + i)->points = checkToEnterOnlyInt(4, "������� ����� ���������� ����� ���������: ");
                        if ((info + i)->points < 0 || (info + i)->points > 9999)
                            printf("[������!]������� ����� �� 0 �� 9999!\n");
                    } while ((info + i)->points < 0 || (info + i)->points > 9999);
                    displayEditableMember(info, i);
                    printf("���������� ����� ��������� ������� ��������!\n\n");
                    system("pause");
                    break;
                }
                case 12: {
                    printf("��������� ����� ����� ���������.\n");
                    do {
                        (info + i)->timeOfLap.minutes = checkToEnterOnlyInt(2, "������� ����� ������ ����� ���������: ");
                        if ((info + i)->timeOfLap.minutes < 0 || (info + i)->timeOfLap.minutes > 59)
                            printf("[������!]������� ����� �� 0 �� 59!\n");
                    } while ((info + i)->timeOfLap.minutes < 0 || (info + i)->timeOfLap.minutes > 59);
                    displayEditableMember(info, i);
                    printf("������ ����� ��������� ������� ��������!\n\n");
                    system("pause");
                    break;
                }
                case 13: {
                    printf("��������� ������ ����� ���������.\n");
                    do {
                        (info + i)->timeOfLap.seconds = checkToEnterOnlyInt(2, "������� ����� ������� ����� ���������: ");
                        if ((info + i)->timeOfLap.seconds < 0 || (info + i)->timeOfLap.seconds > 59)
                            printf("[������!]������� ����� �� 0 �� 59!\n");
                    } while ((info + i)->timeOfLap.seconds < 0 || (info + i)->timeOfLap.seconds > 59);
                    displayEditableMember(info, i);
                    printf("������� ����� ��������� ������� ��������!\n\n");
                    system("pause");
                    break;
                }
                case 14: infoEditFlag = true; break;
                default: break;
            }
        }
        if ((checkFile("info.txt") != false)) {
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
            }
            else printf("[������!]�������������� ����������: �� ������� ������������ ����! ���� �������!\n");
        }
        else printf("[������!]�������������� ����������: �� ������� ����� ����!\n");
    }
    return info;
}

void displayEditableMember(INFORMATION* info, int i) {
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

void displayAllMembers(INFORMATION* info) {
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
}


//�� ��� ������� � ����������� � �������
void pointsFilter(INFORMATION* info) {
    int points = 0;
    bool isAtLeastOneMember = false;
    if (info == NULL)
        printf("[������!]����� � ����������: ���� �� ������!\n\n");
    else if (infoLinesCounter == 0)
        printf("[������!]����� � ����������: ���� ����!\n\n");
    else {
        do {
            points = checkToEnterOnlyInt(4, "������� ���������� �����: ");
            if (points < 0 || points > 9999)
                printf("[������!]������� ����� ������ 0 � ������ 9999!\n");
        } while (points < 0 || points > 9999);
        system("cls");
        printf("���������, � ������� ����� ������ %i: ", points);
        for (int i = 0; i < infoLinesCounter; i++) {
            if ((info + i)->points > points) {
                if (isAtLeastOneMember == false) {
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
                isAtLeastOneMember = true;
            }
            if (isAtLeastOneMember == true && i == infoLinesCounter - 1)
                printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
        }
        if (isAtLeastOneMember == false)
            printf("[������!]��� �� ������ ��������� � ������ ������ %i.\n\n", points);
    }
    //system("pause");
}

void timeOfLapFilter(INFORMATION* info) {
    int minutesOfLap = 0, secondsOfLap = 0;
    bool isAtLeastOneMember = false;
    if (info == NULL) {
        printf("[������!]����� � ����������: ���� �� ������!\n\n");
    }
    else if (infoLinesCounter == 0) {
        printf("[������!]����� � ����������: ���� ����!\n\n");
    }
    else {
        do {
            minutesOfLap = checkToEnterOnlyInt(2, "������� ���������� ����� �����: ");
            if (minutesOfLap < 0 || minutesOfLap > 59)
                printf("[������!]������� ����� ������ 0 � ������ 59!\n");
        } while (minutesOfLap < 0 || minutesOfLap > 59);
        do {
            secondsOfLap = checkToEnterOnlyInt(2, "������� ���������� ������ �����: ");
            if (secondsOfLap < 0 || secondsOfLap > 59)
                printf("[������!]������� ����� ������ 0 � ������ 59!\n");
        } while (secondsOfLap < 0 || secondsOfLap > 59);
        system("cls");
        printf("���������, � ������� ����� ����� ������ %02i:%02i : ", minutesOfLap, secondsOfLap);
        for (int i = 0; i < infoLinesCounter; i++) {
            if ((info + i)->timeOfLap.minutes < minutesOfLap)
                if ((info + i)->timeOfLap.seconds <
                    ((info + i)->timeOfLap.minutes == minutesOfLap ? secondsOfLap : 60)) {
                    if (isAtLeastOneMember == false) {
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
                    isAtLeastOneMember = true;
                }
            if (isAtLeastOneMember == true && i == infoLinesCounter - 1)
                printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
        }
        if (isAtLeastOneMember == false)
            printf("[������!]��� �� ������ ��������� � �������� ����� ������ %02i:%02i.\n\n", minutesOfLap,
                   secondsOfLap);
    }
    //system("pause");
}

void ageFilter(INFORMATION* info) {
    int age = 0;
    bool isAtLeastOneMember = false;
    if (info == NULL)
        printf("[������!]����� � ����������: ���� �� ������!\n\n");
    else if (infoLinesCounter == 0)
        printf("[������!]����� � ����������: ���� ����!\n\n");
    else {
        do {
            age = checkToEnterOnlyInt(3, "������� �������: ");
            if (age < 0 || age > 119)
                printf("[������!]������� ����� ������ 0 � ������ 119!\n");
        } while (age < 0 || age > 119);
        system("cls");
        printf("���������, ������� ������� ������ %i: ", age);
        for (int i = 0; i < infoLinesCounter; i++) {
            if ((info + i)->dateOfBirth.age > age) {
                if (isAtLeastOneMember == false) {
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
                isAtLeastOneMember = true;
            }
            if (isAtLeastOneMember == true && i == infoLinesCounter - 1)
                printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
        }
        if (isAtLeastOneMember == false)
            printf("[������!]��� �� ������ ��������� � ������ ������ %i.\n\n", age);
    }
    //system("pause");
}

void yearOfBirthFilter(INFORMATION* info) {
    int yearOfBirth = 0;
    bool isAtLeastOneMember = false;
    if (info == NULL)
        printf("[������!]����� � ����������: ���� �� ������!\n\n");
    else if (infoLinesCounter == 0)
        printf("[������!]����� � ����������: ���� ����!\n\n");
    else {
        do {
            yearOfBirth = checkToEnterOnlyInt(4, "������� ��� ��������: ");
            if (yearOfBirth < 1900 || yearOfBirth > 2019)
                printf("[������!]������� ����� ������ 1900 � ������ 2019!\n");
        } while (yearOfBirth < 1900 || yearOfBirth > 2019);
        system("cls");
        printf("���������, ��� �������� � ������� ������ %i: ", yearOfBirth);
        for (int i = 0; i < infoLinesCounter; i++) {
            if ((info + i)->dateOfBirth.year > yearOfBirth) {
                if (isAtLeastOneMember == false) {
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
                isAtLeastOneMember = true;
            }
            if (isAtLeastOneMember == true && i == infoLinesCounter - 1) {
                printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
            }
        }
        if (isAtLeastOneMember == false)
            printf("[������!]��� �� ������ ��������� � ����� �������� ������ %i.\n\n", yearOfBirth);
    }
    //system("pause");
}

void timeOfLapSorting(INFORMATION* info) {
    FILE* file = NULL;
    INFORMATION tmp;
    if (info == NULL)
        printf("[������!]����������: ���� �� ������!\n\n");
    else if (infoLinesCounter == 0)
        printf("[������!]����������: ���� ����!\n\n");
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
                    }
                    else if ((info + (j - 1))->timeOfLap.minutes > (info + j)->timeOfLap.minutes) {
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
        }
        else printf("[������!]����������: �� ������� ������� ����! ���� �������!\n\n");
    }
    //system("pause");
}

void numberSearch(INFORMATION* info) {
    int number = 0;
    bool isFounded = false;
    if (info == NULL)
        printf("[������!]����� � ����������: ���� �� ������!\n\n");
    else if (infoLinesCounter == 0)
        printf("[������!]����� � ����������: ���� ����!\n\n");
    else {
        do {
            number = checkToEnterOnlyInt(3, "������� �����: ");
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
                isFounded = true;
                break;
            }
        }
        if (isFounded == false)
            printf("[������!]���� ��������� � ������� %i.\n\n", number);
    }
    //system("pause");
}

void surnameSearch(INFORMATION* info) {
    bool isAtLeastOneMember = false;
    char *surname = NULL;
    if (info == NULL)
        printf("[������!]����� � ����������: ���� �� ������!\n\n");
    else if (infoLinesCounter == 0)
        printf("[������!]����� � ����������: ���� ����!\n\n");
    else {
        surname = stringInputCheck(49, "������� �������: ");
        system("cls");
        printf("���������, � �������� %s: ", surname);
        for (int i = 0; i < infoLinesCounter; i++) {
            if (strcmp((info + i)->fullname.surname, surname) == 0) {
                if (isAtLeastOneMember == false) {
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
                isAtLeastOneMember = true;
            }
            if (isAtLeastOneMember == true && i == infoLinesCounter - 1)
                printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
        }
        if (isAtLeastOneMember == false)
            printf("[������!]��� �� ������ ��������� � �������� %s.\n\n", surname);
    }
    //system("pause");
}

void countrySearch(INFORMATION* info) {
    bool isAtLeastOneMember = false;
    char *country = NULL;
    if (info == NULL)
        printf("[������!]����� � ����������: ���� �� ������!\n\n");
    else if (infoLinesCounter == 0)
        printf("[������!]����� � ����������: ���� ����!\n\n");
    else {
        country = stringInputCheck(49, "������� ������: ");
        system("cls");
        printf("���������, �� ������ %s: ", country);
        for (int i = 0; i < infoLinesCounter; i++) {
            if (strcmp((info + i)->country, country) == 0) {
                if (isAtLeastOneMember == false) {
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
                isAtLeastOneMember = true;
            }
            if (isAtLeastOneMember == true && i == infoLinesCounter - 1)
                printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
        }
        if (isAtLeastOneMember == false)
            printf("[������!]��� �� ������ ��������� �� ������ %s.\n\n", country);
    }
    //system("pause");
}

void categorySearch(INFORMATION* info) {
    bool isAtLeastOneMember = false;
    char *category = NULL;
    if (info == NULL)
        printf("[������!]����� � ����������: ���� �� ������!\n\n");
    else if (infoLinesCounter == 0)
        printf("[������!]����� � ����������: ���� ����!\n\n");
    else {
        category = stringInputCheck(49, "������� ������: ");
        system("cls");
        printf("���������, � �������� %s: ", category);
        for (int i = 0; i < infoLinesCounter; i++) {
            if (strcmp((info + i)->category, category) == 0) {
                if (isAtLeastOneMember == false) {
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
                isAtLeastOneMember = true;
            }
            if (isAtLeastOneMember == true && i == infoLinesCounter - 1)
                printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
        }
        if (isAtLeastOneMember == false)
            printf("[������!]��� �� ������ ��������� � �������� %s.\n\n", category);
    }
    //system("pause");
}

void displayTopMembers(INFORMATION* info) {
    INFORMATION *infoCopy = NULL, tmp;
    system("cls");
    if (info == NULL)
        printf("[������!]����� � ����������: ���� �� ������!\n\n");
    else if (infoLinesCounter == 0)
        printf("[������!]����� � ����������: ���� ����!\n\n");
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
}