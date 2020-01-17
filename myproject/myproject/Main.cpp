#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <random> //for randomize the index of the string
#include <cctype> //for lowering word
#include <algorithm>

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

	for( size_t i = 0; i < std::min<size_t>( input.size(), dict.size() ); i++ )
	{
		if( input[i] == dict[i] )
		{
			score += 2;
			seqOfIndexUsed.push_back( i );
		}
	}

	for( size_t i = 0; i < input.size(); i++ )
	{
		for( size_t j = 0; j < dict.size(); j++ )
		{
			if( !HasUsed( seqOfIndexUsed, j ) && input[i] == dict[j] )
			{
				score += 1;
				seqOfIndexUsed.push_back( j );
				break;
			}
		}
	}

	return score;
}

void LoweringCase( std::string& s )
{
	for( char& c : s )
	{
		if( c >= 'A' && c <= 'Z' )
		{
			c = c + ( 'a' - 'A' );
		}
	}
}

int main()
{;
	std::ifstream in( "20k.txt" );
	std::vector<std::string> seqOfLetter;
	std::string buff;
	std::string input;

	while( !in.eof() )
	{
		std::getline( in, buff );
		seqOfLetter.emplace_back( buff );
	}
	in.close();

	std::mt19937 rng( std::random_device{}( ) );
	std::uniform_int_distribution<int> dist( 0, (seqOfLetter.size() / 20) - 1 ); //cuman ambil word pada line 0 sampai 999

	do
	{
		buff = seqOfLetter[dist( rng )];
	} while( buff.size() == 1 ); //tidak boleh hanya terdiri dari 1 huruf

	const int sizeOfGuessingWord = buff.size();
	bool ShowHint = true;

	int score = 0;
	bool isAnswerFalse = true;
	do
	{
		std::cout << std::endl;
		std::cout << "Write a word: ";
		std::getline( std::cin,input );
		LoweringCase( input );
		if( input.size() != sizeOfGuessingWord && ShowHint )
		{
			std::cout << "Hint: It contain " << sizeOfGuessingWord << " letter" << std::endl;
			ShowHint = false;
		}
		if( IsCorrectWord( seqOfLetter, input ) )
		{
			score = CheckMatch( input, buff );
			isAnswerFalse = score != ( buff.size() * 2 );
			if( isAnswerFalse && score > 0 )
			{
				std::cout << "Well, that's almost right, I give you: " << score << std::endl;
			}
			else if( score == 0 )
			{
				std::cout << "Sorry, but " << "\"" << input << "\"" << " is totally wrong" << std::endl;
			}
		}
		else
		{
			std::cout << input << "? Are you sure that word is really exist?" << std::endl;
		}
	} while( isAnswerFalse );
	std::cout << "Congratulation" << std::endl;

	return 0;
}