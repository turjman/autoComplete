#include <iostream>
#include <cmath>
#include "autoComplete.h"
#include <map>

autoComplete::autoComplete(){
	Root = new root;
}

root* autoComplete::addNode(root* Root, char value){
	if(Root->node.find(value) == Root->node.end()){
		Root->node[value] = new root;
		Root = Root->node[value];
	}
	else{
 		Root = Root->node[value];
	}
	return Root;
}

void autoComplete::addIdentifier(std::string identifier){
	if(!find(identifier)){
		int i = 0; root* Root = autoComplete::Root;
		for(i = 0; i < identifier.size() ; ++i){
			Root = addNode(Root, identifier[i]);
		//	std::cout << (Root == NULL ? "YES" : "NO");
		}
		addNode(Root, '.');
		autoComplete::dictionary++;
	}
}

bool autoComplete::Find(std::string identifier){
	int i = 0; root* Root = autoComplete::Root;
	for(i = 0; i < identifier.size() ; ++i){
		if(Root->node.find(identifier[i]) == Root->node.end())
			return 0;
		Root = Root->node[identifier[i]]; 
	}
	return 1;
}

bool autoComplete::find(std::string identifier){
	int i = 0; root* Root = autoComplete::Root;
	for(i = 0; i < identifier.size() ; ++i){
		if(Root->node.find(identifier[i]) == Root->node.end())
			return 0;
		Root = Root->node[identifier[i]]; 
	}
	return (Root->node.find('.') == Root->node.end() ? 0 : 1);
}

void autoComplete::removeNode(root* Root, std::string identifier, short index){
	if(index < identifier.size())
	removeNode(Root->node[identifier[index]], identifier, index + 1);
	else{
			delete Root->node['.'];
			Root->node.erase('.');
			return;
	}
	if(Root->node[identifier[index]]->node.size() == 0){
		delete Root->node[identifier[index]];
		Root->node.erase(identifier[index]);
	} 
}

void autoComplete::removeIdentifier(std::string identifier){
	if(find(identifier)){
		root* Root = autoComplete::Root;
		removeNode(Root, identifier, 0);
		autoComplete::dictionary--;
	}
}

list autoComplete::complete(std::string identifier){
	list List;
	if(Find(identifier)){
	//	autoComplete::List.clear();
		root* Root = autoComplete::Root;
		std::string prefix;
		prefix += identifier;
		if(prefix.size() != 0){
			int i = 0;
			for(i = 0; i < identifier.size() ; ++i){
				Root = Root->node[identifier[i]];
			}
		}
		traverse(Root, prefix);
		List = autoComplete::List;
		autoComplete::List.clear();
	}

	return List;
}

void autoComplete::traverse(root* Root, std::string prefix){
//	std::map<char, root*>::iterator i;
	for(auto i = (Root->node).begin(); i != (Root->node).end(); ++i){
	//	std::cout << i->first << ' ';
		prefix += i->first;
		traverse(i->second, prefix);
		if(i->first == '.'){
			prefix.pop_back();
			autoComplete::List.push_back(prefix);
			continue;
		}
		prefix.pop_back();
	}
}

void autoComplete::clear(){
	list List = complete("");
	int i = 0;
	for(i = 0; i < List.size(); ++i){
			removeIdentifier(List[i]);
		}
}

short autoComplete::size(){
	return autoComplete::dictionary;
}

autoComplete::~autoComplete(){
	clear();
	delete Root;
}

