/*
Ben Reilly 
Eric Gustin
Brian Steuber
Chris Fergueson 

Implements Stooge, Worse, Cocktail, & Ben Sort
along with a basic testing frame-work
*/

#ifndef PROJ3_H
#define PROJ3_H

#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <assert.h>

using namespace std;

//Main Testing Framework
void run_test(const string &file_name, void (*sort)(int *arr, int n));
int* file_to_array(const string &file_name, int &n);
bool is_sorted(int *arr, int n);

//Stooge Sort
void stooge_sort(int *arr, int n);
void stooge_sort(int arr[], int f, int l);

//Worse Sort
void worse_sort(int *arr, int n);
int** generate_perm(int *arr, int n);
void recur_generate_perm(int **arr_arr, int arr_arr_i, int *arr, int l, int r);
void lex_bubble_sort(int **arr_arr, int fact_n, int n);
bool lex_greater_than(int *lhs_arr, int *rhs_arr, int n);
int factorial(int n);

//Cocktail Sort
void cocktail_sort(int arr[], int arr_size);

//Ben Sort
void ben_sort(int *arr, int n);
void get_high_low(int *arr, int n, int &high, int &low);
void hash_arr(int *arr, int n, int max, int min);
void insertion_sort(int *arr, int n);
int map_func(int data, int n, int max, int min);

#endif