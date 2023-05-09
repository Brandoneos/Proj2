#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>
#include <cctype>
#include <cstring>
#include <sstream>
#include <math.h>
#include <algorithm>
#include <map>
#include <set>


using namespace std;

// INSERTS GIVEN HELPERS CODE BELOW - DO NOT REMOVE
#include "helpers.cpp"
struct musicInfo {
    string name;
    set<string> artists;
    map<int, string> songs;

};
bool operator<(const musicInfo& lhs, const musicInfo& rhs)
{
      return lhs.name < rhs.name;
}
string toLowerCase(string input){ 
    cout << input[0] << endl;

    for (int x = 0; x < input.size(); x++) {
        input[x] = tolower(input[x]);
    }
    return input;
}

int main() {

    // musicInfo musicInfo1 = {};
    // musicInfo1.name = "Test1";
    // musicInfo1.artists.insert("Bob1");
    // musicInfo1.artists.insert("Bob");
    // musicInfo1.songs.insert(pair<int,string>(1,"song1"));
    // set<string> allArtists;
    // allArtists.insert("Bob");
    // allArtists.insert(musicInfo1.artists.begin(),musicInfo1.artists.end());
    // cout << "Set size: " << allArtists.size() << endl;
    string s2 = "WXYZ";
  
    // using transform() function and ::tolower in STL
    s2 = toLowerCase(s2);
    cout << s2 << endl;
    return 0;
}