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
bool sortbysec(const pair<int,double> &a, const pair<int,double> &b);
int * compute_nn_edges();         // Calculates Edges (weight? rank?)
int * compute_matching(void);    // Has to compute the array G2


struct Point {
    int x;
    int y;
    bool free;
    int incidents;

    // Constructors
    Point(){
        free = true;
        incidents = 0;
    }
};

struct sl_edge {
    int p1;                                 // i point
    int p2;                                 // j point
    vector<pair<int, double> > pref_list;   // Pref list of <point, distance>
};

int num_points;
int * G1;                     // Holds nearnest neighbor edges
int * G2;                     // Holds result of Gale-Shapely Algo
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

    cout << "Nearest Neighbors" << endl;
    for(int i = 0; i < points.size(); i++){
        cout << G1[i] << endl;
    }
    cout << "Points & Incident Count" << endl;
    for(int i = 0; i < points.size(); i++){
        cout << points[i].x << "," << points[i].y << ": " << points[i].incidents << endl;
    }

    G2 = compute_matching();
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
int * compute_matching(void){
    int * temp = new int[10];

    // sl-vertices based on incident edge count
    vector<int> sl_vertices;
    for(int i = 0; i < points.size(); i++){
        if (points[i].incidents <= 1){
            sl_vertices.push_back(i);
        }
    }

    cout << sl_vertices.size() << endl;

    // List of Weights for each sl-vertex: <point, weight>
    vector<sl_edge> weights(sl_vertices.size());
    for(int i = 0; i < sl_vertices.size(); i++){
        sl_edge cur_edge;
        cur_edge.p1 = sl_vertices[i];   // p1 = first sl_vertex
        cur_edge.p2 = G1[i];            // p2 = p1's nearest neighbor
        
        for(int j = 0; j < sl_vertices.size(); j++){
            int p3 = sl_vertices[j];
            if(cur_edge.p1 != p3 && cur_edge.p2 != p3){
                double calc_dist = sqrt(pow((points[cur_edge.p2].x - points[p3].x), 2) + pow((points[cur_edge.p2].y - points[p3].y), 2));
                cur_edge.pref_list.push_back(make_pair(p3, calc_dist));
            }
        }
        weights.push_back(cur_edge);
    }

    cout << "Printing out sl_verticies and weights" << endl;
    for(int i = 0; i < weights.size(); i++){
        sortbysec(weights[i].pref_list.begin(), weights[i].pref_list.end());
        for(int j = 0; j < weights[i].pref_list.size(); j++){
            cout << "(" << weights[i].p1 << ", " << weights[i].p2 << "): " << weights[i].pref_list[j].first << " - " << weights[i].pref_list[j].second << endl;
        }
    }

    // Print sl-verticies
    for(int i = 0; i < sl_vertices.size(); i++){
        cout << sl_vertices[i] << endl;
    }


    return temp;
}


bool sortbysec(const pair<int,double> &a, 
              const pair<int,double> &b) 
{ 
    return (a.second < b.second); 
} 