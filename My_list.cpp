#include<iostream>
#include<list>

using namespace std;

class List {
	class Node {
	public:
		int val = 0;
		Node* priv = nullptr;
		Node* next = nullptr;
		Node() {}
		Node(int val, Node* priv, Node* next) : val(val), priv(priv), next(next) {

		}
		};
public:
	class Iter {
		
		Iter(Node* nd) : nd(nd) {};
	public:
		Iter() {}
		// ++it
		Iter& operator++() {
			nd = nd->next;
			return *this;
		}
		//it++
		Iter& operator++(int) {
			Iter other = *this;
			nd = nd->next;
			return other;
		}
		// Разыменование.
		int& operator*() const {
			return nd->val;
		}
		// Равенство указателей на ноды.
		bool operator==(const Iter& other) {
			return nd == other.nd;
		}
		bool operator!=(const Iter & other) {
				return !(*this == other);
		}
	private:
		Node* nd = nullptr;
		friend List;
	};
	//Constructor
	List() {
		first.nd = new Node();
		last.nd = first.nd;
	}
	// Coppy
	List(const List& other) : List() { // вызвали конструктор по умолчанию.
		for (Iter it = first; it != last; ++it) {
			this->push_back(*it); // В конец листа вставляем значение.
		}
	}
	// Функции
	Iter insert(const Iter& it_l, const int x) {
		//1 2 3-> <-x-> <-4
		if (this->empty()) {
			Iter it(new Node(x, nullptr, it_l.nd));
			it_l.nd->priv = it.nd;
			first = it;
			return it;
		}
		Iter it_r = it_l;
		++it_r;
		Iter it(new Node(x, it_l.nd, it_r.nd));
		it_l.nd->next = it.nd;
		it_r.nd->priv = it.nd;
		return it;
	}
	Iter push_back(const int x) {
		// 1 2 3 <-
		if (this->empty()) return this->insert(Iter(last), x);
		return this->insert(Iter(last.nd->priv), x);
	}
	bool empty() {
		return first == last;
	}
	Iter begin() {
		return first;
	}
	Iter end() {
		return last;
	}
	// Distructor
	~List() {
		Iter it2;
		for (Iter it = first; it != last; it = it2) {
			it2 = it;
			it2++;
			delete it.nd;
		}
		delete last.nd;
	}
private:
	Iter first;
	Iter last;
};

int main() {
	List l;
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		int x;
		cin >> x;
		l.push_back(x);
	}
	List::Iter it;
	for (it = l.begin(); it != l.end(); ++it) {
		cout << *it << ' ';
	}
}