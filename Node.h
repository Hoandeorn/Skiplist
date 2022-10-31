//
// Created by 黄志鸿 on 2022/10/28.
//

#ifndef SKIPLIST_NODE_H
#define SKIPLIST_NODE_H

#include <iostream>
#include <cstring>
#include <vector>

template <typename K, typename V>
class Node {

public:

    Node() = default;

    Node(K key, V value, int node_level);

    ~Node();

    K get_key();

    V get_value();

    void set_value(V value);

    std::vector<Node<K, V>* > forward; // forward-> Node*[level]


private:
    K _key;
    V _value;
    int _node_level = 0;
};

template<typename K, typename V>
Node<K, V>::Node(K key, V value, int node_level): _key(key), _value(value), _node_level(node_level) {

    this->forward.resize(node_level, 0);
}

template<typename K, typename V>
Node<K, V>::~Node() {

}

template<typename K, typename V>
inline K Node<K, V>::get_key() {
    return _key;
}

template<typename K, typename V>
inline V Node<K, V>::get_value() {
    return _value;
}

template<typename K, typename V>
inline void Node<K, V>::set_value(V value) {
    _value = value;
};


#endif //SKIPLIST_NODE_H
