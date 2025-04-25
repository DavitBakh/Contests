#include <iostream>
#include <string>

class Trie
{
	struct Node
	{
		bool endOfWord;
		Node* children[26];

		Node() : endOfWord(false)
		{
			for (int i = 0; i < 26; i++)
				children[i] = nullptr;
		}
	};

	Node* root;

public:
	Trie() : root(new Node) {}

	void insert(std::string& word)
	{
		Node* node = root;
		for (char c : word)
		{
			int index = c - 'a';
			if (!node->children[index])
				node->children[index] = new Node();

			node = node->children[index];
		}
		node->endOfWord = true;
	}

	bool search(std::string& word)
	{
		Node* node = root;
		for (char c : word)
		{
			int index = c - 'a';
			if (!node->children[index])
				return false;

			node = node->children[index];
		}
		return node->endOfWord;
	}

	bool startsWith(std::string& prefix)
	{
		Node* node = root;
		for (char c : prefix)
		{
			int index = c - 'a';
			if (!node->children[index])
				return false;

			node = node->children[index];
		}
		return true;
	}

	void deleteWord(std::string& word)
	{
		Node* node = root;
		for (char c : word)
		{
			int index = c - 'a';
			if (!node->children[index])
				return;
			node = node->children[index];
		}

		if (node->endOfWord == true)
			node->endOfWord = false;
	}

	void print(Node* node, std::string prefix) const
	{
		if (node->endOfWord)
			std::cout << prefix << std::endl;

		for (int i = 0; i < 26; i++)
			if (node->children[i])
				print(node->children[i], prefix + char('a' + i));
	}


	void print() const { print(root, ""); }
};