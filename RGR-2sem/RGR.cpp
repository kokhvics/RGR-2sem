#include <iostream>
#include <Windows.h>
#include <cmath>
#include <stdio.h>
#include <conio.h>
#include <string>

#define UP 72
#define DOWN 80
#define ESC 27
#define ENTER 13

using namespace std;
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
HPEN CreatePen(int fnPenStyle, int nWidth, COLORREF crColor);
double e = 2.71828182845904523536;
double Pi = 3.1415926535;

void gotoxy(short x, short y)
{
    COORD Coor{ x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Coor);
}

//задание 1 - табличка
void number_one() {
    

    int a = 1, b = 2, n = 18;
    float x;
    double minF1 = INT_MAX, maxF1 = INT_MIN, minF2 = INT_MAX, maxF2 = INT_MIN;
    float F1[18], F2[18], x_c[18];
    float dx = (fabs(b - a)) / (n - 1);
    x = x_c[0] = a;
    int x_pos = 24, y_pos = 3;
    SetConsoleTextAttribute(hStdOut, 9);
    gotoxy(x_pos, y_pos);
    printf(" __________________________________\n");
    gotoxy(x_pos, y_pos+1);
    printf(" | I |    X    |   F1    |   F2   |\n");
    gotoxy(x_pos, y_pos+2);
    printf(" |___|_________|_________|________|\n");

    for (int i = 0; i < n; i++) {
        F1[i] = ((pow(2, 2 * x)) * log10(x)) - (pow(3, 3 * x));
        F2[i] = 10 / (2 + (pow(x, 2)));
        x_c[i] = x;
        x += dx;
    }

    for (int i = 0; i < n; i++) {
        minF1 = min(F1[i], minF1);
        maxF1 = max(F1[i], maxF1);
        if (F2[i] != -INFINITY) {
            minF2 = min(F2[i], minF2);
        }
        maxF2 = max(F2[i], maxF2);
    }

    for (int i = 1; i <= n; i++) {

        gotoxy(x_pos+1, y_pos + 2 + i);
        SetConsoleTextAttribute(hStdOut, 9);
        printf("|%3d|%8.3f |", i, x_c[i - 1]); //это номер и приращение
        if (F1[i - 1] == minF1) {
            SetConsoleTextAttribute(hStdOut, 14); //минимум 1 ф-и
            printf("%8.4f", F1[i - 1]);
        }
        else if (F1[i - 1] == maxF1) {
            SetConsoleTextAttribute(hStdOut, 15);
            printf("%8.4f", F1[i - 1]);
        }
        else
        {
            SetConsoleTextAttribute(hStdOut, 5);
            printf("%8.4f", F1[i - 1]);
        }

        SetConsoleTextAttribute(hStdOut, 9);
        if (F1[i - 1] > -100) printf(" |");
        else printf("|");
        if (F2[i - 1] == minF2) {
            SetConsoleTextAttribute(hStdOut, 14);
            printf("%8.4f", F2[i - 1]);
        }
        else if (F2[i - 1] == maxF2) {
            SetConsoleTextAttribute(hStdOut, 15);
            printf("%8.4f", F2[i - 1]);
        }
        else
        {
            if (F2[i - 1] == -INFINITY) {
                SetConsoleTextAttribute(hStdOut, 5);
                printf("%8s", "ERROR");
            }
            else {
                SetConsoleTextAttribute(hStdOut, 5);
                printf("%8.4f", F2[i - 1]);
            }
        }
        SetConsoleTextAttribute(hStdOut, 9);
        printf("|\n");
    }

    SetConsoleTextAttribute(hStdOut, 9);
    gotoxy(x_pos+1, y_pos + 3 + n);
    printf("|___|_________|_________|________|\n");



}


//уравнение
double function_equation(double x) {
    return tan(x) - pow(e, x + 1);
}

//Метод половинного деления
double half_div_equation(double a, double b, double e) {
    double c;
    do {
        c = (a + b) / 2;
        if (function_equation(c) * function_equation(a) < 0)  b = c;
        else if (c == 0) return 0;
        else a = c;
    } while (fabs(a - b) >= e);
    return c;
}


//задание 2 - решение уравнения методом половинного деления
void number_two() {
    SetConsoleTextAttribute(hStdOut, 15);
    system("cls");
    
    gotoxy(20, 1);
    cout << "Решение уравнения";
    gotoxy(20, 3);
    cout << "Уравнение: tg(x) - e^(x+1)";
    gotoxy(20, 4);
    cout << "Предлогаемое решение: метод половинного деления";
    gotoxy(20, 5);
    cout << "Интервал решения уравнения: [1,Пи/2]";
    gotoxy(20, 6);
    cout << "Результат: корень уравнения равен " << half_div_equation(1, Pi / 2, 0.001);
}

//интеграл
double function_integral(double x) {
    return (1 / (x + sqrt(abs(cos(x)))));
}

//через трапеции
double trapezoidal_integral(double a, double b, int n) {
    const double width = (b - a) / n;
    double trapezoidal_integral = 0;
    for (int i = 0; i < n; i++) {
        const double x1 = a + i * width;
        const double x2 = a + (i + 1) * width;

        trapezoidal_integral += 0.5 * (x2 - x1) * (function_integral(x1) + function_integral(x2));
    }
    return trapezoidal_integral;
}

//через прямоугольники
double rectangel_integral(double a, double b, double n) {
    double h = (b - a) / n;
    double sum = function_integral(a) + function_integral(b);
    int k;
    for (int i = 1; i <= n - 1; i++) {
        k = 2 + 2 * (i % 2);
        sum += k * function_integral(a + i * h);
    }
    sum *= h / 3;
    return sum;
}


//задание 3 - решение интеграла
void number_three() {
    
    system("cls");
    SetConsoleTextAttribute(hStdOut, 15);
    gotoxy(20, 1);
    cout << "Решение определенного интеграла";
    gotoxy(20, 3);
    cout << "Предложенный интеграл: 1/(x+sqrt(x))";
    gotoxy(20, 4);
    cout << "Верхний предел интеграла: 5.0";
    gotoxy(20, 5);
    cout << "Нижний предел интеграла: 2.0";
    gotoxy(20, 6);
    cout << "Цена приращения: 3/50";
    gotoxy(20, 7);
    cout << "Точность определения: 0.001";
    gotoxy(20, 9);
    cout << "Результат, полученный методом трапеций равен: " << trapezoidal_integral(2.0, 5.0, 50);
    gotoxy(20, 11);
    cout << "Результат, полученный методом прямоугольников равен: " << rectangel_integral(2.0, 5.0, 50);
}


//Графики

void grid()
{
    HWND hwn = GetConsoleWindow();
    COLORREF lineColor = RGB(0, 0, 0);
    HDC hdc = GetDC(hwn);
    const int d = 350, k = 50, x0 = 50, y0 = 500, c = 50; 
    SelectObject(hdc, CreatePen(0, 1, RGB(255, 255, 255)));
    MoveToEx(hdc, 0, d, NULL);
    LineTo(hdc, c * k, d);
    MoveToEx(hdc, c, 0, NULL);
    LineTo(hdc, c, 3 * d);
    for (int i = 0; i < 30; i++) {
        MoveToEx(hdc, x0 - 10, y0 - k * i, NULL);
        LineTo(hdc, x0 + 10, y0 - k * i);
        MoveToEx(hdc, x0 - 10, y0 + k * i, NULL);
        LineTo(hdc, x0 + 10, y0 + k * i);
        MoveToEx(hdc, x0 + k * i, y0 - 10, NULL);
        LineTo(hdc, x0 + k * i, y0 + 10);
        MoveToEx(hdc, x0 - k * i, y0 - 10, NULL);
        LineTo(hdc, x0 - k * i, y0 + 10);
        string s = to_string(i);
        LPCWSTR w;
        wstring ste = wstring(s.begin(), s.end());
        w = ste.c_str();
        if (i < 10) { 
            TextOut(hdc, x0 - 10, y0 - k * i, w, 1);
            TextOut(hdc, x0 + k * i, y0 + 10, w, 1);
        }
        else {
            TextOut(hdc, x0 - 10, y0 - k * i, w, 2);
            TextOut(hdc, x0 + k * i, y0 + 10, w, 2);
        }
        LPCWSTR w1 = L"(2^2x * log10(x)) - 3^3x";
        LPCWSTR w2 = L"10 / 2 + (pow(x, 2))";
        //TextOut(hdc, 300, 350, w1, 24);
        TextOut(hdc, 100, 150, w2, 19); 
    }
}

void grafic() {
     system("mode con cols=160 lines=40");
    system("color 2");
    HWND hwn = GetConsoleWindow();
    COLORREF lineColor = RGB(0, 0, 0);
    HDC hdc = GetDC(hwn);
    const int d = 350, k = 50, x0 = 50, y0 = 500, c = 50; // d = 350 - good. Grafic is upper because that better looking functions

    int n = 100;
    double F1[100], F2[100], x1[100], x, dx, a = 1, b = 2, minF1 = 20000, maxF1 = -20000, minF2 = 20000, maxF2 = -20000;
    dx = fabs(b - a) / (n - 1);//Increment of function, a,b - function interval
    x = a;
    //drawing both funtion
    grid();
    grid();
    grid();
    for (int i = 0; i < n; i++) {
        F1[i] = ((pow(2, 2 * x)) * log10(x)) - (pow(3, 3 * x)); //Function of Grafic #1
        F2[i] = 10 / (2 + (pow(x, 2)));//Function of Grafic #2
        x1[i] = x;
        x += dx;
    }
    grid();
    grid();
    grid();
    for (int i = 0; i < n; i++) {
        SetPixel(hdc, c + k * x1[i], d - k * F2[i], RGB(255, 222, 173));
        MoveToEx(hdc, c + k * x1[i], d - k * F2[i], NULL);
        SetPixel(hdc, c + k * x1[i], d - k * F1[i], RGB(240, 248, 255));
        MoveToEx(hdc, c + k * x1[i], d - k * F1[i], NULL);
    }
    grid();
    grid();
    grid();
}



void Circle(HWND hW, int xCenter, int yCenter, int radius, COLORREF borderColor, COLORREF fillColor)
{
    HDC hDC = GetDC(hW);
    HPEN hPen = CreatePen(PS_SOLID, 1, borderColor);
    HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);
    HBRUSH hBrush = CreateSolidBrush(fillColor);
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

    Ellipse(hDC, xCenter - radius, yCenter - radius, xCenter + radius, yCenter + radius);

    SelectObject(hDC, hOldPen);
    DeleteObject(hPen);
    SelectObject(hDC, hOldBrush);
    DeleteObject(hBrush);
    ReleaseDC(hW, hDC);
}

void dot(HWND hW, int xCenter, int yCenter, int radius, COLORREF borderColor, COLORREF fillColor)
{
    HDC hDC = GetDC(hW);
    HPEN hPen = CreatePen(PS_SOLID, 1, borderColor);
    HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);
    HBRUSH hBrush = CreateSolidBrush(fillColor);
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

    Ellipse(hDC, xCenter - radius, yCenter - radius, xCenter + radius, yCenter + radius);

    SelectObject(hDC, hOldPen);
    DeleteObject(hPen);
    SelectObject(hDC, hOldBrush);
    DeleteObject(hBrush);
    ReleaseDC(hW, hDC);
}

void Picture(HWND hW, int dx, int dy, int mode)
{
    COLORREF border = RGB(255, 255, 0), fill = RGB(255, 255, 0), line = RGB(255, 255, 0), black = RGB(0, 0, 0), white = RGB(255, 255, 255);
    if (!mode)
        border = fill = line = black;
    int x0 = 50, y0 = 100, r = 10;

    Circle(hW, x0 + dx, y0 + dy, r, border, fill);

    if (dx%3==0)
        dot(hW, x0 + 40 + dx, y0 + dy, r / 5, white, white);
    
}


void Animation()
{
    system("mode con cols=75 lines=10");
    HWND hW = GetConsoleWindow();
    int step = -1;
    Sleep(1000);
    for (;; ++step)
    {
        
        if (_kbhit())
        {
            if (GetAsyncKeyState(VK_ESCAPE))
            {
                break;
                //menu.draw(menu.Num);
            }
        }
        Picture(hW, 5 * step, 0, 1);
        Sleep(100);
        Picture(hW, 5 * step, 0, 0);
        if (step > 100)
        {

            system("cls");
            step = 1;
        }
    }
    system("pause");
}

int menu()
{
    string Menu[] = { "Решение функций (Таблица)", "Решение функций (График)", "Решение уравнения", "Решение интеграла", "Анимация", "Об авторе", "Выход" };
    int active_menu = 0;

    char ch;
    while (true)
    {
        int x = 40, y = 11; //Задаем координаты начала
        gotoxy(x, y); //Ловим курсор
        for (int i = 0; i < size(Menu); i++) //Выводим меню на экран
        {
            if (i == active_menu) SetConsoleTextAttribute(hStdOut, 15 | FOREGROUND_INTENSITY); //Меняем цвет текста в консоли
            else SetConsoleTextAttribute(hStdOut, 13);
            /*
            if (i == active_menu) SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY); //Меняем цвет текста в консоли
            else SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
            */
            gotoxy(x, y++); //Сдвигаем вниз координату начала
            cout << Menu[i] << endl;
        }

        ch = _getch();
        if (ch == -32) ch = _getch(); // Отлавливаем стрелочки
        switch (ch)
        {
        case ESC:
            exit(0);
        case UP:
            if (active_menu > 0)
                active_menu--;
            break;
        case DOWN:
            if (active_menu < size(Menu) - 1)
                active_menu++;
            break;
        case ENTER:
            switch (active_menu)
            {
            case 0:
                system("CLS");
                SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                //cout << "Пользователь выбрал \"" << Menu[active_menu] << "\"" << endl;
                if (active_menu == 0)
                {
                    number_one();
                }
                _getch();
                system("CLS");
                break;
            case 1:
                system("CLS");
                SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                if (active_menu == 1)
                {
                    grafic();
                }
                _getch();
                system("CLS");
                break;
            case 2:
                system("CLS");
                SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                //cout << "Пользователь выбрал \"" << Menu[active_menu] << "\"" << endl;
                if (active_menu == 2)
                {
                    number_two();
                }
                _getch();
                system("CLS");
                break;
            case 3:
                system("CLS");
                SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                //cout << "Пользователь выбрал \"" << Menu[active_menu] << "\"" << endl;
                if (active_menu == 3)
                {
                   number_three();
                }
                _getch();
                system("CLS");
                break;
            case 4:
                system("CLS");
                Animation();
                _getch();
                system("CLS");
                break;
            case 5:
                system("CLS");
                SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                //cout << "Пользователь выбрал \"" << Menu[active_menu] << "\"" << endl;
                if (active_menu == 5)
                {
                    int x = 20, y = 11; //Задаем координаты начала
                    gotoxy(x, y);
                    SetConsoleTextAttribute(hStdOut, 13);
                    cout << "Тип работы: расчетно-графическая работа" << endl;
                    gotoxy(x, y + 1);
                    cout << "Дисциплина: программирование" << endl;
                    gotoxy(x, y + 2);
                    cout << "Выполнила работу: " << "Кох Виктория Максимовна, " << "студентка группы ПИН-222 " << endl;
                    gotoxy(x, y + 3);
                    cout << "Год выполнения: 2023";
                }
                _getch();
                system("CLS");
                break;
            case 6:
                exit(0);
            }
            break;
        default:
            cout << "Код " << (int)ch << " " << endl; //Проверяем какой код у кнопки
        }
    }
    return 0;
}



int main() {
    setlocale(LC_ALL, "rus");
   
    menu();

    system("pause > nul");
    return 0;
}

HPEN CreatePen(int fnPenStyle, int nWidth, COLORREF crColor)
{
    return HPEN();
}
