#pragma once
#include <gtest.h>
#include <redblacktree.h>
#include <algorithm>
#include <random>
#include <vector>
using namespace std;
TEST(RedBlackTreeTest, Insert) {
    RedBlackTree<int, int> tree;

    tree.insert(5, 5);
    tree.insert(3, 3);
    tree.insert(7, 7);

	ASSERT_NO_THROW(tree.find(5));
	ASSERT_NO_THROW(tree.find(3));
	ASSERT_NO_THROW(tree.find(7));
}

TEST(RedBlackTreeTest, Remove) {
    RedBlackTree<int, int> tree;

    tree.insert(5, 5);
    tree.insert(3, 3);

    tree.remove(5);

    ASSERT_ANY_THROW(tree.find(5));
    ASSERT_NO_THROW(tree.find(3));
}

TEST(RedBlackTreeTest, InsertAndSearch) {
    RedBlackTree<int, int> tree;

    tree.insert(5,5);
	ASSERT_ANY_THROW(tree.find(3));

    ASSERT_NO_THROW(tree.find(5));
}

TEST(RedBlackTreeTest, RemoveandSearch) {
    RedBlackTree<int, int> tree;

    tree.insert(5,5);
    tree.insert(10, 10);

    ASSERT_NO_THROW(tree.find(5));
    tree.remove(5);
    ASSERT_ANY_THROW(tree.find(5));
}
TEST(RedBlackTreeTest, Iterator) {
    RedBlackTree<int, int> tree;
    tree.insert(10,10);
    tree.insert(5,5);
    tree.insert(15, 15);
    auto it = tree.begin();
    EXPECT_EQ(*it, 5);

    ++it;
    EXPECT_EQ(*it, 10);

    ++it;
    EXPECT_EQ(*it, 15);
}
TEST(RedBlackTreeTest, BigTree) {
	const int N = 1000;
	RedBlackTree<int, int> tree;
	for (int i = 0; i < N; i++) {
		tree.insert(i, i);
	}
	for (auto it = tree.begin(); it != tree.end(); ++it) {
		it->data++;
	}
	for (int i = 0; i < N; i++) {
		EXPECT_EQ(i + 1, tree.find(i)->data);
	}
}
TEST(RedBlackTreeTest, BigTreeOperator) {
	const int N = 1000;
	RedBlackTree<int, int> tree;
	for (int i = 0; i < N; i++) {
		tree.insert(i, i);
	}
	for (int i = 0; i < N; i++) {
		tree[i]++;
	}
	for (int i = 0; i < N; i++) {
		EXPECT_EQ(i + 1, tree[i]);
	}
}
TEST(RedBlackTreeTest, BigRandomInsert) {
	const int N = 15;
	vector<int> ar;
	RedBlackTree<int, int> tree;
	for (int i = 0; i < N; i++) {
		ar.push_back(i);
	}
	random_device rd;
	mt19937 g(rd());
	shuffle(ar.begin(), ar.end(), g);
	for (int i = 0; i < N; i++) {
		tree.insert(ar[i], ar[i]);
		EXPECT_TRUE(tree.checkconditions(tree.rootfind()));
	}
	tree.display();
}

/*TEST(AVLTreeTest, BigRandomRemove) {
	const int N = 500;
	vector<int> ar;
	RedBlackTree<int, int> tree;
	for (int i = 0; i < N; i++) {
		ar.push_back(i);
	}
	random_device rd;
	mt19937 g(rd());
	shuffle(ar.begin(), ar.end(), g);
	for (int i = 0; i < N; i++) {
		tree.insert(ar[i], ar[i]);
	}
	shuffle(ar.begin(), ar.end(), g);
	for (int i = 0; i < N; i++) {
		tree.remove(ar[i]);
	    EXPECT_TRUE(tree.checkconditions());
	}
}
TEST(AVLTreeTest, BigRandomInsertAndRemove) {
	const int N = 1000;
	AVLTree<int, int> tree;
	vector<int> ar;
	for (int i = 0; i < N; i++) {
		ar.push_back(i);
	}
	random_device rd;
	mt19937 g(rd());
	shuffle(ar.begin(), ar.end(), g);
	for (int i = 0; i < N; i++) {
		tree.insert(ar[i], ar[i]);
	}
	bool balance = tree.checkbalance();
	vector<int> ar2;
	for (int i = 1000; i < 1100; i++) {
		ar2.push_back(i);
	}
	int j = 0;
	while (tree.rootfind()->data < 400 && balance != false) {
		shuffle(ar2.begin(), ar2.end(), g);
		for (int i = 0; i < 100; i++) {
			tree.insert(ar2[i], ar2[i]);
			balance = tree.checkbalance();
		}
		shuffle(ar2.begin(), ar2.end(), g);
		for (int i = 0; i < 100; i++) {
			tree.remove(ar2[i]);
			balance = tree.checkbalance();
		}
		j++;
	}
	if (balance == true) {
		cout << 1 <<" "<< j;
	}
	else {
		cout << 0 <<" "<< j;
	}
}*/
