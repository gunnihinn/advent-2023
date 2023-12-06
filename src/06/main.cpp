#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <regex>
#include <utility>

class Input {
public:
    std::vector<std::pair<int64_t, int64_t> > races;
};

Input parse(char *filename) {
    Input input;

    std::vector<int64_t> times;
    std::vector<int64_t> distances;

    std::ifstream fh(filename);
    std::string line;
    std::regex re("(\\d+)");

    std::getline(fh, line); // times
    for (auto it = std::sregex_iterator(line.begin(), line.end(), re); it != std::sregex_iterator(); ++it) {
        times.push_back(std::stol(it->str()));
    }

    std::getline(fh, line); // distances
    for (auto it = std::sregex_iterator(line.begin(), line.end(), re); it != std::sregex_iterator(); ++it) {
        distances.push_back(std::stol(it->str()));
    }

    for (size_t i = 0; i < times.size(); i++) {
        input.races.emplace_back(times[i], distances[i]);
    }

    return input;
}

int64_t partA(char *filename) {
    int64_t result = 1;
    auto inputs = parse(filename);
    for (auto [time, record] : inputs.races) {
        int64_t count = 0;
        for (int64_t c = 0; c <= time; c++) {
            if ( c * (time - c) > record) {
                count++;
            }
        }
        result *= count;
    }
    return result;
}

int64_t partB(char *filename) {
    int64_t result = 0;
    auto inputs = parse(filename);
    return result;
}

int main(int argc, char **argv) {
    std::cout << "Part a = " << partA(argv[1]) << "\n";
    std::cout << "Part b = " << partB(argv[1]) << "\n";

    return 0;
}
