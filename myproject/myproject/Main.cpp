#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <random> //for randomize the index of the string
#define MAXTEXTLINE 5754 //max text line 

bool HasUsed( std::vector<int>& seqOfIndexUsed, int index )
{
	for( const auto& i : seqOfIndexUsed )
	{
		if( index == i )
		{
			return true;
		}
	}
	return false;
}

bool IsCorrectWord( std::vector<std::string>& seqOfLetter, std::string input )
{
	for( const auto& s : seqOfLetter )
	{
		if( s == input )
		{
			return true;
		}
	}
	return false;
}

int CheckMatch( std::string& input, std::string& dict )
{
	int score = 0;
	std::vector<int> seqOfIndexUsed;
	for( size_t i = 0; i < input.size(); i++ )
	{
		for( size_t j = 0; j < dict.size(); j++ )
		{
			if( !HasUsed( seqOfIndexUsed, j ) )
			{
				if( dict[j] == input[i] && i == j )
				{
					score += 20;
					seqOfIndexUsed.push_back( j );
					break;
				}
				else if( dict[j] == input[i] )
				{
					score += 10;
					seqOfIndexUsed.push_back( j );
					break;
				}
			}
		}
	}

	return score;
}

int main()
{
	std::mt19937 rng( std::random_device{}() );
	std::uniform_int_distribution<int> dist( 0,MAXTEXTLINE - 1 );
	std::ifstream in( "sgb-words.txt" );
	std::vector<std::string> seqOfLetter;
	std::string buff;
	std::string input;

	while( !in.eof() )
	{
		std::getline( in, buff );
		seqOfLetter.emplace_back( buff );
	}
	buff = seqOfLetter[ dist( rng ) ];

	std::cout << "Write 5 letter word" << std::endl;
	int score = 0;
	while( score != 100 )
	{
		std::cout << std::endl;
		std::getline( std::cin,input );
		if( input.size() != 5 )
		{
			std::cout << "I said 5 letter word" << std::endl;
		}
		else
		{
			if( IsCorrectWord( seqOfLetter, input ) )
			{
				score = CheckMatch( input, buff );
				std::cout << "Score: " << score << std::endl;
			}
			else
			{
				std::cout << "Incorrect word" << std::endl;
			}
		}
	}
	std::cout << "Congratulation" << std::endl;

	return 0;
}