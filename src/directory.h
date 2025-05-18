#include <bits/stdc++.h>
using namespace std;

class Directory{
private:
	string name;
	Directory *parent;
	vector<Directory*> subDirs;
	bool isFile;

	// returns true if subDirectory was removed successfully or not
	bool removeFromSubDirectory(string dname) {
		int i;
		for(i=0;i<subDirs.size();i++) {
			if(subDirs[i]->name == dname) {
				delete subDirs[i];
				break;
			}
		}
		if(i==subDirs.size()) return false;
		subDirs.erase(subDirs.begin()+i);

		return true;
	}

	// clears all subDirs
	void clearDir() {
		for(Directory *f: subDirs) delete f;
		subDirs.clear();
	}

	// return true if sub directory with given name is present
	bool isSubDirPresent(string dir) {
		for(Directory *f: subDirs) if(f->name == dir) return true;
		return false;
	}

public:
	// constructor <used for root initialisation>
	Directory(string name) {
		this->name= name;
		parent=NULL;
		isFile= false;
	}

	// destructor <used to destory subDirs while deleting cur Directory>
	~Directory() {
		for(Directory *f: subDirs) delete f;
	}

	// constructor for initialisation
	Directory(string name, Directory *par, bool isFile) {
		this->name = name;
		this->parent = par;
		this->isFile = isFile;
	}

	// returns true if Directory was added successfully or not
	// agnostic of file/folder
	bool createSubDirectory(vector<string> &path, int idx, bool isFile) {
		int n= path.size();
		
		// Directory name cannot be '..' or '.'
		if(path[n-1]=="..") return false;
		else if(path[n-1]==".") return false;
		
		pair<Directory*, bool> par = getSubDirectory(path, idx, n-1);
		if(par.first==NULL) return false;
		if(par.second) return false;

		if(par.first->isSubDirPresent(path[n-1])) return false;

		Directory *newDirectory = new Directory(path[n-1], par.first, isFile);
		par.first->subDirs.push_back(newDirectory);

		return true;
	}

	// returns true if Directory(s) was removed successfully or not
	// agnostic of file/folder
	bool deleteSubDirectory(vector<string> &path, int idx) {
		int n= path.size();
		// Directory name cannot be '..' or '.'
		if(path[n-1]=="..") return false;
		else if(path[n-1]==".") return false;
		
		pair<Directory*, bool> par = getSubDirectory(path, idx, n-1);
		if(par.first==NULL) return false;
		if(par.second) return false;

		// delete all Directorys
		if(path[n-1] == "*") {
			par.first->clearDir();
		}else return par.first->removeFromSubDirectory(path[n-1]);

		return true;
	}

	// ########## input
	// <idx,n> states the range to be traversed in the path
	// assumes path.size()>=n
	//
	// ########## output
	// returns subDirectory from Directory tree
	// 1. <child_Directory, false> -> found single Directory
	// 2. <child_Directory, true> -> found multiple Directorys
	// 3. <NULL, false> -> not found
	//
	// assumes crawling(cd) the directories, so it does takes into account file
	pair<Directory*, bool> getSubDirectory(vector<string> &path, int idx, int n) {
		if(idx==path.size() || idx==n) {
			if(this->isFile) return {NULL, false};
			return {this, false};
		}

		// go to parent Directory
		if(path[idx]=="..") {
			if(this->parent == NULL) return {NULL, false};
			return this->parent->getSubDirectory(path, idx+1, n);
		}else if(path[idx]==".") {
			return this->getSubDirectory(path, idx+1, n);
		}

		bool isMultiple= false;
		Directory *ans=NULL;

		for(Directory *f: this->subDirs) {
			
			// skip if its a file
			if(f->isFile) continue;

			if(path[idx]=="*" || path[idx]==f->name) {
				pair<Directory*, bool> p = f->getSubDirectory(path, idx+1, n);

				if(p.second) isMultiple= true;
				else if(p.first != NULL && ans != NULL) isMultiple= true;
				else if(p.first != NULL && ans==NULL) {
					ans= p.first;
				}
			}
		}

		return {ans, isMultiple};
	}

	// does the directory contain the file
	bool constainsFile(string fname) {
		for(Directory *dir: subDirs) {
			if(dir->name ==fname && dir->isFile) return true;
		}
		return false;
	}


/*
Getters
*/
	// Name getter
	string Name() {
		return this->name;
	}

	// Parent
	Directory* Parent() {
		return this->parent;
	}

	// ListSubDirs getter
	vector<Directory*> ListSubDirs() {
		return this->subDirs;
	}

	// IsAFile getter
	bool IsAFile() {
		return this->isFile;
	}

};
