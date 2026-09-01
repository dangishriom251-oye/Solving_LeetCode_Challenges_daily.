class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();

        vector<pair<int, int>> litter;
        int sr = 0, sc = 0;

        // Locate start and litter
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (classroom[i][j] == 'S') {
                    sr = i;
                    sc = j;
                } 
                else if (classroom[i][j] == 'L') {
                    litter.push_back({i, j});
                }
            }
        }

        int k = litter.size();

        if (k == 0)
            return 0;

        // Map each litter cell -> bit
        vector<vector<int>> id(m, vector<int>(n, -1));

        for (int i = 0; i < k; ++i) {
            auto [r, c] = litter[i];
            id[r][c] = i;
        }

        int fullMask = (1 << k) - 1;

        /*
            best[mask][r][c] =
            maximum remaining energy with which
            we have reached (r,c) after collecting mask.
        */
        vector<vector<vector<int>>> best(
            1 << k,
            vector<vector<int>>(m, vector<int>(n, -1))
        );

        struct State {
            int r, c;
            int mask;
            int energy;
        };

        queue<State> q;

        best[0][sr][sc] = energy;
        q.push({sr, sc, 0, energy});

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        int moves = 0;

        while (!q.empty()) {

            int sz = q.size();

            while (sz--) {

                auto [r, c, mask, en] = q.front();
                q.pop();

                if (mask == fullMask)
                    return moves;

                for (int d = 0; d < 4; ++d) {

                    int nr = r + dr[d];
                    int nc = c + dc[d];

                    // Outside grid
                    if (nr < 0 || nr >= m ||
                        nc < 0 || nc >= n)
                        continue;

                    // Obstacle
                    if (classroom[nr][nc] == 'X')
                        continue;

                    // No energy left
                    if (en == 0)
                        continue;

                    int newEnergy = en - 1;
                    int newMask = mask;

                    // Collect litter
                    if (id[nr][nc] != -1) {
                        newMask |= (1 << id[nr][nc]);
                    }

                    // Reset energy
                    if (classroom[nr][nc] == 'R') {
                        newEnergy = energy;
                    }

                    /*
                        Dominance optimization:
                        If we've already reached this exact
                        position + mask with >= energy,
                        this state can never be better.
                    */
                    if (newEnergy <= best[newMask][nr][nc])
                        continue;

                    best[newMask][nr][nc] = newEnergy;

                    q.push({
                        nr,
                        nc,
                        newMask,
                        newEnergy
                    });
                }
            }

            ++moves;
        }

        return -1;
    }
};