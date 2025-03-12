#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <yaml-cpp/yaml.h>

using namespace std;
namespace fs = boost::filesystem;

// 递归获取文件夹中指定后缀的文件
bool getFilesFromFolder(const string& folder, const string& suffix, vector<string>& files) {
    fs::path path(folder);

    if (!fs::exists(path) || !fs::is_directory(path)) {
        cout << "The folder does not exist or is not a directory: " << folder << endl;
        return false;
    }

    fs::recursive_directory_iterator end_iter;
    for (fs::recursive_directory_iterator iter(path); iter != end_iter; ++iter) {
        if (fs::is_regular_file(*iter) && iter->path().extension() == suffix) {
            files.push_back(iter->path().string());
        }
    }

    return true;
}

int main() {
    string ParameterFilePath = "LoadParameters.yaml";
    YAML::Node config;
    try {
        config = YAML::LoadFile(ParameterFilePath);
    } catch (const YAML::Exception& e) {
        cerr << "Error loading YAML file: " << e.what() << endl;
        return 1;
    }

    string file_txt_folder = config["file_txt_folder"].as<string>();
    string file_csv_folder = config["file_csv_folder"].as<string>();
    string filetype = config["filetype"].as<string>();

    vector<string> files;
    if (!getFilesFromFolder(file_txt_folder, filetype, files)) {
        cerr << "Failed to get files from folder: " << file_txt_folder << endl;
        return 1;
    }
    // 使用 set 去重
    set<string> uniqueFiles(files.begin(), files.end());

    // 写入文件
    ofstream outfile_txt(file_csv_folder, ios::app);
    if (!outfile_txt.is_open()) {
        cerr << "Failed to open output file: " << file_csv_folder << endl;
        return 1;
    }

    for (const auto& file : uniqueFiles) {
        
        outfile_txt << file << "\n";
    }

    outfile_txt.close();
    cout << "File paths have been written to: " << file_csv_folder << endl;

    return 0;
}