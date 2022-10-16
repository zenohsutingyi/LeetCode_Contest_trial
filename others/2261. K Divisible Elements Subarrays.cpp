#if 0
  nums = [a1, a2, a3, ... an]
  subarray - by length
    []
    [a1], [a2], [a3], ... [an]
    [a1, a2], [a2, a3], [a3, a4], ... [an-1, an]
  subarray - by end
    [a1]
    [a1, a2], [a2]
    [a1, a2, a3], [a2, a3], [a3]
    [a1, a2, a3, a4], [a2, a3, a4], [a3, a4], [a4]


[pseudo-code]
  init trie
  init node_queue
  push tire.root into node_queue
  for num in nums:
    for node in node_queue:
      if appending num to node is valid:
        create new_node for the num appended to node
        push new_node to node_queue
        
  count the nodes in trie

[test case]
[79,88,50,63,93,15,86,94,13,79,74,2,91,46,68,27,46,17,88,41,7,13,18,32,7,49,94,37,39,51,3,1,78,61,79,1,56,22,37,5,10,68,55,73,97,40,46,49,45,79,86,19,27,95,68,81,55,59,67,96,90,42,18,18,71,37,89,40,38,55,36,75,18,37,78,18,29,77,28,61,96,58,73,20,24,41,14,58,72,82,93,70,8,32,85,81,42,16,60,61,61,44,83,2,26,35,98,38,79,70,45,74,60,83,2,87,52,94,44,93,87,22,61,44,77,66,55,62,47,21,74,73,30,68,56,22,57,52,70,5,27,30,59,90,56,72,37,21,69,17,39,15,96,29,38,21,10,74,56,7,93,95,9,73,35,11,68,57,97,14,86,19,87,13,2,90,47,78,27,25,24,2,54,95,73,13,23]
131
86
[88,1,59,1,8,1,93,51,1,21,1,93,1,55,1,1]
16
1

#endif
class Solution {
  struct Node {
    Node* AddChild(int num, int dividable_count) {
      if (children.find(num) == children.end()) {
        children[num].reset(new Node{num, dividable_count});
      }
      return children[num].get();
    }
    
    int CountNode() {
      int result = 1;
      for (auto& [child_num, child_node] : children) {
        result += child_node->CountNode();
      }
      return result;
    }
    
    int value;
    int dividable_count = 0;
    unordered_map<int, unique_ptr<Node>> children;
  };
  struct Trie {
    Trie(int k) : k(k), node_queue{&root} {}
    
    void AddNum(int num, bool is_divisible) {
      int step = (is_divisible ? 1 : 0);
      // process nodes only already in queue
      size_t size = node_queue.size();
      for (size_t i = 0; i < size; ++i) {
        auto node = node_queue.front();
        node_queue.pop_front();
        if (node->dividable_count + step > k) {
          continue;
        }
        node_queue.push_back(node->AddChild(num, node->dividable_count + step));
      }
      node_queue.push_back(root.AddChild(num, step));
    }
    
    int k = 0;
    Node root;
    deque<Node*> node_queue;
  };
public:
  int countDistinct(vector<int>& nums, int k, int p) {
    Trie trie(k);
    for (auto num : nums) {
      bool is_divisible = ((num % p) == 0);
      trie.AddNum(num, is_divisible);
    }
    return trie.root.CountNode() - 1;
  }
};
