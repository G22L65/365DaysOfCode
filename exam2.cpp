#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Base 62 characters
const string BASE62_CHARS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

// Function to encode a given integer N into a Base 62 string
string encodeBase62(unsigned long long N) {
    if (N == 0) return "0";

    string encoded;
    while (N > 0) {
        encoded += BASE62_CHARS[N % 62];
        N /= 62;
    }

    // Reverse the string to get the correct Base 62 representation
    reverse(encoded.begin(), encoded.end());
    return encoded;
}

// Main function to handle input and output
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    vector<string> results;

    while (T--) {
        unsigned long long N;
        cin >> N;
        results.push_back(encodeBase62(N));
    }

    for (const string& result : results) {
        cout << result << endl;
    }

    return 0;
}
