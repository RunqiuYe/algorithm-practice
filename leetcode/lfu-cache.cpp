#include <algorithm>
#include <array>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

typedef long long ll;

using namespace std;

class Node {
   public:
    int key;
    int val;
    int freq = 0;
    Node* prev;
    Node* next;

    Node(int key = 0, int val = 0) : key(key), val(val) {}
};

class LFUCache {
   public:
    LFUCache(int capacity) : capacity(capacity) {}

    int get(int key) {
        Node* node = get_node(key);
        if (node) {
            return node->val;
        } else {
            return -1;
        }
    }

    void put(int key, int value) {
        Node* node = get_node(key);
        if (node) {
            node->val = value;
            return;
        }
        if (count == capacity) {
            Node* head = freq_to_head[min_freq];
            Node* back_node = head->prev;  // least recently used
            key_to_node.erase(back_node->key);
            remove(back_node);
            delete back_node;
            if (head == head->next) {
                freq_to_head.erase(min_freq);
                delete head;
            }
            count -= 1;
        }
        Node* new_node = new Node(key, value);
        key_to_node.emplace(key, new_node);
        add_node(1, new_node);
        new_node->freq = 1;
        min_freq = 1;
        count += 1;
    }

   private:
    unordered_map<int, Node*> key_to_node;
    unordered_map<int, Node*> freq_to_head;
    int capacity;
    int min_freq = 0;
    int count = 0;
    void remove(Node* node) {
        Node* prev = node->prev;
        Node* next = node->next;
        prev->next = next;
        next->prev = prev;
    }

    Node* get_node(int key) {
        auto it = key_to_node.find(key);
        if (it == key_to_node.end()) {
            return nullptr;
        }
        Node* node = it->second;
        remove(node);
        Node* head = freq_to_head[node->freq];
        if (head->next == head) {
            freq_to_head.erase(node->freq);
            delete head;
            if (min_freq == node->freq) {
                min_freq++;
            }
        }
        node->freq += 1;
        add_node(node->freq, node);
        return node;
    }

    void add_node(int freq, Node* node) {
        Node* head;
        auto it = freq_to_head.find(freq);
        if (it == freq_to_head.end()) {
            head = new_list();
            freq_to_head.emplace(freq, head);
        } else {
            head = it->second;
        }
        node->prev = head;
        node->next = head->next;
        node->next->prev = node;
        node->prev->next = node;
    }

    Node* new_list() {
        Node* node = new Node();
        node->prev = node;
        node->next = node;
        return node;
    }
};
