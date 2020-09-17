/***************************************************
* COP4530 Programming Assignment 1 - Due 9/16/2020
* Cure Reconstruction using matchings
* Author: Kaedon Hamm (kah16h)
****************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

// Function Declaration
bool not_last(int * flags, int size);
bool vec_sort(const pair<int,double> &a,const pair<int,double> &b);
int * compute_nn_edges();         // Calculates Edges (weight? rank?)
void compute_matching(void);    // Has to compute the array G2


struct Point {
    int x;
    int y;
    int incidents;
    Point() : incidents(0) {};
};

int num_points;
int * G1;                     // Holds nearnest neighbor edges
vector<Point> points;   // Holds inputted points   // Holds inputted points


// Body of program
int main(){
    int x, y;
    char basura;
    cin >> num_points;

    for (int i = 0; i < num_points; i++){
        struct Point point;
        string input;
        cin >> x >> basura >> y;

        point.x = x;
        point.y = y;
        points.push_back(point);
    }

    G1 = compute_nn_edges();
    compute_matching();

    return 1;
}


// Function Descriptions

// Calculates distances and finds the nearest neighbor for each point
int * compute_nn_edges(){
    int * nn_list = new int[points.size()];
    // Loop through all Points in order
    for (int i = 0; i < points.size(); i++){

        // Calculate nn to Point i
        double nn_dist = 0;
        int nn_num;
        for (int j = 0; j < points.size(); j++){
            if (i != j){
                double calc_dist = sqrt(pow((points[i].x - points[j].x), 2) + pow((points[i].y - points[j].y), 2));
                if (nn_dist == 0 || calc_dist < nn_dist){
                    nn_dist = calc_dist;
                    nn_num = j;
                }
            }
        }
        points[nn_num].incidents++;
        nn_list[i] = nn_num;
    }
    return nn_list;
}


// Modified Gale-Shapely Algorithm w/ preference matching
void compute_matching(void){

    // sl-vertices based on incident edge count
    vector<int> sl_vertices;
    for(int i = 0; i < points.size(); i++){
        if (points[i].incidents <= 1){
            sl_vertices.push_back(i);
        }
    }

    vector<vector<pair<int, double> > > p_list;
    for(int i = 0; i < sl_vertices.size(); i++){
        int p1 = i;         // SL-vertex being looked at
        int p2 = G1[i];     // Nearest Neighbor

        vector<pair<int, double> > temp;

        // Create preference list for p1
        for(int j = 0; j < sl_vertices.size(); j++){
            if(j != p1){
                int p3 = sl_vertices[j];        // point p1 is attempting to connect to
                double distance = sqrt(pow((points[p1].x - points[p3].x), 2) + pow((points[p1].y - points[p3].y), 2));
                temp.push_back(make_pair(p3, distance));
            }
        }
        sort(temp.begin(), temp.end(), vec_sort);
        p_list.push_back(temp);
    }


    // Set "visited" array to 0
    int * flags = new int[p_list.size()];
    for(int i =0; i < p_list.size(); i++){
        flags[i] = 0;
    }

    // Prints out results.
    int pt = 0;
    cout << "0" << endl;                            // Begins at 0
    while(not_last(flags, p_list.size())){
        for(int i = 0; i < p_list[pt].size(); i++){
            if(flags[p_list[pt][i].first] != 1){
                flags[pt] = 1;                      // Raise visited flag on previous point
                pt = p_list[pt][i].first;           // Closest distance becomes new focal point
                break;
            }
        }
        cout << pt << endl;
    }
    cout << "0" << endl;                            // Ends at 0
}



// Helper Functions
bool not_last(int * flags, int size){
    int n = 0;
    for(int i = 0; i < size; i++){
        if(flags[i] == 0)
            n++;
    }
    if(n > 1)
        return true;
    return false;
}

bool vec_sort(const pair<int,double> &a, const pair<int,double> &b)
{
       return a.second<b.second;
}