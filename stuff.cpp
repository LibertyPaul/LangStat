#include <vector>
#include <stdexcept>
#include <algorithm>
#include <set>
#include <cmath>//abs()

using namespace std;
#include "CharProbability.hpp"
#include "stuff.hpp"




vector<CharProbability> getProbabilities(const vector<wchar_t> &text){
	uint64_t length = text.size();
	vector<CharProbability> stats;
	for(auto ch : text){
		bool isExist = false;
		for(auto &charStat : stats)
			if(charStat.ch == ch){
				charStat.probability += 1. / length;
				isExist = true;
				break;
			}
		if(isExist == false)
			stats.emplace_back(ch, 1. / length);
	}
	return stats;
}


vector<wchar_t> mbVtowcV(const vector<char> &mbText){
	mblen(nullptr, 0);
	mbtowc(nullptr, nullptr, 0);//reset

	vector<wchar_t> wText;

	size_t pos = 0;
	while(pos < mbText.size()){
		int currentMultiByteCharLength = mblen(&mbText[pos], MB_CUR_MAX);
		if(currentMultiByteCharLength == -1)
			throw runtime_error("Not valid multi byte sequence fount at " + to_string(pos));
		if(currentMultiByteCharLength == 0)
			currentMultiByteCharLength = sizeof('\0');//костыль

		wchar_t t;

		int res = mbtowc(&t, &mbText[pos], currentMultiByteCharLength);
		if(res == -1)
			throw runtime_error("Not valid multi byte sequence fount at " + to_string(pos));

		pos += currentMultiByteCharLength;
		wText.push_back(t);
	}

	return wText;
}

vector<char> wcVtombV(const vector<wchar_t> &wcText){
	mblen(nullptr, 0);
	mbtowc(nullptr, nullptr, 0);//reset

	vector<char> mbText;

	char buffer[MB_CUR_MAX];
	for(auto wchar : wcText){
		int length = wctomb(buffer, wchar);
		if(length == -1)
			throw runtime_error("there is no character correspondence");

		for(int i = 0; i < length; ++i)
			mbText.push_back(buffer[i]);
	}

	return mbText;
}



string wc2string(const wchar_t wchar){
	mblen(nullptr, 0);
	mbtowc(nullptr, nullptr, 0);//reset

	char buffer[MB_CUR_MAX];
	int length = wctomb(buffer, wchar);
	if(length == -1)
		throw runtime_error("there is no character correspondence");

	string res;

	for(uint16_t i = 0; i < length; ++i)
		res.push_back(buffer[i]);

	return res;
}






