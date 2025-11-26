void dfsRecursive(Node* node) {
    if (!node) return;

    std::cout << node->val << " ";

    for (Node* child : node->children) {
        dfsRecursive(child);
    }
}

void dfsIterative(Node* root) {
    if (!root) return;

    std::stack<Node*> s;
    s.push(root);

    while (!s.empty()) {
        Node* curr = s.top();
        s.pop();

        std::cout << curr->val << " ";

        for (auto it = curr->children.rbegin(); it != curr->children.rend(); ++it) {
            s.push(*it);
        }
    }
}

void bfsIterative(Node* root) {
    if (!root) return;

    std::queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();

        std::cout << curr->val << " ";

        for (Node* child : curr->children) {
            q.push(child);
        }
    }
}

void bfsRecursiveHelper(std::queue<Node*>& q) {
    if (q.empty()) return;

    Node* curr = q.front();
    q.pop();

    std::cout << curr->val << " ";

    for (Node* child : curr->children) {
        q.push(child);
    }

    bfsRecursiveHelper(q);
}

void bfsRecursive(Node* root) {
    if (!root) return;
    std::queue<Node*> q;
    q.push(root);
    bfsRecursiveHelper(q);
}

void deleteTree(Node* root) {
    if (!root) return;

    for (Node* child : root->children) {
        deleteTree(child);
    }

    delete root;
}