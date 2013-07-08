/*
 * Exercise 13.28: Given the following classes, implement a default constructor
 * and the necessary copy-control members.
 *     (a) class TreeNode {
 *          private:
 *           std::string value;
 *           int count;
 *           TreeNode *left;
 *           TreeNode *right;
 *         };
 *
 *     (b) class BinStrTree {
 *          private:
 *           TreeNode *root;
 *         };
 */

#ifndef CHAPTER_13_EXERCISE_28_H_
#define CHAPTER_13_EXERCISE_28_H_

#include <string>   // std::string
#include <utility>  // std::swap

/**
 * @brief Node in a binary string tree
 *
 * Manages string value and child nodes with proper deep copying behavior.
 * Implements full copy control for tree node structures.
 */
class TreeNode {
 public:
  /**
   * @brief Default constructor
   * @param val String value (default empty)
   * @param cnt Count value (default 0)
   * Time Complexity O(1)
   * Space Complexity O(1)
   */
  explicit TreeNode(const std::string &val = std::string(), int cnt = 0)
      : value(val), count(cnt), left(nullptr), right(nullptr) {}

  /**
   * @brief Copy constructor performs deep copy of subtree rooted at other
   * @param other TreeNode to copy from
   * @details Recursively copies the entire subtree structure.
   * Time Complexity O(n) where n is nodes in subtree
   * Space Complexity O(n) for the copied nodes
   */
  TreeNode(const TreeNode &other)
      : value(other.value),
        count(other.count),
        left(nullptr != other.left ? new TreeNode(*other.left) : nullptr),
        right(nullptr != other.right ? new TreeNode(*other.right) : nullptr) {}

  /**
   * @brief Destructor recursively deletes subtree
   * Time Complexity O(n) where n is nodes in subtree
   * Space Complexity O(h) where h is tree height (recursion stack)
   */
  ~TreeNode() {
    delete left;
    delete right;
  }

  /**
   * @brief Copy-assignment operator using copy-and-swap
   * @param rhs TreeNode to assign from
   * @return Reference to this node
   * @Time Complexity O(n) where n is nodes in both subtrees
   * @Space Complexity O(n) during copy
   */
  TreeNode &operator=(const TreeNode &rhs) {
    TreeNode temp(rhs);
    Swap(temp);
    return *this;
  }

  /**
   * @brief Swaps contents with another TreeNode
   * @param other TreeNode to swap with
   * @Time Complexity O(1)
   */
  void Swap(TreeNode &other) noexcept {
    std::swap(value, other.value);
    std::swap(count, other.count);
    std::swap(left, other.left);
    std::swap(right, other.right);
  }

 private:
  std::string value;  // The string value stored in this node
  int count;          // Frequency count or balancing info (if applicable)
  TreeNode *left;     // Pointer to left child node
  TreeNode *right;    // Pointer to right child node
};

/**
 * @brief Binary string tree container
 *
 * Manages tree root with proper deep copying and destruction.
 * Implements full copy control for tree structures.
 */
class BinStrTree {
 public:
  /**
   * @brief Default constructor creates empty tree
   * Time Complexity O(1)
   * Space Complexity O(1)
   */
  BinStrTree() : root(nullptr) {}

  /**
   * @brief Constructs tree with given root node
   * @param root TreeNode to use as root (copies recursively)
   * @Time Complexity O(n) where n is nodes in tree
   * @Space Complexity O(n) for the copied tree
   */
  explicit BinStrTree(const TreeNode &root) : root(new TreeNode(root)) {}

  /**
   * @brief Copy constructor performs deep copy of tree
   * @param other BinStrTree to copy from
   * Time Complexity O(n) where n is nodes in tree
   * Space Complexity O(n) for the copied tree
   */
  BinStrTree(const BinStrTree &other)
      : root(other.root ? new TreeNode(*other.root) : nullptr) {}

  /**
   * @brief Destructor deletes entire tree
   * Time Complexity O(n) where n is nodes in tree
   * Space Complexity O(h) where h is tree height
   */
  ~BinStrTree() { delete root; }

  /**
   * @brief Copy-assignment operator using copy-and-swap
   * @param rhs BinStrTree to assign from
   * @return Reference to this tree
   * Time Complexity O(n) where n is nodes in both trees
   * Space Complexity O(n) during copy
   */
  BinStrTree &operator=(const BinStrTree &rhs) {
    BinStrTree temp(rhs);
    Swap(temp);
    return *this;
  }

  /**
   * @brief Swaps contents with another BinStrTree
   * @param other BinStrTree to swap with
   * Time Complexity O(1)
   */
  void Swap(BinStrTree &other) { std::swap(root, other.root); }

 private:
  TreeNode *root;
};

#endif  // CHAPTER_13_EXERCISE_28_H_
