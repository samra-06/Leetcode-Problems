class Solution {
public:
    string s;
    int pos = 0;
    set<string> parseExpression() {
        set<string> result;
        set<string> current;
        current.insert("");
        while (pos < s.size() && s[pos] != '}') {
            if (s[pos] == ',') {
                result.insert(current.begin(), current.end());
                current.clear();
                current.insert("");
                pos++;
            }
            else {
                set<string> part;
                if (s[pos] == '{') {
                    pos++; 
                    part = parseExpression();
                    pos++; 
                }
                else {
                    string ch(1, s[pos]);
                    part.insert(ch);
                    pos++;
                }
                set<string> temp;

                for (const string& a : current) {
                    for (const string& b : part) {
                        temp.insert(a + b);
                    }
                }

                current = temp;
            }
        }
        result.insert(current.begin(), current.end());

        return result;
    }
    vector<string> braceExpansionII(string expression) {
        s = expression;
        pos = 0;
        set<string> ans = parseExpression();
        return vector<string>(ans.begin(), ans.end());
    }
};