/*--------------------------------------------------------------------*/
/* task_tracker.cpp                                                             */
/* Author: Anupta Argo                                                */
/*--------------------------------------------------------------------*/

#include <assert.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <list>
#include <unordered_set>
#include <fstream>
#include "nlohmann/json.hpp"
#include "task_tracker.h"

using namespace std;
using json = nlohmann::json;

typedef struct task_node* task_node_t;

struct task_node {
    string task_name;
    int32_t task_id;
    int32_t task_status;                              // 1 if complete
};

namespace N {
    string filename;                            // name of JSON file
    list<task_node_t> task_list;                // list contaiining tasks
    unordered_set<int32_t> id_set;              // set tracking existing ids;

    task_tracker::task_tracker(const string name) {
        assert(name.length() > 0);

        string extension = ".json";
        filename = name + extension;
        cout << "Created new task tracker." << endl;

    }

    task_tracker::~task_tracker() {
        if (ifstream(filename)) {
            if (remove(filename.c_str()) != 0) {
                cout << "Warning: Failed to remove existing file: " << filename << endl;
            } else {
                cout << "Deleted existing task tracker file: " << filename << endl;
            }
        }

        for (auto task : task_list) {
            delete(task);
        }

        filename.clear();
        task_list.clear();
        id_set.clear();
    }

    bool task_tracker::add_task(const string task, int32_t id) {
        assert(filename.length() > 0);

        if (id_set.find(id) != id_set.end()) {
            cout << "Failed to add task: " << task << ", id: " << id << " - ID already exists." << endl;
            return false;
        } else id_set.insert(id);

        task_node_t new_task = new task_node{task, id, 0};
        task_list.push_back(new_task);

        json json_task = json::object();
        json_task["task_name"] = new_task->task_name;
        json_task["task_id"] = new_task->task_id;
        json_task["task_status"] = new_task->task_status;

        string json_string = json_task.dump(4);
        ofstream output(filename);

        if (output.is_open()) {
            output << json_string << endl;
            cout << "Added task: " << task << ", id: " << id << endl;
            return true;
        } else {
            cout << "Failed to add task: " << task << ", id: " << id << " - Unable to open file." << endl;
            return false;
        }

    }

    bool task_tracker::remove_task(const string task, int32_t id) {
        bool res = false;

        for (auto it = task_list.begin(); it != task_list.end(); ++it) {
            string task_name = (*it)->task_name;
            int32_t task_id = (*it)->task_id;
            if (task == task_name && id == task_id) {
                res = true;
                task_list.erase(it);
                break;
            }
        }

        if (!res) {
            cout << "Failed to remove task: " << task << ", id: " << id << " - Task not found." << endl;
            return res;
        }

        json json_array = json::array();

        for (const auto& exist_task : task_list) {
            json json_task = json::object();
            json_task["task_name"] = exist_task->task_name;
            json_task["task_id"] = exist_task->task_id;
            json_task["task_status"] = exist_task->task_status;
            json_array.push_back(json_task);
        }

        string json_string = json_array.dump(4);
        ofstream output(filename);

        if (output.is_open()) {
            res = true;
            output << json_string << endl;
            cout << "Removed task: " << task << ", id: " << id << endl;
        } else {
            cout << "Failed to remove task: " << task << ", id: " << id << " - Unable to open file." << endl;
        }

        return res;

    }

    bool task_tracker::complete_task(const string task, int32_t id) {
        bool taskFound = false;
        bool res = false;

        for (auto it = task_list.begin(); it != task_list.end(); ++it) {
            string task_name = (*it)->task_name;
            int32_t task_id = (*it)->task_id;
            int32_t task_status = (*it)->task_status;

            if (task_name == task && id == task_id) {
                taskFound = true;
                if (task_status != 1) {
                    res = true;
                    (*it)->task_status = 1;
                }
                break;
            }

        }

        if (!taskFound) {
            cout << "Failed to complete task: " << task << ", id: " << id << " - Task not found" << endl;
            return taskFound;
        }

        if (!res) {
            cout << "Failed to complete task: " << task << ", id: " << id << " - Task already complete" << endl;
            return res;
        }

        json json_array = json::array();

        for (const auto& exist_task : task_list) {
            json json_task = json::object();
            json_task["task_name"] = exist_task->task_name;
            json_task["id"] = exist_task->task_id;
            json_task["status"] = exist_task->task_status;
        }

        string json_string = json_array.dump(4);
        ofstream output(filename);

        if (output.is_open()) {
            output << json_string << endl;
            cout << "Completed task: " << task << ", id: " << id << endl;
        } else {
            cout << "Failed to complete task: " << task << ", id: " << id << " - Unable to open file." << endl;
        }

        return res;

    }

    bool task_tracker::task_exists(const string task) const {
        for (const auto& existing_task : task_list) {
            if (existing_task->task_name == task) return true;
        }
        return false;
    }
}