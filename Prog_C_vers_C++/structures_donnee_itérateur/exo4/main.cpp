#include <vector>
#include <iostream>
#include <sstream>
#include <list>
#include <string>
#include <algorithm> // pour std::sort
#include <iterator>
using namespace std;



// Split https://zestedesavoir.com/tutoriels/822/la-programmation-en-c-moderne/le-debut-du-voyage/deployons-la-toute-puissance-des-conteneurs/#couper-une-cha%C3%AEne

// Une autre opération courante, et qui est fournie nativement dans d’autres langages comme Python ou C#, consiste à découper une chaîne de caractères selon un caractère donné. Ainsi, si je coupe la chaîne "Salut, ceci est une phrase." en fonction des espaces, j’obtiens en résultat ["Salut,", "ceci", "est", "une", "phrase.]

// Palindrome
// Vous devez tester si une chaîne de caractères est un palindrome, c’est-à-dire un mot pouvant être lu indifféremment de gauche à droite ou de droite à gauche. Un exemple : “kayak”.
// auto palindrome=[&x]() -> bool { }

void splitSentence(const int& sentence, const char splitCar){

}

int main()
{
//----PALINDROME---------
string myWord{"kayak"};
// fonction lambda en ne testant le mot que par moitié
auto isPalindrome = [](const string &word) -> bool { return equal(begin(word), begin(word) + word.size() / 2, rbegin(word));

// autre solution

auto isPalindrome = [](const string &word) { return all_of(begin(word), begin(word) + word.size(), [&word](char c) {
        static size_t i = 0; // Index pour parcourir la chaîne
        return c == word[word.size() - 1 - i++]; // Comparer début et fin
    });
};


};
// TEST
   if (isPalindrome(myWord)) {
       printf(" %s , est un palindrome \n", myWord.c_str());
    } else {
        printf(" %s , n'est un palindrome \n", myWord.c_str());
    }
    string myWord2{"maison"};
   if (isPalindrome(myWord2)) {
       printf(" %s , est un palindrome \n", myWord2.c_str());
    } else {
        printf(" %s , n'est un palindrome \n", myWord2.c_str());
    }

//----SPLIT---------

    string mySentence{"les carottes sont cuites !"};
    char const splitCar{' '};

   // Lambda pour découper une chaîne
    auto splitSentence = [](const string &sentence, char delimiter) -> vector<string> {
        vector<string> tokenList; //declaration tableau de tokens
        // auto start = sentence.begin();
        // auto end = sentence.end();

        while (begin(sentence) != end(sentence)) {
            auto pos = find(begin(sentence), end(sentence), delimiter);
            tokenList.emplace_back(begin(sentence), pos);
            begin(sentence) = (pos != end(sentence)) ? pos + 1 : end(sentence);
        }
        return tokenList;
    };

    // Découper la chaîne
    vector<string> result = splitSentence(mySentence, splitCar);

    // Afficher le résultat
    cout << "Résultat du découpage : ";
    for (const auto &word : result) {
        cout << "[" << word << "] ";
    }
    cout << endl;

    return 0;
}
