#include<iostream>
#include<vector>
#include<algorithm>
#include <sstream>
using namespace std;

class Node
{
public:
    Node *parent;
    vector<Node *> arr;
    Node *rightChild;
    Node *leftChild;
    int key;
    int value;
    bool makeB;
    Node(Node *p, vector<Node *> ca, Node *right, Node *left, int key, int val)
    {
        parent = p;
        arr = ca;
        rightChild = right;
        leftChild = left;
        this->key = key;
        this->value = val;
    }
};

class fibonacciHeap
{
public:
    Node *maxN;
    vector<Node *> Rootarr;

    fibonacciHeap()
    {
        maxN = NULL;
        Rootarr.resize(100000,NULL);
    }
    fibonacciHeap(Node *maxN, vector<Node *> &Rootarr)
    {
        this->maxN = maxN;
        this->Rootarr = Rootarr;
    }

    void updateNode(Node* node)
{
    if (node != NULL)
    {
        if (node->leftChild !=NULL)
        {
            node->leftChild->rightChild = node->rightChild;
        }
        if (node->rightChild != NULL)
        {
            node->rightChild->leftChild = node->leftChild;
        }
    }
}


void removeMaxNodeFromList(Node* temp) {
    temp->leftChild->rightChild = temp->rightChild;
    temp->rightChild->leftChild = temp->leftChild;
    Rootarr[temp->key] = nullptr;
    delete temp;
}

void checkNodes(vector<Node*>& nodes) {
    Node *n = maxN;
    vector<Node *> NodeSet;
    do {
        NodeSet.push_back(n);
        n = n->rightChild;
    } while (n != maxN);
    for (auto n : NodeSet) {
        nodeCheck(nodes, n);
    }
}

    int extract_max()
    {
        int max;
        if (maxN != nullptr)
        {
            for (auto i : maxN->arr)
            {
                insert(i->key, i->value);
            }
            maxN->arr.clear();
            int maxDeg = 0;
            if (maxN->rightChild != nullptr)
            {
                
                Node *n = maxN->rightChild;
                Node *temp = maxN;
                max = temp->value;
                int maxKey = -1;
                while (n != temp)
                {
                    if (n->key > maxKey)
                    {
                        maxKey = n->key;
                        maxN = n;
                    }
                    if (n->arr.size() > maxDeg)
                    {
                        maxDeg = n->arr.size();
                    }
                    n = n->rightChild;
                }
                removeMaxNodeFromList(temp);
            }
            vector<Node *> nodes(2 * (maxDeg + 1));
            fill(nodes.begin(), nodes.end(), nullptr);
             checkNodes(nodes);

        }

        return max;
    }
    
void nodeCheck(vector<Node *> &nodes, Node *n){
    while (true){
        if (nodes[n->arr.size()] == NULL){
            nodes[n->arr.size()] = n;
            break;
        }else{
            Node *temp = nodes[n->arr.size()];
            nodes[n->arr.size()] = NULL;

            if (temp->key < n->key)
            {
                std::swap(temp, n);
            }

            n->parent = temp;
            n->leftChild->rightChild = n->rightChild;
            n->rightChild->leftChild = n->leftChild;

            if (!temp->arr.empty())
            {
                n->leftChild = temp->arr.back();
                n->rightChild = temp->arr.front();
                temp->arr.front()->leftChild = n;
                temp->arr.back()->rightChild = n;
            }
            else
            {
                n->leftChild = n;
                n->rightChild = n;
            }

            temp->arr.push_back(n);
            n = temp;
        }
    }
}

    Node *find_(int value)
{
    if (maxN == NULL || Rootarr[value] == NULL)
    {
        return NULL;
    }

    return Rootarr[value];
}

Node *meldNode(Node *node, Node *max2, vector<Node *> &ValueArr)
{
    swap(node->rightChild, max2->rightChild);
    node->rightChild->leftChild = node;
    max2->rightChild->leftChild = max2;
    ValueArr[node->value] = node;
    return (node->key > max2->key) ? node : max2;
}


     void insert(int key, int value){
        vector<Node *> arr;
        Node *newN = new Node(NULL,arr,NULL,NULL, key,value);
        newN->rightChild = newN;
        newN->leftChild = newN;

        if (maxN ==NULL)
        {
            maxN = newN;
        }
        else
        {
            maxN = meldNode(newN, maxN, Rootarr);
        }
    }

    fibonacciHeap* meldHeap(fibonacciHeap* heap1, fibonacciHeap* heap2)
{
    if (!heap1 || !heap1->maxN) {
        return heap2;
    }

    if (!heap2 || !heap2->maxN) {
        return heap1;
    }

    Node* max1 = heap1->maxN;
    Node* max2 = heap2->maxN;

    Node* temp1 = max1->rightChild;
    Node* temp2 = max2->rightChild;

    max1->rightChild = temp2;
    max2->rightChild = temp1;

    if (temp1) {
        temp1->leftChild = max2;
    }

    if (temp2) {
        temp2->leftChild = max1;
    }

    for (int i = 0; i < 100002; i++) {
        if (heap2->Rootarr[i]) {
            heap1->Rootarr[i] = heap2->Rootarr[i];
        }
    }

    return (max1->key > max2->key) ? heap1 : heap2;
}



void deleteFromParent(Node *node)
{
    if (node != NULL && node->parent != NULL)
    {
        Node* foundNode = NULL;
        for (Node* child : node->parent->arr)
        {
            if (child == node)
            {
                foundNode = child;
                break;
            }
        }

        if (foundNode != NULL)
        {
            node->parent->arr.erase(std::remove(node->parent->arr.begin(), node->parent->arr.end(), foundNode), node->parent->arr.end());
        }
        node->parent = NULL;
    }
}
void deleteFromSiblings(Node *node)
{
    if (node !=NULL)
    {
        node->leftChild->rightChild = node->rightChild;
        node->rightChild->leftChild = node->leftChild;
        node->rightChild = node;
        node->leftChild = node;
    }
}

 int extractRoot(Node *maxNode)
{
    if (maxNode ==NULL)
    {
        return 0;
    }
    for (auto child : maxNode->arr)
    {
        insert(child->key, child->value);
    }
    maxNode->arr.clear();
    if (maxNode->rightChild == NULL)
    {
        int max = maxNode->value;
        Rootarr[maxNode->value] = NULL;
        delete maxNode;
        return max;
    }

    Node *temp = maxNode->rightChild;
    int max = temp->value;
    Node *maxN = temp;
    int maxDeg = temp->arr.size();

    while (temp != maxNode)
    {
        if (temp->key > max)
        {
            max = temp->key;
            maxN = temp;
        }
        maxDeg = std::max(maxDeg, static_cast<int>(temp->arr.size()));

        temp = temp->rightChild;
    }
    updateNode(maxNode);
    Rootarr[maxNode->value] =NULL;
    delete maxNode;

    vector<Node *> degreeVec(2 * (maxDeg + 1), NULL);
vector<Node *> nodeSet;
for (Node *temp = maxN; temp != maxN; temp = temp->rightChild)
{
    nodeSet.push_back(temp);
}

for (auto node : nodeSet)
{
    nodeCheck(degreeVec, node);
}

    return max;
}

void deleteNode(Node *node)
{
    if (node != NULL)
    {
        if (node->parent == NULL)
        {
            extractRoot(node);
        }
        else
        {
            deleteFromSiblings(node);
            deleteFromParent(node);
            Rootarr[node->value] = NULL;
        }
    }
}
void increaseKey(int value, int new_key)
{
    Node *node = find_(value);
    node->key = new_key;

    if (node->parent != NULL)
    {
        if (!node->parent->makeB)
        {
            node->parent->makeB = true;
            deleteNode(node);
            maxN = meldNode(node, maxN, Rootarr);
        }
        else
        {
            Node *temp = node->parent;
            deleteNode(node);
            deleteNode(temp);
            maxN = meldNode(node, maxN, Rootarr);
            maxN = meldNode(temp, maxN, Rootarr);
        }
    }

    if (node->key > maxN->key)
    {
        maxN = node;
    }
}

string printNode(Node *node, int &count)
{
    stringstream ss;
    if (node->parent == NULL)
    {
        ss << "Tree " << count++ << " : ";
    }
    ss << "(" << node->key << "," << node->value << ") ->";
    for (auto i : node->arr)
    {
        ss << "(" << i->key << "," << i->value << ") ,";
    }
    ss << '\n';
    return ss.str();
}

string print(Node *maxN)
{
    stringstream ss;
    Node *n = maxN;
    int count = 1;
    do
    {
        ss << printNode(n, count);
        for (auto i : n->arr)
        {
            if (i->arr.size() != 0)
            {
                ss << print(i);
            }
        }
        n = n->rightChild;
    } while (n != maxN);
    return ss.str();
}
 bool is_empty()
    {
        return maxN ==NULL;
    }
};


class maxQueue
{
public:
    fibonacciHeap* make_heap()
    {
        return new fibonacciHeap();
    }
bool is_empty(fibonacciHeap* fh)
    {
        return fh->is_empty();
    }
    void insert(fibonacciHeap* fh, int key, int value)
    {
        fh->insert(key, value);
    }

    int extract_max(fibonacciHeap* fh)
    {
        return fh->extract_max();
    }

    void increase_key(fibonacciHeap* fh, int value, int new_key)
    {
        fh->increaseKey(value, new_key);
    }

    void deleteN(fibonacciHeap* fh, int value)
    {
        fh->deleteNode(fh->find_(value));
    }

    fibonacciHeap *meld(fibonacciHeap *heap1, fibonacciHeap *heap2)
    {
        fibonacciHeap *heap = heap1->meldHeap(heap1, heap2);
        return heap;
    }

   int find_max(fibonacciHeap* fh) {
            return fh->maxN->value; 
    }

    string print(fibonacciHeap* fh)
    {
        return fh->print(fh->maxN);
    }
};

void test()
{
    maxQueue m;
    auto heap = m.make_heap();
    std::stringstream ss;
    if (m.is_empty(heap)){
        ss << "true";
    }else{
        ss << "false";
    }
    m.insert(heap, 10, 10);
    m.insert(heap, 2, -5);
    m.insert(heap, 3, -10);
    m.insert(heap, 5, -15);
    m.insert(heap, 4, 3);
    m.insert(heap, 6, 6);
    m.insert(heap, 9, 9);
    ss << m.print(heap);
    ss << m.extract_max(heap);
    m.increase_key(heap, -15, 20);
    ss << m.print(heap);
    m.deleteN(heap, -5);
    ss << m.print(heap);

    auto heap2 = m.make_heap();
    m.insert(heap2, 1, 1);
    m.insert(heap2, 8, 8);
    m.insert(heap2, 11, -12);
    m.insert(heap2, 7, 7);
    ss << m.print(heap2);
    heap = m.meld(heap, heap2);
    ss << m.print(heap);
   

    string str = ss.str();
     string expectedStr = "trueTree 1 : (10,10) ->\n"
                         "Tree 2 : (9,9) ->\n"
                         "Tree 3 : (6,6) ->\n"
                         "Tree 4 : (4,3) ->\n"
                         "Tree 5 : (5,-15) ->\n"
                         "Tree 6 : (3,-10) ->\n"
                         "Tree 7 : (2,-5) ->\n"
                         "10Tree 1 : (20,-15) ->(4,3) ,\n"
                         "Tree 2 : (3,-10) ->(2,-5) ,\n"
                         "Tree 3 : (9,9) ->(6,6) ,\n"
                         "Tree 1 : (20,-15) ->(4,3) ,\n"
                         "Tree 2 : (3,-10) ->\n"
                         "Tree 3 : (9,9) ->(6,6) ,\n"
                         "Tree 1 : (11,-12) ->\n"
                         "Tree 2 : (7,7) ->\n"
                         "Tree 3 : (1,1) ->\n"
                         "Tree 4 : (8,8) ->\n"
                         "Tree 1 : (20,-15) ->(4,3) ,\n"
                         "Tree 2 : (7,7) ->\n"
                        "Tree 3 : (1,1) ->\n"
                        "Tree 4 : (8,8) ->\n"
                        "Tree 5 : (11,-12) ->\n"
                        "Tree 6 : (3,-10) ->\n"
                        "Tree 7 : (9,9) ->(6,6) ,\n";
                        

    if (str == expectedStr){
        cout << "passed" << endl;
    }else{
        cout << "not passed" << endl;
    }
}


int main()
{
    test();
    return 0;
}
