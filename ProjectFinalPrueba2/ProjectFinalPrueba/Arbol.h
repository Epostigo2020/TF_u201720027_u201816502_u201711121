#pragma once
#include <functional>
#include <string>
#include <iostream>
#include <functional>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;
using namespace System;

template<typename T, typename R = T, T NONE = 0>
class Arbol
{
	struct Node;
	Node*           root;
	function<R(T, int)>  key;
	int             len;
	vector<T>* vecF;
	
	int numero;
public:
	Arbol(function<R(T, int)> key, int numero)
		: key(key), root(nullptr), len(0), numero(numero) ,vecF(new vector<T>()) {}
	~Arbol() { clear(root); }
	int height() { return height(root); }
	int size() { return len; }
	void clear() { clear(root); }

	void add(T elem) { add(root, elem); }
	T find(R val) { return find(root, val); }
	T greaterThan(R val) { return greaterThan(root, val); }
	void inOrder(function<void(T)> proc) { inOrder(root, proc); }

	vector<T>* retornarTodo() {
		vecF->clear();
		retornarTodo(root);
		if (vecF->size() > 0) {
			return vecF;
		}
		else {
			return nullptr;
		}
	}
	vector<T>* findElementos(R val) {

		vecF->clear();

		findElementos(root, val);
		
		if (vecF->size() > 0) {
			return vecF;
		}
		else {
			return nullptr;
		}
	}
	vector<T>* mayorQue(R val) {
		vecF->clear();
		mayorQue(root, val);
		if (vecF->size() > 0) {
			return vecF;
		}
		else {
			return nullptr;
		}
	}
	vector<T>*menorQue(R val) {
		vecF->clear();
		menorQue(root, val);
		if (vecF->size() > 0) {
			return vecF;
		}
		else {
			return nullptr;
		}
	}
	vector<T>*encontrarFiltro(R val, function<bool(R, R)> fun) {
		vecF->clear();
		encontrarFiltro(root, val, fun);
		if (vecF->size() > 0) {
			return vecF;
		}
		else {
			return nullptr;
		}
	}

private:
	void    clear(Node*& node);  //eliminar
	int     height(Node* node); //altura
	void    add(Node*& node, T elem); //agregar
	void    inOrder(Node*& node, function<void(T)> proc);  //de menor a mayor
	T       find(Node*& node, R val);
	T       greaterThan(Node*& node, R val);
	void    updateHeight(Node*& node); //actualizar altura
	void    rotateLeft(Node*& node); //
	void    rotateRight(Node*& node);
	void    balance(Node*& node);
	void findElementos(Node*& node, R val);
	void mayorQue(Node*& node, R val);
	void retornarTodo(Node*& node);
	void menorQue(Node*& node, R val);
	void encontrarFiltro(Node*& node, R val, function<bool(R, R)> fun);

	
};

template<typename T, typename R, T NONE>
struct Arbol<T, R, NONE>::Node {
	T       element;
	Node*   left;
	Node*   right;
	int     height;

	Node(T element)
		: element(element), height(0),
		left(nullptr), right(nullptr) {}
};

template<typename T, typename R, T NONE>
void Arbol<T, R, NONE>::clear(Node*& node) {
	if (node != nullptr) {
		clear(node->left);
		clear(node->right);
		delete node;
		node = nullptr;
	}
}

template<typename T, typename R, T NONE>
int Arbol<T, R, NONE>::height(Node* node) {
	return node == nullptr ? -1 : node->height;
}

template<typename T, typename R, T NONE>
void Arbol<T, R, NONE>::add(Node*& node, T elem) {
	if (node == nullptr) {
		node = new Node(elem);
	}
	else {
		if (key(elem, numero) < key(node->element, numero)) {
			add(node->left, elem);
		}
		else {
			add(node->right, elem);
		}
		balance(node);
	}
}

template<typename T, typename R, T NONE>
T Arbol<T, R, NONE>::find(Node*& node, R val) {
	if (node == nullptr) {
		return NONE;
	}
	else if (val == key(node->element,numero)) {
		return node->element;
	}
	else if (val < key(node->element,numero)) {
		return find(node->left, val);
	}
	else {
		return find(node->right, val);
	}
}

template<typename T, typename R, T NONE>
void Arbol<T, R, NONE>::retornarTodo(Node*& node) {

	if (node == nullptr) {
		return;
	}
	else {
		retornarTodo(node->left);
		vecF->push_back(node->element);
		retornarTodo(node->right);
	}
}

template<typename T, typename R, T NONE>
void Arbol<T, R, NONE>::encontrarFiltro(Node*& node, R val, function<bool(R,R)> fun) {
	string* pa;
	if (node == nullptr) {
		return;
	}
	else {
		if (fun(key(node->element, numero), val) == true) {
			vecF->push_back(node->element);
		}
		encontrarFiltro(node->left, val,fun);
		encontrarFiltro(node->right, val,fun);
	}
}
template<typename T, typename R, T NONE>
void Arbol<T, R, NONE>::findElementos(Node*& node, R val) {
	if (node == nullptr) {
		return;
	}
	else {
		if (val == key(node->element, numero)) {
			vecF->push_back(node->element);
		}
		findElementos(node->left, val);
		findElementos(node->right, val);
	}
}
template<typename T, typename R, T NONE>
void Arbol<T, R, NONE>::mayorQue(Node*& node, R val) {
	
	if (node == nullptr) {
		return;
	}
	else {
		if (val < key(node->element, numero)) {
			vecF->push_back(node->element);
		}
		mayorQue(node->left, val);
		mayorQue(node->right, val);
	}
}
template<typename T, typename R, T NONE>
void Arbol<T, R, NONE>::menorQue(Node*& node, R val) {

	if (node == nullptr) {
		return;
	}
	else {
		if (val > key(node->element, numero)) {
			vecF->push_back(node->element);
		}
		menorQue(node->left, val);
		menorQue(node->right, val);
	}
}


template<typename T, typename R, T NONE>
T Arbol<T, R, NONE>::greaterThan(Node*& node, R val) { //Mayor que
	if (node == nullptr) {
		return NONE;
	}
	else if (val < key(node->element)) {
		return node->element;
	}
	return greaterThan(node->right, val);
}

template<typename T, typename R, T NONE>
void Arbol<T, R, NONE>::inOrder(Node*& node, function<void(T)> proc) {
	if (node != nullptr) {
		inOrder(node->left, proc);
		proc(node->element);
		inOrder(node->right, proc);
	}
}
#define max(a, b) (a > b? a : b)

template<typename T, typename R, T NONE>
void Arbol<T, R, NONE>::updateHeight(Node*& node) {
	if (node != nullptr) {
		int hl = height(node->left);
		int hr = height(node->right);

		node->height = max(hl, hr) + 1;
	}
}

template<typename T, typename R, T NONE>
void Arbol<T, R, NONE>::rotateLeft(Node*& node) {
	Node* aux = node->right;
	node->right = aux->left;
	updateHeight(node);
	aux->left = node;
	updateHeight(aux);
	node = aux;
}

template<typename T, typename R, T NONE>
void Arbol<T, R, NONE>::rotateRight(Node*& node) {
	Node* aux = node->left;
	node->left = aux->right;
	updateHeight(node);
	aux->right = node;
	updateHeight(aux);
	node = aux;
}

template<typename T, typename R, T NONE>
void Arbol<T, R, NONE>::balance(Node*& node) {
	int hl = height(node->left);
	int hr = height(node->right);

	if (hl - hr > 1) {
		hl = height(node->left->left);
		hr = height(node->left->right);
		if (hl < hr) {
			rotateLeft(node->left);
		}
		rotateRight(node);
	}
	else if (hl - hr < -1) {
		hl = height(node->right->left);
		hr = height(node->right->right);
		if (hl > hr) {
			rotateRight(node->right);
		}
		rotateLeft(node);
	}
	else {
		updateHeight(node);
	}
}


