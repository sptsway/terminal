#include <bits/stdc++.h>
using namespace std;

class utils{
public:
	static vector<string> parsePaths(string pathstr) {
		string str;
		stringstream ss(pathstr);
		vector<string> path;
		
		while(getline(ss, str, '/')) {
			path.push_back(str);
		}
		return path;
	}
};
