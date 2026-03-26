#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <unordered_set>
#include <vector>
#include <algorithm>

using namespace std;

class TextParser
{
private:
    set<string> terms;
    map<string,int> documents;
    unordered_set<string> stopwords;

public:

    void loadStopwords()
    {
        ifstream file("stopwordlist.txt");
        string word;

        while(file >> word)
        {
            stopwords.insert(word);
        }

        file.close();
    }

    string toLower(string w)
    {
        for(char &c : w)
            c = tolower(c);
        return w;
    }

    bool containsDigit(const string &w)
    {
        for(char c : w)
        {
            if(isdigit(c))
                return true;
        }
        return false;
    }

    vector<string> splitText(const string &line)
    {
        vector<string> tokens;
        string word = "";

        for(char c : line)
        {
            if(isalpha(c))
            {
                word += c;
            }
            else
            {
                if(!word.empty())
                {
                    tokens.push_back(word);
                    word.clear();
                }
            }
        }

        if(!word.empty())
            tokens.push_back(word);

        return tokens;
    }

    void processLine(const string &line)
    {
        vector<string> words = splitText(line);

        for(string w : words)
        {
            if(containsDigit(w))
                continue;

            w = toLower(w);

            if(stopwords.find(w) == stopwords.end())
                terms.insert(w);
        }
    }

    void parseFile(const string &filename)
    {
        ifstream file(filename);

        if(!file)
        {
            cout << "Cannot open file: " << filename << endl;
            return;
        }

        string line;
        bool readingText = false;

        while(getline(file,line))
        {
            if(line.find("<DOCNO>") != string::npos)
            {
                int start = line.find("<DOCNO>") + 7;
                int end = line.find("</DOCNO>");

                string doc = line.substr(start,end-start);

                int dash = doc.find("-");
                int id = stoi(doc.substr(dash+1));

                documents[doc] = id;
            }

            if(line.find("<TEXT>") != string::npos)
            {
                readingText = true;
                continue;
            }

            if(line.find("</TEXT>") != string::npos)
            {
                readingText = false;
                continue;
            }

            if(readingText)
                processLine(line);
        }

        file.close();
    }

    void parseDataset()
    {
        for(int i=1;i<16;i++)
        {
            string file = "ft911/ft911_" + to_string(i);
            parseFile(file);
        }
    }

    void writeOutput()
    {
        ofstream out("parser_output.txt");

        map<string,int> termDict;
        int id = 1;

        for(const string &t : terms)
        {
            termDict[t] = id;
            id++;
        }

        for(auto &t : termDict)
            out << t.first << "\t" << t.second << endl;

        out << endl;

        for(auto &d : documents)
            out << d.first << "\t" << d.second << endl;

        out.close();
    }
};

int main()
{
    TextParser parser;

    parser.loadStopwords();
    parser.parseDataset();
    parser.writeOutput();

    cout << "Parser finished. Output written to parser_output.txt" << endl;

    return 0;
}