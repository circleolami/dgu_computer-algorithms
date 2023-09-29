#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>

using namespace std;

bool is_valid_char(unsigned char c)
{
    return isalnum(c) || (c >= 0x81 && c <= 0xFE);
}

bool compare(const pair<string, int> &a, const pair<string, int> &b)
{
    if (a.second == b.second)
    {
        return a.first < b.first;
    }
    return a.second > b.second;
}

int main()
{
    ifstream file("datafile.txt", ios::binary);
    if (!file.is_open())
    {
        cout << "File not found." << endl;
        return 1;
    }

    map<string, int> wordCount;
    string line, content;

    // Entire file into content
    file.seekg(0, ios::end);
    content.resize(file.tellg());
    file.seekg(0, ios::beg);
    file.read(&content[0], content.size());
    file.close();

    string word;
    for (size_t i = 0; i < content.size(); ++i)
    {
        unsigned char c = content[i];
        if (is_valid_char(c))
        {
            if (c >= 0x81 && c <= 0xFE && i + 1 < content.size())
            {
                word += content.substr(i, 2);
                i += 1;
            }
            else
            {
                word += c;
            }
        }
        else
        {
            if (!word.empty())
            {
                wordCount[word]++;
                word.clear();
            }
        }
    }
    if (!word.empty())
    {
        wordCount[word]++;
    }

    vector<pair<string, int>> wordList(wordCount.begin(), wordCount.end());
    sort(wordList.begin(), wordList.end(), compare);

    for (const auto &p : wordList)
    {
        cout << p.first << " : " << p.second << endl;
    }

    return 0;
}
