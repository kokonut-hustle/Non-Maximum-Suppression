#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include "helper.hpp"

int inp(std::list<BBOX> &list_box, const char *file) {
    std::ifstream inp;
    inp.open(file);
    if (!inp.is_open()) {
        std::cout << "cannot open input file " << file << std::endl;
        return 1;
    }
    std::string line;
    while (getline(inp, line)) {
        std::stringstream ss(line);
        BBOX temp_box;
        ss >> temp_box.lower_left.x >> temp_box.lower_left.y 
            >> temp_box.upper_right.x >> temp_box.upper_right.y >> temp_box.score;
        list_box.push_back(temp_box);
    }
    inp.close();
    return 0;
}

int oup(const std::list<BBOX> &list_box, const char *file) {
    std::ofstream oup;
    oup.open(file);
    if (!oup.is_open()) {
        std::cout << "cannot open output file " << file << std::endl;
        return 1;
    }
    for (const auto &temp_box : list_box) {
        oup << temp_box.lower_left.x << " " << temp_box.lower_left.y 
            << " " << temp_box.upper_right.x << " " << temp_box.upper_right.y << std::endl;
    }
    oup.close();
    return 0;
}

void solve(std::list<BBOX> &list_box, std::list<BBOX> &res, const char *threshold) {
    double sc_threshold = std::atoi(threshold);
    list_box.sort([](const BBOX &lhs, const BBOX &rhs) {
        return lhs.score >= rhs.score;
    });
    for (BBOX temp_box; !list_box.empty();) {
        temp_box = list_box.front();
        list_box.pop_front();
        res.push_back(temp_box);
        for (auto box_iter = list_box.begin(); box_iter != list_box.end(); ++box_iter) {
            if (IOU(temp_box, *box_iter) > sc_threshold) {
                list_box.erase(box_iter);
            }
        }
    }
    return;
}

int main(int argc, char **argv) {
    if (argc != 4)
    {
        std::cout << "need 4 arguments" << std::endl;
        return 1;
    }

    std::list<BBOX> list_box, res;

    if (inp(list_box, argv[1]))
        return 1;
    solve(list_box, res, argv[3]);
    oup(res, argv[2]);

    return 0;
}
