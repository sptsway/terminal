#include <bits/stdc++.h>
#include "utils.h"
#include "folder.h"
#include "fileSystem.h"
using namespace std;

#define int long long
#define fastIO ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define pii pair<long long, long long>
#define ff first
#define ss second
const int mod = 1e9+7;

/*
--- / - a 
    |   | - a/c
    | - b
    |   | - b/d
*/
void example() {
	FileSystem *fs = new FileSystem();

	fs->ls();
	fs->mkdir("/a");
	fs->mkdir("b");
	fs->ls();
	fs->cd("a");
	fs->pwd();
	cout<<"@\n";
	fs->mkdir("c");
	fs->ls();
	fs->mkdir("/b/d");
	fs->cd("*"); fs->pwd();
	fs->cd(".."); fs->pwd();
	fs->cd(".."); fs->pwd();
	fs->cd(".."); fs->pwd();
	fs->cd("b"); fs->pwd();
	fs->ls();
	fs->printdisk();
}

// readme outputs documentation on how to use terminal
void readme() {
	cout<<"################### how to use terminal❓ ###################\n";
	int functions =0;
	string readme = "\n" + to_string(++functions) + ". help : to output documentation\n";
		readme+= to_string(++functions) + ". mkdir <param path of folder> : make a directory\n";
		readme+= to_string(++functions) + ". cd <param path of folder> : change path to the specified directory\n";
		readme+= to_string(++functions) + ". ls : list directory\n";
		readme+= to_string(++functions) + ". pwd - print current working directory\n";
		readme+= to_string(++functions) + ". printdir : print all folders with in the current directory\n";
		readme+= to_string(++functions) + ". printdisk : print all folders from root directory\n";
	cout<<readme<<"\n";
	cout<<"################### ----------------- ###################\n";
	
}

void printDirHead(FileSystem *fs) {
	cout<<"wtf 1.1> ";
}

bool interact(string inp, FileSystem *fs) {
	inp=utils::truncateTrailingSpace(inp);

	auto wrongIn = [&] {
		cout<<"❌invalid input, use \"help\" to get documentation\n";
	};

	vector<string> inpv = utils::splitString(inp, ' ');

	switch(inpv.size()) {
	case 1:
		if(inpv[0] == "help") readme();
		else if(inpv[0] == "ls") fs->ls();
		else if(inpv[0] == "pwd") fs->pwd();
		else if(inpv[0] == "printdir") fs->printdir();
		else if(inpv[0] == "printdisk") fs->printdisk();
		else if(inpv[0] == "exit") return false;
		else wrongIn();
		break;
	case 2:
		if(inpv[0]=="cd") {
			if(fs->cd(inpv[1])) cout<<"✅ changed directory\n";
			else cout<<"❌ error changing directory\n";
		}
		else if(inpv[0]=="mkdir") {
			if(fs->mkdir(inpv[1])) cout<<"✅ created directory\n";
			else cout<<"❌ error creating directory\n";
		}else wrongIn();
		break;
	default:
		wrongIn();
	}

	return true;
}

signed main() {
	fastIO;

	FileSystem *fs = new FileSystem();
	cout<<"\n\n☺☺☺☺☺☺☺☺[WTF]☺☺☺☺☺☺☺☺\nwelcome to funny-terminal\n\n";
	readme(); cout.flush();
	printDirHead(fs); cout.flush();
	
	while(true) {
		
		string inp;
		getline(cin, inp);
		if(!interact(inp, fs)) break;
		printDirHead(fs);
		cout.flush();
	}

	return 0;
}
