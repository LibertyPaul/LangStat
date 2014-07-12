#ifndef STUFF_HPP_INCLUDED
#define STUFF_HPP_INCLUDED

vector<CharProbability> getProbabilities(const vector<wchar_t> &text);

vector<wchar_t> mbVtowcV(const vector<char> &mbText);
vector<char> wcVtombV(const vector<wchar_t> &wcText);

string wc2string(const wchar_t wchar);


#endif // STUFF_HPP_INCLUDED
