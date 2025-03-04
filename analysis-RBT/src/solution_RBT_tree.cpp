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
/////////////////// Player ///////////////////
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
    int color; // "Red"=1 or "Black"=0
    Node *parent, *left, *right;

    Node(publisher);
    ~Node();
    int get_color();
    void set_color(int);
};

/////////////////// RB-Tree ///////////////////
class RB_tree
{
private:
    Node *root;

public:
    publisher *best_seller[3];
    stack<string> tree_deep_stack;

    Node *get_root();

    Node *RB_insert(Node *root, Node *ptr);
    void insertValue(vector<string>);
    void RB_left_rotate(Node *);
    void RB_right_rotate(Node *);
    void RB_insert_fixup(Node *);
    void preorder();
    void find_best_seller();
    Node *search(Node *root, string key);

    RB_tree();
    ~RB_tree();
};

void print_best_sellers(int year, publisher *temp_publisher[3])
{
    cout.precision(5);
    cout << "End of the " + to_string(year) + " Year" << endl;
    cout << "Best seller in North America: " + temp_publisher[0]->name + " - " << temp_publisher[0]->na_sales << " million" << endl;
    cout << "Best seller in Europe: " + temp_publisher[1]->name + " - " << temp_publisher[1]->eu_sales << " million" << endl;
    cout << "Best seller rest of the World: " + temp_publisher[2]->name + " - " << temp_publisher[2]->others_sales << " million" << endl;
}

RB_tree generate_RBT_tree_from_csv(string file_name)
{
    RB_tree temp_RBtree;
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
            temp_RBtree.insertValue(values);
            auto end_insert = chrono::high_resolution_clock::now();
            auto duration_insertion = chrono::duration_cast<chrono::microseconds>(end_insert - start_insert);
            total_insert_time += duration_insertion.count();
            yearr = year;
        }
        else
        {
            temp_RBtree.find_best_seller();
            current_decade_end += 10;
            auto start_insert = chrono::high_resolution_clock::now();
            temp_RBtree.insertValue(values);
            auto end_insert = chrono::high_resolution_clock::now();
            auto duration_insertion = chrono::duration_cast<chrono::microseconds>(end_insert - start_insert);
            total_insert_time += duration_insertion.count();
            yearr = year;
        }

        
        publisherNames.push_back(values[3]);
    }

    temp_RBtree.find_best_seller();
    cout << "Time taken to insert all data into RBT: " << total_insert_time << " µs" << endl;
    return temp_RBtree;
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

bool compareByPublisherName(const VideoGame &a, const VideoGame &b)
{
    return a.publisher < b.publisher;
}

vector<VideoGame> sortGamesByPublisherName(const string &inputFile)
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

    sort(games.begin(), games.end(), compareByPublisherName);

    return games;
}

RB_tree generate_RBT_tree_from_csv_with_name(const string &inputFile)
{
    vector<VideoGame> sortedGames = sortGamesByPublisherName(inputFile);
    RB_tree temp_RBtree;

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
        temp_RBtree.insertValue(values);
        auto end_insert = chrono::high_resolution_clock::now();
        auto duration_insertion = chrono::duration_cast<chrono::microseconds>(end_insert - start_insert);
        total_insert_time += duration_insertion.count();

        // Collect publisher names for search keys
        publisherNames.push_back(game.publisher);
    }

    cout << "Time taken to insert all data into RBT with ordered publisher names: " << total_insert_time << " µs" << endl;
    return temp_RBtree;
}

////////////////////////////////////////////
//----------------- MAIN -----------------//
////////////////////////////////////////////
int main(int argc, char *argv[])
{

    string fname = argv[1]; 
    RB_tree RBtree = generate_RBT_tree_from_csv(fname); 

    // Perform 50 random searches and calculate the average time
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, publisherNames.size() - 1);

    auto start = high_resolution_clock::now();
    for (int i = 0; i < 50; ++i)
    {
        string key = publisherNames[dis(gen)];
        Node *result = RBtree.search(RBtree.get_root(), key); 
        
    }
    auto end = high_resolution_clock::now();
    double avg_search_time = duration_cast<nanoseconds>(end - start).count() / 50.0;
    cout << "Average time for 50 random searches in RBT: " << avg_search_time << " ns" << endl;

    // Please uncomment the following code to print RBT in preorder
    
    RBtree.preorder(); // Print the RBT in preorder

    // Please uncomment the code below for part F

    RB_tree RBtree2 = generate_RBT_tree_from_csv_with_name(fname); 
    
    // Perform 50 random searches and calculate the average time
    random_device rd2;
    mt19937 gen2(rd2());
    uniform_int_distribution<> dis2(0, publisherNames.size() - 1);

    auto start2 = high_resolution_clock::now();
    for (int i = 0; i < 50; ++i)
    {
        string key2 = publisherNames[dis2(gen2)];
        Node *result2 = RBtree2.search(RBtree2.get_root(), key2); 
    
    }
    auto end2 = high_resolution_clock::now();
    double avg_search_time2 = duration_cast<nanoseconds>(end2 - start2).count() / 50.0;
    cout << "Average time for 50 random searches in RBT for ordered publisher names: " << avg_search_time2 << " ns" << endl;

    publisherNames.clear();
    publisherNames.shrink_to_fit();
    return EXIT_SUCCESS;
}

/////////////////// Node ///////////////////

Node::Node(publisher key)
{
    this->key = key;
    this->color = 1; // "RED";
    this->parent = NULL;
    this->left = NULL;
    this->right = NULL;
}
Node::~Node()
{
}
/////////////////// RB-Tree ///////////////////
Node *RB_tree::get_root()
{
    return this->root;
}

Node *RB_tree::RB_insert(Node *root, Node *ptr)
{
    if (root == nullptr)
    {
        return ptr; // If tree is empty, return new node as root
    }

    if (ptr->key.name < root->key.name)
    {
        root->left = RB_insert(root->left, ptr);
        root->left->parent = root;
    }
    else if (ptr->key.name > root->key.name)
    {
        root->right = RB_insert(root->right, ptr);
        root->right->parent = root;
    }
    else
    {
        // Publisher exists, update cumulative sales
        root->key.na_sales += ptr->key.na_sales;
        root->key.eu_sales += ptr->key.eu_sales;
        root->key.others_sales += ptr->key.others_sales;
        delete ptr;
    }

    return root;
}

void RB_tree::insertValue(vector<string> n)
{
    publisher p;
    p.name = n[3];
    p.na_sales = stof(n[4]);
    p.eu_sales = stof(n[5]);
    p.others_sales = stof(n[6]);

    Node *newNode = new Node(p);
    this->root = RB_insert(this->root, newNode);

    RB_insert_fixup(newNode); // Fix Red-Black Tree properties
}


void RB_tree::RB_left_rotate(Node *ptr)
{
    Node *y = ptr->right;
    ptr->right = y->left;

    if (y->left != NULL)
    {
        y->left->parent = ptr;
    }

    y->parent = ptr->parent;

    if (ptr->parent == NULL)
    {
        root = y;
    }
    else if (ptr == ptr->parent->left)
    {
        ptr->parent->left = y;
    }
    else
    {
        ptr->parent->right = y;
    }

    y->left = ptr;
    ptr->parent = y;
}

void RB_tree::RB_right_rotate(Node *ptr)
{
    Node *x = ptr->left;
    ptr->left = x->right;

    if (x->right != NULL)
    {
        x->right->parent = ptr;
    }

    x->parent = ptr->parent;

    if (ptr->parent == NULL)
    {
        root = x;
    }
    else if (ptr == ptr->parent->right)
    {
        ptr->parent->right = x;
    }
    else
    {
        ptr->parent->left = x;
    }

    x->right = ptr;
    ptr->parent = x;
}

void RB_tree::RB_insert_fixup(Node *ptr)
{
    while (ptr != root && ptr->parent != NULL && ptr->parent->color == 1)
    { // Parent is RED
        Node *grandparent = ptr->parent->parent;
        if (ptr->parent == grandparent->left)
        {
            Node *uncle = grandparent->right;
            if (uncle != NULL && uncle->color == 1)
            { // Uncle is RED
                ptr->parent->color = 0;
                uncle->color = 0;
                grandparent->color = 1;
                ptr = grandparent;
            }
            else
            {
                if (ptr == ptr->parent->right)
                {
                    ptr = ptr->parent;
                    RB_left_rotate(ptr);
                }
                ptr->parent->color = 0;
                grandparent->color = 1;
                RB_right_rotate(grandparent);
            }
        }
        else
        {
            Node *uncle = grandparent->left;
            if (uncle != NULL && uncle->color == 1)
            { // Uncle is RED
                ptr->parent->color = 0;
                uncle->color = 0;
                grandparent->color = 1;
                ptr = grandparent;
            }
            else
            {
                if (ptr == ptr->parent->left)
                {
                    ptr = ptr->parent;
                    RB_right_rotate(ptr);
                }
                ptr->parent->color = 0;
                grandparent->color = 1;
                RB_left_rotate(grandparent);
            }
        }
    }
    root->color = 0;
}

void RB_tree::preorder()
{
    stack<pair<Node *, int>> s;
    s.push(make_pair(root, 0)); // Use `make_pair` explicitly

    while (!s.empty())
    {
        pair<Node *, int> top = s.top(); // Retrieve the top element
        s.pop();

        Node *current = top.first;
        int depth = top.second;

        if (current)
        {
            cout << string(depth, '-') << "(" << (current->color == 0 ? "BLACK" : "RED") << ")"
                 << " " << current->key.name << endl;

            // Push right and left children onto the stack
            s.push(make_pair(current->right, depth + 1));
            s.push(make_pair(current->left, depth + 1));
        }
    }
}

void RB_tree::find_best_seller()
{
    if (!root)
        return; // If the tree is empty, do nothing

    // Initialize a stack for iterative in-order traversal
    stack<Node *> s;
    Node *current = root;

    // Reset best sellers to null
    best_seller[0] = best_seller[1] = best_seller[2] = nullptr;

    // Perform iterative in-order traversal
    while (!s.empty() || current != nullptr)
    {
        if (current != nullptr)
        {
            s.push(current);
            current = current->left; // Traverse left
        }
        else
        {
            current = s.top();
            s.pop();

            // Compare and update best sellers
            if (best_seller[0] == nullptr || current->key.na_sales > best_seller[0]->na_sales)
                best_seller[0] = &current->key;

            if (best_seller[1] == nullptr || current->key.eu_sales > best_seller[1]->eu_sales)
                best_seller[1] = &current->key;

            if (best_seller[2] == nullptr || current->key.others_sales > best_seller[2]->others_sales)
                best_seller[2] = &current->key;

            current = current->right; // Traverse right
        }
    }

    // Print the best sellers for each region
    print_best_sellers(yearr, best_seller);
}

RB_tree::RB_tree()
{
    this->root = NULL;
    this->best_seller[0] = NULL;
    this->best_seller[1] = NULL;
    this->best_seller[2] = NULL;
}

RB_tree::~RB_tree()
{
}

Node *RB_tree::search(Node *root, string key)
{
    // Base Cases: root is null or key is present at root
    if (root == NULL || root->key.name == key)
        return root;

    // Key is greater than root's key
    if (root->key.name < key)
        return search(root->right, key);

    // Key is smaller than root's key
    return search(root->left, key);
}