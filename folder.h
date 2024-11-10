#include <bits/stdc++.h>
using namespace std;

/*
[TODO] - add file handling
[TODO] - rename to directory
*/
class Folder{
	string name;
	Folder *parent;
	vector<Folder*> subfolders;

	// returns true if subfolder was removed successfully or not
	bool removeFromSubfolder(string fname) {
		int i;
		for(i=0;i<subfolders.size();i++) {
			if(subfolders[i]->name == fname) {
				delete subfolders[i];
				break;
			}
		}
		if(i==subfolders.size()) return false;
		subfolders.erase(subfolders.begin()+i);

		return true;
	}

	// clears all subfolders
	void clearDir() {
		for(Folder *f: subfolders) delete f;
		subfolders.clear();
	}

public:
	// construct <used for root initialisation>
	Folder(string name) {
		this->name= name;
		parent=NULL;
	}

	// destructor <used to destory subfolders while deleting cur folder>
	~Folder() {
		for(Folder *f: subfolders) delete f;
	}

	// constructor for initialisation
	Folder(string name, Folder *par) {
		this->name= name;
		this->parent=par;
	}

	// returns true if folder was added successfully or not
	bool createSubFolder(vector<string> &path, int idx) {
		int n= path.size();
		// folder name cannot be '..'
		if(path[n-1]=="..") return false;
		
		pair<Folder*, bool> par = getSubFolder(path, idx, n-1);
		if(par.first==NULL) return false;
		if(par.second) return false;

		Folder *newFolder = new Folder(path[n-1], par.first);
		par.first->subfolders.push_back(newFolder);

		return true;
	}

	// returns true if folder(s) was removed successfully or not
	bool deleteSubFolder(vector<string> &path, int idx) {
		int n= path.size();
		// folder name cannot be '..'
		if(path[n-1]=="..") return false;
		
		pair<Folder*, bool> par = getSubFolder(path, idx, n-1);
		if(par.first==NULL) return false;
		if(par.second) return false;

		// delete all folders
		if(path[n-1] == "*") {
			par.first->clearDir();
		}else return par.first->removeFromSubfolder(path[n-1]);

		return true;
	}

	// returns subfolder from folder tree
	// 1. <child_folder, false> -> found single folder
	// 2. <child_folder, true> -> found multiple folders
	// 3. <NULL, false> -> not found
	pair<Folder*, bool> getSubFolder(vector<string> &path, int idx, int n) {
		if(idx==path.size() || idx==n) {
			return {this, false};
		}

		// go to parent folder
		if(path[idx]=="..") {
			if(this->parent == NULL) return {NULL, false};
			return this->parent->getSubFolder(path, idx+1, n);
		}

		bool isMultiple= false;
		Folder *ans=NULL;

		for(Folder *f: this->subfolders) {
			if(path[idx]=="*" || path[idx]==f->name) {
				pair<Folder*, bool> p = f->getSubFolder(path, idx+1, n);

				if(p.second) isMultiple= true;
				else if(p.first != NULL && ans != NULL) isMultiple= true;
				else if(p.first != NULL && ans==NULL) {
					ans= p.first;
				}
			}
		}

		return {ans, isMultiple};
	}

	string Name() {
		return this->name;
	}

	Folder* Parent() {
		return this->parent;
	}

	vector<Folder*> ListSubFolders() {
		return this->subfolders;
	}

};
