#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <regex>
#include <set>
#include <utility>

class Input {
public:
    Input(std::set<int64_t> winning, std::set<int64_t> have) : winning{std::move(winning)}, have{have} {};

    std::set<int64_t> winning;
    std::set<int64_t> have;
};

std::vector<Input> parse(char *filename) {
    std::vector<Input> inputs;

    std::ifstream input(filename);
    std::string line;

    std::regex re_nr("(\\d+)");
    auto nrs = [re_nr](std::string line) {
        std::set<int64_t> ns;
        auto begin = std::sregex_iterator(line.begin(), line.end(), re_nr);
        auto end = std::sregex_iterator();
        for (std::sregex_iterator it = begin; it != end; ++it) {
            ns.insert(std::stoi(it->str()));
        }
        return ns;
    };

    while (std::getline(input, line)) {
        size_t col = line.find(":");
        size_t pipe = line.find("|");
        std::string winning = line.substr(col + 1, pipe - col - 1);
        std::string have = line.substr(pipe + 1, line.length() - pipe);
        inputs.emplace_back(nrs(winning), nrs(have));
    }

    return inputs;
}

int64_t partA(char *filename) {
    int64_t sum = 0;
    auto inputs = parse(filename);
    for (auto input: inputs) {
        int64_t cnt = 0;
        for (auto have: input.have) {
            if (auto ok = input.winning.find(have); ok != input.winning.end()) {
                cnt++;
            }
        }
        if (cnt > 0) {
            sum += 1 << (cnt - 1);
        }
    }
    return sum;
}

int64_t partB(char *filename) {
    auto inputs = parse(filename);

    std::map<uint64_t, uint64_t> card_to_count;
    for (size_t i = 0; i < inputs.size(); i++) {
        card_to_count[i] = 1;
    }

    for (size_t i = 0; i < inputs.size(); i++) {
        auto input = inputs[i];
        int64_t cnt = 0;
        for (auto have: input.have) {
            if (auto ok = input.winning.find(have); ok != input.winning.end()) {
                cnt++;
            }
        }
        for (size_t j = i + 1; j < std::min(i + 1 + cnt, inputs.size()); j++) {
            card_to_count[j] += card_to_count[i];
        }
    }

    int64_t sum = 0;
    for (auto kv : card_to_count)
    {
        sum += kv.second;
    }
    return sum;
}

int main(int argc, char **argv) {
    std::cout << "Part a = " << partA(argv[1]) << "\n";
    std::cout << "Part b = " << partB(argv[1]) << "\n";

    return 0;
}
