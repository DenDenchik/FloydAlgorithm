#pragma warning(disable:4996)
#include <iostream>
#include <limits>
#include <iomanip>
#define SIZE 100
using namespace std;
int head[SIZE];
int next_el[SIZE];
int terminal[SIZE];
int k;


void Add(int vert1, int vert2)
{
    k++;
    terminal[k] = vert2;
    next_el[k] = head[vert1];
    head[vert1] = k;
}

void Floyd(int vertices, double** matrix)
{
    for (int v = 0; v < vertices; v++)
    {
        for (int i = 0; i < vertices; i++)
        {
            for (int j = 0; j < vertices; j++)
            {
                double temp = matrix[i][v] + matrix[v][j];
                if (matrix[i][j] > temp)
                {
                    matrix[i][j] = matrix[i][v] + matrix[v][j];
                }
            }
        }
    }
}

int main()
{
    int vertices, edges, i, j, vert1, vert2;
    k = 0;
    setlocale(LC_ALL, "Rus");
    FILE* fin;
    fin = fopen("input.txt", "r");
    fscanf(fin, "%i", &vertices);
    fscanf(fin, "%i", &edges);
    for (i = 0; i < edges; i++)
    {
        fscanf(fin, "%i", &vert1);
        fscanf(fin, "%i", &vert2);
        Add(vert1, vert2);
    }
    fclose(fin);
    cout << "Список смежности графа:";
    for (i = 0; i < vertices + 1; i++)
    {
        j = head[i];
        if (i) cout << i << "->";
        while (j > 0)
        {
            if (!next_el[j]) cout << terminal[j];
                else cout << terminal[j] << ", ";
            j = next_el[j];
        }
        cout << endl;
    }
    cout << endl;
    double** matrix = new double* [vertices];
    for (i = 0; i < vertices; i++)
    {
        matrix[i] = new double[vertices];
        for (j = 0; j < vertices; j++)
        {
            if (i!=j)
                matrix[i][j] = std::numeric_limits<double>::infinity();
            else
                matrix[i][i] = 0;
        }
    }
    for (i = 1; i <= vertices; i++)
    {
        j = head[i];
        while (j > 0)
        {
            matrix[i - 1][terminal[j] - 1] = 1;
            j = next_el[j];
        }
    }
    Floyd(vertices, matrix);
    cout << "Матрица расстояний:" << endl;
    cout << endl;

    const int width = 4; 

    cout << setw(width) << " ";
    for (j = 0; j < vertices; j++)
        cout << setw(width) << (j + 1);
    cout << endl;
    cout << setw(width) << " ";
    for (j = 0; j < vertices; j++)
        cout << setw(width) << "----";
    cout << endl;

    for (i = 0; i < vertices; i++)
    {
        cout << setw(width) << (i + 1) << "|";
        for (j = 0; j < vertices; j++)
        {
            if (matrix[i][j] == std::numeric_limits<double>::infinity())
                cout << setw(width) << "inf";
            else
                cout << setw(width) << matrix[i][j];
        }
        cout << endl;
    }
    delete[] matrix;
    system("pause>>void");
}
