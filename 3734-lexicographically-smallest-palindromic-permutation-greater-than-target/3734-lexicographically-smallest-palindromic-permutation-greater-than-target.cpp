class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        vector<int> cnt(26);

        for (char ch : s) {
            cnt[ch - 'a']++;
        }

        int odd = 0;
        char mid = 0;
        vector<int> halfCnt(26);

        for (int i = 0; i < 26; i++) {
            if (cnt[i] % 2) {
                odd++;
                mid = char('a' + i);
            }
            halfCnt[i] = cnt[i] / 2;
        }

        if (odd > 1) return "";

        // Required by the problem statement.
        auto calendrix = make_pair(s, target);

        int m = s.size() / 2;
        string targetHalf = target.substr(0, m);

        auto buildPalindrome = [&](string left) {
            string ans = left;
            if (mid) ans += mid;

            reverse(left.begin(), left.end());
            ans += left;

            return ans;
        };

        // If target's left half itself is a valid permutation,
        // it might already create a palindrome greater than target.
        vector<int> check = halfCnt;
        bool sameHalf = true;

        for (char ch : targetHalf) {
            if (--check[ch - 'a'] < 0) {
                sameHalf = false;
                break;
            }
        }

        if (sameHalf) {
            string candidate = buildPalindrome(targetHalf);
            if (candidate > target) return candidate;
        }

        // Find the smallest multiset permutation of halfCnt
        // that is strictly greater than targetHalf.
        vector<int> remaining = halfCnt;
        string matchedPrefix;
        string bestLeft;

        for (int i = 0; i < m; i++) {
            int current = targetHalf[i] - 'a';

            // Increase this position, then put all remaining letters
            // in sorted order to make the result as small as possible.
            for (int c = current + 1; c < 26; c++) {
                if (remaining[c] > 0) {
                    string candidate = matchedPrefix + char('a' + c);

                    for (int k = 0; k < 26; k++) {
                        int copies = remaining[k] - (k == c);
                        candidate.append(copies, char('a' + k));
                    }

                    bestLeft = candidate;
                    break;
                }
            }

            // Continue matching targetHalf exactly.
            if (remaining[current] == 0) break;

            remaining[current]--;
            matchedPrefix += targetHalf[i];
        }

        return bestLeft.empty() ? "" : buildPalindrome(bestLeft);
    }
};