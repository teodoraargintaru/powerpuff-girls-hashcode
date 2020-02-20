#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <set>

using namespace std;

typedef struct Library{
    int index;
    map<int, int> booksMap;
    int signupD; //signup process
    int canShip;
};

vector<int> books;
int B, L, D;
map<float, Library> librariesScoreMap; //float - scorul bibliotecii
set<int> alreadyReadBooks;

int main() {
    ifstream in("d_tough_choices.txt");
    in>>B>>L>>D;

    for(int i = 0; i < B; i++){
        int score;
        in>>score;
        books.push_back(score); // books[i] = score
    }

    for(int i = 0; i < L ; i++){
        int booksNumber;
        Library lib;
        float score = 0;
        in>>booksNumber>>lib.signupD>>lib.canShip;
        lib.index = i;

        for(int j = 0; j < booksNumber; j++){
            int index;
            in>>index;
            lib.booksMap[books[index]] = index;
            score += (float) books[index];
        }

        float days = ((float) booksNumber / (float) lib.canShip) + (float) lib.signupD;
        score = score / days;
        librariesScoreMap[score] = lib;
    }

    in.close();

    int signedUpLibraries = 0;
    int Dcopy = D;
    for(auto it = librariesScoreMap.rbegin(); it != librariesScoreMap.rend(); ++it){
        Library lib = it->second; //value
        Dcopy -= lib.signupD;
        if(Dcopy < 0){
            break;
        }
        signedUpLibraries++;
    }

    ofstream out("out.txt");
    out<<signedUpLibraries<<endl;

    Dcopy = D;
    for(auto it = librariesScoreMap.rbegin(); it != librariesScoreMap.rend(); ++it){
        Library lib = it->second; //value
        out<<lib.index<<" ";
        vector<int> signedBooksIndex;
        Dcopy -= lib.signupD;
        int booksPerDay = 0;
        int DcopyLocal = Dcopy;

        for(auto it2 = lib.booksMap.rbegin(); it2 != lib.booksMap.rend(); ++it2){
            int bookIndex = it2->second;
            if(alreadyReadBooks.find(bookIndex) == alreadyReadBooks.end()){
                alreadyReadBooks.insert(bookIndex);
                signedBooksIndex.push_back(bookIndex);
                booksPerDay++;
                if(booksPerDay == lib.canShip){
                    booksPerDay = 0;
                    DcopyLocal--;
                    if(DcopyLocal <= 0){
                        break;
                    }
                }
            }
        }

        out<<signedBooksIndex.size()<<endl;

        for(int k = 0; k < signedBooksIndex.size(); k++){
            out<<signedBooksIndex[k]<<" ";
        }

        out<<endl;

    }
    out.close();
    return 0;
}
