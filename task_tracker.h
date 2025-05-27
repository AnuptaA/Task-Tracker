/*--------------------------------------------------------------------*/
/* task_tracker.h                                                     */
/* Author: Anupta Argo                                                */
/*--------------------------------------------------------------------*/

#pragma once
#include <string>

namespace N 
{
    // Task tracker class supporting adding new tasks, completing
    // existing tasks, and removing old tasks.
    class task_tracker
    {
    public:
        // Create new task_tracker object
        task_tracker(const std::string name);

        // Delete task_tracker object
        ~task_tracker();

        // Take string task as input, associate it with an integer id
        // and add an instance of it to JSON file. Return true if
        // success, else false.
        bool add_task(const std::string task, int32_t id);

        // Take string task and integer id as input and remove it from
        // JSON file if it exists. Return true if success, else false.
        bool remove_task(const std::string task, int32_t id);

        // Take string task and integer id as input and mark it as
        // completed in JSON file if it exists. Return true if success,
        // else false.
        bool complete_task(const std::string task, int32_t id);

        // Take string task and search for it in task list. Return true
        // if task is found, else false.
        bool task_exists(const std::string task) const;
    };
}