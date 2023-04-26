#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <queue>

struct Cmp {
    bool operator()(std::map<std::string, int>::iterator x1, std::map<std::string, int>::iterator x2) {
        if (x1->second < x2->second)
            return true;
        if (x1->second > x2->second)
            return false;
        if (x1->first < x2->first)
            return false;
        return true;
    }
};
bool cmp(std::map<std::string, int>::iterator x1, std::map<std::string, int>::iterator x2) {
    if (x1->second < x2->second)
        return true;
    else if (x1->first > x2->first)
        return true;
    else
        return false;
}
int main() {
    std::string text;
    std::string cuvant;
    text = "I bought an apple. Then I eat an apple. Apple is my favorite.";
    std::vector<std::string> v;
    std::map<std::string, int> m;
    for (int i = 0; i < text.size(); ++i) {
        if ((text[i] == ' ' || text[i] == '.' || text[i] == '?' || text[i] == '!' || text[i] == ',')) {
            while ((text[i] == ' ' || text[i] == '.' || text[i] == '?' || text[i] == '!' || text[i] == ','))
                i++;
            i--;
            for (auto& c : cuvant) {
                c = std::tolower(c);
            }
            m[cuvant]++;
            v.push_back(cuvant);
            cuvant = "";

        } else {
            cuvant += text[i];
        }
    }
    std::priority_queue<std::map<std::string, int>::iterator, std::vector<std::map<std::string, int>::iterator>, Cmp>
          pq;

    std::map<std::string, int>::iterator it = m.begin();
    while (it != m.end()) {
        pq.push(it);
        it++;
    }
    while (!pq.empty()) {
        std::cout << pq.top()->first << " => " << pq.top()->second << std::endl;
        pq.pop();
    }
    std::cout << std::endl;

    for (const auto& p : m) {
        std::cout << p.first << " : " << p.second << std::endl;
    }
    return 1;
}
