#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int64_t partA( char* filename )
{
    std::ifstream input( filename );
    std::string line;

    int64_t sum = 0;
    while( std::getline( input, line ) )
    {
        int64_t first = -1;
        int64_t last = -1;
        for( auto c : line )
        {
            if( '0' <= c && c <= '9' )
            {
                if( first < 0 )
                {
                    first = c - '0';
                }
                last = c - '0';
            }
        }

        sum += first * 10 + last;
    }

    return sum;
}

int64_t partB( char* filename )
{
    std::ifstream input( filename );
    std::string line;

    int64_t sum = 0;
    while( std::getline( input, line ) )
    {
        int64_t first = -1;
        int64_t last = -1;
        size_t pos = 0;
        while( pos < line.size() )
        {
            if( '0' <= line[ pos ] && line[ pos ] <= '9' )
            {
                if( first < 0 )
                {
                    first = line[ pos ] - '0';
                }
                last = line[ pos ] - '0';
            }
            else if( pos == line.find( "one", pos ) )
            {
                if( first < 0 )
                {
                    first = 1;
                }
                last = 1;
            }
            else if( pos == line.find( "two", pos ) )
            {
                if( first < 0 )
                {
                    first = 2;
                }
                last = 2;
            }
            else if( pos == line.find( "three", pos ) )
            {
                if( first < 0 )
                {
                    first = 3;
                }
                last = 3;
            }
            else if( pos == line.find( "four", pos ) )
            {
                if( first < 0 )
                {
                    first = 4;
                }
                last = 4;
            }
            else if( pos == line.find( "five", pos ) )
            {
                if( first < 0 )
                {
                    first = 5;
                }
                last = 5;
            }
            else if( pos == line.find( "six", pos ) )
            {
                if( first < 0 )
                {
                    first = 6;
                }
                last = 6;
            }
            else if( pos == line.find( "seven", pos ) )
            {
                if( first < 0 )
                {
                    first = 7;
                }
                last = 7;
            }
            else if( pos == line.find( "eight", pos ) )
            {
                if( first < 0 )
                {
                    first = 8;
                }
                last = 8;
            }
            else if( pos == line.find( "nine", pos ) )
            {
                if( first < 0 )
                {
                    first = 9;
                }
                last = 9;
            }
            pos += 1;
        }

        sum += first * 10 + last;
    }

    return sum;
}

int main( int argc, char** argv )
{
    std::cout << "Part a=" << partA( argv[ 1 ] ) << "\n";
    std::cout << "Part b=" << partB( argv[ 1 ] ) << "\n";

    return 0;
}
