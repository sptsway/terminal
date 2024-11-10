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
	fs->printfilesystem();

	return 0;
}
