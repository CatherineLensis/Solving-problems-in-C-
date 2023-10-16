#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <time.h>
using namespace std;
using namespace sf;

double f(double x)
{
    return exp(-1 * fabs(x)) * pow(x, 2);
}

double* Gauss(double** A, double* B, int n)
{
    double* C{ new double[n] {} }, max; //возвращаемый дин. массив коэф. полинома
    int k = 0, index;
    const double e = 1e-5;  // точность
    while (k < n)
    {
        // Поиск строки с максимальным A[i][k]
        max = abs(A[k][k]);
        index = k;
        for (int i = k + 1; i < n; i++)
        {
            if (abs(A[i][k]) > max)
            {
                max = abs(A[i][k]);
                index = i;
            }
        }
        // Перестановка строк
        if (max < e)
        {
            // нет ненулевых диагональных элементов
            cout << "Решение получить невозможно из-за нулевого столбца "
                << index << " матрицы A" << endl;
            return 0;
        }
        for (int j = 0; j < n; j++)
        {
            double temp = A[k][j];
            A[k][j] = A[index][j];
            A[index][j] = temp;
        }
        double temp = B[k];
        B[k] = B[index];
        B[index] = temp;
        // Нормализация уравнений
        for (int i = k; i < n; i++)
        {
            double temp = A[i][k];
            if (abs(temp) < e) continue; // для нулевого коэффициента пропустить
            for (int j = 0; j < n; j++)
                A[i][j] = A[i][j] / temp;
            B[i] = B[i] / temp;
            if (i == k)  continue; // уравнение не вычитать само из себя
            for (int j = 0; j < n; j++)
                A[i][j] = A[i][j] - A[k][j];
            B[i] = B[i] - B[k];
        }
        k++;
    }
    // обратная подстановка
    for (k = n - 1; k >= 0; k--)
    {
        C[k] = B[k];
        for (int i = 0; i < k; i++)
            B[i] = B[i] - A[i][k] * C[k];
    }
    return C;
}

double Y(double* C, double x, int n)
{
    double Y = 0;
    for (int i = 0; i < n; i++)
    {
        Y += C[i] * pow(x, i);
    }
    return Y;
}

void Graphics(double* X, double* F, int m, double* C, int n)
{
    const int W = 1046;//длина окна
    const int H = 546;//высота окна
    int x0 = W / 2;//центр по Х
    int y0 = H / 2;//центр по Y
    int sc = 478;//масштаб графиков
    int anim = 0;//параметр анимации

    RenderWindow window(VideoMode(W, H), "Graphics");//рендер окна

    //цвет точек Fi Xi
    CircleShape point(6.f);
    point.setFillColor(Color::Blue);
    //цвет графика f(x)
    CircleShape gr1(2.f);
    gr1.setFillColor(Color::Green);
    //цвет графика Y(x)
    CircleShape gr2(2.f);
    gr2.setFillColor(Color::Red);

    //текстура координатных осей
    Texture t;
    t.loadFromFile("C:/Users/Кутенок/Desktop/С++/№5 Вар 19/Oxy.png");
    Sprite pic(t);

    //параметры для отрисовки графиков
    int o1 = -2; int o2 = 2; //отрезок, в котором будут отрисованы графики по х
    double c = 700;//точность графиков
    int mas = ((o1) * (-1) + o2) * c + 1;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        if (anim < mas) anim += 20; //скорость анимации

        window.clear(Color::White);//очистка окна

        window.draw(pic);//отрисовка координатных осей

        //отрисовка функции f()
        for (int i = 0; i < anim; i++)
        {
            double x = o1 + (i / c);
            double y = f(x);
            double x1 = x0 + x * sc;
            double y1 = y0 - y * sc;
            gr1.setPosition(x1, y1);
            window.draw(gr1);
        }

        //отрисовка полинома Y(x)
        for (int i = 0; i < anim; i++)
        {
            double x = o1 + (i / c);
            double y = Y(C, x, n);
            double x1 = x0 + x * sc;
            double y1 = y0 - y * sc;
            gr2.setPosition(x1, y1);
            window.draw(gr2);
        }

        //отрисовка точек Xi Fi
        for (int i = 0; i < m; i++)
        {
            double x1 = x0 + X[i] * sc;
            double y1 = y0 - F[i] * sc;
            point.setPosition(x1, y1);
            window.draw(point);
        }
        window.display();
    }
}

int main()
{
    setlocale(LC_ALL, "ru");
    srand(time(NULL));

    double a = -2; double b = 2;//граница
    int n, m;//n-степень полинома; m-количество точек
    cout << "Введите степень полинома и кол-во точек разбиения " << endl;
    cin >> n >> m;
    cout << endl;

    double* X{ new double[m] }; double* F{ new double[m] };//дин. массивы точек xi и yi
    int c = 1 + rand() % 5;//целое число из интервала [1, 5]
    double z; int k;//z-равномерно распред. случ. число из интервала [0, 1]

    //заполнение массива точками xi
    for (int i = 0; i < m; i++) 
    {
        X[i] = a + i * (b - a) / m;
       // cout << X[i] << "\t";
    }
   // cout << endl;
    //заполнение  массива значений функции f(x) в точках xi
    for (int j = 0; j < m; j++) 
    {
        z = (double)(rand()) / RAND_MAX;
        if (z < 0.5)
        {
            k = -1;
        }
        else k = 1;
        F[j] = f(X[j]) * (1 + k * z / c);
       // cout << F[j] << "\t";
    }

    //выделение памяти для дин. матрицы Аij
    double** A{ new  double* [n] {} };
    for (unsigned j{}; j < n; j++)
    {
        A[j] = new double [n] {};
    }
    //создание и заполнение одномерного дин. массива Dk
    double* D{ new double[2 * n] {} };
    for (int k = 0; k < 2 * n; k++)
    {
        D[k] = 0;
        for (int i = 0; i < m; i++)
        {
            D[k] += pow(X[i], k);
        }
    }
    //заполнение матрицы Aij
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            A[i][j] = 0;
            A[i][j] = D[i + j];
        }
    }
    //удаление дин. массива D
    delete[] D;

    //создание и заполнение дин. массива Bk
    double* B{ new double[n] {} };
    for (int k = 0; k < n; k++)
    {
        B[k] = 0;
        for (int i = 0; i < m; i++)
        {
            B[k] += F[i] * pow(X[i], k);
        }
    }

   /*
   for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << A[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        cout << B[i] << "\t";
    }
    */

    //заполнение дин. массива коэф-в полинома
    double* C{ new double[n] {} };
    C = Gauss(A, B, n);
    /*for (int i = 0; i < n; i++)
    {
        cout << C[i] << "\t";
    }*/
    //удаление дин. массивов A и В
    delete[] A; delete[] B;

    //вычисление суммы квадратов отклонений Y и Fi
    double S = 0;
    for (int i = 0; i < m; i++)
    {
        S += pow((Y(C, X[i], n) - F[i]), 2);
    }
    cout<< "S = " << S << endl;
    Graphics(X, F, m, C, n);
}
