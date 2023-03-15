#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <ratio>
#include <iomanip>

std::ifstream in;
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
    void radixSort10();
    void radixSort256();
    void mergeSort(int, int);
    void shellSort();
    //void bubbleSort();
    void descent(int);
    int heap_pop();
    void heapSort();
    int partitions(int, int);
    void quickSort(int, int);

    bool operator== (const SortingAlg&);

    bool sortchecker();

    int getMax();
    int getSize()
    {
        return this->sizeV;
    }
};

int random()
{
    return (rand() % 10000) * (rand() % 10000);
}

SortingAlg::SortingAlg(int option = 0)
{
    sizeV = (rand()%1000) * (rand()%1000);
    v.resize(sizeV);
    temp.resize(sizeV + 1, 0);
    if(option == 0)
        std::generate(v.begin(), v.end(), random);
    else 
    {
        v.clear();
        if (option == 1)
        {
            int x = sizeV;
            while (x > 0)
                v.push_back(sizeV), x--;
        }
        else if (option == 2)
        {
            int x = sizeV;
            while (x > 0)
                v.push_back(x), x--;
        }
        else if (option == 3)
        {
            int x = 0;
            while (x < sizeV)
                v.push_back(x), x++;
        }
        else if (option == 4)
        {
            in.open("input.in");
            long long int x;
            in >> sizeV;
            for (long long int i = 0; i < sizeV; i++)
                in >> x, v.push_back(x);
            in.close();
        }
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
    out << v.size() << '\n';
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

void SortingAlg::radixSort10()
{
    int maxx = getMax();
    for (int exp = 1; maxx / exp > 0; exp *= 10)
    {
        std::vector <long long int> res(sizeV);
        long long int i, fr[10] = {};
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

void SortingAlg::radixSort256() {
    int maxx = getMax();
    int count = 0;
    for (long long int exp = 1; maxx / exp > 0; exp = exp<<8)
    {
        std::vector <long long int> res(sizeV);
        long long int i, fr[256] = {};
        for (auto el : v)
            fr[(el / exp) % 256]++;
        for (i = 1; i < 256; i++)
            fr[i] += fr[i - 1];
        for (i = sizeV - 1; i >= 0; i--) {
            res[fr[(v[i] / exp) % 256] - 1] = v[i];
            fr[(v[i] / exp) % 256]--;
        }
        v.clear();
        for (auto el : res)
            v.push_back(el), count++;
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

/*void SortingAlg::bubbleSort()
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
}*/

void SortingAlg::descent(int pos)
{
    long long int aux;
    if ( 2 * pos + 1 >= v.size())
        return;
    if ((2 * pos + 2 == v.size()) or v[2 * pos + 1] < v[2 * pos + 2])
        if (v[2 * pos + 1] < v[pos])
        {
            aux = v[pos];
            v[pos] = v[2 * pos + 1];
            v[2 * pos + 1] = aux;
            descent(2 * pos + 1);
            return;
        }
        else
            return;
    else
        if (v[2 * pos + 2] < v[pos])
        {
            aux = v[pos];
            v[pos] = v[2 * pos + 2];
            v[2 * pos + 2] = aux;
            descent(2 * pos + 2);
            return;
        }
        else
            return;
}

int SortingAlg::heap_pop()
{
    if (v.size() == 0)
        return -1;
    int top = v[0];
    v[0] = v[v.size() - 1];
    v.pop_back();
    descent(0);
    return 0;
}

void SortingAlg::heapSort() 
{
    temp.clear();
    for (int i = v.size() / 2; i >= 0; i--)
        descent(i);
    while (v.size()) 
    {
        temp.push_back(v[0]);
        heap_pop();
    }
    for (auto el : temp)
        v.push_back(el);
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

bool SortingAlg::operator== (const SortingAlg& obj)
{
    if (this->v == obj.v)
        return true;
    else
        return false;
}

bool SortingAlg::sortchecker() 
{
    if (v.size() != sizeV)
        return false;
    else
        for (long long int i = 0; i < sizeV - 1; i++)
            if (v[i] > v[i + 1])
                return false;
    return true;
}

void results()
{
    out.open("time.txt");
    o.open("tests.txt");
    for (int i = 0; i < 4; i++)
    {
        double tradix10 = 0.0, tmerge = 0.0, tshell = 0.0, tquick = 0.0, tradix256 = 0.0, theap = 0.0, r10m = 0.0, mm = 0.0, sm = 0.0, qm = 0.0, r256m = 0.0, hm = 0.0;
        int wr10, wm, ws, wq, wr256, wh;
        o << "CAZUL " << i << ":\n";
        for (int j = 1; j <= 10; j++)
        {
            SortingAlg a(i);
            SortingAlg b = a, c = a, d = a, e = a, f = a, g = a;
            o << "Testul " << i << '.' << j << ": N=" << a.getSize() << " MAX=" << a.getMax() << ' ';
            auto start1 = std::chrono::high_resolution_clock::now();
            a.radixSort10();
            auto end1 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> diff1 = end1 - start1;
            tradix10 += diff1.count();
            if (diff1.count() > r10m)
                r10m = diff1.count(), wr10 = j;

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
            d.radixSort256();
            auto end4 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> diff4 = end4 - start4;
            tradix256 += diff4.count();
            if (diff4.count() > r256m)
                r256m = diff4.count(), wr256 = j;

            auto start5 = std::chrono::high_resolution_clock::now();
            e.quickSort(0, e.getSize()-1);
            auto end5 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> diff5 = end5 - start5;
            tquick += diff5.count();
            if (diff5.count() > qm)
                qm = diff5.count(), wq = j;

            auto start6 = std::chrono::high_resolution_clock::now();
            f.heapSort();
            auto end6 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> diff6 = end6 - start6;
            theap += diff6.count();
            if (diff6.count() > hm)
                hm = diff6.count(), wh = j;

            if (a.sortchecker() and b.sortchecker() and c.sortchecker() and d.sortchecker() and e.sortchecker() and f.sortchecker())
                if (a == b and b == c and c == d and d == e and e == f and f == a)
                    o << "OK!" << '\n';

        }
        out << "CAZUL " << i << '\n';
        out << std::setprecision(9) << "Radix10: " << tradix10/10 << ' ' << r10m << ' ' << i << '.' << wr10 << '\n';
        out << std::setprecision(9) << "Radix256: " << tradix256 / 10 << ' ' << r256m << ' ' << i << '.' << wr256 << '\n';
        out << std::setprecision(9) << "Shell: " << tshell/10 << ' ' << sm << ' ' << i << '.' << ws << '\n';
        out << std::setprecision(9) << "Merge: " << tmerge/10 << ' ' << mm << ' ' << i << '.' << wm << '\n';
        out << std::setprecision(9) << "Quick: " << tquick/10 << ' ' << qm << ' ' << i << '.' << wq << '\n';
        out << std::setprecision(9) << "Heap: " << theap / 10 << ' ' << hm << ' ' << i << '.' << wh << '\n';
     
    }
    o.close();
    out.close();
}

int main()
{
    results();
    return 0;
}
