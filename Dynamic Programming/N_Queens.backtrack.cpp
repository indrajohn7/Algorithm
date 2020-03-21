class Solution {
public:
    int n;
    vector<vector<string>> ans;
    vector<bool> used_cols;
    vector<string> cur;
    
    vector<vector<string>> solveNQueens(int n) {
        this->n=n;
        this->used_cols.assign(n,false);

        backtrack(0);
        return ans;
    }
    
    void backtrack(int col)
    {
        // check collision with other rows
        int offset=1;
        for(int row=cur.size()-2;row>=0;row--)
        {
            if(col-offset>=0 && cur[row][col-offset]=='Q') return;
            if(col+offset<n && cur[row][col+offset]=='Q') return;
            offset++;
        }

        // found a solution
        if(cur.size()==n)
        {
            ans.push_back(cur);
            return;
        }
        
        // backtrack the next row
        for(int c=0;c<n;++c)
        {
            if(used_cols[c])
                continue;
            
            string row(n,'.');
            row[c]='Q';
            used_cols[c]=true;
            cur.push_back(row);
            
            backtrack(c);
            
            cur.pop_back();
            used_cols[c]=false;
        }
    }
};
