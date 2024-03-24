/* Libs */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

/* Defs */
#define MAX_LINE_LENGTH 1024
#define MAX_LEN 32

/* Structs */
typedef struct task
{
    char name[32];
    char description[512];
    int priority;
    int deadline;
    struct task *next_task;
} task;

/* BACK-END Functions */

// system time and date
int system_time()
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    int time = (tm.tm_hour * 100) + tm.tm_min;

    return time;
}

int system_date()
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    int date = (tm.tm_mday) + ((tm.tm_mon + 1) * 100) + ((tm.tm_year + 1900 - 2000) * 10000);

    return date;
}

// input data functions
int num_scan(int *result) //
{
    int num_input = 0;
    fflush(stdin);
    scanf("%d", &num_input);
    if (num_input == 0)
    {
        *result = 0;
        return 0; // go back
    }
    else if (num_input == -1)
    {
        *result = 0;
        return -1; // exit
    }
    else
    {
        *result = num_input;
        return 1; // ok
    }
}

int str_scan(char result[MAX_LEN]) //
{
    char str_input[MAX_LEN] = {};
    char empty_str[MAX_LEN] = {};
    fflush(stdin);
    scanf("%[^\n]", str_input);
    if ((strcmp(str_input, "back") == 0 || (strcmp(str_input, "0") == 0)))
    {
        strcpy(str_input, empty_str);
        return 0; // go back
    }
    else if (strcmp(str_input, "exit") == 0)
    {
        strcpy(str_input, empty_str);
        return -1; // exit
    }
    else
    {
        strcpy(result, str_input);
        return 1; // ok
    }
}
int str32_scan(char result[32])
{
    char str_input[32] = {};
    char empty_str[32] = {};
    fflush(stdin);
    scanf("%[^\n]", str_input);
    if ((strcmp(str_input, "back") == 0 || (strcmp(str_input, "0") == 0)))
    {
        strcpy(str_input, empty_str);
        return 0; // go back
    }
    else if (strcmp(str_input, "exit") == 0)
    {
        strcpy(str_input, empty_str);
        return -1; // exit
    }
    else
    {
        strcpy(result, str_input);
        return 1; // ok
    }
}
int str128_scan(char result[128])
{
    char str_input[128] = {};
    char empty_str[128] = {};
    fflush(stdin);
    scanf("%[^\n]", str_input);
    if ((strcmp(str_input, "back") == 0 || (strcmp(str_input, "0") == 0)))
    {
        strcpy(str_input, empty_str);
        return 0; // go back
    }
    else if (strcmp(str_input, "exit") == 0)
    {
        strcpy(str_input, empty_str);
        return -1; // exit
    }
    else
    {
        strcpy(result, str_input);
        return 1; // ok
    }
}

// add and delete location in Lists.csv file
void add_locList(char board_name[MAX_LEN], char list_name[MAX_LEN], char username[MAX_LEN]) //
{
    char location[128];
    sprintf(location, ".\\dBoardDB\\Users\\%s\\Locations\\Lists.csv", username);
    FILE *fp = fopen(location, "a");
    if (NULL == fp)
    {
        printf("file can't be opened \n");
    }
    fprintf(fp, "%s,%s\n", board_name, list_name);
    fclose(fp);
}

void del_locList(char board_name[MAX_LEN], char list_name[MAX_LEN], char username[MAX_LEN]) //
{
    char location[128];
    sprintf(location, ".\\dBoardDB\\Users\\%s\\Locations\\Lists.csv", username);
    FILE *fp = fopen(location, "r");
    if (NULL == fp)
    {
        printf("file can't be opened \n");
    }

    char tmp_location[128];
    sprintf(tmp_location, ".\\dBoardDB\\Users\\%s\\Locations\\tmpLists.csv", username);
    FILE *temp = fopen(tmp_location, "w");
    if (NULL == temp)
    {
        printf("file can't be opened \n");
    }

    char delete_board_folder_name[MAX_LEN + 2];
    sprintf(delete_board_folder_name, "%s,%s\n", board_name, list_name);
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, fp))
    {
        if (strcmp(line, delete_board_folder_name) != 0)
        {
            fputs(line, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove(location);
    rename(tmp_location, location);
}

void delete_boardname_lists(char deleated_board_name[MAX_LEN], char username[MAX_LEN]) //
{
    char line_board_name[MAX_LEN] = {};
    char line_list_name[MAX_LEN] = {};
    char location[128];
    sprintf(location, ".\\dBoardDB\\Users\\%s\\Locations\\Lists.csv", username);
    FILE *fp = fopen(location, "r");
    if (NULL == fp)
    {
        printf("file can't be opened \n");
    }

    char tmp_location[128];
    sprintf(tmp_location, ".\\dBoardDB\\Users\\%s\\Locations\\tmpLists.csv", username);
    FILE *temp = fopen(tmp_location, "w");
    if (NULL == temp)
    {
        printf("file can't be opened \n");
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, fp))
    {
        sscanf(line, "%[^,],%s\n", line_board_name, line_list_name);
        if (strcmp(line_board_name, deleated_board_name) != 0)
        {
            fputs(line, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove(location);
    rename(tmp_location, location);
}

// create and delete list file
void create_list_file(char board_name[MAX_LEN], char list_name[MAX_LEN], char username[MAX_LEN]) //
{
    char location[128];
    sprintf(location, ".\\dBoardDB\\Users\\%s\\Boards\\%s\\%s.csv", username, board_name, list_name);
    FILE *fp = fopen(location, "w");
    if (NULL == fp)
    {
        printf("file can't be opened \n");
    }
    fprintf(fp, "Name,Description,0,000000\n");
    fclose(fp);
    // SHOULD <add_locList(board_name, list_name, username);> AFTER USEING THIS FUNCTION
}

void delete_list_file(char board_name[MAX_LEN], char list_name[MAX_LEN], char username[MAX_LEN]) //
{
    char location[128];
    sprintf(location, ".\\dBoardDB\\Users\\%s\\Boards\\%s\\%s.csv", username, board_name, list_name);
    remove(location);
    // SHOULD <del_locList(board_name, list_name, username);> AFTER USEING THIS FUNCTION
}

// add and delete location to Boards.csv file
void add_locBoard(char board_name[MAX_LEN], char username[MAX_LEN]) //
{
    char location[128];
    sprintf(location, ".\\dBoardDB\\Users\\%s\\Locations\\Boards.csv", username);
    FILE *fp = fopen(location, "a");
    if (NULL == fp)
    {
        printf("file can't be opened \n");
    }
    fprintf(fp, "%s\n", board_name);
    fclose(fp);
}

void del_locBoard(char board_name[MAX_LEN], char username[MAX_LEN]) //
{
    char location[128];
    sprintf(location, ".\\dBoardDB\\Users\\%s\\Locations\\Boards.csv", username);
    FILE *fp = fopen(location, "r");
    if (NULL == fp)
    {
        printf("file can't be opened \n");
    }

    char tmp_location[128];
    sprintf(tmp_location, ".\\dBoardDB\\Users\\%s\\Locations\\tmpBoards.csv", username);
    FILE *temp = fopen(tmp_location, "w");
    if (NULL == temp)
    {
        printf("file can't be opened \n");
    }

    char delete_board_folder_name[MAX_LEN + 2];
    sprintf(delete_board_folder_name, "%s\n", board_name);
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, fp))
    {
        if (strcmp(line, delete_board_folder_name) != 0)
        {
            fputs(line, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    char command[MAX_LEN] = {};
    sprintf(command, "cmd /c del %s", location);
    system(command); // remove
    rename(tmp_location, location);



    //TODO: remove lists have that board_name in Lists.csv
}

// create and delete board
void create_board_folder(char board_name[MAX_LEN], char username[MAX_LEN]) //
{
    char command[128];
    sprintf(command, "mkdir \".\\dBoardDB\\Users\\%s\\Boards\\%s\"", username, board_name);
    system(command);

    // SHOULD <setup_board(board_name , username);> AFTER USEING THIS FUNCTION
    // SHOULD <add_locBoard(board_name , username);> AFTER USEING THIS FUNCTION
}

void delete_board_folder(char board_name[MAX_LEN], char username[MAX_LEN]) //
{
    char command[128];
    sprintf(command, "rmdir /s /q \".\\dBoardDB\\Users\\%s\\Boards\\%s\"", username, board_name);
    system(command);

    // SHOULD <clean_lists(board_name , username);> AFTER USEING THIS FUNCTION
    // SHOULD <del_locBoard(board_name , username);> AFTER USEING THIS FUNCTION
}

// setup an empty board
void setup_board(char board_name[MAX_LEN], char username[MAX_LEN]) //
{
    char list_name[MAX_LEN] = {};

    strcpy(list_name, "Completed");
    create_list_file(board_name, list_name, username);
    add_locList(board_name, list_name, username);

    strcpy(list_name, "InProgress");
    create_list_file(board_name, list_name, username);
    add_locList(board_name, list_name, username);

    strcpy(list_name, "ToDo");
    create_list_file(board_name, list_name, username);
    add_locList(board_name, list_name, username);
}

// signup or login user
void setup_user(char username[MAX_LEN]) //
{
    // create and setup basic user folders
    char command[128];
    sprintf(command, "mkdir \".\\dBoardDB\\Users\\%s\"", username);
    system(command);

    sprintf(command, "mkdir \".\\dBoardDB\\Users\\%s\\Boards\"", username);
    system(command);

    sprintf(command, "mkdir \".\\dBoardDB\\Users\\%s\\Logs (can be in next update)\"", username);
    system(command);

    sprintf(command, "mkdir \".\\dBoardDB\\Users\\%s\\Locations\"", username);
    system(command);

    // create basic user files
    char location[128];
    sprintf(location, ".\\dBoardDB\\Users\\%s\\Locations\\Boards.csv", username);
    FILE *fp = fopen(location, "w");
    if (NULL == fp)
    {
        printf("file can't be opened \n");
    }
    fclose(fp);

    sprintf(location, ".\\dBoardDB\\Users\\%s\\Locations\\Lists.csv", username);
    fp = fopen(location, "w");
    if (NULL == fp)
    {
        printf("file can't be opened \n");
    }
    fclose(fp);

    sprintf(location, ".\\dBoardDB\\Users\\%s\\Logs (can be in next update)\\LoginLogs.csv", username);
    fp = fopen(location, "w");
    if (NULL == fp)
    {
        printf("file can't be opened \n");
    }
    fclose(fp);

    sprintf(location, ".\\dBoardDB\\Users\\%s\\Logs (can be in next update)\\ChangeLogs.csv", username);
    fp = fopen(location, "w");
    if (NULL == fp)
    {
        printf("file can't be opened \n");
    }
    fclose(fp);

    // create and setup basic user boards
    char board_name[MAX_LEN] = {};

    strcpy(board_name, "Work");
    create_board_folder(board_name, username);
    add_locBoard(board_name, username);
    setup_board(board_name, username);

    strcpy(board_name, "Personal");
    create_board_folder(board_name, username);
    add_locBoard(board_name, username);
    setup_board(board_name, username);

    strcpy(board_name, "Study");
    create_board_folder(board_name, username);
    add_locBoard(board_name, username);
    setup_board(board_name, username);
}

int signup_user(char username[MAX_LEN], char password[MAX_LEN])
{
    char line_username[MAX_LEN];
    char line_password[MAX_LEN];
    FILE *fp = fopen(".\\dBoardDB\\Users\\UsersInfo\\UsersInfo.csv", "r");
    if (NULL == fp)
    {
        printf("file can't be opened \n");
    }
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, fp))
    {
        sscanf(line, "%[^,],%s\n", line_username, line_password);
        if (strcmp(line_username, username) == 0)
        {
            fclose(fp);
            return 0;
        }
    }
    fclose(fp);

    fp = fopen(".\\dBoardDB\\Users\\UsersInfo\\UsersInfo.csv", "a");
    if (NULL == fp)
    {
        printf("file can't be opened \n");
    }
    fprintf(fp, "%s,%s\n", username, password);
    fclose(fp);

    return 1;

    // SHOULD <setup_user(username);> AFTER USING THIS FUNCTION
}

int login_user(char username[MAX_LEN], char password[MAX_LEN]) //
{
    FILE *fp = fopen(".\\dBoardDB\\Users\\UsersInfo\\UsersInfo.csv", "r");
    if (NULL == fp)
    {
        printf("file can't be opened \n");
    }
    char login_line[MAX_LEN + MAX_LEN + 2];
    sprintf(login_line, "%s,%s\n", username, password);
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, fp))
    {
        if (strcmp(line, login_line) == 0)
        {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

// reading and writing tasks from file and management them
task *read_tasks_csv(char board_name[MAX_LEN], char list_name[MAX_LEN], char username[MAX_LEN]) //
{
    task *head = NULL;
    task *current_task = head;
    int i = 0;

    char location[128];
    sprintf(location, ".\\dBoardDB\\Users\\%s\\Boards\\%s\\%s.csv", username, board_name, list_name);

    FILE *fp = fopen(location, "r");
    if (NULL == fp)
    {
        printf("file can't be opened \n");
    }
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, fp))
    {
        // EX: <Task 1,This is the first task,1,10>
        char line_name[32];
        char line_description[512];
        int line_priority;
        int line_deadline;

        sscanf(line, "%[^,],%[^,],%d,%d", line_name, line_description, &line_priority, &line_deadline);

        if (i == 0)
        {
            // create the first task
            head = (task *)malloc(sizeof(task));
            strcpy(head->name, line_name);
            strcpy(head->description, line_description);
            head->priority = line_priority;
            head->deadline = line_deadline;
            head->next_task = NULL;

            // update current_task to point to head
            current_task = head;
        }
        else
        {
            // create the remaining tasks
            current_task->next_task = (task *)malloc(sizeof(task));
            current_task = current_task->next_task;
            strcpy(current_task->name, line_name);
            strcpy(current_task->description, line_description);
            current_task->priority = line_priority;
            current_task->deadline = line_deadline;
            current_task->next_task = NULL;
        }
        i++;
    }

    fclose(fp);
    return head;
}
void write_tasks_csv(task *head, char board_name[MAX_LEN], char list_name[MAX_LEN], char username[MAX_LEN]) //
{
    task *current_task = head;
    int i = 0;

    char location[128];
    sprintf(location, ".\\dBoardDB\\Users\\%s\\Boards\\%s\\%s.csv", username, board_name, list_name);

    char tmp_location[128];
    sprintf(tmp_location, ".\\dBoardDB\\Users\\%s\\Boards\\%s\\tmp%s.csv", username, board_name, list_name);

    FILE *temp = fopen(tmp_location, "w");
    if (NULL == temp)
    {
        printf("file can't be opened \n");
    }
    char line[MAX_LINE_LENGTH];
    while (current_task != NULL)
    {
        // EX: <Task 1,This is the first task,1,10>
        char line_name[32];
        char line_description[512];
        int line_priority;
        int line_deadline;

        sprintf(line, "%s,%s,%d,%d\n", current_task->name, current_task->description, current_task->priority, current_task->deadline);
        fputs(line, temp);

        // update current_task to point to head
        current_task = current_task->next_task;

        i++;
    }

    fclose(temp);

    remove(location);
    rename(tmp_location, location);
}

void show_tasks(task *head) //
{
    // print tasks
    task *current_task = head;
    while (current_task != NULL)
    {
        printf("Task name: %s\n", current_task->name);
        printf("Task description: %s\n", current_task->description);
        printf("Task priority: %d\n", current_task->priority);
        printf("Task deadline: %d\n", current_task->deadline);
        printf("\n");
        current_task = current_task->next_task;
    }
}

void free_all_tasks(task *head) //
{
    // free memory
    task *current_task = head;
    while (current_task != NULL)
    {
        head = head->next_task;
        free(current_task);
        current_task = head;
    }
}

void swap_tasks(task *task1, task *task2) //
{
    // swapping all datas but their locations will be remained
    char tmp_name[32];
    char tmp_description[512];
    int tmp_priority;
    int tmp_deadline;

    // copy data from task1 to temporary variables
    strcpy(tmp_name, task1->name);
    strcpy(tmp_description, task1->description);
    tmp_priority = task1->priority;
    tmp_deadline = task1->deadline;

    // copy data from task2 to task1
    strcpy(task1->name, task2->name);
    strcpy(task1->description, task2->description);
    task1->priority = task2->priority;
    task1->deadline = task2->deadline;

    // copy data from temporary variables (original task1 data) to task2
    strcpy(task2->name, tmp_name);
    strcpy(task2->description, tmp_description);
    task2->priority = tmp_priority;
    task2->deadline = tmp_deadline;
}

void add_task_atEnd(task *head, char name[32], char description[512], int priority, int deadline) //
{
    task *new_task = (task *)malloc(sizeof(task));

    strcpy(new_task->name, name);
    strcpy(new_task->description, description);
    new_task->priority = priority;
    new_task->deadline = deadline;
    new_task->next_task = NULL;

    task *current_task = head;
    task *previous_task = NULL;

    do
    {
        if (current_task->next_task == NULL)
        {
            current_task->next_task = new_task;
            return;
        }

        previous_task = current_task;
        current_task = current_task->next_task;
    } while (current_task != NULL);
}

void delete_task_byPtr(task *head, task *deleted_task) //
{

    task *current_task = head;
    task *previous_task = NULL;

    do
    {
        if (head == NULL || deleted_task == NULL)
        {
            return;
        }

        if (head == deleted_task)
        {
            task *temp = head;      // store old head
            head = temp->next_task; // Change head
            free(temp);             // free old head
            return;
        }

        else if (current_task == deleted_task)
        {
            previous_task->next_task = current_task->next_task;
        }

        previous_task = current_task;
        current_task = current_task->next_task;
    } while (current_task != NULL);

    free(deleted_task);
}

void edit_task_byPtr_autoInp(task *edited_task) //
{
    char tmp_name[32];
    char tmp_description[512];
    int tmp_priority;
    int tmp_deadline;

    fflush(stdin);
    printf("Enter your new  -NAME- :\nYour last input is <%s>\n", edited_task->name);
    scanf("%[^\n]", tmp_name);
    fflush(stdin);
    strcpy(edited_task->name, tmp_name);

    printf("Enter your new  -DESCRIPTION- :\nYour last input is <%s>\n", edited_task->description);
    scanf("%[^\n]", tmp_description);
    fflush(stdin);
    if (tmp_name[0] != '\n')
    {
        strcpy(edited_task->description, tmp_description);
    }

    printf("Enter your new  -PRIORITY- <1-2-3> :\nYour last input is <%d>\n", edited_task->priority);
    scanf("%d", &tmp_priority);
    if (tmp_name[0] != '\n')
    {
        edited_task->priority = tmp_priority;
    }

    printf("Enter your new  -DEADLINE- <YYMMDD> :\nYour last input is <%d>\n", edited_task->deadline);
    scanf("%d", &tmp_deadline);
    if (tmp_name[0] != '\n')
    {
        edited_task->deadline = tmp_deadline;
    }
}

task *search_task_by_index(task *head, int index) //
{
    task *current_task = head;
    int i = 0;

    do
    {
        if (i == index)
        {
            return current_task;
        }
        current_task = current_task->next_task;
        i++;
    } while (current_task != NULL);
}

// kinds of soarting
void sort_tasks_priority_a(task *head) //
{
    if (head == NULL)
    {
        printf("Invalid parameters\n");
        return;
    }

    int swapped;
    task *current_task;
    task *previous_task = NULL;

    do
    {
        swapped = 0;
        current_task = head;

        while (current_task->next_task != previous_task)
        {
            if (current_task->priority > current_task->next_task->priority)
            {
                if (current_task != head)
                {
                    swap_tasks(current_task, current_task->next_task);
                    swapped = 1;
                }
            }
            current_task = current_task->next_task;
        }
        previous_task = current_task;
    } while (swapped);
}

void sort_tasks_deadline_a(task *head) //
{
    if (head == NULL)
    {
        printf("Invalid parameters\n");
        return;
    }

    int swapped;
    task *current_task;
    task *previous_task = NULL;

    do
    {
        swapped = 0;
        current_task = head;

        while (current_task->next_task != previous_task)
        {
            if (current_task->deadline > current_task->next_task->deadline)
            {
                if (current_task != head)
                {
                    swap_tasks(current_task, current_task->next_task);
                    swapped = 1;
                }
            }
            current_task = current_task->next_task;
        }
        previous_task = current_task;
    } while (swapped);
}

void sort_tasks_name_a(task *head) //
{
    if (head == NULL)
    {
        printf("Invalid parameters\n");
        return;
    }

    int swapped;
    task *current_task;
    task *previous_task = NULL;

    do
    {
        swapped = 0;
        current_task = head;

        while (current_task->next_task != previous_task)
        {
            if (strcasecmp(current_task->name, current_task->next_task->name) == 1)
            {
                if (current_task != head)
                {
                    swap_tasks(current_task, current_task->next_task);
                    swapped = 1;
                }
            }
            current_task = current_task->next_task;
        }
        previous_task = current_task;
    } while (swapped);
}

void sort_tasks_priority_d(task *head) //
{
    if (head == NULL)
    {
        printf("Invalid parameters\n");
        return;
    }

    int swapped;
    task *current_task;
    task *previous_task = NULL;

    do
    {
        swapped = 0;
        current_task = head;

        while (current_task->next_task != previous_task)
        {
            if (current_task->priority < current_task->next_task->priority)
            {
                if (current_task != head)
                {
                    swap_tasks(current_task, current_task->next_task);
                    swapped = 1;
                }
            }
            current_task = current_task->next_task;
        }
        previous_task = current_task;
    } while (swapped);
}

void sort_tasks_deadline_d(task *head) //
{
    if (head == NULL)
    {
        printf("Invalid parameters\n");
        return;
    }

    int swapped;
    task *current_task;
    task *previous_task = NULL;

    do
    {
        swapped = 0;
        current_task = head;

        while (current_task->next_task != previous_task)
        {
            if (current_task->deadline < current_task->next_task->deadline)
            {
                if (current_task != head)
                {
                    swap_tasks(current_task, current_task->next_task);
                    swapped = 1;
                }
            }
            current_task = current_task->next_task;
        }
        previous_task = current_task;
    } while (swapped);
}

void sort_tasks_name_d(task *head) //
{
    if (head == NULL)
    {
        printf("Invalid parameters\n");
        return;
    }

    int swapped;
    task *current_task;
    task *previous_task = NULL;

    do
    {
        swapped = 0;
        current_task = head;

        while (current_task->next_task != previous_task)
        {
            if (strcasecmp(current_task->name, current_task->next_task->name) == -1)
            {
                if (current_task != head)
                {
                    swap_tasks(current_task, current_task->next_task);
                    swapped = 1;
                }
            }
            current_task = current_task->next_task;
        }
        previous_task = current_task;
    } while (swapped);
}

int reminder_compare_task(task *current_task, int date)
{
    int task_year = current_task->deadline / 10000;
    int task_month = (current_task->deadline / 100) - (task_year * 100);
    int task_day = current_task->deadline % 100;

    int task_days = (task_year * 365) + (task_month * 30) + task_day;

    int date_year = date / 10000;
    int date_month = (date / 100) - (date_year * 100);
    int date_day = date % 100;

    int date_days = (date_year * 365) + (date_month * 30) + date_day;

    if (((task_days - date_days) <= 3) && ((task_days - date_days) >= 0))
    {
        return 1;
    }
    return 0;
}

/* FRONT-END Functions */

// login pages
int login_menu_autoInp(char username[MAX_LEN]) //
{
    int result = 0;
    char password[MAX_LEN];

    char command[MAX_LINE_LENGTH];
    printf("Signin Or Signup :\n");
    printf("    login <username> <password>\n");
    printf("    signup <username> <password>\n");

    fflush(stdin);
    scanf("%[^\n]", command);

    char order[16];
    sscanf(command, "%s %s %s", order, username, password);

    if (strcmp(order, "login") == 0)
    {
        printf("loging in...\n");
        return login_user(username, password);
    }
    else if (strcmp(order, "signup") == 0)
    {
        printf("signing up ...\n");
        result = signup_user(username, password);
        if (result)
        {
            setup_user(username);
        }
        return result;
    }
    else
    {
        printf("unknown command <%s>\n", command);
        return 1;
    }

    // IF CAN LOGIN OR SIGNUP WRITE SOMETHING LIKE <loging in successfully> AFTER USING THIS FUNCTION
}
// set date
void set_time_menu(char username[MAX_LEN], int date, int time)
{

    /* CreateDisplay */
    char header_display[7][121] = {
        {".----------------------------------------------------------------------------------------------------------------------."},
        {"| .---------------. .-----------------------. .-----------------------------------------..---------------------------. |"},
        {"| |               | |  DBOARD               | |  GUIDE:                                 ||             |   _   _     | |"},
        {"| |     /\\_/\\     | | USER-NAME:            | | write date you want to set like this    ||       . | . x .|.|-|.|    | |"},
        {"| |    ( 0.0 )    | | DATE:                 | | <YY/MM/DD>                              ||    |\\ ./.\\-/.\\-|.|.|.|    | |"},
        {"| |     > ^ <     | | TIME:                 | |                                         || ~~~|.|_|.|_|.|.|.|_|.|~~~ | |"},
        {"| '---------------' '-----------------------' '-----------------------------------------''---------------------------' |"}};

    /* Date and Time */
    int date_year = date / 10000;
    int date_month = (date / 100) - (date_year * 100);
    int date_day = date % 100;

    int time_hour = time / 100;
    int time_min = time % 100;

    header_display[4][28] = ((char)(date_year / 10) + 48);
    header_display[4][29] = ((char)(date_year % 10) + 48);
    header_display[4][30] = '/';
    header_display[4][31] = ((char)(date_month / 10) + 48);
    header_display[4][32] = ((char)(date_month % 10) + 48);
    header_display[4][33] = '/';
    header_display[4][34] = ((char)(date_day / 10) + 48);
    header_display[4][35] = ((char)(date_day % 10) + 48);

    header_display[5][28] = ((char)(time_hour / 10) + 48);
    header_display[5][29] = ((char)(time_hour % 10) + 48);
    header_display[5][30] = ':';
    header_display[5][31] = ((char)(time_min / 10) + 48);
    header_display[5][32] = ((char)(time_min % 10) + 48);

    /* Username */
    for (int i = 0; i < 10; i++)
    {
        if (username[i] != '\0')
        {
            header_display[3][(32 + i)] = username[i];
        }
    }

    /* ShowDisplay */
    for (int j = 0; j < 7; j++)
    {
        for (int i = 0; i < 121; i++)
        {
            printf("%c", header_display[j][i]);
        }
        printf("\n");
    }

    /* CreateDisplay */
    char body_display[21][121] = {
        {"| .------------------------------------------------------------------------------------------------------------------. |"},
        {"| |                                                                                                                  | |"},
        {"| |                                                                                                                  | |"},
        {"| |                                                                                                                  | |"},
        {"| |                                                                                                                  | |"},
        {"| |                                                                                                                  | |"},
        {"| |                                                                                                                  | |"},
        {"| |                                                                                                                  | |"},
        {"| |                                                                                                                  | |"},
        {"| |                                                                                                                  | |"},
        {"| |                                                                                                                  | |"},
        {"| |                                                                                                                  | |"},
        {"| |                                                                                                                  | |"},
        {"| |                                                                                                                  | |"},
        {"| |                                                                                                                  | |"},
        {"| |                                                                                                                  | |"},
        {"| |                                                                                                                  | |"},
        {"| |                                                                                                                  | |"},
        {"| |                                                                                                                  | |"},
        {"| |                                                                                                                  | |"}};

    /* ShowDisplay */
    for (int j = 0; j < 20; j++)
    {
        for (int i = 0; i < 121; i++)
        {
            printf("%c", body_display[j][i]);
        }
        printf("\n");
    }

    /* CreateDisplay */
    char footer_display[2][121] = {
        {"| '------------------------------------------------------------------------------------------------------------------' |"},
        {"'----------------------------------------------------------------------------------------------------------------------'"}};

    /* ShowDisplay */
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < 121; i++)
        {
            printf("%c", footer_display[j][i]);
        }
        printf("\n");
    }
}
// board pages
void boards_menu(char username[MAX_LEN], int date, int time)
{

    /* CreateDisplay */
    char header_display[7][121] = {
        {".----------------------------------------------------------------------------------------------------------------------."},
        {"| .---------------. .-----------------------. .-----------------------------------------..---------------------------. |"},
        {"| |               | |  DBOARD               | |  IMPORTANT:                             ||             |   _   _     | |"},
        {"| |     /\\_/\\     | | USER-NAME:            | | number 0 and text <back> means go back  ||       . | . x .|.|-|.|    | |"},
        {"| |    ( 0.0 )    | | DATE:                 | |  GUIDE:                                 ||    |\\ ./.\\-/.\\-|.|.|.|    | |"},
        {"| |     > ^ <     | | TIME:                 | | input number of your order              || ~~~|.|_|.|_|.|.|.|_|.|~~~ | |"},
        {"| '---------------' '-----------------------' '-----------------------------------------''---------------------------' |"}};

    /* Date and Time */
    int date_year = date / 10000;
    int date_month = (date / 100) - (date_year * 100);
    int date_day = date % 100;

    int time_hour = time / 100;
    int time_min = time % 100;

    header_display[4][28] = ((char)(date_year / 10) + 48);
    header_display[4][29] = ((char)(date_year % 10) + 48);
    header_display[4][30] = '/';
    header_display[4][31] = ((char)(date_month / 10) + 48);
    header_display[4][32] = ((char)(date_month % 10) + 48);
    header_display[4][33] = '/';
    header_display[4][34] = ((char)(date_day / 10) + 48);
    header_display[4][35] = ((char)(date_day % 10) + 48);

    header_display[5][28] = ((char)(time_hour / 10) + 48);
    header_display[5][29] = ((char)(time_hour % 10) + 48);
    header_display[5][30] = ':';
    header_display[5][31] = ((char)(time_min / 10) + 48);
    header_display[5][32] = ((char)(time_min % 10) + 48);

    /* Username */
    for (int i = 0; i < 10; i++)
    {
        if (username[i] != '\0')
        {
            header_display[3][(32 + i)] = username[i];
        }
    }

    /* ShowDisplay */
    for (int j = 0; j < 7; j++)
    {
        for (int i = 0; i < 121; i++)
        {
            printf("%c", header_display[j][i]);
        }
        printf("\n");
    }

    /* CreateDisplay */
    char body_display[21][121] = {
        {"| .------------------------------------------------------------------------------------------------------------------. |"},
        {"| | .--------------------------------------------------------------------------------------------------------------. | |"},
        {"| | |  1. View Boards                                                                                              | | |"},
        {"| | '--------------------------------------------------------------------------------------------------------------' | |"},
        {"| | .--------------------------------------------------------------------------------------------------------------. | |"},
        {"| | |  2. Create New Board                                                                                         | | |"},
        {"| | '--------------------------------------------------------------------------------------------------------------' | |"},
        {"| | .--------------------------------------------------------------------------------------------------------------. | |"},
        {"| | |  3. Delete Board                                                                                             | | |"},
        {"| | '--------------------------------------------------------------------------------------------------------------' | |"},
        {"| | .--------------------------------------------------------------------------------------------------------------. | |"},
        {"| | |  4. Set Date                                                                                                 | | |"},
        {"| | '--------------------------------------------------------------------------------------------------------------' | |"},
        {"| | .--------------------------------------------------------------------------------------------------------------. | |"},
        {"| | |  5. Exit                                                                                                     | | |"},
        {"| | '--------------------------------------------------------------------------------------------------------------' | |"},
        {"| |                                                                                                                  | |"},
        {"| |                                                                                                                  | |"},
        {"| |                                                                                                                  | |"},
        {"| |                                                                                                                  | |"}};

    /* ShowDisplay */
    for (int j = 0; j < 20; j++)
    {
        for (int i = 0; i < 121; i++)
        {
            printf("%c", body_display[j][i]);
        }
        printf("\n");
    }

    /* CreateDisplay */
    char footer_display[2][121] = {
        {"| '------------------------------------------------------------------------------------------------------------------' |"},
        {"'----------------------------------------------------------------------------------------------------------------------'"}};

    /* ShowDisplay */
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < 121; i++)
        {
            printf("%c", footer_display[j][i]);
        }
        printf("\n");
    }
}

void boards_view_menu(char username[MAX_LEN], int date, int time)
{
    /* CreateDisplay */
    char header_display[11][121] = {
        {".----------------------------------------------------------------------------------------------------------------------."},
        {"| .---------------. .-----------------------. .-----------------------------------------..---------------------------. |"},
        {"| |               | |  DBOARD               | |  GUIDE:                                 ||             |   _   _     | |"},
        {"| |     /\\_/\\     | | USER-NAME:            | | input name of board you want to enter   ||       . | . x .|.|-|.|    | |"},
        {"| |    ( -.- )    | | DATE:                 | |                                         ||    |\\ ./.\\-/.\\-|.|.|.|    | |"},
        {"| |     > ^ <     | | TIME:                 | |                                         || ~~~|.|_|.|_|.|.|.|_|.|~~~ | |"},
        {"| '---------------' '-----------------------' '-----------------------------------------''---------------------------' |"},
        {"| .------------------------------------------------------------------------------------------------------------------. |"},
        {"| | .-------------------------------------.                                                                          | |"},
        {"| | |  Available Boards:                  |                                                                          | |"},
        {"| | '-------------------------------------'                                                                          | |"}};

    /* Date and Time */
    int date_year = date / 10000;
    int date_month = (date / 100) - (date_year * 100);
    int date_day = date % 100;

    int time_hour = time / 100;
    int time_min = time % 100;

    header_display[4][28] = ((char)(date_year / 10) + 48);
    header_display[4][29] = ((char)(date_year % 10) + 48);
    header_display[4][30] = '/';
    header_display[4][31] = ((char)(date_month / 10) + 48);
    header_display[4][32] = ((char)(date_month % 10) + 48);
    header_display[4][33] = '/';
    header_display[4][34] = ((char)(date_day / 10) + 48);
    header_display[4][35] = ((char)(date_day % 10) + 48);

    header_display[5][28] = ((char)(time_hour / 10) + 48);
    header_display[5][29] = ((char)(time_hour % 10) + 48);
    header_display[5][30] = ':';
    header_display[5][31] = ((char)(time_min / 10) + 48);
    header_display[5][32] = ((char)(time_min % 10) + 48);

    /* Username */
    for (int i = 0; i < 10; i++)
    {
        if (username[i] != '\0')
        {
            header_display[3][(32 + i)] = username[i];
        }
    }

    /* ShowDisplay */
    for (int j = 0; j < 11; j++)
    {
        for (int i = 0; i < 121; i++)
        {
            printf("%c", header_display[j][i]);
        }
        printf("\n");
    }

    /* CreateTables */
    char location[128];
    sprintf(location, ".\\dBoardDB\\Users\\%s\\Locations\\Boards.csv", username);
    FILE *fp = fopen(location, "r");
    if (NULL == fp)
    {
        printf("file can't be opened \n");
    }
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, fp))
    {
        char table[3][121] = {
            {"| | .--------------------------------------------------------------------------------------------------------------. | |"},
            {"| | |                                                                                                              | | |"},
            {"| | '--------------------------------------------------------------------------------------------------------------' | |"}};
        for (int i = 0; i < (strlen(line) - 1); i++)
        {
            table[1][(6 + i)] = line[i];
        }
        /* ShowTables */
        for (int j = 0; j < 3; j++)
        {
            for (int i = 0; i < 121; i++)
            {
                printf("%c", table[j][i]);
            }
            printf("\n");
        }
    }

    /* CreateDisplay */
    char footer_display[3][121] = {
        {"| |                                                                                                                  | |"},
        {"| '------------------------------------------------------------------------------------------------------------------' |"},
        {"'----------------------------------------------------------------------------------------------------------------------'"},
    };

    /* ShowDisplay */
    for (int j = 0; j < 3; j++)
    {
        for (int i = 0; i < 121; i++)
        {
            printf("%c", footer_display[j][i]);
        }
        printf("\n");
    }

    fclose(fp);
}

void boards_create_menu(char username[MAX_LEN], int date, int time)
{
    /* CreateDisplay */
    char header_display[11][121] = {
        {".----------------------------------------------------------------------------------------------------------------------."},
        {"| .---------------. .-----------------------. .-----------------------------------------..---------------------------. |"},
        {"| |               | |  DBOARD               | |  GUIDE:                                 ||             |   _   _     | |"},
        {"| |     /\\_/\\     | | USER-NAME:            | | input name of board you want to create  ||       . | . x .|.|-|.|    | |"},
        {"| |    ( *.* )    | | DATE:                 | |                                         ||    |\\ ./.\\-/.\\-|.|.|.|    | |"},
        {"| |     > ^ <     | | TIME:                 | |                                         || ~~~|.|_|.|_|.|.|.|_|.|~~~ | |"},
        {"| '---------------' '-----------------------' '-----------------------------------------''---------------------------' |"},
        {"| .------------------------------------------------------------------------------------------------------------------. |"},
        {"| | .-------------------------------------.                                                                          | |"},
        {"| | |  Available boards:                  |                                                                          | |"},
        {"| | '-------------------------------------'                                                                          | |"}};

    /* Date and Time */
    int date_year = date / 10000;
    int date_month = (date / 100) - (date_year * 100);
    int date_day = date % 100;

    int time_hour = time / 100;
    int time_min = time % 100;

    header_display[4][28] = ((char)(date_year / 10) + 48);
    header_display[4][29] = ((char)(date_year % 10) + 48);
    header_display[4][30] = '/';
    header_display[4][31] = ((char)(date_month / 10) + 48);
    header_display[4][32] = ((char)(date_month % 10) + 48);
    header_display[4][33] = '/';
    header_display[4][34] = ((char)(date_day / 10) + 48);
    header_display[4][35] = ((char)(date_day % 10) + 48);

    header_display[5][28] = ((char)(time_hour / 10) + 48);
    header_display[5][29] = ((char)(time_hour % 10) + 48);
    header_display[5][30] = ':';
    header_display[5][31] = ((char)(time_min / 10) + 48);
    header_display[5][32] = ((char)(time_min % 10) + 48);

    /* Username */
    for (int i = 0; i < 10; i++)
    {
        if (username[i] != '\0')
        {
            header_display[3][(32 + i)] = username[i];
        }
    }

    /* ShowDisplay */
    for (int j = 0; j < 11; j++)
    {
        for (int i = 0; i < 121; i++)
        {
            printf("%c", header_display[j][i]);
        }
        printf("\n");
    }

    /* CreateTables */
    char location[128];
    sprintf(location, ".\\dBoardDB\\Users\\%s\\Locations\\Boards.csv", username);
    FILE *fp = fopen(location, "r");
    if (NULL == fp)
    {
        printf("file can't be opened \n");
    }
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, fp))
    {
        char table[3][121] = {
            {"| | .--------------------------------------------------------------------------------------------------------------. | |"},
            {"| | |                                                                                                              | | |"},
            {"| | '--------------------------------------------------------------------------------------------------------------' | |"}};
        for (int i = 0; i < (strlen(line) - 1); i++)
        {
            table[1][(6 + i)] = line[i];
        }
        /* ShowTables */
        for (int j = 0; j < 3; j++)
        {
            for (int i = 0; i < 121; i++)
            {
                printf("%c", table[j][i]);
            }
            printf("\n");
        }
    }

    /* CreateDisplay */
    char footer_display[2][121] = {
        {"| '------------------------------------------------------------------------------------------------------------------' |"},
        {"'----------------------------------------------------------------------------------------------------------------------'"}};

    /* ShowDisplay */
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < 121; i++)
        {
            printf("%c", footer_display[j][i]);
        }
        printf("\n");
    }

    fclose(fp);
}

void boards_delete_menu(char username[MAX_LEN], int date, int time)
{
    /* CreateDisplay */
    char header_display[11][121] = {
        {".----------------------------------------------------------------------------------------------------------------------."},
        {"| .---------------. .-----------------------. .-----------------------------------------..---------------------------. |"},
        {"| |               | |  DBOARD               | |  GUIDE:                                 ||             |   _   _     | |"},
        {"| |     /\\_/\\     | | USER-NAME:            | | input name of board you want to delete  ||       . | . x .|.|-|.|    | |"},
        {"| |    ( x.x )    | | DATE:                 | |                                         ||    |\\ ./.\\-/.\\-|.|.|.|    | |"},
        {"| |     > ^ <     | | TIME:                 | |                                         || ~~~|.|_|.|_|.|.|.|_|.|~~~ | |"},
        {"| '---------------' '-----------------------' '-----------------------------------------''---------------------------' |"},
        {"| .------------------------------------------------------------------------------------------------------------------. |"},
        {"| | .-------------------------------------.                                                                          | |"},
        {"| | |  Available boards:                  |                                                                          | |"},
        {"| | '-------------------------------------'                                                                          | |"}};

    /* Date and Time */
    int date_year = date / 10000;
    int date_month = (date / 100) - (date_year * 100);
    int date_day = date % 100;

    int time_hour = time / 100;
    int time_min = time % 100;

    header_display[4][28] = ((char)(date_year / 10) + 48);
    header_display[4][29] = ((char)(date_year % 10) + 48);
    header_display[4][30] = '/';
    header_display[4][31] = ((char)(date_month / 10) + 48);
    header_display[4][32] = ((char)(date_month % 10) + 48);
    header_display[4][33] = '/';
    header_display[4][34] = ((char)(date_day / 10) + 48);
    header_display[4][35] = ((char)(date_day % 10) + 48);

    header_display[5][28] = ((char)(time_hour / 10) + 48);
    header_display[5][29] = ((char)(time_hour % 10) + 48);
    header_display[5][30] = ':';
    header_display[5][31] = ((char)(time_min / 10) + 48);
    header_display[5][32] = ((char)(time_min % 10) + 48);

    /* Username */
    for (int i = 0; i < 10; i++)
    {
        if (username[i] != '\0')
        {
            header_display[3][(32 + i)] = username[i];
        }
    }

    /* ShowDisplay */
    for (int j = 0; j < 11; j++)
    {
        for (int i = 0; i < 121; i++)
        {
            printf("%c", header_display[j][i]);
        }
        printf("\n");
    }

    /* CreateTables */
    char location[128];
    sprintf(location, ".\\dBoardDB\\Users\\%s\\Locations\\Boards.csv", username);
    FILE *fp = fopen(location, "r");
    if (NULL == fp)
    {
        printf("file can't be opened \n");
    }
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, fp))
    {
        char table[3][121] = {
            {"| | .--------------------------------------------------------------------------------------------------------------. | |"},
            {"| | |                                                                                                              | | |"},
            {"| | '--------------------------------------------------------------------------------------------------------------' | |"}};
        for (int i = 0; i < (strlen(line) - 1); i++)
        {
            table[1][(6 + i)] = line[i];
        }
        /* ShowTables */
        for (int j = 0; j < 3; j++)
        {
            for (int i = 0; i < 121; i++)
            {
                printf("%c", table[j][i]);
            }
            printf("\n");
        }
    }

    /* CreateDisplay */
    char footer_display[2][121] = {
        {"| '------------------------------------------------------------------------------------------------------------------' |"},
        {"'----------------------------------------------------------------------------------------------------------------------'"}};

    /* ShowDisplay */
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < 121; i++)
        {
            printf("%c", footer_display[j][i]);
        }
        printf("\n");
    }

    fclose(fp);
}

// lists pages
void lists_menu(char username[MAX_LEN], char board_name[MAX_LEN], int date, int time)
{
    /* CreateDisplay */
    char header_display[7][121] = {
        {".----------------------------------------------------------------------------------------------------------------------."},
        {"| .---------------. .-----------------------. .-----------------------------------------..---------------------------. |"},
        {"| |               | |  DBOARD               | |  GUIDE:                                 ||             |   _   _     | |"},
        {"| |     /\\_/\\     | | USER-NAME:            | | input number of your order              ||       . | . x .|.|-|.|    | |"},
        {"| |    ( o.o )    | | DATE:                 | |                                         ||    |\\ ./.\\-/.\\-|.|.|.|    | |"},
        {"| |     > ^ <     | | TIME:                 | |                                         || ~~~|.|_|.|_|.|.|.|_|.|~~~ | |"},
        {"| '---------------' '-----------------------' '-----------------------------------------''---------------------------' |"}};

    /* Date and Time */
    int date_year = date / 10000;
    int date_month = (date / 100) - (date_year * 100);
    int date_day = date % 100;

    int time_hour = time / 100;
    int time_min = time % 100;

    header_display[4][28] = ((char)(date_year / 10) + 48);
    header_display[4][29] = ((char)(date_year % 10) + 48);
    header_display[4][30] = '/';
    header_display[4][31] = ((char)(date_month / 10) + 48);
    header_display[4][32] = ((char)(date_month % 10) + 48);
    header_display[4][33] = '/';
    header_display[4][34] = ((char)(date_day / 10) + 48);
    header_display[4][35] = ((char)(date_day % 10) + 48);

    header_display[5][28] = ((char)(time_hour / 10) + 48);
    header_display[5][29] = ((char)(time_hour % 10) + 48);
    header_display[5][30] = ':';
    header_display[5][31] = ((char)(time_min / 10) + 48);
    header_display[5][32] = ((char)(time_min % 10) + 48);

    /* Username */
    for (int i = 0; i < 10; i++)
    {
        if (username[i] != '\0')
        {
            header_display[3][(32 + i)] = username[i];
        }
    }

    /* ShowDisplay */
    for (int j = 0; j < 7; j++)
    {
        for (int i = 0; i < 121; i++)
        {
            printf("%c", header_display[j][i]);
        }
        printf("\n");
    }

    /* CreateDisplay */
    char body_display[21][121] = {
        {"| .-----. .----------------------------------------------------------------------------------------------------------. |"},
        {"| | .-. | | .------------------------------------------------------------------------------------------------------. | |"},
        {"| | | | | | |  1. View Lists                                                                                       | | |"},
        {"| | | | | | '------------------------------------------------------------------------------------------------------' | |"},
        {"| | | | | | .------------------------------------------------------------------------------------------------------. | |"},
        {"| | | | | | |  2. Create New List                                                                                  | | |"},
        {"| | | | | | '------------------------------------------------------------------------------------------------------' | |"},
        {"| | | | | | .------------------------------------------------------------------------------------------------------. | |"},
        {"| | | | | | |  3. Delete List                                                                                      | | |"},
        {"| | | | | | '------------------------------------------------------------------------------------------------------' | |"},
        {"| | | | | | .------------------------------------------------------------------------------------------------------. | |"},
        {"| | | | | | |  4. Back                                                                                             | | |"},
        {"| | | | | | '------------------------------------------------------------------------------------------------------' | |"},
        {"| | | | | |                                                                                                          | |"},
        {"| | | | | |                                                                                                          | |"},
        {"| | | | | |                                                                                                          | |"},
        {"| | | | | |                                                                                                          | |"},
        {"| | | | | |                                                                                                          | |"},
        {"| | | | | |                                                                                                          | |"},
        {"| | '-' | |                                                                                                          | |"}};

    for (int i = 0; i < 17; i++)
    {
        if (board_name[i] != '\0')
        {
            body_display[(2 + i)][5] = board_name[i];
        }
    }

    /* ShowDisplay */
    for (int j = 0; j < 20; j++)
    {
        for (int i = 0; i < 121; i++)
        {
            printf("%c", body_display[j][i]);
        }
        printf("\n");
    }

    /* CreateDisplay */
    char footer_display[2][121] = {
        {"| '-----' '----------------------------------------------------------------------------------------------------------' |"},
        {"'----------------------------------------------------------------------------------------------------------------------'"}};

    /* ShowDisplay */
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < 121; i++)
        {
            printf("%c", footer_display[j][i]);
        }
        printf("\n");
    }
}

void lists_view_menu(char username[MAX_LEN], char board_name[MAX_LEN], int date, int time)
{
    /* CreateDisplay */
    char header_display[11][121] = {
        {".----------------------------------------------------------------------------------------------------------------------."},
        {"| .---------------. .-----------------------. .-----------------------------------------..---------------------------. |"},
        {"| |               | |  DBOARD               | |  GUIDE:                                 ||             |   _   _     | |"},
        {"| |     /\\_/\\     | | USER-NAME:            | | input name of list you want to enter    ||       . | . x .|.|-|.|    | |"},
        {"| |    ( _._ )    | | DATE:                 | |                                         ||    |\\ ./.\\-/.\\-|.|.|.|    | |"},
        {"| |     > ^ <     | | TIME:                 | |                                         || ~~~|.|_|.|_|.|.|.|_|.|~~~ | |"},
        {"| '---------------' '-----------------------' '-----------------------------------------''---------------------------' |"},
        {"| .------------------------------------------------------------------------------------------------------------------. |"},
        {"| | .-------------------------------------.                                                                          | |"},
        {"| | |  Available Lists:                   |                                                                          | |"},
        {"| | '-------------------------------------'                                                                          | |"}};

    /* Date and Time */
    int date_year = date / 10000;
    int date_month = (date / 100) - (date_year * 100);
    int date_day = date % 100;

    int time_hour = time / 100;
    int time_min = time % 100;

    header_display[4][28] = ((char)(date_year / 10) + 48);
    header_display[4][29] = ((char)(date_year % 10) + 48);
    header_display[4][30] = '/';
    header_display[4][31] = ((char)(date_month / 10) + 48);
    header_display[4][32] = ((char)(date_month % 10) + 48);
    header_display[4][33] = '/';
    header_display[4][34] = ((char)(date_day / 10) + 48);
    header_display[4][35] = ((char)(date_day % 10) + 48);

    header_display[5][28] = ((char)(time_hour / 10) + 48);
    header_display[5][29] = ((char)(time_hour % 10) + 48);
    header_display[5][30] = ':';
    header_display[5][31] = ((char)(time_min / 10) + 48);
    header_display[5][32] = ((char)(time_min % 10) + 48);

    /* Username */
    for (int i = 0; i < 10; i++)
    {
        if (username[i] != '\0')
        {
            header_display[3][(32 + i)] = username[i];
        }
    }

    /* ShowDisplay */
    for (int j = 0; j < 11; j++)
    {
        for (int i = 0; i < 121; i++)
        {
            printf("%c", header_display[j][i]);
        }
        printf("\n");
    }

    /* CreateTables */
    char location[128];
    sprintf(location, ".\\dBoardDB\\Users\\%s\\Locations\\Lists.csv", username);
    FILE *fp = fopen(location, "r");
    if (NULL == fp)
    {
        printf("file can't be opened \n");
    }
    char line[MAX_LINE_LENGTH];
    char current_board_name[MAX_LEN];
    char current_list_name[MAX_LEN];
    while (fgets(line, MAX_LINE_LENGTH, fp))
    {
        sscanf(line, "%[^,],%[^,]\n", current_board_name, current_list_name);
        if (strcmp(current_board_name, board_name) == 0)
        {
            char table[3][121] = {
                {"| | .--------------------------------------------------------------------------------------------------------------. | |"},
                {"| | |                                                                                                              | | |"},
                {"| | '--------------------------------------------------------------------------------------------------------------' | |"}};
            for (int i = 0; i < (strlen(current_list_name) - 1); i++)
            {
                table[1][(6 + i)] = current_list_name[i];
            }
            /* ShowTables */
            for (int j = 0; j < 3; j++)
            {
                for (int i = 0; i < 121; i++)
                {
                    printf("%c", table[j][i]);
                }
                printf("\n");
            }
        }
    }
    fclose(fp);

    /* CreateDisplay */
    char footer_display[2][121] = {
        {"| '------------------------------------------------------------------------------------------------------------------' |"},
        {"'----------------------------------------------------------------------------------------------------------------------'"}};

    /* ShowDisplay */
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < 121; i++)
        {
            printf("%c", footer_display[j][i]);
        }
        printf("\n");
    }
}

void lists_create_menu(char username[MAX_LEN], char board_name[MAX_LEN], int date, int time)
{
    /* CreateDisplay */
    char header_display[11][121] = {
        {".----------------------------------------------------------------------------------------------------------------------."},
        {"| .---------------. .-----------------------. .-----------------------------------------..---------------------------. |"},
        {"| |               | |  DBOARD               | |  GUIDE:                                 ||             |   _   _     | |"},
        {"| |     /\\_/\\     | | USER-NAME:            | | input name of list you want to create   ||       . | . x .|.|-|.|    | |"},
        {"| |    ( +.+ )    | | DATE:                 | |                                         ||    |\\ ./.\\-/.\\-|.|.|.|    | |"},
        {"| |     > ^ <     | | TIME:                 | |                                         || ~~~|.|_|.|_|.|.|.|_|.|~~~ | |"},
        {"| '---------------' '-----------------------' '-----------------------------------------''---------------------------' |"},
        {"| .------------------------------------------------------------------------------------------------------------------. |"},
        {"| | .-------------------------------------.                                                                          | |"},
        {"| | |  Available Lists:                   |                                                                          | |"},
        {"| | '-------------------------------------'                                                                          | |"}};

    /* Date and Time */
    int date_year = date / 10000;
    int date_month = (date / 100) - (date_year * 100);
    int date_day = date % 100;

    int time_hour = time / 100;
    int time_min = time % 100;

    header_display[4][28] = ((char)(date_year / 10) + 48);
    header_display[4][29] = ((char)(date_year % 10) + 48);
    header_display[4][30] = '/';
    header_display[4][31] = ((char)(date_month / 10) + 48);
    header_display[4][32] = ((char)(date_month % 10) + 48);
    header_display[4][33] = '/';
    header_display[4][34] = ((char)(date_day / 10) + 48);
    header_display[4][35] = ((char)(date_day % 10) + 48);

    header_display[5][28] = ((char)(time_hour / 10) + 48);
    header_display[5][29] = ((char)(time_hour % 10) + 48);
    header_display[5][30] = ':';
    header_display[5][31] = ((char)(time_min / 10) + 48);
    header_display[5][32] = ((char)(time_min % 10) + 48);

    /* Username */
    for (int i = 0; i < 10; i++)
    {
        if (username[i] != '\0')
        {
            header_display[3][(32 + i)] = username[i];
        }
    }

    /* ShowDisplay */
    for (int j = 0; j < 11; j++)
    {
        for (int i = 0; i < 121; i++)
        {
            printf("%c", header_display[j][i]);
        }
        printf("\n");
    }

    /* CreateTables */
    char location[128];
    sprintf(location, ".\\dBoardDB\\Users\\%s\\Locations\\Lists.csv", username);
    FILE *fp = fopen(location, "r");
    if (NULL == fp)
    {
        printf("file can't be opened \n");
    }
    char line[MAX_LINE_LENGTH];
    char current_board_name[MAX_LEN];
    char current_list_name[MAX_LEN];
    while (fgets(line, MAX_LINE_LENGTH, fp))
    {
        sscanf(line, "%[^,],%[^,]\n", current_board_name, current_list_name);
        if (strcmp(current_board_name, board_name) == 0)
        {
            char table[3][121] = {
                {"| | .--------------------------------------------------------------------------------------------------------------. | |"},
                {"| | |                                                                                                              | | |"},
                {"| | '--------------------------------------------------------------------------------------------------------------' | |"}};
            for (int i = 0; i < (strlen(current_list_name) - 1); i++)
            {
                table[1][(6 + i)] = current_list_name[i];
            }
            /* ShowTables */
            for (int j = 0; j < 3; j++)
            {
                for (int i = 0; i < 121; i++)
                {
                    printf("%c", table[j][i]);
                }
                printf("\n");
            }
        }
    }
    fclose(fp);

    /* CreateDisplay */
    char footer_display[2][121] = {
        {"| '------------------------------------------------------------------------------------------------------------------' |"},
        {"'----------------------------------------------------------------------------------------------------------------------'"}};

    /* ShowDisplay */
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < 121; i++)
        {
            printf("%c", footer_display[j][i]);
        }
        printf("\n");
    }
}

void lists_delete_menu(char username[MAX_LEN], char board_name[MAX_LEN], int date, int time)
{
    /* CreateDisplay */
    char header_display[11][121] = {
        {".----------------------------------------------------------------------------------------------------------------------."},
        {"| .---------------. .-----------------------. .-----------------------------------------..---------------------------. |"},
        {"| |               | |  DBOARD               | |  GUIDE:                                 ||             |   _   _     | |"},
        {"| |     /\\_/\\     | | USER-NAME:            | | input name of list you want to delete   ||       . | . x .|.|-|.|    | |"},
        {"| |    ( X.X )    | | DATE:                 | |                                         ||    |\\ ./.\\-/.\\-|.|.|.|    | |"},
        {"| |     > ^ <     | | TIME:                 | |                                         || ~~~|.|_|.|_|.|.|.|_|.|~~~ | |"},
        {"| '---------------' '-----------------------' '-----------------------------------------''---------------------------' |"},
        {"| .------------------------------------------------------------------------------------------------------------------. |"},
        {"| | .-------------------------------------.                                                                          | |"},
        {"| | |  Available Lists:                   |                                                                          | |"},
        {"| | '-------------------------------------'                                                                          | |"}};

    /* Date and Time */
    int date_year = date / 10000;
    int date_month = (date / 100) - (date_year * 100);
    int date_day = date % 100;

    int time_hour = time / 100;
    int time_min = time % 100;

    header_display[4][28] = ((char)(date_year / 10) + 48);
    header_display[4][29] = ((char)(date_year % 10) + 48);
    header_display[4][30] = '/';
    header_display[4][31] = ((char)(date_month / 10) + 48);
    header_display[4][32] = ((char)(date_month % 10) + 48);
    header_display[4][33] = '/';
    header_display[4][34] = ((char)(date_day / 10) + 48);
    header_display[4][35] = ((char)(date_day % 10) + 48);

    header_display[5][28] = ((char)(time_hour / 10) + 48);
    header_display[5][29] = ((char)(time_hour % 10) + 48);
    header_display[5][30] = ':';
    header_display[5][31] = ((char)(time_min / 10) + 48);
    header_display[5][32] = ((char)(time_min % 10) + 48);

    /* Username */
    for (int i = 0; i < 10; i++)
    {
        if (username[i] != '\0')
        {
            header_display[3][(32 + i)] = username[i];
        }
    }

    /* ShowDisplay */
    for (int j = 0; j < 11; j++)
    {
        for (int i = 0; i < 121; i++)
        {
            printf("%c", header_display[j][i]);
        }
        printf("\n");
    }

    /* CreateTables */
    char location[128];
    sprintf(location, ".\\dBoardDB\\Users\\%s\\Locations\\Lists.csv", username);
    FILE *fp = fopen(location, "r");
    if (NULL == fp)
    {
        printf("file can't be opened \n");
    }
    char line[MAX_LINE_LENGTH];
    char current_board_name[MAX_LEN];
    char current_list_name[MAX_LEN];
    while (fgets(line, MAX_LINE_LENGTH, fp))
    {
        sscanf(line, "%[^,],%[^,]\n", current_board_name, current_list_name);
        if (strcmp(current_board_name, board_name) == 0)
        {
            char table[3][121] = {
                {"| | .--------------------------------------------------------------------------------------------------------------. | |"},
                {"| | |                                                                                                              | | |"},
                {"| | '--------------------------------------------------------------------------------------------------------------' | |"}};
            for (int i = 0; i < (strlen(current_list_name) - 1); i++)
            {
                table[1][(6 + i)] = current_list_name[i];
            }
            /* ShowTables */
            for (int j = 0; j < 3; j++)
            {
                for (int i = 0; i < 121; i++)
                {
                    printf("%c", table[j][i]);
                }
                printf("\n");
            }
        }
    }
    fclose(fp);

    /* CreateDisplay */
    char footer_display[2][121] = {
        {"| '------------------------------------------------------------------------------------------------------------------' |"},
        {"'----------------------------------------------------------------------------------------------------------------------'"}};

    /* ShowDisplay */
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < 121; i++)
        {
            printf("%c", footer_display[j][i]);
        }
        printf("\n");
    }
}

// task pages
void tasks_menu(char board_name[MAX_LEN], char list_name[MAX_LEN], char username[MAX_LEN], int date, int time)
{
    /* CreateDisplay */
    char header_display[7][121] = {
        {".----------------------------------------------------------------------------------------------------------------------."},
        {"| .---------------. .-----------------------. .-----------------------------------------..---------------------------. |"},
        {"| |               | |  DBOARD               | |  GUIDE:                                 ||             |   _   _     | |"},
        {"| |     /\\_/\\     | | USER-NAME:            | | input number of your order              ||       . | . x .|.|-|.|    | |"},
        {"| |    ( v.v )    | | DATE:                 | |                                         ||    |\\ ./.\\-/.\\-|.|.|.|    | |"},
        {"| |     > ^ <     | | TIME:                 | |                                         || ~~~|.|_|.|_|.|.|.|_|.|~~~ | |"},
        {"| '---------------' '-----------------------' '-----------------------------------------''---------------------------' |"}};

    /* Date and Time */
    int date_year = date / 10000;
    int date_month = (date / 100) - (date_year * 100);
    int date_day = date % 100;

    int time_hour = time / 100;
    int time_min = time % 100;

    header_display[4][28] = ((char)(date_year / 10) + 48);
    header_display[4][29] = ((char)(date_year % 10) + 48);
    header_display[4][30] = '/';
    header_display[4][31] = ((char)(date_month / 10) + 48);
    header_display[4][32] = ((char)(date_month % 10) + 48);
    header_display[4][33] = '/';
    header_display[4][34] = ((char)(date_day / 10) + 48);
    header_display[4][35] = ((char)(date_day % 10) + 48);

    header_display[5][28] = ((char)(time_hour / 10) + 48);
    header_display[5][29] = ((char)(time_hour % 10) + 48);
    header_display[5][30] = ':';
    header_display[5][31] = ((char)(time_min / 10) + 48);
    header_display[5][32] = ((char)(time_min % 10) + 48);

    /* Username */

    for (int i = 0; i < 10; i++)
    {
        if (username[i] != '\0')
        {
            header_display[3][(32 + i)] = username[i];
        }
    }

    /* ShowDisplay */
    for (int j = 0; j < 7; j++)
    {
        for (int i = 0; i < 121; i++)
        {
            printf("%c", header_display[j][i]);
        }
        printf("\n");
    }

    /* CreateDisplay */
    char body_display[21][121] = {
        {"| .-----. .----------------------------------------------------------------------------------------------------------. |"},
        {"| | .-. | | .------------------------------------------------------------------------------------------------------. | |"},
        {"| | | | | | |  1. View Tasks                                                                                       | | |"},
        {"| | | | | | '------------------------------------------------------------------------------------------------------' | |"},
        {"| | | | | | .------------------------------------------------------------------------------------------------------. | |"},
        {"| | | | | | |  2. Create New Task                                                                                  | | |"},
        {"| | '-' | | '------------------------------------------------------------------------------------------------------' | |"},
        {"| | .-. | | .------------------------------------------------------------------------------------------------------. | |"},
        {"| | | | | | |  3. Delete Task                                                                                      | | |"},
        {"| | | | | | '------------------------------------------------------------------------------------------------------' | |"},
        {"| | | | | | .------------------------------------------------------------------------------------------------------. | |"},
        {"| | | | | | |  4. Edit Task                                                                                        | | |"},
        {"| | | | | | '------------------------------------------------------------------------------------------------------' | |"},
        {"| | | | | | .------------------------------------------------------------------------------------------------------. | |"},
        {"| | | | | | |  5. Sort Tasks                                                                                       | | |"},
        {"| | | | | | '------------------------------------------------------------------------------------------------------' | |"},
        {"| | | | | | .------------------------------------------------------------------------------------------------------. | |"},
        {"| | | | | | |  6. Move Task                                                                                        | | |"},
        {"| | | | | | '------------------------------------------------------------------------------------------------------' | |"},
        {"| | '-' | |                                                                                                          | |"}};

    for (int i = 0; i < 4; i++)
    {
        if (board_name[i] != '\0')
        {
            body_display[(2 + i)][5] = board_name[i];
        }
    }

    for (int i = 0; i < 11; i++)
    {
        if (list_name[i] != '\0')
        {
            body_display[(8 + i)][5] = list_name[i];
        }
    }

    /* ShowDisplay */
    for (int j = 0; j < 20; j++)
    {
        for (int i = 0; i < 121; i++)
        {
            printf("%c", body_display[j][i]);
        }
        printf("\n");
    }

    /* CreateDisplay */
    char footer_display[2][121] = {
        {"| '-----' '----------------------------------------------------------------------------------------------------------' |"},
        {"'----------------------------------------------------------------------------------------------------------------------'"}};

    /* ShowDisplay */
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < 121; i++)
        {
            printf("%c", footer_display[j][i]);
        }
        printf("\n");
    }
}

void tasks_show_menu(task *head, char username[MAX_LEN], int date, int time)
{
    /* CreateDisplay */
    char header_display[11][121] = {
        {".----------------------------------------------------------------------------------------------------------------------."},
        {"| .---------------. .-----------------------. .-----------------------------------------..---------------------------. |"},
        {"| |               | |  DBOARD               | |  GUIDE:                                 ||             |   _   _     | |"},
        {"| |     /\\_/\\     | | USER-NAME:            | |                                         ||       . | . x .|.|-|.|    | |"},
        {"| |    ( V.V )    | | DATE:                 | |                                         ||    |\\ ./.\\-/.\\-|.|.|.|    | |"},
        {"| |     > ^ <     | | TIME:                 | |                                         || ~~~|.|_|.|_|.|.|.|_|.|~~~ | |"},
        {"| '---------------' '-----------------------' '-----------------------------------------''---------------------------' |"},
        {"| .------------------------------------------------------------------------------------------------------------------. |"},
        {"| | .---------------------------.                                                                                    | |"},
        {"| | |  Tasks:                   |                                                                                    | |"},
        {"| | '---------------------------'                                                                                    | |"}};

    /* Date and Time */
    int date_year = date / 10000;
    int date_month = (date / 100) - (date_year * 100);
    int date_day = date % 100;

    int time_hour = time / 100;
    int time_min = time % 100;

    header_display[4][28] = ((char)(date_year / 10) + 48);
    header_display[4][29] = ((char)(date_year % 10) + 48);
    header_display[4][30] = '/';
    header_display[4][31] = ((char)(date_month / 10) + 48);
    header_display[4][32] = ((char)(date_month % 10) + 48);
    header_display[4][33] = '/';
    header_display[4][34] = ((char)(date_day / 10) + 48);
    header_display[4][35] = ((char)(date_day % 10) + 48);

    header_display[5][28] = ((char)(time_hour / 10) + 48);
    header_display[5][29] = ((char)(time_hour % 10) + 48);
    header_display[5][30] = ':';
    header_display[5][31] = ((char)(time_min / 10) + 48);
    header_display[5][32] = ((char)(time_min % 10) + 48);

    /* Username */
    for (int i = 0; i < 10; i++)
    {
        if (username[i] != '\0')
        {
            header_display[3][(32 + i)] = username[i];
        }
    }

    /* ShowDisplay */
    for (int j = 0; j < 11; j++)
    {
        for (int i = 0; i < 121; i++)
        {
            printf("%c", header_display[j][i]);
        }
        printf("\n");
    }

    /* CreateTables */
    task *current_task = head;
    int number = 0;
    while (current_task != NULL)
    {
        // priority to text
        char priority[16];
        if (current_task->priority == 1)
        {
            char tmp_priority[16] = "Low";
            strcpy(priority, tmp_priority);
        }
        else if (current_task->priority == 2)
        {
            char tmp_priority[16] = "Medium";
            strcpy(priority, tmp_priority);
        }
        else if (current_task->priority == 3)
        {
            char tmp_priority[16] = "High";
            strcpy(priority, tmp_priority);
        }
        else if (current_task->priority == 0)
        {
            char tmp_priority[16] = "Priority";
            strcpy(priority, tmp_priority);
        }
        else
        {
            char tmp_priority[16] = "Unknown";
            strcpy(priority, tmp_priority);
        }

        // deadline to text

        char deadline[9] = "00/00/00";
        int year = current_task->deadline / 10000;
        int month = (current_task->deadline / 100) - (year * 100);
        int day = current_task->deadline % 100;

        deadline[0] = ((char)(year / 10) + 48);
        deadline[1] = ((char)(year % 10) + 48);
        deadline[3] = ((char)(month / 10) + 48);
        deadline[4] = ((char)(month % 10) + 48);
        deadline[6] = ((char)(day / 10) + 48);
        deadline[7] = ((char)(day % 10) + 48);

        // name to name and index
        char number_str[8];
        sprintf(number_str, "%d.", number);
        number++;

        char table[3][121] = {
            {"| |                                                                                                                  | |"},
            {"| |                                                                                                                  | |"},
            {"| |                                                                                                                  | |"}};
        {
            // line 0
            int j = 0;
            int i = 0;
            i += 7;

            table[j][i] = '.';
            i++;
            table[j][i] = '-';
            i++;
            for (int text_i = 0; text_i < strlen(number_str); text_i++)
            {
                table[j][i] = '-';
                i++;
            }
            table[j][i] = '-';
            i++;
            table[j][i] = '.';
            i++;
            table[j][i] = ' ';
            i++;

            table[j][i] = '.';
            i++;
            table[j][i] = '-';
            i++;
            for (int text_i = 0; text_i < strlen(current_task->name); text_i++)
            {
                table[j][i] = '-';
                i++;
            }
            table[j][i] = '-';
            i++;
            table[j][i] = '.';
            i++;
            table[j][i] = ' ';
            i++;
            table[j][i] = '.';
            i++;
            table[j][i] = '-';
            i++;
            for (int text_i = 0; text_i < strlen(priority); text_i++)
            {
                table[j][i] = '-';
                i++;
            }
            table[j][i] = '-';
            i++;
            table[j][i] = '.';
            i++;
            table[j][i] = ' ';
            i++;
            table[j][i] = '.';
            i++;
            table[j][i] = '-';
            i++;
            for (int text_i = 0; text_i < strlen(deadline); text_i++)
            {
                table[j][i] = '-';
                i++;
            }
            table[j][i] = '-';
            i++;
            table[j][i] = '.';
            i++;
        }

        {
            // line 1
            int j = 1;
            int i = 0;
            i += 7;

            table[j][i] = '|';
            i++;
            table[j][i] = ' ';
            i++;
            for (int text_i = 0; text_i < strlen(number_str); text_i++)
            {
                table[j][i] = number_str[text_i];
                i++;
            }
            table[j][i] = ' ';
            i++;
            table[j][i] = '|';
            i++;
            table[j][i] = ' ';
            i++;

            table[j][i] = '|';
            i++;
            table[j][i] = ' ';
            i++;
            for (int text_i = 0; text_i < strlen(current_task->name); text_i++)
            {
                table[j][i] = current_task->name[text_i];
                i++;
            }
            table[j][i] = ' ';
            i++;
            table[j][i] = '|';
            i++;
            table[j][i] = ' ';
            i++;
            table[j][i] = '|';
            i++;
            table[j][i] = ' ';
            i++;
            for (int text_i = 0; text_i < strlen(priority); text_i++)
            {
                table[j][i] = priority[text_i];
                i++;
            }
            table[j][i] = ' ';
            i++;
            table[j][i] = '|';
            i++;
            table[j][i] = ' ';
            i++;
            table[j][i] = '|';
            i++;
            table[j][i] = ' ';
            i++;
            for (int text_i = 0; text_i < strlen(deadline); text_i++)
            {
                table[j][i] = deadline[text_i];
                i++;
            }
            table[j][i] = ' ';
            i++;
            table[j][i] = '|';
            i++;
        }

        {
            // line 2
            int j = 2;
            int i = 0;
            i += 7;

            table[j][i] = '\'';
            i++;
            table[j][i] = '-';
            i++;
            for (int text_i = 0; text_i < strlen(number_str); text_i++)
            {
                table[j][i] = '-';
                i++;
            }
            table[j][i] = '-';
            i++;
            table[j][i] = '\'';
            i++;
            table[j][i] = ' ';
            i++;

            table[j][i] = '\'';
            i++;
            table[j][i] = '-';
            i++;
            for (int text_i = 0; text_i < strlen(current_task->name); text_i++)
            {
                table[j][i] = '-';
                i++;
            }
            table[j][i] = '-';
            i++;
            table[j][i] = '\'';
            i++;
            table[j][i] = ' ';
            i++;
            table[j][i] = '\'';
            i++;
            table[j][i] = '-';
            i++;
            for (int text_i = 0; text_i < strlen(priority); text_i++)
            {
                table[j][i] = '-';
                i++;
            }
            table[j][i] = '-';
            i++;
            table[j][i] = '\'';
            i++;
            table[j][i] = ' ';
            i++;
            table[j][i] = '\'';
            i++;
            table[j][i] = '-';
            i++;
            for (int text_i = 0; text_i < strlen(deadline); text_i++)
            {
                table[j][i] = '-';
                i++;
            }
            table[j][i] = '-';
            i++;
            table[j][i] = '\'';
            i++;
        }

        /* ShowTables */
        for (int j = 0; j < 3; j++)
        {
            for (int i = 0; i < 121; i++)
            {
                printf("%c", table[j][i]);
            }
            printf("\n");
        }

        current_task = current_task->next_task;
    }

    /* CreateDisplay */
    char footer_display[2][121] = {
        {"| '------------------------------------------------------------------------------------------------------------------' |"},
        {"'----------------------------------------------------------------------------------------------------------------------'"}};

    /* ShowDisplay */
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < 121; i++)
        {
            printf("%c", footer_display[j][i]);
        }
        printf("\n");
    }
}
void tasks_view_menu(task *head, char username[MAX_LEN], int date, int time)
{
    /* CreateDisplay */
    char header_display[11][121] = {
        {".----------------------------------------------------------------------------------------------------------------------."},
        {"| .---------------. .-----------------------. .-----------------------------------------..---------------------------. |"},
        {"| |               | |  DBOARD               | |  GUIDE:                                 ||             |   _   _     | |"},
        {"| |     /\\_/\\     | | USER-NAME:            | | input number of task you want to        ||       . | . x .|.|-|.|    | |"},
        {"| |    ( U.U )    | | DATE:                 | | see description                         ||    |\\ ./.\\-/.\\-|.|.|.|    | |"},
        {"| |     > ^ <     | | TIME:                 | |                                         || ~~~|.|_|.|_|.|.|.|_|.|~~~ | |"},
        {"| '---------------' '-----------------------' '-----------------------------------------''---------------------------' |"},
        {"| .------------------------------------------------------------------------------------------------------------------. |"},
        {"| | .---------------------------.                                                                                    | |"},
        {"| | |  Tasks:                   |                                                                                    | |"},
        {"| | '---------------------------'                                                                                    | |"}};

    /* Date and Time */
    int date_year = date / 10000;
    int date_month = (date / 100) - (date_year * 100);
    int date_day = date % 100;

    int time_hour = time / 100;
    int time_min = time % 100;

    header_display[4][28] = ((char)(date_year / 10) + 48);
    header_display[4][29] = ((char)(date_year % 10) + 48);
    header_display[4][30] = '/';
    header_display[4][31] = ((char)(date_month / 10) + 48);
    header_display[4][32] = ((char)(date_month % 10) + 48);
    header_display[4][33] = '/';
    header_display[4][34] = ((char)(date_day / 10) + 48);
    header_display[4][35] = ((char)(date_day % 10) + 48);

    header_display[5][28] = ((char)(time_hour / 10) + 48);
    header_display[5][29] = ((char)(time_hour % 10) + 48);
    header_display[5][30] = ':';
    header_display[5][31] = ((char)(time_min / 10) + 48);
    header_display[5][32] = ((char)(time_min % 10) + 48);

    /* Username */
    for (int i = 0; i < 10; i++)
    {
        if (username[i] != '\0')
        {
            header_display[3][(32 + i)] = username[i];
        }
    }

    /* ShowDisplay */
    for (int j = 0; j < 11; j++)
    {
        for (int i = 0; i < 121; i++)
        {
            printf("%c", header_display[j][i]);
        }
        printf("\n");
    }

    /* CreateTables */
    task *current_task = head;
    int number = 0;
    while (current_task != NULL)
    {
        // priority to text
        char priority[16];
        if (current_task->priority == 1)
        {
            char tmp_priority[16] = "Low";
            strcpy(priority, tmp_priority);
        }
        else if (current_task->priority == 2)
        {
            char tmp_priority[16] = "Medium";
            strcpy(priority, tmp_priority);
        }
        else if (current_task->priority == 3)
        {
            char tmp_priority[16] = "High";
            strcpy(priority, tmp_priority);
        }
        else if (current_task->priority == 0)
        {
            char tmp_priority[16] = "Priority";
            strcpy(priority, tmp_priority);
        }
        else
        {
            char tmp_priority[16] = "Unknown";
            strcpy(priority, tmp_priority);
        }

        // deadline to text

        char deadline[9] = "00/00/00";
        int year = current_task->deadline / 10000;
        int month = (current_task->deadline / 100) - (year * 100);
        int day = current_task->deadline % 100;

        deadline[0] = ((char)(year / 10) + 48);
        deadline[1] = ((char)(year % 10) + 48);
        deadline[3] = ((char)(month / 10) + 48);
        deadline[4] = ((char)(month % 10) + 48);
        deadline[6] = ((char)(day / 10) + 48);
        deadline[7] = ((char)(day % 10) + 48);

        // name to name and index
        char number_str[8];
        sprintf(number_str, "%d.", number);
        number++;

        char table[3][121] = {
            {"| |                                                                                                                  | |"},
            {"| |                                                                                                                  | |"},
            {"| |                                                                                                                  | |"}};
        {
            // line 0
            int j = 0;
            int i = 0;
            i += 7;

            table[j][i] = '.';
            i++;
            table[j][i] = '-';
            i++;
            for (int text_i = 0; text_i < strlen(number_str); text_i++)
            {
                table[j][i] = '-';
                i++;
            }
            table[j][i] = '-';
            i++;
            table[j][i] = '.';
            i++;
            table[j][i] = ' ';
            i++;

            table[j][i] = '.';
            i++;
            table[j][i] = '-';
            i++;
            for (int text_i = 0; text_i < strlen(current_task->name); text_i++)
            {
                table[j][i] = '-';
                i++;
            }
            table[j][i] = '-';
            i++;
            table[j][i] = '.';
            i++;
            table[j][i] = ' ';
            i++;
            table[j][i] = '.';
            i++;
            table[j][i] = '-';
            i++;
            for (int text_i = 0; text_i < strlen(priority); text_i++)
            {
                table[j][i] = '-';
                i++;
            }
            table[j][i] = '-';
            i++;
            table[j][i] = '.';
            i++;
            table[j][i] = ' ';
            i++;
            table[j][i] = '.';
            i++;
            table[j][i] = '-';
            i++;
            for (int text_i = 0; text_i < strlen(deadline); text_i++)
            {
                table[j][i] = '-';
                i++;
            }
            table[j][i] = '-';
            i++;
            table[j][i] = '.';
            i++;
        }

        {
            // line 1
            int j = 1;
            int i = 0;
            i += 7;

            table[j][i] = '|';
            i++;
            table[j][i] = ' ';
            i++;
            for (int text_i = 0; text_i < strlen(number_str); text_i++)
            {
                table[j][i] = number_str[text_i];
                i++;
            }
            table[j][i] = ' ';
            i++;
            table[j][i] = '|';
            i++;
            table[j][i] = ' ';
            i++;

            table[j][i] = '|';
            i++;
            table[j][i] = ' ';
            i++;
            for (int text_i = 0; text_i < strlen(current_task->name); text_i++)
            {
                table[j][i] = current_task->name[text_i];
                i++;
            }
            table[j][i] = ' ';
            i++;
            table[j][i] = '|';
            i++;
            table[j][i] = ' ';
            i++;
            table[j][i] = '|';
            i++;
            table[j][i] = ' ';
            i++;
            for (int text_i = 0; text_i < strlen(priority); text_i++)
            {
                table[j][i] = priority[text_i];
                i++;
            }
            table[j][i] = ' ';
            i++;
            table[j][i] = '|';
            i++;
            table[j][i] = ' ';
            i++;
            table[j][i] = '|';
            i++;
            table[j][i] = ' ';
            i++;
            for (int text_i = 0; text_i < strlen(deadline); text_i++)
            {
                table[j][i] = deadline[text_i];
                i++;
            }
            table[j][i] = ' ';
            i++;
            table[j][i] = '|';
            i++;
        }

        {
            // line 2
            int j = 2;
            int i = 0;
            i += 7;

            table[j][i] = '\'';
            i++;
            table[j][i] = '-';
            i++;
            for (int text_i = 0; text_i < strlen(number_str); text_i++)
            {
                table[j][i] = '-';
                i++;
            }
            table[j][i] = '-';
            i++;
            table[j][i] = '\'';
            i++;
            table[j][i] = ' ';
            i++;

            table[j][i] = '\'';
            i++;
            table[j][i] = '-';
            i++;
            for (int text_i = 0; text_i < strlen(current_task->name); text_i++)
            {
                table[j][i] = '-';
                i++;
            }
            table[j][i] = '-';
            i++;
            table[j][i] = '\'';
            i++;
            table[j][i] = ' ';
            i++;
            table[j][i] = '\'';
            i++;
            table[j][i] = '-';
            i++;
            for (int text_i = 0; text_i < strlen(priority); text_i++)
            {
                table[j][i] = '-';
                i++;
            }
            table[j][i] = '-';
            i++;
            table[j][i] = '\'';
            i++;
            table[j][i] = ' ';
            i++;
            table[j][i] = '\'';
            i++;
            table[j][i] = '-';
            i++;
            for (int text_i = 0; text_i < strlen(deadline); text_i++)
            {
                table[j][i] = '-';
                i++;
            }
            table[j][i] = '-';
            i++;
            table[j][i] = '\'';
            i++;
        }

        /* ShowTables */
        for (int j = 0; j < 3; j++)
        {
            for (int i = 0; i < 121; i++)
            {
                printf("%c", table[j][i]);
            }
            printf("\n");
        }

        current_task = current_task->next_task;
    }

    /* CreateDisplay */
    char footer_display[2][121] = {
        {"| '------------------------------------------------------------------------------------------------------------------' |"},
        {"'----------------------------------------------------------------------------------------------------------------------'"}};

    /* ShowDisplay */
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < 121; i++)
        {
            printf("%c", footer_display[j][i]);
        }
        printf("\n");
    }
}

void tasks_create_menu(task *head, char username[MAX_LEN], int date, int time)
{
    /* CreateDisplay */
    char header_display[11][121] = {
        {".----------------------------------------------------------------------------------------------------------------------."},
        {"| .---------------. .-----------------------. .-----------------------------------------..---------------------------. |"},
        {"| |               | |  DBOARD               | |  GUIDE:                                 ||             |   _   _     | |"},
        {"| |     /\\_/\\     | | USER-NAME:            | | write name of task, its description,    ||       . | . x .|.|-|.|    | |"},
        {"| |    ( $.$ )    | | DATE:                 | | its priority <1:Low-2:Medium-3:High>    ||    |\\ ./.\\-/.\\-|.|.|.|    | |"},
        {"| |     > ^ <     | | TIME:                 | | and its deadline <YYMMDD>               || ~~~|.|_|.|_|.|.|.|_|.|~~~ | |"},
        {"| '---------------' '-----------------------' '-----------------------------------------''---------------------------' |"},
        {"| .------------------------------------------------------------------------------------------------------------------. |"},
        {"| | .---------------------------.                                                                                    | |"},
        {"| | |  Tasks:                   |                                                                                    | |"},
        {"| | '---------------------------'                                                                                    | |"}};

    /* Date and Time */
    int date_year = date / 10000;
    int date_month = (date / 100) - (date_year * 100);
    int date_day = date % 100;

    int time_hour = time / 100;
    int time_min = time % 100;

    header_display[4][28] = ((char)(date_year / 10) + 48);
    header_display[4][29] = ((char)(date_year % 10) + 48);
    header_display[4][30] = '/';
    header_display[4][31] = ((char)(date_month / 10) + 48);
    header_display[4][32] = ((char)(date_month % 10) + 48);
    header_display[4][33] = '/';
    header_display[4][34] = ((char)(date_day / 10) + 48);
    header_display[4][35] = ((char)(date_day % 10) + 48);

    header_display[5][28] = ((char)(time_hour / 10) + 48);
    header_display[5][29] = ((char)(time_hour % 10) + 48);
    header_display[5][30] = ':';
    header_display[5][31] = ((char)(time_min / 10) + 48);
    header_display[5][32] = ((char)(time_min % 10) + 48);

    /* Username */
    for (int i = 0; i < 10; i++)
    {
        if (username[i] != '\0')
        {
            header_display[3][(32 + i)] = username[i];
        }
    }

    /* ShowDisplay */
    for (int j = 0; j < 11; j++)
    {
        for (int i = 0; i < 121; i++)
        {
            printf("%c", header_display[j][i]);
        }
        printf("\n");
    }

    /* CreateTables */
    task *current_task = head;
    int number = 0;
    while (current_task != NULL)
    {
        // priority to text
        char priority[16];
        if (current_task->priority == 1)
        {
            char tmp_priority[16] = "Low";
            strcpy(priority, tmp_priority);
        }
        else if (current_task->priority == 2)
        {
            char tmp_priority[16] = "Medium";
            strcpy(priority, tmp_priority);
        }
        else if (current_task->priority == 3)
        {
            char tmp_priority[16] = "High";
            strcpy(priority, tmp_priority);
        }
        else if (current_task->priority == 0)
        {
            char tmp_priority[16] = "Priority";
            strcpy(priority, tmp_priority);
        }
        else
        {
            char tmp_priority[16] = "Unknown";
            strcpy(priority, tmp_priority);
        }

        // deadline to text

        char deadline[9] = "00/00/00";
        int year = current_task->deadline / 10000;
        int month = (current_task->deadline / 100) - (year * 100);
        int day = current_task->deadline % 100;

        deadline[0] = ((char)(year / 10) + 48);
        deadline[1] = ((char)(year % 10) + 48);
        deadline[3] = ((char)(month / 10) + 48);
        deadline[4] = ((char)(month % 10) + 48);
        deadline[6] = ((char)(day / 10) + 48);
        deadline[7] = ((char)(day % 10) + 48);

        // name to name and index
        char number_str[8];
        sprintf(number_str, "%d.", number);
        number++;

        char table[3][121] = {
            {"| |                                                                                                                  | |"},
            {"| |                                                                                                                  | |"},
            {"| |                                                                                                                  | |"}};
        {
            // line 0
            int j = 0;
            int i = 0;
            i += 7;

            table[j][i] = '.';
            i++;
            table[j][i] = '-';
            i++;
            for (int text_i = 0; text_i < strlen(number_str); text_i++)
            {
                table[j][i] = '-';
                i++;
            }
            table[j][i] = '-';
            i++;
            table[j][i] = '.';
            i++;
            table[j][i] = ' ';
            i++;

            table[j][i] = '.';
            i++;
            table[j][i] = '-';
            i++;
            for (int text_i = 0; text_i < strlen(current_task->name); text_i++)
            {
                table[j][i] = '-';
                i++;
            }
            table[j][i] = '-';
            i++;
            table[j][i] = '.';
            i++;
            table[j][i] = ' ';
            i++;
            table[j][i] = '.';
            i++;
            table[j][i] = '-';
            i++;
            for (int text_i = 0; text_i < strlen(priority); text_i++)
            {
                table[j][i] = '-';
                i++;
            }
            table[j][i] = '-';
            i++;
            table[j][i] = '.';
            i++;
            table[j][i] = ' ';
            i++;
            table[j][i] = '.';
            i++;
            table[j][i] = '-';
            i++;
            for (int text_i = 0; text_i < strlen(deadline); text_i++)
            {
                table[j][i] = '-';
                i++;
            }
            table[j][i] = '-';
            i++;
            table[j][i] = '.';
            i++;
        }

        {
            // line 1
            int j = 1;
            int i = 0;
            i += 7;

            table[j][i] = '|';
            i++;
            table[j][i] = ' ';
            i++;
            for (int text_i = 0; text_i < strlen(number_str); text_i++)
            {
                table[j][i] = number_str[text_i];
                i++;
            }
            table[j][i] = ' ';
            i++;
            table[j][i] = '|';
            i++;
            table[j][i] = ' ';
            i++;

            table[j][i] = '|';
            i++;
            table[j][i] = ' ';
            i++;
            for (int text_i = 0; text_i < strlen(current_task->name); text_i++)
            {
                table[j][i] = current_task->name[text_i];
                i++;
            }
            table[j][i] = ' ';
            i++;
            table[j][i] = '|';
            i++;
            table[j][i] = ' ';
            i++;
            table[j][i] = '|';
            i++;
            table[j][i] = ' ';
            i++;
            for (int text_i = 0; text_i < strlen(priority); text_i++)
            {
                table[j][i] = priority[text_i];
                i++;
            }
            table[j][i] = ' ';
            i++;
            table[j][i] = '|';
            i++;
            table[j][i] = ' ';
            i++;
            table[j][i] = '|';
            i++;
            table[j][i] = ' ';
            i++;
            for (int text_i = 0; text_i < strlen(deadline); text_i++)
            {
                table[j][i] = deadline[text_i];
                i++;
            }
            table[j][i] = ' ';
            i++;
            table[j][i] = '|';
            i++;
        }

        {
            // line 2
            int j = 2;
            int i = 0;
            i += 7;

            table[j][i] = '\'';
            i++;
            table[j][i] = '-';
            i++;
            for (int text_i = 0; text_i < strlen(number_str); text_i++)
            {
                table[j][i] = '-';
                i++;
            }
            table[j][i] = '-';
            i++;
            table[j][i] = '\'';
            i++;
            table[j][i] = ' ';
            i++;

            table[j][i] = '\'';
            i++;
            table[j][i] = '-';
            i++;
            for (int text_i = 0; text_i < strlen(current_task->name); text_i++)
            {
                table[j][i] = '-';
                i++;
            }
            table[j][i] = '-';
            i++;
            table[j][i] = '\'';
            i++;
            table[j][i] = ' ';
            i++;
            table[j][i] = '\'';
            i++;
            table[j][i] = '-';
            i++;
            for (int text_i = 0; text_i < strlen(priority); text_i++)
            {
                table[j][i] = '-';
                i++;
            }
            table[j][i] = '-';
            i++;
            table[j][i] = '\'';
            i++;
            table[j][i] = ' ';
            i++;
            table[j][i] = '\'';
            i++;
            table[j][i] = '-';
            i++;
            for (int text_i = 0; text_i < strlen(deadline); text_i++)
            {
                table[j][i] = '-';
                i++;
            }
            table[j][i] = '-';
            i++;
            table[j][i] = '\'';
            i++;
        }

        /* ShowTables */
        for (int j = 0; j < 3; j++)
        {
            for (int i = 0; i < 121; i++)
            {
                printf("%c", table[j][i]);
            }
            printf("\n");
        }

        current_task = current_task->next_task;
    }

    /* CreateDisplay */
    char footer_display[2][121] = {
        {"| '------------------------------------------------------------------------------------------------------------------' |"},
        {"'----------------------------------------------------------------------------------------------------------------------'"}};

    /* ShowDisplay */
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < 121; i++)
        {
            printf("%c", footer_display[j][i]);
        }
        printf("\n");
    }
}

void tasks_delete_menu(task *head, char username[MAX_LEN], int date, int time)
{
    /* CreateDisplay */
    char header_display[11][121] = {
        {".----------------------------------------------------------------------------------------------------------------------."},
        {"| .---------------. .-----------------------. .-----------------------------------------..---------------------------. |"},
        {"| |               | |  DBOARD               | |  GUIDE:                                 ||             |   _   _     | |"},
        {"| |     /\\_/\\     | | USER-NAME:            | | input number of task you want to        ||       . | . x .|.|-|.|    | |"},
        {"| |    ( #.# )    | | DATE:                 | | create                                  ||    |\\ ./.\\-/.\\-|.|.|.|    | |"},
        {"| |     > ^ <     | | TIME:                 | |                                         || ~~~|.|_|.|_|.|.|.|_|.|~~~ | |"},
        {"| '---------------' '-----------------------' '-----------------------------------------''---------------------------' |"},
        {"| .------------------------------------------------------------------------------------------------------------------. |"},
        {"| | .---------------------------.                                                                                    | |"},
        {"| | |  Tasks:                   |                                                                                    | |"},
        {"| | '---------------------------'                                                                                    | |"}};

    /* Date and Time */
    int date_year = date / 10000;
    int date_month = (date / 100) - (date_year * 100);
    int date_day = date % 100;

    int time_hour = time / 100;
    int time_min = time % 100;

    header_display[4][28] = ((char)(date_year / 10) + 48);
    header_display[4][29] = ((char)(date_year % 10) + 48);
    header_display[4][30] = '/';
    header_display[4][31] = ((char)(date_month / 10) + 48);
    header_display[4][32] = ((char)(date_month % 10) + 48);
    header_display[4][33] = '/';
    header_display[4][34] = ((char)(date_day / 10) + 48);
    header_display[4][35] = ((char)(date_day % 10) + 48);

    header_display[5][28] = ((char)(time_hour / 10) + 48);
    header_display[5][29] = ((char)(time_hour % 10) + 48);
    header_display[5][30] = ':';
    header_display[5][31] = ((char)(time_min / 10) + 48);
    header_display[5][32] = ((char)(time_min % 10) + 48);

    /* Username */
    for (int i = 0; i < 10; i++)
    {
        if (username[i] != '\0')
        {
            header_display[3][(32 + i)] = username[i];
        }
    }

    /* ShowDisplay */
    for (int j = 0; j < 11; j++)
    {
        for (int i = 0; i < 121; i++)
        {
            printf("%c", header_display[j][i]);
        }
        printf("\n");
    }

    /* CreateTables */
    task *current_task = head;
    int number = 0;
    while (current_task != NULL)
    {
        // priority to text
        char priority[16];
        if (current_task->priority == 1)
        {
            char tmp_priority[16] = "Low";
            strcpy(priority, tmp_priority);
        }
        else if (current_task->priority == 2)
        {
            char tmp_priority[16] = "Medium";
            strcpy(priority, tmp_priority);
        }
        else if (current_task->priority == 3)
        {
            char tmp_priority[16] = "High";
            strcpy(priority, tmp_priority);
        }
        else if (current_task->priority == 0)
        {
            char tmp_priority[16] = "Priority";
            strcpy(priority, tmp_priority);
        }
        else
        {
            char tmp_priority[16] = "Unknown";
            strcpy(priority, tmp_priority);
        }

        // deadline to text

        char deadline[9] = "00/00/00";
        int year = current_task->deadline / 10000;
        int month = (current_task->deadline / 100) - (year * 100);
        int day = current_task->deadline % 100;

        deadline[0] = ((char)(year / 10) + 48);
        deadline[1] = ((char)(year % 10) + 48);
        deadline[3] = ((char)(month / 10) + 48);
        deadline[4] = ((char)(month % 10) + 48);
        deadline[6] = ((char)(day / 10) + 48);
        deadline[7] = ((char)(day % 10) + 48);

        // name to name and index
        char number_str[8];
        sprintf(number_str, "%d.", number);
        number++;

        char table[3][121] = {
            {"| |                                                                                                                  | |"},
            {"| |                                                                                                                  | |"},
            {"| |                                                                                                                  | |"}};
        {
            // line 0
            int j = 0;
            int i = 0;
            i += 7;

            table[j][i] = '.';
            i++;
            table[j][i] = '-';
            i++;
            for (int text_i = 0; text_i < strlen(number_str); text_i++)
            {
                table[j][i] = '-';
                i++;
            }
            table[j][i] = '-';
            i++;
            table[j][i] = '.';
            i++;
            table[j][i] = ' ';
            i++;

            table[j][i] = '.';
            i++;
            table[j][i] = '-';
            i++;
            for (int text_i = 0; text_i < strlen(current_task->name); text_i++)
            {
                table[j][i] = '-';
                i++;
            }
            table[j][i] = '-';
            i++;
            table[j][i] = '.';
            i++;
            table[j][i] = ' ';
            i++;
            table[j][i] = '.';
            i++;
            table[j][i] = '-';
            i++;
            for (int text_i = 0; text_i < strlen(priority); text_i++)
            {
                table[j][i] = '-';
                i++;
            }
            table[j][i] = '-';
            i++;
            table[j][i] = '.';
            i++;
            table[j][i] = ' ';
            i++;
            table[j][i] = '.';
            i++;
            table[j][i] = '-';
            i++;
            for (int text_i = 0; text_i < strlen(deadline); text_i++)
            {
                table[j][i] = '-';
                i++;
            }
            table[j][i] = '-';
            i++;
            table[j][i] = '.';
            i++;
        }

        {
            // line 1
            int j = 1;
            int i = 0;
            i += 7;

            table[j][i] = '|';
            i++;
            table[j][i] = ' ';
            i++;
            for (int text_i = 0; text_i < strlen(number_str); text_i++)
            {
                table[j][i] = number_str[text_i];
                i++;
            }
            table[j][i] = ' ';
            i++;
            table[j][i] = '|';
            i++;
            table[j][i] = ' ';
            i++;

            table[j][i] = '|';
            i++;
            table[j][i] = ' ';
            i++;
            for (int text_i = 0; text_i < strlen(current_task->name); text_i++)
            {
                table[j][i] = current_task->name[text_i];
                i++;
            }
            table[j][i] = ' ';
            i++;
            table[j][i] = '|';
            i++;
            table[j][i] = ' ';
            i++;
            table[j][i] = '|';
            i++;
            table[j][i] = ' ';
            i++;
            for (int text_i = 0; text_i < strlen(priority); text_i++)
            {
                table[j][i] = priority[text_i];
                i++;
            }
            table[j][i] = ' ';
            i++;
            table[j][i] = '|';
            i++;
            table[j][i] = ' ';
            i++;
            table[j][i] = '|';
            i++;
            table[j][i] = ' ';
            i++;
            for (int text_i = 0; text_i < strlen(deadline); text_i++)
            {
                table[j][i] = deadline[text_i];
                i++;
            }
            table[j][i] = ' ';
            i++;
            table[j][i] = '|';
            i++;
        }

        {
            // line 2
            int j = 2;
            int i = 0;
            i += 7;

            table[j][i] = '\'';
            i++;
            table[j][i] = '-';
            i++;
            for (int text_i = 0; text_i < strlen(number_str); text_i++)
            {
                table[j][i] = '-';
                i++;
            }
            table[j][i] = '-';
            i++;
            table[j][i] = '\'';
            i++;
            table[j][i] = ' ';
            i++;

            table[j][i] = '\'';
            i++;
            table[j][i] = '-';
            i++;
            for (int text_i = 0; text_i < strlen(current_task->name); text_i++)
            {
                table[j][i] = '-';
                i++;
            }
            table[j][i] = '-';
            i++;
            table[j][i] = '\'';
            i++;
            table[j][i] = ' ';
            i++;
            table[j][i] = '\'';
            i++;
            table[j][i] = '-';
            i++;
            for (int text_i = 0; text_i < strlen(priority); text_i++)
            {
                table[j][i] = '-';
                i++;
            }
            table[j][i] = '-';
            i++;
            table[j][i] = '\'';
            i++;
            table[j][i] = ' ';
            i++;
            table[j][i] = '\'';
            i++;
            table[j][i] = '-';
            i++;
            for (int text_i = 0; text_i < strlen(deadline); text_i++)
            {
                table[j][i] = '-';
                i++;
            }
            table[j][i] = '-';
            i++;
            table[j][i] = '\'';
            i++;
        }

        /* ShowTables */
        for (int j = 0; j < 3; j++)
        {
            for (int i = 0; i < 121; i++)
            {
                printf("%c", table[j][i]);
            }
            printf("\n");
        }

        current_task = current_task->next_task;
    }

    /* CreateDisplay */
    char footer_display[2][121] = {
        {"| '------------------------------------------------------------------------------------------------------------------' |"},
        {"'----------------------------------------------------------------------------------------------------------------------'"}};

    /* ShowDisplay */
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < 121; i++)
        {
            printf("%c", footer_display[j][i]);
        }
        printf("\n");
    }
}

void tasks_edit_menu(task *head, char username[MAX_LEN], int date, int time)
{
    /* CreateDisplay */
    char header_display[11][121] = {
        {".----------------------------------------------------------------------------------------------------------------------."},
        {"| .---------------. .-----------------------. .-----------------------------------------..---------------------------. |"},
        {"| |               | |  DBOARD               | |  GUIDE:                                 ||             |   _   _     | |"},
        {"| |     /\\_/\\     | | USER-NAME:            | | input number of task you want to        ||       . | . x .|.|-|.|    | |"},
        {"| |    ( =.= )    | | DATE:                 | | edit                                    ||    |\\ ./.\\-/.\\-|.|.|.|    | |"},
        {"| |     > ^ <     | | TIME:                 | |                                         || ~~~|.|_|.|_|.|.|.|_|.|~~~ | |"},
        {"| '---------------' '-----------------------' '-----------------------------------------''---------------------------' |"},
        {"| .------------------------------------------------------------------------------------------------------------------. |"},
        {"| | .---------------------------.                                                                                    | |"},
        {"| | |  Tasks:                   |                                                                                    | |"},
        {"| | '---------------------------'                                                                                    | |"}};

    /* Date and Time */
    int date_year = date / 10000;
    int date_month = (date / 100) - (date_year * 100);
    int date_day = date % 100;

    int time_hour = time / 100;
    int time_min = time % 100;

    header_display[4][28] = ((char)(date_year / 10) + 48);
    header_display[4][29] = ((char)(date_year % 10) + 48);
    header_display[4][30] = '/';
    header_display[4][31] = ((char)(date_month / 10) + 48);
    header_display[4][32] = ((char)(date_month % 10) + 48);
    header_display[4][33] = '/';
    header_display[4][34] = ((char)(date_day / 10) + 48);
    header_display[4][35] = ((char)(date_day % 10) + 48);

    header_display[5][28] = ((char)(time_hour / 10) + 48);
    header_display[5][29] = ((char)(time_hour % 10) + 48);
    header_display[5][30] = ':';
    header_display[5][31] = ((char)(time_min / 10) + 48);
    header_display[5][32] = ((char)(time_min % 10) + 48);

    /* Username */
    for (int i = 0; i < 10; i++)
    {
        if (username[i] != '\0')
        {
            header_display[3][(32 + i)] = username[i];
        }
    }

    /* ShowDisplay */
    for (int j = 0; j < 11; j++)
    {
        for (int i = 0; i < 121; i++)
        {
            printf("%c", header_display[j][i]);
        }
        printf("\n");
    }

    /* CreateTables */
    task *current_task = head;
    int number = 0;
    while (current_task != NULL)
    {
        // priority to text
        char priority[16];
        if (current_task->priority == 1)
        {
            char tmp_priority[16] = "Low";
            strcpy(priority, tmp_priority);
        }
        else if (current_task->priority == 2)
        {
            char tmp_priority[16] = "Medium";
            strcpy(priority, tmp_priority);
        }
        else if (current_task->priority == 3)
        {
            char tmp_priority[16] = "High";
            strcpy(priority, tmp_priority);
        }
        else if (current_task->priority == 0)
        {
            char tmp_priority[16] = "Priority";
            strcpy(priority, tmp_priority);
        }
        else
        {
            char tmp_priority[16] = "Unknown";
            strcpy(priority, tmp_priority);
        }

        // deadline to text

        char deadline[9] = "00/00/00";
        int year = current_task->deadline / 10000;
        int month = (current_task->deadline / 100) - (year * 100);
        int day = current_task->deadline % 100;

        deadline[0] = ((char)(year / 10) + 48);
        deadline[1] = ((char)(year % 10) + 48);
        deadline[3] = ((char)(month / 10) + 48);
        deadline[4] = ((char)(month % 10) + 48);
        deadline[6] = ((char)(day / 10) + 48);
        deadline[7] = ((char)(day % 10) + 48);

        // name to name and index
        char number_str[8];
        sprintf(number_str, "%d.", number);
        number++;

        char table[3][121] = {
            {"| |                                                                                                                  | |"},
            {"| |                                                                                                                  | |"},
            {"| |                                                                                                                  | |"}};
        {
            // line 0
            int j = 0;
            int i = 0;
            i += 7;

            table[j][i] = '.';
            i++;
            table[j][i] = '-';
            i++;
            for (int text_i = 0; text_i < strlen(number_str); text_i++)
            {
                table[j][i] = '-';
                i++;
            }
            table[j][i] = '-';
            i++;
            table[j][i] = '.';
            i++;
            table[j][i] = ' ';
            i++;

            table[j][i] = '.';
            i++;
            table[j][i] = '-';
            i++;
            for (int text_i = 0; text_i < strlen(current_task->name); text_i++)
            {
                table[j][i] = '-';
                i++;
            }
            table[j][i] = '-';
            i++;
            table[j][i] = '.';
            i++;
            table[j][i] = ' ';
            i++;
            table[j][i] = '.';
            i++;
            table[j][i] = '-';
            i++;
            for (int text_i = 0; text_i < strlen(priority); text_i++)
            {
                table[j][i] = '-';
                i++;
            }
            table[j][i] = '-';
            i++;
            table[j][i] = '.';
            i++;
            table[j][i] = ' ';
            i++;
            table[j][i] = '.';
            i++;
            table[j][i] = '-';
            i++;
            for (int text_i = 0; text_i < strlen(deadline); text_i++)
            {
                table[j][i] = '-';
                i++;
            }
            table[j][i] = '-';
            i++;
            table[j][i] = '.';
            i++;
        }

        {
            // line 1
            int j = 1;
            int i = 0;
            i += 7;

            table[j][i] = '|';
            i++;
            table[j][i] = ' ';
            i++;
            for (int text_i = 0; text_i < strlen(number_str); text_i++)
            {
                table[j][i] = number_str[text_i];
                i++;
            }
            table[j][i] = ' ';
            i++;
            table[j][i] = '|';
            i++;
            table[j][i] = ' ';
            i++;

            table[j][i] = '|';
            i++;
            table[j][i] = ' ';
            i++;
            for (int text_i = 0; text_i < strlen(current_task->name); text_i++)
            {
                table[j][i] = current_task->name[text_i];
                i++;
            }
            table[j][i] = ' ';
            i++;
            table[j][i] = '|';
            i++;
            table[j][i] = ' ';
            i++;
            table[j][i] = '|';
            i++;
            table[j][i] = ' ';
            i++;
            for (int text_i = 0; text_i < strlen(priority); text_i++)
            {
                table[j][i] = priority[text_i];
                i++;
            }
            table[j][i] = ' ';
            i++;
            table[j][i] = '|';
            i++;
            table[j][i] = ' ';
            i++;
            table[j][i] = '|';
            i++;
            table[j][i] = ' ';
            i++;
            for (int text_i = 0; text_i < strlen(deadline); text_i++)
            {
                table[j][i] = deadline[text_i];
                i++;
            }
            table[j][i] = ' ';
            i++;
            table[j][i] = '|';
            i++;
        }

        {
            // line 2
            int j = 2;
            int i = 0;
            i += 7;

            table[j][i] = '\'';
            i++;
            table[j][i] = '-';
            i++;
            for (int text_i = 0; text_i < strlen(number_str); text_i++)
            {
                table[j][i] = '-';
                i++;
            }
            table[j][i] = '-';
            i++;
            table[j][i] = '\'';
            i++;
            table[j][i] = ' ';
            i++;

            table[j][i] = '\'';
            i++;
            table[j][i] = '-';
            i++;
            for (int text_i = 0; text_i < strlen(current_task->name); text_i++)
            {
                table[j][i] = '-';
                i++;
            }
            table[j][i] = '-';
            i++;
            table[j][i] = '\'';
            i++;
            table[j][i] = ' ';
            i++;
            table[j][i] = '\'';
            i++;
            table[j][i] = '-';
            i++;
            for (int text_i = 0; text_i < strlen(priority); text_i++)
            {
                table[j][i] = '-';
                i++;
            }
            table[j][i] = '-';
            i++;
            table[j][i] = '\'';
            i++;
            table[j][i] = ' ';
            i++;
            table[j][i] = '\'';
            i++;
            table[j][i] = '-';
            i++;
            for (int text_i = 0; text_i < strlen(deadline); text_i++)
            {
                table[j][i] = '-';
                i++;
            }
            table[j][i] = '-';
            i++;
            table[j][i] = '\'';
            i++;
        }

        /* ShowTables */
        for (int j = 0; j < 3; j++)
        {
            for (int i = 0; i < 121; i++)
            {
                printf("%c", table[j][i]);
            }
            printf("\n");
        }

        current_task = current_task->next_task;
    }

    /* CreateDisplay */
    char footer_display[2][121] = {
        {"| '------------------------------------------------------------------------------------------------------------------' |"},
        {"'----------------------------------------------------------------------------------------------------------------------'"}};

    /* ShowDisplay */
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < 121; i++)
        {
            printf("%c", footer_display[j][i]);
        }
        printf("\n");
    }
}

void tasks_sort_menu(char board_name[MAX_LEN], char list_name[MAX_LEN], char username[MAX_LEN], int date, int time)
{
    /* CreateDisplay */
    char header_display[7][121] = {
        {".----------------------------------------------------------------------------------------------------------------------."},
        {"| .---------------. .-----------------------. .-----------------------------------------..---------------------------. |"},
        {"| |               | |  DBOARD               | |  GUIDE:                                 ||             |   _   _     | |"},
        {"| |     /\\_/\\     | | USER-NAME:            | | input number of your order              ||       . | . x .|.|-|.|    | |"},
        {"| |    ( @.@ )    | | DATE:                 | |                                         ||    |\\ ./.\\-/.\\-|.|.|.|    | |"},
        {"| |     > ^ <     | | TIME:                 | |                                         || ~~~|.|_|.|_|.|.|.|_|.|~~~ | |"},
        {"| '---------------' '-----------------------' '-----------------------------------------''---------------------------' |"}};

    /* Date and Time */
    int date_year = date / 10000;
    int date_month = (date / 100) - (date_year * 100);
    int date_day = date % 100;

    int time_hour = time / 100;
    int time_min = time % 100;

    header_display[4][28] = ((char)(date_year / 10) + 48);
    header_display[4][29] = ((char)(date_year % 10) + 48);
    header_display[4][30] = '/';
    header_display[4][31] = ((char)(date_month / 10) + 48);
    header_display[4][32] = ((char)(date_month % 10) + 48);
    header_display[4][33] = '/';
    header_display[4][34] = ((char)(date_day / 10) + 48);
    header_display[4][35] = ((char)(date_day % 10) + 48);

    header_display[5][28] = ((char)(time_hour / 10) + 48);
    header_display[5][29] = ((char)(time_hour % 10) + 48);
    header_display[5][30] = ':';
    header_display[5][31] = ((char)(time_min / 10) + 48);
    header_display[5][32] = ((char)(time_min % 10) + 48);

    /* Username */

    for (int i = 0; i < 10; i++)
    {
        if (username[i] != '\0')
        {
            header_display[3][(32 + i)] = username[i];
        }
    }

    /* ShowDisplay */
    for (int j = 0; j < 7; j++)
    {
        for (int i = 0; i < 121; i++)
        {
            printf("%c", header_display[j][i]);
        }
        printf("\n");
    }

    /* CreateDisplay */
    char body_display[21][121] = {
        {"| .-----. .----------------------------------------------------------------------------------------------------------. |"},
        {"| | .-. | | .------------------------------------------------------------------------------------------------------. | |"},
        {"| | | | | | |  1. Sort Tasks Name Ascending                                                                        | | |"},
        {"| | | | | | '------------------------------------------------------------------------------------------------------' | |"},
        {"| | | | | | .------------------------------------------------------------------------------------------------------. | |"},
        {"| | | | | | |  2. Sort Tasks Name Descending                                                                       | | |"},
        {"| | '-' | | '------------------------------------------------------------------------------------------------------' | |"},
        {"| | .-. | | .------------------------------------------------------------------------------------------------------. | |"},
        {"| | | | | | |  3. Sort Tasks Priority Ascending                                                                    | | |"},
        {"| | | | | | '------------------------------------------------------------------------------------------------------' | |"},
        {"| | | | | | .------------------------------------------------------------------------------------------------------. | |"},
        {"| | | | | | |  4. Sort Tasks Priority Descending                                                                   | | |"},
        {"| | | | | | '------------------------------------------------------------------------------------------------------' | |"},
        {"| | | | | | .------------------------------------------------------------------------------------------------------. | |"},
        {"| | | | | | |  5. Sort Tasks Deadline Ascending                                                                    | | |"},
        {"| | | | | | '------------------------------------------------------------------------------------------------------' | |"},
        {"| | | | | | .------------------------------------------------------------------------------------------------------. | |"},
        {"| | | | | | |  6. Sort Tasks Deadline Descending                                                                   | | |"},
        {"| | | | | | '------------------------------------------------------------------------------------------------------' | |"},
        {"| | '-' | |                                                                                                          | |"}};

    for (int i = 0; i < 4; i++)
    {
        if (board_name[i] != '\0')
        {
            body_display[(2 + i)][5] = board_name[i];
        }
    }

    for (int i = 0; i < 11; i++)
    {
        if (list_name[i] != '\0')
        {
            body_display[(8 + i)][5] = list_name[i];
        }
    }

    /* ShowDisplay */
    for (int j = 0; j < 20; j++)
    {
        for (int i = 0; i < 121; i++)
        {
            printf("%c", body_display[j][i]);
        }
        printf("\n");
    }

    /* CreateDisplay */
    char footer_display[2][121] = {
        {"| '-----' '----------------------------------------------------------------------------------------------------------' |"},
        {"'----------------------------------------------------------------------------------------------------------------------'"}};

    /* ShowDisplay */
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < 121; i++)
        {
            printf("%c", footer_display[j][i]);
        }
        printf("\n");
    }
}

void tasks_move_menu(task *head, char username[MAX_LEN], int date, int time)
{
    /* CreateDisplay */
    char header_display[11][121] = {
        {".----------------------------------------------------------------------------------------------------------------------."},
        {"| .---------------. .-----------------------. .-----------------------------------------..---------------------------. |"},
        {"| |               | |  DBOARD               | |  GUIDE:                                 ||             |   _   _     | |"},
        {"| |     /\\_/\\     | | USER-NAME:            | | input number of task you want to        ||       . | . x .|.|-|.|    | |"},
        {"| |    ( '.' )    | | DATE:                 | | move                                    ||    |\\ ./.\\-/.\\-|.|.|.|    | |"},
        {"| |     > ^ <     | | TIME:                 | |                                         || ~~~|.|_|.|_|.|.|.|_|.|~~~ | |"},
        {"| '---------------' '-----------------------' '-----------------------------------------''---------------------------' |"},
        {"| .------------------------------------------------------------------------------------------------------------------. |"},
        {"| | .---------------------------.                                                                                    | |"},
        {"| | |  Tasks:                   |                                                                                    | |"},
        {"| | '---------------------------'                                                                                    | |"}};

    /* Date and Time */
    int date_year = date / 10000;
    int date_month = (date / 100) - (date_year * 100);
    int date_day = date % 100;

    int time_hour = time / 100;
    int time_min = time % 100;

    header_display[4][28] = ((char)(date_year / 10) + 48);
    header_display[4][29] = ((char)(date_year % 10) + 48);
    header_display[4][30] = '/';
    header_display[4][31] = ((char)(date_month / 10) + 48);
    header_display[4][32] = ((char)(date_month % 10) + 48);
    header_display[4][33] = '/';
    header_display[4][34] = ((char)(date_day / 10) + 48);
    header_display[4][35] = ((char)(date_day % 10) + 48);

    header_display[5][28] = ((char)(time_hour / 10) + 48);
    header_display[5][29] = ((char)(time_hour % 10) + 48);
    header_display[5][30] = ':';
    header_display[5][31] = ((char)(time_min / 10) + 48);
    header_display[5][32] = ((char)(time_min % 10) + 48);

    /* Username */
    for (int i = 0; i < 10; i++)
    {
        if (username[i] != '\0')
        {
            header_display[3][(32 + i)] = username[i];
        }
    }

    /* ShowDisplay */
    for (int j = 0; j < 11; j++)
    {
        for (int i = 0; i < 121; i++)
        {
            printf("%c", header_display[j][i]);
        }
        printf("\n");
    }

    /* CreateTables */
    task *current_task = head;
    int number = 0;
    while (current_task != NULL)
    {
        // priority to text
        char priority[16];
        if (current_task->priority == 1)
        {
            char tmp_priority[16] = "Low";
            strcpy(priority, tmp_priority);
        }
        else if (current_task->priority == 2)
        {
            char tmp_priority[16] = "Medium";
            strcpy(priority, tmp_priority);
        }
        else if (current_task->priority == 3)
        {
            char tmp_priority[16] = "High";
            strcpy(priority, tmp_priority);
        }
        else if (current_task->priority == 0)
        {
            char tmp_priority[16] = "Priority";
            strcpy(priority, tmp_priority);
        }
        else
        {
            char tmp_priority[16] = "Unknown";
            strcpy(priority, tmp_priority);
        }

        // deadline to text

        char deadline[9] = "00/00/00";
        int year = current_task->deadline / 10000;
        int month = (current_task->deadline / 100) - (year * 100);
        int day = current_task->deadline % 100;

        deadline[0] = ((char)(year / 10) + 48);
        deadline[1] = ((char)(year % 10) + 48);
        deadline[3] = ((char)(month / 10) + 48);
        deadline[4] = ((char)(month % 10) + 48);
        deadline[6] = ((char)(day / 10) + 48);
        deadline[7] = ((char)(day % 10) + 48);

        // name to name and index
        char number_str[8];
        sprintf(number_str, "%d.", number);
        number++;

        char table[3][121] = {
            {"| |                                                                                                                  | |"},
            {"| |                                                                                                                  | |"},
            {"| |                                                                                                                  | |"}};
        {
            // line 0
            int j = 0;
            int i = 0;
            i += 7;

            table[j][i] = '.';
            i++;
            table[j][i] = '-';
            i++;
            for (int text_i = 0; text_i < strlen(number_str); text_i++)
            {
                table[j][i] = '-';
                i++;
            }
            table[j][i] = '-';
            i++;
            table[j][i] = '.';
            i++;
            table[j][i] = ' ';
            i++;

            table[j][i] = '.';
            i++;
            table[j][i] = '-';
            i++;
            for (int text_i = 0; text_i < strlen(current_task->name); text_i++)
            {
                table[j][i] = '-';
                i++;
            }
            table[j][i] = '-';
            i++;
            table[j][i] = '.';
            i++;
            table[j][i] = ' ';
            i++;
            table[j][i] = '.';
            i++;
            table[j][i] = '-';
            i++;
            for (int text_i = 0; text_i < strlen(priority); text_i++)
            {
                table[j][i] = '-';
                i++;
            }
            table[j][i] = '-';
            i++;
            table[j][i] = '.';
            i++;
            table[j][i] = ' ';
            i++;
            table[j][i] = '.';
            i++;
            table[j][i] = '-';
            i++;
            for (int text_i = 0; text_i < strlen(deadline); text_i++)
            {
                table[j][i] = '-';
                i++;
            }
            table[j][i] = '-';
            i++;
            table[j][i] = '.';
            i++;
        }

        {
            // line 1
            int j = 1;
            int i = 0;
            i += 7;

            table[j][i] = '|';
            i++;
            table[j][i] = ' ';
            i++;
            for (int text_i = 0; text_i < strlen(number_str); text_i++)
            {
                table[j][i] = number_str[text_i];
                i++;
            }
            table[j][i] = ' ';
            i++;
            table[j][i] = '|';
            i++;
            table[j][i] = ' ';
            i++;

            table[j][i] = '|';
            i++;
            table[j][i] = ' ';
            i++;
            for (int text_i = 0; text_i < strlen(current_task->name); text_i++)
            {
                table[j][i] = current_task->name[text_i];
                i++;
            }
            table[j][i] = ' ';
            i++;
            table[j][i] = '|';
            i++;
            table[j][i] = ' ';
            i++;
            table[j][i] = '|';
            i++;
            table[j][i] = ' ';
            i++;
            for (int text_i = 0; text_i < strlen(priority); text_i++)
            {
                table[j][i] = priority[text_i];
                i++;
            }
            table[j][i] = ' ';
            i++;
            table[j][i] = '|';
            i++;
            table[j][i] = ' ';
            i++;
            table[j][i] = '|';
            i++;
            table[j][i] = ' ';
            i++;
            for (int text_i = 0; text_i < strlen(deadline); text_i++)
            {
                table[j][i] = deadline[text_i];
                i++;
            }
            table[j][i] = ' ';
            i++;
            table[j][i] = '|';
            i++;
        }

        {
            // line 2
            int j = 2;
            int i = 0;
            i += 7;

            table[j][i] = '\'';
            i++;
            table[j][i] = '-';
            i++;
            for (int text_i = 0; text_i < strlen(number_str); text_i++)
            {
                table[j][i] = '-';
                i++;
            }
            table[j][i] = '-';
            i++;
            table[j][i] = '\'';
            i++;
            table[j][i] = ' ';
            i++;

            table[j][i] = '\'';
            i++;
            table[j][i] = '-';
            i++;
            for (int text_i = 0; text_i < strlen(current_task->name); text_i++)
            {
                table[j][i] = '-';
                i++;
            }
            table[j][i] = '-';
            i++;
            table[j][i] = '\'';
            i++;
            table[j][i] = ' ';
            i++;
            table[j][i] = '\'';
            i++;
            table[j][i] = '-';
            i++;
            for (int text_i = 0; text_i < strlen(priority); text_i++)
            {
                table[j][i] = '-';
                i++;
            }
            table[j][i] = '-';
            i++;
            table[j][i] = '\'';
            i++;
            table[j][i] = ' ';
            i++;
            table[j][i] = '\'';
            i++;
            table[j][i] = '-';
            i++;
            for (int text_i = 0; text_i < strlen(deadline); text_i++)
            {
                table[j][i] = '-';
                i++;
            }
            table[j][i] = '-';
            i++;
            table[j][i] = '\'';
            i++;
        }

        /* ShowTables */
        for (int j = 0; j < 3; j++)
        {
            for (int i = 0; i < 121; i++)
            {
                printf("%c", table[j][i]);
            }
            printf("\n");
        }

        current_task = current_task->next_task;
    }

    /* CreateDisplay */
    char footer_display[2][121] = {
        {"| '------------------------------------------------------------------------------------------------------------------' |"},
        {"'----------------------------------------------------------------------------------------------------------------------'"}};

    /* ShowDisplay */
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < 121; i++)
        {
            printf("%c", footer_display[j][i]);
        }
        printf("\n");
    }
}

void tasks_move_lists_menu(char board_name[MAX_LEN], char username[MAX_LEN], int date, int time)
{
    /* CreateDisplay */
    char header_display[11][121] = {
        {".----------------------------------------------------------------------------------------------------------------------."},
        {"| .---------------. .-----------------------. .-----------------------------------------..---------------------------. |"},
        {"| |               | |  DBOARD               | |  GUIDE:                                 ||             |   _   _     | |"},
        {"| |     /\\_/\\     | | USER-NAME:            | | input name of list you want to move     ||       . | . x .|.|-|.|    | |"},
        {"| |    (  .  )    | | DATE:                 | | task in it                              ||    |\\ ./.\\-/.\\-|.|.|.|    | |"},
        {"| |     > ^ <     | | TIME:                 | |                                         || ~~~|.|_|.|_|.|.|.|_|.|~~~ | |"},
        {"| '---------------' '-----------------------' '-----------------------------------------''---------------------------' |"},
        {"| .------------------------------------------------------------------------------------------------------------------. |"},
        {"| | .-------------------------------------.                                                                          | |"},
        {"| | |  Available Lists:                   |                                                                          | |"},
        {"| | '-------------------------------------'                                                                          | |"}};

    /* Date and Time */
    int date_year = date / 10000;
    int date_month = (date / 100) - (date_year * 100);
    int date_day = date % 100;

    int time_hour = time / 100;
    int time_min = time % 100;

    header_display[4][28] = ((char)(date_year / 10) + 48);
    header_display[4][29] = ((char)(date_year % 10) + 48);
    header_display[4][30] = '/';
    header_display[4][31] = ((char)(date_month / 10) + 48);
    header_display[4][32] = ((char)(date_month % 10) + 48);
    header_display[4][33] = '/';
    header_display[4][34] = ((char)(date_day / 10) + 48);
    header_display[4][35] = ((char)(date_day % 10) + 48);

    header_display[5][28] = ((char)(time_hour / 10) + 48);
    header_display[5][29] = ((char)(time_hour % 10) + 48);
    header_display[5][30] = ':';
    header_display[5][31] = ((char)(time_min / 10) + 48);
    header_display[5][32] = ((char)(time_min % 10) + 48);

    /* Username */
    for (int i = 0; i < 10; i++)
    {
        if (username[i] != '\0')
        {
            header_display[3][(32 + i)] = username[i];
        }
    }

    /* ShowDisplay */
    for (int j = 0; j < 11; j++)
    {
        for (int i = 0; i < 121; i++)
        {
            printf("%c", header_display[j][i]);
        }
        printf("\n");
    }

    /* CreateTables */
    char location[128];
    sprintf(location, ".\\dBoardDB\\Users\\%s\\Locations\\Lists.csv", username);
    FILE *fp = fopen(location, "r");
    if (NULL == fp)
    {
        printf("file can't be opened \n");
    }
    char line[MAX_LINE_LENGTH];
    char current_board_name[MAX_LEN];
    char current_list_name[MAX_LEN];
    while (fgets(line, MAX_LINE_LENGTH, fp))
    {
        sscanf(line, "%[^,],%[^,]\n", current_board_name, current_list_name);
        if (strcmp(current_board_name, board_name) == 0)
        {
            char table[3][121] = {
                {"| | .--------------------------------------------------------------------------------------------------------------. | |"},
                {"| | |                                                                                                              | | |"},
                {"| | '--------------------------------------------------------------------------------------------------------------' | |"}};
            for (int i = 0; i < (strlen(current_list_name) - 1); i++)
            {
                table[1][(6 + i)] = current_list_name[i];
            }
            /* ShowTables */
            for (int j = 0; j < 3; j++)
            {
                for (int i = 0; i < 121; i++)
                {
                    printf("%c", table[j][i]);
                }
                printf("\n");
            }
        }
    }
    fclose(fp);

    /* CreateDisplay */
    char footer_display[2][121] = {
        {"| '------------------------------------------------------------------------------------------------------------------' |"},
        {"'----------------------------------------------------------------------------------------------------------------------'"}};

    /* ShowDisplay */
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < 121; i++)
        {
            printf("%c", footer_display[j][i]);
        }
        printf("\n");
    }
}

void task_show_description(task *current_task, char username[MAX_LEN])
{
    printf("description: \n%s\n", current_task->description);
}

void reminder_panel(char username[MAX_LEN], int date)
{
    /* Reminder */
    printf(".----------------------------------------------------------------------------------------------------------------------.\n");
    printf("	Reminder:\n");

    task *head = NULL;
    task *current_task = NULL;

    char line[MAX_LINE_LENGTH];
    char line_list_name[MAX_LEN];
    char line_board_name[MAX_LEN];
    char deadline[9] = "00/00/00";
    char task_date[MAX_LEN];
    char location[128];
    sprintf(location, ".\\dBoardDB\\Users\\%s\\Locations\\Lists.csv", username);
    FILE *fp = fopen(location, "r");
    if (NULL == fp)
    {
        printf("file can't be opened \n");
    }
    while (fgets(line, MAX_LINE_LENGTH, fp))
    {
        head = NULL;
        sscanf(line, "%[^,],%[^\n]\n", line_board_name, line_list_name);
        head = read_tasks_csv(line_board_name, line_list_name, username);
        current_task = head;
        while (current_task->next_task != NULL)
        {
            current_task = current_task->next_task;
            // priority to text
            char priority[16];
            if (current_task->priority == 1)
            {
                char tmp_priority[16] = "Low";
                strcpy(priority, tmp_priority);
            }
            else if (current_task->priority == 2)
            {
                char tmp_priority[16] = "Medium";
                strcpy(priority, tmp_priority);
            }
            else if (current_task->priority == 3)
            {
                char tmp_priority[16] = "High";
                strcpy(priority, tmp_priority);
            }
            else if (current_task->priority == 0)
            {
                char tmp_priority[16] = "Priority";
                strcpy(priority, tmp_priority);
            }
            else
            {
                char tmp_priority[16] = "Unknown";
                strcpy(priority, tmp_priority);
            }

            // deadline to text
            strcpy(deadline, "00/00/00");
            int year = current_task->deadline / 10000;
            int month = (current_task->deadline / 100) - (year * 100);
            int day = current_task->deadline % 100;

            deadline[0] = ((char)(year / 10) + 48);
            deadline[1] = ((char)(year % 10) + 48);
            deadline[3] = ((char)(month / 10) + 48);
            deadline[4] = ((char)(month % 10) + 48);
            deadline[6] = ((char)(day / 10) + 48);
            deadline[7] = ((char)(day % 10) + 48);

            if (reminder_compare_task(current_task, date))
            {
                printf("	TaskName: %s - ListName: %s - BoardName: %s - Priority: %s - Deadline: %s\n", current_task->name, line_list_name, line_board_name, priority, deadline);
            }
        }
    }
    printf("'----------------------------------------------------------------------------------------------------------------------'\n");
}

/* MAIN */
int main()
{
    int status = 0;

    char board_name[MAX_LEN] = {};
    char list_name[MAX_LEN] = {};
    char username[MAX_LEN] = {};
    char password[MAX_LEN] = {};
    char empty_str[MAX_LEN] = {};

    int inp_num = 0;
    char inp_str[MAX_LEN] = {};

    task *tasks_head = NULL;
    char task_name[32] = {};
    char task_description[512] = {};
    int task_priority = 0;
    int task_deadline = 0;

    task *moved_tasks_head = NULL;
    task *moved_task = NULL;

    int date = system_date();

    while (1)
    {
        int time = system_time();

        Sleep(100);
        system("cls");

        switch (status)
        {
        case 0:
            strcpy(username, empty_str);
            if (login_menu_autoInp(username))
            {
                printf("Successed!\n");
                status = 10;
            }
            else
            {
                printf("Failed!\n");
            }
            break;

        case 10:
            reminder_panel(username, date);
            boards_menu(username, date, time);
            if (num_scan(&inp_num))
            {
                switch (inp_num)
                {
                case 1:
                    status = 11;
                    break;
                case 2:
                    status = 12;
                    break;
                case 3:
                    status = 13;
                    break;
                case 4:
                    status = 14;
                    break;
                case 5:
                    return 0;
                    break;

                default:
                    break;
                }
            }
            else
            {
                return 0;
            }

            break;
        case 11:
            boards_view_menu(username, date, time);
            if (str_scan(board_name))
            {
                status = 20;
            }
            else
            {
                status = 10;
            }
            break;
        case 12:
            boards_create_menu(username, date, time);
            if (str_scan(board_name))
            {
                add_locBoard(board_name, username);
                create_board_folder(board_name, username);
                setup_board(board_name, username);
                system("cls");
                boards_create_menu(username, date, time);
                Sleep(1000);
                status = 10;
            }
            else
            {
                status = 10;
            }
            break;
        case 13:
            boards_delete_menu(username, date, time);
            if (str_scan(board_name))
            {
                del_locBoard(board_name, username);
                delete_board_folder(board_name, username);
                system("cls");
                boards_delete_menu(username, date, time);
                Sleep(1000);
                status = 10;
            }
            else
            {
                status = 10;
            }
            break;
        case 14:
            reminder_panel(username, date);
            set_time_menu(username, date, time);
            if (num_scan(&inp_num))
            {
                date = inp_num;
            }
            else
            {
                status = 10;
            }

            system("cls");
            set_time_menu(username, date, time);
            Sleep(1000);
            status = 10;

            break;

        case 20:
            lists_menu(username, board_name, date, time);
            if (num_scan(&inp_num))
            {
                switch (inp_num)
                {
                case 1:
                    status = 21;
                    break;
                case 2:
                    status = 22;
                    break;
                case 3:
                    status = 23;
                    break;
                case 4:
                    status = 10;
                    break;

                default:
                    break;
                }
            }
            else
            {
                status = 10;
            }
            break;

        case 21:
            lists_view_menu(username, board_name, date, time);
            if (str_scan(list_name))
            {
                tasks_head = read_tasks_csv(board_name, list_name, username);
                status = 30;
            }
            else
            {
                status = 20;
            }
            break;
        case 22:
            lists_create_menu(username, board_name, date, time);
            if (str_scan(list_name))
            {
                create_list_file(board_name, list_name, username);
                add_locList(board_name, list_name, username);
                system("cls");
                lists_create_menu(username, board_name, date, time);
                Sleep(1000);
                status = 20;
            }
            else
            {
                status = 20;
            }
            break;
        case 23:
            lists_delete_menu(username, board_name, date, time);
            if (str_scan(list_name))
            {
                delete_list_file(board_name, list_name, username);
                del_locList(board_name, list_name, username);
                system("cls");
                lists_delete_menu(username, board_name, date, time);
                Sleep(1000);
                status = 20;
            }
            else
            {
                status = 20;
            }
            break;

        case 30:
            tasks_menu(board_name, list_name, username, date, time);
            if (num_scan(&inp_num))
            {
                switch (inp_num)
                {
                case 1:
                    status = 31;
                    break;
                case 2:
                    status = 32;
                    break;
                case 3:
                    status = 33;
                    break;
                case 4:
                    status = 34;
                    break;
                case 5:
                    status = 35;
                    break;
                case 6:
                    status = 36;
                    break;
                }
            }
            else
            {
                free_all_tasks(tasks_head);
                status = 20;
            }
            break;

        case 31:
            tasks_view_menu(tasks_head, username, date, time);
            if (num_scan(&inp_num))
            {
                system("cls");
                task_show_description(search_task_by_index(tasks_head, inp_num), username);
                str_scan(inp_str);
            }
            else
            {
                status = 30;
            }
            break;
        case 32:
            tasks_create_menu(tasks_head, username, date, time);
            if (str32_scan(task_name))
            {
                if (str128_scan(task_description))
                {
                    if (num_scan(&task_priority))
                    {
                        if (num_scan(&task_deadline))
                        {
                            add_task_atEnd(tasks_head, task_name, task_description, task_priority, task_deadline);
                        }
                        else
                        {
                            status = 30;
                        }
                    }
                    else
                    {
                        status = 30;
                    }
                }
                else
                {
                    status = 30;
                }
                write_tasks_csv(tasks_head, board_name, list_name, username);
                system("cls");
                tasks_show_menu(tasks_head, username, date, time);
                Sleep(1000);
                status = 30;
            }
            else
            {
                status = 30;
            }
            break;
        case 33:
            tasks_delete_menu(tasks_head, username, date, time);
            if (num_scan(&inp_num))
            {
                delete_task_byPtr(tasks_head, search_task_by_index(tasks_head, inp_num));
            }
            else
            {
                status = 30;
            }
            write_tasks_csv(tasks_head, board_name, list_name, username);
            system("cls");
            tasks_show_menu(tasks_head, username, date, time);
            Sleep(1000);
            status = 30;
            break;
        case 34:
            tasks_edit_menu(tasks_head, username, date, time);
            if (num_scan(&inp_num))
            {
                edit_task_byPtr_autoInp(search_task_by_index(tasks_head, inp_num));
            }
            else
            {
                status = 30;
            }
            write_tasks_csv(tasks_head, board_name, list_name, username);
            system("cls");
            tasks_show_menu(tasks_head, username, date, time);
            Sleep(1000);
            status = 30;
            break;
        case 35:
            tasks_sort_menu(board_name, list_name, username, date, time);
            if (num_scan(&inp_num))
            {
                switch (inp_num)
                {
                case 1:
                    sort_tasks_name_a(tasks_head);
                    system("cls");
                    tasks_show_menu(tasks_head, username, date, time);
                    write_tasks_csv(tasks_head, board_name, list_name, username);
                    Sleep(1000);
                    status = 30;
                    break;
                case 2:
                    sort_tasks_name_d(tasks_head);
                    system("cls");
                    tasks_show_menu(tasks_head, username, date, time);
                    write_tasks_csv(tasks_head, board_name, list_name, username);
                    Sleep(1000);
                    status = 30;
                    break;
                case 3:
                    sort_tasks_priority_a(tasks_head);
                    system("cls");
                    tasks_show_menu(tasks_head, username, date, time);
                    write_tasks_csv(tasks_head, board_name, list_name, username);
                    Sleep(1000);
                    status = 30;
                    break;
                case 4:
                    sort_tasks_priority_d(tasks_head);
                    system("cls");
                    tasks_show_menu(tasks_head, username, date, time);
                    write_tasks_csv(tasks_head, board_name, list_name, username);
                    Sleep(1000);
                    status = 30;
                    break;
                case 5:
                    sort_tasks_deadline_a(tasks_head);
                    system("cls");
                    tasks_show_menu(tasks_head, username, date, time);
                    write_tasks_csv(tasks_head, board_name, list_name, username);
                    Sleep(1000);
                    status = 30;
                    break;
                case 6:
                    sort_tasks_deadline_d(tasks_head);
                    system("cls");
                    tasks_show_menu(tasks_head, username, date, time);
                    write_tasks_csv(tasks_head, board_name, list_name, username);
                    Sleep(1000);
                    status = 30;
                    break;

                default:
                    break;
                }
            }
            else
            {
                status = 30;
            }
            break;
        case 36:
            tasks_move_menu(tasks_head, username, date, time);
            if (num_scan(&inp_num))
            {
                moved_task = search_task_by_index(tasks_head, inp_num);
                system("cls");
                tasks_move_lists_menu(board_name, username, date, time);
                if (str_scan(inp_str)) // write list_name
                {
                    // add to new list
                    moved_tasks_head = read_tasks_csv(board_name, inp_str, username);
                    add_task_atEnd(moved_tasks_head, moved_task->name, moved_task->description, moved_task->priority, moved_task->deadline);
                    write_tasks_csv(moved_tasks_head, board_name, inp_str, username);

                    // delete from previous list
                    delete_task_byPtr(tasks_head, search_task_by_index(tasks_head, inp_num));
                    write_tasks_csv(tasks_head, board_name, list_name, username);

                    system("cls");
                    tasks_show_menu(tasks_head, username, date, time);
                    Sleep(1000);
                    status = 30;
                }
                else
                {
                    status = 30;
                }
            }
            else
            {
                status = 30;
            }
            break;

        default:
            break;
        }
    }
}