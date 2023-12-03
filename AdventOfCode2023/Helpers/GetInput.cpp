#include "GetInput.h"

#include <iostream>
#include <fstream>
#include <filesystem>

#include<iostream>

using namespace std;

InputManager::InputManager(const std::string& day) : file()
{
    file.open("../../../" + day + ".txt");

    if (!file)
    {
        throw std::exception("File does not exist");
    }
}

Matrix InputManager::getMatrix()
{
    file.clear();
    file.seekg(0);

    Matrix matrix{};

    std::string s;

    while (std::getline(file, s))
    {
        std::vector<char> line;

        for (char c : s)
        {
            line.push_back(c);
        }

        matrix.push_back(line);
    }

    return matrix;
}