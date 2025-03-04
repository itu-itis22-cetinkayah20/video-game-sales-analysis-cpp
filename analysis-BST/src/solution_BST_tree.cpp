// Hakan Çetinkaya
// 150200114



#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <string.h>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stack>
#include <iomanip>
#include <chrono>
#include <random>
using namespace std;
using namespace std::chrono;

int yearr = 1980;
vector<string> publisherNames;
/////////////////// Publisher ///////////////////
class publisher
{
public:
    string name;
    float na_sales;
    float eu_sales;
    float others_sales;
};

/////////////////// Node ///////////////////
class Node
{
public:
    publisher key;
    Node *parent, *left, *right;

    Node(publisher);
    ~Node();
};

Node::Node(publisher key)
{
    this->key = key;
    this->parent = NULL;
    this->left = NULL;
    this->right = NULL;
}

Node::~Node()
{
    
}

/////////////////// BST-Tree ///////////////////
class BST_tree
{
private:
    Node *root;

public:
    publisher *best_seller[3];
    stack<string> tree_deep_stack;

    Node *get_root();

    Node *BST_insert(Node *root, Node *ptr);
    void insertValue(vector<string>);
    void find_best_seller();
    Node *search(Node *root, string key); 

    BST_tree();
    ~BST_tree();
};

void print_best_sellers(int year, publisher *temp_publisher[3])
{
    cout.precision(5);
    cout << "End of the " + to_string(year) + " Year" << endl;
    cout << "Best seller in North America: " + temp_publisher[0]->name + " - " << temp_publisher[0]->na_sales << " million" << endl;
    cout << "Best seller in Europe: " + temp_publisher[1]->name + " - " << temp_publisher[1]->eu_sales << " million" << endl;
    cout << "Best seller rest of the World: " + temp_publisher[2]->name + " - " << temp_publisher[2]->others_sales << " million" << endl;
}

BST_tree generate_BST_tree_from_csv(string file_name)
{
    BST_tree temp_BSTtree; 
    ifstream file(file_name); 


    string line;
    
    getline(file, line); 

    int current_decade_end = 1990; 

    auto total_insert_time = 0;
    while (getline(file, line)) 
    {
        stringstream ss(line); 
        vector<string> values; 
        string temp;

        while (getline(ss, temp, ',')) 
        {
            values.push_back(temp); 
        }

        int year = stoi(values[2]); 

        if (year <= current_decade_end) 
        {
            auto start_insert = chrono::high_resolution_clock::now();
            temp_BSTtree.insertValue(values); 
            auto end_insert = chrono::high_resolution_clock::now();
            auto duration_insertion = chrono::duration_cast<chrono::microseconds>(end_insert - start_insert);
            total_insert_time += duration_insertion.count();
            yearr = year; 
        }
        else 
        {
            temp_BSTtree.find_best_seller(); 
            current_decade_end += 10; 
            auto start_insert = chrono::high_resolution_clock::now();
            temp_BSTtree.insertValue(values); 
            auto end_insert = chrono::high_resolution_clock::now();
            auto duration_insertion = chrono::duration_cast<chrono::microseconds>(end_insert - start_insert);
            total_insert_time += duration_insertion.count();
            yearr = year; 
        }

        
        publisherNames.push_back(values[3]);
    }
    temp_BSTtree.find_best_seller();
    cout << "Time taken to insert all data into BST: " << total_insert_time << " µs" << endl;
    return temp_BSTtree; 
}

struct VideoGame
{
    string name;
    string platform;
    int year_of_release;
    string publisher;
    double na_sales;
    double eu_sales;
    double other_sales;
};

bool compareByName(const VideoGame &a, const VideoGame &b)
{
    return a.publisher < b.publisher;
}

vector<VideoGame> sortGamesByName(const string &inputFile)
{
    ifstream file(inputFile);

    string line;
    vector<VideoGame> games;
    getline(file, line);

    while (getline(file, line))
    {
        stringstream ss(line);
        VideoGame game;
        string temp;

        getline(ss, game.name, ',');
        getline(ss, game.platform, ',');
        getline(ss, temp, ',');
        game.year_of_release = stoi(temp);
        getline(ss, game.publisher, ',');
        getline(ss, temp, ',');
        game.na_sales = stod(temp);
        getline(ss, temp, ',');
        game.eu_sales = stod(temp);
        getline(ss, temp, ',');
        game.other_sales = stod(temp);

        games.push_back(game);
    }
    file.close();

    sort(games.begin(), games.end(), compareByName);

    return games;
}

BST_tree generate_BST_tree_from_csv_with_name(const string &inputFile)
{
    vector<VideoGame> sortedGames = sortGamesByName(inputFile);
    BST_tree temp_BSTtree;

    auto total_insert_time = 0;
    for (const auto &game : sortedGames)
    {
        vector<string> values = {
            game.name,
            game.platform,
            to_string(game.year_of_release),
            game.publisher,
            to_string(game.na_sales),
            to_string(game.eu_sales),
            to_string(game.other_sales)
        };

        auto start_insert = chrono::high_resolution_clock::now();
        temp_BSTtree.insertValue(values);
        auto end_insert = chrono::high_resolution_clock::now();
        auto duration_insertion = chrono::duration_cast<chrono::microseconds>(end_insert - start_insert);
        total_insert_time += duration_insertion.count();

        publisherNames.push_back(game.publisher);
    }

    cout << "Time taken to insert all data into BST with ordered game names: " << total_insert_time << " µs" << endl;
    return temp_BSTtree;
}

////////////////////////////////////////////
//----------------- MAIN -----------------//
////////////////////////////////////////////
int main(int argc, char *argv[])
{
    string fname = argv[1];
    BST_tree BSTtree = generate_BST_tree_from_csv(fname);
    
    // Perform 50 random searches and calculate the average time
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, publisherNames.size() - 1);

    auto start = high_resolution_clock::now();
    for (int i = 0; i < 50; ++i)
    {
        string key = publisherNames[dis(gen)];
        Node *result = BSTtree.search(BSTtree.get_root(), key);
        
    }
    auto end = high_resolution_clock::now();
    double avg_search_time = duration_cast<nanoseconds>(end - start).count() / 50.0;
    cout << "Average time for 50 random searches: " << avg_search_time << " ns" << endl;

    // Uncomment the following code for part F

    BST_tree BSTtree2 = generate_BST_tree_from_csv_with_name(fname);

    random_device rd2;
    mt19937 gen2(rd());
    uniform_int_distribution<> dis2(0, publisherNames.size() - 1);

    auto start2 = high_resolution_clock::now();
    for (int i = 0; i < 50; ++i)
    {
        string key2 = publisherNames[dis(gen)];
        Node *result2 = BSTtree2.search(BSTtree2.get_root(), key2);
    }
    auto end2 = high_resolution_clock::now();
    double avg_search_time2 = duration_cast<nanoseconds>(end2 - start2).count() / 50.0;
    cout << "Average time for 50 random searches in BST for ordered game names: " << avg_search_time2 << " ns" << endl;

    publisherNames.clear();
    publisherNames.shrink_to_fit();

    return EXIT_SUCCESS;
}

Node *BST_tree::get_root()
{
    return this->root;
}

Node *BST_tree::BST_insert(Node *root, Node *ptr)
{
    if (root == nullptr)
    {
        return ptr; 
    }

    if (ptr->key.name < root->key.name)
    {
        root->left = BST_insert(root->left, ptr);
        root->left->parent = root;
    }
    else if (ptr->key.name > root->key.name)
    {
        root->right = BST_insert(root->right, ptr);
        root->right->parent = root;
    }
    else
    {
        // Publisher exists, update cumulative sales
        root->key.na_sales += ptr->key.na_sales;
        root->key.eu_sales += ptr->key.eu_sales;
        root->key.others_sales += ptr->key.others_sales;
        delete ptr; // Avoid memory leak
    }

    return root;
}
// Format: Name, Platform, Year of Release, Publisher, NA_Sales, EU_Sales, Other_Sales, Year
void BST_tree::insertValue(vector<string> n)
{
    publisher p;
    p.name = n[3];
    p.na_sales = stof(n[4]);
    p.eu_sales = stof(n[5]);
    p.others_sales = stof(n[6]);

    Node *newNode = new Node(p);
    this->root = BST_insert(this->root, newNode);
}

void BST_tree::find_best_seller()
{
    if (!root)
        return;

    stack<Node *> s;
    Node *current = root;

    while (!s.empty() || current != nullptr)
    {
        if (current != nullptr)
        {
            s.push(current);
            current = current->left;
        }
        else
        {
            current = s.top();
            s.pop();

            // Compare and update best_seller
            if (best_seller[0] == nullptr || current->key.na_sales > best_seller[0]->na_sales)
                best_seller[0] = &current->key;

            if (best_seller[1] == nullptr || current->key.eu_sales > best_seller[1]->eu_sales)
                best_seller[1] = &current->key;

            if (best_seller[2] == nullptr || current->key.others_sales > best_seller[2]->others_sales)
                best_seller[2] = &current->key;

            current = current->right;
        }
    }
    print_best_sellers(yearr, best_seller);
}

BST_tree::BST_tree()
{
    this->root = NULL;
    this->best_seller[0] = NULL;
    this->best_seller[1] = NULL;
    this->best_seller[2] = NULL;
}

BST_tree::~BST_tree()
{
}

Node *BST_tree::search(Node *root, string key)
{
    
    if (root == NULL || root->key.name == key)
        return root;

    
    if (root->key.name < key)
        return search(root->right, key);

    
    return search(root->left, key);
}
