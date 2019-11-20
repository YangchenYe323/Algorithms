#include<iostream>
#include<vector>
#include<queue>
#define MAGIC_NUMBER 23 //the number we're interested in
using namespace std;

typedef struct vertex{
	int id;
	int height;
	vector<vertex*> * children;
	vertex* parent;
} node;

/*
build a matrix multiplication tree and find the first appearance of
a node with id 23.
*/
int find23(){

	//use bfs
	queue<node*> bfs{};

	//initialize root node
	node * root = (node*)malloc(sizeof(node));
	root-> id = 1;
	root-> height = 0;
	root-> children = new vector<vertex*>{};
	root-> parent = nullptr;

	bfs.push(root);

	while (!bfs.empty()){

		node* cur = bfs.front();
		bfs.pop();
		//find the first appearance of 23
		if (cur->id == MAGIC_NUMBER){
			return cur->height;
		}

		//add children to the root node by the given algorithm
		node * iter = cur;
		while (iter != nullptr){
			int next = iter->id + cur->id;
			node* next_node = (node*)malloc(sizeof(node));;
			next_node->id = next;
			next_node->height = cur->height + 1;
			next_node->children = new vector<vertex*>{};
			next_node->parent = cur;
			(*cur->children).push_back(next_node);
			bfs.push(next_node);

			iter = iter->parent;
		}

	}

}

int main(){

	cout << find23() << endl;

}


