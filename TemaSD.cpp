#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <ratio>
#include <iomanip>

std::ofstream out;
std::ofstream o;

class SortingAlg
{
    long long int sizeV;
    std::vector<long long int> v;
    std::vector <long long int> temp;
public:
    SortingAlg(int);
    SortingAlg(const SortingAlg&);
    void printVec();
    void radixSort();
    void mergeSort(int, int);
    void shellSort();
    void bubbleSort();
    int partitions(int, int);
    void quickSort(int, int);
    int getMax();
    int getSize()
    {
        return this->sizeV;
    }
};

int random() {
    return (rand() % 999999001) + 1000000;
}

SortingAlg::SortingAlg(int option = 0)
{
    sizeV = (rand()%999999001)+10000;
    v.resize(sizeV);
    temp.resize(sizeV + 1, 0);
    if(option == 0)
        std::generate(v.begin(), v.end(), random);
    else if(option == 1)
    {
        v.clear();
        int x = sizeV;
        while (x > 0)
            v.push_back(sizeV), x--;
    }
    else if(option == 2)
    {
        v.clear();
        int x = sizeV;
        while (x > 0)
            v.push_back(x), x--;
    }
    else if (option == 3)
    {
        v.clear();
        int x = 0;
        while (x < sizeV)
            v.push_back(x), x++;
    }
}

SortingAlg::SortingAlg(const SortingAlg& obj)
{
    this->sizeV = obj.sizeV;
    for (auto el : obj.v)
        this->v.push_back(el);
    for (auto el : obj.temp)
        this->temp.push_back(el);
}

void SortingAlg::printVec()
{
    out << sizeV << '\n';
    for (auto i : v)
    {
        out << i << ' ';
    }
}

int SortingAlg::getMax()
{
    int maxx = -1;
    for (int i = 0; i < sizeV; i++)
    {
        if (v[i] > maxx)
            maxx = v[i];
    }
    return maxx;
}

void SortingAlg::radixSort()
{
    int maxx = getMax();
    for (int exp = 1; maxx / exp > 0; exp *= 10)
    {
        std::vector <long long int> res(sizeV);
        int i, fr[10] = {};
        for (auto el : v)
            fr[(el / exp) % 10]++;
        for (i = 1; i < 10; i++)
            fr[i] += fr[i - 1];
        for (i = sizeV - 1; i >= 0; i--) {
            res[fr[(v[i] / exp) % 10] - 1] = v[i];
            fr[(v[i] / exp) % 10]--;
        }
        v.clear();
        for (auto el : res)
            v.push_back(el);
    }
}

void SortingAlg::mergeSort(int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;
        mergeSort(left, mid);
        mergeSort(mid + 1, right);
        int i = left, j = mid + 1, k = 0;
        while (i <= mid and j <= right)
            if (v[i] < v[j])
               temp[++k] = v[i++];
            else
                temp[++k] = v[j++];
        while (i <= mid)
            temp[++k] = v[i++];
        while (j <= right)
            temp[++k] = v[j++];
        for (i = left, j = 1; i <= right; i++, j++)
            v[i] = temp[j];
    }
}

void SortingAlg::shellSort() 
{
    for (int gap = sizeV / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < sizeV; i++)
        {
            int copyEl = v[i], j = i;
            while (j >= gap and v[j - gap] > copyEl) 
            {
                v[j] = v[j - gap];
                j -= gap;
            }
            v[j] = copyEl;
        }
    }
}

void SortingAlg::bubbleSort()
{
    bool done = 0;
    long long int i, aux;
    while (done == 0)
    {
        done = 1;
        for (i = 0; i < sizeV - 1; i++)
        {
            if (v[i] > v[i + 1])
            {
                aux = v[i];
                v[i] = v[i + 1];
                v[i + 1] = aux;
                done = 0;
            }
        }
    }
}

int SortingAlg::partitions(int left, int right)
{
    long long int piv[3] = { v[left + (rand() % (right - left + 1))],v[left + (rand() % (right - left + 1))],v[left + (rand() % (right - left + 1))] }, pivot, i = left - 1, j = right + 1, aux;
    if ((piv[0] <= piv[1] and piv[1] <= piv[2]) or (piv[2] <= piv[1] and piv[1] <= piv[0]))
        pivot = piv[1];
    else if ((piv[1] <= piv[0] and piv[0] <= piv[2]) or (piv[2] <= piv[0] and piv[0] <= piv[1]))
        pivot = piv[0];
    else
        pivot = piv[2];
    while (true)
    {
        do {
            i++;
        } while (v[i] < pivot);
        do {
            j--;
        } while (v[j] > pivot);
        if (i >= j)
            return j;
        aux = v[i];
        v[i] = v[j];
        v[j] = aux;
    }
}

void SortingAlg::quickSort(int left, int right)
{
    if (left >= 0 and right >= 0 and left < right)
    {
        int p = SortingAlg::partitions(left, right);
        quickSort(left, p);
        quickSort(p + 1, right);
    }
}

int main()
{
    out.open("time.txt");
    o.open("tests.txt");
    for (int i = 0; i < 4; i++)
    {
        double tradix = 0.0, tmerge = 0.0, tshell = 0.0, tquick = 0.0, tbubble = 0.0, rm = 0.0, mm = 0.0, sm = 0.0, qm = 0.0, bm = 0.0;
        int wr, wm, ws, wq, wb;
        o << "CAZUL " << i << ":\n";
        for (int j = 1; j <= 10; j++)
        {
            SortingAlg a(i);
            SortingAlg b = a, c = a, d = a, e = a;
            o << "Testul " << j << ": N=" << a.getSize() << " MAX=" << a.getMax() << '\n';
            auto start1 = std::chrono::high_resolution_clock::now();
            a.radixSort();
            auto end1 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> diff1 = end1 - start1;
            tradix += diff1.count();
            if (diff1.count() > rm)
                rm = diff1.count(), wr = j;

            auto start2 = std::chrono::high_resolution_clock::now();
            b.shellSort();
            auto end2 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> diff2 = end2 - start2;
            tshell += diff2.count();
            if (diff2.count() > sm)
                sm = diff2.count(), ws = j;

            auto start3 = std::chrono::high_resolution_clock::now();
            c.mergeSort(0, c.getSize()-1);
            auto end3 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> diff3 = end3 - start3;
            tmerge += diff3.count();
            if (diff3.count() > mm)
                mm = diff3.count(), wm = j;

            auto start4 = std::chrono::high_resolution_clock::now();
            d.bubbleSort();
            auto end4 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> diff4 = end4 - start4;
            tbubble += diff4.count();
            if (diff4.count() > bm)
                bm = diff4.count(), wb = j;

            auto start5 = std::chrono::high_resolution_clock::now();
            e.quickSort(0, e.getSize()-1);
            auto end5 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> diff5 = end5 - start5;
            tquick += diff5.count();
            if (diff5.count() > qm)
                qm = diff5.count(), wq = j;
        }
        out << "CAZUL " << i << '\n';
        out << std::setprecision(9) << "Radix: " << tradix/10 << ' ' << rm << ' ' << wr << '\n';
        out << std::setprecision(9) << "Shell: " << tshell/10 << ' ' << sm << ' ' << ws << '\n';
        out << std::setprecision(9) << "Merge: " << tmerge/10 << ' ' << mm << ' ' << wm << '\n';
        out << std::setprecision(9) << "Bubble: " << tbubble/10 << ' ' << bm << ' ' << wb << '\n';
        out << std::setprecision(9) << "Quick: " << tquick/10 << ' ' << qm << ' ' << wq << '\n';
     
    }
    o.close();
    out.close();
    return 0;
}
