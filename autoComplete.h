#pragma once
#include <map> 
#include <vector>
#include <string>

struct root {
	std::map<char, root*> node;
};

typedef std::vector<std::string> list;

class autoComplete
{
private:
	root* addNode(root* Root, char value);
	void removeNode(root* Root, std::string identifier, short index);
	bool Find(std::string identifier);
	void traverse(root* Root, std::string prefix);
	short dictionary = 0;
	root* Root;
	list List;

public:
	autoComplete();
	void addIdentifier(std::string identifier);
	list complete(std::string identifier);
	void removeIdentifier(std::string identifier);
	bool find(std::string identifier);
	short size();
	void clear();
	~autoComplete();
};