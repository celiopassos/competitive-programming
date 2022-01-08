template<typename T>
struct ImplicitSegmentTree {
    struct Node {
        T value = T();
        Node *left = nullptr, *right = nullptr;
        int l, r, m, tag;
        Node(int l, int r, int tag) : l(l), r(r), m((l + r) / 2), tag(tag) {}
    };
    int num_tags = 0;
    std::deque<Node> deq;
    Node* create(int l, int r, int tag = -1) {
        return &deq.emplace_back(l, r, tag == -1 ? num_tags++ : tag);
    }
    Node* copy(Node* p, int tag = -1) {
        Node* q = &deq.emplace_back(*p);
        q->tag = tag == -1 ? num_tags++ : tag;
        return q;
    }
    Node* get_left(Node* p) {
        if (p->left == nullptr) {
            p->left = create(p->l, p->m, p->tag);
        } else if (p->left->tag != p->tag) {
            p->left = copy(p->left, p->tag);
        }
        return p->left;
    }
    Node* get_right(Node* p) {
        if (p->right == nullptr) {
            p->right = create(p->m, p->r, p->tag);
        } else if (p->right->tag != p->tag) {
            p->right = copy(p->right, p->tag);
        }
        return p->right;
    }
    T get_value(Node* p) {
        return p ? p->value : T();
    }
    void modify(Node* p, int i, T value) {
        if (p->l + 1 == p->r) {
            p->value = value;
        } else {
            modify(i < p->m ? get_left(p) : get_right(p), i, value);
            p->value = get_value(p->left) + get_value(p->right);
        }
    }
    T query(Node* p, int ql, int qr) const {
        if (p == nullptr || p->r <= ql || qr <= p->l) {
            return T();
        } else if (ql <= p->l && p->r <= qr) {
            return p->value;
        } else {
            return query(p->left, ql, qr) + query(p->right, ql, qr);
        }
    }
    template<typename Iterator>
    void build(Node* p, Iterator first) {
        if (p->l + 1 == p->r) {
            p->value = first[p->l];
        } else {
            build(get_left(p), first);
            build(get_right(p), first);
            p->value = p->left->value + p->right->value;
        }
    }
    template<typename Iterator>
    Node* build(Iterator first, Iterator last) {
        Node* root = create(0, last - first, num_tags++);
        build(root, first);
        return root;
    }
    // merges in p 'into' q
    template<typename LeafMerger>
    void merge(Node* p, Node* q, LeafMerger&& leaf_merger) {
        if (p == nullptr) {
            return;
        } else if (p->l + 1 < p->r) {
            if (q->left == nullptr) {
                q->left = p->left;
            } else {
                merge(p->left, get_left(q), leaf_merger);
            }
            if (q->right == nullptr) {
                q->right = p->right;
            } else {
                merge(p->right, get_right(q), leaf_merger);
            }
            q->value = get_value(q->left) + get_value(q->right);
        } else {
            q->value = leaf_merger(p->value, q->value);
        }
    }
    void merge(Node* p, Node* q) {
        merge(p, q, std::plus<T>());
    }
};
