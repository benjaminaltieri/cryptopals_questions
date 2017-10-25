#include "my_class.h"

#include <deque>
#include <unordered_set>

using namespace std;

MyClass::MyClass()
{
}

MyClass::~MyClass()
{
}

string MyClass::str_repr() const
{
    return str_repr_;
}

vector<string> MyClass::mesh_path(unordered_map<string, vector<string> >& mesh, pair<string, string> connection)
{
    // corner case of loopback
    if (connection.first == connection.second) return {};
    unordered_set<string> visited;
    deque<deque<string> > next;

    deque<string> start, valid_path;
    start.push_front(connection.first);
    next.push_back(start);
    while (valid_path.empty() && !next.empty())
    {
        deque<string> path = next.front();
        next.pop_front();
        visited.insert(path.front());
        auto it = mesh.find(path.front());
        if (it != mesh.end()) {
            for(const string& name : it->second)
            {
                if (name == connection.second) { // found it!
                    valid_path = path;
                    valid_path.push_front(name);
                    break;
                } else if (visited.find(name) == visited.end()) {
                    deque<string> new_path = path;
                    new_path.push_front(name);
                    next.push_back(new_path);
                }
            }
        }

    }

    // undeque path if it was populated
    vector<string> result;
    while (!valid_path.empty()) {
        result.push_back(valid_path.back());
        valid_path.pop_back();
    }

    return result;
}
