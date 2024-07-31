#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
#include <climits>

using namespace std;

class LFUCache {
private:
    int capacity;
    int minFreq;
    unordered_map<int, int> cache; // Key to value
    unordered_map<int, int> freq; // Key to frequency
    unordered_map<int, list<int>> freqList; // Frequency to list of keys
    unordered_map<int, list<int>::iterator> keyIter; // Key to list iterator
    
public:
    LFUCache(int cap) : capacity(cap), minFreq(0) {}
    
    int get(int key) {
        if (cache.find(key) == cache.end()) {
            return -1;
        }
        
        // Update frequency of the key
        int currentFreq = freq[key];
        freq[key]++;
        int newFreq = currentFreq + 1;
        
        // Move key to the new frequency list
        freqList[currentFreq].erase(keyIter[key]);
        if (freqList[currentFreq].empty()) {
            freqList.erase(currentFreq);
            if (minFreq == currentFreq) {
                minFreq++;
            }
        }
        
        freqList[newFreq].push_back(key);
        keyIter[key] = --freqList[newFreq].end();
        
        return cache[key];
    }
    
    void put(int key, int value) {
        if (capacity == 0) return;
        
        if (cache.find(key) != cache.end()) {
            // Key exists, update value and frequency
            cache[key] = value;
            get(key); // This will update the frequency
        } else {
            if (cache.size() >= capacity) {
                // Remove the least frequently used key
                int evictKey = freqList[minFreq].front();
                freqList[minFreq].pop_front();
                cache.erase(evictKey);
                freq.erase(evictKey);
                keyIter.erase(evictKey);
                
                if (freqList[minFreq].empty()) {
                    freqList.erase(minFreq);
                }
            }
            
            // Insert new key
            cache[key] = value;
            freq[key] = 1;
            minFreq = 1;
            freqList[1].push_back(key);
            keyIter[key] = --freqList[1].end();
        }
    }
};

vector<int> solve(int N, int Q, vector<vector<int>>& operations) {
    LFUCache cache(N);
    vector<int> result;
    
    for (const auto& op : operations) {
        if (op[0] == 1) {
            result.push_back(cache.get(op[1]));
        } else if (op[0] == 2) {
            cache.put(op[1], op[2]);
        }
    }
    
    return result;
}

int main() {
    int N = 2;
    int Q = 5;
    vector<vector<int>> operations = {
        {1, 2},
        {2, 1, 3},
        {2, 2, 4},
        {2, 4, 5},
        {1, 2}
    };
    
    vector<int> result = solve(N, Q, operations);
    for (int res : result) {
        cout << res << " ";
    }
    cout << endl;
    
    return 0;
}
