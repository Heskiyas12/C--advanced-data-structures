#include <map>
#include "generateUsers.hpp"
using namespace std;


map<string, User> buildMapByUserName(const vector<User>& users) {
    map<string, User> usersMap;

    for (const User& user : users) {
        if (!user.userName.empty()) {
            usersMap.emplace(user.userName, user);  // Use emplace instead of []
        }
        else {
            cerr << "User with missing username found, skipping..." << endl;
        }
    }

    return usersMap;
}


map<string, User> buildMapByEmail(vector<User> users) {
    map<string, User> usersMap;
    for (const auto& user : users) {
        usersMap[user.email] = user;
    }

    //cout << "TODO" << endl;

    return usersMap;
}


void printMap(const map<string, User>& aMap) {
    if (aMap.empty()) {
        cout << "The map is empty, nothing to print." << endl;
        return;
    }

    for (auto it = aMap.begin(); it != aMap.end(); ++it) {
        int index = std::distance(aMap.begin(), it);
        cout << "#" << index << " Key: " << it->first << endl;
        printAUser(it->second);
    }

    cout << "Finished printing map." << endl;
}



bool isMapSorted(const map<string, User>& aMap) {
    if (aMap.size() < 2) {
        return true;  // A map with 0 or 1 element is always sorted
    }

    auto previous = aMap.begin();

    for (auto current = std::next(aMap.begin()); current != aMap.end(); ++current) {
        if (current->first < previous->first) {
            return false;  // Not sorted if current key is less than the previous key
        }
        previous = current;
    }

    return true;  // The map is sorted
}



bool testSearchByKey(map<string, User> aMap, string keyToSearch) {
    //cout << "TODO" << endl;
    if (aMap.find(keyToSearch) != aMap.end()) {
        // If the key is found, return true
        return true;
    }

    // If the key is not found, return false
    return false;

}


bool testDeleteByKey(map<string, User> aMap, string keyToDelete) {
    //cout << "TODO" << endl;
    auto n = aMap.find(keyToDelete);
    if (n != aMap.end()) {
        // Key exists, so delete it
        aMap.erase(n);
        return true;  // Return true if deletion was successful
    }

    // Return false if the key was not found
    return false;
}


void printActiveUsers(const map<string, User>& aMap, int activeThreshold = 800) {
    if (aMap.empty()) {
        cout << "No users to print, the map is empty." << endl;
        return;
    }

    auto isActive = [activeThreshold](const User& user) {
        return user.numPosts > activeThreshold;
        };

    for (const auto& entry : aMap) {
        if (isActive(entry.second)) {
            printAUser(entry.second);
        }
    }
}



void printMostPopularCategory(const map<string, User>& aMap) {
    if (aMap.empty()) {
        std::cout << "No users available, the map is empty." << std::endl;
        return;
    }

    std::map<std::string, int> categoryCount;
    for (const auto& entry : aMap)
        categoryCount[entry.second.mostViewedCategory]++;

    auto mostPopular = std::max_element(categoryCount.begin(), categoryCount.end(),
        [](const auto& a, const auto& b) { return a.second < b.second; });

    std::cout << (mostPopular != categoryCount.end() ?
        "Most popular category: " + mostPopular->first + " with " + std::to_string(mostPopular->second) + " occurrences."
        : "No categories found.") << std::endl;
}



int main()
{
    int numUsers = 10;
    vector<User> users = generateUsers(numUsers);


    cout << "Build map with username as key" << endl;
    map<string, User> mapByUserName = buildMapByUserName(users);
    if (mapByUserName.size() == numUsers)
        cout << "  Built successfully." << endl << endl;
    else
        cout << "  Built unsuccessfully." << endl << endl;


    cout << "Print \"mapByUserName\" map:" << endl;
    printMap(mapByUserName);
    cout << endl;


    string keyToSearch = "smith55";
    cout << "Search by key: mapByUserName[\"" << keyToSearch << "\"]" << endl;
    if (testSearchByKey(mapByUserName, keyToSearch))
        cout << "  Search successfully." << endl << endl;
    else
        cout << "  Search unsuccessfully." << endl << endl;


    string keyToDelete = "smith55";
    cout << "Delete by key: \"" << keyToDelete << "\"" << endl;
    if (testDeleteByKey(mapByUserName, keyToDelete))
        cout << "  Delete successfully." << endl << endl;
    else
        cout << "  Delete unsuccessfully." << endl << endl;


    cout << "Test if map's key is sorted" << endl;
    if (isMapSorted(mapByUserName))
        cout << "  Order test passed!" << endl << endl;
    else
        cout << "  Order test failed!" << endl << endl;


    cout << "Print usernames with more than 800 tweets:" << endl;
    printActiveUsers(mapByUserName);
    cout << endl;

    cout << "Print the most popular category" << endl;
    printMostPopularCategory(mapByUserName);
    cout << endl;


    cout << " ============================================================================== " << endl << endl;


    cout << "Build map with email as key" << endl;
    map<string, User> mapByEmail = buildMapByEmail(users);
    if (mapByEmail.size() == numUsers)
        cout << "  Built successfully." << endl << endl;
    else
        cout << "  Built unsuccessfully." << endl << endl;


    keyToSearch = "kat@gmail.com";
    cout << "Search by key: mapByEmail[\"" << keyToSearch << "\"]" << endl;
    if (testSearchByKey(mapByEmail, keyToSearch))
        cout << "  Search successfully." << endl << endl;
    else
        cout << "  Search unsuccessfully." << endl << endl;


    keyToDelete = "kat@gmail.com";
    cout << "Delete by key: \"" << keyToDelete << "\"" << endl;
    if (testDeleteByKey(mapByEmail, keyToDelete))
        cout << "  Delete successfully." << endl << endl;
    else
        cout << "  Delete unsuccessfully." << endl << endl;


    return 0;
}