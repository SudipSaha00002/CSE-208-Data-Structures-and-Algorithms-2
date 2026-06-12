#include <bits/stdc++.h>
#include<climits>
using namespace std;

typedef long long HT;


const int INF = INT_MAX;
const HT C1 = 11;
const HT C2 = 7;


class dataN{
    public:
    string key;
    HT value;
};



class node{
    public:
    int flag;
    dataN *item;
    node *next;
};

typedef node *nodes;
 typedef dataN *dataPoint;


HT hash1(const string& key) {
    HT h = 0;
    for (char c : key) {
        h = (h * 37) + static_cast<HT>(c);
    }
    return h;
}

HT hash2(const string& key) {
    HT h = 0;
    for (char c : key) {
        h = (h * 41) ^ static_cast<HT>(c);
    }
    return h;
}

HT auxhashing(const string k)
    {
        HT hash = 0;
        for (char c : k)
        {
            hash += ((hash << 5) + hash) ^ static_cast<HT>(c);
        }
        return hash;
    }


HT findIndex(HT h1, HT h2, HT i, HT n, HT type) {
    if (type == 2)
        return (h1 + (i * h2)) % n;
    else
        return (h1 + (C1 * i * h2) + (C2 * i * i)) % n;
}


vector<pair<string, HT>> wordgenerate(HT n)
{
    unordered_map<string, HT> wordMap;
    vector<pair<string, HT>> result;
    string letter = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    HT val = 1;
    while (result.size() < n)
    {
        HT len = rand() % 6 + 5;
        string temp = "";
        for (HT i = 0; i < len; i++)
            temp += letter[rand() % letter.length()];

        if (wordMap.find(temp) == wordMap.end())
        {
            wordMap[temp] = val;
            result.push_back({temp, val});
            val++;
        }
    }

    return result;
}

class hashTable
{
    vector<nodes> table;
    HT count;
    HT size;
    HT hash;
    HT operateCol;
    HT collision;
    HT probe;
private:
 int maxLength;
   int minTableS;

    void rehash();
    void printRehash(string type);

public:
    hashTable(HT n, HT hash, HT operateCol, int maxLength, int minTableS);
    ~hashTable();
    bool isfull();
    void insert(pair<string, HT> key, HT val);
    HT search(pair<string, HT> key);
    void deleteK(const string& key);
    void resetcalc() { 
        collision= 0, probe = 0;
         };
    HT getcol() { 
        return collision; 
        };
    HT getprobe() { 
        return probe; 
        };
    HT getelemsize() { 
        return count; 
        };
    HT calculateHash(const pair<string, HT>& key);
    HT searchProbing(const pair<string, HT>& key, HT h1, HT h2);
    HT searchChaining(const string& key, HT h1);
    HT searchKeyInTable(nodes tableSize, const string& key);
    void insertChaining(HT h1, dataPoint temp);
    void insertLinearProbing(HT h1, HT h2, dataPoint temp);
    void deleteChaining(const string& key, HT h1);
    void deleteLinearProbing(const string& key, HT h1, HT h2);

};

hashTable::hashTable(HT n, HT hash, HT operateCol, int maxLength, int minTableS)
    : maxLength(maxLength), minTableS(minTableS)
{
    this->table = vector<nodes>(n);
    for (int i = 0; i < n; i++)
    {
        table[i] = new node;
        table[i]->flag = 0, table[i]->item = NULL, table[i]->next = NULL;
    }
    this->count = 0;
    this->size = n;
    this->hash = hash;
    this->operateCol = operateCol;
    resetcalc();
}

hashTable::~hashTable()
{
    this->table.clear();
}

bool hashTable::isfull()
{
    return count >= size;
}

void hashTable::insertChaining(HT h1, dataPoint temp)
{
    HT index = h1 % size;
    nodes current = table[index];

    if (current->flag != 1)
    {
        current->flag = 1;
        current->item = temp;
        current->next = NULL;
    }
    else
    {
        collision++;
        while (current->next)
            current = current->next;

        nodes newNode = new node{1, temp,NULL};
        current->next = newNode;
    }
    count++;
}

void hashTable::insertLinearProbing(HT h1, HT h2, dataPoint temp)
{
    HT i = 0;
    HT index;

    while (table[index = findIndex(h1 % size, h2 % size, i, size, operateCol)]->flag == 1)
    {
        if (i && index == h1 % size)
            return;
        collision++;
        i++;
    }

    table[index]->flag = 1;
    table[index]->item = temp;
    table[index]->next = NULL;
    count++;
}

void hashTable::insert(pair<string, HT> key, HT val)
{
    if (isfull())
    {
        rehash();
    }

        HT h1;
if (this->hash == 1)
    h1 = hash1(key.first);
else
    h1 = hash2(key.first);
h1 %= this->size;
    HT h2 = auxhashing(key.first);
    dataPoint temp = new dataN{key.first, val};

    if (operateCol == 1)
    {
        insertChaining(h1, temp);
    }
    else
    {
        insertLinearProbing(h1, h2, temp);
    }
}

HT hashTable::calculateHash(const pair<string, HT>& key) {
    if (this->hash == 1)
        return hash1(key.first) % this->size;
    else
        return hash2(key.first) % this->size;
}

HT hashTable::searchKeyInTable(nodes tableSize, const string& key) {
    nodes head = tableSize;
    while (head) {
        this->probe++;
        if (head->item->key == key)
            return head->item->value;
        head = head->next;
    }
    return -1;
}

HT hashTable::searchChaining(const string& key, HT h1) {
   
        HT index = h1;
        this->probe++;
        if (table[index]->flag != 1)
            return -1;
        else
        {
            this->probe--;
            nodes head = table[index];
            while (head)
            {
                this->probe++;
                if (head->item->key == key)
                    return head->item->value;
                head = head->next;
            }
            return -1;
        }
}

HT hashTable::searchProbing(const pair<string, HT>& key, HT h1, HT h2) {
    HT i = 0;
    HT index;
    while (table[index = findIndex(h1, h2, i, this->size, this->operateCol)]->flag != 0) {
        if (i && index == h1)
            break;

        if (table[index]->flag == 1 && table[index]->item->key == key.first)
            return table[index]->item->value;

        i++;
        this->probe++;
    }
    return -1;
}


HT hashTable::search(pair<string, HT> key) {
    HT h1;
if (this->hash == 1)
    h1 = hash1(key.first);
else
    h1 = hash2(key.first);
h1 %= this->size;



    HT h2 = auxhashing(key.first) % this->size;
    HT index;
    if (operateCol == 1) {
        return searchChaining(key.first, h1);
    } else {
        return searchProbing(key, h1, h2);
    }
}

void hashTable::deleteChaining(const string& key, HT h1) {
    HT index = h1 % size;
    nodes current = table[index];
    nodes prev = NULL;

    while (current) {
        if (current->item->key == key) {
            if (prev) {
                prev->next = current->next;
            } else {
                table[index] = current->next;
            }
            delete current->item;
            delete current;
            count--;
            return;
        }
        prev = current;
        current = current->next;
    }
}

void hashTable::deleteLinearProbing(const string& key, HT h1, HT h2) {
    HT i = 0;
    HT index;

    while (table[index = findIndex(h1 % size, h2 % size, i, size, operateCol)]->flag != 0) {
        if (i && index == h1 % size) {
            break;
        }
        if (table[index]->flag == 1 && table[index]->item->key == key) {
            table[index]->flag = 2;
            delete table[index]->item;
            count--;
            return;
        }
        i++;
    }
}

void hashTable::deleteK(const string& key) {
    if (count == 0) {
        return;
    }

    HT h1 = (hash == 1) ? hash1(key) : hash2(key);
    HT h2 = auxhashing(key);

    if (operateCol == 1) {
        deleteChaining(key, h1);
    } else {
        deleteLinearProbing(key, h1, h2);
    }

    if (count % 100 == 0 && size > minTableS) {
        int maxLength = 0;
        for (int i = 0; i < size; i++) {
            nodes head = table[i];
            int chain_length = 0;
            while (head) {
                chain_length++;
                head = head->next;
            }
            maxLength = max(maxLength, chain_length);
        }

        if (maxLength < 0.8 * maxLength && size > minTableS) {
            rehash();
        }
    }
}


void hashTable::rehash()
{
    printRehash("Before Rehash");
    vector<nodes> oldTable = table;
    HT oldSize = size;

    size *= 2;
    count = 0;
    collision= 0;
    probe = 0;

    table = vector<nodes>(size);
    for (int i = 0; i < size; i++)
    {
        table[i] = new node;
        table[i]->flag = 0, table[i]->item = NULL, table[i]->next = NULL;
    }

    for (int i = 0; i < oldSize; i++)
    {
        nodes head = oldTable[i];
        while (head)
        {
            insert({head->item->key, head->item->value}, head->item->value);
            nodes temp = head;
            head = head->next;
            delete temp;
        }
    }

    printRehash("After Rehash");
}

void hashTable::printRehash(string type)
{
    cout << "Rehashing " << type << endl;
    cout << "Average probe count:\t" << (probe * 1.0 / count) << endl;
    cout << "Load factor:\t\t" << (count * 1.0 / size) << endl;
    int maxLength = 0;
    for (int i = 0; i < size; i++)
    {
        nodes head = table[i];
        int length = 0;
        while (head)
        {
            length++;
            head = head->next;
        }
        maxLength = max(maxLength,length);
    }
    cout << "Max Length:\t" << maxLength << endl;
}

int main()
{

    srand(2);

    vector<pair<string, HT>> words = wordgenerate(10000);

    hashTable hashetable1(20000, 1, 1, 10, 10);
    hashTable hashetable2(20000, 2, 1, 10, 10);
    hashTable hashetable3(20000, 1, 2, 10, 10);
    hashTable hashetable4(20000, 2, 2, 10, 10);
    hashTable hashetable5(20000, 1, 3, 10, 10);
    hashTable hashetable6(20000, 2, 3, 10, 10);



    for (int i = 0; i < 10000; i++)
    {
        hashetable1.insert(words[i], i + 1);
        hashetable2.insert(words[i], i + 1);
        hashetable3.insert(words[i], i + 1);
        hashetable4.insert(words[i], i + 1);
        hashetable5.insert(words[i], i + 1);
        hashetable6.insert(words[i], i + 1);
    }

    // for (int i = 0; i < 10000; i++)
    // {
    //     hashetable1.deleteK(words[i].first);
    //     hashetable2.deleteK(words[i].first);
    //     hashetable3.deleteK(words[i].first);
    //     hashetable4.deleteK(words[i].first);
    //     hashetable5.deleteK(words[i].first);
    //     hashetable6.deleteK(words[i].first);
    // }


    // for (int i = 0; i < 10000; i++)
    // {
    //     hashetable1.insert(words[i], i + 1);
    //     hashetable2.insert(words[i], i + 1);
    //     hashetable3.insert(words[i], i + 1);
    //     hashetable4.insert(words[i], i + 1);
    //     hashetable5.insert(words[i], i + 1);
    //     hashetable6.insert(words[i], i + 1);
    // }

    for (int i = 0; i < 10000; i++)
    {
        hashetable1.search(words[rand() % 10000]);
        hashetable2.search(words[rand() % 10000]);
        hashetable3.search(words[rand() % 10000]);
        hashetable4.search(words[rand() % 10000]);
        hashetable5.search(words[rand() % 10000]);
        hashetable6.search(words[rand() % 10000]);
    }
    cout<<"Hash table size: 20000"<<endl;
  
    cout << "HASH 1" << endl;
    
    cout << "Chaining :" << endl;
    cout << "# of collisions :\t" << hashetable1.getcol() << endl;
    cout << "Average probes:\t" << (hashetable1.getprobe() * 1.0 / 10000) << endl << endl;

    cout << "Double Hashing:" << endl;
    cout << "# of collisions :\t" << hashetable3.getcol() << endl;
    cout << "Average probes:\t" << (hashetable3.getprobe() * 1.0 / 10000) << endl << endl;

    cout << "Custom probing:" << endl;
    cout << "# of collisions :\t" << hashetable5.getcol() << endl;
    cout << "Average probes:\t" << (hashetable5.getprobe() * 1.0 / 10000) << endl << endl;

   
    cout << "HASH 2" << endl;
    
    cout << "Chaining :" << endl;
    cout << "# of collisions :\t" << hashetable2.getcol() << endl;
    cout << "Average probes:\t" << (hashetable2.getprobe() * 1.0 / 10000) << endl << endl;

    cout << "Double Hashing:" << endl;
    cout << "# of collisions :\t" << hashetable4.getcol() << endl;
    cout << "Average probes:\t" << (hashetable4.getprobe() * 1.0 / 10000) << endl << endl;

    cout << "Custom probing:" << endl;
    cout << "# of collisions :\t" << hashetable6.getcol() << endl;
    cout << "Average probes:\t" << (hashetable6.getprobe() * 1.0 / 10000) << endl << endl;



    hashTable hashetable7(10000, 1, 1, 10, 10);
    hashTable hashetable8(10000, 2, 1, 10, 10);
    hashTable hashetable9(10000, 1, 2, 10, 10);
    hashTable hashetable10(10000, 2, 2, 10, 10);
    hashTable hashetable11(10000, 1, 3, 10, 10);
    hashTable hashetable12(10000, 2, 3, 10, 10);



    for (int i = 0; i < 10000; i++)
    {
        hashetable7.insert(words[i], i + 1);
        hashetable8.insert(words[i], i + 1);
        hashetable9.insert(words[i], i + 1);
        hashetable10.insert(words[i], i + 1);
        hashetable11.insert(words[i], i + 1);
        hashetable12.insert(words[i], i + 1);
    }

    // for (int i = 0; i < 10000; i++)
    // {
    //     hashetable1.deleteK(words[i].first);
    //     hashetable2.deleteK(words[i].first);
    //     hashetable3.deleteK(words[i].first);
    //     hashetable4.deleteK(words[i].first);
    //     hashetable5.deleteK(words[i].first);
    //     hashetable6.deleteK(words[i].first);
    // }


    // for (int i = 0; i < 10000; i++)
    // {
    //     hashetable1.insert(words[i], i + 1);
    //     hashetable2.insert(words[i], i + 1);
    //     hashetable3.insert(words[i], i + 1);
    //     hashetable4.insert(words[i], i + 1);
    //     hashetable5.insert(words[i], i + 1);
    //     hashetable6.insert(words[i], i + 1);
    // }

    for (int i = 0; i < 10000; i++)
    {
        hashetable7.search(words[rand() % 10000]);
        hashetable8.search(words[rand() % 10000]);
        hashetable9.search(words[rand() % 10000]);
        hashetable10.search(words[rand() % 10000]);
        hashetable11.search(words[rand() % 10000]);
        hashetable12.search(words[rand() % 10000]);
    }
    cout<<"Hash table size: 10000"<<endl;

    cout << "HASH 1" << endl;
    
    cout << "Chaining :" << endl;
    cout << "# of collisions :\t" << hashetable7.getcol() << endl;
    cout << "Average probes:\t" << (hashetable7.getprobe() * 1.0 / 10000) << endl << endl;

    cout << "Double Hashing:" << endl;
    cout << "# of collisions :\t" << hashetable9.getcol() << endl;
    cout << "Average probes:\t" << (hashetable9.getprobe() * 1.0 / 10000) << endl << endl;

    cout << "Custom probing:" << endl;
    cout << "# of collisions :\t" << hashetable11.getcol() << endl;
    cout << "Average probes:\t" << (hashetable11.getprobe() * 1.0 / 10000) << endl << endl;


    cout << "HASH 2" << endl;
    
    cout << "Chaining :" << endl;
    cout << "# of collisions :\t" << hashetable8.getcol() << endl;
    cout << "Average probes:\t" << (hashetable8.getprobe() * 1.0 / 10000) << endl << endl;

    cout << "Double Hashing:" << endl;
    cout << "# of collisions :\t" << hashetable10.getcol() << endl;
    cout << "Average probes:\t" << (hashetable10.getprobe() * 1.0 / 10000) << endl << endl;

    cout << "Custom probing:" << endl;
    cout << "# of collisions :\t" << hashetable12.getcol() << endl;
    cout << "Average probes:\t" << (hashetable12.getprobe() * 1.0 / 10000) << endl << endl;



hashTable hashetable13(5000, 1, 1, 10, 10);
    hashTable hashetable14(5000, 2, 1, 10, 10);
    hashTable hashetable15(5000, 1, 2, 10, 10);
    hashTable hashetable16(5000, 2, 2, 10, 10);
    hashTable hashetable17(5000, 1, 3, 10, 10);
    hashTable hashetable18(5000, 2, 3, 10, 10);



    for (int i = 0; i < 1000; i++)
    {
        hashetable13.insert(words[i], i + 1);
        hashetable14.insert(words[i], i + 1);
        hashetable15.insert(words[i], i + 1);
        hashetable16.insert(words[i], i + 1);
        hashetable17.insert(words[i], i + 1);
        hashetable18.insert(words[i], i + 1);
    }

    // for (int i = 0; i < 10000; i++)
    // {
    //     hashetable1.deleteK(words[i].first);
    //     hashetable2.deleteK(words[i].first);
    //     hashetable3.deleteK(words[i].first);
    //     hashetable4.deleteK(words[i].first);
    //     hashetable5.deleteK(words[i].first);
    //     hashetable6.deleteK(words[i].first);
    // }


    // for (int i = 0; i < 10000; i++)
    // {
    //     hashetable1.insert(words[i], i + 1);
    //     hashetable2.insert(words[i], i + 1);
    //     hashetable3.insert(words[i], i + 1);
    //     hashetable4.insert(words[i], i + 1);
    //     hashetable5.insert(words[i], i + 1);
    //     hashetable6.insert(words[i], i + 1);
    // }

    for (int i = 0; i < 1000; i++)
    {
        hashetable13.search(words[rand() % 1000]);
        hashetable14.search(words[rand() % 1000]);
        hashetable15.search(words[rand() % 1000]);
        hashetable16.search(words[rand() % 1000]);
        hashetable17.search(words[rand() % 1000]);
        hashetable18.search(words[rand() % 1000]);
    }
cout<<"Hash table size: 5000"<<endl;

    cout << "HASH 1" << endl;

    cout << "Chaining :" << endl;
    cout << "# of collisions :\t" << hashetable13.getcol() << endl;
    cout << "Average probes:\t" << (hashetable13.getprobe() * 1.0 / 1000) << endl << endl;

    cout << "Double Hashing:" << endl;
    cout << "# of collisions :\t" << hashetable15.getcol() << endl;
    cout << "Average probes:\t" << (hashetable15.getprobe() * 1.0 / 1000) << endl << endl;

    cout << "Custom probing:" << endl;
    cout << "# of collisions :\t" << hashetable17.getcol() << endl;
    cout << "Average probes:\t" << (hashetable17.getprobe() * 1.0 / 1000) << endl << endl;

    cout << "HASH 2" << endl;
    
    cout << "Chaining :" << endl;
    cout << "# of collisions :\t" << hashetable14.getcol() << endl;
    cout << "Average probes:\t" << (hashetable14.getprobe() * 1.0 / 1000) << endl << endl;

    cout << "Double Hashing:" << endl;
    cout << "# of collisions :\t" << hashetable16.getcol() << endl;
    cout << "Average probes:\t" << (hashetable16.getprobe() * 1.0 / 1000) << endl << endl;

    cout << "Custom probing:" << endl;
    cout << "# of collisions :\t" << hashetable18.getcol() << endl;
    cout << "Average probes:\t" << (hashetable18.getprobe() * 1.0 / 1000) << endl << endl;
    return 0;
}
