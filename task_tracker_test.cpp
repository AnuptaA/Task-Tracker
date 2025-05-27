/*--------------------------------------------------------------------*/
/* task_tracker_test.cpp                                                        */
/* Author: Anupta Argo                                                */
/*--------------------------------------------------------------------*/

#include <assert.h>
#include <iostream>
#include "task_tracker.h"

using namespace std;
using namespace N;

void run_tests() {
    cout << "Starting task_tracker tests..." << endl;

    // Create a tracker
    task_tracker tracker("test_tasks");

    // Test adding tasks
    bool added1 = tracker.add_task("Write unit tests", 1);
    assert(added1);

    bool added2 = tracker.add_task("Fix bug in parser", 2);
    assert(added2);

    // Duplicate ID should fail
    bool added3 = tracker.add_task("Another task", 1);
    assert(!added3);

    // Test task existence
    assert(tracker.task_exists("Write unit tests"));
    assert(!tracker.task_exists("Nonexistent task"));

    // Test completing a task
    bool completed1 = tracker.complete_task("Write unit tests", 1);
    assert(completed1);

    // Trying to complete again should fail
    bool completed_again = tracker.complete_task("Write unit tests", 1);
    assert(!completed_again);

    // Test removing a task
    bool removed = tracker.remove_task("Fix bug in parser", 2);
    assert(removed);

    // Try removing a task that doesn't exist
    bool removed_nonexistent = tracker.remove_task("Fix bug in parser", 2);
    assert(!removed_nonexistent);

    cout << "All task_tracker tests passed." << endl;
}

int main() {
    run_tests();
    return 0;
}
