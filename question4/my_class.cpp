#include "my_class.h"
#include <algorithm>

using namespace std;

MyClass::MyClass()
{
}

MyClass::~MyClass()
{
}

static bool meeting_compare(const Meeting& m1, const Meeting& m2)
{
    return m2.getStartTime() > m1.getStartTime();
}

static bool is_overlapping(const Meeting& m1, const Meeting& m2)
{
    bool m1_is_first = meeting_compare(m1, m2);
    Meeting first = m1_is_first ? m1 : m2,
           second = m1_is_first ? m2 : m1;
    return first.getEndTime() >= second.getStartTime();
}

static Meeting merge_meetings(const Meeting& m1, const Meeting& m2)
{
    unsigned int new_start =   m1.getStartTime() < m2.getStartTime()
                             ? m1.getStartTime() : m2.getStartTime(),
                   new_end =   m1.getEndTime() > m2.getEndTime()
                             ? m1.getEndTime() : m2.getEndTime();
    return Meeting(new_start, new_end);
}

vector<Meeting> MyClass::mergeRanges(vector<Meeting> meetings)
{
    vector<Meeting> merged_meetings;
    sort(meetings.begin(), meetings.end(), meeting_compare);
    Meeting merging = *meetings.begin();
    meetings.erase(meetings.begin());
    for(auto& meeting : meetings)
    {
        if(is_overlapping(meeting, merging)) {
            merging = merge_meetings(meeting, merging);
        } else {
            merged_meetings.push_back(merging);
            merging = meeting;
        }
    }
    merged_meetings.push_back(merging);
    return merged_meetings;
}
