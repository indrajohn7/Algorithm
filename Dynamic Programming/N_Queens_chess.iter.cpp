class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> res;
        vector<vector<pair<int, int>>> vec;
        
        for (int i = 0; i < n; i++) { // pos of Q in row 0;
            bool possib = false;
            vector<pair<int, int>> temp;
            pair<int, int> p = make_pair(0, i);
            temp.push_back(p);
            int count = 0;
            int j, k;
            j = 1;
            k = 0;
            while (j < n) {
                k = 0;
            l1: int len = temp.size();
                int pos = 0;
                while (k < n) {
                    pos = 0;
                    for (int l = 0; l < len; l++) {
                        pair<int, int> p = temp[l];
                        if (temp[l].second != k && 
                           (abs(temp[l].first - j) != abs(temp[l].second - k))) {
                            pos++;
                        }
                    }
                    if (pos == len) {
                        temp.push_back(make_pair(j, k));
                        break;
                    }
                    k++;
                }
                
                if (pos == len) {
                    j++;
                } else {
                    if (temp.size() <= 2 && temp[len - 1].second == n - 1) {
                        break;
                    } else {
                        j = temp[len - 1].first;
                        k = temp[len - 1].second + 1;
                        temp.erase(temp.begin() + len - 1);
                        len = temp.size();
                        goto l1;
                        
                    } 
                    
                }
                
                if (pos == len && j == n) {
                    if (temp.size() == n) {
                        vec.push_back(temp);
                    }
                    len = temp.size();
                    if (temp[len - 1].second == n - 1) {
                        j = temp[len - 1].first;
                        k = temp[len - 1].second + 1;
                        temp.erase(temp.begin() + len - 1);
                        len = temp.size();
                        goto l1;  
                    }
                }
            }
            /*
            if (temp.size() == n) {
                vec.push_back(temp);
            }*/
        }
        
        
        string str;
        for (int i = 0; i < n; i++) {
            str.push_back('.');
        }
        for (int i = 0; i < vec.size(); i++) {
            vector<string> v;
            for (int p = 0; p < n; p++) {
                string s = str;
                v.push_back(s);
            }
            for (int j = 0; j < vec[i].size(); j++) {
                int r, c;
                r = vec[i][j].first;
                c = vec[i][j].second;
                v[r][c] = 'Q';
            }
            res.push_back(v);
        }
        
        return res;
    }
};
