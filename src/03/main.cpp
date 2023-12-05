#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <regex>
#include <set>
#include <utility>

class Input {
public:
    Input(std::vector<std::tuple<int64_t, int64_t, int64_t, int64_t >> nr_line_coords,
          std::map<std::pair<int64_t, int64_t>, std::string> symbols) : nr_line_coords{std::move(nr_line_coords)},
                                                                        symbols{std::move(symbols)} {};

    std::vector<std::tuple<int64_t, int64_t, int64_t, int64_t >> nr_line_coords;
    std::map<std::pair<int64_t, int64_t>, std::string> symbols;
};

Input parse(char *filename) {
    std::vector<std::tuple<int64_t, int64_t, int64_t, int64_t >> nr_line_coords;
    std::map<std::pair<int64_t, int64_t>, std::string> symbols;

    std::ifstream input(filename);
    std::string line;
    std::regex re_nr("(\\d+)");
    std::regex re_symbol("([^0-9\\.])");

    int64_t line_nr = 0;
    while (std::getline(input, line)) {
        for (std::sregex_iterator it = std::sregex_iterator(line.begin(), line.end(), re_nr);
             it != std::sregex_iterator(); ++it) {
            auto nr = std::stoi(it->str());
            nr_line_coords.emplace_back(nr, line_nr, it->position(), it->position() + it->length() - 1);
        }

        for (std::sregex_iterator it = std::sregex_iterator(line.begin(), line.end(), re_symbol);
             it != std::sregex_iterator(); ++it) {
            symbols[{line_nr, it->position()}] = it->str();
        }

        line_nr++;
    }

    return Input(nr_line_coords, symbols);
}

int64_t partA(char *filename) {
    auto input = parse(filename);

    auto is_part_nr = [&input](const std::tuple<int64_t, int64_t, int64_t, int64_t> &coords) {
        const auto [nr, line, begin, end] = coords;

        for (int64_t pos = begin - 1; pos <= end + 1; pos++) {
            if (input.symbols.find({line - 1, pos}) != input.symbols.end()) {
                return true;
            }
        }

        if (input.symbols.find({line, begin - 1}) != input.symbols.end()) {
            return true;
        }

        if (input.symbols.find({line, end + 1}) != input.symbols.end()) {
            return true;
        }

        for (int64_t pos = begin - 1; pos <= end + 1; pos++) {
            if (input.symbols.find({line + 1, pos}) != input.symbols.end()) {
                return true;
            }
        }

        return false;
    };

    int64_t sum = 0;
    for (const auto &kv: input.nr_line_coords) {
        if (is_part_nr(kv)) {
            sum += std::get<0>(kv);
        }
    }

    return sum;
}

int64_t partB(char *filename) {
    auto input = parse(filename);

    auto neighbors = [&input](const std::pair<int64_t, int64_t> &symbol) {
        const auto [s_line, s_col] = symbol;

        std::vector<int64_t> nbs;
        for (const auto [nr, line, begin, end]: input.nr_line_coords) {
            if (std::abs(s_line - line) <= 1 && (begin - 1 <= s_col && s_col <= end + 1)) {
                nbs.push_back(nr);
            }
        }

        return nbs;
    };


    int64_t sum = 0;
    for (auto symbol: input.symbols) {
        if (symbol.second == "*") {
            auto nbs = neighbors(symbol.first);
            if (nbs.size() == 2) {
                sum += nbs[0] * nbs[1];
            }
        }
    }
    return sum;
}

int main(int argc, char **argv) {
    std::cout << "Part a = " << partA(argv[1]) << "\n";
    std::cout << "Part b = " << partB(argv[1]) << "\n";

    return 0;
}
