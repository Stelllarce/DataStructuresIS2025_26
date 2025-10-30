class Solution {
public:
    bool isValid(string s) {
        if (s.length() < 2 || s.front() == ')'
                || s.front() == '}'
                || s.front() == ']') return false;
        std::stack<char> braces;
        int curr = 0;
        while(s[curr]) {
            switch (s[curr])
            {
                case '(':
                case '[':
                case '{': 
                {
                    braces.push(s[curr]);
                    curr++;
                    continue;
                }
                default: break;
            }

            if (!braces.empty() && (braces.top() == '{' && s[curr] == '}' || 
                braces.top() == '(' && s[curr] == ')'||
                braces.top() == '[' && s[curr] == ']') ) {
                    braces.pop();
                    curr++;
                }
            else return false;
        }
        return braces.empty();
    }
};