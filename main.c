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
USER *user = NULL;
INFORMATION *info = NULL;


//����
char* stringInputCheck(int limit, const char* message);//������� ����� ������ ����
char* bufferedInput(int limit, const char* inputText);//������� ����� ������������� ���-�� ��������
int checkToEnterOnlyInt(int limit, const char *inputText);//������� ����� ������ �����
char* maskedPasswordInput(int limit, const char* message);

//����
void indicateCursor(bool status);//������� ������/������� ������� �����
int menu();//������� �������� ����
int adminSubmenu();//������� ������� ���������������
int userSubmenu();//������� ������� �������������
int userEditMenu(int i);//������� ���� �������������� �������������
int memberEditMenu(int i);//������� ���� �������������� ����������
void searchingAndFiltering();//������� ������ ������� ���� ������ � ����������
int searchAndFilteringMenu();//������� ���� ������ � ����������
void userManagement();//������� ������ ������� ���� ���������� ��������������
int userManagementMenu();//������� ���� ���������� ��������������
int userLoginOrRegMenu();//������� ������� ����� ��� �������������

// �����
bool checkFile(const char* filename);//������� �������� ����� �� ������������� �����
//true - ���� ����������, false - ���� �� ����������
bool createFile(const char* filename);//������� �������� �����
void crypterTool(int status);//������� ����� ������

//������������
bool adminLogin();//������� ����� ���������������
bool userLogin();//������� ����� �������������
void firstStartAdminReg();//������� ����������� �������������� ��� ������ �������
void usersInit();//������� ������ ��������� �� �����
void userAdd();//������� ���������� ��������
void userDelete();//������� �������� ��������
void userEdit();//������� �������������� ��������
void displayEditableUser(int i);//������� ������ ���������� � ������������� ��������
void displayAllUsers();//������� ������ ���������� � ���� ���������
void userReg();//������� ����������� ������������

//���������
void membersOpenAdmin();//������� ��������/�������� ����� ��� �������������
void membersOpenUser();//������� �������� ����� ��� �������������
void membersInit();//������� ������ ���������� �� ���������� �� �����
void memberAdd();//������� ���������� ���������
void memberEdit();//������� �������������� ���������
void memberDelete();//������� �������� ���������
void displayEditableMember(int i);//������� ������ ���������� �� ������������� ���������
void displayAllMembers();//������� ������ ���������� � ���� ����������

//���������� � �����
void pointsFilter();//������� ���������� ���������� �� �����
void timeOfLapFilter();//������� ���������� ���������� �� ������� �����
void ageFilter();//������� ���������� ���������� �� ��������
void yearOfBirthFilter();//������� ���������� ���������� �� ���� ��������
void timeOfLapSorting();//������� ���������� ���������� �� ������� �����
void numberSearch();//������� ������ ���������� �� ������
void surnameSearch();//������� ������ ���������� �� �������
void countrySearch();//������� ������ ����������� �� ������
void categorySearch();//������� ������ ���������� �� �������
void displayTopMembers();//������� ������ ���-3 ������ ����������


int main() {
    setlocale(LC_ALL, "Rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    system("color 0B");
    system("mode con cols=128 lines=32");
    indicateCursor(false);
    printf("--------------------------------------------------------------------------------------------------------------------------------\n"
           "                            ��������� ����� ���������� �� ���������� ������������ �� ���� �� �������                            \n"
           "--------------------------------------------------------------------------------------------------------------------------------\n"
           "                                                                                                                  � by Minilooth");
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
            printf("[������!]��������� ����!");
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
            if (ch == 13 || ch == 9) {
                if (i > 0) {
                    buffer[i] = '\0';
                    putchar('\n');
                    break;
                }
                else {
                    printf("\n[������!]������� ���� �� ���� ������!");
                    Sleep(1000);
                    printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
                    printf("%s", inputText);
                }
            }
            else if (ch == 8 && i > 0) {
                i--;
                printf("\b \b");
            }
            else if (ch == 8 && !i)
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
            printf("[������!]�� ���������� ����!");
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
                printf("\n[������!]������ �� ����� ��������� ������ "" ""!");
                Sleep(1000);
                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
            } else return password;
        } else {
            printf("\n[������!]������� ���� �� ���� ������!");
            Sleep(1000);
            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
        }
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
    int choice = 1, ch = (int)NULL;
    bool isShowed = false;
    const char *line[] = { "���� ��� ���������������.", "���� ��� �������������.", "�����.", NULL }, pointer = '>';
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
    int choice = 1, ch = (int)NULL;
    bool isShowed = false;
    const char pointer = '>', *line[] = { "��������/�������� �����.", "���������� ������.", "�������������� ������.",
                                          "�������� ������.", "�������� ���� ������ � ��������� �����.",
                                          "��������� ��������� ������ � ���������� ������.", "���������� ��������������.",
                                          "����� � ����.", NULL };
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
    int choice = 1, ch = (int)NULL;
    bool isShowed = false;
    const char pointer = '>', *line[] = { "�������� ����� � �������.", "�������� ���� ������ � ��������� �����.",
                                          "�������� ���-3 ����� ������� ����������.", "��������� ��������� ������ � ���������� ������.",
                                          "����� � ����.", NULL };
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

int userEditMenu(int i) {
    int choice = 1, ch = (int)NULL;
    bool isShowed = false;
    const char pointer = '>', *line[] = { "�������� �����.", "�������� ������.", "�������� ����� ��������������.",
                                          "����� �� ���� �������������� ��������.", NULL };
    indicateCursor(false);
    while (true) {
        if (ch == KEY_RETURN || ch == KEY_UP || ch == KEY_DOWN || !isShowed) {
            isShowed = true;
            displayEditableUser(i);
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

int memberEditMenu(int i) {
    int choice = 1, ch = (int)NULL;
    bool isShowed = false;
    const char pointer = '>', *line[] = { "��������� ������ ���������.", "��������� ����� ���������.",
                                          "��������� ������� ���������.", "��������� �������� ���������.",
                                          "��������� ������ ���������.", "��������� ��� �������� ���������.",
                                          "��������� ������ �������� ���������.", "��������� ���� �������� ���������.",
                                          "��������� ������� ���������.", "��������� ������ ������� ���������.",
                                          "��������� ���������� ����� ���������.", "��������� ����� ����� ���������.",
                                          "��������� ������ ����� ���������.", "����� �� ���� �������������� ���������.", NULL };
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
    const char pointer = '>', *line[] = { "������ �� ���������� �����.", "������ �� ������� �����.",
                                          "������ �� ��������.", "������ �� ���� ��������.", "����� �� ������.",
                                          "����� �� �������.", "����� �� ������.", "����� �� �������.",
                                          "���������� �� ������� �����.", "����� �� ���� ������ � ����������.", NULL };
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

void userManagement() {
    while (1) {
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
                system("cls");
                displayAllUsers();
                system("pause");
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
    const char pointer = '>', *line[] = { "�������� �������.", "������� �������.", "������������� �������.",
                                          "�������� ���� ���������.", "����� �� ���� ���������� ��������������/����������������.", NULL };
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

int userLoginOrRegMenu(){
    int choice = 1, ch = (int)NULL;
    bool isShowed = false;
    const char pointer = '>', *line[] = { "�����.", "������������������.", "�������� � ����." , NULL };
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
            printf("���� ��� �������������:\n");
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
        printf("[������!]����������: �� ������� ������� ���� � ��������/��������!\n\n");
        system("pause");
        exit(0);
    }
    if (!(output = fopen("tempdb.dat", "wb"))) {
        printf("[������!]����������: �� ������� ������� ��������� ���� � ��������/��������!\n\n");
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
        printf("[������!]����������: �� ������� ������������ ���� � ��������/��������!\n\n");
        system("pause");
        exit(0);
    }
    if (!(output = fopen("tempdb.dat", "rb"))) {
        printf("[������!]����������: �� ������� ������� ��������� ���� � ��������/��������!\n\n");
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
        printf("\n[������!]����������: �� ������� ������� ��������� ���� � ��������/��������!\n\n");
        system("pause");
        exit(0);
    }
    fclose(input);
}


//�� ��� ������� � ��������������
bool adminLogin() {
    system("cls");
    int i = 0, j = 0, counter = 0;
    bool isLoginRight = false, isPasswordRight = false;
    char *login = NULL, password[30], ch;
    do {
        login = bufferedInput(29, "������� �����: ");
        for (i = 0; i < usersLinesCounter; i++)
            if (!strcmp(login, (user + i)->login)) {
                isLoginRight = true;
                break;
            }
        if (!isLoginRight) {
            printf("[������!]������ �������������� �� ����������!\n\n");
            system("pause");
            return false;
        }
    } while (!isLoginRight);
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
        if (!strcmp(password, (user + i)->password))
            isPasswordRight = true;
        else {
            printf("\n[������!]�������� ������!");
            Sleep(1000);
            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
        }
    } while (!isPasswordRight);
    if ((user + i)->isAdmin) {
        printf("\n\n�� ������� ��������������!");
        Sleep(1000);
        printf("%c[2K\r����� ����������, %s!\n\n", 27, (user + i)->login);
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

bool userLogin() {
    system("cls");
    int i = 0, j = 0, counter = 0;
    bool isLoginRight = false, isPasswordRight = false;
    char *login = NULL, password[30], ch;
    do {
        login = bufferedInput(29, "������� �����: ");
        for (i = 0; i < usersLinesCounter; i++)
            if (!strcmp(login, (user + i)->login)) {
                isLoginRight = true;
                break;
            }
        if (!isLoginRight) {
            printf("[������!]������ ������������ �� ����������!\n\n");
            system("pause");
            free(login);
            return false;
        }
    } while (!isLoginRight);
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
        if (!strcmp(password, (user + i)->password))
            isPasswordRight = true;
        else {
            printf("\n[������!]�������� ������!");
            Sleep(1000);
            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
        }
    } while (!isPasswordRight);
    if (!(user + i)->isAdmin) {
        printf("\n\n�� ������� ��������������!");
        Sleep(1000);
        printf("%c[2K\r����� ����������, %s!\n\n", 27, (user + i)->login);
        free(login);
        system("pause");
        return true;
    }
    else {
        printf("\n[������!]�����������: ������� ����� ��������������!\n\n");
        system("pause");
        free(login);
        return false;
    }
}

void firstStartAdminReg() {
    FILE *file = NULL;
    char *login = NULL, *password = NULL;
    USER newUser;
    system("cls");
    printf("--------------------------------------------------------------------------------------------------------------------------------\n"
           "            �� ����� � ��������� � ������ ���. ��� ���������� ������ ��������� ����� ���������������� ��������������!           \n"
           "--------------------------------------------------------------------------------------------------------------------------------\n");
    printf("����������� ��������������.\n\n");
    login = bufferedInput(29, "������� �����: ");
    strcpy(newUser.login,login);
    password = maskedPasswordInput(29, "������� ������: ");
    strcpy(newUser.password, password);
    newUser.isAdmin = 1;
    if ((file = fopen("db.dat", "ab+"))) {
        fwrite(&newUser, sizeof(USER), 1, file);
        fclose(file);
        crypterTool(ENCRYPT);
        printf("\n����� ������������� ������� ���������������!\n\n");
        system("pause");
    }
    else {
        printf("\n[������!]�����������: �� ������� ������� ���� ��� ���������� ������ ��������������!\n");
        exit(0);
    }
    system("cls");
}

void usersInit() {
    FILE* file = NULL;
    long fsize = 0;
    if (checkFile("db.dat")) {               //���� ���� ����������
        if ((file = fopen("db.dat", "rb"))){                //���� ���� ������� ������� ��� ������


            fseek(file, 0, SEEK_END);               //������� ���-�� ���� � �����
            fsize = ftell(file);
            usersLinesCounter = fsize/sizeof(USER);
            rewind(file);


            if (usersLinesCounter != 0) {               //���� ���� ������ ���� ������
                crypterTool(DECRYPT);               //������������ ����
                user = (USER *)malloc(usersLinesCounter * (sizeof(USER)));
                for (int i = 0; i < usersLinesCounter; i++)
                    fread((user + i), sizeof(USER), 1, file);
                fclose(file);
                crypterTool(ENCRYPT); //����������� ����
            } else {
                //���� ��� �� ����� ������
                firstStartAdminReg();
                usersInit();
            }
        } else {
            //���� ���� �� ������� �������
            printf("[������!]������������� �������������: �� ������� ������� ���� � ��������/��������!\n");
            system("pause");
            exit(0);
        }
    } else if (createFile("db.dat")) {
        //���� ���� �� ���������� - �������
        firstStartAdminReg();
        usersInit();
    } else {
        //���� ���� �� ���������� � ��� �� ������� �������
        printf("[������!]������������� �������������: �� ������� ������� ���� � ��������/��������!\n");
        system("pause");
        exit(0);
    }
}

void userAdd() {
    bool isLoginExist = false, isShowed = false;
    int choice = 1, ch = (int)NULL;
    char *login = NULL, *password = NULL;
    const char *line[] = { "��", "���", NULL }, pointer = '>';
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
        if (isLoginExist) {
            printf("[������!]����� ������� ��� ����������!");
            Sleep(1000);
            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
        }
        else strcpy((user + usersLinesCounter)->login, login);
    } while (isLoginExist);
    free(login);
    password = bufferedInput(29, "������� ������: ");
    strcpy((user + usersLinesCounter)->password, password);
    free(password);
    indicateCursor(false);
    while (true) {
        if (ch == KEY_LEFT || ch == KEY_RIGHT || ch == KEY_RETURN || !isShowed) {
            isShowed = true;
            if (ch == KEY_RETURN) {
                printf("%c[2K\r", 27);
                printf("�������������? ");
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
            printf("�������������? ");
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
        //���� ���� ����������
        crypterTool(DECRYPT);//������������
        if ((file = fopen("db.dat", "ab+"))) {
            //���� ���� ������� �������
            fwrite((user + usersLinesCounter), sizeof(USER), 1, file);
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
    displayAllUsers();
    printf("�������� ��������.\n");
    do {
        login = bufferedInput(29, "������� ����� ��������, ������� �� ������ �������: ");
        for (i = 0; i < usersLinesCounter; i++) {
            if (!strcmp((user + i)->login, login)) {
                isLoginExist = true;
                break;
            }
        }
        if (!isLoginExist) {
            printf("[������!]������ �������� �� ����������!");
            Sleep(1000);
            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
        }
    } while (!isLoginExist);
    free(login);
    if(adminCounter == 1 && (user + i)->isAdmin) {
        system("cls");
        displayAllUsers();
        printf("\n[������!]������ ������� ���������� ��������������!\n\n");
    }
    else {
        if (checkFile("db.dat")) {             //���� ���� ����������
            crypterTool(DECRYPT);               //������������
            if ((file = fopen("db.dat", "wb"))) {               //���� ���� ������� �����������
                for (int j = i; j < usersLinesCounter; j++)
                    *(user + j) = *(user + (j + 1));
                user = (USER *) realloc(user, sizeof(USER) * usersLinesCounter);
                usersLinesCounter--;
                for (int j = 0; j < usersLinesCounter; j++)
                    fwrite((user + j), sizeof(USER), 1, file);
                fclose(file);
                system("cls");
                displayAllUsers();
                printf("������� ������� �����!\n\n");
            } else
                printf("[������!]�������� �������������: ������ �������� ����� � ��������/��������! ���� �������!\n\n");               //���� ���� �� ������� �����������
            crypterTool(ENCRYPT);               //�����������
        } else
            printf("[������!]�������� �������������: ������ �������� ����� � ��������/��������!\n\n");             //���� ���� �� ����������
    }
    system("pause");
}

void userEdit() {
    char *login = NULL, *newLogin = NULL, *newPassword = NULL;
    int i = 0, adminCounter = 0;
    bool isLoginExist = false, isNewLoginExist = false, editFlag = false;
    FILE* file = NULL;
    displayAllUsers();
    do {
        login = bufferedInput(29, "������� ����� ��������, ������� �� ������ ���������������: ");
        for (i = 0; i < usersLinesCounter; i++) {
            if (!strcmp((user + i)->login, login)) {
                isLoginExist = true;
                break;
            }
            else isLoginExist = false;
        }
        if (!isLoginExist) {
            printf("[������!]������ �������� �� ����������!");
            Sleep(1000);
            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
        }
    } while (!isLoginExist);
    free(login);
    while (!editFlag) {
        for(int j = 0; j < usersLinesCounter; j++) {
            if ((user + j)->isAdmin)
                adminCounter++;
        }
        switch (userEditMenu(i)) {
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
                    if (isNewLoginExist) {
                        printf("[������!]����� ����� ��� ����������!\n");
                        Sleep(1000);
                        printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
                    }
                } while (isNewLoginExist);
                strcpy((user + i)->login, newLogin);
                displayEditableUser(i);
                printf("����� ������� �������!\n\n");
                free(newLogin);
                system("pause");
                break;
            }
            case 2: {
                printf("��������� ������.\n");
                newPassword = bufferedInput(29, "������� ����� ������: ");
                strcpy((user + i)->password, newPassword);
                displayEditableUser(i);
                printf("������ ������� �������!\n\n");
                free(newPassword);
                system("pause");
                break;
            }
            case 3: {
                if(adminCounter == 1 && (user + i)->isAdmin)
                    printf("[������!]������ �������� ����� ���������� ��������������!\n\n");
                else {
                    if ((user + i)->isAdmin) {
                        (user + i)->isAdmin = false;
                        displayEditableUser(i);
                        printf("����� �������������� ������� ��������.\n\n");
                    } else {
                        (user + i)->isAdmin = true;
                        displayEditableUser(i);
                        printf("����� �������������� ������� ��������.\n\n");
                    }
                }
                system("pause");
                break;
            }
            case 4: editFlag = true; break;
            default: break;
        }
        if (editFlag) break;
    }
    if (checkFile("db.dat")) {
        //���� ���� ����������
        crypterTool(DECRYPT);//������������
        if ((file = fopen("db.dat", "wb"))) {
            //���� ���� ������� �����������
            for (i = 0; i < usersLinesCounter; i++)
                fwrite((user + i), sizeof(USER), 1, file);
            fclose(file);
        }
        else printf("[������!]�������������� �������������: �� ������� ������� ���� � ��������/��������! ���� �������!\n\n");//���� ���� �� ������� �����������
        crypterTool(ENCRYPT);//�����������
    }
    else printf("[������!]�������������� �������������: �� ������� ������� ���� � ��������/��������!\n\n");//���� ���� �� ����������
}

void displayEditableUser(int i) {
    char yes[] = "��", no[] = "���";
    system("cls");
    printf("-----------------------------------------------------------------------------------\n");
    printf("|�����:                       |������:                      |����� ��������������:|\n");
    printf("-----------------------------------------------------------------------------------\n");
    printf("|%-29s|%-29s|%-21s|\n", (user + i)->login, (user + i)->password, (user + i)->isAdmin == 1 ? yes : no);
    printf("-----------------------------------------------------------------------------------\n\n");
}

void displayAllUsers() {
    char yes[] = "��", no[] = "���";
    printf("-----------------------------------------------------------------------------------------\n");
    printf("|�    |�����:                       |������:                      |����� ��������������:|\n");
    printf("-----------------------------------------------------------------------------------------\n");
    for (int i = 0; i < usersLinesCounter; i++)
        printf("|%-5i|%-29s|%-29s|%-21s|\n", i + 1, (user + i)->login, (user + i)->password, (user + i)->isAdmin == 1 ? yes : no);
    printf("-----------------------------------------------------------------------------------------\n\n");
}

void userReg(){
    bool isLoginExist = false;
    char *login = NULL, *password = NULL;
    FILE* file = NULL;
    user = (USER*)realloc(user, (usersLinesCounter + 1) * sizeof(USER));
    printf("����������� ������������:\n");
    do {
        login = bufferedInput(29, "������� �����: ");
        for (int i = 0; i < usersLinesCounter; i++) {
            if (strcmp((user + i)->login, login) == 0) {
                isLoginExist = true;
                break;
            }
            else isLoginExist = false;
        }
        if (isLoginExist) {
            printf("[������!]����� ������� ��� ����������!");
            Sleep(1000);
            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
        }
        else strcpy((user + usersLinesCounter)->login, login);
    } while (isLoginExist);
    free(login);
    password = maskedPasswordInput(29, "������� ������: ");
    strcpy((user + usersLinesCounter)->password, password);
    free(password);
    (user + usersLinesCounter)->isAdmin = 0;
    if (checkFile("db.dat")) {
        //���� ���� ����������
        crypterTool(DECRYPT);//������������
        if ((file = fopen("db.dat", "ab+"))) {
            //���� ���� ������� �������
            fwrite((user + usersLinesCounter), sizeof(USER), 1, file);
            fclose(file);
            printf("\n�� ������� ������������������!\n\n");
            _flushall();
            usersLinesCounter++;
        }
        else printf("[������!]���������� �������������: ������ �������� ����� � ��������/��������! ������������ �� ��������!\n\n"); //���� ���� �� ������� �������
        crypterTool(ENCRYPT);//�����������
    }
    else printf("[������!]���������� �������������: ���� �� ����������!\n\n"); //���� ���� �� ����������
    system("pause");
}


//�� ��� ������� � �����������
void membersOpenAdmin() {
    int choice = 1, ch = (int)NULL;
    bool isShowed = false;
    const char *line[] = { "��", "���", NULL }, pointer = '>';
    if (!checkFile("info.dat")) {
        printf("[������!]�������� ����������: ���� ��� �� ������!\n");
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
                printf("������� ����? ");
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
                printf("�������� ����������: ���� ������� ������!\n");
                membersInit();
                system("pause");
            }
            else printf("[������!]�������� ����������: �� ������� ������� ����!\n");
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
        printf("[������!]�������� ����������: ���� ��� �� ������!\n\n");
}

void membersInit() {
    FILE *file = NULL;
    long fsize;
    if (info)
        printf("[������!]�������� ����������: ���� ��� ������!\n\n");
    else {
        if ((file = fopen("info.dat", "rb+"))) {
            fseek(file, 0, SEEK_END);     //���-�� ����
            fsize = ftell(file);          //� �����
            infoLinesCounter = fsize / sizeof(INFORMATION);
            rewind(file);


            if (infoLinesCounter != 0) {
                info = (INFORMATION *)malloc(infoLinesCounter * sizeof(INFORMATION));
                for (int i = 0; i < infoLinesCounter; i++)
                    fread((info + i), sizeof(INFORMATION), 1, file);
            }
            fclose(file);
            printf("�������� ����������: ���� ������� ������!\n\n");
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
        printf("[������!]���������� ����������: ���� �� ������!\n\n");
    else if (!(file = fopen("info.dat", "ab+")))
        printf("[������!]���������� ����������: �� ������� ������� ���� ��� ����������!\n");
    else {
        info = (INFORMATION *)realloc(info, (infoLinesCounter + 1) * sizeof(INFORMATION));
        printf("���������� ���������.\n");
        do {
            do {
                (info + infoLinesCounter)->number = checkToEnterOnlyInt(3, "������� ����� ���������: ");
                if ((info + infoLinesCounter)->number < 1) {
                    printf("[������!]������� ����� ������ 0!");
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
                printf("[������!]�������� � ����� ������� ��� ����������!");
                Sleep(1000);
                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
            }
        } while (isMemberExist);
        firstname = stringInputCheck(49, "������� ��� ���������: ");
        strcpy((info + infoLinesCounter)->fullname.firstname, firstname);
        free(firstname);
        surname = stringInputCheck(49, "������� ������� ���������: ");
        strcpy((info + infoLinesCounter)->fullname.surname, surname);
        free(surname);
        lastname = stringInputCheck(49, "������� �������� ���������: ");
        strcpy((info + infoLinesCounter)->fullname.lastname, lastname);
        free(lastname);
        country = stringInputCheck(29, "������� ������ ���������: ");
        strcpy((info + infoLinesCounter)->country, country);
        free(country);
        do {
            (info + infoLinesCounter)->dateOfBirth.day = checkToEnterOnlyInt(2, "������� ���� �������� ���������: ");
            if ((info + infoLinesCounter)->dateOfBirth.day < 1 || (info + infoLinesCounter)->dateOfBirth.day > 31) {
                printf("[������!]������� ����� �� 1 �� 31!");
                Sleep(1000);
                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
            }
        } while ((info + infoLinesCounter)->dateOfBirth.day < 1 || (info + infoLinesCounter)->dateOfBirth.day > 31);
        do {
            (info + infoLinesCounter)->dateOfBirth.month = checkToEnterOnlyInt(2, "������� ����� �������� ���������(������): ");
            if ((info + infoLinesCounter)->dateOfBirth.month < 1 || (info + infoLinesCounter)->dateOfBirth.month > 12) {
                printf("[������!]������� ����� �� 1 �� 12!");
                Sleep(1000);
                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
            }
        } while ((info + infoLinesCounter)->dateOfBirth.month < 1 || (info + infoLinesCounter)->dateOfBirth.month > 12);
        do {
            (info + infoLinesCounter)->dateOfBirth.year = checkToEnterOnlyInt(4, "������� ��� �������� ���������: ");
            if ((info + infoLinesCounter)->dateOfBirth.year < 1900 || (info + infoLinesCounter)->dateOfBirth.year > 2019) {
                printf("[������!]������� ����� �� 1900 �� 2019!");
                Sleep(1000);
                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
            }
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
            if ((info + infoLinesCounter)->points < 0 || (info + infoLinesCounter)->points > 9999) {
                printf("[������!]������� ����� �� 0 �� 9999!");
                Sleep(1000);
                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
            }
        } while ((info + infoLinesCounter)->points < 0 || (info + infoLinesCounter)->points > 9999);
        do {
            (info + infoLinesCounter)->timeOfLap.minutes = checkToEnterOnlyInt(2, "������� ������ ����� ���������: ");
            if ((info + infoLinesCounter)->timeOfLap.minutes < 0 || (info + infoLinesCounter)->timeOfLap.minutes > 59) {
                printf("[������!]������� ����� �� 0 �� 59!");
                Sleep(1000);
                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
            }
        } while ((info + infoLinesCounter)->timeOfLap.minutes < 0 || (info + infoLinesCounter)->timeOfLap.minutes > 59);
        do {
            (info + infoLinesCounter)->timeOfLap.seconds = checkToEnterOnlyInt(2, "������� ������� ����� ���������: ");
            if ((info + infoLinesCounter)->timeOfLap.seconds < 0 || (info + infoLinesCounter)->timeOfLap.seconds > 59) {
                printf("[������!]������� ����� �� 0 �� 59!");
                Sleep(1000);
                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
            }
        } while ((info + infoLinesCounter)->timeOfLap.seconds < 0 || (info + infoLinesCounter)->timeOfLap.seconds > 59);
        fwrite((info + infoLinesCounter), sizeof(INFORMATION), 1, file);
        _flushall();
        fclose(file);
        infoLinesCounter++;
        printf("�������� ������� ��������!\n\n");
    }
}

void memberDelete() {
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
        displayAllMembers();
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
            if (!isNumberExist) {
                printf("[������!]��������� � ����� ������� �� ����������!");
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
                printf("�������� ������� �����!\n\n");
            }
            else printf("[������!]�������� ����������: �� ������� ������������ ����! ���� �������!\n\n");
        }
        else printf("[������!]�������� ����������: �� ������� ����� ����!\n\n");
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
        printf("[������!]�������������� ����������: ���� �� ������!\n\n");
        system("pause");
    }
    else if (infoLinesCounter == 0) {
        printf("[������!]�������������� ����������: ���� ����!\n\n");
        system("pause");
    }
    else {
        displayAllMembers();
        do {
            number = checkToEnterOnlyInt(3, "������� ����� ���������, �������� ����� ���������������: ");
            for (i = 0; i < infoLinesCounter; i++) {
                if ((info + i)->number == number) {
                    isMemberExist = true;
                    break;
                }
                else isMemberExist = false;
            }
            if (!isMemberExist) {
                printf("[������!]��������� � ����� ������� �� ����������!");
                Sleep(1000);
                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
            }
        } while (!isMemberExist);
        while (!infoEditFlag) {
            switch (memberEditMenu(i)) {
                case 1: {
                    printf("�������� ������ ���������.\n");
                    do {
                        do {
                            newNumber = checkToEnterOnlyInt(3, "������� ����� ����� ���������: ");
                            if (newNumber < 1) {
                                printf("[������!]������� ����� ������ 0!");
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
                            printf("[������!]�������� � ����� ������� ��� ����������!");
                            Sleep(1000);
                            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
                        }
                    } while (isNumberExist);
                    (info + i)->number = newNumber;
                    displayEditableMember(i);
                    printf("����� ��������� ������� �������!\n\n");
                    system("pause");
                    break;
                }
                case 2: {
                    printf("��������� ����� ���������.\n");
                    firstname = stringInputCheck(49, "������� ����� ��� ���������: ");
                    strcpy((info + i)->fullname.firstname, firstname);
                    free(firstname);
                    displayEditableMember(i);
                    printf("��� ��������� ������� ��������!\n\n");
                    system("pause");
                    break;
                }
                case 3: {
                    printf("��������� ������� ���������.\n");
                    surname = stringInputCheck(49, "������� ����� ������� ���������: ");
                    strcpy((info + i)->fullname.surname, surname);
                    free(surname);
                    displayEditableMember(i);
                    printf("������� ��������� ������� ��������!\n\n");
                    system("pause");
                    break;
                }
                case 4: {
                    printf("��������� �������� ���������.\n");
                    lastname = stringInputCheck(49, "������� ����� �������� ���������: ");
                    strcpy((info + i)->fullname.lastname, lastname);
                    free(lastname);
                    displayEditableMember(i);
                    printf("�������� ��������� ������� ��������!\n\n");
                    system("pause");
                    break;
                }
                case 5: {
                    printf("��������� ������ ���������.\n");
                    country = stringInputCheck(29, "������� ����� ������ ���������: ");
                    strcpy((info + i)->country, country);
                    free(country);
                    displayEditableMember(i);
                    printf("������ ��������� ������� ��������.\n\n");
                    system("pause");
                    break;
                }
                case 6: {
                    printf("��������� ��� �������� ���������.\n");
                    do {
                        newBirthDay = checkToEnterOnlyInt(2, "������� ����� ���� �������� ���������: ");
                        if (newBirthDay < 1 || newBirthDay > 31) {
                            printf("[������!]������� ����� �� 1 �� 31!");
                            Sleep(1000);
                            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
                        }
                    } while (newBirthDay < 1 || newBirthDay > 31);
                    (info + i)->dateOfBirth.day = newBirthDay;
                    displayEditableMember(i);
                    printf("���� �������� ��������� ������� �������!\n\n");
                    system("pause");
                    break;
                }
                case 7: {
                    printf("��������� ������ �������� ���������.\n");
                    do {
                        newBirthMonth = checkToEnterOnlyInt(2, "������� ����� ����� �������� ���������(������): ");
                        if (newBirthMonth < 1 || newBirthMonth > 12) {
                            printf("[������!]������� ����� �� 1 �� 12!");
                            Sleep(1000);
                            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
                        }
                    } while (newBirthMonth < 1 || newBirthMonth > 12);
                    (info + i)->dateOfBirth.month = newBirthMonth;
                    displayEditableMember(i);
                    printf("����� �������� ��������� ������� �������!\n\n");
                    system("pause");
                    break;
                }
                case 8: {
                    printf("��������� ���� �������� ���������.\n");
                    do {
                        newBirthYear = checkToEnterOnlyInt(4, "������� ����� ��� �������� ���������: ");
                        if (newBirthYear < 1900 || newBirthYear > 2019) {
                            printf("[������!]������� ����� �� 1900 �� 2019!");
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
                    printf("��� �������� ��������� ������� �������!\n\n");
                    system("pause");
                    break;
                }
                case 9: {
                    printf("��������� ������� ���������.\n");
                    category = stringInputCheck(29, "������� ����� ������ ���������: ");
                    strcpy((info + i)->category, category);
                    free(category);
                    displayEditableMember(i);
                    printf("������ ��������� ������� �������!\n\n");
                    system("pause");
                    break;
                }
                case 10: {
                    printf("��������� ������ ������� ���������.\n");
                    model = stringInputCheck(29, "������� ����� ������ ������� ���������: ");
                    strcpy((info + i)->model, model);
                    free(model);
                    displayEditableMember(i);
                    printf("������ ������� ��������� ������� ��������!\n\n");
                    system("pause");
                    break;
                }
                case 11: {
                    printf("��������� ���������� ����� ���������.\n");
                    do {
                        (info + i)->points = checkToEnterOnlyInt(4, "������� ����� ���������� ����� ���������: ");
                        if ((info + i)->points < 0 || (info + i)->points > 9999) {
                            printf("[������!]������� ����� �� 0 �� 9999!");
                            Sleep(1000);
                            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
                        }
                    } while ((info + i)->points < 0 || (info + i)->points > 9999);
                    displayEditableMember(i);
                    printf("���������� ����� ��������� ������� ��������!\n\n");
                    system("pause");
                    break;
                }
                case 12: {
                    printf("��������� ����� ����� ���������.\n");
                    do {
                        (info + i)->timeOfLap.minutes = checkToEnterOnlyInt(2, "������� ����� ������ ����� ���������: ");
                        if ((info + i)->timeOfLap.minutes < 0 || (info + i)->timeOfLap.minutes > 59) {
                            printf("[������!]������� ����� �� 0 �� 59!");
                            Sleep(1000);
                            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
                        }
                    } while ((info + i)->timeOfLap.minutes < 0 || (info + i)->timeOfLap.minutes > 59);
                    displayEditableMember(i);
                    printf("������ ����� ��������� ������� ��������!\n\n");
                    system("pause");
                    break;
                }
                case 13: {
                    printf("��������� ������ ����� ���������.\n");
                    do {
                        (info + i)->timeOfLap.seconds = checkToEnterOnlyInt(2, "������� ����� ������� ����� ���������: ");
                        if ((info + i)->timeOfLap.seconds < 0 || (info + i)->timeOfLap.seconds > 59) {
                            printf("[������!]������� ����� �� 0 �� 59!");
                            Sleep(1000);
                            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
                        }
                    } while ((info + i)->timeOfLap.seconds < 0 || (info + i)->timeOfLap.seconds > 59);
                    displayEditableMember(i);
                    printf("������� ����� ��������� ������� ��������!\n\n");
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
            else printf("[������!]�������������� ����������: �� ������� ������������ ����! ���� �������!\n");
        }
        else printf("[������!]�������������� ����������: �� ������� ����� ����!\n");
    }
}

void displayEditableMember(int i) {
    system("cls");
    printf("--------------------------------------------------------------------------------------------------------------------------------\n"
           "|�����|���             �������         ��������       |  ������  |����  ��������|�������|  ������  |  ������  |����|����� �����|\n"
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
void pointsFilter() {
    int points = 0;
    bool isAtLeastOneMember = false;
    if (!info)
        printf("[������!]����� � ����������: ���� �� ������!\n\n");
    else if (infoLinesCounter == 0)
        printf("[������!]����� � ����������: ���� ����!\n\n");
    else {
        do {
            points = checkToEnterOnlyInt(4, "������� ���������� �����: ");
            if (points < 0 || points > 9999) {
                printf("[������!]������� ����� ������ 0 � ������ 9999!");
                Sleep(1000);
                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
            }
        } while (points < 0 || points > 9999);
        system("cls");
        printf("���������, � ������� ����� ������ %i: ", points);
        for (int i = 0; i < infoLinesCounter; i++) {
            if ((info + i)->points > points) {
                if (!isAtLeastOneMember) {
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
            if (isAtLeastOneMember && i == infoLinesCounter - 1)
                printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
        }
        if (!isAtLeastOneMember)
            printf("[������!]��� �� ������ ��������� � ������ ������ %i.\n\n", points);
    }
}

void timeOfLapFilter() {
    int minutesOfLap = 0, secondsOfLap = 0;
    bool isAtLeastOneMember = false;
    if (!info) {
        printf("[������!]����� � ����������: ���� �� ������!\n\n");
    }
    else if (infoLinesCounter == 0) {
        printf("[������!]����� � ����������: ���� ����!\n\n");
    }
    else {
        do {
            minutesOfLap = checkToEnterOnlyInt(2, "������� ���������� ����� �����: ");
            if (minutesOfLap < 0 || minutesOfLap > 59) {
                printf("[������!]������� ����� ������ 0 � ������ 59!\n");
                Sleep(1000);
                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
            }
        } while (minutesOfLap < 0 || minutesOfLap > 59);
        do {
            secondsOfLap = checkToEnterOnlyInt(2, "������� ���������� ������ �����: ");
            if (secondsOfLap < 0 || secondsOfLap > 59) {
                printf("[������!]������� ����� ������ 0 � ������ 59!\n");
                Sleep(1000);
                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
            }
        } while (secondsOfLap < 0 || secondsOfLap > 59);
        system("cls");
        printf("���������, � ������� ����� ����� ������ %02i:%02i : ", minutesOfLap, secondsOfLap);
        for (int i = 0; i < infoLinesCounter; i++) {
            if ((info + i)->timeOfLap.minutes < minutesOfLap)
                if ((info + i)->timeOfLap.seconds <
                    ((info + i)->timeOfLap.minutes == minutesOfLap ? secondsOfLap : 60)) {
                    if (!isAtLeastOneMember) {
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
            if (isAtLeastOneMember && i == infoLinesCounter - 1)
                printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
        }
        if (!isAtLeastOneMember)
            printf("[������!]��� �� ������ ��������� � �������� ����� ������ %02i:%02i.\n\n", minutesOfLap,
                   secondsOfLap);
    }
}

void ageFilter() {
    int age = 0;
    bool isAtLeastOneMember = false;
    if (!info)
        printf("[������!]����� � ����������: ���� �� ������!\n\n");
    else if (infoLinesCounter == 0)
        printf("[������!]����� � ����������: ���� ����!\n\n");
    else {
        do {
            age = checkToEnterOnlyInt(3, "������� �������: ");
            if (age < 0 || age > 119) {
                printf("[������!]������� ����� ������ 0 � ������ 119!\n");
                Sleep(1000);
                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
            }
        } while (age < 0 || age > 119);
        system("cls");
        printf("���������, ������� ������� ������ %i: ", age);
        for (int i = 0; i < infoLinesCounter; i++) {
            if ((info + i)->dateOfBirth.age > age) {
                if (!isAtLeastOneMember) {
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
            if (isAtLeastOneMember && i == infoLinesCounter - 1)
                printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
        }
        if (!isAtLeastOneMember)
            printf("[������!]��� �� ������ ��������� � ������ ������ %i.\n\n", age);
    }
}

void yearOfBirthFilter() {
    int yearOfBirth = 0;
    bool isAtLeastOneMember = false;
    if (!info)
        printf("[������!]����� � ����������: ���� �� ������!\n\n");
    else if (infoLinesCounter == 0)
        printf("[������!]����� � ����������: ���� ����!\n\n");
    else {
        do {
            yearOfBirth = checkToEnterOnlyInt(4, "������� ��� ��������: ");
            if (yearOfBirth < 1900 || yearOfBirth > 2019) {
                printf("[������!]������� ����� ������ 1900 � ������ 2019!\n");
                Sleep(1000);
                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
            }
        } while (yearOfBirth < 1900 || yearOfBirth > 2019);
        system("cls");
        printf("���������, ��� �������� � ������� ������ %i: ", yearOfBirth);
        for (int i = 0; i < infoLinesCounter; i++) {
            if ((info + i)->dateOfBirth.year > yearOfBirth) {
                if (!isAtLeastOneMember) {
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
            if (isAtLeastOneMember && i == infoLinesCounter - 1) {
                printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
            }
        }
        if (!isAtLeastOneMember)
            printf("[������!]��� �� ������ ��������� � ����� �������� ������ %i.\n\n", yearOfBirth);
    }
}

void timeOfLapSorting() {
    FILE* file = NULL;
    INFORMATION tmp;
    if (!info)
        printf("[������!]����������: ���� �� ������!\n\n");
    else if (infoLinesCounter == 0)
        printf("[������!]����������: ���� ����!\n\n");
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
            printf("����������: ��������� ������� �������������!\n\n");
        }
        else printf("[������!]����������: �� ������� ������� ����! ���� �������!\n\n");
    }
}

void numberSearch() {
    int number = 0;
    bool isFounded = false;
    if (!info)
        printf("[������!]����� � ����������: ���� �� ������!\n\n");
    else if (infoLinesCounter == 0)
        printf("[������!]����� � ����������: ���� ����!\n\n");
    else {
        do {
            number = checkToEnterOnlyInt(3, "������� �����: ");
            if (number < 0) {
                printf("[������!]������� ����� ������ 0!\n");
                Sleep(1000);
                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
            }
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
        if (!isFounded)
            printf("�������� � ������� %i �� ������.\n\n", number);
    }
}

void surnameSearch() {
    bool isAtLeastOneMember = false;
    char *surname = NULL;
    if (!info)
        printf("[������!]����� � ����������: ���� �� ������!\n\n");
    else if (infoLinesCounter == 0)
        printf("[������!]����� � ����������: ���� ����!\n\n");
    else {
        surname = stringInputCheck(49, "������� �������: ");
        system("cls");
        printf("���������, � �������� %s: ", surname);
        for (int i = 0; i < infoLinesCounter; i++) {
            if (strcmp((info + i)->fullname.surname, surname) == 0) {
                if (!isAtLeastOneMember) {
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
            if (isAtLeastOneMember && i == infoLinesCounter - 1)
                printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
        }
        if (!isAtLeastOneMember)
            printf("[������!]��� �� ������ ��������� � �������� %s.\n\n", surname);
    }
}

void countrySearch() {
    bool isAtLeastOneMember = false;
    char *country = NULL;
    if (!info)
        printf("[������!]����� � ����������: ���� �� ������!\n\n");
    else if (infoLinesCounter == 0)
        printf("[������!]����� � ����������: ���� ����!\n\n");
    else {
        country = stringInputCheck(49, "������� ������: ");
        system("cls");
        printf("���������, �� ������ %s: ", country);
        for (int i = 0; i < infoLinesCounter; i++) {
            if (strcmp((info + i)->country, country) == 0) {
                if (!isAtLeastOneMember) {
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
            if (isAtLeastOneMember && i == infoLinesCounter - 1)
                printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
        }
        if (!isAtLeastOneMember)
            printf("[������!]��� �� ������ ��������� �� ������ %s.\n\n", country);
    }
}

void categorySearch() {
    bool isAtLeastOneMember = false;
    char *category = NULL;
    if (!info)
        printf("[������!]����� � ����������: ���� �� ������!\n\n");
    else if (infoLinesCounter == 0)
        printf("[������!]����� � ����������: ���� ����!\n\n");
    else {
        category = stringInputCheck(49, "������� ������: ");
        system("cls");
        printf("���������, � �������� %s: ", category);
        for (int i = 0; i < infoLinesCounter; i++) {
            if (strcmp((info + i)->category, category) == 0) {
                if (!isAtLeastOneMember) {
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
            if (isAtLeastOneMember && i == infoLinesCounter - 1)
                printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
        }
        if (!isAtLeastOneMember)
            printf("[������!]��� �� ������ ��������� � �������� %s.\n\n", category);
    }
}

void displayTopMembers() {
    INFORMATION *infoCopy = NULL, tmp;
    system("cls");
    if (!info)
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