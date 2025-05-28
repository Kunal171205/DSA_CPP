#include <iostream>
#include <queue>
#include <fstream>
#include <climits>
using namespace std;

struct node {
    int start;
    int end;
    int weight;
    node* next;

    node(int start, int end, int weight) 
    {
        this->start = start;
        this->end = end;
        this->weight = weight;
        this->next = NULL;
    }
};

struct edge {
    int start;
    int end;
    int weight;
};

class graph {
    node** A;
    int v;
    string* v_name;

public:
    graph(string f1, string f2) {
        fstream fin;
        fin.open(f1, ios::in);
        fin >> v;
        cout << "No of vertices : " << v << endl;
        A = new node*[v];
        for (int i = 0; i < v; i++)
            A[i] = NULL;

        node* nn;
        int e;
        for (int i = 0; i < v; i++) {
            for (int j = 0; j < v; j++) {
                fin >> e;
                if (e) {
                    nn = new node(i, j, e);
                    nn->next = A[i];
                    A[i] = nn;
                }
            }
        }

        fstream fin2;
        fin2.open(f2, ios::in);
        fin2 >> v;
        string s;
        v_name = new string[v];
        for (int i = 0; i < v; i++) {
            fin2 >> s;
            v_name[i] = s;
        }
    }

    ~graph() {
        for (int i = 0; i < v; i++) {
            node* ptr = A[i];
            while (ptr) {
                node* next = ptr->next;
                delete ptr;
                ptr = next;
            }
        }
        delete[] A;
        delete[] v_name;
    }

    void prims(int start) {
        bool* visited = new bool[v]();
        visited[start] = true;

        edge* st = new edge[v - 1];
        edge min;

        node* ptr;
        int count = 0;
        for (int i = 0; i < v - 1; i++) {
            min.start = -1;
            min.end = -1;
            min.weight = INT_MAX;

            for (int j = 0; j < v; j++) {
                if (visited[j]) {
                    ptr = A[j];
                    while (ptr) {
                        if (!visited[ptr->end] && ptr->weight < min.weight) {
                            min.start = ptr->start;
                            min.end = ptr->end;
                            min.weight = ptr->weight;
                        }
                        ptr = ptr->next;
                    }
                }
            }

            if (min.start != -1 && min.end != -1) {
                st[count] = min;
                visited[min.end] = true;
                count++;
            }
        }

        if (count != v - 1) {
            cout << "Graph is not connected" << endl;
        } else {
            for (int i = 0; i < v - 1; i++) {
                cout << v_name[st[i].start] << " -> " << v_name[st[i].end] << " Weight " << st[i].weight << endl;
            }
        }

        delete[] st;
        delete[] visited;
    }
};

int main() {
    graph g("vertex2.txt", "Dept.txt");
    g.prims(0);
    return 0;
}