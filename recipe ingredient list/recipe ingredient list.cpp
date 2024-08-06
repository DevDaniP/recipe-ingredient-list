#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_INGREDIENTS = 200;
string ingredients[MAX_INGREDIENTS];
int numIngredients;

int ReadIngredients(string ingredients[]);
void menu();

int main() {
    numIngredients = ReadIngredients(ingredients);
    menu();
    return 0;
}

int ReadIngredients(string ingredients[]) {
    int spices = 0;
    ifstream fin("pantry.txt");

    if (fin.is_open()) {
        while (spices < MAX_INGREDIENTS && getline(fin, ingredients[spices])) {
            spices++;
        }
        fin.close();
    }
    else {
        cout << "Error: File not found\n\n" << endl;
    }
    return spices;
}

void addIngredient(string newIngredient) {
    if (numIngredients < MAX_INGREDIENTS) {
        ingredients[numIngredients++] = newIngredient;
        cout << "Ingredient added successfully.\n\n";
    }
    else {
        cout << "Maximum ingredients reached. Cannot add more.\n\n";
    }
}

void removeIngredient(string deleteIngredient) {
    for (int i = 0; i < numIngredients; i++) {
        if (ingredients[i] == deleteIngredient) {
            for (int j = i; j < numIngredients - 1; j++) {
                ingredients[j] = ingredients[j + 1];
            }
            numIngredients--;
            cout << "Ingredient removed successfully.\n\n";
            return;
        }
    }
    cout << "Ingredient not found.\n\n";
}

void searchIngredient(string searchIngredient) {
    for (int i = 0; i < numIngredients; i++) {
        if (ingredients[i] == searchIngredient) {
            cout << "Ingredient found!\n\n";
            return;
        }
    }
    cout << "Ingredient not found.\n\n";
}

void editIngredient(string editIngredient) {
    for (int i = 0; i < numIngredients; i++) {
        if (ingredients[i] == editIngredient) {
            cout << "Please enter the new name of the ingredient: ";
            cin >> ingredients[i];
            cout << "Ingredient edited successfully.\n\n";
            return;
        }
    }
    cout << "Ingredient not found.\n\n";
}

void saveIngredientsToFile() {
    ofstream fout("pantry.txt");
    if (fout.is_open()) {
        for (int i = 0; i < numIngredients; i++) {
            fout << ingredients[i] << endl;
        }
        fout.close();
        cout << "Ingredients saved to file.\n\n";
    }
    else {
        cout << "Error: Unable to save ingredients to file.\n\n";
    }
}

void displayIngredients() {
    ifstream fin("pantry.txt");
    if (fin.is_open()) {
        string ingredient;
        while (getline(fin, ingredient)) {
            cout << ingredient << endl;
        }
        fin.close();
    }
    else {
        cout << "Error: Unable to open file.\n\n";
    }
}

void checkRecipeForIngredients(string recipeFile) {
    ifstream fin(recipeFile);
    if (fin.is_open()) {
        string recipe;
        while (getline(fin, recipe)) {
            size_t start_pos = recipe.find("<");
            size_t end_pos = recipe.find(">", start_pos);
            while (start_pos != string::npos && end_pos != string::npos) {
                string ingredient = recipe.substr(start_pos + 1, end_pos - start_pos - 1);
                addIngredient(ingredient);
                start_pos = recipe.find("<", end_pos);
                end_pos = recipe.find(">", start_pos);
            }
        }
        fin.close();
        cout << "Ingredients added to pantry.\n\n";
    }
    else {
        cout << "Error: Unable to open recipe file.\n\n";
    }
}

void menu() {
    string menuChoice = "";
    do {
        cout << "Please select from the following menu: " << endl;
        cout << "1. Add ingredient\n2. Remove Ingredient\n3. Search for an ingredient\n4. Edit Ingredient\n5. Save Ingredients to File\n6. Display Ingredients\n7. Check recipe for Ingredients\n8. Exit" << endl;
        cin >> menuChoice;

        switch (stoi(menuChoice)) {
        case 1: {
            cout << "Please enter the name of the ingredient you would like to add: ";
            string newIngredient;
            cin >> newIngredient;
            addIngredient(newIngredient);
            break;
        }
        case 2: {
            cout << "Please enter the name of the ingredient you would like to remove: ";
            string deleteIngredient;
            cin >> deleteIngredient;
            removeIngredient(deleteIngredient);
            break;
        }
        case 3: {
            cout << "Please enter the name of the ingredient you would like to search for: ";
            string findIngredient;
            cin >> findIngredient;
            searchIngredient(findIngredient);
            break;
        }
        case 4: {
            cout << "Please enter the name of the ingredient you would like to edit: ";
            string changeIngredient;
            cin >> changeIngredient;
            editIngredient(changeIngredient);
            break;
        }
        case 5: {
            saveIngredientsToFile();
            break;
        }
        case 6: {
            displayIngredients();
            break;
        }
        case 7: {
            cout << "Please enter the filename of a recipe.txt file to check for ingredients: ";
            string recipeFile;
            cin >> recipeFile;
            checkRecipeForIngredients(recipeFile);
            break;
        }
        case 8: {
            cout << "Exiting and saving pantry." << endl;
            saveIngredientsToFile();
            return;
        }

        }
    } while (menuChoice != "8");
}