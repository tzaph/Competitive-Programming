/*
	IOI 2011 2A Crocodile
	Multisource dijkstra from exit to start
	Skip first appearance cuz t r a p
*/
#include "crocodile.h"
#include <vector>
#include <queue>
using namespace std;

vector<pair<int, int> > adj[100005];
int dist[100005];
int travel_plan(int N, int M, int R[][2], int L[], int K, int P[]){
	for(int i = 0; i < N; i ++) dist[i] = -1;
	for(int i = 0; i < M; i ++){
		adj[R[i][0]].push_back({R[i][1], L[i]});
		adj[R[i][1]].push_back({R[i][0], L[i]});
	}

	priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
	for(int i = 0; i < K; i ++){
		pq.push({0, P[i]});
		dist[P[i]] = -69;
	}

	while(!pq.empty()){
		pair<int, int> nw = pq.top();
		pq.pop();

		if(dist[nw.second] >= 0) continue;
		if(dist[nw.second] == -1){
			dist[nw.second] = -69;
			continue;
		}

		dist[nw.second] = nw.first;

		for(pair<int, int> nx : adj[nw.second])
			pq.push({nw.first + nx.second, nx.first});
	}

	return dist[0];
}