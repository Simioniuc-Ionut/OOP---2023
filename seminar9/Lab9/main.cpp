#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <sstream>
#include <cstdio>
#include <queue>

struct Episode {
    std::string title;
    std::string date;
    int length;
    int viewersmm;
    double score;
    Episode(std::string title, std::string date, int length, int viewersmm, double score)
        : title(std::move(title)), date(std::move(date)), length(length), viewersmm(viewersmm), score(score) {
    }
    static Episode from_csv_columns(const std::vector<std::string>& columns) {
        std::string title = columns[0];
        std::string date = columns[1];
        int length = std::stoi(columns[2]);
        int viewersmm = std::stoi(columns[3]);
        double score = std::stod(columns[4]);
        return Episode(title, date, length, viewersmm, score);
    }
    std::string to_string() const {
        std::stringstream ss;
        ss << title << "," << date << "," << length << "," << viewersmm << "," << score;
        return ss.str();
    }
};

class CsvIterator {
  private:
    std::istream& stream;
    std::vector<std::string> row;

  public:
    explicit CsvIterator(std::istream& str) : stream(str) {
    }

    std::vector<std::string> operator*() const {
        return row;
    }
    CsvIterator& operator++() {
        readNextRow();
        return *this;
    }
    CsvIterator operator++(int) {
        CsvIterator tmp(*this);
        ++(*this);
        return tmp;
    }

    bool operator==(const CsvIterator& rhs) const {
        return (this == &rhs || (stream.eof() && rhs.stream.eof()));
    }
    bool operator!=(const CsvIterator& rhs) const {
        return !(*this == rhs);
    }
    void readNextRow() {
        row.clear();
        std::string line;
        if (std::getline(stream, line)) {
            std::string::size_type pos = 0, last_pos = 0;
            while ((pos = line.find_first_of(',', last_pos)) != std::string::npos) {
                std::string field = line.substr(last_pos, pos - last_pos);
                if (field.front() == '"' && field.back() != '"') {
                    do {
                        pos = line.find_first_of(',', pos + 1);
                        field = line.substr(last_pos, pos - last_pos);
                    } while (field.back() != '"');
                }
                if (field.front() == '"' && field.back() == '"') {
                    field.erase(0, 1);
                    field.erase(field.size() - 1);
                }
                row.push_back(field);
                last_pos = pos + 1;
            }
            std::string field = line.substr(last_pos);
            if (field.front() == '"' && field.back() == '"') {
                field.erase(0, 1);
                field.erase(field.size() - 1);
            }
            row.push_back(field);
        }
    }
};
class CsvReader {
  private:
    std::ifstream& file;
  public:
    CsvReader(std::ifstream& file) : file(file) {
    }
    CsvIterator begin() {
        file.seekg(0);
        return CsvIterator(file);
    }
    CsvIterator end() {
        return CsvIterator(file);
    }
};


int main() {
    std::ifstream input_file("episodes.csv");
    if (!input_file.is_open()) {
        printf("File couldn't be opened\n");
        return 1;
    }
    CsvReader reader(input_file);

    std::vector<Episode> episodes;
    for (CsvIterator it = reader.begin(); it != reader.end(); ++it) {
        std::vector<std::string> columns = *it;
        Episode episode = Episode::from_csv_columns(columns);
        episodes.push_back(episode);
    }

    printf("number of episodes: %zu\n\n", episodes.size());

    std::sort(episodes.begin(), episodes.end(), [](const Episode& a, const Episode& b) {
        if (a.score != b.score) {
            return a.score > b.score;
        } else {
            return a.title < b.title;
        }
    });

    printf("10 most appreciated episodes:\n");
    for (int i = 0; i < 10 && i < episodes.size(); i++) {
        std::cout<<episodes[i].title.c_str()<<" "<<episodes[i].score<<std::endl;
    }
    printf("\n");

    std::sort(episodes.begin(), episodes.end(), [](const Episode& a, const Episode& b) {
        if (a.length != b.length) {
            return a.length > b.length;
        } else {
            return a.title < b.title;
        }
    });

    printf("10 longest episodes:\n");
    for (int i = 0; i < 10 && i < episodes.size(); i++) {
        printf("%s (%d minutes)\n", episodes[i].title.c_str(), episodes[i].length);
    }
    printf("\n");

    std::map<int, int> year_count;
    for (const Episode& episode : episodes) {
        int year =std::stoi( episode.date.substr(0,4));
        year_count[year]++;
    }

    int most_episodes_year = -1;
    int most_episodes_count = 0;
    for (const auto& [year, count] : year_count) {
        if (count > most_episodes_count) {
            most_episodes_count = count;
            most_episodes_year = year;
        }
    }

    printf("Year with most episodes: %d (%d episodes)\n\n", most_episodes_year, most_episodes_count);

    std::ofstream output_file("output.txt");
    for (const Episode& episode : episodes) {
        output_file << episode.to_string() << std::endl;
    }

    return 0;
}