#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Queue.h"

Queue q;

Node** read(char* file_path, int* node_num);
int readHospital(char* file_path, Node **node_list);
int* findNearestHospital(Node* nodes, int node_num, int* distance,int* predecessor, int* path );
void findHospitalAllNodes(Node** all_nodes, int node_num, char* file_path);
void writeOutput(char* file_path, int** path_list, int* distance_list, int node_num, int start, int append);
int main()
{
    char* file_path = "roadNet-CA.txt";
    char* hospital_file = "hospital.txt";
    char* output_file = "output2.txt";
    int node_num,hospital;
    int* distance_list;
    int **path_list;
    Node **node_list;

    q.size = 0;
    q.head = NULL;
    q.tail = NULL;

    node_list = read(file_path,&node_num);
    hospital = readHospital(hospital_file,node_list);
    distance_list = malloc(sizeof(int)*node_num);
    printf("%d nodes loaded\n",node_num);



    findHospitalAllNodes(node_list, node_num,output_file);

    return 0;
}

Node** read(char* file_path, int* node_num){
    //return a list of nodes and number of nodes

    FILE *fp;
    int nodes = 0;
    int node1,node2;
    char* temp;
    Node** node_list;
    Node* temp_node;
    //allocate space for nodes
    node_list = malloc(sizeof(Node*)*MAX_NODE);


    fp = fopen(file_path, "r");
    if(fp == NULL){
        printf("Error opening file\n");
    }
    char line[500];
    while (!feof(fp)){
		if (fgets(line, 499, fp) == NULL)
			break;
        if (line[0]!='#'){
            line[strlen(line)-1] = '\0';
            temp = strtok(line,"\t");
            if (temp!=NULL){
                node1 = atoi(temp);
                temp = strtok(NULL,"\t");
                node2 = atoi(temp);
            }
            else{
                continue;
            }
            while(node1>=nodes || node2>=nodes){
                //create nodes if not already done
                temp_node = malloc(sizeof(Node));
                if (temp_node == NULL){
                    printf("ERROR: no memory\n");
                }
                temp_node->id = nodes;
                temp_node->vertice_num = 0;
                temp_node->hospital = 0;
                node_list[nodes] = temp_node;
                nodes++;
            }
            //printf("nodes: %d\n",nodes);
            //printf("node1: %d, node2: %d\n",node_list[node1]->id,node_list[node2]->id);

            node_list[node1]->vertice[node_list[node1]->vertice_num] = node_list[node2];
            node_list[node1]->vertice_num++;

        }
    }

    fclose(fp);
    *node_num = nodes;
    return node_list;
}

int readHospital(char* file_path, Node **node_list){
    FILE *fp;
    fp = fopen(file_path, "r");
    char temp[100];
    int node;
    int hospital = 0;
    while (!feof(fp)){
        fgets(temp, 499, fp);
        if (temp[0]!='#'){
            node = atoi(temp);
            node_list[node]->hospital = 1;
            hospital ++;
        }
    }

    fclose(fp);
    return hospital;
}

int* findNearestHospital(Node* nodes, int node_num, int* distance,int* predecessor, int* path ){

    Queue q;
    q.size = 0;
    q.head = NULL;
    q.tail = NULL;
    Node* start = nodes;
    int trail = -1;


    if(path == NULL || predecessor == NULL){
        printf("No space\n");

        return NULL;
    }

    int found = 0;

    for(int p = 0;p<node_num;p++){
        predecessor[p] = -1;
    }

    *distance = 0;

    enqueue(&q,nodes);
    do{
        nodes = dequeue(&q);

        if(nodes->hospital == 1){
            found = 1;

            break;
        }

        for(int i = 0;i<nodes->vertice_num;i++){
            if(predecessor[nodes->vertice[i]->id] < 0){
                predecessor[nodes->vertice[i]->id] = nodes->id;
                enqueue(&q,nodes->vertice[i]);
            }
        }
    }while(!isEmptyQueue(&q));

    while(!isEmptyQueue(&q)){
        dequeue(&q);

    }
    trail = nodes->id;

    while(start->id!=trail && found){
        path[*distance] = trail;
        trail = predecessor[trail];
        *distance = *distance+1;
    }
    path[*distance] = start->id;
    *distance = *distance+1;
    if(!found){
        *distance = -1;
    }

    return path;
}

void findHospitalAllNodes(Node** all_nodes, int node_num, char* file_path){
    //all_nodes: array of all_nodes
    //node_num: number of nodes
    //distance_list: array of distance to nearest hospital for each node
    //note: distance_list have to be created by calling function and is assumed to be of length node_num
    //return array of array of path to nearest hospital for each node
    int* predecessor = malloc(sizeof(int)*node_num);
    int distance;
    FILE *fp;
    fp = fopen(file_path, "w");
    int* path = malloc(sizeof(int)*MAX_DISTANCE);
    for(int i = 0; i<node_num; i++){

        //printf("Node %d\n",i);
        findNearestHospital(all_nodes[i], node_num, &distance, predecessor, path);

        fprintf(fp,"%d %d ",i,distance);
        for (int j = distance-1; j>=0; j--){
            fprintf(fp, "%d", path[j]);
            if(j>0){
                fprintf(fp,",");
            }
        }
        fprintf(fp,"\r\n");

    }

    free(path);
    free(predecessor);
    fclose(fp);
}

void writeOutput(char* file_path, int** path_list, int* distance_list, int node_num, int start, int append){
    FILE *fp;
    if (append){
        fp = fopen(file_path, "a");
    }
    else{
        fp = fopen(file_path, "w");
    }

    for(int x = start; x<node_num; x++){
        fprintf(fp,"%d %d ",x,distance_list[x-start]);
        for (int i = distance_list[x-start]-1; i>=0; i--){
            fprintf(fp, "%d",path_list[x-start][i]);
            if(i>0){
                fprintf(fp,",");
            }
            else{
                fprintf(fp,"\n");
            }
        }
    }
    fclose(fp);
}
