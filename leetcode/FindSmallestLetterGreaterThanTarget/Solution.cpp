#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    char nextGreatestLetter(vector<char>& letters, char target) {
        vector<bool> letterMap;
        letterMap.resize(26);
        
        for(auto& c : letters) {
            letterMap[c-'a'] = true;
        }
        
        int i = target - 'a'+1;
        if (i==26)
            i = 0;
        
        while (!letterMap[i]) {
            i++;
            if (i==26)
                i = 0;
        }
        
        return 'a'+i;
    }
};
