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

    int64_t map(int64_t n) const {
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
    std::regex re("\\d+");

    std::getline(fh, line); // seeds
    for (auto it = std::sregex_iterator(line.begin(), line.end(), re); it != std::sregex_iterator(); ++it) {
        input.seeds.push_back(std::stol(it->str()));
    }

    Map map;
    while (std::getline(fh, line)) {
        if (line.empty()) {
            if (!map.empty()) {
                input.maps.push_back(map);
            }
            map = Map();
        } else if (std::string::npos != line.find("map")) {
            // skip
        } else {
            std::vector<int64_t> ints;
            for (auto it = std::sregex_iterator(line.begin(), line.end(), re); it != std::sregex_iterator(); ++it) {
                ints.push_back(std::stol(it->str()));
            }
            map.add(ints[1], ints[0], ints[2]);
        }
    }

    if (!map.empty()) {
        input.maps.push_back(map);
    }

    return input;
}

int64_t run(int64_t seed, const std::vector<Map>& maps)
{
    for (const auto& map: maps) {
        seed = map.map(seed);
    }
    return seed;
}

int64_t partA(char *filename) {
    auto inputs = parse(filename);
    std::vector<int64_t> finals;
    for (int64_t seed: inputs.seeds) {
        finals.push_back(run(seed, inputs.maps));
    }

    auto result = std::min_element(finals.begin(), finals.end());
    return *result;
}


int64_t partB(char *filename) {
    auto inputs = parse(filename);

    int64_t result = run(inputs.seeds[0], inputs.maps);
    for (size_t i = 0; i < inputs.seeds.size() / 2; i++) {
        int64_t seed = inputs.seeds[2 * i];
        std::cout << "seed=" << seed << "\n";
        for (int64_t j = 0; j < inputs.seeds[2 * i + 1]; j++) {
            result = std::min(result, run(seed + j, inputs.maps));
        }
    }

    return result;
}

int main(int argc, char **argv) {
    std::cout << "Part a = " << partA(argv[1]) << "\n";
    std::cout << "Part b = " << partB(argv[1]) << "\n";

    return 0;
}
