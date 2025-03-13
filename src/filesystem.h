#include <bits/stdc++.h>
using namespace std;

/*

mkdir - a/b <relative path>
    | - /a/b/c <absolute path>

cd - a/b <relative path>
    | - /a/b/c <absolute path>
    | - a/\*\/b can have '*' in both relative and absolute path

ls - list all with current path

pwd - print current working directory

printdir - list all recursively from current path

printdisk - pretty print from root

*/

// assuming only Directories
class FileSystem{
	string rootName = "/";
	Directory *root, *cur;

	string prettyPrint(Directory *d, int tabs=0) {
		if(d==NULL) return "";

		stringstream out;

		string dname = d==root?"/":d->Name();
		for(int i=0;i<tabs;i++) out<<"|\t";
		out<<"-"<<" "<<dname; out<<"\n";
		
		vector<Directory*> subDirectories= d->ListSubDirs();
		for(Directory *subf: subDirectories) {
			string subout = prettyPrint(subf, tabs+1);
			out<<subout;
		}

		return out.str();
	}

public:
	FileSystem() {
		root = cur = new Directory("");
	}

	// true -> created directory
	// false -> error creating directory
	bool mkdir(string pathstr) {
		if(pathstr=="") return false;
		vector<string> path = utils::parsePaths(pathstr);

		bool noerr;
		// case of absolute path
		// indx0 will be root, so start from 1
		if(path[0]=="") noerr= root->createSubDirectory(path, 1); 
		else noerr = cur->createSubDirectory(path, 0);

		return noerr;
	}

	// true -> removed directory
	// false -> error removing directory
	// assumes deletes are recursive
	bool rm(string pathstr) {
		if(pathstr=="") return false;
		vector<string> path = utils::parsePaths(pathstr);

		bool noerr;
		// case of absolute path
		// indx0 will be root, so start from 1
		if(path[0]=="") noerr= root->deleteSubDirectory(path, 1); 
		else noerr = cur->deleteSubDirectory(path, 0);

		return noerr;
	}

	// true -> changed cur path
	// false -> error changing cur path
	bool cd(string pathstr) {
		if(pathstr=="") return false;
		vector<string> path = utils::parsePaths(pathstr);

		pair<Directory*, bool> updatedCur;
		// case of absolute path
		// indx0 will be root, so start from 1
		if(path[0]=="") updatedCur= root->getSubDirectory(path, 1, path.size()); 
		else updatedCur = cur->getSubDirectory(path, 0, path.size());

		if(updatedCur.first==NULL) return false;
		if(updatedCur.second) return false;
		cur = updatedCur.first;

		return true;
	}

	// print working directory
	void pwd() {
		Directory *d= cur;
		vector<string> out;
		while(d != root) {
			out.push_back(d->Name());
			d= d->Parent();
		}
		cout<<"/";
		for(int i=out.size()-1;i>=0;i--) cout<<out[i]<<"/";
		cout<<"\n";
	}

	// list all Directories
	void ls() {
		cout<<".\t";
		if(cur != root) cout<<"..\t";
		vector<Directory*> v = this->cur->ListSubDirs();
		for(Directory *d: v) cout<<d->Name()<<"\t";
		cout<<"\n";
	}

	// pretty print current directory
	void printdir() {
		cout<<this->prettyPrint(this->cur);
	}

	// pretty print root
	void printdisk() {
		cout<<this->prettyPrint(this->root);
	}

	string getCurrentDir() {
		if(cur == root) return rootName;
		return cur->Name();
	}

};
