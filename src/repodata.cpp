#include <fstream>   // For file input/output operations
#include <iostream>  // For basic input/output
#include <sstream>   // For string stream operations
#include <string>    // For string handling
#include <vector>    // For dynamic arrays
#include <cstring>
#include "repodata.h"
#include "dataframe.h"
#include "sqlite3.h"
#include "series.h"
#include <fcntl.h>
#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/file.h>  // For file locking operations


// Constructor
RepoData::RepoData() {
    strategy_ = nullptr;
}

// Set Strategy
void RepoData::setStrategy(int type, std::string path, DB *db, std::string table) {
    /**
    * @brief Set the strategy to extract data
    * @param type: Type of the strategy
    * @param path: Path of the file
    * @param db: Database object
    * @param table: Table name
    * @return None
    */
    delete strategy_;
    switch (type) {
        case ExtractorCSVType:
            strategy_ = new ExtractorCSV(path);
            break;
        case ExtractorTXTType:
            strategy_ = new ExtractorTXT(path);
            break;
        case ExtractorSQLType:
            strategy_ = new ExtractorSQL(db, table);
            break;
        default:
            strategy_ = nullptr;
            break;
    }
}

DataFrame<DefaultObject> RepoData::extractData() {
    /**
    * @brief Extract data from the file
    * @return DataFrame<DefaultObject>: Dataframe object
    */
   int file_descriptor = open(strategy_->path_.c_str(), O_RDONLY);

    if (file_descriptor == -1) {
        std::cerr << "Error opening file." << std::endl;
        return DataFrame<DefaultObject>();
    }

    struct flock fl;
    fl.l_type   = F_RDLCK;  // F_RDLCK, F_WRLCK, F_UNLCK
    fl.l_whence = SEEK_SET; // SEEK_SET, SEEK_CUR, SEEK_END
    fl.l_start  = 0;        // Offset from l_whence
    fl.l_len    = 0;        // length, 0 = to EOF
    fl.l_pid    = getpid(); // our PID

    if (fcntl(file_descriptor, F_SETLKW, &fl) == -1) {
        std::cerr << "Failed to lock the file: " << strategy_->path_ << std::endl;
        return DataFrame<DefaultObject>();
    }

    DataFrame<DefaultObject> df = strategy_->extractData();

    fl.l_type = F_UNLCK;
    fcntl(file_descriptor, F_SETLK, &fl); // Unlock the file
    close(file_descriptor);
    return df;
}

void RepoData::loadData(DataFrame<DefaultObject> *df) {
    /**
    * @brief Load data to the file
    * @param df: Dataframe object
    * @return None
    */
//    int file_descriptor = open(strategy_->path_.c_str(), O_WRONLY);

//     if (file_descriptor == -1) {
//         std::cerr << "Error opening file load: " << strategy_->path_.c_str() << std::endl;
//         return;
//     }

//     if (flock(file_descriptor, LOCK_EX) == -1) {
//         std::cerr << "Error acquiring shared lock." << std::endl;
//         close(file_descriptor);
//         return;
//     }
    strategy_->loadData(df);

    // if (flock(file_descriptor, LOCK_UN) == -1) {
    //     std::cerr << "Error releasing lock." << std::endl;
    // }

    // close(file_descriptor);
}

std::vector<std::vector<std::string>> ExtractorEstrategy::readTextFile(std::string sep) {
    /**
    * @brief Read data from the file
    * @param sep: Separator
    * @return std::vector<std::vector<std::string>>: Data
    */
    std::ifstream file;

    file.open(path_, std::ios::in);
    if (!file.is_open()) {
         std::cerr << "Error opening file" << std::endl;
         return std::vector<std::vector<std::string>>();
    }

    std::string line;
    std::vector<std::vector<std::string>> allData = {};

    while (std::getline(file, line, '\n')) {
        std::stringstream ss(line);
        std::string cell;
        std::vector<std::string> data;
        while (std::getline(ss, cell, sep[0])) {
            data.push_back(cell);
        }
        allData.push_back(data);
    }
    return allData;
}

void ExtractorEstrategy::saveTextFile(DataFrame<DefaultObject> *df, std::string sep) {
    /**
    * @brief Save data to the file
    * @param df: Dataframe object
    * @param sep: Separator
    * @return None
    */

    std::ofstream file;
    file.open(path_, std::ios::out);
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }

    // get size
    std::pair<int, int> s = df->shape;

    SavetoFile saver(file);

    for (auto column : df->columns) {
        file << column << sep;
    }
    file << std::endl;

    for (int i = 0; i < s.first; i++) {
        for (int j = 0; j < s.second; j++) {
            std::visit(saver, df->series[i][j]);
            file << sep;
        }
        file << std::endl;
    }

    file.close();
}

// ExtractorCSV
DataFrame<DefaultObject> ExtractorCSV::extractData() {
    /**
    * @brief Extract data from the CSV file
    * @return DataFrame<DefaultObject>: Dataframe object
    */
    std::cout << "Extracting data from CSV file" << std::endl;
    std::vector<std::vector<std::string>> data = readTextFile(",");
    std::vector<std::string> columns = data[0];
    DataFrame<DefaultObject> df;
    data.erase(data.begin());
    for (auto row : data) {
        std::map<std::string, DefaultObject> rowMap;
        for (int i = 0; i < columns.size(); i++) {
            rowMap[columns[i]] = row[i];
        }
        df.append(rowMap);
    }
    return df;
}

void ExtractorCSV::loadData(DataFrame<DefaultObject> *df) {
    /**
    * @brief Load data to the CSV file
    * @param df: Dataframe object
    * @return None
    */
    std::cout << "Loading data into CSV file" << std::endl;
    saveTextFile(df, ",");
}

// ExtractorTXT
DataFrame<DefaultObject> ExtractorTXT::extractData() {
    /**
    * @brief Extract data from the TXT file
    * @return DataFrame<DefaultObject>: Dataframe object
    */

    std::cout << "Extracting data from TXT file" << std::endl;
    std::vector<std::vector<std::string>> data = readTextFile(";");
    std::vector<std::string> columns = data[0];
    DataFrame<DefaultObject> df;
    data.erase(data.begin());
    for (auto row : data) {
        std::map<std::string, DefaultObject> rowMap;
        for (int i = 0; i < columns.size(); i++) {
            rowMap[columns[i]] = row[i];
        }
        df.append(rowMap);
    }
    return df;
}

void ExtractorTXT::loadData(DataFrame<DefaultObject> *df) {
    /**
    * @brief Load data to the TXT file
    * @param df: Dataframe object
    * @return None
    */
    std::cout << "Loading data into TXT file" << std::endl;
    saveTextFile(df, " ");
}

// ExtractorSQL
DataFrame<DefaultObject> ExtractorSQL::extractData() {
    /**
    * @brief Extract data from the SQL database
    * @return DataFrame<DefaultObject>: Dataframe object
    */

    std::cout << "Extracting data from SQL database" << std::endl;
    return DataFrame<DefaultObject>();
}

void ExtractorSQL::loadData(DataFrame<DefaultObject> *df) {
    /**
    * @brief Load data to the SQL database
    * @param df: Dataframe object
    * @return None
    */
    std::cout << "Loading data into SQL database" << std::endl;
    std::pair<int, int> s = df->shape;
    for (int j = 0; j < s.first; j++) {
        int v = std::get<int>(df->series[0][j]);
        std::string a = std::get<std::string>(df->series[1][j]);
        db_->insertData(table_, a, v);
    }
}