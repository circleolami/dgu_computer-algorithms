#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

int getNextPrime(int currentPrime)
{
    for (int num = currentPrime + 1;; ++num)
    {
        bool isPrime = true;
        for (int i = 2; i * i <= num; ++i)
        {
            if (num % i == 0)
            {
                isPrime = false;
                break;
            }
        }
        if (isPrime)
            return num;
    }
}

int hashCode1(const string &input)
{
    return input.length();
}

int hashCode3(const string &input)
{
    long long output = 1;
    int nextPrime = 1;

    for (char c : input)
    {
        nextPrime = getNextPrime(nextPrime);
        output = (output * static_cast<long long>(pow(nextPrime, c))) % INT_MAX;
    }

    return static_cast<int>(output);
}

int myHashCode(const string &input)
{
    int hash = 0;
    for (char c : input)
    {
        hash = 31 * hash + c;
    }
    return hash;
}

class HashTable
{
private:
    vector<list<string>> table;
    int size;

    int hash(const string &key, int (*hashFunc)(const string &))
    {
        int hashValue = hashFunc(key);
        return abs(hashValue % size);
    }

public:
    HashTable(int size) : size(size)
    {
        table.resize(size);
    }

    void insert(const string &key, int (*hashFunc)(const string &))
    {
        int hashValue = hash(key, hashFunc);
        table[hashValue].push_back(key);
    }

    int search(const string &key, int (*hashFunc)(const string &))
    {
        int hashValue = hash(key, hashFunc);
        int comparisons = 0;

        for (const auto &elem : table[hashValue])
        {
            comparisons++;
            if (elem == key)
            {
                return comparisons;
            }
        }

        return comparisons;
    }
};

string generateRandomString(int length)
{
    string str = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    string randomString;

    for (int i = 0; i < length; ++i)
    {
        randomString += str[rand() % str.size()];
    }

    return randomString;
}

int main()
{
    srand(time(nullptr));

    int N;

    cin >> N;

    HashTable table(N / 2);
    vector<string> strings;

    for (int i = 0; i < N; ++i)
    {
        string str = generateRandomString(rand() % 100 + 1);
        strings.push_back(str);
        table.insert(str, hashCode1);
    }

    HashTable table1(N / 2);
    HashTable table2(N / 2);
    HashTable table3(N / 2);

    for (int i = 0; i < N; ++i)
    {
        string str = generateRandomString(rand() % 100 + 1);
        strings.push_back(str);
        table1.insert(str, hashCode1);
        table2.insert(str, hashCode3);
        table3.insert(str, myHashCode);
    }

    // implementation1
    int totalComparison1 = 0;
    for (int i = 0; i < 100; ++i)
    {
        int idx = rand() % N;
        totalComparison1 += table.search(strings[idx], hashCode1);
    }
    cout << "implementation1: " << (totalComparison1 / 100.0) << endl;

    // implementation2
    int totalComparison2 = 0;
    for (int i = 0; i < 100; ++i)
    {
        int idx = rand() % N;
        totalComparison2 += table.search(strings[idx], hashCode3);
    }
    cout << "implementation3: " << (totalComparison2 / 100.0) << endl;

    // 정의한 hash
    int totalComparison3 = 0;
    for (int i = 0; i < 100; ++i)
    {
        int idx = rand() % N;
        totalComparison3 += table.search(strings[idx], myHashCode);
    }
    cout << "my hash code: " << (totalComparison3 / 100.0) << endl;

    return 0;
}
