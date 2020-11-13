#include "getallsongs.h"

getallsongs::getallsongs()
{

}

/**
 * @brief getallsongs::fetchPreviousSongs Takes a position and gets the previous 20 songs from the csv
 * @param position Position inside the csv
 */
void getallsongs::fetchPreviousSongs(int position)
{
    std::ifstream ip("/home/migue/Desktop/fma_metadata/raw_tracks1.csv");
    std::vector<std::vector<std::string>> parsedCsv;
    csvparse myParse;
    parsedCsv = myParse.readCSV(ip);

    while(song_list.size()!=20)
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

/**
 * @brief getallsongs::fetchSongs Takes a position and gets the next 20 songs from the csv
 * @param position Position inside the csv
 */
void getallsongs::fetchSongs(int position)
{
    std::ifstream ip("/home/migue/Desktop/fma_metadata/raw_tracks1.csv");
    std::vector<std::vector<std::string>> parsedCsv;
    csvparse myParse;
    parsedCsv = myParse.readCSV(ip);

    while(song_list.size()!=20)
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
