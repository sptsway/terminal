#include <bits/stdc++.h>
using namespace std;

class utils{
public:
	static vector<string> parsePaths(string pathstr) {
		return splitString(pathstr, '/');
	}

	static vector<string> splitString(string str, char del) {
		string curstr;
		vector<string> v;
		stringstream ss(str);
		
		while(getline(ss, curstr, del)) {
			v.push_back(curstr);
		}

		return v;
	}

	static string truncateTrailingSpace(string str) {
		int x= str.length()-1;
		while(x>=0) {
			if(str[x]!=' ') break;
			x--;
		}
		return string(str, 0, x+1);
	}

};
