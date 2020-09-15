/***************************************************
* COP4530 Programming Assignment 1 - Due 9/16/2020
* Cure Reconstruction using matchings
* Author: Kaedon Hamm (kah16h)
* Partner: Karl Cooley
****************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

// Function Declaration
int * compute_nn_edges();         // Calculates Edges (weight? rank?)
int * compute_matching(void);    // Has to compute the array G2


struct Point {
    int x;
    int y;
    bool free;
    int degree;

    // Constructors
    Point(){
        free = true;
        degree = 0;
    }
};

int * G1;               // Holds nearnest neighbor edges
int * G2;               // Holds result of Gale-Shapely Algo
vector<Point> points;   // Holds inputted points


// Body of program
int main(){
    int num_points, x, y;
    char basura;
    cin >> num_points;

    for (int i = 0; i < num_points; i++){
        struct Point point;
        string input;
        cin >> x >> basura >> y;
        //point.x = stoi(input.substr(0, input.find(',')));
        //point.y = stoi(input.substr(input.find(',') + 1));
        point.x = x;
        point.y = y;
        points.push_back(point);
    }

    G1 = compute_nn_edges();
    for(int i = 0; i < points.size(); i++){
        cout << G1[i] << endl;
    }
    //G2 = compute_matching();
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
        nn_list[i] = nn_num;
    }
    return nn_list;
}

//
int * compute_matching(void){

}