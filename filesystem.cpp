#include <bits/stdc++.h>
using namespace std;

#define int long long
#define fastIO ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define pii pair<long long, long long>
#define ff first
#define ss second
const int mod = 1e9+7;

/*
mkdir - a/b <relative path>
    | - /a/b/c <absolute path>
    | - can not have '*' while mkdir

cd - a/b <relative path>
    | - /a/b/c <absolute path>
    | - a/\*\/b can have '*' in both relative and absolute path

ls - list all with current path
[TODO]: lsAll - list all recursively from current path
[TODO]: lsFileSystem - pretty print from root
*/

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


// assuming only folders
class FileSystem{
	Folder *root, *cur;
public:
	FileSystem() {
		root = cur = new Folder("");
	}

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

	void ls() {
		vector<Folder*> v = this->cur->ListSubFolders();
		for(Folder *f: v) cout<<f->Name()<<"\t";
		cout<<"\n";
	}
};

/*

--- /  - a 
		    - c
     | - b
       		- d

*/

signed main() {
	fastIO;
	/*
	[TODO]: create an input stream
	*/

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

	return 0;
}
