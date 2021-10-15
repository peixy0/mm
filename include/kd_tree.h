#pragma once

#include <algorithm>
#include <gsl/gsl>
#include <stdexcept>
#include <vector>

#include "linear_alg.h"

namespace kd_tree {
template <typename>
class Tree;

template <std::size_t N, typename ValueT>
class Tree<linear_alg::V<N, ValueT>> {
  using NodeT = linear_alg::V<N, ValueT>;
  struct Node;

  struct NearestNode {
    const Node* node;
    ValueT dist;
  };

  struct Node {
    explicit Node(const NodeT& v) : value{v} {}
    NodeT value;
    std::size_t index;
    Node* left{nullptr};
    Node* right{nullptr};

    NearestNode FindNearest(const NodeT& node) const {
      auto v = node - value;
      auto d = v.T() * v;
      NearestNode result{this, d(0)};

      Node* firstChild = left;
      Node* secondChild = right;
      if (node(index) > value(index)) {
        firstChild = right;
        secondChild = left;
      }
      if (firstChild != nullptr) {
        auto r = firstChild->FindNearest(node);
        if (r.dist < result.dist) {
          result = r;
        }
      }
      auto vsplit = node(index) - value(index);
      auto dsplit = vsplit * vsplit;
      if (dsplit < result.dist and secondChild != nullptr) {
        auto r = secondChild->FindNearest(node);
        if (r.dist < result.dist) {
          result = r;
        }
      }
      return result;
    }
  };

public:
  explicit Tree(gsl::span<NodeT> s) : nodes(s.begin(), s.end()) {
    root = MakeTree(nodes.begin(), nodes.end(), 0);
  }
  ~Tree() = default;

  Tree(const Tree<NodeT>&) = default;
  Tree(Tree<NodeT>&&) = default;
  Tree<NodeT>& operator=(const Tree<NodeT>&) = default;
  Tree<NodeT>& operator=(Tree<NodeT>&&) = default;

  bool Empty() const {
    return root == nullptr;
  }

  NodeT FindNearest(const NodeT& node) const {
    if (Empty()) {
      throw std::logic_error("empty KD-Tree");
    }
    return root->FindNearest(node).node->value;
  }

private:
  Node* MakeTree(const typename std::vector<Node>::iterator& begin, const typename std::vector<Node>::iterator& end,
                 std::size_t index) {
    if (begin == end) {
      return nullptr;
    }
    auto m = FindMedium(begin, end, index);
    auto& r = *m;
    r.index = index;
    index = (index + 1) % N;
    r.left = MakeTree(begin, m, index);
    r.right = MakeTree(m + 1, end, index);
    return &r;
  }

  typename std::vector<Node>::iterator FindMedium(const typename std::vector<Node>::iterator& begin,
                                                  const typename std::vector<Node>::iterator& end, std::size_t index) {
    auto n = (end - begin) / 2;
    auto medium = begin + n;
    std::nth_element(begin, medium, end,
                     [index](const Node& lhs, const Node& rhs) { return lhs.value(index) < rhs.value(index); });
    return medium;
  }

  std::vector<Node> nodes;
  Node* root{nullptr};
};
}  // namespace kd_tree
