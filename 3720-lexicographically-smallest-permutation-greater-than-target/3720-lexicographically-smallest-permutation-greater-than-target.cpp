class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.size();
        vector<int> freq(26, 0);

        for (char c : s)
            freq[c - 'a']++;

        // First, try to match target from left to right.
        for (int i = 0; i < n; i++) {
            int x = target[i] - 'a';

            if (freq[x] > 0) {
                freq[x]--;
                continue;
            }

            // Cannot match target[i].
            // Find the smallest character > target[i].
            for (int c = x + 1; c < 26; c++) {
                if (freq[c] > 0) {
                    string ans = target.substr(0, i);
                    ans += char('a' + c);

                    freq[c]--;

                    // Remaining characters in sorted order
                    for (int j = 0; j < 26; j++) {
                        while (freq[j]--) {
                            ans += char('a' + j);
                        }
                    }

                    return ans;
                }
            }

            // No larger character here.
            // We need to backtrack.
            break;
        }

        // Rebuild frequency array.
        freq.assign(26, 0);
        for (char c : s)
            freq[c - 'a']++;

        // Try changing target from right to left.
        for (int i = n - 1; i >= 0; i--) {

            // Use characters of target[0 ... i-1]
            bool possible = true;

            vector<int> temp = freq;

            for (int j = 0; j < i; j++) {
                int x = target[j] - 'a';

                if (temp[x] == 0) {
                    possible = false;
                    break;
                }

                temp[x]--;
            }

            if (!possible)
                continue;

            int x = target[i] - 'a';

            // Find smallest character greater than target[i].
            for (int c = x + 1; c < 26; c++) {
                if (temp[c] > 0) {
                    string ans = target.substr(0, i);
                    ans += char('a' + c);

                    temp[c]--;

                    // Append remaining characters sorted.
                    for (int j = 0; j < 26; j++) {
                        while (temp[j] > 0) {
                            ans += char('a' + j);
                            temp[j]--;
                        }
                    }

                    return ans;
                }
            }
        }

        return "";
    }
};