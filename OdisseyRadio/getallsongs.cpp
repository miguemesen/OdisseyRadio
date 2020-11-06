#include "getallsongs.h"

getallsongs::getallsongs()
{

}


void getallsongs::fetchSongs(int position)
{
    std::ifstream ip("/home/migue/Desktop/fma_metadata/raw_tracks2.csv");
    std::vector<std::vector<std::string>> parsedCsv;
    csvparse myParse;
    parsedCsv = myParse.readCSV(ip);

    while(song_list.size()!=5)
    {
        song *mySong = new song();
        mySong->artistName = parsedCsv[position][5];
        mySong->songLength = parsedCsv[position][21];
        mySong->songId = stoi(parsedCsv[position][0]);
        mySong->songName = parsedCsv[position][37];

        std::string id = std::to_string(mySong->songId);
        mySong->songPath = myRCsums.getSongPathById(id);

        song_list[mySong->songName] = mySong;
        std::cout<<song_list.size()<<std::endl;
        position+=1;
    }
}
