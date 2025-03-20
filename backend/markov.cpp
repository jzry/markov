#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <random>
#include <sstream>

using namespace std;

// Function to build the Markov chain model
map<string, vector<string> > buildMarkovChain(const string &filename, int order)
{
    map<string, vector<string> > markovChain;
    ifstream file(filename);
    string word;
    vector<string> buffer;

    if (!file.is_open())
    {
        cerr << "Error opening file: " << filename << endl;
        return markovChain; // Return empty chain
    }

    // Add every word from the file into the vector string buffer.
    while (file >> word)
    {
        buffer.push_back(word);

        // Once we reach the max number of words given by order, terminate.
        if (buffer.size() > order)
        {
            string prefix;

            // Add 100 words from the original buffer.
            for (int i = 0; i < order; ++i)
            {
                prefix += buffer[i];
                if (i < order - 1) prefix += " ";
            }

            markovChain[prefix].push_back(buffer[order]);
            buffer.erase(buffer.begin());
        }
    }

    file.close();
    return markovChain;
}

// Function to generate text from the Markov chain
string generateText(const map<string, vector<string> > &markovChain, const string &start, int length, int order)
{
    string current = start;
    string result = current;
    random_device rd;
    mt19937 gen(rd());

    for (int i = 0; i < length; ++i)
    {
        // While the strings are found in the hash map, continue printing them out.
        if (markovChain.find(current) != markovChain.end())
        {
            const vector<string> &suffixes = markovChain.at(current);

            // Gives a random uniform distribution for generating random phrases.
            uniform_int_distribution<> distrib(0, suffixes.size() - 1);

            // We begin generating from the start parameter.
            string nextWord = suffixes[distrib(gen)];
            result += " " + nextWord;

            // Update current prefix for the next iteration
            vector<string> currentWords;
            string temp;
            stringstream ss(result);

            while (ss >> temp)
            {
                currentWords.push_back(temp);
            }

            current = "";

            for (size_t j = currentWords.size() - order; j < currentWords.size(); ++j)
            {
                current += currentWords[j];
                if (j < currentWords.size() - 1) current += " ";
            }

        }
        else
        {
            break;
        }
    }
    return result;
}

int main(int argc, char **argv)
{
    if (argc > 2 || argc < 2)
    {
        cout << "ERROR: Proper syntax: ./a.out (filename.txt)." << endl;
        return 1;
    }

    string filename = argv[1];
    int order = 2; // Order of the Markov Chain (e.g., 2 for bigrams)
    int length = 100; // Number of words to generate
    string start = "This is"; // Starting prefix

    map<string, vector<string> > markovChain = buildMarkovChain(filename, order);

    // Error.
    if (markovChain.empty())
    {
        return 1;
    }

    string generatedText = generateText(markovChain, start, length, order);
    cout << generatedText << endl;

    return 0;
}