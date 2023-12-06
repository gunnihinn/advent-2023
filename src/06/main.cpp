#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <regex>
#include <set>
#include <utility>

class Map {
public:
    class Range {
    public:
        int64_t src_start{0};
        int64_t dst_start{0};
        int64_t range{0};
    };

    int64_t map(int64_t n) {
        for (auto range: ranges) {
            if (range.src_start <= n && n <= range.src_start + range.range) {
                return n - range.src_start + range.dst_start;
            }
        }
        return n;
    }

    void add(int64_t src, int64_t dst, int64_t range) {
        ranges.emplace_back(src, dst, range);
    }

    bool empty() {
        return ranges.empty();
    }

private:
    std::vector<Range> ranges;
};


class Input {
public:
    std::vector<int64_t> seeds;
    std::vector<Map> maps;
};

Input parse(char *filename) {
    Input input;

    std::ifstream fh(filename);
    std::string line;

    std::getline(fh, line); // seeds
    std::getline(fh, line); // empty line

    Map map;
    while (std::getline(fh, line)) {
        if (line.empty()) {
            if (!map.empty()) {
                input.maps.push_back(map);
            }
            map = Map();
        } else if (line.find("map")) {
            // skip
        } else {
            int64_t src = std::stoi(line.substr())

        }
    }

    if (!map.empty()) {
        input.maps.push_back(map);
    }

    return input;
}

int64_t partA(char *filename) {
    int64_t result = 0;
    auto inputs = parse(filename);
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
