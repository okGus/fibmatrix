#include <iostream>
#include <vector>
#include <string>
#include <cmath>

std::string tobinary(int decimal)
{
    std::string ret{};
    while (decimal > 0)
    {
        ret = ret + std::to_string(decimal % 2);
        decimal = decimal / 2;
    }
    return ret;
}

using Matrix = std::vector<std::vector<int>>;

Matrix mul(Matrix &a, Matrix &b)
{
    // if a is identity matrix
    if (a[0][0] == 1 && a[0][1] == 0 && a[1][0] == 0 && a[1][1] == 1)
        return b;
    // if b is identity matrix
    if (b[0][0] == 1 && b[0][1] == 0 && b[1][0] == 0 && b[1][1] == 1)
        return a;

    int w{};
    int x{};
    int y{};
    int z{};
    w = a[0][0] * b[0][0] + a[0][1] * b[1][0];
    x = a[0][0] * b[0][1] + a[0][1] * b[1][1];
    y = a[1][0] * b[0][0] + a[1][1] * b[1][0];
    z = a[1][0] * b[0][1] + a[1][1] * b[1][1];

    return {{w, x},
            {y, z}};
}

Matrix mull(Matrix &a, Matrix &b)
{
    int y = a[0][0] * b[0][0] + a[0][1] * b[1][0];
    int z = a[1][0] * b[0][0] + a[1][1] * b[1][0];

    return {{y}, {z}};
}

Matrix mpower(Matrix a, int p)
{
    if (p == 1)
        return a;

    a = mul(a, a);
    a = mpower(a, p / 2);

    return a;
}

int fib(int nth)
{
    int n_less = nth - 1;
    // 13 = 1101 but it returns it backwards 1011
    // to get proper index
    std::string n_binary = tobinary(n_less);
    Matrix matrix{{1, 1},
                  {1, 0}};
    std::vector<Matrix> fibmatrix;
    Matrix finalMatrix{};
    Matrix identity = {{1, 0}, {0, 1}};
    for (int idx{0}; idx < n_binary.size(); idx++)
    {
        fibmatrix.push_back(mpower(matrix, pow(2, idx)));
    }
    for (int cidx{0}; cidx < n_binary.size(); cidx++)
    {
        // initial, mul with identity if bit is set to 0
        // otherwise mul with final

        if (finalMatrix.empty() && n_binary[cidx] == '1')
        {
            finalMatrix = mul(fibmatrix[cidx], identity);
            continue;
        }
        else
        {
            if (n_binary[cidx] == '1')
                finalMatrix = mul(finalMatrix, fibmatrix[cidx]);
        }
        // if (cidx == 0)
        // {
        //     if (n_binary[cidx] == '1')
        //     {
        //         finalMatrix = mul(fibmatrix[cidx], identity);
        //         continue;
        //     }
        // }
        // if (n_binary[cidx] == '1')
        //     if (finalMatrix.empty())
        //     {
        //         finalMatrix = mul(fibmatrix[cidx], identity);
        //         continue;
        //     }
        //     finalMatrix = mul(finalMatrix, fibmatrix[cidx]);
    }
    Matrix initial = {{1}, {1}};
    Matrix ret = mull(finalMatrix, initial);

    return ret[0][0];
}

int main()
{
    std::cout << "Enter number to find in Fibonacci: ";
    std::string number;
    std::cin >> number;
    std::cout << "N: " << number << ", finding nth Fibonacci: " << fib(std::stoi(number)) << '\n';

    return EXIT_SUCCESS;
}