#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

/* convert word to lowercase */
void makeLower(string &w)
{
    for(char &c : w)
        c = tolower(c);
}

/* check if token contains digit */
bool hasDigit(const string &w)
{
    for(char c : w)
        if(isdigit(c))
            return true;
    return false;
}

/* load stopwords */
void loadStopwords(unordered_set<string> &stop)
{
    ifstream file("stopwordlist.txt");
    string w;

    while(file >> w)
        stop.insert(w);

    file.close();
}

/* extract tokens from a line manually */
void extractWords(
        const string &line,
        unordered_set<string> &termSet,
        const unordered_set<string> &stop)
{
    string word = "";

    for(size_t i=0;i<=line.size();i++)
    {
        char c = (i < line.size()) ? line[i] : ' ';

        if(isalpha(c))
        {
            word += c;
        }
        else
        {
            if(!word.empty())
            {
                makeLower(word);

                if(!hasDigit(word) && stop.find(word)==stop.end())
                    termSet.insert(word);

                word.clear();
            }
        }
    }
}

/* read dataset file */
void parseFile(
        const string &filename,
        unordered_set<string> &termSet,
        map<string,int> &docDict,
        const unordered_set<string> &stop)
{
    ifstream file(filename);

    if(!file)
    {
        cout << "Error opening " << filename << endl;
        return;
    }

    string line;
    bool insideText = false;

    while(getline(file,line))
    {
        if(line.find("<DOCNO>") != string::npos)
        {
            int s = line.find("<DOCNO>") + 7;
            int e = line.find("</DOCNO>");

            string doc = line.substr(s,e-s);

            int dash = doc.find("-");
            int id = stoi(doc.substr(dash+1));

            docDict[doc] = id;
        }

        if(line.find("<TEXT>") != string::npos)
        {
            insideText = true;
            continue;
        }

        if(line.find("</TEXT>") != string::npos)
        {
            insideText = false;
            continue;
        }

        if(insideText)
            extractWords(line,termSet,stop);
    }

    file.close();
}

/* write output file */
void writeOutput(
        const map<string,int> &termDict,
        const map<string,int> &docDict)
{
    ofstream out("parser_output.txt");

    for(auto &t : termDict)
        out << t.first << "\t" << t.second << endl;

    out << endl;

    for(auto &d : docDict)
        out << d.first << "\t" << d.second << endl;

    out.close();
}

int main()
{
    unordered_set<string> termSet;
    unordered_set<string> stopwords;
    map<string,int> documentDictionary;

    loadStopwords(stopwords);

    for(int i=1;i<16;i++)
    {
        string file = "ft911/ft911_" + to_string(i);
        parseFile(file,termSet,documentDictionary,stopwords);
    }

    /* move terms to vector then sort */
    vector<string> words(termSet.begin(),termSet.end());
    sort(words.begin(),words.end());

    map<string,int> termDictionary;
    int id = 1;

    for(string &w : words)
    {
        termDictionary[w] = id;
        id++;
    }

    writeOutput(termDictionary,documentDictionary);

    cout << "Parsing completed successfully." << endl;

    return 0;
}