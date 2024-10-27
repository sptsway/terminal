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

public:
	Folder(string name) {
		this->name= name;
		parent=NULL;
	}

	Folder(string name, Folder *par) {
		this->name= name;
		this->parent=par;
	}

	// returns if folder was added successfully of not
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
