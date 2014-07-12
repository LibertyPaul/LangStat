#include <iostream>
#include <fstream>
#include <stdexcept>
#include <set>
#include <vector>
#include <algorithm>


using namespace std;
#include "CharProbability.hpp"
#include "stuff.hpp"


int main(){
	setlocale(LC_ALL, "");
	ofstream langStatFile("LangStat", ios_base::out | ios_base::trunc | ios_base::binary);
	if(!langStatFile)
		throw runtime_error("Cant open destination file");

	multiset<wchar_t> symbols;
	set<wchar_t> symbolList;

	uint64_t filesSize = 0;

	for(uint16_t i = 1; i <= 6; ++i){
		ifstream text("books/book" + to_string(i) + ".txt", ios_base::in | ios_base::binary);
		if(!text)
			throw runtime_error("Cant open book #" + to_string(i));
		text.seekg(0, text.end);
		size_t textSize = text.tellg();
		text.seekg(0, text.beg);

		filesSize += textSize;

		vector<char> mbText(textSize);
		text.read(&mbText[0], textSize);

		vector<wchar_t> wText = mbVtowcV(mbText);

		for(auto wchar : wText){
			symbols.insert(wchar);
			symbolList.insert(wchar);
		}
	}

	vector<CharProbability> langStat;
	for(auto wchar : symbolList)
		langStat.push_back(CharProbability(wchar, static_cast<double>(symbols.count(wchar)) / filesSize));

	sort(langStat.rbegin(), langStat.rend(), [](const CharProbability &rhs, const CharProbability &lhs){
		return rhs.probability < lhs.probability;
	});

	for(auto &cp : langStat){
		langStatFile << cp;
		cp.show(cout);
	}



}
