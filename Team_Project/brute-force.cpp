#include <iostream>
#include <vector>
#include <climits>

using namespace std;

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
    cout << "Enter desired amount of carbohydrates (g): ";
    cin >> carbs;
    cout << "Enter desired amount of protein (g): ";
    cin >> protein;
    cout << "Enter desired amount of fat (g): ";
    cin >> fat;
}

int calculateTotalCalories(int carbs, int protein, int fat) {
    return carbs * 4 + protein * 4 + fat * 9;
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

void findOptimalCombination(const vector<FoodItem>& items, vector<FoodItem>& current, vector<FoodItem>& best, int& minPrice, int targetCalories, int maxSodium, int index = 0) {
    if (index == items.size()) {
        if (isValid(current, targetCalories, maxSodium)) {
            int currentPrice = 0;
            for (const auto& item : current) {
                currentPrice += item.price;
            }
            if (currentPrice < minPrice) {
                minPrice = currentPrice;
                best = current;
            }
        }
        return;
    }

    // Include current item
    current.push_back(items[index]);
    findOptimalCombination(items, current, best, minPrice, targetCalories, maxSodium, index + 1);

    // Exclude current item
    current.pop_back();
    findOptimalCombination(items, current, best, minPrice, targetCalories, maxSodium, index + 1);
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
        {"3XL고추참치삼각", 1700, 303, 510, 51, 2, 7, 9},
        {"채식버섯잡채밥", 4300, 555, 840, 115, 7, 7, 8},
        {"꿀호떡버거", 3400, 446, 750, 68, 23, 14, 12},
        {"크라비아스틱", 2000, 65, 430, 6, 1, 1, 6},
        {"프로틴액티브초코", 3200, 135, 170, 7, 4, 3, 20},
        {"먹태리아나쵸칩", 1500, 300, 300, 39, 2, 14, 4},
        {"틈새라면고기짬뽕컵", 1900, 450, 1630, 69, 5, 15, 10},
        {"HEYROO닭가슴살득템", 1900, 114, 640, 1, 1, 2, 23},
        {"햇반", 2100, 315, 15, 70, 0, 2, 5},
        {"놀라운파스타샐러드", 2300, 161, 110, 24, 3, 5, 5},
        {"놀라운계란샐러드", 2500, 167, 105, 6, 4, 5, 8},
        {"놀라운치즈견과샐러드", 2500, 140, 65, 12, 3, 8, 5},
        {"고대초코&블루베리크림파이", 3200, 787, 190, 74, 51, 51, 8},
        {"백종원제대로제육한판", 4500, 812, 1590, 99, 21, 28, 41},
        {"간장맛닭갈비", 6000, 166, 480, 10, 6, 8, 14},
        {"스팸닭가슴살", 6200, 170, 480, 1, 1, 11, 17},
        {"꼬꼬봉크림치즈", 1600, 55, 112, 5, 3, 3, 3},
        {"호만두명란교자", 4400, 530, 1250, 27, 11, 40, 15},
        {"레드스푼고기짬뽕", 700, 300, 21020, 19, 5, 14, 24}
    };

    int carbs, protein, fat;
    getInput(carbs, protein, fat);

    int targetCalories = calculateTotalCalories(carbs, protein, fat);
    int maxSodium = 2000; // 나트륨 최대 한계

    vector<FoodItem> currentCombination, optimalCombination;
    int minPrice = INT_MAX;

    findOptimalCombination(items, currentCombination, optimalCombination, minPrice, targetCalories, maxSodium);

    // 결과 출력
    cout << "Optimal Food Combination:" << endl;
    for (const auto& item : optimalCombination) {
        cout << item.name << " - Price: " << item.price << endl;
    }
    cout << "Total Price: " << minPrice << endl;

    return 0;
}
