#include <chrono>
#include <string>
#include <sstream>
#include <iostream>
#include <set>

const std::set<unsigned int> UNIVERSE = 
{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 
    12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 
    26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40};

namespace SetTheory 
{
    void Print(const std::set<unsigned int>& set, const std::string& name) 
    {
        std::cout << name << ": {";
        for (auto it = set.begin(); it != set.end(); ++it ) 
        {
            if (it != set.begin()) std::cout << ", ";
            std::cout << *it;
        }
        std::cout << "}" << std::endl;
    }

    std::set<unsigned int> Input(const std::string& setName) 
    {
        std::set<unsigned int> result;
        std::string input;
        std::cout << "Enter elements for Set " << setName << " 1-40 separate with a space : ";
        std::getline(std::cin, input);
        std::stringstream ss(input);
        unsigned int val;
        while (ss >> val) 
        {
            if (val >= 1 && val <= 40) result.insert(val);
            else std::cout << "Invalid value: " << val << " Keep between 1-40\n";
        }
        return result;
    }
}

unsigned long long combinations(unsigned int n, unsigned int k ) 
{
    if (k > n / 2) k = n - k;
    if (k == 0) return 1;
    unsigned long long result = 1;
    for (unsigned int i = 1; i <= k; ++i )
        result = result * (n - i + 1) / i;
    return result;
}

unsigned long long permutations(unsigned int n, unsigned int k) 
{
    unsigned long long result = 1;
    for (unsigned int i = 0; i < k; ++i)
        result *= (n - i);
    return result;
}

unsigned long long recursivefib(unsigned int n) 
{
    if (n <= 1) return n;
    return recursivefib(n - 1) + recursivefib(n - 2);
}

unsigned long long iterativefib(unsigned int n) 
{
    if (n <= 1) return n;
    unsigned long long a = 0, b = 1, result = 0;
    for (unsigned int i = 2; i <= n; ++i) 
    {
        result = a + b;
        a = b;
        b = result;
    }
    return result;
}

template <typename Func>
void fibo_og(Func fibFunc, const std::string& label, unsigned int n)
{
    auto start = std::chrono::high_resolution_clock::now();
    unsigned long long result = fibFunc(n);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << label << ":\nFibonacci(" << n << ") = " << result << "\nTime: " << elapsed.count() << " seconds\n\n";
}

void displaymenu() 
{
    std::cout << "\n1. Set Theory\n2. Combinatorics\n3. Recursive Relations\n0. Exit\n";
}

void settheory() 
{
    using namespace SetTheory;
    std::cout << "\n--------- SET THEORY --------\n";
    auto setA = Input("A");
    auto setB = Input("B");
    std::cout << "\nSet Operations:\n";
    Print(setA, "Set A");
    Print(setB, "Set B");
    std::cout << "\n";
    std::set<unsigned int> result;
    
    // A ∪ B (Union)
    result.clear();
    for (auto& elem : setA) result.insert(elem);
    for (auto& elem : setB) result.insert(elem);
    Print(result, "A ∪ B");

    // A ∩ B (Intersection)
    result.clear();
    for (auto& elem : setA) 
        if (setB.count(elem)) result.insert(elem);
    Print(result, "A ∩ B");

    // A - B (Difference)
    result.clear();
    for (auto& elem : setA) 
        if (!setB.count(elem)) result.insert(elem);
    Print(result, "A - B");

    // B - A (Difference)
    result.clear();
    for (auto& elem : setB) 
        if (!setA.count(elem)) result.insert(elem);
    Print(result, "B - A");

    // A' (Complement of A)
    result.clear();
    for (auto& elem : UNIVERSE) 
        if (!setA.count(elem)) result.insert(elem);
    Print(result, "A'");

    // B' (Complement of B)
    result.clear();
    for (auto& elem : UNIVERSE) 
        if (!setB.count(elem)) result.insert(elem);
    Print(result, "B'");
}

void Combinatorics() 
{
    unsigned int n, k;
    while (true) 
    {
        std::cout << "Enter n: "; std::cin >> n;
        std::cout << "Enter k: "; std::cin >> k;
        if (std::cin.fail() || k > n) 
        {
            std::cin.clear(); std::cin.ignore(10000, '\n');
            std::cout << "Invalid input\n";
        } else break;
    }
    std::cin.ignore(10000, '\n');
    std::cout << "\nResults:\n";
    std::cout << "C(" << n << ", " << k << ") = " << combinations(n, k) << "\n";
    std::cout << "P(" << n << ", " << k << ") = " << permutations(n, k) << "\n";
}

void RecurRelations() 
{
    unsigned int n;
    while (true) 
    {
        std::cout << "Enter n for Fibonacci calculation: ";
        std::cin >> n;
        if (std::cin.fail() || n > 998) 
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Error! Please enter a number between 0 and 998.\n";
        } 
        else break;
    }
    std::cin.ignore(10000, '\n');

    // Skip recursive if n is large
    if (n > 50) 
    {
        std::cout << "Recursive method is skipped for n > 50 to avoid long processing times.\n";
        fibo_og(iterativefib, "Iterative Method", n);
    } 
    else 
    {
        fibo_og(recursivefib, "Recursive Method", n);
        fibo_og(iterativefib, "Iterative Method", n);
    }
}

int main() 
{
    bool exit = false;
    while (!exit) 
    {
        displaymenu();
        int choice;
        std::cout << "Enter your choice (0-3): ";
        std::cin >> choice;
        std::cin.ignore(10000, '\n');
        switch (choice) 
        {
            case 0: exit = true; std::cout << "Ciao!\n"; break;
            case 1: settheory(); break;
            case 2: Combinatorics(); break;
            case 3: RecurRelations(); break;
            default: std::cout << "Error! Please select a valid option.\n"; break;
        }
    }
    return 0;
}