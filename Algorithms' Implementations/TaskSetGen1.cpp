#include<bits/stdc++.h>

#define int long long int
#define ff first
#define ss second
#define pb push_back

using namespace :: std;

class Task{
	public:
		double u;   // utilisation of a task
		double c;     // worst case utilisation time of a task
		double t;     // inter-arrival time period
		int d;     // deadline of a task
};

vector<Task> generator(int n, double U){
	int cur_time = 0;
	vector<Task> ans(n);

	int i = 0;
	if(n%2){
		ans[0].u = U/(double)n;
		ans[0].t = (double)(rand()%41)/(double)10+3.0;
		ans[0].d = cur_time+3;
		ans[0].c = ans[0].u*ans[0].t;
		i++;
		cur_time+=3;
	}

	while(i<n){
		double extra = (min(1.0-(double)U/(double)n, (double)U/(double)n))*((double)(rand()%11)/(double)10);
		
		ans[i].u = U/(double)(n)+extra;
		ans[i].t = (double)(rand()%41)/(double)10+3.0;
		ans[i].d = cur_time+3;
		ans[i].c = ans[i].u*ans[i].t;
		i++;
		cur_time+=3;
		

		ans[i].u = U/(double)(n)-extra;
		ans[i].t = (double)(rand()%41)/(double)10+3.0;
		ans[i].d = cur_time+3;
		ans[i].c = ans[i].u*ans[i].t;
		i++;
		cur_time+=3;
		
	}


	return ans;
}

int32_t main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	double U;
	int n;
	
	cout<<setprecision(6);

	// cout<<"Enter Maximum Utilisation of the Multiprocessor System: ";
	cin>>U;
	// cout<<"Enter Number of tasks required to be generated: ";
	cin>>n;
	
	bool invalid = false;

	try{
		if(U>n){
			invalid = true;
			throw invalid;
		}
	}
	catch(bool invalid){
		cout<<"Invalid values. Task-set could not be generated.\n";
		cout<<"Maximum Utilisation should be less than or equal to the number of tasks.\n";
		return 0;
	}

	// Vector to store the tasks
	vector<Task> taskset = generator(n, U);

	cout<<"---------------------------------------------------------------------------------------------------------------------\n";

	cout<<"Inter-arrival time period\tdeadline of a task\tutilisation of a task\tworst case utilisation time of a task\n";
    
    double x = 0;

	for(auto i:taskset){
	    x+=i.u;
		cout<<"\t\t\t"<<i.t<<"\t\t\t\t\t\t"<<i.d<<"\t\t\t\t\t"<<i.u<<"\t\t\t\t\t"<<i.c<<"\n";
	}
    
	return 0;
}