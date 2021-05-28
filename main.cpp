#include <iostream>
#include <cmath>
#include "autoComplete.h"
#include <fstream>


int main() {
	autoComplete IMDB;
	autoComplete WORLD;

	std::ifstream in("IMDB.txt");

  	if(!in) {
    	std::cout << "Cannot open input file.\n";
    	return 1;
  	}

  	char Movie[255];

  	while(in) {
    	in.getline(Movie, 255);  // delim defaults to '\n'
    	if(in) IMDB.addIdentifier(Movie);

  	}

  	in.close();

  	std::ifstream _in("WORLD.txt");

  	if(!_in) {
    	std::cout << "Cannot open input file.\n";
    	return 1;
  	}

  	char World[255];

  	while(_in) {
    	_in.getline(World, 255);  // delim defaults to '\n'
    	if(_in) WORLD.addIdentifier(World);

  	}

  	_in.close();


  	std::cout << "IMDB dictionary size : " << IMDB.size() << '\n';
  	std::cout << "WORLD dictionary size : " << WORLD.size() << '\n';
	char pre[32] = "", mode;
	while(pre[0] != '.' || mode == '.'){
		std::cout << "Where to complete ? (W : World, I : IMDB) : ";
		std::cin >> mode;
		std::cout << "What to complete : ";
		std::cin >> pre;
		if(mode == 'I'){
			list List = IMDB.complete(pre);
			for(auto i = List.begin(); i != List.end(); ++i){
				std::cout << *i << '\n';
			}
		}
		else if(mode == 'W'){
			list List = WORLD.complete(pre);
			for(auto i = List.begin(); i != List.end(); ++i){
				std::cout << *i << '\n';
			}
		}

	}
}
