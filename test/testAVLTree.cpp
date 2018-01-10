#include "testAVLTree.h"

using namespace std;

AVLTree *insertNodes(AVLTree &tree, const vector<int> &nodes);
bool searchNodes(const AVLTree &tree, const vector<int> &nodes);

// Empty tree
TEST(AVLTreeTest, Empty_Tree) {
    AVLTree *tree = new AVLTree();
    EXPECT_EQ(nullptr, tree->inorder());
    EXPECT_EQ(nullptr, tree->postorder());
    EXPECT_EQ(nullptr, tree->preorder());
}

// insert and search without rotation
TEST(AVLTreeTest, One_Node) {
    AVLTree *tree = new AVLTree();
    tree->insert(1);
    EXPECT_TRUE(tree->search(1));
    EXPECT_FALSE(tree->search(10));
    EXPECT_FALSE(tree->search(-1));
    EXPECT_THAT(*tree->preorder(), testing::ElementsAre(1));
    EXPECT_THAT(*tree->inorder(), testing::ElementsAre(1));
    EXPECT_THAT(*tree->postorder(), testing::ElementsAre(1));
}

TEST(AVLTreeTest, Root_With_Child_Left) {
    AVLTree *tree = new AVLTree();
    tree->insert(2);
    tree->insert(1);
    EXPECT_TRUE(tree->search(1));
    EXPECT_TRUE(tree->search(2));
    EXPECT_THAT(*tree->preorder(), testing::ElementsAre(2, 1));
    EXPECT_THAT(*tree->inorder(), testing::ElementsAre(1, 2));
    EXPECT_THAT(*tree->postorder(), testing::ElementsAre(1, 2));
}

TEST(AVLTreeTest, Root_With_Child_Right) {
    AVLTree *tree = new AVLTree();
    tree->insert(2);
    tree->insert(3);
    EXPECT_TRUE(tree->search(2));
    EXPECT_TRUE(tree->search(3));
    EXPECT_THAT(*tree->preorder(), testing::ElementsAre(2, 3));
    EXPECT_THAT(*tree->inorder(), testing::ElementsAre(2, 3));
    EXPECT_THAT(*tree->postorder(), testing::ElementsAre(3, 2));
}

TEST(AVLTreeTest, Root_With_two_Children) {
    AVLTree *tree = new AVLTree();
    tree->insert(2);
    tree->insert(3);
    tree->insert(1);
    EXPECT_TRUE(tree->search(2));
    EXPECT_TRUE(tree->search(3));
    EXPECT_TRUE(tree->search(1));
    EXPECT_THAT(*tree->preorder(), testing::ElementsAre(2, 1, 3));
    EXPECT_THAT(*tree->inorder(), testing::ElementsAre(1, 2 ,3));
    EXPECT_THAT(*tree->postorder(), testing::ElementsAre(1, 3, 2));
}

//Insert and search with root rotation
TEST(AVLTreeTest, Rotate_Root_Left_Three_Nodes) {
    AVLTree *tree = new AVLTree();
    tree = insertNodes(*tree, {4, 6, 8});
    EXPECT_TRUE(searchNodes(*tree, {4, 6, 8}));
    EXPECT_THAT(*tree->preorder(), testing::ElementsAre(6, 4, 8));
    EXPECT_THAT(*tree->inorder(), testing::ElementsAre(4, 6, 8));
    EXPECT_THAT(*tree->postorder(), testing::ElementsAre(4, 8, 6));
}

TEST(AVLTreeTest, Rotate_Root_Right_Three_Nodes) {
    AVLTree *tree = new AVLTree();
    tree = insertNodes(*tree, {4, 8, 6});
    EXPECT_TRUE(searchNodes(*tree, {4, 8, 6}));
    EXPECT_THAT(*tree->preorder(), testing::ElementsAre(6, 4, 8));
    EXPECT_THAT(*tree->inorder(), testing::ElementsAre(4, 6, 8));
    EXPECT_THAT(*tree->postorder(), testing::ElementsAre(4, 8, 6));
}

TEST(AVLTreeTest, Rotate_Root_Left_Right_Three_Nodes) {
    AVLTree *tree = new AVLTree();
    tree = insertNodes(*tree, {8, 4, 6});
    EXPECT_TRUE(searchNodes(*tree, {8, 4, 6}));
    EXPECT_THAT(*tree->preorder(), testing::ElementsAre(6, 4, 8));
    EXPECT_THAT(*tree->inorder(), testing::ElementsAre(4, 6, 8));
    EXPECT_THAT(*tree->postorder(), testing::ElementsAre(4, 8, 6));
}

TEST(AVLTreeTest, Rotate_Root_Right_Left_Three_Nodes) {
    AVLTree *tree = new AVLTree();
    tree = insertNodes(*tree, {4, 8, 6});
    EXPECT_TRUE(searchNodes(*tree, {4, 8, 6}));
    EXPECT_THAT(*tree->preorder(), testing::ElementsAre(6, 4, 8));
    EXPECT_THAT(*tree->inorder(), testing::ElementsAre(4, 6, 8));
    EXPECT_THAT(*tree->postorder(), testing::ElementsAre(4, 8, 6));
}

TEST(AVLTreeTest, Rotate_Root_Left_Six_Nodes) {
    AVLTree *tree = new AVLTree();
    tree = insertNodes(*tree, {4, 2, 8, 6, 10, 12});
    EXPECT_TRUE(searchNodes(*tree, {4, 2, 8, 6, 10, 12}));
    EXPECT_THAT(*tree->preorder(), testing::ElementsAre(8, 4, 2, 6, 10, 12));
    EXPECT_THAT(*tree->inorder(), testing::ElementsAre(2, 4, 6, 8, 10, 12));
    EXPECT_THAT(*tree->postorder(), testing::ElementsAre(2, 6, 4, 12, 10, 8));
}

TEST(AVLTreeTest, Rotate_Root_Right_Six_Nodes) {
    AVLTree *tree = new AVLTree();
    tree = insertNodes(*tree, {10, 6, 4, 8, 2, 12});
    EXPECT_TRUE(searchNodes(*tree, {10, 6, 4, 8, 2, 12}));
    EXPECT_THAT(*tree->preorder(), testing::ElementsAre(6, 4, 2, 10, 8, 12));
    EXPECT_THAT(*tree->inorder(), testing::ElementsAre(2, 4, 6, 8, 10, 12));
    EXPECT_THAT(*tree->postorder(), testing::ElementsAre(2, 4, 8, 12, 10, 6));
}

TEST(AVLTreeTest, Rotate_Root_Left_Right_Six_Nodes) {
    AVLTree *tree = new AVLTree();
    tree = insertNodes(*tree, {8, 4, 2, 6, 12, 7});
    EXPECT_TRUE(searchNodes(*tree, {8, 4, 2, 6, 12, 7}));
    EXPECT_THAT(*tree->preorder(), testing::ElementsAre(6, 4, 2, 8, 7, 12));
    EXPECT_THAT(*tree->inorder(), testing::ElementsAre(2, 4, 6, 7, 8, 12));
    EXPECT_THAT(*tree->postorder(), testing::ElementsAre(2, 4, 7, 12, 8, 6));
}

TEST(AVLTreeTest, Rotate_Root_Right_Left_Six_Nodes) {
    AVLTree *tree = new AVLTree();
    tree = insertNodes(*tree, {4, 2, 8, 6, 12, 5});
    EXPECT_TRUE(searchNodes(*tree, {4, 2, 8, 6, 12, 5}));
    EXPECT_THAT(*tree->preorder(), testing::ElementsAre(6, 4, 2, 5, 8, 12));
    EXPECT_THAT(*tree->inorder(), testing::ElementsAre(2, 4, 5, 6, 8, 12));
    EXPECT_THAT(*tree->postorder(), testing::ElementsAre(2, 5, 4, 12, 8, 6));
}

// Insert and search with inner node rotation
TEST(AVLTreeTest, Rotate_Inner_Node_Left_Six_Nodes) {
    AVLTree *tree = new AVLTree();
    tree = insertNodes(*tree, {8, 4, 6, 7, 10, 12});
    EXPECT_TRUE(searchNodes(*tree, {8, 4, 6, 7, 10, 12}));
    EXPECT_THAT(*tree->preorder(), testing::ElementsAre(8, 6, 4, 7, 10, 12));
    EXPECT_THAT(*tree->inorder(), testing::ElementsAre(4, 6, 7, 8, 10, 12));
    EXPECT_THAT(*tree->postorder(), testing::ElementsAre(4, 7, 6, 12, 10, 8));
}

TEST(AVLTreeTest, Rotate_Inner_Node_Right_Six_Nodes) {
    AVLTree *tree = new AVLTree();
    tree = insertNodes(*tree, {8, 6, 10, 4, 12, 2});
    EXPECT_TRUE(searchNodes(*tree, {8, 6, 4, 2, 10, 12}));
    EXPECT_THAT(*tree->preorder(), testing::ElementsAre(8, 4, 2, 6, 10, 12));
    EXPECT_THAT(*tree->inorder(), testing::ElementsAre(2, 4, 6, 8, 10, 12));
    EXPECT_THAT(*tree->postorder(), testing::ElementsAre(2, 6, 4, 12, 10, 8));
}

TEST(AVLTreeTest, Rotate_Inner_Node_Left_Right_Six_Nodes) {
    AVLTree *tree = new AVLTree();
    tree = insertNodes(*tree, {8, 6, 10, 4, 12, 5});
    EXPECT_TRUE(searchNodes(*tree, {8, 6, 10, 4, 12, 5}));
    EXPECT_THAT(*tree->preorder(), testing::ElementsAre(8, 5, 4, 6, 10, 12));
    EXPECT_THAT(*tree->inorder(), testing::ElementsAre(4, 5, 6, 8, 10, 12));
    EXPECT_THAT(*tree->postorder(), testing::ElementsAre(4, 6, 5, 12, 10, 8));
}

TEST(AVLTreeTest, Rotate_Inner_Node_Right_Left_Six_Nodes) {
    AVLTree *tree = new AVLTree();
    tree = insertNodes(*tree, {8, 4, 10, 2, 12, 11});
    EXPECT_TRUE(searchNodes(*tree, {8, 11, 10, 4, 12, 2}));
    EXPECT_THAT(*tree->preorder(), testing::ElementsAre(8, 4, 2, 11, 10, 12));
    EXPECT_THAT(*tree->inorder(), testing::ElementsAre(2, 4, 8, 10, 11, 12));
    EXPECT_THAT(*tree->postorder(), testing::ElementsAre(2, 4, 10, 12, 11, 8));
}

// Remove root without rotation
TEST(AVLTreeTest, Remove_EmptyTree) {
    AVLTree *tree = new AVLTree();
    tree->remove(2);
    EXPECT_EQ(nullptr, tree->inorder());
    EXPECT_EQ(nullptr, tree->postorder());
    EXPECT_EQ(nullptr, tree->preorder());
}

TEST(AVLTreeTest, Remove_Root_Without_Children) {
    AVLTree *tree = new AVLTree();
    tree->insert(2);
    tree->remove(2);
    EXPECT_FALSE(searchNodes(*tree, {2}));
    EXPECT_EQ(nullptr, tree->inorder());
    EXPECT_EQ(nullptr, tree->postorder());
    EXPECT_EQ(nullptr, tree->preorder());
}

TEST(AVLTreeTest, Remove_Root_With_Child_Left) {
    AVLTree *tree = new AVLTree();
    insertNodes(*tree, {2, 1});
    tree->remove(2);
    EXPECT_FALSE(searchNodes(*tree, {2}));
    EXPECT_THAT(*tree->preorder(), testing::ElementsAre(1));
    EXPECT_THAT(*tree->inorder(), testing::ElementsAre(1));
    EXPECT_THAT(*tree->postorder(), testing::ElementsAre(1));
}

TEST(AVLTreeTest, Remove_Root_With_Child_Right) {
    AVLTree *tree = new AVLTree();
    insertNodes(*tree, {2, 3});
    tree->remove(2);
    EXPECT_FALSE(searchNodes(*tree, {2}));
    EXPECT_THAT(*tree->preorder(), testing::ElementsAre(3));
    EXPECT_THAT(*tree->inorder(), testing::ElementsAre(3));
    EXPECT_THAT(*tree->postorder(), testing::ElementsAre(3));
}

TEST(AVLTreeTest, Remove_Root_With_Two_Children) {
    AVLTree *tree = new AVLTree();
    insertNodes(*tree, {2, 3, 1});
    tree->remove(2);
    EXPECT_FALSE(searchNodes(*tree, {2}));
    EXPECT_THAT(*tree->preorder(), testing::ElementsAre(3, 1));
    EXPECT_THAT(*tree->inorder(), testing::ElementsAre(1, 3));
    EXPECT_THAT(*tree->postorder(), testing::ElementsAre(1, 3));
}

// Remove root with rotation
TEST(AVLTreeTest, Remove_Root_Rotate_Right) {
    AVLTree *tree = new AVLTree();
    insertNodes(*tree, {6, 4, 8, 2, 5, 7, 3});
    tree->remove(6);
    EXPECT_FALSE(searchNodes(*tree, {6}));
    EXPECT_THAT(*tree->preorder(), testing::ElementsAre(4, 2, 3, 7, 5, 8));
    EXPECT_THAT(*tree->inorder(), testing::ElementsAre(2, 3, 4, 5, 7, 8));
    EXPECT_THAT(*tree->postorder(), testing::ElementsAre(3, 2, 5, 8, 7, 4));
}

TEST(AVLTreeTest, Remove_Root_Rotate_Left_Right) {
    AVLTree *tree = new AVLTree();
    insertNodes(*tree, {8, 4, 10, 2, 6, 9, 5});
    tree->remove(8);
    EXPECT_FALSE(searchNodes(*tree, {8}));
    EXPECT_THAT(*tree->preorder(), testing::ElementsAre(6, 4, 2, 5, 9, 10));
    EXPECT_THAT(*tree->inorder(), testing::ElementsAre(2, 4, 5, 6, 9, 10));
    EXPECT_THAT(*tree->postorder(), testing::ElementsAre(2, 5, 4, 10, 9, 6));
}

// Remove leaf without rotation
TEST(AVLTreeTest, Remove_One_Leaf_Left) {
    AVLTree *tree = new AVLTree();
    insertNodes(*tree, {4, 2, 5, 1});
    tree->remove(1);
    EXPECT_FALSE(tree->search(1));
    EXPECT_THAT(*tree->preorder(), testing::ElementsAre(4, 2, 5));
    EXPECT_THAT(*tree->inorder(), testing::ElementsAre(2, 4, 5));
    EXPECT_THAT(*tree->postorder(), testing::ElementsAre(2, 5, 4));
}

TEST(AVLTreeTest, Remove_One_Leaf_Right) {
    AVLTree *tree = new AVLTree();
    insertNodes(*tree, {4, 2, 5, 3});
    tree->remove(3);
    EXPECT_FALSE(tree->search(3));
    EXPECT_THAT(*tree->preorder(), testing::ElementsAre(4, 2, 5));
    EXPECT_THAT(*tree->inorder(), testing::ElementsAre(2, 4, 5));
    EXPECT_THAT(*tree->postorder(), testing::ElementsAre(2, 5, 4));
}

TEST(AVLTreeTest, Remove_One_Leaf_Of_Two_Left) {
    AVLTree *tree = new AVLTree();
    insertNodes(*tree, {6, 4, 8, 2, 5});
    tree->remove(2);
    EXPECT_FALSE(tree->search(2));
    EXPECT_THAT(*tree->preorder(), testing::ElementsAre(6, 4, 5, 8));
    EXPECT_THAT(*tree->inorder(), testing::ElementsAre(4, 5, 6, 8));
    EXPECT_THAT(*tree->postorder(), testing::ElementsAre(5, 4, 8, 6));
}

TEST(AVLTreeTest, Remove_One_Leaf_Of_Two_Right) {
    AVLTree *tree = new AVLTree();
    insertNodes(*tree, {6, 4, 2, 8});
    tree->remove(2);
    EXPECT_FALSE(tree->search(2));
    EXPECT_THAT(*tree->preorder(), testing::ElementsAre(6, 4, 8));
    EXPECT_THAT(*tree->inorder(), testing::ElementsAre(4, 6, 8));
    EXPECT_THAT(*tree->postorder(), testing::ElementsAre(4, 8, 6));
}

// Remove inner node without rotation
TEST(AVLTreeTest, Remove_Inner_Node_With_One_Child_Left) {
    AVLTree *tree = new AVLTree();
    insertNodes(*tree, {4, 3, 5, 2});
    tree->remove(3);
    EXPECT_FALSE(tree->search(3));
    EXPECT_THAT(*tree->preorder(), testing::ElementsAre(4, 2, 5));
    EXPECT_THAT(*tree->inorder(), testing::ElementsAre(2, 4, 5));
    EXPECT_THAT(*tree->postorder(), testing::ElementsAre(2, 5, 4));
}

TEST(AVLTreeTest, Remove_Inner_Node_With_One_Child_Right) {
    AVLTree *tree = new AVLTree();
    insertNodes(*tree, {4, 2, 5, 3});
    tree->remove(2);
    EXPECT_FALSE(tree->search(2));
    EXPECT_THAT(*tree->preorder(), testing::ElementsAre(4, 3, 5));
    EXPECT_THAT(*tree->inorder(), testing::ElementsAre(3, 4, 5));
    EXPECT_THAT(*tree->postorder(), testing::ElementsAre(3, 5, 4));
}

TEST(AVLTreeTest, Remove_Inner_Node_With_Two_Children) {
    AVLTree *tree = new AVLTree();
    insertNodes(*tree, {6, 4, 8, 2, 5});
    tree->remove(4);
    EXPECT_FALSE(tree->search(4));
    EXPECT_THAT(*tree->preorder(), testing::ElementsAre(6, 5, 2, 8));
    EXPECT_THAT(*tree->inorder(), testing::ElementsAre(2, 5, 6, 8));
    EXPECT_THAT(*tree->postorder(), testing::ElementsAre(2, 5, 8, 6));
}

/*
 * Adds nodes from vector to a tree.
 * Returns this tree.
 */
AVLTree *insertNodes(AVLTree &tree, const vector<int> &nodes) {
    for(auto it = nodes.begin(); it < nodes.end(); it++)
        tree.insert(*it);
    return &tree;
}

/*
 * Searches for nodes from vector in a tree.
 * Gives true, if all nodes were found. False, if not.
 */
bool searchNodes(const AVLTree &tree, const vector<int> &nodes) {
    for(auto it = nodes.begin(); it < nodes.end(); it++) {
        if(!tree.search(*it))
            return false;
    }
    return true;
}
