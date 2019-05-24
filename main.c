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
#define KEY_ESC 27
#define DECRYPT 1 //������������
#define ENCRYPT 0 //�����������
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


int usersLinesCounter = 0;              //������� ���������� �������������
int infoLinesCounter = 0;               //������� ���������� ����������
USER *user = NULL;              //������ �������� �������������
INFORMATION *info = NULL;               //������ �������� ����������


//����
char* stringInputCheck(int limit, const char* message);//������� ����� ������ ����
char* bufferedInput(int limit, const char* message);//������� ����� ������������� ���-�� ��������
int checkToEnterOnlyInt(int limit, const char *message);//������� ����� ������ ����� �����
char* maskedPasswordInput(int limit, const char* message);//������� ��� ����� ������
char* loginInput(int limit, const char* message);//������� ��� ����� ������
char* categoryInput(int limit, const char* message);//������� ��� ����� �������
void dateOfBirthInput(int *day, int *month, int *year, const char* message);
void timeOfLapInput(int *minutes, int *seconds, const char* message);

//����
void indicateCursor(bool status);//������� ������/������� ������� �����
int menu();//������� �������� ����
int adminSubmenu();//������� ������� ���������������
int userSubmenu();//������� ������� �������������
int userEditMenu(int i, bool showPass);//������� ���� �������������� �������������
int memberEditMenu(int i);//������� ���� �������������� ����������
void searchingAndFiltering();//������� ������ ������� ���� ������ � ����������
int searchAndFilteringMenu();//������� ���� ������ � ����������
void userManagement();//������� ������ ������� ���� ���������� ��������������
int userManagementMenu();//������� ���� ���������� ��������������
int userLoginOrRegMenu();//������� ������� ����� ��� �������������
int displayAllUsersMenu(bool showPass);//������� ������ ���� ������ ���� �������������

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
void displayEditableUser(int i, bool showPass);//������� ������ ���������� � ������������� ��������
void displayAllUsers(bool showPass);//������� ������ ���������� � ���� ���������
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
    setlocale(LC_ALL, "Rus");           //��������� ������ �������
    SetConsoleCP(1251);         //��������� ��������� �������
    SetConsoleOutputCP(1251);           //��������� ��������� ������ �������
    system("color 0B");             //��������� ����� ������ �������
    system("mode con cols=139 lines=32");               //��������� ������� ���� �������
    indicateCursor(false);          //������� ������� �����
    printf("-------------------------------------------------------------------------------------------------------------------------------------------\n"
           "                                  ��������� ����� ���������� �� ���������� ������������ �� ���� �� �������                                 \n"
           "-------------------------------------------------------------------------------------------------------------------------------------------\n"
           "                                                                                                                             � by Minilooth");
    Sleep(3500);            //��������� ��������� �� 3.5 ���
    indicateCursor(true);               //����� ������� �����
    usersInit();            //������������� �������������
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
                                break;
                            case 3:
                                memberEdit();
                                break;
                            case 4:
                                memberDelete();
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
        buffer = bufferedInput(limit, message);         //���� ������ � ����������
        if (buffer == NULL)
            return NULL;
        while (buffer[i] != '\0') {
            checkLetter = isdigit((unsigned char)buffer[i]);            //�������� ������� �� ����� �� 0 �� 9
            checkSymbol = isalnum((unsigned char)buffer[i]);            //�������� ������� �� ����� ��� �����
            if (checkLetter != 0 || !checkSymbol) {             //���� ������ �� ����� � �� �����
                isLetter = false;
                break;              //����� �� �����
            }
            else isLetter = true;
            i++;
        }
        if (isLetter) {             //���� ������ �������� ������ �����
            buffer[0] = (char)toupper((int)buffer[0]);              //��������� ������ ����� �� ��� �� ����� �������� ��������
            return buffer;              //������� �������� �������
        }
        else {          //���� ������ �������� �� ������ �����
            printf("[������!]��� ���� �� ����� ��������� ������ \"%c\"!", buffer[i]);
            Sleep(1000);
            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);               //�������� ���� ��������� ����� � ������
        }
    }
}

char* bufferedInput(int limit, const char* message) {
    char ch, *buffer = NULL;
    int i = 0;
    buffer = (char*)realloc(NULL, sizeof(char)*(limit + 1));            //��������� ������ ��� ������
    printf("%s", message);
    while (true) {
        ch = (char)_getch();                //���� ������� � ����������
        if (ch != '\0') {               //���� ������ - �� ����-������
            if (ch == KEY_RETURN || ch == KEY_TAB) {                //���� ��� ������ ����� ��� ���������
                if (i > 0) {            //���� ������� �������� ������ 0
                    buffer[i] = '\0';               //������ ����-������� � i-�� ������
                    putchar('\n');
                    break;              //����� �� �����
                }
                else {          //���� ������� ������� ����� 0
                    printf("\n[������!]������� ���� �� ���� ������!");
                    Sleep(1000);
                    printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);               //�������� ���� ��������� ����� � ������
                    printf("%s", message);
                }
            }
            else if (ch == KEY_BKSP && i > 0) {         //���� ������ backspace � ������� �������� ������ 0
                i--;
                printf("\b \b");                //������� ������ � �������
            }
            else if (ch == KEY_BKSP && !i)              //���� ������ backspace � ������� ����� 0
                continue;               //������� �� ��������� �������� �����
            else if (ch == KEY_ESC)
                return NULL;
            else {
                if (i < limit) {            //���� ������� ������ ������������
                    buffer[i++] = ch;           //������ ������� � ������
                    putchar(ch);                //����� ������� �� �����
                }
            }
        }
    }
    return buffer;              //������� �������� �������
}

int checkToEnterOnlyInt(int limit, const char *message) {
    char *buffer = NULL;
    int numberEntered = 0, i = 0, check = 0;
    bool isNumeral = false, flag = false;
    while (true) {
        i = 0;
        buffer = bufferedInput(limit, message);         //���� ������ � ����������
        if (buffer == NULL)
            return INT_MIN;
        while (buffer[i] != '\0') {             //���� i-�� ������ �� ����-������
            if (buffer[i] == '-' && !flag) {            //���� i-�� ������ ����� ������� "-" � ���� = true
                i++;
                flag = true;
            }
            check = isdigit((unsigned char)buffer[i]);              //��������� �������� �� i-�� ������ ������
            if (!check) {           //���� i-�� ������ �� �������� ������
                isNumeral = false;
                break;
            }
            else isNumeral = true;            //���� i-�� ������ �������� ������
            i++;
        }
        if (isNumeral) {                //���� ������ �������� ������ �����
            numberEntered = strtol(buffer, NULL, 10);               //�������������� ������ � ����� �����
            free(buffer);               //������������ ������ ����������
            return numberEntered;               //������� �������� �������
        }
        else {                  //���� ������ �������� �� �����
            printf("[������!]�� ���������� ����!");
            Sleep(1000);
            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);               //�������� ���� ��������� ����� � ������
        }
    }
}

char* maskedPasswordInput(int limit, const char* message) {
    char ch, *password = NULL;
    int i = 0;
    bool isSpaceEntered = false;
    password = (char*)realloc(NULL, sizeof(char)*(limit + 1));          //��������� ������ ��� ������
    while (true) {
        i = 0;
        printf("%s", message);
        while (true) {          //������������ ������ �������� � ������
            ch = (char)_getch();               //���� �������
            if (ch != '\0') {
                if (ch == KEY_RETURN || ch == KEY_TAB) {            //���� ������ - ������ ����� ��� ���������
                    password[i] = '\0';         //������ ����-������ � i-�� ������
                    putchar('\n');
                    break;              //����� �� �����
                }
                else if (ch == KEY_BKSP && i > 0) {               //���� ������ - backspace � ������� �������� > 0
                    i--;
                    printf("\b \b");               //������� ������ � ������
                }
                else if (ch == KEY_BKSP && i == 0) {              //���� ������ - backspace � ������� �������� = 0
                    continue;               //������� �� ��������� �������� �����
                }
                else if (ch == KEY_ESC)
                    return NULL;
                else if (i < limit) {                 //���� ������� �������� ������ ������������
                    password[i++] = ch;         //������ ������� � ������
                    putchar('*');               //����� �� ����� ������ "*"
                }
            }
        }
        if (i > 0) {                //���� ������� �������� ������ 0
            for (int j = 0; password[j]; j++) {             //����� ������� "������" � ������� �������
                if (password[j] == ' ') {               //���� j-�� ������ - ������
                    isSpaceEntered = true;
                    break;              //����� �� �����
                }
                else isSpaceEntered = false;
            }
            if (isSpaceEntered) {               //���� ��������� ������ "������"
                printf("[������!]������ �� ����� ��������� ������ \" \"!");
                Sleep(1000);
                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);               //�������� ���� ��������� ����� � ������
            }
            else return password;         //���� "������" �� ���������
        }
        else {            //���� ������� �������� ����� 0
            printf("[������!]������� ���� �� ���� ������!");
            Sleep(1000);
            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);               //�������� ���� ��������� �����
        }
    }
}

char* loginInput(int limit, const char* message) {
    char *buffer = NULL;
    int i = 0, checkSymbol = 0;
    bool isLetter = false;
    while (true) {
        i = 0;
        buffer = bufferedInput(limit, message);             //���� ������
        if (buffer == NULL) {
            printf("%c[2K\r", 27);
            return NULL;
        }
        while (buffer[i] != '\0') {             //���� i-�� ������ �� ����-������
            checkSymbol = isalnum((unsigned char)buffer[i]);            //�������� i-�� ������� �� ����� ��� �����
            if (!checkSymbol) {             //���� i-�� ������ - ����� ��� �����
                isLetter = false;
                break;              //����� �� �����
            }
            else isLetter = true;           //���� i-�� ������ - �� ����� ��� �� �����
            i++;
        }
        if (isLetter)               //���� ������ �������� ������ ����� ��� �����
            return buffer;              //������� �������� �������
        else {          //���� �� �������� �� ������ ����� ��� �����
            printf("[������!]����� �� ����� ��������� ������ \"%c\"!", buffer[i]);
            Sleep(1000);
            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);               //�������� ���� ��������� ����� � ������
        }
    }
}

char* categoryInput(int limit, const char* message) {
    char *buffer = NULL;
    int i = 0, checkSymbol = 0, checkLetter = 0;
    bool isLetter = false;
    while (true) {
        i = 0;
        buffer = bufferedInput(limit, message);         //���� ������
        if (buffer == NULL) {
            //printf("%c[2K\r", 27);
            return NULL;
        }
        while (buffer[i] != '\0') {             //���� i-�� ������ �� ����-������
            if (buffer[i] != ' ' && buffer[i] != '.') {          //���� i-�� ������ �� ������ � �� �����
                checkLetter = isdigit((unsigned char)buffer[i]);            //�������� ������� �� ����� �� 0 �� 9
                checkSymbol = isalnum((unsigned char)buffer[i]);           //�������� i-�� ������� �� �����
                if (!checkSymbol || checkLetter != 0) {             //���� i-�� ������ �� ����� � �� �����
                    isLetter = false;
                    break;              //����� �� �����
                }
                else isLetter = true;         //���� i-�� ������ ����� ��� �����
            }
            i++;
        }
        if (isLetter) {                 //���� ������ �������� ������ ����� ��� �����
            buffer[0] = (char)toupper((int)buffer[0]);              //������� ������� ������� � ������� �������
            return buffer;              //������� �������� �������
        }
        else {              //���� ������ �������� �� ������ ����� ��� �����
            printf("[������!]������ �� ����� ��������� ������ \"%c\"!", buffer[i]);
            Sleep(1000);
            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);               //�������� ���� ��������� ����� � ������
        }
    }
}

void dateOfBirthInput(int *day, int *month, int *year, const char* message) {
    char *buffer = NULL;
    bool isDateInputtedCorrectly = false, isDayInputtedCorrectly, isMonthInputtedCorrectly, isYearInputtedCorrectly, isDateConsistOfDigits;
    do {
        isDateConsistOfDigits = true;
        isDayInputtedCorrectly = false;
        isMonthInputtedCorrectly = false;
        isYearInputtedCorrectly = false;
        buffer = bufferedInput(10, message);
        if (buffer == NULL) {
            *day = INT_MIN;
            *month = INT_MIN;
            *year = INT_MIN;
            return;
        }
        for (int i = 0; i < 10; i++) {
            if (i != 2 && i != 5 && (isdigit((int)buffer[i])) == 0) {
                isDateConsistOfDigits = false;
                break;
            }
        }
        if (buffer[2] != '.' || buffer[5] != '.' || isDateConsistOfDigits == false) {
            printf("[������!]���� ������� �����������!");
            Sleep(1000);
            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
            continue;
        }
        *day = atoi(buffer);
        if (*day < 1 || *day > 31) {
            printf("[������!]���� ������ ���� ������ �� 1 �� 31!");
            Sleep(1000);
            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
        }
        else isDayInputtedCorrectly = true;
        *month = atoi(buffer + 3);
        if (*month < 1 || *month > 12) {
            printf("[������!]����� ������ ���� ������ �� 1 �� 12!");
            Sleep(1000);
            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
        }
        else isMonthInputtedCorrectly = true;
        *year = atoi(buffer + 6);
        if (*year < 1900 || *year > 2019) {
            printf("[������!]��� ������ ���� ������ �� 1900 �� 2019!");
            Sleep(1000);
            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
        }
        else isYearInputtedCorrectly = true;
        if (isDayInputtedCorrectly == true && isMonthInputtedCorrectly == true && isYearInputtedCorrectly == true)
            isDateInputtedCorrectly = true;
    } while (isDateInputtedCorrectly == false);
}

void timeOfLapInput(int *minutes, int *seconds, const char* message) {
    char *buffer = NULL;
    bool isTimeInputtedCorrectly = false, isMinutesInputtedCorrectly, isSecondsInputtedCorrectly, isTimeConsistsOfDigits;
    do {
        isMinutesInputtedCorrectly = false;
        isSecondsInputtedCorrectly = false;
        isTimeConsistsOfDigits = true;
        buffer = bufferedInput(5, message);
        if (buffer == NULL) {
            *minutes = INT_MIN;
            *seconds = INT_MIN;
            return;
        }
        for (int i = 0; i < 5; i++) {
            if (i != 2 && (isdigit((int)buffer[i])) == 0) {
                isTimeConsistsOfDigits = false;
                break;
            }
        }
        if (buffer[2] != ':' || isTimeConsistsOfDigits == false) {
            printf("[������!]����� ����� ������� �����������!");
            Sleep(1000);
            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
            continue;
        }
        *minutes = atoi(buffer);
        if (*minutes < 0 || *minutes > 59) {
            printf("[������!]������ ������ ���� ������� �� 0 �� 59!");
            Sleep(1000);
            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
        }
        else isMinutesInputtedCorrectly = true;
        *seconds = atoi(buffer + 3);
        if (*seconds < 0 || *seconds > 59) {
            printf("[������!]������� ������ ���� ������� �� 0 �� 59!");
            Sleep(1000);
            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
        }
        else isSecondsInputtedCorrectly = true;
        if (isMinutesInputtedCorrectly == true && isSecondsInputtedCorrectly == true)
            isTimeInputtedCorrectly = true;
    } while (isTimeInputtedCorrectly == false);
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
    indicateCursor(false);              //������� ������� �����
    while (true) {
        if (ch == KEY_RETURN || ch == KEY_UP || ch == KEY_DOWN || !isShowed) {              //���� ��������� ������ - ������ ����� ��� ������ ������� ����� ��� ���� ��� ���� �� ���� ��������
            isShowed = true;
            system("cls");              //������� ������
            if (ch == KEY_RETURN) {             //���� ��� ������ ������ �����
                indicateCursor(true);               //�������� ������� �����
                return choice;
            }
            if (ch == KEY_UP) choice--;                 //���� ��� ������ ������ ������� �����
            else if (ch == KEY_DOWN) choice++;              //���� ��� ������ ������ ������� ����
            if (choice > 3) choice = 1;                 //���� ��������� ������ ������ 3 ������� ��� � ��������� ���������
            else if (choice < 1) choice = 3;            //���� ��������� ������ ������ 1 ������� ��� � ��������� ���������
            printf("����:\n");
            for (int i = 0; line[i]; i++) {             //����� ����
                if (choice == i + 1) {                  //���� ��������� ����� (i + 1)-�� ������ ������� �����
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);               //�������� ���� ������
                    printf("%c", pointer);              //����� ��������� �� �����
                }
                printf(i + 1 == choice ? "%s\n" : " %s\n", line[i]);                //����� ������ �� �������
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);               //����� ����� �����
            }
        }
        ch = _getch();              //���� ������� � ����������
    }
}

int adminSubmenu() {
    int choice = 1, ch = (int)NULL;
    bool isShowed = false;
    const char pointer = '>', *line[] = { "��������/�������� �����.", "���������� ������.", "�������������� ������.",
                                          "�������� ������.", "�������� ���� ������ � ��������� �����.",
                                          "��������� ��������� ������ � ���������� ������.", "���������� ��������������.",
                                          "����� � ����.", NULL };
    indicateCursor(false);                  //������� ������� �����
    while (true) {
        if (ch == KEY_RETURN || ch == KEY_UP || ch == KEY_DOWN || !isShowed) {                  //���� ��������� ������ - ������ ����� ��� ������ ������� ����� ��� ���� ��� ���� �� ���� ��������
            isShowed = true;
            system("cls");              //������� ������
            if (ch == KEY_RETURN) {             //���� ��� ������ ������ �����
                indicateCursor(true);               //�������� ������� �����
                return choice;
            }
            if (ch == KEY_UP) choice--;                 //���� ��� ������ ������ ������� �����
            if (ch == KEY_DOWN) choice++;                 //���� ��� ������ ������ ������� ����
            if (choice > 8) choice = 1;                 //���� ��������� ������ ������ 8 ������� ��� � ��������� ���������
            if (choice < 1) choice = 8;                 //���� ��������� ������ ������ 1 ������� ��� � ��������� ���������
            printf("�������(��� ���������������):\n");
            for (int i = 0; line[i]; i++) {                 //����� ����
                if (choice == i + 1) {                  //���� ��������� ����� (i + 1)-�� ������ ������� �����
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);               //�������� ���� ������
                    printf("%c", pointer);                  //����� ��������� �� �����
                }
                printf(i + 1 == choice ? "%s\n" : " %s\n", line[i]);                 //����� ������ �� �������
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);                   //����� ����� �����
            }
        }
        ch = _getch();                  //���� ������� � ����������
    }
}

int userSubmenu() {
    int choice = 1, ch = (int)NULL;
    bool isShowed = false;
    const char pointer = '>', *line[] = { "�������� ����� � �������.", "�������� ���� ������ � ��������� �����.",
                                          "�������� ���-3 ����� ������� ����������.", "��������� ��������� ������ � ���������� ������.",
                                          "����� � ����.", NULL };
    indicateCursor(false);                  //������� ������� �����
    while (true) {
        if (ch == KEY_RETURN || ch == KEY_UP || ch == KEY_DOWN || !isShowed) {              //���� ��������� ������ - ������ ����� ��� ������ ������� ����� ��� ���� ��� ���� �� ���� ��������
            isShowed = true;
            system("cls");                  //������� ������
            if (ch == KEY_RETURN) {             //���� ��� ������ ������ �����
                indicateCursor(true);                   //�������� ������� �����
                return choice;
            }
            if (ch == KEY_UP) choice--;                 //���� ��� ������ ������ ������� �����
            if (ch == KEY_DOWN) choice++;                   //���� ��� ������ ������ ������� ����
            if (choice > 5) choice = 1;                 //���� ��������� ������ ������ 5 ������� ��� � ��������� ���������
            if (choice < 1) choice = 5;                 //���� ��������� ������ ������ 1 ������� ��� � ��������� ���������
            printf("�������(��� �������������):\n");
            for (int i = 0; line[i]; i++) {             //����� ����
                if (choice == i + 1) {                  //���� ��������� ����� (i + 1)-�� ������ ������� �����
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);               //�������� ���� ������
                    printf("%c", pointer);              //����� ��������� �� �����
                }
                printf(i + 1 == choice ? "%s\n" : " %s\n", line[i]);            //����� ������ �� �������
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);           //����� ����� �����
            }
        }
        ch = _getch();              //���� ������� � ����������
    }
}

int userEditMenu(int i, bool showPass) {
    int choice = 1, ch = (int)NULL;
    bool isShowed = false;
    const char pointer = '>', *line[] = { "�������� �����.", "�������� ������.", "�������� ����� ��������������.", "��������/������ ������.",
                                          "����� �� ���� �������������� ��������.", NULL };
    indicateCursor(false);              //������� ������� �����
    while (true) {
        if (ch == KEY_RETURN || ch == KEY_UP || ch == KEY_DOWN || !isShowed) {                  //���� ��������� ������ - ������ ����� ��� ������ ������� ����� ��� ���� ��� ���� �� ���� ��������
            isShowed = true;
            displayEditableUser(i, showPass);                   //������� ������ ������������ ������������
            if (ch == KEY_RETURN) {                 //���� ��� ������ ������ �����
                indicateCursor(true);                   //�������� ������� �����
                return choice;
            }
            if (ch == KEY_UP) choice--;                 //���� ��� ������ ������ ������� �����
            if (ch == KEY_DOWN) choice++;                   //���� ��� ������ ������ ������� ����
            if (choice > 5) choice = 1;                 //���� ��������� ������ ������ 5 ������� ��� � ��������� ���������
            if (choice < 1) choice = 5;                 //���� ��������� ������ ������ 1 ������� ��� � ��������� ���������
            printf("���� �������������� ���������:\n");
            for (int j = 0; line[j]; j++) {                 //����� ����
                if (choice == j + 1) {                  //���� ��������� ����� (j + 1)-�� ������ ������� �����
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);               //�������� ���� ������
                    printf("%c", pointer);                      //����� ��������� �� �����
                }
                printf(j + 1 == choice ? "%s\n" : " %s\n", line[j]);                //����� ������ �� �������
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);               //����� ����� �����
            }
        }
        ch = _getch();              //���� ������� � ����������
    }
}

int memberEditMenu(int i) {
    int choice = 1, ch = (int)NULL;
    bool isShowed = false;
    const char pointer = '>', *line[] = { "��������� ������ ���������.", "��������� ����� ���������.",
                                          "��������� ������� ���������.", "��������� �������� ���������.",
                                          "��������� ������ ���������.", "��������� ���� �������� ���������.",
                                          "��������� ������� ���������.", "��������� ������ ������� ���������.",
                                          "��������� ���������� ����� ���������.", "��������� ������� ����� ���������.",
                                          "����� �� ���� �������������� ���������.", NULL };
    indicateCursor(false);              //������� ������� �����
    displayEditableMember(i);               //����� �������������� ���������
    while (true) {
        if (ch == KEY_RETURN || ch == KEY_UP || ch == KEY_DOWN || !isShowed) {              //���� ��������� ������ - ������ ����� ��� ������ ������� ����� ��� ���� ��� ���� �� ���� ��������
            if (ch == KEY_RETURN) {               //���� ��� ������ ������ �����
                indicateCursor(true);               //���������� ������� �����
                displayEditableMember(i);               //����� �������������� ���������
                return choice;
            }
            if (ch == KEY_UP) choice--;                 //���� ��� ������ ������ ������� �����
            if (ch == KEY_DOWN) choice++;               //���� ��� ������ ������ ������� ����
            if (choice > 11) choice = 1;                //���� ��������� ������ ������ 14 ������� ��� � ��������� ���������
            if (choice < 1) choice = 11;                //���� ��������� ������ ������ 1 ������� ��� � ��������� ���������
            if (isShowed == true)                //���� ���� ���� ��������
                for (int j = 0; j < 12; j++)            //���������� �������� ���� � ������
                    printf("%c[2K\r%c[A", 27, 27);
            isShowed = true;
            printf("���� �������������� ���������:\n");
            for (int j = 0; line[j]; j++) {             //����� ����
                if (choice == j + 1) {              //���� ��������� ����� (j + 1)-�� ������ ������� �����
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);               //�������� ���� ������
                    printf("%c", pointer);              //����� ��������� �� �����
                }
                printf(j + 1 == choice ? "%s\n" : " %s\n", line[j]);                //����� ������
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);               //������� ����� �����
            }
        }
        ch = _getch();          //���� ������� � ����������
    }
}

void searchingAndFiltering() {
    while (true) {
        system("cls");              //������� ����
        switch (searchAndFilteringMenu()) {             //����� � ����� ������ ����
            case 1: pointsFilter(); break;
            case 2: timeOfLapFilter(); break;
            case 3: ageFilter(); break;
            case 4: yearOfBirthFilter(); break;
            case 5: numberSearch(); break;
            case 6: surnameSearch(); break;
            case 7: countrySearch(); break;
            case 8: categorySearch(); break;
            case 9: timeOfLapSorting(); break;
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
    indicateCursor(false);              //������� ������� �����
    while (true) {
        if (ch == KEY_RETURN || ch == KEY_UP || ch == KEY_DOWN || !isShowed) {              //���� ��������� ������ - ������ ����� ��� ������ ������� ����� ��� ���� ��� ���� �� ���� ��������
            isShowed = true;
            system("cls");              //������� ������
            if (ch == KEY_RETURN) {             //���� ��� ������ ������ �����
                indicateCursor(true);               //���������� ������� �����
                return choice;
            }
            if (ch == KEY_UP) choice--;             //���� ��� ������ ������ ������� �����
            if (ch == KEY_DOWN) choice++;               //���� ��� ������ ������ ������� ����
            if (choice > 10) choice = 1;                //���� ��������� ������ ������ 10 ������� ��� � ��������� ���������
            if (choice < 1) choice = 10;                //���� ��������� ������ ������ 1 ������� ��� � ��������� ���������
            printf("���� ������ � ����������:\n");
            for (int i = 0; line[i]; i++) {             //����� ����
                if (choice == i + 1) {              //���� ��������� ����� (i + 1)-�� ������ ������� �����
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);               //�������� ���� ������
                    printf("%c", pointer);              //����� ��������� �� �����
                }
                printf(i + 1 == choice ? "%s\n" : " %s\n", line[i]);                //����� ������
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);               //������� ����� �����
            }
        }
        ch = _getch();              //���� ������� � ����������
    }
}

void userManagement() {
    bool showPass = false, displayAllUsersFlag = true;
    while (true) {
        system("cls");              //������� ������
        switch (userManagementMenu()) {             //����� � ����� ������ ����
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
                while (displayAllUsersFlag == true) {
                    switch (displayAllUsersMenu(showPass)) {
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
    const char pointer = '>', *line[] = { "�������� �������.", "������� �������.", "������������� �������.",
                                          "�������� ���� ���������.", "����� �� ���� ���������� ��������������/����������������.", NULL };
    indicateCursor(false);                  //������� ������� �����
    while (true) {
        if (ch == KEY_RETURN || ch == KEY_UP || ch == KEY_DOWN || !isShowed) {                  //���� ��������� ������ - ������ ����� ��� ������ ������� ����� ��� ���� ��� ���� �� ���� ��������
            isShowed = true;
            system("cls");              //������� ������
            if (ch == KEY_RETURN) {                 //���� ��� ������ ������ �����
                indicateCursor(true);               //���������� ������� �����
                return choice;
            }
            if (ch == KEY_UP) choice--;                 //���� ��� ������ ������ ������� �����
            if (ch == KEY_DOWN) choice++;               //���� ��� ������ ������ ������� ����
            if (choice > 5) choice = 1;                 //���� ��������� ������ ������ 10 ������� ��� � ��������� ���������
            if (choice < 1) choice = 5;                 //���� ��������� ������ ������ 1 ������� ��� � ��������� ���������
            printf("���� ���������� ��������������/����������������:\n");
            for (int i = 0; line[i]; i++) {                 //����� ����
                if (choice == i + 1) {              //���� ��������� ����� (i + 1)-�� ������ ������� �����
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);               //�������� ���� ������
                    printf("%c", pointer);              //����� ��������� �� �����
                }
                printf(i + 1 == choice ? "%s\n" : " %s\n", line[i]);                //����� ������
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);               //������� ����� �����
            }
        }
        ch = _getch();              //���� ������� � ����������
    }
}

int userLoginOrRegMenu() {
    int choice = 1, ch = (int)NULL;
    bool isShowed = false;
    const char pointer = '>', *line[] = { "�����.", "������������������.", "�������� � ����." , NULL };
    indicateCursor(false);              //������� ������� �����
    while (true) {
        if (ch == KEY_RETURN || ch == KEY_UP || ch == KEY_DOWN || !isShowed) {                  //���� ��������� ������ - ������ ����� ��� ������ ������� ����� ��� ���� ��� ���� �� ���� ��������
            isShowed = true;
            system("cls");              //������� ������
            if (ch == KEY_RETURN) {             //���� ��� ������ ������ �����
                indicateCursor(true);               //���������� ������� �����
                return choice;
            }
            if (ch == KEY_UP) choice--;             //���� ��� ������ ������ ������� �����
            if (ch == KEY_DOWN) choice++;               //���� ��� ������ ������ ������� ����
            if (choice > 3) choice = 1;             //���� ��������� ������ ������ 10 ������� ��� � ��������� ���������
            if (choice < 1) choice = 3;             //���� ��������� ������ ������ 1 ������� ��� � ��������� ���������
            printf("���� ��� �������������:\n");
            for (int i = 0; line[i]; i++) {             //����� ����
                if (choice == i + 1) {              //���� ��������� ����� (i + 1)-�� ������ ������� �����
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);               //�������� ���� ������
                    printf("%c", pointer);              //����� ��������� �� �����
                }
                printf(i + 1 == choice ? "%s\n" : " %s\n", line[i]);                //����� ������
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);               //������� ����� �����
            }
        }
        ch = _getch();              //���� ������� � ����������
    }
}

int displayAllUsersMenu(bool showPass) {
    int choice = 1, ch = (int)NULL;
    bool isShowed = false;
    const char pointer = '>', *line[] = { "��������/������ ������.", "�������� � ����." , NULL };
    indicateCursor(false);
    while (true) {
        if (ch == KEY_RETURN || ch == KEY_UP || ch == KEY_DOWN || !isShowed) {                  //���� ��������� ������ - ������ ����� ��� ������ ������� ����� ��� ���� ��� ���� �� ���� ��������
            isShowed = true;
            system("cls");              //������� ������
            if (ch == KEY_RETURN) {             //���� ��� ������ ������ �����
                indicateCursor(true);               //���������� ������� �����
                return choice;
            }
            if (ch == KEY_UP) choice--;             //���� ��� ������ ������ ������� �����
            if (ch == KEY_DOWN) choice++;               //���� ��� ������ ������ ������� ����
            if (choice > 2) choice = 1;             //���� ��������� ������ ������ 10 ������� ��� � ��������� ���������
            if (choice < 1) choice = 2;             //���� ��������� ������ ������ 1 ������� ��� � ��������� ���������
            displayAllUsers(showPass);
            printf("���� ��������� ���� �������������:\n");
            for (int i = 0; line[i]; i++) {             //����� ����
                if (choice == i + 1) {              //���� ��������� ����� (i + 1)-�� ������ ������� �����
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);               //�������� ���� ������
                    printf("%c", pointer);              //����� ��������� �� �����
                }
                printf(i + 1 == choice ? "%s\n" : " %s\n", line[i]);                //����� ������
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);               //������� ����� �����
            }
        }
        ch = _getch();              //���� ������� � ����������
    }
}


//�� ��� ������� � �������
bool checkFile(const char* filename) {
    FILE* file = NULL;
    if (!(file = fopen(filename, "rt+")))               //���� ���� �� ����������� ��� ������ - ������� false
        return false;
    else {                  //���� ���� ������������� ��� ������ - ������� ��� � ������� true
        fclose(file);
        return true;
    }
}

bool createFile(const char* filename) {
    FILE* file = NULL;
    if ((file = fopen(filename, "wt"))) {               //���� ���� �������� �� ������� ��� � ������� true
        fclose(file);
        return true;
    }
    else return false;                //���� �� �������� ������� false
}

void crypterTool(int status) {
    int ch, key = 0;
    if (status == ENCRYPT) key = 2;         //key - ���� ����������
    else if (status == DECRYPT) key = -2;
    FILE *input = NULL, *output = NULL;
    if (!(input = fopen("db.dat", "rb"))) {
        //���� ���� � ��������/�������� �� ������� �������
        printf("[������!]����������: �� ������� ������� ���� � ��������/��������!\n\n");
        system("pause");
        exit(0);
    }
    if (!(output = fopen("tempdb.dat", "wb"))) {
        //���� ��������� ���� �� ������� �������
        printf("[������!]����������: �� ������� ������� ��������� ���� � ��������/��������!\n\n");
        system("pause");
        exit(0);
    }
    while (1) {
        fread(&ch, sizeof(char), 1, input);         //������ ������� �� �����
        if (feof(input)) break;             //���� ����� ����� �� ����� �� �����
        else {              //���� �� ����� �����
            if (ch != '\n')         //���� ����������� ������ �� ����� ������� ��������� ������
                ch += key;          //��������� � ���� ������� ����
            fwrite(&ch, sizeof(char), 1, output);           //�������� ���������� ������ �� ��������� ����
        }
    }
    fclose(input);          //������� ���� � ��������/������
    fclose(output);             //������� ��������� ����
    if (!(input = fopen("db.dat", "wb"))) {
        //���� ���� � ��������/�������� �� ������� �����������
        printf("[������!]����������: �� ������� ������������ ���� � ��������/��������!\n\n");
        system("pause");
        exit(0);
    }
    if (!(output = fopen("tempdb.dat", "rb"))) {
        //���� ��������� ���� �� ������� ������� ��� ������
        printf("[������!]����������: �� ������� ������� ��������� ���� � ��������/��������!\n\n");
        system("pause");
        exit(0);
    }
    while (1) {
        fread(&ch, sizeof(char), 1, output);            //������ ������� �� ���������� �����
        if (feof(output)) break;                //���� ����� ����� ����� �� �����
        else fwrite(&ch, sizeof(char), 1, input);               //�������� ����������� ������ � ���� � ��������/��������
    }
    fclose(output);             //������� ��������� ����
    if (remove("tempdb.dat")) {
        //���� �� ������� ������� ��������� ����
        printf("\n[������!]����������: �� ������� ������� ��������� ���� � ��������/��������!\n\n");
        system("pause");
        exit(0);
    }
    fclose(input);              //������� ���� � ��������/��������
}


//�� ��� ������� � ��������������
bool adminLogin() {
    system("cls");              //������� ������
    int i = 0, j = 0, attemptCounter = 0;
    bool isLoginRight = false, isPasswordRight = false;
    char *login = NULL, password[30], ch;
    login = bufferedInput(29, "������� �����: ");               //���� ������
    if (login == NULL)
        return false;
    for (i = 0; i < usersLinesCounter; i++) {         //����� ������ � �������
        if (!strcmp(login, (user + i)->login) && (user + i)->isAdmin == true) {         //���� ����� ����� ������ � �� ����� ����� ��������������
            isLoginRight = true;
            break;              //����� �� �����
        }
    }
    if (!isLoginRight) {                //���� ����� ����� �� ������
        printf("[������!]������ �������������� �� ����������!\n\n");
        system("pause");
        free(login);
        return false;
    }
    do {                //���� ������
        j = 0;
        printf("������� ������: ");
        while (true) {
            ch = (char)_getch();               //���� �������
            if (ch != '\0') {               //���� ��� �� ����-������
                if (ch == KEY_RETURN || ch == KEY_TAB) {            //���� ������ ����� ��� ������ ���������
                    password[j] = '\0';             //������ ����-������� � j-�� ������
                    break;              //����� �� �����
                }
                else if (ch == KEY_BKSP && j > 0) {           //���� ������ backspace � ������� �������� > 0
                    j--;
                    printf("\b \b");                //�������� ������� � ������
                }
                else if (ch == KEY_BKSP && j == 0) {          //���� ������ backspace � ������� �������� = 0
                    continue;           //������� �� ��������� �������� �����
                }
                else if (ch == KEY_ESC)
                    return false;
                else {
                    if (j < 29 && attemptCounter < 5) {         //���� ������� �������� < 29 � ������� ������� < 5
                        password[j++] = ch;         //������ ������� � ������
                        putchar('*');               //���������� ��������� ������� �������� "*"
                    }
                    else if (j < 29) {            //���� ������� �������� < 29 � ������� ������� >= 5
                        password[j++] = ch;         //������ ������� � ������
                        putchar(ch);                //����� ��������� �������
                    }
                }
            }
        }
        if (!strcmp(password, (user + i)->password))            //���� ��������� ������ ��������� � ������� ������
            isPasswordRight = true;
        else {              //���� �� ���������
            if (attemptCounter < 10) {                //���� ������� ������� ������ 10
                printf("\n[������!]�������� ������!");
                Sleep(1000);
                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);               //�������� ���� ��������� �����
                attemptCounter++;               //������� ������� ++
            }
            else {                //���� ������� ������� ������ 10
                printf("\n[������!]�������� ������!\n");
                printf("\n�� ��������� �������������� ����� ������� �����!\n\n");
                Sleep(1000);
                system("pause");
                return false;           //������� false
            }
        }
    } while (!isPasswordRight);             //���� �� ����� ������ ������ ������
    printf("\n\n�� ������� ��������������!");
    Sleep(1000);
    printf("%c[2K\r����� ����������, %s!\n\n", 27, (user + i)->login);
    free(login);
    system("pause");
    return true;            //���� ����������� ������ ������� ������� true
}

bool userLogin() {
    system("cls");              //������� ������
    int i = 0, j = 0, attemptCounter = 0;
    bool isLoginRight = false, isPasswordRight = false;
    char *login = NULL, password[30], ch;
    login = bufferedInput(29, "������� �����: ");               //���� ������
    if (login == NULL)
        return false;
    for (i = 0; i < usersLinesCounter; i++) {               //����� ������ � �������
        if (!strcmp(login, (user + i)->login) && (user + i)->isAdmin == false) {                //���� ����� ����� ������ � �� �� ����� ����� ��������������
            isLoginRight = true;
            break;              //����� �� �����
        }
    }
    if (!isLoginRight) {                //���� ����� ����� �� ������
        printf("[������!]������ ������������ �� ����������!\n\n");
        system("pause");
        free(login);
        return false;
    }
    do {                //���� ������
        j = 0;
        printf("������� ������: ");
        while (true) {
            ch = (char)_getch();               //���� �������
            if (ch != '\0') {               //���� ��� �� ����-������
                if (ch == KEY_RETURN || ch == KEY_TAB) {                //���� ������ ����� ��� ������ ���������
                    password[j] = '\0';             //������ ����-������� � j-�� ������
                    break;              //����� �� �����
                }
                else if (ch == KEY_BKSP && j > 0) {               //���� ������ backspace � ������� �������� > 0
                    j--;
                    printf("\b \b");                //�������� ������� � ������
                }
                else if (ch == KEY_BKSP && j == 0)               //���� ������ backspace � ������� �������� = 0
                    continue;               //������� �� ��������� �������� �����
                else if (ch == KEY_ESC)
                    return false;
                else {
                    if (j < 29 && attemptCounter < 5) {             //���� ������� �������� < 29 � ������� ������� < 5
                        password[j++] = ch;             //������ ������� � ������
                        putchar('*');               //���������� ��������� ������� �������� "*"
                    }
                    else if (j < 29) {                //���� ������� �������� < 29 � ������� ������� >= 5
                        password[j++] = ch;             //������ ������� � ������
                        putchar(ch);                //����� ��������� �������
                    }
                }
            }
        }
        if (!strcmp(password, (user + i)->password))                //���� ��������� ������ ��������� � ������� ������
            isPasswordRight = true;
        else {              //���� �� ���������
            if (attemptCounter < 10) {                //���� ������� ������� ������ 10
                printf("\n[������!]�������� ������!");
                Sleep(1000);
                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);               //�������� ���� ��������� �����
                attemptCounter++;               //������� ������� ++
            }
            else {                //���� ������� ������� ������ 10
                printf("\n[������!]�������� ������!\n");
                printf("\n�� ��������� �������������� ����� ������� �����!\n\n");
                Sleep(1000);
                system("pause");
                return false;               //������� false
            }
        }
    } while (!isPasswordRight);             //���� �� ����� ������ ������ ������
    printf("\n\n�� ������� ��������������!");
    Sleep(1000);
    printf("%c[2K\r����� ����������, %s!\n\n", 27, (user + i)->login);
    free(login);
    system("pause");
    return true;                //���� ����������� ������ ������� ������� true
}

void firstStartAdminReg() {
    FILE *file = NULL;
    char *login = NULL, *password = NULL;
    USER newUser;
    system("cls");          //������� ������
    printf("-------------------------------------------------------------------------------------------------------------------------------------------\n"
           "                  �� ����� � ��������� � ������ ���. ��� ���������� ������ ��������� ����� ���������������� ��������������!                \n"
           "-------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("����������� ��������������.\n\n");
    do {
        login = loginInput(29, "������� �����: ");              //���� ������
    } while (login == NULL);
    strcpy(newUser.login, login);                //����������� ������ � ���������� ���� USER
    do {
        password = maskedPasswordInput(29, "������� ������: ");
    }
    while(password == NULL);             //���� ������
    strcpy(newUser.password, password);             //����������� ������ � ���������� ���� USER
    newUser.isAdmin = 1;                //��������� ���� �������������� � ���������� ���� USER
    if ((file = fopen("db.dat", "ab+"))) {              //���� ���� ������� �������
        fwrite(&newUser, sizeof(USER), 1, file);                //������ ���������� ���� USER � ����
        fclose(file);               //�������� �����
        crypterTool(ENCRYPT);               //����������� �����
        printf("\n����� ������������� ������� ���������������!\n\n");
        system("pause");
    }
    else {              //���� �� ������� ������� ����
        printf("\n[������!]�����������: �� ������� ������� ���� ��� ���������� ������ ��������������!\n");
        exit(0);
    }
    system("cls");              //������� ������
}

void usersInit() {
    FILE* file = NULL;
    long fsize = 0;
    if (checkFile("db.dat")) {               //���� ���� ����������
        if ((file = fopen("db.dat", "rb"))) {                //���� ���� ������� ������� ��� ������
            fseek(file, 0, SEEK_END);               //��������� ��������� � ����� �����
            fsize = ftell(file);                //������ ���� ����� ����������
            usersLinesCounter = fsize / sizeof(USER);             //������ ���������� �������������
            rewind(file);               //��������� ��������� �� ������ �����
            if (usersLinesCounter != 0) {               //���� ���� ������ ���� ������������
                crypterTool(DECRYPT);               //������������ ����
                user = (USER *)malloc(usersLinesCounter * (sizeof(USER)));          //��������� ������
                for (int i = 0; i < usersLinesCounter; i++)             //������ �� ����� � ������ � ������
                    fread((user + i), sizeof(USER), 1, file);
                fclose(file);               //�������� �����
                crypterTool(ENCRYPT);               //����������� ����
            }
            else {                //���� ��� �� ����� ������
                firstStartAdminReg();               //������� ����������� ������������ ��� ������ ������� ���������
                usersInit();                //������������� �������������
            }
        }
        else {                //���� ���� �� ������� �������
            printf("[������!]������������� �������������: �� ������� ������� ���� � ��������/��������!\n");
            system("pause");
            exit(0);
        }
    }
    else if (createFile("db.dat")) {                  //���� ���� �� ���������� - �������
        firstStartAdminReg();
        usersInit();
    }
    else {                //���� ���� �� ���������� � ��� �� ������� �������
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
    USER newUser;
    printf("�������� ������������:\n");
    do {
        login = loginInput(29, "������� �����: ");              //���� ������
        if (login == NULL)
            return;
        for (int i = 0; i < usersLinesCounter; i++) {           //�������� �� ������������� ������ ������
            if (strcmp((user + i)->login, login) == 0) {                //���� i-�� ����� ��������� � ���������
                isLoginExist = true;
                break;              //����� �� �����
            }
            else isLoginExist = false;              //���� �� ���������
        }
        if (isLoginExist) {                 //���� ����� ����� ������
            printf("[������!]����� ������� ��� ����������!");
            Sleep(1000);
            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);               //������� ���� ��������� �����
        }
        else strcpy(newUser.login, login);
    } while (isLoginExist);             //���� �� ����� ������ �� ������������ �����
    free(login);                //������������ ������ ��� ������
    password = maskedPasswordInput(29, "������� ������: ");             //���� ������
    if (password == NULL)
        return;
    strcpy(newUser.password, password);
    free(password);             //������������ ������ ��� ������
    indicateCursor(false);              //������� ������� �����
    while (true) {
        if (ch == KEY_LEFT || ch == KEY_RIGHT || ch == KEY_RETURN || ch == KEY_ESC|| !isShowed) {               //���� ��������� ������ - ������ ����� ��� ������ ������� ����� ��� ���� ��� ���� �� ���� ��������
            isShowed = true;
            if (ch == KEY_RETURN) {             //���� ��������� ������ ������ �����
                printf("%c[2K\r", 27);              //������� ������ � ������
                printf("�������������? ");
                for (int i = 0; line[i]; i++)               //����� ������ �� �����
                    if (choice == i + 1)                //���� ����� ����� (i+1)-�� ������ �������
                        printf("%s", line[i]);              //����� ���� ������
                indicateCursor(true);               //���������� ������� �����
                break;              //����� �� �����
            }
            printf("%c[2K\r", 27);              //������� ������ � ������
            if (ch == KEY_LEFT) choice--;               //���� ������ ������� �����
            if (ch == KEY_RIGHT) choice++;              //���� ������ ������� ������
            if (ch == KEY_ESC) return;
            if (choice > 2) choice = 2;             //���� ��������� ������ ������ 2 ������� ��� � ��������� ���������
            if (choice < 1) choice = 1;             //���� ��������� ������ ������ 1 ������� ��� � �������� ���������
            printf("�������������? ");
            for (int i = 0; line[i]; i++) {             //����� ���� ������
                if (choice == i + 1) {              //���� ����� ����� (i+1) - �� ������ �������
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);               //��������� ����� ������
                    printf("%c", pointer);              //����� ���������
                }
                printf(i + 1 == choice ? "%s " : " %s ", line[i]);              //����� �����
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);               //��������� ����� �����
            }
        }
        ch = _getch();              //���� �������
    }
    if (choice == 1) newUser.isAdmin = 1;               //���� ����� ����� 1 ���� ����� �������������� ����� ������������
    else newUser.isAdmin = 0;               //� ������ ������� �� ������ ����� ��������������
    user = (USER*)realloc(user, (usersLinesCounter + 1) * sizeof(USER));                //����������������� ������
    user[usersLinesCounter] = newUser;
    if (checkFile("db.dat")) {              //���� ���� ����������
        crypterTool(DECRYPT);               //������������ ����
        if ((file = fopen("db.dat", "ab+"))) {              //���� ���� ������� �������
            fwrite((user + usersLinesCounter), sizeof(USER), 1, file);              //������ ���� ������ ������� �������� � ����
            fclose(file);               //������� ����
            printf("\n������� ������� ��������!\n\n");
            _flushall();                //������������� ��� �����
            usersLinesCounter++;
        }
        else printf("[������!]���������� �������������: ������ �������� ����� � ��������/��������! ������������ �� ��������!\n\n");             //���� ���� �� ������� �������
        crypterTool(ENCRYPT);               //����������� ����
    }
    else printf("[������!]���������� �������������: ���� �� ����������!\n\n");              //���� ���� �� ����������
    system("pause");
}

void userDelete() {
    char *login = NULL;
    int i = 0, adminCounter = 0;
    bool isLoginExist = false;
    FILE* file = NULL;
    for (int j = 0; j < usersLinesCounter; j++) {            //������� ���������� ���������������
        if ((user + j)->isAdmin)                //���� j-�� ������������ ����� ����� ���������������
            adminCounter++;             //������� ���������� ���������������� ++
    }
    displayAllUsers(false);             //����� ���� ������������� �� �����, �� ��������� �� ������
    printf("�������� ��������.\n");
    login = bufferedInput(29, "������� ����� ��������, ������� �� ������ �������: ");               //���� ������
    if (login == NULL)
        return;
    for (i = 0; i < usersLinesCounter; i++) {               //����� ������ ������ � �������
        if (!strcmp((user + i)->login, login)) {                //���� i-�� ����� ��������� � ���������
            isLoginExist = true;
            break;                  //����� �� �����
        }
    }
    if (!isLoginExist) {                //���� ����� ����� �� ������
        printf("[������!]������ �������� �� ����������!\n\n");
        system("pause");
        return;                 //����� �� �������
    }
    free(login);                //������������ ������ ��� ������
    if (adminCounter == 1 && (user + i)->isAdmin) {              //���� ��������� ����� �������������� � �� ���������
        system("cls");
        displayAllUsers(false);
        printf("[������!]������ ������� ���������� ��������������!\n\n");
    }
    else {
        if (checkFile("db.dat")) {             //���� ���� ����������
            crypterTool(DECRYPT);               //������������
            if ((file = fopen("db.dat", "wb"))) {               //���� ���� ������� �����������
                for (int j = i; j < usersLinesCounter; j++)             //�������� ��� ������ ����� ����� ���������� ������������
                    *(user + j) = *(user + (j + 1));
                user = (USER *)realloc(user, sizeof(USER) * usersLinesCounter);            //���������������� ������
                usersLinesCounter--;
                for (int j = 0; j < usersLinesCounter; j++)             //���������� � ����
                    fwrite((user + j), sizeof(USER), 1, file);
                fclose(file);                   //������� ����
                system("cls");              //������� ������
                displayAllUsers(false);             //�������� ���� �������������, ������� �� ������
                printf("������� ������� �����!\n\n");
            }
            else
                printf("[������!]�������� �������������: ������ �������� ����� � ��������/��������! ���� �������!\n\n");               //���� ���� �� ������� �����������
            crypterTool(ENCRYPT);               //�����������
        }
        else
            printf("[������!]�������� �������������: ������ �������� ����� � ��������/��������!\n\n");             //���� ���� �� ����������
    }
    system("pause");
}

void userEdit() {
    char *login = NULL, *newLogin = NULL, *newPassword = NULL;
    int i = 0, adminCounter = 0;
    bool isLoginExist = false, isNewLoginExist = false, editFlag = false, showPass = false;
    FILE* file = NULL;
    displayAllUsers(showPass);              //�������� ���� �������������, ������� �� ������
    login = loginInput(29, "������� ����� ��������, ������� �� ������ ���������������: ");               //���� ������
    if (login == NULL)
        return;
    for (i = 0; i < usersLinesCounter; i++) {               //����� ���������� ������ � �������
        if (!strcmp((user + i)->login, login)) {                //���� i-�� ����� ��������� � ���������
            isLoginExist = true;
            break;              //����� �� �����
        }
        else isLoginExist = false;
    }
    if (!isLoginExist) {                //���� ����� ����� �� ������
        printf("[������!]������ �������� �� ����������!\n\n");
        system("pause");
        return;
    }
    free(login);                //������������ ������ ��� ������
    while (!editFlag) {
        adminCounter = 0;               //��������� �������� ���������� ���������������
        for (int j = 0; j < usersLinesCounter; j++) {                //������� ���������� ���������������
            if ((user + j)->isAdmin)                //���� j-�� ������������� ����� ����� ��������������
                adminCounter++;             //������� ��������������� ++
        }
        switch (userEditMenu(i, showPass)) {                //����� ���������� �� ������������� ������������ � ���� ��������������
            case 1: {
                printf("�������� �����.\n");
                do {
                    newLogin = loginInput(29, "������� ����� �����: ");                 //���� ������ ������
                    if (newLogin == NULL)
                        break;
                    for (int j = 0; j < usersLinesCounter; j++) {               //����� ���������� ������ � �������
                        if (strcmp((user + j)->login, newLogin) == 0) {             //���� j-�� ����� ��������� � ���������
                            isNewLoginExist = true;
                            break;              //����� �� �����
                        }
                        else isNewLoginExist = false;
                    }
                    if (isNewLoginExist) {              //���� ����� ����� ������
                        printf("[������!]����� ����� ��� ����������!\n");
                        Sleep(1000);
                        printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
                    }
                } while (isNewLoginExist);              //���� �� ����� ������ ����� ����� � �������
                if (newLogin != NULL) {
                    strcpy((user + i)->login, newLogin);                //����������� ������ ������ � ������������� ������ ������� ��������
                    displayEditableUser(i, showPass);               //����� ���������� �� ������������� ������������
                    printf("����� ������� �������!\n\n");
                    free(newLogin);             //������������ ������ ��� ������ ������
                    system("pause");
                }
                break;              //����� �� switch
            }
            case 2: {
                printf("��������� ������.\n");
                newPassword = maskedPasswordInput(29, "������� ����� ������: ");                    //���� ������ ������
                if (newPassword != NULL) {
                    strcpy((user + i)->password, newPassword);              //����������� ������ ������ � ������������� ������ ������� ��������
                    displayEditableUser(i, showPass);               //����� ���������� �� ������������� ������������
                    printf("������ ������� �������!\n\n");
                    free(newPassword);              //������������ ������ ��� ������ ������
                    system("pause");
                }
                break;              //����� �� switch
            }
            case 3: {
                if (adminCounter == 1 && (user + i)->isAdmin)                //���� �������� ������������� ����� �������������� ���������� ��������������
                    printf("[������!]������ �������� ����� ���������� ��������������!\n\n");
                else {
                    if ((user + i)->isAdmin) {              //���� ������������ ����� ����� �������������� ������ ��
                        (user + i)->isAdmin = false;
                        displayEditableUser(i, showPass);               //����� ���������� �� ������������� ������������
                        printf("����� �������������� ������� ��������.\n\n");
                    }
                    else {                    //���� ������������ �� ����� ����� ������������� ���� ��
                        (user + i)->isAdmin = true;
                        displayEditableUser(i, showPass);               //����� ���������� �� ������������� ������������
                        printf("����� �������������� ������� ��������.\n\n");
                    }
                }
                system("pause");
                break;              //����� �� switch
            }
            case 4: showPass = showPass == true ? false : true; break;              //��������� ���������� ������� ���������� ��� �������� ������
            case 5: editFlag = true; break;
            default: break;
        }
        if (editFlag) break;
    }
    if (checkFile("db.dat")) {              //���� ���� ����������
        crypterTool(DECRYPT);               //������������
        if ((file = fopen("db.dat", "wb"))) {               //���� ���� ������� �����������
            for (i = 0; i < usersLinesCounter; i++)             //������ i-��� ������������ � ����
                fwrite((user + i), sizeof(USER), 1, file);
            fclose(file);               //�������� �����
        }
        else printf("[������!]�������������� �������������: �� ������� ������� ���� � ��������/��������! ���� �������!\n\n");               //���� ���� �� ������� �����������
        crypterTool(ENCRYPT);               //�����������
    }
    else printf("[������!]�������������� �������������: �� ������� ������� ���� � ��������/��������!\n\n");             //���� ���� �� ����������
}

void displayEditableUser(int i, bool showPass) {
    char yes[] = "��", no[] = "���", mask[] = "**********";
    system("cls");
    printf("-----------------------------------------------------------------------------------\n");
    printf("|�����:                       |������:                      |����� ��������������:|\n");
    printf("-----------------------------------------------------------------------------------\n");
    printf("|%-29s|%-29s|%-21s|\n", (user + i)->login, showPass == true ? (user + i)->password : mask, (user + i)->isAdmin == 1 ? yes : no);
    printf("-----------------------------------------------------------------------------------\n\n");
}

void displayAllUsers(bool showPass) {
    char yes[] = "��", no[] = "���", mask[] = "**********";
    printf("-----------------------------------------------------------------------------------------\n");
    printf("|�    |�����:                       |������:                      |����� ��������������:|\n");
    printf("-----------------------------------------------------------------------------------------\n");
    for (int i = 0; i < usersLinesCounter; i++)
        printf("|%-5i|%-29s|%-29s|%-21s|\n", i + 1, (user + i)->login, showPass == true ? (user + i)->password : mask, (user + i)->isAdmin == 1 ? yes : no);
    printf("-----------------------------------------------------------------------------------------\n\n");
}

void userReg() {
    bool isLoginExist = false;
    char *login = NULL, *password = NULL;
    FILE* file = NULL;
    USER newUser;
    printf("����������� ������������:\n");
    do {
        login = loginInput(29, "������� �����: ");                  //���� ������
        if (login == NULL)
            return;
        for (int i = 0; i < usersLinesCounter; i++) {                   //����� ���������� ������ � �������
            if (strcmp((user + i)->login, login) == 0) {                    //���� i-�� ����� ��������� � ���������
                isLoginExist = true;
                break;              //����� �� �����
            }
            else isLoginExist = false;
        }
        if (isLoginExist) {                 //���� ����� ����� ������
            printf("[������!]����� ������� ��� ����������!");
            Sleep(1000);
            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);               //�������� ���� ��������� ����� � ������
        }
        else strcpy(newUser.login, login);              //���� ����� ����� �� ������, ����������� � ���������� ������ ������� ��������
    } while (isLoginExist);             //���� ����� ����� ����� �� ������
    free(login);                //������������ ����������
    password = maskedPasswordInput(29, "������� ������: ");             //���� ������
    if (password == NULL)
        return;
    strcpy(newUser.password, password);             //����������� ������ � ���������� ������ ������� ��������
    free(password);                 //������������ ����������
    newUser.isAdmin = 0;                //�� ������ ����� ��������������
    user = (USER*)realloc(user, (usersLinesCounter + 1) * sizeof(USER));                    //����������������� ������
    user[usersLinesCounter] = newUser;
    if (checkFile("db.dat")) {              //���� ���� ����������
        crypterTool(DECRYPT);               //������������
        if ((file = fopen("db.dat", "ab+"))) {              //���� ���� ������� �������
            fwrite((user + usersLinesCounter), sizeof(USER), 1, file);              //�������� ������ ������� �������� � ����
            fclose(file);               //������� ����
            printf("\n�� ������� ������������������!\n\n");
            _flushall();
            usersLinesCounter++;                //������� ������������� ++
        }
        else printf("[������!]���������� �������������: ������ �������� ����� � ��������/��������! ������������ �� ��������!\n\n");             //���� ���� �� ������� �������
        crypterTool(ENCRYPT);               //�����������
    }
    else printf("[������!]���������� �������������: ���� �� ����������!\n\n");              //���� ���� �� ����������
    system("pause");
}


//�� ��� ������� � �����������
void membersOpenAdmin() {
    int choice = 1, ch = (int)NULL;
    bool isShowed = false;
    const char *line[] = { "��", "���", NULL }, pointer = '>';
    if (!checkFile("info.dat")) {               //���� ���� �� ����������
        printf("[������!]�������� ����������: ���� ��� �� ������!\n");
        indicateCursor(false);              //������ ������� �����
        while (true) {
            if (ch == KEY_RETURN || ch == KEY_LEFT || ch == KEY_RIGHT || ch == KEY_ESC || !isShowed) {               //���� ��������� ������ - ������ ����� ��� ������ ������� ����� ��� ���� ��� ���� �� ���� ��������
                isShowed = true;
                printf("%c[2K\r", 27);              //������� ������ � ������
                if (ch == KEY_RETURN) {             //���� ������ �����
                    indicateCursor(true);               //���������� ������� �����
                    break;              //����� �� �����
                }
                if (ch == KEY_LEFT) choice--;               //���� ������ "������� �����"
                if (ch == KEY_RIGHT) choice++;              //���� ������ "������� ������"
                if (ch == KEY_ESC) return;
                if (choice > 2) choice = 2;             //���� ��������� ������ ������ 2, ������� ��� � �������� ���������
                if (choice < 1) choice = 1;             //���� ��������� ������ ������ 1, ������� ��� � ��������� ���������
                printf("������� ����? ");
                for (int i = 0; line[i]; i++) {             //����� ���� ������ �������� �����
                    if (choice == i + 1) {              //���� ��������� ������ ����� (i+1)-�� ������� �������
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);               //��������� ����� ������
                        printf("%c", pointer);              //����� ���������
                    }
                    printf(i + 1 == choice ? "%s " : " %s ", line[i]);              //����� ����� ����
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);               //��������� ����� �����
                }
            }
            ch = _getch();              //���� �������
        }
        if (choice == 1) {              //���� ���������� ����� 1
            if (createFile("info.dat")) {               //���� ������� ������� ����
                printf("�������� ����������: ���� ������� ������!\n");
                membersInit();              //������������� ����������
                system("pause");
            }               //���� ���� �� ������� �������
            else printf("[������!]�������� ����������: �� ������� ������� ����!\n");
        }
    }
    else {              //���� ���� ����������
        membersInit();              //������������� ����������
        system("pause");
    }
};

void membersOpenUser() {
    if (checkFile("info.dat"))              //���� ���� ����������
        membersInit();              //������������� ����������
    else                //���� ���� �� ����������
        printf("[������!]�������� ����������: ���� ��� �� ������!\n\n");
}

void membersInit() {
    FILE *file = NULL;
    long fsize;
    if (info)               //���� ��������� �� ������ �������� �� ����� NULL
        printf("[������!]�������� ����������: ���� ��� ������!\n\n");
    else {              //���� ��������� �� ������ �������� ����� NULL
        if ((file = fopen("info.dat", "rb+"))) {                //���� ���� ������� �������
            fseek(file, 0, SEEK_END);     //��������� ��������� � ����� �� ����� �����
            fsize = ftell(file);          //������� ������ � ����� �� ���������
            infoLinesCounter = fsize / sizeof(INFORMATION);             //������� ���������� ����������
            rewind(file);               //��������� ��������� �� ������ �����
            info = (INFORMATION *)malloc(infoLinesCounter * sizeof(INFORMATION));               //��������� ������
            for (int i = 0; i < infoLinesCounter; i++)              //������ ���������� �� �����
                fread((info + i), sizeof(INFORMATION), 1, file);
            fclose(file);               //������� ����
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
    INFORMATION newMember;
    if (!info)              //���� ��������� �� ������ �������� ����� NULL
        printf("[������!]���������� ����������: ���� �� ������!\n\n");
    else if (!(file = fopen("info.dat", "ab+")))                //���� �� ������� ������� ���� ��� ����������
        printf("[������!]���������� ����������: �� ������� ������� ���� ��� ����������!\n");
    else {              //���� ������� ������� ���� ��� ����������
        printf("���������� ���������.\n");
        do {
            do {
                newMember.number = checkToEnterOnlyInt(3, "������� ����� ���������: ");                //���� ������ ���������
                if (newMember.number == INT_MIN)
                    return;
                if (newMember.number < 1) {                //���� ��������� ����� < 1
                    printf("[������!]������� ����� ������ 0!");
                    Sleep(1000);
                    printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);               //�������� ���� ��������� ����� � ������
                }
            } while (newMember.number < 1);                //���� �� ����� ������ ����� > 0
            for (int i = 0; i < infoLinesCounter; i++) {                //����� ��������� � ����� ������� � ������� ��������
                if ((info + i)->number == newMember.number) {              //���� i-�� �������� ����� ����� �����
                    isMemberExist = true;
                    break;              //����� �� �����
                }
                else isMemberExist = false;
            }
            if (isMemberExist) {                //���� ����� �������� ��� ������
                printf("[������!]�������� � ����� ������� ��� ����������!");
                Sleep(1000);
                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);               //�������� ���� ��������� ����� � ������
            }
        } while (isMemberExist);                //���� �������� � ����� ������� ����� �� ������
        firstname = stringInputCheck(15, "������� ��� ���������: ");                //���� ����� ���������
        if (firstname == NULL)
            return;
        strcpy(newMember.fullname.firstname, firstname);               //����������� ����� ��������� � ������ ������� ��������
        free(firstname);                //������������ ������ ��� ����������, ���������� ��� ���������
        surname = stringInputCheck(15, "������� ������� ���������: ");              //���� ������� ���������
        if (surname == NULL)
            return;
        strcpy(newMember.fullname.surname, surname);               //����������� ������� ��������� � ������ ������� ��������
        free(surname);              //������������ ������ ��� ����������, ���������� ������� ���������
        lastname = stringInputCheck(15, "������� �������� ���������: ");                //���� �������� ���������
        if (lastname == NULL)
            return;
        strcpy(newMember.fullname.lastname, lastname);             //����������� �������� ��������� � ������ ������� ��������
        free(lastname);             //������������ ������ ��� ����������, ���������� �������� ���������
        country = stringInputCheck(15, "������� ������ ���������: ");               //���� ������ ���������
        if (country == NULL)
            return;
        strcpy(newMember.country, country);                //����������� �������� ��������� � ������ ������� ��������
        free(country);              //������������ ������ ��� ����������, ���������� ������ ���������
        dateOfBirthInput(&(newMember.dateOfBirth.day), &(newMember.dateOfBirth.month), &(newMember.dateOfBirth.year), "������� ���� �������� ���������(� ������� ��.��.����): ");
        if (newMember.dateOfBirth.day == INT_MIN && newMember.dateOfBirth.month == INT_MIN && newMember.dateOfBirth.year == INT_MIN)
            return;
        if (newMember.dateOfBirth.month > aTm->tm_mon + 1)             //���� ��������� ����� ������ �������� ������
            newMember.dateOfBirth.age = 2018 - newMember.dateOfBirth.year;                //�� 2018 ���������� ��������� ��� � ���������� �������
        else newMember.dateOfBirth.age = 2019 - newMember.dateOfBirth.year;               //�� 2018 ���������� ��������� ��� � ���������� �������
        category = categoryInput(10, "������� ������ ���������: ");             //���� ������� ���������
        if (category == NULL)
            return;
        strcpy(newMember.category, category);              //����������� ������� ��������� � ������ ������� ��������
        free(category);             //������������ ������ ��� ����������, ���������� ������ ���������
        model = stringInputCheck(15, "������� ������ ������� ���������: ");             //���� ������ ������� ���������
        if (model == NULL)
            return;
        strcpy(newMember.model, model);                //����������� ������ ������� ��������� � ������ ������� ��������
        free(model);                //������������ ������ ��� ����������, ���������� ������ ������� ���������
        do {
            newMember.points = checkToEnterOnlyInt(4, "������� ���������� ����� ���������: ");             //���� ���������� ����� ���������
            if (newMember.points == INT_MIN)
                return;
            if (newMember.points < 0 || newMember.points > 9999) {                //���� ��������� ���������� ����� ��������� ������ 0 ��� ������ 9999
                printf("[������!]������� ����� �� 0 �� 9999!");
                Sleep(1000);
                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);               //�������� ���� ��������� ����� ���������
            }
        } while (newMember.points < 0 || newMember.points > 9999);                //���� �� ����� ������� ���������� ����� ��������� ������ 0 ��� ������ 9999
        timeOfLapInput(&(newMember.timeOfLap.minutes), &(newMember.timeOfLap.seconds), "������� ����� ����� ���������(� ������� ��:��): ");
        if (newMember.timeOfLap.minutes == INT_MIN && newMember.timeOfLap.seconds == INT_MIN)
            return;
        info = (INFORMATION *)realloc(info, (infoLinesCounter + 1) * sizeof(INFORMATION));              //����������������� ������
        info[infoLinesCounter] = newMember;
        fwrite((info + infoLinesCounter), sizeof(INFORMATION), 1, file);                //������ ������ ������� �������� � ����
        _flushall();
        fclose(file);               //�������� �����
        infoLinesCounter++;             //������� ���������� ���������� ++
        printf("�������� ������� ��������!\n\n");
        system("pause");
    }
}

void memberDelete() {
    int delNumber = 0, i = 0;
    bool isNumberExist = false;
    FILE *file = NULL;
    if (!info) {                //���� ��������� �� ������ �������� ����� NULL
        printf("[������!]�������� ����������: ���� �� ������!\n\n");
    }
    else if (infoLinesCounter == 0) {               //���� ���������� ���������� ����� ����
        printf("[������!]�������� ����������: ���� ����!\n\n");
    }
    else {
        displayAllMembers();                //����� ���� ���������� �� �����
        printf("�������� ���������.\n");
        delNumber = checkToEnterOnlyInt(3, "������� ����� ��������� ��� ��������: ");               //���� ������ ��������� ��� ��������
        if (delNumber == INT_MIN)
            return;
        for (i = 0; i < infoLinesCounter; i++) {                //����� ��������� � ������� �������� � ����� �������
            if (delNumber == (info + i)->number) {              //���� �������� ����� ����� ������ i-�� ���������
                isNumberExist = true;
                break;              //����� �� �����
            }
            else isNumberExist = false;
        }
        if (!isNumberExist) {               //���� ��������� ����� �� ������
            printf("[������!]��������� � ����� ������� �� ����������!\n\n");
            system("pause");
            return;             //����� �� �������
        }
        for (int j = i; j < infoLinesCounter; j++)              //�������� ��� ������ ����� ��������� ����� �� ����
            *(info + j) = *(info + (j + 1));
        info = (INFORMATION*)realloc(info, sizeof(INFORMATION)*infoLinesCounter);               //����������������� ������
        infoLinesCounter--;             //������� ���������� ���������� --
        if (checkFile("info.dat")) {                //���� ���� ����������
            if ((file = fopen("info.dat", "wb"))) {             //���� ���� ������� �����������
                for (int j = 0; j < infoLinesCounter; j++)              //������ ����� ������� �������� � ����
                    fwrite((info + j), sizeof(INFORMATION), 1, file);
                fclose(file);               //�������� �����
                system("cls");
                if(infoLinesCounter != 0)
                    displayAllMembers();
                printf("�������� ������� �����!\n\n");
            }
            else printf("[������!]�������� ����������: �� ������� ������������ ����! ���� �������!\n\n");               //���� ���� �� ������� �����������
        }
        else printf("[������!]�������� ����������: �� ������� ����� ����!\n\n");                //���� ���� �� ����������
    }
    system("pause");
}

void memberEdit() {
    time_t t = time(NULL);
    FILE *file = NULL;
    struct tm *aTm = localtime(&t);
    bool isMemberExist = false, isNumberExist = false, infoEditFlag = false;
    int number = 0, i = 0, j = 0, newNumber = 0, day = 0, month = 0, year = 0, points = 0, minutes = 0, seconds = 0;
    char *firstname = NULL, *surname = NULL, *lastname = NULL, *country = NULL, *category = NULL, *model = NULL;
    if (!info) {                //���� ��������� �� ������ �������� ����� NULL
        printf("[������!]�������������� ����������: ���� �� ������!\n\n");
        system("pause");
    }
    else if (infoLinesCounter == 0) {               //���� ������� ���������� ����� ����
        printf("[������!]�������������� ����������: ���� ����!\n\n");
        system("pause");
    }
    else {
        displayAllMembers();                //����� ���� ���������� �� �����
        number = checkToEnterOnlyInt(3, "������� ����� ���������, �������� ����� ���������������: ");               //���� ������ ���������
        if (number == INT_MIN)
            return;
        for (i = 0; i < infoLinesCounter; i++) {                //����� ��������� � ����� ������� � ������� ��������
            if ((info + i)->number == number) {             //���� i-�� �������� ����� ����� �����
                isMemberExist = true;
                break;              //����� �� �����
            }
            else isMemberExist = false;
        }
        if (!isMemberExist) {               //���� �������� � ����� ������� �� ������
            printf("[������!]��������� � ����� ������� �� ����������!\n\n");
            system("pause");
            return;             //����� �� �������
        }
        while (!infoEditFlag) {
            switch (memberEditMenu(i)) {                //����� ���������� �� ������������� ��������� � ���� ��������������
                case 1: {
                    printf("�������� ������ ���������.\n");
                    do {
                        do {
                            newNumber = checkToEnterOnlyInt(3, "������� ����� ����� ���������: ");                  //���� ������ ������ ���������
                            if (newNumber == INT_MIN)
                                break;
                            if (newNumber < 1) {                //���� ��������� ����� ������ 1
                                printf("[������!]������� ����� ������ 0!");
                                Sleep(1000);
                                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);               //�������� ���� ��������� ����� � ������
                            }
                        } while (newNumber < 1);                //���� �� ����� ������ ����� ������ 0
                        if (newNumber != INT_MIN) {
                            for (j = 0; j < infoLinesCounter; j++) {                    //����� ��������� � ����� ������� � ������� ��������
                                if ((info + j)->number == newNumber) {              //���� j-�� �������� ����� ����� �����
                                    isNumberExist = true;
                                    break;              //����� �� �����
                                }
                                else isNumberExist = false;
                            }
                            if (isNumberExist) {                //���� �������� � ����� ������� ������
                                printf("[������!]�������� � ����� ������� ��� ����������!");
                                Sleep(1000);
                                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);               //�������� ���� ��������� �����
                            }
                        }
                    } while (isNumberExist);                //���� �� ����� ������ �� ������������ �����
                    if (newNumber != INT_MIN) {
                        (info + i)->number = newNumber;             //��������� ������ �� ��������� � j-��� ���������
                        displayEditableMember(i);               //����� ���� ���������� �� ������������� ���������
                        printf("����� ��������� ������� �������!\n\n");
                        system("pause");
                    }
                    break;              //����� �� switch
                }
                case 2: {
                    printf("��������� ����� ���������.\n");
                    firstname = stringInputCheck(15, "������� ����� ��� ���������: ");              //���� ����� ��� ���������
                    if (firstname != NULL) {
                        strcpy((info + i)->fullname.firstname, firstname);              //����������� ������ ����� � ������������� ������ ������� ��������
                        free(firstname);                //������������ ������ ��� ����������, ���������� ��� ���������
                        displayEditableMember(i);               //����� ���� ���������� �� ������������� ���������
                        printf("��� ��������� ������� ��������!\n\n");
                        system("pause");
                    }
                    break;              //����� �� switch
                }
                case 3: {
                    printf("��������� ������� ���������.\n");
                    surname = stringInputCheck(15, "������� ����� ������� ���������: ");                //���� ����� ������� ���������
                    if (surname != NULL) {
                        strcpy((info + i)->fullname.surname, surname);              //����������� ����� ������� � ������������� ������ ������� ��������
                        free(surname);              //������������ ������ ��� ����������, ���������� ������� ���������
                        displayEditableMember(i);               //����� ���� ���������� �� ������������� ���������
                        printf("������� ��������� ������� ��������!\n\n");
                        system("pause");
                    }
                    break;              //����� �� switch
                }
                case 4: {
                    printf("��������� �������� ���������.\n");
                    lastname = stringInputCheck(15, "������� ����� �������� ���������: ");              //���� ������ �������� ���������
                    if (lastname != NULL) {
                        strcpy((info + i)->fullname.lastname, lastname);                //����������� ������ �������� � ������������� ������ ������� ��������
                        free(lastname);             //������������ ������ ��� ����������, ���������� �������� ���������
                        displayEditableMember(i);               //����� ���� ���������� �� ������������� ���������
                        printf("�������� ��������� ������� ��������!\n\n");
                        system("pause");
                    }
                    break;                  //����� �� switch
                }
                case 5: {
                    printf("��������� ������ ���������.\n");
                    country = stringInputCheck(15, "������� ����� ������ ���������: ");             //���� ����� ������ ���������
                    if (country != NULL) {
                        strcpy((info + i)->country, country);               //����������� ����� ������ � ������������� ������ ������� ��������
                        free(country);              //������������ ������ ��� ����������, ���������� ������ ���������
                        displayEditableMember(i);               //����� ���� ���������� �� ������������� ���������
                        printf("������ ��������� ������� ��������.\n\n");
                        system("pause");
                    }
                    break;              //����� �� switch
                }
                case 6: {
                    printf("��������� ���� �������� ���������.\n");
                    dateOfBirthInput(&day, &month, &year, "������� ����� ���� ��������(� ������� ��.��.����): ");
                    if (day != INT_MIN && month != INT_MIN && year != INT_MIN) {
                        (info + i)->dateOfBirth.day = day;
                        (info + i)->dateOfBirth.month = month;
                        (info + i)->dateOfBirth.year = year;
                        if ((info + i)->dateOfBirth.month >= aTm->tm_mon + 1)               //���� ����� ����� ������ �������� ������
                            (info + i)->dateOfBirth.age = 2018 - (info + i)->dateOfBirth.year;              //���������� ��������
                        else
                            (info + i)->dateOfBirth.age = 2019 - (info + i)->dateOfBirth.year;
                        displayEditableMember(i);               //����� ���� ���������� �� ������������� ���������
                        printf("���� �������� ��������� ������� ��������!\n\n");
                        system("pause");
                    }
                    break;              //����� �� switch
                }
                case 7: {
                    printf("��������� ������� ���������.\n");
                    category = categoryInput(10, "������� ����� ������ ���������: ");               //���� ������ ������� ���������
                    if (category != NULL) {
                        strcpy((info + i)->category, category);                 //����������� ������ ������� � ������������ ������ ������� ��������
                        free(category);                 //������������ ������ ��� ����������, ���������� ����� ������
                        displayEditableMember(i);               //����� ���� ���������� �� ������������� ���������
                        printf("������ ��������� ������� �������!\n\n");
                        system("pause");
                    }
                    break;              //����� �� switch
                }
                case 8: {
                    printf("��������� ������ ������� ���������.\n");
                    model = stringInputCheck(15, "������� ����� ������ ������� ���������: ");               //���� ����� ������ ������� ���������
                    if (model != NULL) {
                        strcpy((info + i)->model, model);               //����������� ����� ������ ������� ��������� � ������������� ������
                        free(model);                //������������ ������ ��� ����������, ���������� ����� ������ �������
                        displayEditableMember(i);               //����� ���� ���������� �� ������������� ���������
                        printf("������ ������� ��������� ������� ��������!\n\n");
                        system("pause");
                    }
                    break;              //����� �� switch
                }
                case 9: {
                    printf("��������� ���������� ����� ���������.\n");
                    do {
                        points = checkToEnterOnlyInt(4, "������� ����� ���������� ����� ���������: ");              //���� ������ ���������� ����� ���������
                        if (points == INT_MIN)
                            break;
                        if (points < 0 || points > 9999) {              //���� ��������� ���������� ����� ������ 0 � ������ 9999
                            printf("[������!]������� ����� �� 0 �� 9999!");
                            Sleep(1000);
                            printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);               //�������� ���� ��������� ����� � ������
                        }
                    } while (points < 0 || points > 9999);              //���� �� ����� ������� ����� ���� ��������� ������ -1 ��� ������ 10000
                    if (points != INT_MIN) {
                        (info + i)->points = points;
                        displayEditableMember(i);               //����� ���� ���������� �� ������������� ���������
                        printf("���������� ����� ��������� ������� ��������!\n\n");
                        system("pause");
                    }
                    break;              //����� �� switch
                }
                case 10: {
                    printf("��������� ������� ����� ���������.\n");
                    timeOfLapInput(&minutes, &seconds, "������� ����� ����� ����� ���������(� ������� ��:��): ");
                    if (minutes != INT_MIN && seconds != INT_MIN) {
                        (info + i)->timeOfLap.minutes = minutes;
                        (info + i)->timeOfLap.seconds = seconds;
                        displayEditableMember(i);               //����� ���� ���������� �� ������������� ���������
                        printf("����� ����� ��������� ������� ��������!\n\n");
                        system("pause");
                    }
                    break;              //����� �� switch
                }
                case 11: infoEditFlag = true; break;
                default: break;
            }
        }
        if (checkFile("info.dat")) {                //���� ���� ����������
            if ((file = fopen("info.dat", "wb"))) {             //���� ������� ����������� ����
                for (j = 0; j < infoLinesCounter; j++)              //������ ����� ������� �������� � ����
                    fwrite((info + j), sizeof(INFORMATION), 1, file);
                fclose(file);               //�������� �����
            }
            else printf("[������!]�������������� ����������: �� ������� ������������ ����! ���� �������!\n");               //���� �� ������� ����������� ����
        }
        else printf("[������!]�������������� ����������: �� ������� ����� ����!\n");                //���� ���� �� ����������
    }
}

void displayEditableMember(int i) {
    system("cls");
    printf("-------------------------------------------------------------------------------------------------------------------------------------------\n"
           "|�����|���             �������         ��������       |    ������     |����  ��������|�������|  ������  | ������ ������� |����|����� �����|\n"
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
    if (!info)              //���� ��������� �� ������ �������� ����� NULL
        printf("[������!]����� ����������: ���� ��� �� ������!\n\n");
    else if (infoLinesCounter == 0)             //���� ��� �� ������ ���������
        printf("[������!]����� ����������: ���� ����!\n\n");
    else {
        printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("|�����|���             �������         ��������       |    ������     |����  ��������|�������|  ������  | ������ ������� |����|����� �����|\n");
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


//�� ��� ������� � ����������� � �������
void pointsFilter() {
    int points = 0;
    bool isAtLeastOneMember = false;
    if (!info)              //���� ��������� �� ������ �������� ����� NULL
        printf("[������!]����� � ����������: ���� �� ������!\n\n");
    else if (infoLinesCounter == 0)             //���� ��� �� ������ ���������
        printf("[������!]����� � ����������: ���� ����!\n\n");
    else {
        do {
            points = checkToEnterOnlyInt(4, "������� ���������� �����: ");              //���� ���������� ����� ��� �������
            if (points == INT_MIN)
                return;
            if (points < 0 || points > 9999) {              //���� ��������� ���������� ����� ������ 0 ��� ������ 9999
                printf("[������!]������� ����� ������ 0 � ������ 9999!");
                Sleep(1000);
                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);               //�������� ���� ��������� ����� � ������
            }
        } while (points < 0 || points > 9999);              //���� �� ����� ������� ���������� ����� ������ -1 ��� ������ 10000
        system("cls");              //������� ������
        printf("���������, � ������� ����� ������ %i: ", points);
        for (int i = 0; i < infoLinesCounter; i++) {                //����� ���������� � ����������� ����� ������ ����������
            if ((info + i)->points > points) {              //���� � i-�� ��������� ���������� ����� ������ ����������
                if (!isAtLeastOneMember) {              //���� ������ ���� �� ���� ����� ��������
                    printf("\n-------------------------------------------------------------------------------------------------------------------------------------------\n");
                    printf("|�����|���             �������         ��������       |    ������     |����  ��������|�������|  ������  | ������ ������� |����|����� �����|\n");
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
            if (isAtLeastOneMember && i == infoLinesCounter - 1)                //���� ������ ���� �� ���� ����� �������� � ������ �������� ��������
                printf("-------------------------------------------------------------------------------------------------------------------------------------------\n\n");
        }
        if (!isAtLeastOneMember)                //���� ����� ���������� �� �������
            printf("��� �� ������ ��������� � ������ ������ %i.\n\n", points);
    }
    system("pause");
}

void timeOfLapFilter() {
    int minutesOfLap = 0, secondsOfLap = 0;
    bool isAtLeastOneMember = false;
    if (!info)                //���� ��������� �� ������ �������� ����� NULL
        printf("[������!]����� � ����������: ���� �� ������!\n\n");
    else if (infoLinesCounter == 0)             //���� ��� �� ������ ���������
        printf("[������!]����� � ����������: ���� ����!\n\n");
    else {
        timeOfLapInput(&minutesOfLap, &secondsOfLap, "������� ����� �����(� ������� ��:��): ");
        if (minutesOfLap == INT_MIN && secondsOfLap == INT_MIN)
            return;
        system("cls");              //������� ������
        printf("���������, � ������� ����� ����� ������ %02i:%02i: ", minutesOfLap, secondsOfLap);
        for (int i = 0; i < infoLinesCounter; i++) {                //����� ����������, � ������� ����� ����� ������ ����������
            if ((info + i)->timeOfLap.minutes < minutesOfLap)               //���� � i-�� ��������� ������ ����� ������ ���������
                if ((info + i)->timeOfLap.seconds < ((info + i)->timeOfLap.minutes == minutesOfLap ? secondsOfLap : 60)) {              //���� ��������� ������ ����� ������� i-�� ��������� �� ������� ������������ � ����������
                    if (!isAtLeastOneMember) {              //���� ������ ���� �� ���� ��������
                        printf("\n-------------------------------------------------------------------------------------------------------------------------------------------\n");
                        printf("|�����|���             �������         ��������       |    ������     |����  ��������|�������|  ������  | ������ ������� |����|����� �����|\n");
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
            if (isAtLeastOneMember && i == infoLinesCounter - 1)                //���� ������ ������ ���� �������� � ������ ��������� ��������
                printf("-------------------------------------------------------------------------------------------------------------------------------------------\n\n");
        }
        if (!isAtLeastOneMember)                //���� �� ������� �� ���� ���������
            printf("��� �� ������ ��������� � �������� ����� ������ %02i:%02i.\n\n", minutesOfLap, secondsOfLap);
    }
    system("pause");
}

void ageFilter() {
    int age = 0;
    bool isAtLeastOneMember = false;
    if (!info)              //���� ��������� �� ������ �������� ����� NULL
        printf("[������!]����� � ����������: ���� �� ������!\n\n");
    else if (infoLinesCounter == 0)             //���� ��� �� ������ ���������
        printf("[������!]����� � ����������: ���� ����!\n\n");
    else {
        do {
            age = checkToEnterOnlyInt(3, "������� �������: ");              //���� �������� ��� ������
            if (age == INT_MIN)
                return;
            if (age < 0 || age > 119) {             //���� ��������� ������� ������ 0 ��� ������ 119
                printf("[������!]������� ����� ������ 0 � ������ 119!");
                Sleep(1000);
                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);               //�������� ���� ��������� ����� � ������
            }
        } while (age < 0 || age > 119);             //���� �� ����� ������ ������� ������ -1 ��� ������ 119
        system("cls");              //������� ������
        printf("���������, ������� ������� ������ %i: ", age);
        for (int i = 0; i < infoLinesCounter; i++) {                //����� ����������
            if ((info + i)->dateOfBirth.age > age) {                //���� ������� i-�� ��������� ������ ����������
                if (!isAtLeastOneMember) {              //���� ������ ���� �� ���� ��������
                    printf("\n-------------------------------------------------------------------------------------------------------------------------------------------\n");
                    printf("|�����|���             �������         ��������       |    ������     |����  ��������|�������|  ������  | ������ ������� |����|����� �����|\n");
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
            if (isAtLeastOneMember && i == infoLinesCounter - 1)                //���� ������ ���� �� ���� �������� � ������ ��������� ��������
                printf("-------------------------------------------------------------------------------------------------------------------------------------------\n\n");
        }
        if (!isAtLeastOneMember)                //���� �� ������ �� ���� �������
            printf("��� �� ������ ��������� � ������ ������ %i.\n\n", age);
    }
    system("pause");
}

void yearOfBirthFilter() {
    int yearOfBirth = 0;
    bool isAtLeastOneMember = false;
    if (!info)              //���� ��������� �� ������ �������� ����� NULL
        printf("[������!]����� � ����������: ���� �� ������!\n\n");
    else if (infoLinesCounter == 0)             //���� ��� �� ������ ���������
        printf("[������!]����� � ����������: ���� ����!\n\n");
    else {
        do {
            yearOfBirth = checkToEnterOnlyInt(4, "������� ��� ��������: ");             //���� ���� �������� ��� ����������
            if (yearOfBirth == INT_MIN)
                return;
            if (yearOfBirth < 1900 || yearOfBirth > 2019) {             //���� ��������� ��� �������� ������ 1900 ��� ������ 2019
                printf("[������!]������� ����� ������ 1900 � ������ 2019!");
                Sleep(1000);
                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);               //�������� ���� ��������� ����� � ������
            }
        } while (yearOfBirth < 1900 || yearOfBirth > 2019);             //���� �� ����� ������ ��� �������� ������ 1899 ��� ������ 2020
        system("cls");              //������� ������
        printf("���������, ��� �������� � ������� ������ %i: ", yearOfBirth);
        for (int i = 0; i < infoLinesCounter; i++) {                //����� ����������
            if ((info + i)->dateOfBirth.year > yearOfBirth) {               //���� � i-�� ��������� ������� ������ ����������
                if (!isAtLeastOneMember) {              //���� ������ ���� �� ���� ��������
                    printf("\n-------------------------------------------------------------------------------------------------------------------------------------------\n");
                    printf("|�����|���             �������         ��������       |    ������     |����  ��������|�������|  ������  | ������ ������� |����|����� �����|\n");
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
            if (isAtLeastOneMember && i == infoLinesCounter - 1) {              //���� ������ ������ ���� �������� � ������ �������� ��������
                printf("-------------------------------------------------------------------------------------------------------------------------------------------\n\n");
            }
        }
        if (!isAtLeastOneMember)                //���� �� ������ ��������� �� �������
            printf("��� �� ������ ��������� � ����� �������� ������ %i.\n\n", yearOfBirth);
    }
    system("pause");
}

void timeOfLapSorting() {
    FILE* file = NULL;
    INFORMATION tmp;
    if (!info)              //���� ��������� �� ������ �������� ����� NULL
        printf("[������!]����������: ���� �� ������!\n\n");
    else if (infoLinesCounter == 0)             //���� ��� �� ������ ���������
        printf("[������!]����������: ���� ����!\n\n");
    else {
        if ((file = fopen("info.dat", "wb"))) {             //���� ������� ������� ���� ��� ����������
            for (int i = 1; i < infoLinesCounter; i++)              //���������� ���������
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
            for (int j = 0; j < infoLinesCounter; j++)              //������ ����� ������� �������� � ����
                fwrite((info + j), sizeof(INFORMATION), 1, file);
            fclose(file);               //�������� �����
            printf("����������: ��������� ������� �������������!\n\n");
        }               //���� �� ������� ������� ���� ��� ����������
        else printf("[������!]����������: �� ������� ������� ����! ���� �������!\n\n");
    }
    system("pause");
}

void numberSearch() {
    int number = 0;
    bool isFounded = false;
    if (!info)              //���� ��������� �� ������ �������� ����� NULL
        printf("[������!]����� � ����������: ���� �� ������!\n\n");
    else if (infoLinesCounter == 0)             //���� ��� �� ������ ���������
        printf("[������!]����� � ����������: ���� ����!\n\n");
    else {
        do {
            number = checkToEnterOnlyInt(3, "������� �����: ");             //���� ������ ��� ������
            if (number == INT_MIN)
                return;
            if (number < 0) {               //���� ��������� ����� ������ 0
                printf("[������!]������� ����� ������ 0!\n");
                Sleep(1000);
                printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);               //�������� ���� ��������� �����
            }
        } while (number < 0);               //���� �� ����� ������ ����� ������ -1
        system("cls");              //������� ������
        printf("��������, ����� �������� %i: ", number);
        for (int i = 0; i < infoLinesCounter; i++) {                //����� ����������
            if ((info + i)->number == number) {             //���� ����� i-�� ��������� ����� ����������
                printf("\n-------------------------------------------------------------------------------------------------------------------------------------------\n");
                printf("|�����|���             �������         ��������       |    ������     |����  ��������|�������|  ������  | ������ ������� |����|����� �����|\n");
                printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");
                printf("|%-3i  |%-15s %-15s %-15s|%-15s|  %02i/%02i/%-4i  |  %-3i  |%-10s|%-16s|%-4i|   %02i:%02i   |\n",
                       (info + i)->number, (info + i)->fullname.firstname, (info + i)->fullname.surname,
                       (info + i)->fullname.lastname, (info + i)->country, (info + i)->dateOfBirth.day,
                       (info + i)->dateOfBirth.month, (info + i)->dateOfBirth.year, (info + i)->dateOfBirth.age,
                       (info + i)->category, (info + i)->model, (info + i)->points, (info + i)->timeOfLap.minutes,
                       (info + i)->timeOfLap.seconds);
                printf("-------------------------------------------------------------------------------------------------------------------------------------------\n\n");
                isFounded = true;
                break;              //����� �� �����
            }
        }
        if (!isFounded)             //���� ����� �������� �� ������
            printf("�������� � ������� %i �� ������.\n\n", number);
    }
    system("pause");
}

void surnameSearch() {
    bool isAtLeastOneMember = false;
    char *surname = NULL;
    if (!info)              //���� ��������� �� ������ �������� ����� NULL
        printf("[������!]����� � ����������: ���� �� ������!\n\n");
    else if (infoLinesCounter == 0)             //���� ��� �� ������ ���������
        printf("[������!]����� � ����������: ���� ����!\n\n");
    else {
        surname = stringInputCheck(15, "������� �������: ");                //���� ������� ��� ������
        if (surname == NULL)
            return;
        system("cls");              //������� ������
        printf("���������, � �������� %s: ", surname);
        for (int i = 0; i < infoLinesCounter; i++) {                //����� ����������
            if (strcmp((info + i)->fullname.surname, surname) == 0) {               //���� ������� i-�� ��������� ����� �� ��� ���������
                if (!isAtLeastOneMember) {              //���� ������ ���� �� ���� ��������
                    printf("\n-------------------------------------------------------------------------------------------------------------------------------------------\n");
                    printf("|�����|���             �������         ��������       |    ������     |����  ��������|�������|  ������  | ������ ������� |����|����� �����|\n");
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
            if (isAtLeastOneMember && i == infoLinesCounter - 1)                //���� ���� �� ���� �������� ������ � ������ ��������� ��������
                printf("-------------------------------------------------------------------------------------------------------------------------------------------\n\n");
        }
        if (!isAtLeastOneMember)                //���� �� ���� �������� �� ������
            printf("��� �� ������ ��������� � �������� %s.\n\n", surname);
    }
    system("pause");
}

void countrySearch() {
    bool isAtLeastOneMember = false;
    char *country = NULL;
    if (!info)              //���� ��������� �� ������ �������� ����� NULL
        printf("[������!]����� � ����������: ���� �� ������!\n\n");
    else if (infoLinesCounter == 0)             //���� ��� �� ������ ���������
        printf("[������!]����� � ����������: ���� ����!\n\n");
    else {
        country = stringInputCheck(15, "������� ������: ");             //���� ������
        if (country == NULL)
            return;
        system("cls");              //������� ������
        printf("���������, �� ������ %s: ", country);
        for (int i = 0; i < infoLinesCounter; i++) {                //����� ����������
            if (strcmp((info + i)->country, country) == 0) {                //���� ������ i-�� ��������� ��������� � ���������
                if (!isAtLeastOneMember) {              //���� ���� �� ���� �������� ������
                    printf("\n-------------------------------------------------------------------------------------------------------------------------------------------\n");
                    printf("|�����|���             �������         ��������       |    ������     |����  ��������|�������|  ������  | ������ ������� |����|����� �����|\n");
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
            if (isAtLeastOneMember && i == infoLinesCounter - 1)                //���� ���� �� ���� �������� ������ � ������ ��������� ��������
                printf("-------------------------------------------------------------------------------------------------------------------------------------------\n\n");
        }
        if (!isAtLeastOneMember)                //���� ���� �� ���� �������� ������
            printf("��� �� ������ ��������� �� ������ %s.\n\n", country);
    }
    system("pause");
}

void categorySearch() {
    bool isAtLeastOneMember = false;
    char *category = NULL;
    if (!info)              //���� ��������� �� ������ �������� ����� NULL
        printf("[������!]����� � ����������: ���� �� ������!\n\n");
    else if (infoLinesCounter == 0)             //���� ��� �� ������ ���������
        printf("[������!]����� � ����������: ���� ����!\n\n");
    else {
        category = categoryInput(10, "������� ������: ");               //���� �������
        if (category == NULL)
            return;
        system("cls");              //������� ������
        printf("���������, � �������� %s: ", category);
        for (int i = 0; i < infoLinesCounter; i++) {                //����� ����������
            if (strcmp((info + i)->category, category) == 0) {              //���� ������ i-�� ��������� ��������� � ���������
                if (!isAtLeastOneMember) {              //���� ���� �� ���� �������� ������
                    printf("\n-------------------------------------------------------------------------------------------------------------------------------------------\n");
                    printf("|�����|���             �������         ��������       |    ������     |����  ��������|�������|  ������  | ������ ������� |����|����� �����|\n");
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
            if (isAtLeastOneMember && i == infoLinesCounter - 1)                //���� ���� �� ���� �������� ������ � ������ �������� ��������
                printf("-------------------------------------------------------------------------------------------------------------------------------------------\n\n");
        }
        if (!isAtLeastOneMember)                //���� �� ������ �� ���� ��������
            printf("��� �� ������ ��������� � �������� %s.\n\n", category);
    }
    system("pause");
}

void displayTopMembers() {
    INFORMATION *infoCopy = NULL, tmp;
    system("cls");
    if (!info)              //���� ��������� �� ������ �������� ����� NULL
        printf("[������!]����� ���-3 ����������: ���� �� ������!\n\n");
    else if (infoLinesCounter == 0)             //���� ��� �� ������ ���������
        printf("[������!]����� ���-3 ����������: ���� ����!\n\n");
    else {
        infoCopy = (INFORMATION*)realloc(NULL, sizeof(INFORMATION)*infoLinesCounter);               //��������� ������ ��� ����� �������
        memcpy(infoCopy, info, sizeof(INFORMATION)*infoLinesCounter);               //����������� ���������� � ����� �������
        if (infoLinesCounter != 1) {                //���� ���������� ������ ������, �� ������������� ����� �������
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
        printf("|�����|���             �������         ��������       |    ������     |����  ��������|�������|  ������  | ������ ������� |����|����� �����|\n");
        printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");
        for (int i = 0; i < infoLinesCounter && i < 3; i++) {               //����� ������ ���� ����������
            printf("|%-3i  |%-15s %-15s %-15s|%-15s|  %02i/%02i/%-4i  |  %-3i  |%-10s|%-16s|%-4i|   %02i:%02i   |\n",
                   (infoCopy + i)->number, (infoCopy + i)->fullname.firstname, (infoCopy + i)->fullname.surname,
                   (infoCopy + i)->fullname.lastname, (infoCopy + i)->country, (infoCopy + i)->dateOfBirth.day,
                   (infoCopy + i)->dateOfBirth.month, (infoCopy + i)->dateOfBirth.year, (infoCopy + i)->dateOfBirth.age,
                   (infoCopy + i)->category, (infoCopy + i)->model, (infoCopy + i)->points, (infoCopy + i)->timeOfLap.minutes,
                   (infoCopy + i)->timeOfLap.seconds);
        }
        printf("-------------------------------------------------------------------------------------------------------------------------------------------\n\n");
    }
    system("pause");
}