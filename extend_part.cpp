 /*
        -------- Sagar Kumar -----------
        -------- Krish Agarwal -------
 */


#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;
class SuffixTree {
private:
    struct Node {
        int start;
        int *end; 
        
        map<char, Node*> children;
        Node *suffix_link;
        int suffix_index; 

        Node(int start, int *end) : start(start), end(end), suffix_link(nullptr), suffix_index(-1) {}
    };

    string text;
    Node *root;
    
    
    Node *active_node;
    int active_edge; 
    int active_length;
    
    int remainder; 
    
    int *global_end; 
    
    int size; 

    Node* new_node(int start, int *end) {
        return new Node(start, end);
    }

    int edge_length(Node *n) {
        if(n == root) return 0;
        return *(n->end) - (n->start) + 1;
    }

    bool walk_down(Node *curr_node) {
        int len = edge_length(curr_node);
        if (active_length >= len) {
            active_edge += len;
            active_length -= len;
            active_node = curr_node;
            return true;
        }
        return false;
    }

    void extend(int pos) {
        
        (*global_end)++;
        
        
        remainder++;
        
        Node *last_new_node = nullptr;

        while (remainder > 0) {
            if (active_length == 0) {
                active_edge = pos;
            }

            char current_char = text[active_edge];
            
            if (active_node->children.find(current_char) == active_node->children.end()) {
               
                active_node->children[current_char] = new_node(pos, global_end);

                if (last_new_node != nullptr) {
                    last_new_node->suffix_link = active_node;
                    last_new_node = nullptr;
                }
            } else {

                Node *next = active_node->children[current_char];
                
                if (walk_down(next)) {
                    continue; 
                }


                if (text[next->start + active_length] == text[pos]) {
                    if (last_new_node != nullptr && active_node != root) {
                        last_new_node->suffix_link = active_node;
                        last_new_node = nullptr;
                    }
                    active_length++;
                    break; 
                }

                int *split_end = new int(next->start + active_length - 1);
                Node *split = new_node(next->start, split_end);
                
                active_node->children[current_char] = split;

                split->children[text[pos]] = new_node(pos, global_end);
                
                next->start += active_length;
                split->children[text[next->start]] = next;

                
                if (last_new_node != nullptr) {
                    last_new_node->suffix_link = split;
                }
                last_new_node = split;
            }

            remainder--;
            
            if (active_node == root && active_length > 0) {
                active_length--;
                active_edge = pos - remainder + 1;
            } else if (active_node != root) {
                active_node = active_node->suffix_link ? active_node->suffix_link : root;
            }
        }
    }

    void set_suffix_index_by_dfs(Node *n, int current_height) {
        if (!n) return;

        bool is_leaf = true;
        for (auto const& it : n->children) {
            is_leaf = false;
            set_suffix_index_by_dfs(it.second, current_height + edge_length(it.second));
        }

        if (is_leaf) {
            n->suffix_index = size - current_height;
        }
    }

    void free_tree(Node *n) {
        if (!n) return;
        for (auto const& it : n->children) {
            free_tree(it.second);
        }
        
        if (n->end != global_end && n->end != nullptr) {
            delete n->end;
        }
        delete n;
    }

    void collect_indices(Node *n, vector<int> &result) {
        if (!n) return;
        if (n->suffix_index != -1) {
            result.push_back(n->suffix_index);
        }
        for (auto const& it : n->children) {
            collect_indices(it.second, result);
        }
    }

public:
    SuffixTree(string t) {
        text = t;
        size = text.length();
        
        global_end = new int(-1);
        
        root = new_node(-1, nullptr); 
        
        active_node = root;
        active_length = 0;
        active_edge = -1;
        remainder = 0;

        for (int i = 0; i < size; i++) {
            extend(i);
        }

        set_suffix_index_by_dfs(root, 0);
    }

    ~SuffixTree() {
        free_tree(root);
        delete global_end;
    }

    void find_pattern(string pattern) {
        Node *curr = root;
        int i = 0;
        int pat_len = pattern.length();

        cout<<"Searching for \"" << pattern << "\": ";

       
        while (i < pat_len) {
            if (curr->children.find(pattern[i]) == curr->children.end()) {
                cout << "Not found (0 occurrences)" << endl;
                cout<<endl;
                return;
            }

            Node *next = curr->children[pattern[i]];
            int len = edge_length(next);
            

            for (int j = 0; j < len && i < pat_len; j++) {
                if (text[next->start + j] != pattern[i]) {
                    cout << "Not found (0 occurrences)" << endl;
                    cout << endl;
                    return;
                }
                i++;
            }
            curr = next;
        }

        
        vector<int> occurrences;
        collect_indices(curr, occurrences);
        
        //sort(occurrences.begin(), occurrences.end());

        cout << occurrences.size() << " occurrences at indices: ";
        for (int idx : occurrences) {
            cout << idx << " ";
        }
        cout << endl;
        cout << endl;

    }
};

int main() {
    
    
    
    cout << "Enter Text T: ";
    
    ifstream myfile("input.txt"); 
    //fopen(input.txt);
    string t_input;

    
    if (!myfile.is_open()) {
        cout << "Error opening file" << endl;
        return 1;
    }

    if (!getline(myfile, t_input)) {
        return 0; 
    }
    
    //input
    t_input += "$";

    cout << "Building Suffix Tree..." << endl;
    SuffixTree st(t_input);
    cout << "Build Complete." << endl;
    int p_count;

    if (!(myfile >> p_count)) return 0; 
    //auto start = high_resolution_clock::now();
    for (int i = 0; i < p_count; i++) {
        string pat;
        myfile >> pat; 
        st.find_pattern(pat);
    }

    myfile.close();

    //auto stop = high_resolution_clock::now();
    
    //auto duration = duration_cast<microseconds>(stop - start);

    //cout << "Time taken by Suffix Tree: " << duration.count() << " microseconds" << endl;

    return 0;
}
    