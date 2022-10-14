#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <rime/dict/table.h>

std::multimap<std::string, std::string> code2wordMap;
std::set<std::string> codeSet;

void queryCode(rime::Table& table, int i0) {
    rime::TableAccessor v = table.QueryWords(i0);
    if (!v.exhausted()) {
        std::string code = table.GetSyllableById(i0);
        do {
            rime::string str = table.GetEntryText(*v.entry());
            unsigned char c = str[0];
            if (c < 20) {
                continue;
            }
            code2wordMap.insert(std::pair<std::string, std::string>(code, str));
            codeSet.insert(code);
        } while(v.Next());
    }
}

void printW2CTable() {
    std::string prev = "";
    bool first = true;
    for (auto codeIt = codeSet.begin(); codeIt != codeSet.end(); ++codeIt) {
        std::string code = *codeIt;
        for (auto wordIt = code2wordMap.lower_bound(code); wordIt != code2wordMap.upper_bound(code); ++wordIt) {
            std::string word = wordIt->second;
            std::cout << word << "\t" << code << "\n";
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 3) {
        std::cerr << "Usage: " << argv[0] << " <file> [version]" << std::endl;
        return 1;
    }
    std::string fileName(argv[1]);
    std::string version = "1.0";
    if (argc == 3) {
        version = argv[2];
    }

    rime::Table table(fileName);
    if (table.Load() == false) {
        std::cerr << "ERROR: Can't find INDEX section for table.bin file."<< std::endl;
        return 1;
    }

    // Remove directory if present.
    // Do this before extension removal incase directory has a period character.
    const size_t last_slash_idx = fileName.find_last_of("\\/");
    if (std::string::npos != last_slash_idx) {
        fileName.erase(0, last_slash_idx + 1);
    }

    // Remove extension if present.
    const size_t period_idx = fileName.find('.');
    if (std::string::npos != period_idx){
        fileName.erase(period_idx);
    }

    std::cout << "---\n"
            "name: ";
    std::cout << fileName;
    std::cout <<"\nversion: \"" << version <<"\"\n"
            "sort: original\n"
            "use_preset_vocabulary: false\n"
            "...\n";
    uint32_t synLen = table.Find<rime::table::Metadata>(0)->num_syllables;
    for (int i = 0; i < synLen; i++) {
        queryCode(table, i);
    }
    printW2CTable();
    return 0;
}
