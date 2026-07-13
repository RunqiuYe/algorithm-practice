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

struct Node {
    int key;
    Node* prev;
    Node* next;
};

class LRUCache {
   public:
    LRUCache(int capacity) {
        this->capacity = capacity;
        cnt = 0;
        cache = new Node;
        cache->prev = cache;
        cache->next = cache;
    }

    int get(int key) {
        auto iter = key_to_val.find(key);
        if (iter == key_to_val.end()) {
            return -1;
        }
        Node* node = key_to_node[key];
        remove(node);
        insert(node);
        return iter->second;
    }

    void put(int key, int value) {
        auto iter = key_to_val.find(key);
        if (iter != key_to_val.end()) {
            Node* node = key_to_node[key];
            remove(node);
            insert(node);
            key_to_val[key] = value;
            return;
        }

        if (cnt == capacity) {
            Node* tail = cache->prev;
            remove(tail);
            key_to_val.erase(tail->key);
            key_to_node.erase(tail->key);
            delete tail;
            cnt--;
        }
        Node* node = new Node;
        node->key = key;
        insert(node);
        key_to_val[key] = value;
        key_to_node[key] = node;
        cnt++;
    }

   private:
    int capacity;
    int cnt;
    Node* cache;
    map<int, int> key_to_val;
    map<int, Node*> key_to_node;

    void insert(Node* node) {
        Node* next_node = cache->next;
        next_node->prev = node;
        node->next = next_node;
        cache->next = node;
        node->prev = cache;
    }

    void remove(Node* node) {
        node->next->prev = node->prev;
        node->prev->next = node->next;
    }
};
