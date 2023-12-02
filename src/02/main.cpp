#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <regex>

int64_t partA(char* filename)
{
	std::ifstream input(filename);
	std::string line;

    std::regex re_game("Game (\\d+): (.*)");
    std::regex re_red("(\\d+) red");
    std::regex re_green("(\\d+) green");
    std::regex re_blue("(\\d+) blue");

    int max_red = 12;
    int max_green = 13;
    int max_blue = 14;

    auto color_ok = [](std::string line, std::regex re, int max) {
        std::smatch match;
        while (std::regex_search(line, match, re)) {
            if (std::stoi(match[1].str()) > max) {
                return false;
            }
            line = match.suffix();
        }
        return true;
    };

    int sum = 0;
	while (std::getline(input, line)) {
        auto game_begin = std::sregex_iterator(line.begin(), line.end(), re_game);
        const auto& game_match = *game_begin;
        int nr = std::stoi(game_match[1] );

        std::string colors = game_match[2].str();
        if ( color_ok(colors, re_red, max_red) && color_ok(colors, re_green, max_green) && color_ok(colors, re_blue, max_blue))
        {
            sum += nr;
        }
	}

	return sum;
}

int64_t partB(char* filename)
{
    std::ifstream input(filename);
    std::string line;

    std::regex re_game("Game (\\d+): (.*)");
    std::regex re_red("(\\d+) red");
    std::regex re_green("(\\d+) green");
    std::regex re_blue("(\\d+) blue");

    auto color_max = [](std::string line, std::regex re) {
        std::smatch match;
        int max = 0;
        while (std::regex_search(line, match, re)) {
            int got = std::stoi(match[1].str());
            if (got > max) {
                max = got;
            }
            line = match.suffix();
        }
        return max;
    };

    int sum = 0;
    while (std::getline(input, line)) {
        auto game_begin = std::sregex_iterator(line.begin(), line.end(), re_game);
        const auto& game_match = *game_begin;
        int nr = std::stoi(game_match[1] );

        std::string colors = game_match[2].str();
        int min_red = color_max(colors, re_red);
        int min_green = color_max(colors, re_green);
        int min_blue = color_max(colors, re_blue);
        sum += min_red * min_green * min_blue;
    }

    return sum;
}

int main(int argc, char** argv)
{
	std::cout << "Part a=" << partA(argv[1]) << "\n";
	std::cout << "Part b=" << partB(argv[1]) << "\n";

	return 0;
}
