class Solution {
public:
    char upc(char c) {
        if (c=='9')
            return '0';
        return c+1;
    }
    char downc(char c) {
        if (c=='0')
            return '9';
        return c-1;
    }
    bool isValid(string ss,
                 unordered_set<string>& deadends,
                 unordered_set<string>& visited) {
        if (deadends.find(ss) == deadends.end()
           && visited.find(ss) == visited.end()) {
            return true;
        }
        
        return false;
    }

    int openLock(vector<string>& deadends, string target) {
        unordered_set<string> de;
        for (auto ds : deadends) {
            de.insert(ds);
        }
        unordered_set<string> visited;
        
        int count = 0;
        queue<string> qs;
        qs.push("0000");
        visited.insert("0000");
        
        while (!qs.empty()) {
            string cur = qs.front();
            visited.insert(cur);
            qs.pop();
            
            if (cur==target)
                break;
            
            for (int i=0; i<4; i++) {
                // up
                string ups = cur;
                ups[i] = upc(ups[i]);
                if (isValid(ups, de, visited))
                    qs.push(ups);
                
                // down
                string downs = cur;
                downs[i] = downc(downs[i]);
                if (isValid(downs, de, visited))
                    qs.push(downs);
            }
            count ++;
        }
        
        return count;;
    }
};
