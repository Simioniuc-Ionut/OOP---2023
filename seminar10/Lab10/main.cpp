#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <functional>
#include <filesystem>
using namespace std;
class FileException : public exception {
  private:
    string filename;
    string message;
  public:
    FileException(string filename, string message) : filename(filename), message(message) {
    }
    const char* what() const throw() {
        string err = "FileException: ";
        err += message;
        err += " - ";
        err += filename;
        return err.c_str();
    }
};

class CommandManager {
private:
    map<string, function<void(vector<string>)>> commands;
    map<string, int> times;

public:
    void add(string name, function<void(vector<string>)> fn){
        commands[name] = fn;
        times[name] = 0;
    }
    void run() 
    {
    string tmp;
    vector<string> args;

    while (true) {
        printf("\n");

        std::getline(std::cin, tmp);
        args.clear();

        auto ptr = strtok(&tmp[0], " ");
        while (ptr) {
            args.push_back(ptr);
            ptr = strtok(nullptr, " ");
        }

        if (args.empty()) {
            // empty command, doing nothing
            continue;
        }

        auto command = args[0];
        if (command == "stop") {
            return;
        }
        auto it = commands.find(command);
        if (it == commands.end()) {
            printf("no command with that name: %s\n", command.c_str());
            continue;
        }
        // remove the command name
        args.erase(args.begin());

        try {
            it->second(args);
        } catch (FileException& e) {
            fprintf(stderr, "command `%s` failed: %s\n", command.c_str(), e.what());
        }catch (std::exception & e) {
            fprintf(stderr, "command `%s` failed: %s\n", command.c_str(), e.what());
        }
    }
    };
};

int main()
{
    CommandManager manager;

    auto ping = [](vector<string> args) { printf("pong!\n"); };
    manager.add("ping", ping);

    auto count = [](vector<string> args) {printf("counted %zu args", args.size()); };
    manager.add("count", count);
    
    int a = 0;
    auto times = [a](vector<string> args) mutable {a++; printf("number times %d", a); };
    manager.add("times", times);

    auto copy = [](vector<string> args) { 
        if (args.size() != 2) {
           cout<<"arguments error";
            return;
        }
        if(!filesystem::remove(args[1])) {
            throw FileException(args[1], "Failed to remove old output");
        }
        if(!filesystem::copy_file(args[0], args[1])) {
            throw FileException(args[0], "Failed to cpy input to output");
        }
    };
     manager.add("copy", copy);

    // add one more command of anything you'd like
     auto consons = [](vector<string> args) {
         for (auto i = args.begin(); i < args.end(); i++) {
             string key;
             key = *i;
             int nr = 0;
             for (int j = 0; j < key.size(); j++)
                 if (strchr("aeiouAEIOU", key[j]) == 0)
                     nr++;

             printf("Number of consons %s is %d \n", key.c_str(), nr);
         }
     };
     manager.add("consons", consons);

     auto allocate = [](vector<string> args) {
         size_t size = atoi(args[0].c_str());
         if (size < 0) {
             throw bad_alloc();
         }
         char* ptr = new char[size];
         delete[] ptr;
     };
     manager.add("allocate", allocate);
     manager.run();
    printf("goodbye.\n");
    return 0;
}

