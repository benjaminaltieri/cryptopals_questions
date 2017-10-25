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
    if(!mesh.count(connection.first) || !mesh.count(connection.second)) return {};
    // corner case of loopback
    if (connection.first == connection.second) return {connection.first};
    unordered_set<string> visited;
    deque<deque<string> > next;

    deque<string> start, valid_path;
    start.push_back(connection.first);
    next.push_back(start);
    while (valid_path.empty() && !next.empty())
    {
        deque<string> path = next.front();
        next.pop_front();
        string current = path.back();
        visited.insert(current);
        auto it = mesh.find(current);
        if (it != mesh.end()) {
            for(const string& child : it->second)
            {
                if (child == connection.second) { // found it!
                    valid_path = path;
                    valid_path.push_back(child);
                    break;
                } else if (visited.find(child) == visited.end()) {
                    deque<string> new_path = path;
                    new_path.push_back(child);
                    next.push_back(new_path);
                }
            }
        }

    }

    return {valid_path.begin(), valid_path.end()};
}
