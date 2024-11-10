#include <bits/stdc++.h>
using namespace std;

/*

mkdir - a/b <relative path>
    | - /a/b/c <absolute path>
    | - can not have '*' while mkdir

cd - a/b <relative path>
    | - /a/b/c <absolute path>
    | - a/\*\/b can have '*' in both relative and absolute path

ls - list all with current path

printdir - list all recursively from current path

printfilesystem - pretty print from root

*/

// assuming only folders
class FileSystem{
	Folder *root, *cur;

	string prettyPrint(Folder *f, int tabs=0) {
		if(f==NULL) return "";

		stringstream out;

		string fname = f==root?"/":f->Name();
		for(int i=0;i<tabs;i++) out<<"|\t";
		out<<"-"<<" "<<fname; out<<"\n";
		
		vector<Folder*> subfolders= f->ListSubFolders();
		for(Folder *subf: subfolders) {
			string subout = prettyPrint(subf, tabs+1);
			out<<subout;
		}

		return out.str();
	}

public:
	FileSystem() {
		root = cur = new Folder("");
	}

	// true -> created directory
	// false -> error creating directory
	bool mkdir(string pathstr) {
		if(pathstr=="") return false;
		vector<string> path = utils::parsePaths(pathstr);

		bool noerr;
		// case of absolute path
		// indx0 will be root, so start from 1
		if(path[0]=="") noerr= root->createSubFolder(path, 1); 
		else noerr = cur->createSubFolder(path, 0);

		return noerr;
	}

	// true -> changed cur path
	// false -> error changing cur path
	bool cd(string pathstr) {
		if(pathstr=="") return false;
		vector<string> path = utils::parsePaths(pathstr);

		pair<Folder*, bool> updatedCur;
		// case of absolute path
		// indx0 will be root, so start from 1
		if(path[0]=="") updatedCur= root->getSubFolder(path, 1, path.size()); 
		else updatedCur = cur->getSubFolder(path, 0, path.size());

		if(updatedCur.first==NULL) return false;
		if(updatedCur.second) return false;
		cur = updatedCur.first;

		return true;
	}

	// print working directory
	void pwd() {
		Folder *f= cur;
		vector<string> out;
		while(f != root) {
			out.push_back(f->Name());
			f= f->Parent();
		}
		cout<<"/";
		for(int i=out.size()-1;i>=0;i--) cout<<out[i]<<"/";
		cout<<"\n";
	}

	// list all folders
	void ls() {
		vector<Folder*> v = this->cur->ListSubFolders();
		for(Folder *f: v) cout<<f->Name()<<"\t";
		cout<<"\n";
	}

	// pretty print current directory
	void printdir() {
		cout<<this->prettyPrint(this->cur);
	}

	// pretty print root
	void printfilesystem() {
		cout<<this->prettyPrint(this->root);
	}

};
