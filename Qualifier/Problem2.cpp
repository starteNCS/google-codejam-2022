#include <iostream>
#include <vector>

const int PRINTER_COUNT = 3;
const int COLOR_COUNT = 4;
const int COLOR_USE_AMOUNT = 1000000;

struct Printer {
    int cyan;
    int magenta;
    int yellow;
    int kblack;
};

int findLowest(const int value[]){
    int currentLowest = value[0];
    for (int i = 1; i < PRINTER_COUNT; i++) {
        if(value[i] < currentLowest){
            currentLowest = value[i];
        }
    }
    return currentLowest;
}

void printCase(int testCase, std::vector<int> colors){
    std::cout << "Case #" << testCase << ": " << colors[0] << " " << colors[1] << " " << colors[2] << " " << colors[3] << std::endl;
}

void handlePrinter(int testCase, const std::vector<Printer*>& printers){
    std::vector<int> min_colors;
    min_colors.push_back(findLowest(new int[PRINTER_COUNT]{printers[0]->cyan, printers[1]->cyan, printers[2]->cyan}));
    min_colors.push_back(findLowest(new int[PRINTER_COUNT]{printers[0]->magenta, printers[1]->magenta, printers[2]->magenta}));
    min_colors.push_back(findLowest(new int[PRINTER_COUNT]{printers[0]->yellow, printers[1]->yellow, printers[2]->yellow}));
    min_colors.push_back(findLowest(new int[PRINTER_COUNT]{printers[0]->kblack, printers[1]->kblack, printers[2]->kblack}));

    int sum = min_colors[0] + min_colors[1] + min_colors[2] + min_colors[3];
    if(sum < COLOR_USE_AMOUNT){
        std::cout << "Case #" << testCase << ": IMPOSSIBLE" << std::endl;
        return;
    }

    if(sum == COLOR_USE_AMOUNT){
        printCase(testCase, min_colors);
        return;
    }

    if(sum > COLOR_USE_AMOUNT){
        int overhead = sum - COLOR_USE_AMOUNT;
        for (int i = 0; i < COLOR_COUNT; i++){
            int newValue = min_colors[i] - overhead;
            if(newValue >= 0){
                min_colors[i] = newValue;
                printCase(testCase, min_colors);
                return;
            }

            overhead = overhead - min_colors[i];
            min_colors[i] = 0;
        }
    }
}

int main() {
    int dataCount;
    scanf("%d", &dataCount);

    std::vector<std::vector<Printer*>> printers;
    for (int i = 0; i < dataCount; ++i) {
        std::vector<Printer *> subPrinter;
        for (int j = 0; j < PRINTER_COUNT; ++j) {
            int c, m, y, k;
            scanf("%d %d %d %d", &c, &m, &y, &k);
            subPrinter.insert(subPrinter.cend(), new Printer{c, m , y, k});
        }
        printers.insert(printers.cend(), subPrinter);
    }

    int index = 1;
    for (const auto& printer : printers) {
        handlePrinter(index, printer);
        index++;
    }

    return 0;
}