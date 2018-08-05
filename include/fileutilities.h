#ifndef _XFILEROUTINES_H
#define	_XFILEROUTINES_H

#include <string>
#include <vector>
#include <memory>
#include <array>
#include <boost/filesystem.hpp>

using namespace std;
namespace fs = boost::filesystem;

class pathobject {
public:
    fs::path thispath;
    bool validpath;

    pathobject();
    pathobject(fs::path apath, bool valid);
};

class fileutilities {
public:
    static string includepathseparator(const string path);
    static string addchildsubpath(const string path, const string subpath, bool checkExist, bool includeTrailing);
    static string assemblepath(const string origpath, const string filename);
    static string extractparentpath(const string path);
    static string extractfullpath(const string path);
    static string extractfilename(const string path);
    static string removeextension(const string path, bool allExt = true);

    static string removetrailingpath(const string path, int removecount = 1);
    static string getfullpath(const string path);
    static bool pathexists(string path);
    static bool fileexists(const string path);
    static bool containspath(string& mainpath, string& pathtoFind);

    static bool createfile(const string filepath, bool checkExist = true);
    static bool deletefile(const string filepath);
    static bool copyfile(const string frompath, const string destpath);
    static string readfilecontent(const string path);

    static void createdirectory(string dir);
    static void createfullpath(string dirpath, bool check = false);
    static std::unique_ptr<vector<string>> parsePathsList(string pathsText);
    static std::unique_ptr<vector<pathobject>> returnvalidpathsinarray(std::vector<std::string>& setOfPaths);
private:

};

#endif	/* _XXFILEROUTINES_H */
