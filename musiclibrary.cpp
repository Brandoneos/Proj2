/// TODO Update File Header
///
/// Assignment details and provided code are created and
/// owned by Adam T Koehler, PhD - Copyright 2023.
/// University of Illinois Chicago - CS 251 Spring 2023

/*
AUTHOR: BRANDON KIM
PROGRAM OVERVIEW: This program allows the user to input 
music files to create a music library where they can
load, look at stats, export, and search for music.

*/

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
 // INSERTS GIVEN HELPERS CODE ABOVE - DO NOT REMOVE

//
// NOTE TO STUDENTS:
// You may use the functions in the helpers file,
// but you may not modify the file or its contents in any way whatsoever.
//

//
// STUDENT CODE MAY GO BELOW THIS LINE
//

//Struct for the object of a record / musicInfo
struct musicInfo {
  string name;
  set < string > artists;
  map < int, string > songs;

};
//function returning a set of strings. This function takes 2 sets, the main library one and a created one,
// and makes a new set which contains the union of the 2 sets, intersection, or difference. Checks for all nine 
// possibilities which are the 3 types of set functions(union, difference, intersection)and what search type the user gave
set < string > checkSet(string searchType1, string id, map < string, string > library, set < string > given) {
  //id is for whether the set given is union,inter,differ type of set.
  set < string > returnSet;
  if (id == "u") {

    if (searchType1 == "album") {

      for (auto name: library) {

        for (string ob1: given) {

          if (ob1 == name.first) {

            returnSet.insert(name.second);

          }
        }
      }
    } else if (searchType1 == "artist") { //unknown yet
      //library has name, artists
      size_t found;

      for (auto name: library) {
        for (string ob1: given) {

          if (name.first.find(ob1) != string::npos) {
            returnSet.insert(name.second);

          }
        }

      }

    } else if (searchType1 == "song") {
      size_t found;
      for (auto name: library) {
        for (string ob1: given) {

          if (name.first.find(ob1) != string::npos) {
            returnSet.insert(name.second);

          }
        }

      }
    }

  } else if (id == "i") {
    size_t found;
    int counter = 0;
    if (searchType1 == "album") {
      size_t found;
      int counter = 0;
      for (auto name: library) {
        for (string ob1: given) {
          if (name.first.find(ob1) != string::npos) {
            counter++;
          }

          if (counter == given.size() && counter != 0) {
            returnSet.insert(name.second);
          }
          counter = 0;
        }

      }
      counter = 0;

    } else if (searchType1 == "artist") {
      size_t found;
      int counter = 0;
      for (auto name: library) {
        for (string ob1: given) {
          if (name.first.find(ob1) != string::npos) {
            counter++;
          }
        }

        if (counter == given.size() && counter != 0) {
          returnSet.insert(name.second);
        }

      }
      counter = 0;

    } else if (searchType1 == "song") {
      size_t found;
      int counter = 0;
      for (auto name: library) {
        for (string ob1: given) {
          if (name.first.find(ob1) != string::npos) {
            counter++;
          }
        }

        if (counter == given.size() && counter != 0) {
          returnSet.insert(name.second);
        }

      }
      counter = 0;
    }

  } else if (id == "d") {
    size_t found;
    if (searchType1 == "album") {
      size_t found;
      int counter = 0;
      string send1;
      if (given.size() == 0) {
        for (auto name: library) {
          returnSet.insert(name.second);
        }

      } else {
        for (auto name: library) {
          send1 = name.second;

          for (string ob1: given) {

            if (name.first.find(ob1) != string::npos) {
              counter++;
            }

            if (counter == 1 && counter != 0) {
              counter = 0;
            } else {

              returnSet.insert(send1);
            }
          }

        }

      }

    } else if (searchType1 == "artist") {
      size_t found;
      int counter = 0;
      string send1;
      for (auto name: library) {
        send1 = name.second;
        for (string ob1: given) {
          if (name.first.find(ob1) != string::npos) {
            counter++;
          }
        }

      }

      if (counter == 1 && counter != 0) {

      } else {
        returnSet.insert(send1);
      }

    } else if (searchType1 == "song") {

      size_t found;
      int counter = 0;
      string send1;
      for (auto name: library) {
        send1 = name.second;
        for (string ob1: given) {
          if (name.first.find(ob1) != string::npos) {
            counter++;
          }
        }

      }

      if (counter == 1 && counter != 0) {

      } else {
        returnSet.insert(send1);
      }
    }

  } else {
    //error
    cout << "Error encountered" << endl;
  }
  return returnSet;

}
//My own function to lower case an entire string
string toLowerCase(string input) {

  for (int x = 0; x < input.size(); x++) {
    input[x] = tolower(input[x]);
  }
  return input;
}
//a function returning a set of strings which takes in 3 sets
// each with the strings given by the user but which set it goes in depends on
// the modifier symbol the user gave
// This function searches through the entire database loaded by the user.
set < string > searchLibraryFunc(string searchType, map < int, musicInfo > map2, set < string > setOfTermsUnion1, set < string > setOfTermsInter1,
  set < string > setOfTermsDiffer1) {
  map < string, string > libraryMap; //map for sending into other functions, has title as the 
  // value and keys as either the artists,songs, or titles
  set < string > returnSet;
  string item1;
  set < string > funcSet; //set used for intersection of resSet and resSetI
  set < string > endSet; // resulting set containing record titles.
  //6 sets for the result of the union,difference,and intersection functions in checkSet()
  set < string > resSet;
  set < string > resSetI;
  set < string > resSetD;
  set < string > resSet1;
  set < string > resSetI1;
  set < string > resSetD1;
  if (searchType == "album") {
    for (int x = 0; x < map2.size(); x++) {
      libraryMap.insert(pair < string, string > (toLowerCase(map2[x].name), toLowerCase(map2[x].name)));

      //need to only set library for one record;
    }

    resSet1 = checkSet("album", "u", libraryMap, setOfTermsUnion1);
    resSetI1 = checkSet("album", "i", libraryMap, setOfTermsInter1);
    resSetD1 = checkSet("album", "d", libraryMap, setOfTermsDiffer1);
    resSet.insert(resSet1.begin(), resSet1.end());
    resSetI.insert(resSetI1.begin(), resSetI1.end());
    resSetD.insert(resSetD1.begin(), resSetD1.end());

  } else if (searchType == "artist") {

    for (int x = 0; x < map2.size(); x++) {
      for (string artist1: map2[x].artists) {

        libraryMap.insert(pair < string, string > (toLowerCase(artist1), toLowerCase(map2[x].name)));

      }
      resSet1 = checkSet("artist", "u", libraryMap, setOfTermsUnion1);
      resSetI1 = checkSet("artist", "i", libraryMap, setOfTermsInter1);
      resSetD1 = checkSet("artist", "d", libraryMap, setOfTermsDiffer1);
      resSet.insert(resSet1.begin(), resSet1.end());
      resSetI.insert(resSetI1.begin(), resSetI1.end());
      resSetD.insert(resSetD1.begin(), resSetD1.end());

      libraryMap.clear();
    }

    //resSet intersect with resSetI, then difference with resSetD to get final set.

  } else if (searchType == "song") {

    for (int x = 0; x < map2.size(); x++) {
      for (auto song1: map2[x].songs) {

        libraryMap.insert(pair < string, string > (toLowerCase(song1.second), toLowerCase(map2[x].name)));
        //make sure to send multiple words for spaces

      }

      resSet1 = checkSet("song", "u", libraryMap, setOfTermsUnion1);
      resSetI1 = checkSet("song", "i", libraryMap, setOfTermsInter1);
      resSetD1 = checkSet("song", "d", libraryMap, setOfTermsDiffer1);
      resSet.insert(resSet1.begin(), resSet1.end());
      resSetI.insert(resSetI1.begin(), resSetI1.end());
      resSetD.insert(resSetD1.begin(), resSetD1.end());

      libraryMap.clear();
    }

  } else {
    cout << "Error while searching Library" << endl;
  }
  if (searchType == "album" || searchType == "artist" || searchType == "song") {
    if (resSetI.empty()) {
      funcSet = resSet;
    } else {
      set_intersection(resSet.begin(), resSet.end(), resSetI.begin(), resSetI.end(), std::inserter(funcSet, funcSet.begin()));
    }

    set_intersection(funcSet.begin(), funcSet.end(), resSetD.begin(), resSetD.end(), std::inserter(endSet, endSet.begin()));
  } //resSet intersect with resSetI, then intersect with resSetD to get final set.

  //got main set. Main Intersect with Union set. 
  //Union set intersected with Inter set.
  return endSet;
}
//command to search through the sent database of information, using modifiers given in remains1
//This then prints out a set based on the conditions given by user input.
void searchCommand(string remains1, map < int, musicInfo > map1) { //make sure to have space between symbol and new terms, 
  //can have multiple terms but only of the same type
  size_t spaceFinder = remains1.find_first_of(" ");
  int count1 = 0;
  set < string > setOfTermsUnion; //3 sets of strings modified put in each
  set < string > setOfTermsInter;
  set < string > setOfTermsDiffer;
  string type1;
  string terms; //used for first term.
  string oneTerm;
  string additionalTerms; //only used if user inputs additional terms
  if (spaceFinder != string::npos) { //album AlbumName
    type1 = remains1.substr(0, spaceFinder);

    terms = remains1.substr(spaceFinder + 1, remains1.size() - spaceFinder - 1);
    spaceFinder = terms.find_first_of(" ");
    oneTerm = terms.substr(0, spaceFinder);
    if (!(type1 == "album" || type1 == "artist" || type1 == "song")) {
      cout << "No results found." << endl;
    }

    while (spaceFinder != string::npos) {

      if (type1 == "album" || type1 == "artist" || type1 == "song") {

        if (oneTerm[0] == '+') {

          oneTerm = oneTerm.substr(1, oneTerm.size() - 1);
          setOfTermsInter.insert(toLowerCase(oneTerm));
        } else if (oneTerm[0] == '-') {
          oneTerm = oneTerm.substr(1, oneTerm.size() - 1);
          setOfTermsDiffer.insert(toLowerCase(oneTerm));

        } else {
          //Union the term and put it in set as it is.
          setOfTermsUnion.insert(toLowerCase(oneTerm));
        }

        terms = terms.substr(spaceFinder + 1, terms.size() - spaceFinder - 1);

        //
      } else {
        cout << "No results found." << endl; //incorrect search type

      }

      spaceFinder = terms.find_first_of(" ");
      oneTerm = terms.substr(0, spaceFinder);
    }

    if (oneTerm[0] == '+') {

      oneTerm = oneTerm.substr(1, oneTerm.size() - 1);
      setOfTermsInter.insert(toLowerCase(oneTerm));
    } else if (oneTerm[0] == '-') {
      oneTerm = oneTerm.substr(1, oneTerm.size() - 1);
      setOfTermsDiffer.insert(toLowerCase(oneTerm));
    } else {
      //Union the term and put it in set as it is.
      setOfTermsUnion.insert(toLowerCase(oneTerm));
    }

    //do code to search.
  } else {
    cout << "Error: Search terms cannot be empty." << endl;
    cout << "No results found." << endl;
    count1 = 1;
  }

  // return that set and print it out
  if (count1 == 0 && (type1 == "album" || type1 == "artist" || type1 == "song")) {
    set < string > returnSet;
    returnSet = searchLibraryFunc(type1, map1, setOfTermsUnion, setOfTermsInter, setOfTermsDiffer);
    if (returnSet.empty()) {

      cout << "No results found." << endl;
    } else {
      cout << "Your search results exist in the following albums:" << endl;
      for (string ob: returnSet) {
        ob[0] = toupper(ob[0]);
        cout << ob << endl;
      }
    }

  } else {
    // cout << "No results found." << endl;
  }
  cout << endl;

}
//This function makes a new file with the current music library, which is map1
void exportCommand(string remains1, map < int, musicInfo > map1) {
  //remains here is the name of the file exporting to.
  ofstream output1;
  output1.open(remains1);
  if (!output1.is_open()) {
    cout << "Error. Couldn't open file" << endl;
  } else {
    for (int x = 0; x < map1.size(); x++) {
      output1 << map1[x].name << endl;
      for (string artists1: map1[x].artists) {
        output1 << "" << artists1 << endl;
        for (int y = 1; y < (map1[x].songs.size() + 1); y++) {

          if (y < 10) {
            output1 << "0" << y << " " << map1[x].songs[y] << endl;
          } else {
            output1 << y << " " << map1[x].songs[y] << endl;
          }

        }
        output1 << map1[x].name << endl;
      }

    }

  }

  output1.close();
}
//This function returns an empty map, which the music library is set equal to when cleared.
map < int, musicInfo > clearCommand() {
  map < int, musicInfo > emptyMap = {};
  return emptyMap;

}
//This function prints out the info on the music library, -d dumping more info.
void statsCommand(string remains1, map < int, musicInfo > map1) {

  set < string > allArtists;
  int totalSongCount = 0;

  for (int x = 0; x < map1.size(); x++) {
    allArtists.insert(map1[x].artists.begin(), map1[x].artists.end());
    totalSongCount += map1[x].songs.size();
  }

  cout << "Overall Music Library Stats" << endl;
  cout << "===========================" << endl;
  //print out numbers
  cout << "Total Records: " << map1.size() << endl;
  cout << "Total Unique Artists: " << allArtists.size() << endl;
  cout << "Total Songs: " << totalSongCount << endl;
  cout << endl;

  if (remains1 == "-d") {
    cout << "Your Current Music Library Includes" << endl;
    cout << "===================================" << endl;
    for (int x = 0; x < map1.size(); x++) {
      cout << map1[x].name << endl;
      for (string artists1: map1[x].artists) {
        cout << " " << artists1 << endl;
        for (int y = 1; y < (map1[x].songs.size() + 1); y++) {

          if (y < 10) {
            cout << "   0" << y << " " << map1[x].songs[y] << endl;
          } else {
            cout << "   " << y << " " << map1[x].songs[y] << endl;
          }

        }
      }

    }

    cout << endl;
  }

}
//This function loads in a file which contains information that is added onto the current music library.
// This function returns a map because it updates the current library each time.
map < int, musicInfo > loadCommand(string remains1, map < int, musicInfo > origMap) { //return a set of structs
  map < int, musicInfo > allRecords = origMap;
  int recordCount = allRecords.size();
  ifstream filestream1;
  string fileContent;
  int songNumber;
  string actualSong;
  size_t space;
  int artistCount;
  musicInfo musicInfo1;
  int mode = 0; // 0 = Album Title, 1 = Album Artist, 2 = Album songs
  int previousLineWasLastSong = 1;
  string previousRecordName;

  filestream1.open(remains1);
  if (remains1 == "") {
    // cout << "Error. Could not open music library file - musicdatabase.txt " << remains1 << endl;
  } else if (!filestream1.is_open()) {
    cout << "Error: Could not open music library file - " << remains1 << endl;
  } else {

    while (!filestream1.eof()) {
      getline(filestream1, fileContent);

      if (fileContent == "") {
        break;
      }

      if (!(musicInfo1.name == fileContent) && mode == 0) {
        musicInfo1 = {};
        previousRecordName = fileContent;
        musicInfo1.name = fileContent;
        mode = 1;
        // cout << "First Record Name: "<< fileContent << endl;
      } else if (mode == 1 && !(isdigit(fileContent.at(0)))) {
        musicInfo1.artists.insert(fileContent);
        // cout << "Artist Name here: " << fileContent << endl;
        // cout << "Artist Count: " << artistCount << endl;
        artistCount++; // Unnecessary
      } else if (isdigit(fileContent.at(0))) {
        mode = 2;
        space = fileContent.find_first_of(" ");
        if (space != string::npos) {
          songNumber = stoi(fileContent.substr(0, space));
          actualSong = fileContent.substr(space + 1, fileContent.size() - space - 1);
          musicInfo1.songs.insert(pair < int, string > (songNumber, actualSong));
          // cout << "Artist songs here: "<< fileContent << endl;
        } else {
          cout << "Error encountered." << endl;
        }
        //parse string to get the name of the song.
      } else if (previousRecordName == fileContent) {
        mode = 0;
        //End of Record;
        // cout << "End of Record: " << musicInfo1.name << endl;
        
        allRecords.insert(pair < int, musicInfo > (recordCount, musicInfo1));
        // cout << "Record Count: " << recordCount << endl;
        recordCount++;
        artistCount = 0;
      } else {
        cout << "Error" << endl;
      }

    }

  }

  return allRecords;
}
//Main
int main() {
  string userEntry;
  string command, remains;

  // TODO: Declare any necessary variables for the music libary
  map < int, musicInfo > mapOfRecords;
  // Display welcome message once per program execution
  cout << "Welcome to the Music Library App" << endl;
  cout << "--------------------------------" << endl;

  // Stay in menu until exit command
  do {
    cout << endl;
    cout << "Enter a command (help for help): " << endl;
    getline(cin, userEntry);
    cout << endl;

    // Split the user entry into two pieces
    splitFirstWord(userEntry, command, remains);
    tolower(command);

    // take an action, one per iteration, based on the command
    if (command == "help") {
      helpCommand();
    } else if (command == "clear") {
      mapOfRecords = clearCommand();
    } else if (command == "export") {
      exportCommand(remains, mapOfRecords);
    } else if (command == "load") {
      mapOfRecords = loadCommand(remains, mapOfRecords);
      //Returned a map of integer keys with struct values.

    } else if (command == "stats") {
      statsCommand(remains, mapOfRecords);
      //Printed Correct Information

    } else if (command == "search") {
      // TODO
      searchCommand(remains, mapOfRecords);
    }

  } while (command != "exit");

  cout << "Thank you for using the Music Library App" << endl;
  return 0;
}