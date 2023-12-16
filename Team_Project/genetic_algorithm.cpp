#include <bits/stdc++.h>
#define ll long long
using namespace std;
typedef struct food
{
    string name;
    int price, cal, carb, prot, fat;
} food;
typedef struct fitness
{
    int isSatisfied, cost, idx;
    double nutrientRatio;
} fitness;
ll N, ansCost, ansIdx, chromosomeCount, neededCal,
    neededCarb, neededProt, neededFat;
vector<vector<int>> chromosomes;
vector<fitness> fitnesses;
vector<food> foods = {
    {"자이언트머스타드치킨", 9900, 1559, 140, 72, 79},
    {"맛있구마샌드", 3400, 363, 56, 10, 11},
    {"바삭오렌지치킨", 6900, 949, 103, 33, 45},
    {"그릴드치킨버거", 3800, 447, 39, 21, 23},
    {"과카몰리부리또볼", 5900, 264, 33, 6, 12},
    {"김치카츠나베우동", 5000, 533, 75, 20, 17},
    {"바삭새우온소바", 5000, 465, 65, 13, 17},
    {"로스트닭가슴살덮밥", 4700, 414, 64, 32, 3},
    {"소금구이너비아니김밥", 3000, 457, 55, 12, 21},
    {"소금구이너비아니밥바", 2300, 465, 43, 18, 25},
    {"2XL간장바싹불고기", 1600, 275, 45, 8, 7},
    {"뉴비빔한줄", 3000, 372, 66, 9, 8},
    {"3XL고추참치삼각", 1700, 303, 51, 9, 7},
    {"채식버섯잡채밥", 4300, 555, 115, 8, 7},
    {"꿀호떡버거", 3400, 446, 68, 12, 14},
    {"크라비아스틱", 2000, 65, 6, 6, 1},
    {"프로틴액티브초코", 3200, 135, 7, 20, 3},
    {"먹태리아나쵸칩", 1500, 300, 39, 4, 14},
    {"틈새라면고기짬뽕컵", 1900, 450, 69, 10, 15},
    {"HEYROO닭가슴살득템", 1900, 114, 1, 23, 2},
    {"햇반", 2100, 315, 70, 5, 2},
    {"놀라운파스타샐러드", 2300, 161, 24, 5, 5},
    {"놀라운계란샐러드", 2500, 167, 66, 8, 5},
    {"놀라운치즈견과샐러드", 2500, 140, 12, 5, 8},
    {"고대초코&블루베리크림파이", 3200, 787, 74, 8, 51},
    {"백종원제대로제육한판", 4500, 812, 99, 41, 28},
    {"꼬꼬봉크림치즈", 1600, 55, 5, 3, 3},
    {"호만두명란교자", 4400, 530, 27, 15, 40},
    {"레드스푼고기짬뽕", 700, 300, 19, 24, 14},
    {"스팸닭가슴살", 6200, 340, 2, 17, 11}};
bool cmp(fitness f1, fitness f2)
{
    if (f1.isSatisfied && (f1.isSatisfied == f2.isSatisfied))
        return f1.cost < f2.cost;
    else if (!f1.isSatisfied && (f1.isSatisfied == f2.isSatisfied))
        return f1.nutrientRatio > f2.nutrientRatio;
    return f1.isSatisfied > f2.isSatisfied;
}
void calculateFitness(vector<int> &curChromosome, int idx)
{
    ll isSatisfied = 0, totCost = 0, totCal = 0,
       totCarb = 0, totProt = 0, totFat = 0;
    double calRatio, carbRatio, protRatio, fatRatio, totRatio;
    for (int i = 0; i < N; i++)
    {
        if (curChromosome[i] == 0)
            continue;
        totCost += foods[i].price;
        totCal += foods[i].cal;
        totCarb += foods[i].carb;
        totProt += foods[i].prot;
        totFat += foods[i].fat;
    }
    if (totCal >= neededCal && totCarb >= neededCarb &&
        totProt >= neededProt && totFat >= neededFat)
        isSatisfied = 1;
    calRatio = min(totCal, neededCal) / neededCal;
    carbRatio = min(totCarb, neededCarb) / neededCarb;
    protRatio = min(totProt, neededProt) / neededProt;
    fatRatio = min(totFat, neededFat) / neededFat;
    totRatio = calRatio * carbRatio * protRatio * fatRatio * 10000;
    fitness curFitness = {isSatisfied, totCost, idx, totRatio};
    fitnesses.push_back(curFitness);
}
void inPut()
{
    cout << "유전알고리즘\n\n";
    cout << "섭취하고자하는 영양소를 입력하시오 (최소 1)\n";
    cout << "열량(kcal) : ";
    cin >> neededCal;
    cout << "탄수화물(g) : ";
    cin >> neededCarb;
    cout << "단백질(g) : ";
    cin >> neededProt;
    cout << "지방(g) : ";
    cin >> neededFat;
}
void initialize()
{
    for (int i = 0; i < chromosomeCount; i++)
    {
        vector<int> tmp;
        for (int j = 0; j < N; j++)
        {
            int randVal = rand() % 100 + 1;
            randVal = ((randVal > 9) ? 0 : 1);
            tmp.push_back(randVal);
        }
        chromosomes.push_back(tmp);
    }
}
void selection()
{
    for (int i = 0; i < chromosomeCount; i++)
        calculateFitness(chromosomes[i], i);
    sort(fitnesses.begin(), fitnesses.end(), cmp);
    vector<vector<int>> tmpChromosomes;
    for (int i = 0; i < chromosomeCount / 2; i++)
        tmpChromosomes.push_back(chromosomes[fitnesses[i].idx]);
    chromosomes.clear();
    chromosomes = tmpChromosomes;
}
void crossoverNreplace()
{
    int size = (int)chromosomes.size();
    while ((int)chromosomes.size() < chromosomeCount)
    {
        vector<int> newChromosome(N);
        int i = rand() % (size - 1) + 1;
        int j = rand() % (size - 1) + 1;
        for (int k = 0; k < N; k++)
        {
            if (k <= N / 2)
                newChromosome[k] = chromosomes[i][k];
            else
                newChromosome[k] = chromosomes[j][k];
        }
        chromosomes.push_back(newChromosome);
    }
    if ((int)chromosomes.size() > chromosomeCount)
        chromosomes.resize(chromosomeCount);
}
void mutation()
{
    // skip
}
void loop()
{
    selection();
    crossoverNreplace();
    fitnesses.clear();
}
void getAns()
{
    fitnesses.clear();
    ansCost = LLONG_MAX;
    ansIdx = -1;
    for (int i = 0; i < chromosomeCount; i++)
        calculateFitness(chromosomes[i], i);
    for (auto nxt : fitnesses)
    {
        if (nxt.isSatisfied)
        {
            if (ansCost > nxt.cost)
            {
                ansCost = nxt.cost;
                ansIdx = nxt.idx;
            }
        }
    }
}
void outPut()
{
    cout << "\n\n최소 비용 : " << ansCost << "\n";
    cout << "구매하는 식품 조합 : \n";
    int cnt = 1;
    for (int i = 0; i < N; i++)
        if (chromosomes[ansIdx][i])
        {
            cout << cnt << " " << foods[i].name << "\n";
            cnt++;
        }
}
void solve()
{
    srand((unsigned int)time(NULL));
    chromosomeCount = 100;
    N = foods.size();
    inPut();
    initialize();
    for (int i = 0; i < 100000; i++)
        loop();
    getAns();
    outPut();
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    clock_t st, ed;
    st = clock();
    solve();
    ed = clock();
    long double rest = (long double)(ed - st);
    cout << "\n\n 수행 시간(ms) : " << rest;
    return 0;
}