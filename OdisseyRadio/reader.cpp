#include <iostream>
#include "reader.h"
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include "LinkedList.h"
#include <sstream>
#define log(x) std::cout<<x<<std::endl;

using namespace std;


string songName;
string artistName;
string songLength;
string songGenre;
string line;
int localId = 0;
LinkedList<std::string> myList;
vector<string> csvColumn;
string path = "/home/migue/Desktop/fma_metadata/raw_tracks.csv";
//std::string path2 = "/home/migue/Desktop/fma_small/checksums";


reader::reader()
{

}

    void reader::getIp(int id){
        ifstream ip(::path);
        getline(ip,line,'\n');
        log(line)

        while (true){
            getline(ip,line,',');
            log(line)
            stringstream xd(line);
            xd >> localId;
            if(localId==id){
                getline(ip,line,'\n');
                break;
            }
            else if (localId > id){
                log("No existe esta pieza")
                break;
            }
            else{
                getline(ip,line,'\n');
            }
        }
    }

    void reader::fillCsvColumn() {
        const char *mystart = line.c_str();
        bool instring{false};
        for (const char *p = mystart; *p; p++) {
            if (*p == '"')
                instring = !instring;
            else if (*p == ',' && !instring) {
                csvColumn.push_back(string(mystart, p - mystart));
                mystart = p + 1;
            }
        }
        csvColumn.push_back(string(mystart));

    }

    void reader::fillList(){
        for (auto &x: csvColumn)
            myList.addNodo(x);
        for (int i = 0; i < myList.getSize(); ++i) {
            //log(myList.get(i)->data)
        }

    }

    void reader::assignSongInfo(){
        artistName = myList.get(4)->data;
        songName = myList.get(36)->data;
        songLength = myList.get(21)->data;
        songGenre = myList.get(26)->data;
    }

    void reader::logMetadata() {
        std::cout<<"Artist Name: "<<artistName<<std::endl;
        std::cout<<"Song Name: "<<songName<<std::endl;
        std::cout<<"Song Length: "<<songLength<<std::endl;
        std::cout<<"Song Genre: "<<songGenre<<std::endl;
    }





int main() {
    reader myReader;
    myReader.getIp(20);
    myReader.fillCsvColumn();
    myReader.fillList();
    myReader.assignSongInfo();
    myReader.logMetadata();
    return 0;
}


