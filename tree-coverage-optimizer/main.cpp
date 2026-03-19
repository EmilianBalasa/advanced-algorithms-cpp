#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <regex>

using namespace std;

struct TreeVertex {
    int data;
    TreeVertex* leftChild;
    TreeVertex* rightChild;

    TreeVertex(int val = 0) : data(val), leftChild(nullptr), rightChild(nullptr) {}
    ~TreeVertex() {
        delete leftChild;
        delete rightChild;
    }
};

class TreeProcessor {
private:
    vector<string> tokens;
    int guardianCount;

    void tokenizeInput(const string& rawInput) {
        tokens.clear();
        regex pattern(R"(\w+|null)");
        sregex_iterator iter(rawInput.begin(), rawInput.end(), pattern);
        sregex_iterator end;

        while (iter != end) {
            tokens.push_back(iter->str());
            ++iter;
        }
    }

    TreeVertex* constructTreeFromTokens() {
        if (tokens.empty() || tokens[0] == "null") {
            return nullptr;
        }

        TreeVertex* rootNode = new TreeVertex(0);
        deque<TreeVertex*> nodeQueue;
        nodeQueue.push_back(rootNode);

        size_t tokenIndex = 1;

        while (!nodeQueue.empty() && tokenIndex < tokens.size()) {
            TreeVertex* currentVertex = nodeQueue.front();
            nodeQueue.pop_front();

            if (tokenIndex < tokens.size()) {
                if (tokens[tokenIndex] != "null") {
                    currentVertex->leftChild = new TreeVertex(0);
                    nodeQueue.push_back(currentVertex->leftChild);
                }
                tokenIndex++;
            }

            if (tokenIndex < tokens.size()) {
                if (tokens[tokenIndex] != "null") {
                    currentVertex->rightChild = new TreeVertex(0);
                    nodeQueue.push_back(currentVertex->rightChild);
                }
                tokenIndex++;
            }
        }

        return rootNode;
    }

    int deployGuardians(TreeVertex* vertex) {
        if (vertex == nullptr) {
            return 1; // State: covered by parent
        }

        int leftSubtreeState = deployGuardians(vertex->leftChild);
        int rightSubtreeState = deployGuardians(vertex->rightChild);

        if (leftSubtreeState == 0 || rightSubtreeState == 0) {
            guardianCount++;
            return 2; // State: has guardian
        }

        if (leftSubtreeState == 2 || rightSubtreeState == 2) {
            return 1;
        }

        return 0;
    }

public:
    TreeProcessor() : guardianCount(0) {}

    int processTreeInput(const string& input) {
        guardianCount = 0;
        tokenizeInput(input);
        TreeVertex* treeRoot = constructTreeFromTokens();

        if (treeRoot == nullptr) {
            return 0;
        }

        int rootState = deployGuardians(treeRoot);
        if (rootState == 0) {
            guardianCount++;
        }

        int result = guardianCount;
        delete treeRoot;
        return result;
    }
};

int main() {
    string inputLine;
    getline(cin, inputLine);

    TreeProcessor processor;
    int result = processor.processTreeInput(inputLine);

    cout << result << endl;

    return 0;
}