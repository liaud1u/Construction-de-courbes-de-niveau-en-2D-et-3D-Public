#ifndef UNIONFIND_H
#define UNIONFIND_H

#include <vector>
#include <algorithm>
#include <iostream>

/**
 ** @brief Node structure for the UnionFind structure
 ** @author A. LIAUD
 **/
struct node{

    /// @brief unique int id of the node
    int id;

    /// @brief vector of int as date of the node
    std::vector<int> data;

    /// @brief Constructor of the node
    /// @param int unique id of the node
    /// @param int initial value of the node
    node(int id, int value){
        this->id = id;
        data.push_back(value);
    }
};

/**
 ** @brief UnionFind data structure
 ** @author A. LIAUD
 **/
class UnionFind
{

private:

     /// @brief vector of all the nodes
     std::vector<node> data;

     /// @brief cpt to get uniques id for new nodes
     int cpt = 0;

public:

    /// @brief Default constructor
    UnionFind();

    /// @brief Union operation on two nodes
    /// @param Node where we will add data
    /// @param Node wich will be merge in the first node
    void union_op(node * id1, node * id2);

    /// @brief Find node containing element
    /// @param int element we are looking for
    /// @return node containing element
    node * find_op(int element);

    /// @brief Add new node to the structure
    /// @param int value of the new node
    void add_node(int value);

    /// @brief Print the structure (for debugging)
    void print();

    /// @brief Get all nodes
    /// @return list of all nodes
    std::vector<node> get_data(){return data;}

    /// @brief Check if the structure contains a value
    /// @param int value to check if contained
    /// @return bool true if value is in the structure, else false
    bool contains(int value);
};

#endif // UNIONFIND_H
