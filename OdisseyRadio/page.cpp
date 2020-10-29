#include "page.h"
#define log(x) std::cout<<x<<std::endl;

std::vector<page> mySongs[5];

page::page()
{

}

void page::something(){
    song song1;
    song1.artistName="this is song1";
    song song2;
    song2.artistName="this is song2";
    song song3;
    song3.artistName="this is song3";
    song song4;
    song4.artistName="this is song4";
    song song5;
    song5.artistName="this is song5";

    std::vector<song> newVector(5);
    newVector[0]=song1;
    newVector[1]=song2;
    newVector[2]=song3;
    newVector[3]=song4;
    newVector[4]=song5;

    for(int i=0; i<5;i++)
    {
        log(newVector[i].artistName)
    }
    log('\n');
}


//int main(){
//    song song1;
//    song1.artistName="this is song1";
//    song song2;
//    song1.artistName="this is song2";
//    song song3;
//    song1.artistName="this is song3";
//    song song4;
//    song1.artistName="this is song4";
//    song song5;
//    song1.artistName="this is song5";

//    std::vector<song> newVector;
//    newVector[0]=song1;
//    newVector[1]=song2;
//    newVector[2]=song3;
//    newVector[3]=song4;
//    newVector[4]=song5;

//    for(int i=0; i<newVector.size();i++)
//    {
//        log(newVector[i].artistName)
//    }
//    log('\n');


//}
