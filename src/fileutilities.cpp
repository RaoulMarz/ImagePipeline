#include <boost/filesystem.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <ctime>
#include <sys/stat.h>
#include <sys/types.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <errno.h>
#include "fileutilities.h"
#include "stringframework.h"
#include "stringmanipulation.h"

using namespace std;

pathobject::pathobject() : validpath(false) {

}

pathobject::pathobject(fs::path apath, bool valid) {
    thispath = apath;
    validpath = valid;
}

string fileutilities::includepathseparator(const string path) {
    string res = path;
    if (path.length() > 0) {

    }
    return res;
}

string fileutilities::addchildsubpath(const string path, const string subpath, bool checkExist, bool includeTrailing) {
    string res = "";
    if (path.length() <= 0)
        return res;
    int pathlen = path.length();
    if (pathlen >= 1) {
        string parentpath = path;
        string newpath;
        newpath += subpath;
        if (checkExist) {
            bool existSub = pathexists(newpath.c_str());
            if (existSub)
                res = newpath;
            else
                res = path;
        } else
            res = newpath;
        if ((res.length() > 0) && (includeTrailing)) {
            res = includepathseparator(res);
        }
    }
    return res;
}

string fileutilities::extractparentpath(const string path) {
    string res = path;
    if (path.length() > 0) {
        boost::filesystem::path p(path);
        const boost::filesystem::path dir = p.parent_path();
        res = dir.filename().string();
    }
    return res;
}

string fileutilities::extractfullpath(const string path) {
    string res = path;
    if (path.length() > 0) {
        boost::filesystem::path p(path);
        const boost::filesystem::path dir = p.remove_filename();
        res = dir.string();
    }
    return res;
}

string fileutilities::extractfilename(const string path) {
    string res = path;
    if (path.length() > 0) {
        boost::filesystem::path p(path);
        const boost::filesystem::path thisfile = p.filename();
        res = thisfile.string();
    }
    return res;
}

string fileutilities::removeextension(const string path, bool allExt) {
    string newstring = path;
    if (path.length() > 0) {
        string parent = extractparentpath(path);
        if (parent == path)
            parent = "";

        if (parent.length() > 0)
            newstring = parent + newstring;
    }
    return newstring;
}

bool fileutilities::pathexists(const string path) {
    DIR *dire = opendir(path.c_str());
    if (dire == NULL)
        return false;
    else {
        closedir(dire);
        return true;
    }
}

bool fileutilities::fileexists(const string path) {
    struct stat statbuf;

    int iret = stat(path.c_str(), &statbuf);
    if (iret < 0)
        return false;
    return true;
}

bool fileutilities::containspath(string& mainpath, string& pathtoFind) {
    if (pathtoFind.length() >= mainpath.length()) {
        return false;
    } else {
        if (mainpath.find(pathtoFind) < 0)
            return false;
        else
            return true;
    }
}

string fileutilities::getfullpath(const string path) {
    boost::filesystem::path p(path);
    const boost::filesystem::path dir = fs::complete(p);
    string res = dir.string();
    return res;
}

string fileutilities::readfilecontent(const string path) {
    ifstream in = ifstream(path, ios::binary);
    std::ostringstream ss;
    ss << in.rdbuf();
    auto s = ss.str();
    return s;
}

void fileutilities::createdirectory(string dir) {
    if (dir.length() > 0) {
        int res = mkdir(dir.c_str(), S_IRWXU);
        if (res < 0) {
            //sets errno to ??
        }
    }
}

void fileutilities::createfullpath(string dirpath, bool check) {
    int idx = 1;
    int pathcnt = 0;
    int pathlen = dirpath.length();
    string partdir;
    bool bPathSep = false;
    boost::filesystem::path p(dirpath);

    std::vector<boost::filesystem::path> v;
    for (auto&& x : boost::filesystem::directory_iterator(p))
        v.push_back(x.path());

    for (auto&& x : v) {
        if (pathexists(partdir.c_str()) == false) {
            createdirectory(partdir);
            pathcnt = 0;
        }
    }
}

std::unique_ptr<vector<string>> fileutilities::parsePathsList(string pathsText) {
    std::unique_ptr<vector < string>> pathComponents = nullptr; //make_unique<std::vector<std::string>>();
    if (pathsText.length() > 0) {
        pathComponents = stringframework::getTokensOnDelimiter(pathsText, ":");
    }
    return pathComponents;
}

std::unique_ptr<vector<pathobject>> fileutilities::returnvalidpathsinarray(std::vector<std::string>& setOfPaths) {
    std::unique_ptr<vector < pathobject>> pathArrObjects = make_unique<std::vector < pathobject >> ();
    if (pathArrObjects != nullptr) {
        for (string pathitem : setOfPaths) {
            pathArrObjects->push_back(pathobject(fs::path(pathitem), true));
        }
    }
    return pathArrObjects;
}

bool fileutilities::createfile(const string filepath, bool checkExist) {
    if (checkExist) {
        if (fileutilities::fileexists(filepath))
            return false;
    }
    FILE *fNew = fopen(filepath.c_str(), "ab+");
    if (fNew != NULL) {
#ifdef DEBUG
        printf("fileutilities::createfile, filepath=%s\n", filepath.c_str());
#endif
        fprintf(fNew, "%s", "");
        fclose(fNew);
        return true;
    }
    return false;
}

bool fileutilities::deletefile(const string filepath) {
    return false;
}

bool fileutilities::copyfile(const string frompath, const string destpath) {
    return false;
}
