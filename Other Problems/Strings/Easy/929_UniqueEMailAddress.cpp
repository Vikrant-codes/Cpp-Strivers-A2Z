/*
Leetcode - 929. Unique Email Addresses : Easy

Every valid email consists of a local name and a domain name, separated by the '@' sign. Besides lowercase letters, 
the email may contain one or more '.' or '+'.
For example, in "alice@leetcode.com", "alice" is the local name, and "leetcode.com" is the domain name.

If you add periods '.' between some characters in the local name part of an email address, 
mail sent there will be forwarded to the same address without dots in the local name. 
Note that this rule does not apply to domain names.
For example, "alice.z@leetcode.com" and "alicez@leetcode.com" forward to the same email address.

If you add a plus '+' in the local name, everything after the first plus sign will be ignored. 
This allows certain emails to be filtered. Note that this rule does not apply to domain names.
For example, "m.y+name@email.com" will be forwarded to "my@email.com".

It is possible to use both of these rules at the same time.

Given an array of strings emails where we send one email to each emails[i], 
return the number of different addresses that actually receive mails.

Examples :-

Input: emails = ["test.email+alex@leetcode.com","test.e.mail+bob.cathy@leetcode.com","testemail+david@lee.tcode.com"]
Output: 2
Explanation: "testemail@leetcode.com" and "testemail@lee.tcode.com" actually receive mails.

Input: emails = ["a@leetcode.com","b@leetcode.com","c@leetcode.com"]
Output: 3

Constraints :-
- 1 <= emails.length <= 100
- 1 <= emails[i].length <= 100
- emails[i] consist of lowercase English letters, '+', '.' and '@'.
- Each emails[i] contains exactly one '@' character.
- All local and domain names are non-empty.
- Local names do not start with a '+' character.
- Domain names end with the ".com" suffix.
- Domain names must contain at least one character before ".com" suffix.
*/

#include<bits/stdc++.h>
using namespace std;

// Time Complexity : O(n * m) , where n = emails.size(), m = average email length __ Space Complexity : O(n * m)

int numUniqueEmails1(vector<string>& emails) {
    unordered_set<string> unique_mails;
    for (string& s : emails) {
        string address = "";
        int i = 0;
        // check local name and get the actual local name
        while (s[i] != '@') {
            if (s[i] == '+') {
                while (s[i] != '@') i++;
                break;
            }
            if (s[i] != '.') address += s[i];
            i++;
        }
        // now add the global name as it is.
        while (i < s.size()) {
            address += s[i];
            i++;
        }
        unique_mails.insert(address);
    }   
    return unique_mails.size();
}

int numUniqueEmails2(vector<string>& emails) {
    unordered_set<string> st;
    for (string& s : emails) {
        string mail_id = "";
        bool plus = false;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '@') {
                mail_id += s.substr(i);
                break;
            }
            // local name part
            else {
                if (s[i] == '+') plus = true;
                else if (!plus && s[i] != '.') mail_id += s[i];
            }
        }
        st.insert(mail_id);
    }
    return st.size();
}

int main() {
    vector<string> emails = {"test.email+alex@leetcode.com","test.e.mail+bob.cathy@leetcode.com","testemail+david@lee.tcode.com"};
    cout << "Hii" << endl;
    int u = numUniqueEmails2(emails);
    cout << u;
    return 0;
}