#include <chrono>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include "SortingAlgorithm.hpp"

using namespace std;
using namespace SortLibrary;

double tempo_Bubblesort(vector<int> v, double& tempo, unsigned int& num_iterazioni)
{
    for(unsigned int i = 0; i < num_iterazioni; i++)
    {chrono::steady_clock::time_point t_inizio = chrono::steady_clock::now();
        BubbleSort(v);
        chrono::steady_clock::time_point t_fine = chrono::steady_clock::now();
        tempo += chrono::duration_cast<chrono::microseconds> (t_fine - t_inizio).count();
    }
    return tempo/num_iterazioni;
}

double tempo_Mergesort(vector<int> v, double& tempo, unsigned int num_iterazioni)
{
    for(unsigned int i = 0; i < num_iterazioni; i++)
    {chrono::steady_clock::time_point t_inizio = chrono::steady_clock::now();
        MergeSort(v);
        chrono::steady_clock::time_point t_fine = chrono::steady_clock::now();
        tempo += chrono::duration_cast<chrono::microseconds> (t_fine - t_inizio).count();
    }
    return tempo/num_iterazioni;
}

int main(int argc, char ** argv)
{
    int n = 0;
    unsigned int num_iterazioni = 100;
    vector<double> time_Bubblesort(argc);
    vector<double> time_Mergesort(argc);
    for(int i = 1; i < argc; i++){
        double tempo_B = 0;
        double tempo_M = 0;
        size_t dimv = stoll(argv[i]); // stol mi trasforma il carattere in numero long long
        vector<int> v1(dimv); // Vettore già ordinato, il metodo Bubblesort converge più rapidamente
        generate(v1.begin(), v1.end(), [&n] () {return n++;});
        tempo_B = tempo_Bubblesort(v1, tempo_B, num_iterazioni);
        time_Bubblesort[i-1] = tempo_B;
        tempo_M = tempo_Mergesort(v1, tempo_B, num_iterazioni);
        time_Mergesort[i-1] = tempo_M;
    }
    cout << "Tempi in microsecondi per l'ordinamento di un vettore pre-riordinato" << endl;
    cout << "Bubblesort: " << endl;
    for(int k = 0; k < argc - 1; k++)
        cout << "dimensione: " << argv[k+1] << " ,tempo: " << time_Bubblesort[k] << ";  ";
    cout<< endl;
    cout << "Mergesort: " << endl;
    for(int k = 0; k < argc - 1; k++)
        cout << "dimensione: " << argv[k+1] << " ,tempo: " << time_Mergesort[k] << ";  ";
    cout<< endl;


    for(int i = 1; i < argc; i++){
        double tempo_B = 0;
        double tempo_M = 0;
        size_t dimv = stoll(argv[i]); // stol mi trasforma il carattere in numero long long
        vector<int> v2(dimv); // Vettore randomico, il metodo Mergesort converge più rapidamente
        for(unsigned int j = 0; j < dimv; j++)
            v2[j] = rand()%1000;
        tempo_B = tempo_Bubblesort(v2, tempo_B, num_iterazioni);
        time_Bubblesort[i-1] = tempo_B;
        tempo_M = tempo_Mergesort(v2, tempo_B, num_iterazioni);
        time_Mergesort[i-1] = tempo_M;
    }
    cout << "Tempi in microsecondi per l'ordinamento di un vettore randomico" << endl;
    cout << "Bubblesort: " << endl;
    for(int k = 0; k < argc - 1; k++)
        cout << "dimensione: " << argv[k+1] << " ,tempo: " << time_Bubblesort[k] << ";  ";
    cout<< endl;
    cout << "Mergesort: " << endl;
    for(int k = 0; k < argc - 1; k++)
        cout << "dimensione: " << argv[k+1] << " ,tempo: " << time_Mergesort[k] << ";  ";
    cout<< endl;

    return 0;
}

