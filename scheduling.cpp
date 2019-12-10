/*      Project 2
        EECE 7205 - Fundamentals of Computer Engineering

        by Anna DeVries and Hannah Khafif
        1 December 2019

        Usage:
        ./project

        Problem Description:            
        Implement and test the proposed algorithms 
        in "Energy and Performance-Aware Task Scheduling 
        in a Mobile Cloud Computing Environment" by Xue
        Lin, Yanzhi Wang, Qing Xie, and Massoud Pedram.  

        Steps:
        A) Initial Scheduling
            1. Primary assignment
            2. Task prioritizing
            3. Execution unit selection
        B) Task Migration
            1. Outer Loop: determines the tasks for 
            migration and the new execution locations for the tasks.
            2. Kernel Algorithm: reschedules task executions
                                        */

/*      Libraries to include            */
#include <stdio.h>
#include <stdlib.h>
#include <iostream> 
#include <vector>
#include <iomanip>
#include <bits/stdc++.h>
#include <algorithm>
#include <iterator>

/*      Macros                          */
#define DEBUG false                      // Prints debugging information
#define EXAMPLE 1                        // Defines which example to run: 1, 2, 3

#if EXAMPLE == 1
#define R_s 5                            // Sending rate to cloud
#define R_r 5                            // Receiving rate from cloud
#define P_1 6                            // Power to execute task on core 1
#define P_2 7                            // Power to execute task on core 2
#define P_3 8                            // Power to execute task on core 3
#define P_s 7                            // Power to send task to cloud
#define T_MAX 20                         // Max completion time for tasks
#endif

#if EXAMPLE == 2
#define R_s 3                            // Sending rate to cloud
#define R_r 3                            // Receiving rate from cloud
#define P_1 3                            // Power to execute task on core 1
#define P_2 2                            // Power to execute task on core 2
#define P_3 1                            // Power to execute task on core 3
#define P_s 2                            // Power to send task to cloud
#define T_MAX 20                         // Max completion time for tasks
#endif

#if EXAMPLE == 3
#define R_s 9                           // Sending rate to cloud
#define R_r 9                            // Receiving rate from cloud
#define P_1 5                            // Power to execute task on core 1
#define P_2 6                            // Power to execute task on core 2
#define P_3 7                            // Power to execute task on core 3
#define P_s 5                            // Power to send task to cloud
#define T_MAX 20                         // Max completion time for tasks
#endif

/*      Typedefs                        */
typedef struct Characteristics_* Characteristics;
typedef struct Predeccessors_* Predeccessors;
typedef struct Node_* Node;
typedef struct Graph_* Graph;
typedef struct Rect_ Rect;

/*      Struct objects                  */
// Characteristics list object 
struct Characteristics_{
    int dst;
    Characteristics next;
};

// Successors list object
struct Predeccessors_{
    int src;
    Predeccessors nextSucc;
};

// Head node pointing to characteristics object 
struct Node_{
    int upload_weight;
    int download_weight;
    int cloud;
    int core1;
    int core2;
    int core3;
    int cloud_task;
    float T_re; 
    float priority;
    Characteristics head;
    Predeccessors otherhead;
};

// Graph object 
struct Graph_{
    int length;
    Node array;
};

// Rect Struct
struct Rect_{
    float total_time;
    float total_energy;
    std::vector<std::vector<float>> core1;
    std::vector<std::vector<float>> core2;
    std::vector<std::vector<float>> core3;
    std::vector<std::vector<float>> wireless_send_ch;
    std::vector<std::vector<float>> cloud;
    std::vector<std::vector<float>> wireless_recv_ch;

    float updated_total_time;
    float updated_total_energy;
    std::vector<std::vector<float>> updated_core1;
    std::vector<std::vector<float>> updated_core2;
    std::vector<std::vector<float>> updated_core3;
    std::vector<std::vector<float>> updated_wireless_send_ch;
    std::vector<std::vector<float>> updated_cloud;
    std::vector<std::vector<float>> updated_wireless_recv_ch;

    Rect_(std::vector<std::vector<float>>c1,
    std::vector<std::vector<float>>c2,
    std::vector<std::vector<float>>c3,
    std::vector<std::vector<float>> wSend,
    std::vector<std::vector<float>> cl,
    std::vector<std::vector<float>> wRecv,
    float tTime,
    float tEnergy,
    std::vector<std::vector<float>>new_c1,
    std::vector<std::vector<float>>new_c2,
    std::vector<std::vector<float>>new_c3,
    std::vector<std::vector<float>>new_wSend,
    std::vector<std::vector<float>>new_cl,
    std::vector<std::vector<float>>new_wRecv,
    float new_tTime,
    float new_tEnergy
    ) {
        core1=c1;
        core2=c2;
        core3=c3;
        wireless_send_ch = wSend;
        cloud = cl;
        wireless_recv_ch = wRecv;
        total_time = tTime;
        total_energy = tEnergy;
        updated_core1=new_c1;
        updated_core2=new_c2;
        updated_core3=new_c3;
        updated_wireless_send_ch = new_wSend;
        updated_cloud = new_cl;
        updated_wireless_recv_ch = new_wRecv;
        updated_total_time = new_tTime;
        updated_total_energy = new_tEnergy;
    }
};

/*      Graph functions                 */
// Creates a new node on the graph
Characteristics newNodeList(int dst){
    // Local Variables 
    Characteristics newNode;

    // Initialize newNode
    newNode = (Characteristics) malloc(sizeof(struct Characteristics_));

    // Initialize characteristics
    (*newNode).dst = dst;
    (*newNode).next = NULL;

    // Return function
    return newNode;    
}

// Creates a new node on the graph for sucessors
Predeccessors newPredeccessors(int src){
    // Local Variables 
    Predeccessors newSucc;

    // Initialize newNode
    newSucc = (Predeccessors) malloc(sizeof(struct Predeccessors_));

    // Initialize characteristics
    (*newSucc).src = src;
    (*newSucc).nextSucc = NULL;

    // Return function
    return newSucc;    
}

// Creates the graph
Graph createGraph(int length){
    // Local Variables 
    Graph graph;
    int i;

    // Initialize graph
    graph = (Graph) malloc(sizeof(struct Graph_));
    (*graph).length = length;

    // Initialize array
    (*graph).array = (Node) malloc(sizeof(struct Node_) * length);
    for(i = 0; i < length; i++){
        (*graph).array[i].head = NULL;
        (*graph).array[i].upload_weight = 0;
        (*graph).array[i].download_weight = 0;
        (*graph).array[i].cloud = 0;
        (*graph).array[i].core1 = 0;
        (*graph).array[i].core2 = 0;
        (*graph).array[i].core3 = 0;
        (*graph).array[i].priority = 0;
    }

    // Return function
    return graph;
}

// Add successor to graph
void addPredeccessors(Graph graph, int src, int dst){
    // Local Variables 
    Predeccessors newSucc;
    
    // Create successors for node
    newSucc = newPredeccessors(src);
    (*newSucc).nextSucc = (*graph).array[dst].otherhead;
    (*graph).array[dst].otherhead = newSucc;
}

// Add point to graph
void addPoint(Graph graph, int src, int dst){
    // Local Variables 
    Characteristics newNode;
    
    // Create node for directed graph
    newNode = newNodeList(dst);
    (*newNode).next = (*graph).array[src].head;
    (*graph).array[src].head = newNode;

    // Add predeccessor values
    addPredeccessors(graph, src, dst);
}

// Add weight to node
void addWeight(Graph graph, int src, int upload_weight, int download_weight, int core1, int core2, int core3, int cloud_weight){ 
    // Create node for directed graph
    (*graph).array[src].upload_weight = upload_weight;
    (*graph).array[src].download_weight = download_weight;
    (*graph).array[src].cloud = cloud_weight;
    (*graph).array[src].core1 = core1;
    (*graph).array[src].core2 = core2;
    (*graph).array[src].core3 = core3;
    (*graph).array[src].cloud_task = 0;
    (*graph).array[src].T_re = 0;
}

// Destroy graph
Graph destroy(Graph graph){
    // Free heap 
    free((*graph).array);
    free(graph);

    // Return empty graph
    graph = NULL;
    return graph;
}

/*      Utility functions               */

// Initial print of adj list and task table
void initialPrint(Graph graph){
    // Local Variables 
    int i;
    Graph part;
    Characteristics characteristics;

    // Print graph as adjacency list 
    std::cout << std::endl;
    std::cout << "\tFigure 1: Task Graph\n";
    std::cout << "---------------------------------------------\n";
    std::cout << "\tGraph as Adj. Lists\n";
    for(i = 1; i < (*graph).length; i++){
        std::cout << "{" << i << ":";
        characteristics = (*graph).array[i].head;
        while(characteristics != NULL){
            std::cout << " " << (*characteristics).dst;
            characteristics = (*characteristics).next;
        }
        std::cout << "}  \n";
    }

    // Print task table 
    std::cout << "\tTask Table\n";
    std::cout << "Task" << "\tCore1" << "\tCore2" << "\tCore3" << std::endl;
    for(i = 1; i < (*graph).length; i++){

        // characteristics = (*graph).array[i].head;
        std::cout << i << "\t";
        std::cout << (*graph).array[i].core1 << "\t" ;
        std::cout << (*graph).array[i].core2 << "\t" ;
        std::cout << (*graph).array[i].core3 << "\n" ;
    }
}

// Print each individual timeline
void printTimeline(std::vector<std::vector<float>> core){
    std::vector<char> time_line;
    int flag = 0, prev_end = 0, start_time, total_time, end_time, j = 0;
    float addon = 0.0;

    std::setprecision(0);
    for(auto i : core){
        // Compare start/end time with current location in time line
        start_time = static_cast<int>(i.at(1)*100);
        total_time = static_cast<int>(i.at(2)*100);
        end_time = start_time + total_time;

        if (time_line.size() > 0 && prev_end == start_time){
            // Fix last
            time_line[time_line.size() -1] = 'I';
        }

        while(j <= end_time){
            if(abs(j - start_time) <= 5){
                time_line.push_back('[');
                if(flag > 0){
                    flag--;
                }
                else{
                    std::cout << " ";
                }
            }
            else if (abs(j - end_time) <= 10){
                time_line.push_back(']');
                if(flag > 0){
                    flag--;
                }
                else {
                    std::cout << " ";
                }
            }
            else {
                time_line.push_back(' ');
                if(flag > 0){
                    flag--;
                }
                else {
                    std::cout << " ";
                }
            }

            if (abs(j - ((end_time + start_time) / 2) + 40) <= 5) {
                std::cout << std::setprecision(0) <<  "Task " << i.at(0);
                flag = 6;
            }
            j += 10;
            prev_end = end_time;
        }
    }
    std::cout << std::endl;

    // Print saved timeline
    for(auto i : time_line){
        std::cout << i;
    }
    std::cout << std::endl;   

    // Print timeline's x-axis                                                                                                       
    std::cout << "|---------|---------|---------|---------|---------|---------|---------|---------|---------|---------|---------|---------|---------|---------|---------|---------|---------|---------|---------|---------|---------|---------|---------|---------|---------|---------|---------|---------|---------|--------->\n";
    std::cout << "0         1         2         3         4         5         6         7         8         9         10        11        12        13        14        15        16       17         18        19        20        21        22        23        24        25        26        27        28        29 (unit time)\n\n";
}

// Print out Figure 3 scheduling
void fig3Print(std::vector<std::vector<float>> core1, std::vector<std::vector<float>> core2, std::vector<std::vector<float>> core3, std::vector<std::vector<float>> wireless_send_ch, std::vector<std::vector<float>> cloud, std::vector<std::vector<float>> wireless_recv_ch){
    // Local Variables
    std::vector<char> time_line;
    int flag;
    float addon;

    // Print start and end times of each medium
    if(DEBUG == true){
        std::cout << "\t\t\tIntermediate Execution Times\n";
        std::cout << "\t\t\t\tCore1\n";
        for(auto i : core1){
            std::cout << std::setprecision(0) << "Task: " << i.at(0) << "  \t\t";
            std::cout << std::setprecision(1) << "Start time: " << i.at(1) << "  \t\t";
            std::cout << "End time: " << i.at(2) + i.at(1) << "    \t\t";
            std::cout << "Total time: " << i.at(2)  << std::endl;
        }
        std::cout << "\t\t\t\tCore2\n";
        for(auto i : core2){
            std::cout << std::setprecision(0) << "Task: " << i.at(0) << "  \t\t";
            std::cout << std::setprecision(1) << "Start time: " << i.at(1) << "  \t\t";
            std::cout << "End time: " << i.at(2) + i.at(1) << "    \t\t";
            std::cout << "Total time: " << i.at(2)  << std::endl;
        }
        std::cout << "\t\t\t\tCore3\n";
        for(auto i : core3){
            std::cout << std::setprecision(0) << "Task: " << i.at(0) << "  \t\t";
            std::cout << std::setprecision(1) << "Start time: " << i.at(1) << "  \t\t";
            std::cout << "End time: " << i.at(2) + i.at(1) << "    \t\t";
            std::cout << "Total time: " << i.at(2)  << std::endl;
        }
        std::cout << "\t\t\t\tWireless Sending Channel\n";
        for(auto i : wireless_send_ch){
            std::cout << std::setprecision(0) << "Task: " << i.at(0) << "  \t\t";
            std::cout << std::setprecision(1) << "Start time: " << i.at(1) << "  \t\t";
            std::cout << "End time: " << i.at(2) + i.at(1) << "    \t\t";
            std::cout << "Total time: " << i.at(2)  << std::endl;
        }
        std::cout << "\t\t\t\tCloud\n";
        for(auto i : cloud){
            std::cout << std::setprecision(0) << "Task: " << i.at(0) << "  \t\t";
            std::cout << std::setprecision(1) << "Start time: " << i.at(1) << "  \t\t";
            std::cout << "End time: " << i.at(2) + i.at(1) << "    \t\t";
            std::cout << "Total time: " << i.at(2)  << std::endl;
        }
        std::cout << "\t\t\t\tWireless Receiving Channel\n";
        for(auto i : wireless_recv_ch){
            std::cout << std::setprecision(0) << "Task: " << i.at(0) << "  \t\t";
            std::cout << std::setprecision(1) << "Start time: " << i.at(1) << "  \t\t";
            std::cout << "End time: " << i.at(2) + i.at(1) << "    \t\t";
            std::cout << "Total time: " << i.at(2)  << std::endl;
        }
        std::cout << std::endl;
    }

    std::cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";

    // Print timeline for Core 1
    // Set addon and flag to 0
    addon = 0.0;
    flag = 0;

    // For each task selected on core 1
    std::cout << "\t\t\t\t\t\t\t\tCore 1 Timeline\n";
    printTimeline(core1);
    
    // For each task selected on core 2
    std::cout << "\t\t\t\t\t\t\t\tCore 2 Timeline\n";
    printTimeline(core2);

    // For each task selected on core 3
    std::cout << "\t\t\t\t\t\t\t\tCore 3 Timeline\n";
    printTimeline(core3);

    // For each task selected on Wireless Send Channel
    std::cout << "\t\t\t\t\t\t\t\tWireless Send Timeline\n";
    printTimeline(wireless_send_ch);

    // For each task selected on Wireless Cloud Channel
    std::cout << "\t\t\t\t\t\t\t\tCloud Timeline\n";
    printTimeline(cloud);

    // For each task selected on Wireless Receive Channel
    std::cout << "\t\t\t\t\t\t\t\tWireless Receive Timeline\n";
    printTimeline(wireless_recv_ch);

    std::cout << "=====================================================================================================================================================================\n\n";
}

// Sort by second element of pairs in a vector
bool sortSecond(const std::pair<int,float> &a, const std::pair<int,float> &b){ 
    return (a.second < b.second); 
} 

// Find max priority of successors
float max_ele(Graph graph, int i){
    // Local varaibles
    float max = 0;
    int count = 0;
    Characteristics characteristics;

    // Compare successors
    characteristics = (*graph).array[i].head;
    while(characteristics != NULL){
        if(count == 0){
            count++;
            max = (*graph).array[(*characteristics).dst].priority;
        }
        else{
            if((*graph).array[(*characteristics).dst].priority > max){
                max = (*graph).array[(*characteristics).dst].priority;
            }
        }
        characteristics = (*characteristics).next;
    }

    return max;
}

/*      Initial Scheduling Algorithm    */
// Determines the subset of tasks initially assigned to the cloud for execution
int primary_assign(Graph graph, int i){
    // Local Variables 
    float T_l, T_re, T_c, T_s, T_r;
    Characteristics characteristics;

    // Determine minimum execution time locally
    T_l = (*graph).array[i].core1;
    if((*graph).array[i].core2 < T_l){
        T_l = (*graph).array[i].core2;
    }
    if((*graph).array[i].core3 < T_l){
        T_l = (*graph).array[i].core3;
    }

    // Determine remove execution time
    T_s = (float) (*graph).array[i].upload_weight / (float) R_s;
    T_r = (float) (*graph).array[i].download_weight / (float) R_r;
    T_c = (float) (*graph).array[i].cloud;
    T_re = T_s + T_r + T_c;
    (*graph).array[i].T_re = T_re;
    std::cout << std::fixed << std::setprecision(1) << i << "\t" << T_s << "\t" << T_c << "\t" << T_r << "\t" << T_re << std::endl;

    // Compare local versus remote execution speeds
    if(T_re < T_l){

        // Return 1 for remote execution
        (*graph).array[i].cloud_task = 1;
        return 1;
    }
    else{

        // Return 2 for local execution
        return 0;
    }
}

// Caculate the priority of each task, similar to HEFT algorithm
float task_priority(Graph graph, int i, int cloud_task){
    // Local Variables
    float weight, priority;

    // If cloud task, weight = T_re
    if(cloud_task == 1){
        weight = ((float) (*graph).array[i].upload_weight / (float) R_s) + ((float) (*graph).array[i].download_weight / (float) R_r) + ((float) (*graph).array[i].cloud);
    }

    // Else if not a cloud task, weight = average of local execution
    else{
        weight = (((float) (*graph).array[i].core1) + ((float) (*graph).array[i].core2) + ((float) (*graph).array[i].core3)) / (float) 3;
    }

    // Return weight for priority calculations
    return weight;
}

// Select tasks and schedule in descending order of priorities
Rect selection(Graph graph){
    // Local Variables
    Predeccessors predeccessors;
    //Rect rect;
    int i, index, final_i, task, min, j;
    float max, t_1_availability = 0, t_2_availability = 0, t_3_availability = 0, t_cloud_availability = 0, T_s, T_c, T_r, send_start_time, min_start_time = 0;
    float exec_time[4];

    std::vector<int>::iterator it;
    std::vector<int> queue;
    std::vector<std::pair<int, float>> priority_queue;
    std::vector<std::vector<float>> core1;
    std::vector<std::vector<float>> core2;
    std::vector<std::vector<float>> core3;
    std::vector<std::vector<float>> wireless_send_ch;
    std::vector<std::vector<float>> wireless_recv_ch;
    std::vector<std::vector<float>> cloud;

    // Sort priority array by second element such that most expensive task is first
    // Initialize queue
    for(i = 1; i < (*graph).length; i++){
        queue.push_back(i);
    }
    while(queue.size() != 0){
        max = 0;
        for(i = 1; i < (*graph).length; i++){
            // if priority is max and i exists within queue, return new max and index to be removed from queue
            if((*graph).array[i].priority > max && (std::find(queue.begin(), queue.end(), i) != queue.end())){
                max = (*graph).array[i].priority;
                it = std::find(queue.begin(), queue.end(), i);
                index = std::distance(queue.begin(), it);
                final_i = i;
            }
        }
        // Pop value from queue and add value to priority queue
        queue.erase(queue.begin() + index,queue.begin() + index + 1);
        priority_queue.push_back(std::make_pair(final_i, max));
    }

    if(DEBUG == true){
        std::cout << "\t\t\tIntermediate Priority Task List" << std::endl;
        std::cout << "Task" << "\tCloud Task" << "\tPriority" << "\tT_l_1" << "\tT_l_2" << "\tT_l_3" << "\tT_re" << "\tPredeccessors\n";
        for(auto i : priority_queue){
            index = i.first;
            std::cout << index << "\t" << (*graph).array[index].cloud_task << "\t\t";
            std::cout << (*graph).array[index].priority << "\t\t";
            std::cout << (*graph).array[index].core1 << "\t" << (*graph).array[index].core2 << "\t";
            std::cout << (*graph).array[index].core3 << "\t" << (*graph).array[index].T_re << "\t";
            predeccessors = (*graph).array[index].otherhead;
            while(predeccessors != NULL){
                std::cout << (*predeccessors).src << " ";
                predeccessors = (*predeccessors).nextSucc;
            }
            std::cout << std::endl;
        }

    }

    // Scheduler
    for(auto i : priority_queue){
        min_start_time = 0;
        task = i.first;

        // Find max predeccessor 
        predeccessors = (*graph).array[task].otherhead;
        while(predeccessors != NULL){
            // Search for max time of predeccessors
            // Search core1
            for(auto j : core1){
                if((*predeccessors).src == j.at(0)){
                    if(min_start_time < j.at(1) + j.at(2)){
                        min_start_time = j.at(1) + j.at(2);
                    }
                }
            }
            // Search core2
            for(auto j : core2){
                if((*predeccessors).src == j.at(0)){
                    if(min_start_time < j.at(1) + j.at(2)){
                        min_start_time = j.at(1) + j.at(2);
                    }
                }
            }
            // Search core3
            for(auto j : core3){
                if((*predeccessors).src == j.at(0)){
                    if(min_start_time < j.at(1) + j.at(2)){
                        min_start_time = j.at(1) + j.at(2);
                    }
                }
            }
            // Search cloud
            for(auto j : wireless_recv_ch){
                if((*predeccessors).src == j.at(0)){
                    if(min_start_time < j.at(1) + j.at(2)){
                        min_start_time = j.at(1) + j.at(2);
                    }
                }
            }
            predeccessors = (*predeccessors).nextSucc;
        }

        T_s = (float) (*graph).array[task].upload_weight / (float) R_s;
        T_r = (float) (*graph).array[task].download_weight / (float) R_r;
        T_c = (float) (*graph).array[task].cloud;
        send_start_time = 0;
        
        // Determine if task is a cloud task
        // Cloud task
        if((*graph).array[task].cloud_task == 1){

            // Need to check cloud availability as well as min start time
            // go by whichever is larger
            t_cloud_availability = (t_cloud_availability>min_start_time) ? t_cloud_availability : min_start_time ;

            // Calculate execution time
            if(t_cloud_availability == 0){
                t_cloud_availability = T_s;
            }
            else{
                send_start_time = t_cloud_availability - T_s;
            }

            // t_cloud_availability may need to include T_s. depends on if a predecessor is in receiving
            if (send_start_time < min_start_time){
                send_start_time = min_start_time;
                t_cloud_availability += T_s;
            }

            wireless_send_ch.push_back(std::vector<float>{(float) task, (float) send_start_time, (float) T_s});
            cloud.push_back(std::vector<float>{(float) task, t_cloud_availability, (float) T_c});

            // add weight to start time for next task
            t_cloud_availability += T_c;
            wireless_recv_ch.push_back(std::vector<float>{(float) task, t_cloud_availability,(float) T_r});
        }
        // Not a cloud task
        else{
            // Create execution time array
            exec_time[0] = ((t_1_availability > min_start_time) ? t_1_availability : min_start_time) + (*graph).array[task].core1;
            exec_time[1] = ((t_2_availability > min_start_time) ? t_2_availability : min_start_time) + (*graph).array[task].core2;
            exec_time[2] = ((t_3_availability > min_start_time) ? t_3_availability : min_start_time) + (*graph).array[task].core3;
            exec_time[3] = ((t_cloud_availability > min_start_time) ? t_cloud_availability : min_start_time) + (*graph).array[task].cloud;

            // Compare execution times to find min
            min = 0;
            for(j = 1; j < 4; j++){
                if(exec_time[j] < exec_time[min]){
                    min = j;
                }
            }

            // Assign to optimal execution medium
            switch(min){
                case 0:
                    // append to core1 vector
                    core1.push_back(std::vector<float>{(float) task, exec_time[0] - (*graph).array[task].core1, (float) (*graph).array[task].core1});
                    // add weight to start time for next task
                    t_1_availability = min_start_time + (*graph).array[task].core1;
                    break;
                case 1:
                    // append to core2 vector
                    core2.push_back(std::vector<float>{(float) task, exec_time[1] - (*graph).array[task].core2, (float) (*graph).array[task].core2});
                    // add weight to start time for next task
                    t_2_availability = min_start_time + (*graph).array[task].core2;
                    break;
                case 2:
                    // append to core3 vector
                    core3.push_back(std::vector<float>{(float) task, exec_time[2] - (*graph).array[task].core3, (float) (*graph).array[task].core3});
                    // add weight to start time for next task
                    t_3_availability = min_start_time + (*graph).array[task].core3;
                    break;
                case 3:
                    // Need to check cloud availability as well as min start time
                    // go by whichever is larger
                    t_cloud_availability = (t_cloud_availability>min_start_time) ? t_cloud_availability : min_start_time ;

                    // Calculate execution time
                    if(t_cloud_availability == 0){
                        t_cloud_availability = T_s;
                    }
                    else{
                        send_start_time = t_cloud_availability - T_s;
                    }
                    
                    if (send_start_time < min_start_time){
                        send_start_time = min_start_time;
                        t_cloud_availability += T_s;
                    }

                    wireless_send_ch.push_back(std::vector<float>{(float) task, (float) send_start_time, (float) T_s});
                    cloud.push_back(std::vector<float>{(float) task, t_cloud_availability, (float) T_c});

                    // add weight to start time for next task
                    t_cloud_availability += T_c;
                    wireless_recv_ch.push_back(std::vector<float>{(float) task, t_cloud_availability,(float) T_r});

                    break;
            }
        }
    }
    std::cout << "\n\tFigure 3: Task scheduling result by the initial scheduling algorithm\n";
    fig3Print(core1, core2, core3, wireless_send_ch, cloud, wireless_recv_ch);

    // Energy Consumption and Application Completion Time
    std::cout << "\nEnergy Consumption and Application Completion Time\n";
    std::cout << "---------------------------------------------------\n";
    float energy_1 = 0, energy_2 = 0, energy_3 = 0, energy_send = 0, energy_total = 0, completion_time = 0;

    for(auto i : core1){
        energy_1 += i.at(2) * P_1;
        if(i.at(2) + i.at(1) > completion_time){
            completion_time = i.at(2) + i.at(1);
        }
    }
    for(auto i : core2){
        energy_2 += i.at(2) * P_2;
        if(i.at(2) + i.at(1) > completion_time){
            completion_time = i.at(2) + i.at(1);
        }
    }
    for(auto i : core3){
        energy_3 += i.at(2) * P_3;
        if(i.at(2) + i.at(1) > completion_time){
            completion_time = i.at(2) + i.at(1);
        }
    }
    for(auto i : wireless_send_ch){
        energy_send += i.at(2) * P_s;
        if(i.at(2) + i.at(1) > completion_time){
            completion_time = i.at(2) + i.at(1);
        }
    }
    for(auto i : wireless_recv_ch){
        energy_send += i.at(2) * P_s;
        if(i.at(2) + i.at(1) > completion_time){
            completion_time = i.at(2) + i.at(1);
        }
    }

    energy_total = energy_1 + energy_2 + energy_3 + energy_send;

    std::cout << "Power of core 1:\t" << P_1 << std::endl;
    std::cout << "Power of core 2:\t" << P_2 << std::endl;
    std::cout << "Power of core 3:\t" << P_3 << std::endl;
    std::cout << "Power to send task:\t" << P_s << std::endl << std::endl;
    std::cout << "Total energy for initial scheduling algorithm:\t\t" << energy_total << std::endl;
    std::cout << std::setprecision(1) << "Completion Time for initial scheduling algorithm:\t" << completion_time << std::endl << std::endl;

    return Rect(core1, core2, core3, wireless_send_ch, cloud, wireless_recv_ch, completion_time, energy_total,core1, core2, core3, wireless_send_ch, cloud, wireless_recv_ch, completion_time, energy_total);
}

// Generates min-delay scheduling w/o considering energy consumption
Rect stepOne(Graph graph, int length){
    // Local Variables 
    int i, j, weight_i, index, cloud_task, size;
    float weight;
    Characteristics characteristics;
    std::vector<float> succ;
    std::vector<std::pair<int, float>> weight_array;

    // Initialize vector succ to hold priorities of successors
    for(j = 0; j < length; j++){
        succ.push_back(0);
    }

    // Part A: Primary assignment
    std::cout << "\tExecution Time\n";
    std::cout << "Task" << "\tT_s" << "\tT_c" << "\tT_r" << "\tT_re" << std::endl;
    for(i = 1; i < (*graph).length; i++){
        // cloud_task = 1 for remote execution; assignment = 0 for local execution
        cloud_task = primary_assign(graph, i);

        // Part B: Task prioritizing
        weight = task_priority(graph, i, cloud_task);
        weight_array.push_back(std::make_pair(i, weight));
    }
    std::cout << "==============================================\n";
    std::cout << std::endl;

    // Define priority for the last element
    size = weight_array.size();
    (*graph).array[size].priority = weight_array[size - 1].second;
    
    // Traverse task graph and define priority array recursively
    // Begins on second to last element
    for(i = (*graph).length - 2; i > 0; i--){
        (*graph).array[i].priority = weight_array[i - 1].second + max_ele(graph, i);
    }

    // Part C: Execution unit selection 
    return selection(graph);
}

// Relocate tasks to ensure sucessors are executed in order
Rect relocate(Graph graph, Rect rect, int task, float start_time){
    // Local variables
    int environment;
    std::vector<float> task_manager;

    // Find the environment that the task runs in
    for(auto i : rect.core1){
        if(i.at(0) == task){
            environment = 1;
        }
    }
    for(auto i : rect.core2){
        if(i.at(0) == task){
            environment = 2;
        }
    }
    for(auto i : rect.core3){
        if(i.at(0) == task){
            environment = 3;
        }
    }
    for(auto i : rect.cloud){
        if(i.at(0) == task){
            environment = 4;
        }
    }

    // Update start time for task based upon previously scheduled tasks
    if(environment == 1){
        // Erase tasks scheduled after
        for(int i = 0; i < rect.updated_core1.size(); i++){
            if(rect.updated_core1.at(i).at(1) >= start_time){
                rect.updated_core1.erase(rect.updated_core1.begin() + i);
            }
        }
        // Reassign tasks
        for(int i = 0; i < rect.core1.size(); i++){
            if(rect.core1.at(i).at(1) >= start_time){
                task_manager.push_back(rect.core1.at(i).at(0));
                task_manager.push_back(start_time);
                task_manager.push_back(rect.core1.at(i).at(2));
                rect.updated_core1.push_back(task_manager);
                start_time += task_manager.at(2);
                task_manager.clear();
            }
        }
    }

    if(environment == 2){
        // Erase tasks scheduled after
        for(int i = 0; i < rect.updated_core2.size(); i++){
            if(rect.updated_core2.at(i).at(1) >= start_time){
                rect.updated_core2.erase(rect.updated_core2.begin() + i);
            }
        }
        // Reassign tasks
        for(int i = 0; i < rect.core2.size(); i++){
            if(rect.core2.at(i).at(1) >= start_time){
                task_manager.push_back(rect.core2.at(i).at(0));
                task_manager.push_back(start_time);
                task_manager.push_back(rect.core2.at(i).at(2));
                rect.updated_core2.push_back(task_manager);
                start_time += task_manager.at(2);
                task_manager.clear();
            }
        }
    }

    if(environment == 3){
        // Erase tasks scheduled after
        for(int i = 0; i < rect.updated_core3.size(); i++){
            if(rect.updated_core3.at(i).at(1) >= start_time){
                rect.updated_core3.erase(rect.updated_core3.begin() + i);
            }
        }
        // Reassign tasks
        for(int i = 0; i < rect.core3.size(); i++){
            if(rect.core3.at(i).at(1) >= start_time){
                task_manager.push_back(rect.core3.at(i).at(0));
                task_manager.push_back(start_time);
                task_manager.push_back(rect.core3.at(i).at(2));
                rect.updated_core3.push_back(task_manager);
                start_time += task_manager.at(2);
                task_manager.clear();
            }
        }
    }

    if(environment == 4){
        // Erase tasks scheduled after
        for(int i = 0; i < rect.updated_wireless_send_ch.size(); i++){
            if(rect.updated_wireless_send_ch.at(i).at(1) >= start_time){
                rect.updated_wireless_send_ch.erase(rect.updated_wireless_send_ch.begin() + i);
                rect.updated_cloud.erase(rect.updated_cloud.begin() + i);
                rect.updated_wireless_recv_ch.erase(rect.updated_wireless_recv_ch.begin() + i);
            }
        }
        // Reassign tasks
        for(int i = 0; i < rect.wireless_send_ch.size(); i++){
            if(rect.wireless_send_ch.at(i).at(1) >= start_time){
                // Update Send Channel
                task_manager.push_back(rect.wireless_send_ch.at(i).at(0));
                task_manager.push_back(start_time);
                task_manager.push_back(rect.wireless_send_ch.at(i).at(2));
                rect.updated_wireless_send_ch.push_back(task_manager);
                start_time += task_manager.at(2);
                task_manager.clear();

                // Update Cloud
                task_manager.push_back(rect.cloud.at(i).at(0));
                task_manager.push_back(start_time);
                task_manager.push_back(rect.cloud.at(i).at(2));
                rect.updated_cloud.push_back(task_manager);
                start_time += task_manager.at(2);
                task_manager.clear();

                // Update Recv Channel
                task_manager.push_back(rect.wireless_recv_ch.at(i).at(0));
                task_manager.push_back(start_time);
                task_manager.push_back(rect.wireless_recv_ch.at(i).at(2));
                rect.wireless_recv_ch.push_back(task_manager);
                start_time += task_manager.at(2);
                task_manager.clear();

            }
        }
    }

    // Check successors of target task
    Characteristics successors;
    successors = (*graph).array[task].head;
    while(successors != NULL){
        // Recursively call relocate
        rect = relocate(graph, rect, (*successors).dst, start_time);
        successors = (*successors).next;
    }

    return rect;
}

// Kernel Loop
// Determines new schedule and calculates corresponding energy consumption + application completion time
Rect kernel(Graph graph, Rect rect, float task, int core, int original_core){
    // Local variables
    int i, j;
    float old_completion_time, old_energy_total;
    float energy_1 = 0, energy_2 = 0, energy_3 = 0, energy_send = 0, energy_total = 0, completion_time = 0;
    std::vector<std::vector<float>> core1 = rect.core1;
    std::vector<std::vector<float>> core2 = rect.core2;
    std::vector<std::vector<float>> core3 = rect.core3;
    std::vector<std::vector<float>> wireless_send_ch = rect.wireless_send_ch;
    std::vector<std::vector<float>> wireless_recv_ch = rect.wireless_recv_ch;
    std::vector<std::vector<float>> cloud = rect.cloud;

    std::vector<std::vector<float>> new_core1 = rect.core1;
    std::vector<std::vector<float>> new_core2 = rect.core2;
    std::vector<std::vector<float>> new_core3 = rect.core3;
    std::vector<std::vector<float>> new_wireless_send_ch = rect.wireless_send_ch;
    std::vector<std::vector<float>> new_wireless_recv_ch = rect.wireless_recv_ch;
    std::vector<std::vector<float>> new_cloud = rect.cloud;

    std::vector<float> target_task;

    // Remove the target task from the original core 
    // Core 1
    if(original_core == 1){
        // Find the index of the task
        for(j = 0; j < core1.size(); j++){
            if(core1.at(j).at(0) == task){
                // define target task
                target_task = core1.at(j);
                //  erase the task
                new_core1.erase(new_core1.begin()+j);
            }
        }
    }
    // Core 2
    else if(original_core == 2){
        // Find the index of the task
        for(j = 0; j < core2.size(); j++){
            if(core2.at(j).at(0) == task){
                // define target task
                target_task = core2.at(j);
                //  erase the task
                new_core2.erase(new_core2.begin()+j);
            }
        }
    }
    // Core 3
    else if(original_core == 3){
        // Find the index of the task
        for(j = 0; j < core3.size(); j++){
            if(core3.at(j).at(0) == task){
                // define target task
                target_task = core3.at(j);
                //  erase the task
                new_core3.erase(new_core3.begin()+j);
            }
        }
    }

    float buffer, time;
    int flag, t;
    std::vector<std::vector<float>> old_task;
    // Place target task onto new destination core
    // Core 1
    if(core == 1){
        // Define buffer, flag, and time at zero
        buffer = 0;
        flag = 0;
        time = 0;
        // For each task at the core
        for(i = 0; i < core1.size(); i++){
            // If target task has an open space on new core, place it
            if(flag == 0 && core1.at(i).at(1) >= target_task.at(1) && buffer >= 0){
                buffer = 0;
                flag = 1;
                new_core1.at(i) = target_task;
                old_task.push_back(core1.at(i));
                target_task.at(1) = new_core1.at(i).at(1);
            }
            // If target task has already been placed, remove the next tasks and add them to an array
            else if(flag == 1){
                old_task.push_back(core1.at(i));
                new_core1.erase(new_core1.begin()+i);
            }
            // If target task cannot be placed, incremented buffer to ensure we place it after the previous task executing
            else if(flag == 0){
                buffer = target_task.at(1) - (core1.at(i).at(1) + core1.at(i).at(2));
            }
        }

        // Increment time to the end of target task run time
        time += target_task.at(1);
        time += target_task.at(2);
        // Add each task after the target task back to the core at new start time
        for(t = 0; t < old_task.size(); t++){
            old_task.at(t).at(1) = time;
            new_core1.push_back(old_task.at(t));
            time += old_task.at(t).at(2);
        }
        // Check successors of target task
        Characteristics successors;
        successors = (*graph).array[(int) task].head;
        while(successors != NULL){
            float start_time = (target_task.at(1) + target_task.at(2));
            rect = relocate(graph, rect, (*successors).dst, start_time);
            successors = (*successors).next;
        }
        std::cout << std::endl;
    }

    // Core 2
    if(core == 2){
        // Define buffer, flag, and time at zero
        buffer = 0;
        flag = 0;
        time = 0;
        // For each task at the core
        for(i = 0; i < core2.size(); i++){
            // If target task has an open space on new core, place it
            if(flag == 0 && core2.at(i).at(1) >= target_task.at(1) && buffer >= 0){
                buffer = 0;
                flag = 1;
                new_core2.at(i) = target_task;
                old_task.push_back(core2.at(i));
                target_task.at(1) = new_core2.at(i).at(1);
            }
            // If target task has already been placed, remove the next tasks and add them to an array
            else if(flag == 1){
                old_task.push_back(core2.at(i));
                new_core2.erase(new_core2.begin()+i);
            }
            // If target task cannot be placed, incremented buffer to ensure we place it after the previous task executing
            else if(flag == 0){
                buffer = target_task.at(1) - (core2.at(i).at(1) + core2.at(i).at(2));
            }
        }

        // Increment time to the end of target task run time
        time += target_task.at(1);
        time += target_task.at(2);
        // Add each task after the target task back to the core at new start time
        for(t = 0; t < old_task.size(); t++){
            old_task.at(t).at(1) = time;
            new_core2.push_back(old_task.at(t));
            time += old_task.at(t).at(2);
        }
        // Check successors of target task
        Characteristics successors;
        successors = (*graph).array[(int) task].head;
        while(successors != NULL){
            float start_time = (target_task.at(1) + target_task.at(2));
            rect = relocate(graph, rect, (*successors).dst, start_time);
            successors = (*successors).next;
        }
    }

    // Core 3
    if(core == 3){
        // Define buffer, flag, and time at zero
        buffer = 0;
        flag = 0;
        time = 0;
        // For each task at the core
        for(i = 0; i < core3.size(); i++){
            // If target task has an open space on new core, place it
            if(flag == 0 && core3.at(i).at(1) >= target_task.at(1) && buffer >= 0){
                buffer = 0;
                flag = 1;
                new_core3.at(i) = target_task;
                old_task.push_back(core3.at(i));
                target_task.at(1) = new_core3.at(i).at(1);
            }
            // If target task has already been placed, remove the next tasks and add them to an array
            else if(flag == 1){
                old_task.push_back(core3.at(i));
                new_core3.erase(new_core3.begin()+i);
            }
            // If target task cannot be placed, incremented buffer to ensure we place it after the previous task executing
            else if(flag == 0){
                buffer = target_task.at(1) - (core3.at(i).at(1) + core3.at(i).at(2));
            }
        }

        // Increment time to the end of target task run time
        time += target_task.at(1);
        time += target_task.at(2);
        // Add each task after the target task back to the core at new start time
        for(t = 0; t < old_task.size(); t++){
            old_task.at(t).at(1) = time;
            new_core3.push_back(old_task.at(t));
            time += old_task.at(t).at(2);
        }
        // Check successors of target task
        Characteristics successors;
        successors = (*graph).array[(int) task].head;
        while(successors != NULL){
            float start_time = (target_task.at(1) + target_task.at(2));
            rect = relocate(graph, rect, (*successors).dst, start_time);
            successors = (*successors).next;
        }
    }


    if(DEBUG == true){
        std::cout << "TASK: " << task << "\n";
        std::cout << "Core 1: " << task << "\n";
        printTimeline(core1);
        std::cout << "Core 2: " << task << "\n";
        printTimeline(core2);
        std::cout << "Core 3: " << task << "\n";
        printTimeline(core3);
        std::cout << "Wireless Send Ch: " << task << "\n";
        printTimeline(wireless_send_ch);
        std::cout << "Cloud: " << task << "\n";
        printTimeline(cloud);
        std::cout << "Wireless Recv Ch: " << task << "\n";
        printTimeline(wireless_recv_ch);
        std::cout << "New Core 1: " << task << "\n";
        printTimeline(new_core1);
        std::cout << "New Core 2: " << task << "\n";
        printTimeline(new_core2);
        std::cout << "New Core 3: " << task << "\n";
        printTimeline(new_core3);
        std::cout << "New Wireless Send Ch: " << task << "\n";
        printTimeline(new_wireless_send_ch);
        std::cout << "New Cloud 1: " << task << "\n";
        printTimeline(new_cloud);
        std::cout << "New Wireless Recv Ch: " << task << "\n";
        printTimeline(new_wireless_recv_ch);
    }

    // Energy Consumption and Application Completion Time
    completion_time = 0;
    for(auto i : rect.updated_core1){
        energy_1 += i.at(2) * P_1;
        if(i.at(2) + i.at(1) > completion_time){
            completion_time = i.at(2) + i.at(1);
        }
    }
    for(auto i : rect.updated_core2){
        energy_2 += i.at(2) * P_2;
        if(i.at(2) + i.at(1) > completion_time){
            completion_time = i.at(2) + i.at(1);
        }
    }
    for(auto i : rect.updated_core3){
        energy_3 += i.at(2) * P_3;
        if(i.at(2) + i.at(1) > completion_time){
            completion_time = i.at(2) + i.at(1);
        }
    }
    for(auto i : rect.updated_wireless_send_ch){
        energy_send += i.at(2) * P_s;
        if(i.at(2) + i.at(1) > completion_time){
            completion_time = i.at(2) + i.at(1);
        }
    }
    for(auto i : rect.updated_wireless_recv_ch){
        energy_send += i.at(2) * P_s;
        if(i.at(2) + i.at(1) > completion_time){
            completion_time = i.at(2) + i.at(1);
        }
    }

    energy_total = energy_1 + energy_2 + energy_3 + energy_send;

    return Rect(core1, core2, core3, wireless_send_ch, cloud, wireless_recv_ch, old_completion_time, old_energy_total, new_core1, new_core2, new_core3, new_wireless_send_ch, new_cloud, new_wireless_recv_ch, completion_time, energy_total);
}

//
void outerloop(Graph graph, Rect rect){
    // Local variables
    int i, core;
    std::vector<Rect> manager;

    // Pick a task from the local cores and assign new environment for computing task
    for(auto i : rect.core1){
        core = 2;
        manager.push_back(kernel(graph, rect, (float) i.at(0), core, 1));

        core = 3;
        manager.push_back(kernel(graph, rect, (float) i.at(0), core, 1));

        core = 4; // refers to cloud
        manager.push_back(kernel(graph, rect, (float) i.at(0), core, 1));
    }
    for(auto i : rect.core2){
        core = 1;
        manager.push_back(kernel(graph, rect, (float) i.at(0), core, 2));

        core = 3;
        manager.push_back(kernel(graph, rect, (float) i.at(0), core, 2));
        
        core = 4; // refers to cloud
        manager.push_back(kernel(graph, rect, (float) i.at(0), core, 2));
    }
    for(auto i : rect.core3){
        core = 2;
        manager.push_back(kernel(graph, rect, (float) i.at(0), core, 3));

        core = 1;
        manager.push_back(kernel(graph, rect, (float) i.at(0), core, 3));
        
        core = 4; // refers to cloud
        manager.push_back(kernel(graph, rect, (float) i.at(0), core, 3));
    }

    // Find most efficient scheduling algorithm
    std::pair<int, float> min;
    min = std::make_pair(INT_MAX, INT_MAX);
    int index = 0;

    for(auto i : manager){
        float energy_1 = 0, energy_2 = 0, energy_3 = 0, energy_send = 0, energy_total = 0, completion_time = 0;
        for(auto j : i.updated_core1){
            energy_1 += j.at(2) * P_1;
            if(j.at(2) + j.at(1) > completion_time){
                completion_time = j.at(2) + j.at(1);
            }
        }
        for(auto j : i.updated_core2){
            energy_2 += j.at(2) * P_2;
            if(j.at(2) + j.at(1) > completion_time){
                completion_time = j.at(2) + j.at(1);
            }
        }
        for(auto j : i.updated_core3){
            energy_3 += j.at(2) * P_3;
            if(j.at(2) + j.at(1) > completion_time){
                completion_time = j.at(2) + j.at(1);
            }
        }
        for(auto j : i.updated_wireless_send_ch){
            energy_send += j.at(2) * P_s;
            if(j.at(2) + j.at(1) > completion_time){
                completion_time = j.at(2) + j.at(1);
            }
        }
        for(auto j : i.updated_wireless_recv_ch){
            energy_send += j.at(2) * P_s;
            if(j.at(2) + j.at(1) > completion_time){
                completion_time = j.at(2) + j.at(1);
            }
        }

        energy_total = energy_1 + energy_2 + energy_3 + energy_send;

        i.updated_total_energy = energy_total;
        i.updated_total_time = completion_time;

        if(i.updated_total_time <= T_MAX){
            if(i.updated_total_energy < min.second){
                min.first = index;
                min.second = i.updated_total_energy;
            }   
        }
        index++;
    }

    // Print figure 4
    std::cout << "\n\tFigure 4: Task scheduling result after task migration\n";
    fig3Print(manager.at(min.first).updated_core1, manager.at(min.first).updated_core2, manager.at(min.first).updated_core3, manager.at(min.first).updated_wireless_send_ch, manager.at(min.first).updated_cloud, manager.at(min.first).updated_wireless_recv_ch);

    // Energy Consumption and Application Completion Time
    std::cout << "\nEnergy Consumption and Application Completion Time\n";
    std::cout << "---------------------------------------------------\n";
    std::cout << "Power of core 1:\t" << P_1 << std::endl;
    std::cout << "Power of core 2:\t" << P_2 << std::endl;
    std::cout << "Power of core 3:\t" << P_3 << std::endl;
    std::cout << "Power to send task:\t" << P_s << std::endl << std::endl;
    std::cout << std::setprecision(1) << "Total energy for task migration algorithm:\t\t" << min.second << std::endl;
    std::cout << std::setprecision(1) << "Completion Time for task migration algorithm:\t" << manager.at(min.first).updated_total_time << std::endl << std::endl;

    return;
}

/*      Task Migration Algorithm        */
// Minimize energy consumption under the application completion time constraint
void stepTwo(Graph graph, Rect rect){
    // Local Variables 
    int i;

    // Outer Loop
    // Determines the target tasks to migrate from one local core to another, or from one local core to the cloud
    // Note: this will never check cloud to local core because the energy will generally increase with this
    outerloop(graph, rect);

    return;
}

/*      Main function                   */
int main(int argc, char **argv){
    // Local Variables 
    Graph graph;
    // Rect rect;
    Characteristics characteristics;
    int i, length;

    if(EXAMPLE == 1){
        length = 11;

        // Initialize graph
        graph = createGraph(length);
        // Add weight to nodes with the following parameters:
            // graph, src, upload weight, download weight
            // core1 weight, core2 weight, core3 weight, cloud_weight
        addWeight(graph, 1, 5, 5, 9, 7, 5, 1);
        addWeight(graph, 2, 4, 3, 5, 6, 8, 2);
        addWeight(graph, 3, 4, 4, 6, 4, 5, 3);
        addWeight(graph, 4, 3, 3, 7, 5, 3, 4);
        addWeight(graph, 5, 3, 4, 2, 5, 4, 5);
        addWeight(graph, 6, 2, 3, 6, 4, 7, 4);
        addWeight(graph, 7, 3, 2, 8, 5, 3, 3);
        addWeight(graph, 8, 2, 2, 2, 4, 6, 2);
        addWeight(graph, 9, 3, 4, 3, 2, 5, 1);
        addWeight(graph, 10, 4, 5, 7, 4, 2, 1);

        // Add connections to graph
        addPoint(graph, 1, 2);
        addPoint(graph, 1, 3);
        addPoint(graph, 1, 4);
        addPoint(graph, 1, 5);
        addPoint(graph, 1, 6);
        addPoint(graph, 2, 8);
        addPoint(graph, 2, 9);
        addPoint(graph, 3, 7);
        addPoint(graph, 4, 8);
        addPoint(graph, 4, 9);
        addPoint(graph, 5, 9);
        addPoint(graph, 6, 8);
        addPoint(graph, 7, 10);
        addPoint(graph, 8, 10);
        addPoint(graph, 9, 10);
    }

    else if(EXAMPLE == 2){
        length = 10;

        // Initialize graph
        graph = createGraph(length);
        // Add weight to nodes with the following parameters:
            // graph, src, upload weight, download weight
            // core1 weight, core2 weight, core3 weight, cloud_weight
        addWeight(graph, 1, 3, 3, 3, 3, 3, 3);
        addWeight(graph, 2, 3, 4, 5, 4, 3, 2);
        addWeight(graph, 3, 2, 3, 4, 5, 4, 3);
        addWeight(graph, 4, 2, 2, 2, 2, 2, 2);
        addWeight(graph, 5, 3, 3, 3, 3, 3, 3);
        addWeight(graph, 6, 3, 4, 5, 4, 3, 2);
        addWeight(graph, 7, 2, 3, 4, 5, 4, 3);
        addWeight(graph, 8, 2, 2, 2, 2, 2, 2);
        addWeight(graph, 9, 3, 3, 3, 3, 3, 3);

        // Add connections to graph
        addPoint(graph, 1, 2);
        addPoint(graph, 1, 3);
        addPoint(graph, 2, 4);
        addPoint(graph, 2, 5);
        addPoint(graph, 2, 6);
        addPoint(graph, 3, 7);
        addPoint(graph, 3, 8);
        addPoint(graph, 4, 9);
        addPoint(graph, 5, 9);
        addPoint(graph, 6, 9);
        addPoint(graph, 7, 9);
        addPoint(graph, 8, 9);
    }

    else if(EXAMPLE == 3){
        length = 11;

        // Initialize graph
        graph = createGraph(length);
        // Add weight to nodes with the following parameters:
            // graph, src, upload weight, download weight
            // core1 weight, core2 weight, core3 weight, cloud_weight
        addWeight(graph, 1, 5, 5, 9, 7, 5, 1);
        addWeight(graph, 2, 4, 3, 5, 6, 8, 2);
        addWeight(graph, 3, 4, 4, 6, 4, 5, 3);
        addWeight(graph, 4, 3, 3, 7, 5, 3, 4);
        addWeight(graph, 5, 3, 4, 2, 5, 4, 5);
        addWeight(graph, 6, 2, 3, 6, 4, 7, 4);
        addWeight(graph, 7, 3, 2, 8, 5, 3, 3);
        addWeight(graph, 8, 2, 2, 2, 4, 6, 2);
        addWeight(graph, 9, 3, 4, 3, 2, 5, 1);
        addWeight(graph, 10, 3, 4, 3, 2, 5, 1);

        // Add connections to graph
        addPoint(graph, 1, 2);
        addPoint(graph, 2, 3);
        addPoint(graph, 2, 4);
        addPoint(graph, 2, 6);
        addPoint(graph, 3, 7);
        addPoint(graph, 3, 8);
        addPoint(graph, 4, 7);
        addPoint(graph, 4, 8);
        addPoint(graph, 4, 5);
        addPoint(graph, 3, 5);
        addPoint(graph, 5, 9);
        addPoint(graph, 6, 9);
        addPoint(graph, 7, 9);
        addPoint(graph, 8, 9);
        addPoint(graph, 9, 10);
    }

    // Print task graph and task table
    initialPrint(graph);

    // Initial scheduling algorithm
    Rect rect = stepOne(graph, length);

    // Task migration algorithm
    stepTwo(graph, rect);

    // Gracefully terminate
    destroy(graph);

    // Return function
    return 0;

}
