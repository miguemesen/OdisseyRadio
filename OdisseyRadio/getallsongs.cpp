#include "getallsongs.h"

getallsongs::getallsongs()
{

}


void getallsongs::fetchPreviousSongs(int position)
{
    std::ifstream ip("/home/migue/Desktop/fma_metadata/raw_tracks1.csv");
    std::vector<std::vector<std::string>> parsedCsv;
    csvparse myParse;
    parsedCsv = myParse.readCSV(ip);

    while(song_list.size()!=12)
    {
        song *mySong = new song();
        mySong->artistName = parsedCsv[position][1];
        mySong->songId = stoi(parsedCsv[position][0]);
        mySong->songName = parsedCsv[position][2];

        std::string id = std::to_string(mySong->songId);
        mySong->songPath = myRCsums.getSongPathById(id);

        song_list[mySong->songName] = mySong;
        position-=1;
    }
}


void getallsongs::fetchSongs(int position)
{
    std::ifstream ip("/home/migue/Desktop/fma_metadata/raw_tracks1.csv");
    std::vector<std::vector<std::string>> parsedCsv;
    csvparse myParse;
    parsedCsv = myParse.readCSV(ip);

    while(song_list.size()!=12)
    {
        song *mySong = new song();
        mySong->artistName = parsedCsv[position][1];
        mySong->songId = stoi(parsedCsv[position][0]);
        mySong->songName = parsedCsv[position][2];

        std::string id = std::to_string(mySong->songId);
        mySong->songPath = myRCsums.getSongPathById(id);

        song_list[mySong->songName] = mySong;
        position+=1;
    }
}
