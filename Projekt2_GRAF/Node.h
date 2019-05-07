#pragma once

template<typename T>
class MNode {
private:
	T elem;
	MNode<T>* prev;
	MNode<T>* next;
public:
	MNode(T a);
	MNode();
	MNode(const MNode<T>& a);
public:
	void SetPrev(MNode<T>* m) { prev = m; }
	void SetNext(MNode<T>* m) { next = m; }
	void SetElem(T m) { elem = m; }
	MNode* GetPrev() { return prev; }
	MNode* GetNext() { return next; }
	T GetElem() { return elem; }


};

template <typename T>
MNode<T>::MNode(T a) {
	elem = a;
	prev = nullptr;
	next = nullptr;
}

template <typename T>
MNode<T>::MNode() {
}

template <typename T>
MNode<T>::MNode(const MNode<T>& a) {
	elem = a.elem;
	prev = a.prev;
	next = a.next;
}