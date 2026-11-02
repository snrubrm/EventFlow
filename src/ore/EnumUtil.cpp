#include <algorithm>
#include <ore/EnumUtil.h>

namespace ore {

int detail::EnumUtil::FindIndex(int value, const IterRange<const int*>& values) {
    auto it = std::find_if(values.begin(), values.end(), [value](int x) { return value == x; });
    if (it == values.end())
        return -1;
    return static_cast<int>(it - values.begin());
}

// NON_MATCHING: the original lowers the searches and trimming through different loop and register sequences.
void detail::EnumUtil::Parse(const IterRange<StringView*>& out, StringView definition) {
    const char* text = definition.data();
    int length = definition.size();
    for (auto& name : out) {
        int separator = 0;
        while (separator < length && text[separator] != ',' && text[separator] != '=')
            ++separator;

        int first = 0;
        int last = separator;
        while (first < last && (text[first] == ' ' || (text[first] >= '\t' && text[first] <= '\r')))
            ++first;
        while (last > first && (text[last - 1] == ' ' || (text[last - 1] >= '\t' && text[last - 1] <= '\r')))
            --last;
        const char* name_start = text;
        if (first != 0)
            name_start += first;
        name = StringView(name_start, last - first);

        int next = separator;
        while (next < length && text[next] != ',')
            ++next;
        if (next < length)
            ++next;
        else
            next = separator;
        if (next != 0)
            text += next;
        length -= next;
    }
}

}  // namespace ore
