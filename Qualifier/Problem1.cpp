#include <iostream>
#include <tuple>

void printFields(int rowIndex, int c){
    int colStartAmount = 0;
    if(rowIndex == 0){
        std::cout << "..";
        colStartAmount = 1;
    }
    for (int col = colStartAmount; col < c; ++col) {
        std::cout << "|.";
    }
    std::cout << "|" << std::endl;
}

void printBorders(int rowIndex, int c){
    int colStartAmount = 0;
    if(rowIndex == 0){
        std::cout << "..";
        colStartAmount = 1;
    }
    for (int col = colStartAmount; col < c; ++col) {
        std::cout << "+-";
    }
    std::cout << "+" << std::endl;
}

void printMatrix(int caseNr, int r, int c){
    std::cout << "Case #" << caseNr << ":" << std::endl;
    for(int row = 0; row < r; row++){
        printBorders(row, c);
        printFields(row, c);
    }
    printBorders(r, c);
}

int main() {
    
    int dataCount;
    scanf("%d", &dataCount);
    std::tuple<int, int> matrixTemplates[dataCount];

    for (int i = 0; i < dataCount; ++i) {
        int r, c;
        scanf("%d %d", &r, &c);
        matrixTemplates[i] = std::tuple<int, int>{r, c};
    }

    int index = 1;
    for (auto templ : matrixTemplates) {
        printMatrix(index, std::get<0>(templ), std::get<1>(templ));
        index++;
    }
    
    return 0;
}
