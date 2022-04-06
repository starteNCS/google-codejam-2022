#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <thread>

struct Module {
    long fun = 0;
    Module *nextModule = nullptr;
    bool isStart = true;
    bool hasReacted = false;
};

template<typename T>
void permutationHeapAlgorithm(size_t k, std::vector<Module *> &modules, T handler) {
    long *c = (long *) calloc(k, sizeof(long));
    handler(modules);

    long i = 0;
    while (i < k) {
        if (c[i] < i) {
            if (i % 2 == 0) {
                std::swap(modules[0], modules[i]);
            } else {
                std::swap(modules[c[i]], modules[i]);
            }
            handler(modules);

            c[i] += 1;
            i = 1;
        } else {
            c[i] = 0;
            i += 1;
        }
    }
}

long max(std::vector<long> &values) {
    long currentMax = values[0];
    for (int i = 1; i < values.size(); i++) {
        if (currentMax < values[i]) {
            currentMax = values[i];
        }
    }
    return currentMax;
}

std::vector<Module *> onlyStartModules(std::vector<Module *> &modules) {
    std::vector<Module *> copy;
    for (auto module: modules) {
        if (module->isStart) {
            copy.push_back(module);
        }
    }
    return copy;
}

void clearReactions(std::vector<Module *> &modules) {
    for (auto module: modules) {
        module->hasReacted = false;
    }
}

long funOfReactionByStartModule(Module *start) {
    Module *currentModule = start;
    std::vector<long> funValues;
    while (currentModule != nullptr) {
        if (currentModule->hasReacted) {
            break;
        }
        funValues.push_back(currentModule->fun);
        currentModule->hasReacted = true;
        currentModule = currentModule->nextModule;
    }

    return max(funValues);
}

void printMostFun(int testCase, std::vector<Module *> &modules) {
    auto onlyStarterModules = onlyStartModules(modules);
    std::vector<long> totalFuns;
    permutationHeapAlgorithm(
            onlyStarterModules.size(),
            onlyStarterModules,
            [&](std::vector<Module *> &startModules) mutable {
        long totalFun = 0;
        for (int i = 0; i < startModules.size(); i++) {
            totalFun += funOfReactionByStartModule(startModules[i]);
        }
        clearReactions(modules);
        totalFuns.push_back(totalFun);
    });


    std::cout << "Case #" << testCase << ": " << max(totalFuns) << std::endl;
}

int main() {
    int dataCount;
    std::cin >> dataCount;
    std::vector<std::vector<Module *>> modules;

    for (int i = 0; i < dataCount; ++i) {
        int moduleCount;
        std::cin >> moduleCount;

        std::vector<Module *> mods;
        for (int j = 0; j < moduleCount; ++j) {
            auto module = new Module{};
            std::cin >> module->fun;
            mods.push_back(module);
        }

        for (int j = 0; j < moduleCount; ++j) {
            Module *module = mods.at(j);
            int nextModulePosition;
            std::cin >> nextModulePosition;
            if (nextModulePosition != 0) {
                auto next = mods.at(nextModulePosition - 1);
                module->nextModule = next;
                next->isStart = false;
            }
        }

        std::thread thread_object ([&] {
            printMostFun(i + 1, mods);
        });
        thread_object.join();
    }

    return 0;
}