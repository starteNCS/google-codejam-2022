#include <iostream>
#include <vector>
#include <thread>

template<typename T>
void permutationHeapAlgorithm(size_t k, std::vector<int> &modules, T handler) {
    int *c = (int *) calloc(k, sizeof(int));
    if (handler(modules)) {
        return;
    }

    int i = 0;
    while (i < k) {
        if (c[i] < i) {
            if (i % 2 == 0) {
                std::swap(modules[0], modules[i]);
            } else {
                std::swap(modules[c[i]], modules[i]);
            }
            if (handler(modules)) {
                return;
            }

            c[i] += 1;
            i = 1;
        } else {
            c[i] = 0;
            i += 1;
        }
    }
}

int findHighest(const std::vector<int> &values) {
    int currentHighest = values[0];
    for (int i = 1; i < values.size(); i++) {
        if (values[i] > currentHighest) {
            currentHighest = values[i];
        }
    }
    return currentHighest;
}

int bruteForceMaxStraight(std::vector<int> &dices) {
    int currentHighestStreet = 0;
    size_t dicesCount = dices.size();
    int maxPossibleStraightFromValue = findHighest(dices);
    permutationHeapAlgorithm(dices.size(), dices, [&](std::vector<int> permutation) mutable {
        int permutationValue = 0;
        for (int i = 0; i < dicesCount; i++) {
            if (permutation[i] >= i + 1) {
                permutationValue += 1;
            } else {
                break;
            }
        }

        if (permutationValue > currentHighestStreet) {
            currentHighestStreet = permutationValue;
        }

        if (permutationValue == dicesCount || permutationValue == maxPossibleStraightFromValue) {
            return true;
        }
        return false;
    });

    return currentHighestStreet;
}

void printDices(int testCase, std::vector<int> &dices) {
    std::cout << "Case #" << testCase << ": " << bruteForceMaxStraight(dices) << std::endl;
}

int main() {
    int dataCount;
    scanf("%d", &dataCount);

    for (int i = 0; i < dataCount; ++i) {
        int diceCount;
        std::cin >> diceCount;

        std::vector<int> dices;
        for (int j = 0; j < diceCount; ++j) {
            int dice;
            std::cin >> dice;
            dices.push_back(dice);
        }

        std::thread thread_object([&] {
            printDices(i + 1, dices);
        });
        thread_object.join();
    }

    return 0;
}