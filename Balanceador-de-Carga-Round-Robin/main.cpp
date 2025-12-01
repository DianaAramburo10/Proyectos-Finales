#include <iostream>
#include "LoadBalancer.h"

using namespace std;

int main() {
    int numServers = 5;
    int totalRequests = 10000;

    cout << "Simulacion Load Balancer - Round Robin\n";
    cout << "Servidores: " << numServers << endl;
    cout << "Requests: " << totalRequests << endl;

    Server* head = createCircularServerList(numServers);

    distributeRequestsRoundRobin(head, totalRequests);

    printLoadTable(head, totalRequests);
    printBarChart(head);

    freeCircularServerList(head);

    return 0;
}
