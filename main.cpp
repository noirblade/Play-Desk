#include <iostream>
#include <fstream>

using namespace std;

const int variants = 15;
int allVariants[variants][21] = {
        {1, 0, 0,
      1, 1, 1, 0, 0,
      0, 1, 0, 0, 0,
      0, 0, 0, 0, 0,
         0, 0, 0},

        {0, 1, 0,
      0, 1, 1, 1, 0,
      0, 0, 1, 0, 0,
      0, 0, 0, 0, 0,
      0, 0, 0},

        {0, 0, 1,
      0, 0, 1, 1, 1,
      0, 0, 0, 1, 0,
      0, 0, 0, 0, 0,
         0, 0, 0},

        {0, 0, 0,
      0, 1, 0, 0, 0,
      1, 1, 1, 0, 0,
      0, 1, 0, 0, 0,
         0, 0, 0},

        {0, 0, 0,
      0, 0, 1, 0, 0,
      0, 1, 1, 1, 0,
      0, 0, 1, 0, 0,
         0, 0, 0},

        {0, 0, 0,
      0, 0, 0, 1, 0,
      0, 0, 1, 1, 1,
      0, 0, 0, 1, 0,
         0, 0, 0},

        {0, 0, 0,
      0, 0, 0, 0, 0,
      0, 1, 0, 0, 0,
      1, 1, 1, 0, 0,
         1, 0, 0},

        {0, 0, 0,
      0, 0, 0, 0, 0,
      0, 0, 1, 0, 0,
      0, 1, 1, 1, 0,
         0, 1, 0},

        {0, 0, 0,
      0, 0, 0, 0, 0,
      0, 0, 0, 1, 0,
      0, 0, 1, 1, 1,
         0, 0, 1},

        {1, 1, 1,
      0, 1, 1, 1, 0,
      0, 1, 1, 1, 0,
      0, 0, 0, 0, 0,
         0, 0, 0},

        {0, 0, 0,
      1, 1, 1, 0, 0,
      1, 1, 1, 0, 0,
      1, 1, 1, 0, 0,
         0, 0, 0},

        {0, 0, 0,
      0, 1, 1, 1, 0,
      0, 1, 1, 1, 0,
      0, 1, 1, 1, 0,
         0, 0, 0},

        {0, 0, 0,
      0, 0, 1, 1, 1,
      0, 0, 1, 1, 1,
      0, 0, 1, 1, 1,
         0, 0, 0},

        {0, 0, 0,
      0, 0, 0, 0, 0,
      0, 1, 1, 1, 0,
      0, 1, 1, 1, 0,
         1, 1, 1},

        {1, 1, 1,
      1, 1, 1, 1, 1,
      1, 1, 1, 1, 1,
      1, 1, 1, 1, 1,
         1, 1, 1},
};

int* applyVariant(int resultTable[], int index){
    for (int j = 0; j < 21; j++) {
        if (allVariants[index][j] == 1) {
            resultTable[j] = 1 - resultTable[j];
        }
    }
    return resultTable;
}

void printTable(int resultTable[]){
    cout << " ";
    for (int i = 0; i < 21; i++){
        cout << resultTable[i];
        if (i == 2 || i == 7 || i == 12 || i == 17){
            cout << endl;
            if (i == 17){
                cout << " ";
            }
        }
    }
    cout << endl;
}

bool checkValidSolution(int target[], int solution[]){
    for (int i = 0; i < 21; i++){
        if (target[i] != solution[i]){
            return false;
        }
    }
    return true;
}

int checkSolutions(int inputTable[], int resultTable[], int level, int steps){

    if (checkValidSolution(inputTable, resultTable)){
        //cout << "Found solution in " << steps << " steps" << endl;
        //printTable(resultTable);
        return 0;
    }
    if (level == variants){
        return steps;
    }

    steps = checkSolutions(inputTable, resultTable, level+1, steps);

    int tmpTable[21];
    for (int i = level; i < variants; i++){
        copy(resultTable, resultTable+21, tmpTable);
        applyVariant(resultTable, i);
        level++;
        int resSteps = checkSolutions(inputTable, resultTable, level, steps);
        copy(tmpTable, tmpTable+21, resultTable);
        if (steps > resSteps){
            steps = resSteps;
        }
    }
    return steps+1;
}

int main() {

    int inputTable[21];
    int resultTable[21];

    ifstream inputFile ("game.inp");
    if (inputFile.is_open())
    {
        int numTables = 0;
        inputFile >> numTables;

        for (int i = 0; i < numTables; i++){
            for (int j = 0; j < 21; j++){
                inputFile >> inputTable[j];
                resultTable[j] = 0;
            }
            cout << "Final steps " << checkSolutions(inputTable, resultTable, 0, 0) << endl;
        }
        inputFile.close();
    }
    return 0;
}