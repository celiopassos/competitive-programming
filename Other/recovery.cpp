bool chmin(auto& x, const auto& y) { return y < x ? (x = y, true) : false; }
bool chmax(auto& x, const auto& y) { return x < y ? (x = y, true) : false; }
 
template<typename T>
struct Recovery
{
    struct Node
    {
        T value;
        Node* prev;
        Node(T value, Node* prev) : value(value), prev(prev) { }
    };
    deque<Node> states;
    Node* create(T value, Node* prev)
    {
        return &states.emplace_back(value, prev);
    } 
    vector<T> recover(Node* last)
    {
        vector<T> res;
        while (last != nullptr)
        {
            res.push_back(last->value);
            last = last->prev;
        }
        reverse(all(res));
        return res;
    }
};
