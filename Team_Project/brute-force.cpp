#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
#include <chrono> // 실행 시간 측정을 위한 헤더 추가

using namespace std;
using namespace std::chrono; // chrono 네임스페이스 사용

struct FoodItem {
    string name;
    int price;
    int calories;
    int sodium;
    int carbs;
    int sugars;
    int fat;
    int protein;
};

void getInput(int& carbs, int& protein, int& fat) {
    cout << "탄수화물 (g): ";
    cin >> carbs;
    cout << "단백질 (g): ";
    cin >> protein;
    cout << "지방 (g): ";
    cin >> fat;
}

int nutrientDifference(const vector<FoodItem>& combination, int carbs, int protein, int fat) {
    int totalCarbs = 0, totalProtein = 0, totalFat = 0;
    for (const auto& item : combination) {
        totalCarbs += item.carbs;
        totalProtein += item.protein;
        totalFat += item.fat;
    }
    return abs(carbs - totalCarbs) + abs(protein - totalProtein) + abs(fat - totalFat);
}

bool isValid(const vector<FoodItem>& combination, int targetCalories, int maxSodium) {
    int totalCalories = 0, totalSodium = 0, totalSugars = 0;
    for (const auto& item : combination) {
        totalCalories += item.calories;
        totalSodium += item.sodium;
        totalSugars += item.sugars;
        if (totalCalories > targetCalories || totalSodium > maxSodium || totalSugars > targetCalories * 0.1) {
            return false;
        }
    }
    return true;
}

void findOptimalCombination(const vector<FoodItem>& items, vector<FoodItem>& current, vector<FoodItem>& best, int& minPrice, int& minDifference, int carbs, int protein, int fat, int maxSodium, int index = 0) {
    if (index == items.size()) {
        int difference = nutrientDifference(current, carbs, protein, fat);
        if (isValid(current, carbs * 4 + protein * 4 + fat * 9, maxSodium) && difference < minDifference) {
            int currentPrice = 0;
            for (const auto& item : current) {
                currentPrice += item.price;
            }
            if (currentPrice < minPrice) {
                minPrice = currentPrice;
                minDifference = difference;
                best = current;
            }
        }
        return;
    }

    // Include current item
    current.push_back(items[index]);
    findOptimalCombination(items, current, best, minPrice, minDifference, carbs, protein, fat, maxSodium, index + 1);

    // Exclude current item
    current.pop_back();
    findOptimalCombination(items, current, best, minPrice, minDifference, carbs, protein, fat, maxSodium, index + 1);
}

int main() {
    vector<FoodItem> items = {
        {"자이언트머스타드치킨", 9900, 1559, 3230, 140, 51, 79, 72},
        {"맛있구마샌드", 3400, 363, 510, 56, 13, 11, 10},
        {"바삭오렌지치킨", 6900, 949, 1470, 103, 28, 45, 33},
        {"그릴드치킨버거", 3800, 447, 1070, 39, 10, 23, 21},
        {"과카몰리부리또볼", 5900, 264, 290, 33, 6, 12, 6},
        {"김치카츠나베우동", 5000, 533, 2730, 75, 3, 17, 20},
        {"바삭새우온소바", 5000, 465, 3250, 65, 13, 17, 13},
        {"로스트닭가슴살덮밥", 4700, 414, 610, 64, 8, 3, 32},
        {"소금구이너비아니김밥", 3000, 457, 780, 55, 6, 21, 12},
        {"소금구이너비아니밥바", 2300, 465, 760, 43, 2, 25, 18},
        {"2XL간장바싹불고기", 1600, 275, 500, 45, 1, 7, 8},
        {"뉴비빔한줄", 3000, 372, 1510, 66, 16, 8, 9},
        {"3XL고추참치삼각", 1700, 303, 510, 51, 2, 7, 9} };

    int carbs, protein, fat;
    getInput(carbs, protein, fat);

    int maxSodium = 2000; // 나트륨 최대 한계

    vector<FoodItem> currentCombination, optimalCombination;
    int minPrice = INT_MAX;
    int minDifference = INT_MAX;

    // 프로그램 시작 시간 측정
    auto start = high_resolution_clock::now();

    findOptimalCombination(items, currentCombination, optimalCombination, minPrice, minDifference, carbs, protein, fat, maxSodium);

    // 프로그램 종료 시간 측정
    auto stop = high_resolution_clock::now();

    // 결과 출력
    cout << "최적의 음식 조합은:" << endl;
    for (const auto& item : optimalCombination) {
        cout << item.name << " (가격: " << item.price << ")" << endl;
    }
    cout << endl;
    cout << "총액: " << minPrice << endl;

    // 실행 시간 계산 및 출력 (밀리초 단위)
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "실행 시간: " << duration.count() << " 밀리초" << endl;

    return 0;
}
