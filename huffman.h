#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <iterator>
using namespace std;

class Decoder
{
public:
    // read in a file with symbol and
    // probability as such:
    // ...
    // s: .25
    // b: .13
    // ...
    // example file given
    // at example.in
    Decoder(ifstream &is)
    {

        string input;
        int count = 0;
        while (is >> input)
        {
            if (count % 2 == 0)
            {
                input.erase(input.size() - 1);
                s.push_back(input);
            }
            else if (count % 2 == 1)
            {
                p.push_back(stod(input));
            }
            count++;
        }
    }

    // print symbol and probability
    // in same format as input
    void print()
    {
        cout << "Printing Data" << endl;
        for (int i = 0; i < s.size(); i++)
        {
            cout << s.at(i);
            cout << ": ";
            cout << p.at(i);
            if (i < c.size())
            {
                cout << " CODE: ";
                cout << c.at(i);
            }
            cout << endl;
        }
        cout << endl;
    }

    // uses huffman encoding algorithm
    // to populate vector c with corresponding
    // code
    void encode()
    {
        // copy vectors

        while (p.size() != 1)
        {
            // get two most min elements from vector
            double min_one = get_min(p);
            double min_index_one = get_min_index(p);
            string min_one_sbl = s[min_index_one];
            s.erase(s.begin() + min_index_one);
            p.erase(p.begin() + min_index_one);
            double min_two = get_min(p);
            double min_index_two = get_min_index(p);
            string min_two_sbl = s[min_index_two];
            p.erase(p.begin() + min_index_two);
            s.erase(s.begin() + min_index_two);

            // create internal node out of
            // concatenation of these two probabilities
            Node *internal_node = new Node;
            double concatenate = min_one + min_two;
            internal_node->sbl = "Internal Node";
            internal_node->prb = concatenate;

            // We must now consider two invariants:
            // either the minimum probability and
            // symbol represents a symbol element,
            // or they represent an internal node.
            if (min_one_sbl != "Internal Node")
            {
                Node *left_prb = new Node;
                internal_node->left = left_prb;
                left_prb->sbl = min_one_sbl;
                left_prb->prb = min_one;
                left_prb->left = nullptr;
                left_prb->right = nullptr;
            }
            else if (min_one_sbl == "Internal Node")
            {
                internal_node->left = n[0];
                n.erase(n.begin());
            }

            if (min_two_sbl != "Internal Node")
            {
                Node *right_prb = new Node;
                internal_node->right = right_prb;
                right_prb->sbl = min_two_sbl;
                right_prb->prb = min_two;
                right_prb->left = nullptr;
                right_prb->right = nullptr;
            }
            else
            {
                internal_node->right = n[0];
                n.erase(n.begin());
            }

            // to keep track of nodes
            // push back to node ptr vector
            n.push_back(internal_node);

            // push internal node back into
            // string and probability vectors
            p.push_back(concatenate);
            s.push_back("Internal Node");
        }

        // now, we encode!
        p.clear();
        s.clear();
        populate_codes(c, p, s, n[0]);
    }

    void decode(istream &is, ostream &os)
    {

        string message;

        while (is >> message)
        {
            string code = "";
            for (int i = 0; i < message.size(); i++)
            {
                code = code + message.at(i);
                for (int i = 0; i < c.size(); i++)
                {
                    if (code == c.at(i))
                    {
                        os << s.at(i);
                        code = "";
                    }
                }
            }
            os << " ";
        }
    }

private:
    // the following two vectors
    // correlate with one another such
    // that the symbol at s[i] has probability
    // p[i]

    // vector of symbols
    vector<string>
        s;

    // vector of probabilities
    vector<double> p;

    // vector of codes
    vector<string> c;

    // node class for Binary Search Tree
    class Node
    {
        friend class Decoder;

    private:
        string sbl;
        string code;
        double prb;
        Node *left;
        Node *right;
    };

    // vector of node ptrs
    vector<Node *> n;

    int get_min_index(vector<double> &v)
    {
        double min_index = 0;
        double min = v[0];
        for (int i = 1; i < v.size(); i++)
        {
            if (v[i] < min)
            {
                min_index = i;
                min = v[i];
            }
        }
        return min_index;
    }

    double get_min(vector<double> &v)
    {
        double min = v[0];
        for (int i = 1; i < v.size(); i++)
        {
            if (v[i] < min)
            {
                min = v[i];
            }
        }
        return min;
    }

    void populate_codes(vector<string> &c, vector<double> &p, vector<string> &s, Node *node)
    {
        node->left->code = node->code + "0";
        p.push_back(node->left->prb);
        s.push_back(node->left->sbl);
        c.push_back(node->left->code);

        node->right->code = node->code + "1";
        p.push_back(node->right->prb);
        s.push_back(node->right->sbl);
        c.push_back(node->right->code);

        if (node->left->left)
        {
            populate_codes(c, p, s, node->left);
        }

        if (node->right->right)
        {
            populate_codes(c, p, s, node->right);
        }

        for (int i = 0; i < s.size(); i++)
        {
            if (s.at(i) == "Internal Node")
            {
                s.erase(s.begin() + i);
                c.erase(c.begin() + i);
                p.erase(p.begin() + i);
            }
        }
    }

    void print_tree(Node *node)
    {
        if (!node)
        {
            return;
        }
        print_tree(node->left);
        cout << node->sbl << " " << endl;
        print_tree(node->right);
    }
};

#endif
