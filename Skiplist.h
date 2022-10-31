//
// Created by 黄志鸿 on 2022/10/28.
//

#ifndef SKIPLIST_SKIPLIST_H
#define SKIPLIST_SKIPLIST_H

#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <mutex>
#include <unistd.h>

#include "Node.h"
#include "tools.h"

#define STORE_DIR "/store/"
#define STORE_DIR_DEFAULT "/store/dump_file.txt"

std::mutex mtx;
std::string delimiter = ":";

template<class K, class V>
class Skiplist {

public:

    explicit Skiplist(int max_level = 1);

    ~Skiplist();

    int insert(K key, V value);

    int erase(K key);

    int find(K key);

    void store();

    void load();

    inline int size() const;

    inline bool empty() const;

    void clear();

public:
    // debug only
    void display() const;

public:
    // deleted methods.

    Skiplist(const Skiplist& rhs) = delete;
    Skiplist(const Skiplist&& rhs) = delete;

    Skiplist& operator = (const Skiplist& rhs) = delete;
    Skiplist& operator = (const Skiplist&& rhs) = delete;

private:

    const int _max_level;

    int _level;
    int _size;

    Node<K, V> *_head = nullptr;

    std::ofstream _fcout;
    std::ifstream _fin;

//    inline Node<K, V>* _add_node(K key, V value, int node_level) {
//        return new Node<K, V>(key, value, node_level);
//    }

    int _get_rand_levels() const;

};

template<class K, class V>
int Skiplist<K, V>::_get_rand_levels() const {
    int c = Random_int_generator::get_instance().random_int(_max_level, 1.0/4);
    return c;
}

template<class K, class V>
Skiplist<K, V>::Skiplist(int max_level): _max_level(max_level), _level(0), _size(0) {
    K k;
    memset(&k, 0, sizeof k);
    V v;
    memset(&v, 0, sizeof v);
    _head = new Node<K, V>(k, v, _max_level);
}

template<class K, class V>
Skiplist<K, V>::~Skiplist() {
    clear();

    if (_fcout.is_open()) {
        _fcout.close();
    }
    if (_fin.is_open()) {
        _fin.close();
    }
}

template<class K, class V>
int Skiplist<K, V>::insert(K key, V value) {

    mtx.lock();

    auto cur = _head;
    std::vector<Node<K, V>* > update(_max_level, 0);

    // find the place to be inserted
    for (int i = _level - 1; i >= 0;  i --) {
        while(cur->forward[i] != nullptr && cur->forward[i]->get_key() < key) {
            cur = cur->forward[i];
        }
        update[i] = cur;
    }

    cur = cur->forward[0]; // insert here

    int return_val; // return the index of the place to be inserted.

    // The key does not exist.
    if (cur == nullptr || cur->get_key() != key) {
        // insert
        auto rand_level = _get_rand_levels();
        auto node = new Node<K, V>(key, value, rand_level);

        if (rand_level > _level) {
            for(int i = _level; i < rand_level; i ++) {
                update[i] = _head;
            }
            _level = rand_level;
        }

        for(int i = 0; i < rand_level; i ++) {
            node->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = node;
        }

        ++ _size;
        return_val = key;
    }
    else {
        return_val = key;
    }

    mtx.unlock();

    return return_val;

}

template<class K, class V>
int Skiplist<K, V>::find(K key) {
    if (_size == 0) return -1;

    auto cur = _head;
    Node<K, V> *update[_max_level];

    for (int i = _level - 1; i >= 0;  i --) {
        while(cur->forward[i] != nullptr && cur->forward[i]->get_key() < key) {
            cur = cur->forward[i];
        }
        update[i] = cur;
    }

    cur = cur->forward[0];

//    if (cur == nullptr) return -1;
//
    int return_val;

    if (cur != nullptr && cur->get_key() == key) {
        return_val = key;
    }
    else {
        return_val = -1;
    }

    return return_val;
}

template<class K, class V>
void Skiplist<K, V>::display() const {
    std::cout << "*********** Display *************" << std::endl;
    for(int i = 0; i < _max_level; i ++) {
        std::cout << "Level " << i << ": ";
        auto cur = _head;
        while(cur != nullptr) {
            std::cout << cur->get_key() << "\t";
            cur = cur->forward[i];
        }
        std::cout << std::endl;
    }
    std::cout << "*********** End *************" << std::endl;
}

template<class K, class V>
int Skiplist<K, V>::erase(K key) {
    if (_size == 0) return -1;

    auto cur = _head;
    Node<K, V> *update[_max_level];

    for (int i = _level - 1; i >= 0;  i --) {
        while(cur->forward[i] != nullptr && cur->forward[i]->get_key() < key) {
            cur = cur->forward[i];
        }
        update[i] = cur;
    }

    cur = cur->forward[0];

    int return_val;
    // mod == INSERT
    // The key exists. No operation.
    if (cur == nullptr || cur->get_key() != key) {
        return_val = -1;
    }
    if (cur != nullptr && cur->get_key() == key) {
        // erase
        for(int i = 0; i < _level; i ++) {
            if (update[i]->forward[i] != cur) break;
            update[i]->forward[i] = cur->forward[i];
        }

        while(_level > 0 && _head->forward[_level - 1] == nullptr) {
            -- _level;
        }

        -- _size;

        delete cur;
        cur = nullptr;

        return_val = key;
    }

    return return_val;
}

template<class K, class V>
void Skiplist<K, V>::clear() {
    if (_size == 0) return;

    mtx.lock();

    auto cur = _head;
    while(cur) {
        auto tmp = cur->forward[0];
        delete cur;
        cur = tmp;
    }

    mtx.unlock();
}

template<class K, class V>
inline int Skiplist<K, V>::size() const{
    return _size;
}

template<class K, class V>
inline bool Skiplist<K, V>::empty() const{
    return _size == 0;
}

template<class K, class V>
inline void Skiplist<K, V>::store() {

}

template<class K, class V>
inline void Skiplist<K, V>::load() {

}



#endif //SKIPLIST_SKIPLIST_H
