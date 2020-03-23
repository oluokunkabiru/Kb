#include<iostream>
#include<conio.h>
#include<math.h>
#include<string>
#include <sstream>
#include<iomanip>
using namespace std;

int findNextEvent(float aa, float bb, float cc, int dd);
void generateRandomNumber();
void generateArrivalTimeTable();
void generateTraceTable();
void startServiceA();
void endServiceA();
void startServiceB();
void endServiceB();

float startA, startB, endA, endB, CLOCK, R[101],interArrivalTime[50],arrivalTime[50],serviceTypeRND[50];
bool isBusyA, isBusyB, aWorkedLast;
int arrival, Q, X[101],Xn = 71,next;
string nextevent;

stringstream ss;

int main()
{
	cout<<setprecision(3)<<fixed;
	cout<<"======================================================================================"<<endl;
	cout<<"SIMULATION PROGRAM FOR THE HAIRDRESSER'S SHOP, CSE409[PROF GANIYU]"<<endl;
	cout<<"======================================================================================"<<endl;
	cout<<endl;
	cout<<"Xn+1 = (97Xn + 3) mod 1000"<<endl;
	cout<<"Rn = Xn/1000 	where n = 1,2,3,...,n"<<endl;
	cout<<"R0 = 71\n"<<endl;
	generateRandomNumber();
	cout<<endl;
	cout<<"We then use 19 random numbers to generate teh next table, 9 for the inter-arrival time and\n";
	cout<<"10 for the service type. Such that, if (RND<0.6) the customer wants a CUT and if (RND>6),\n";
	cout<<"the user wants a WASH AND CUT service\n";
	cout<<"-3ln(RND) is used to calculate the arrival time\n";
	cout<<endl;
	generateArrivalTimeTable();
	cout<<endl;
	generateTraceTable();
	cout<<"\n\n"<<endl;
	cout<<"======================================================================================"<<endl;
	cout<<"SIMULATION DONE BY GROUP 4 CSE409 PROJECT ASSIGNMENT, THANKS!"<<endl;
	cout<<"======================================================================================"<<endl;
	getch();
}

void generateRandomNumber(){
	X[0]= Xn;
	R[0] = X[0]/1000.0 ;
	for (int i =1; i<=100; i++){

		X[i]= ((97*Xn) + 3)%1000;
		Xn = X[i];
		R[i] = X[i]/1000.0 ;
	}
	cout<<"TABLE FOR RANDOM NUMBERS"<<endl;
	cout<<"======================="<<endl;
	cout<<"n"<<"	"<<"Xn"<<"	"<<"Rn"<<endl;
	cout<<"======================="<<endl;
	for (int i =1; i<=100; i++){
		cout<<i<<"	"<<X[i]<<"	"<<R[i]<<endl;
	}
	cout<<"======================="<<endl;
}

void generateArrivalTimeTable(){
	arrivalTime[0]=0.0;
	interArrivalTime[9]=0.0;
	string typep;
	cout<<"TABLE FOR ARRIVAL TIMES AND SERVICE TYPE"<<endl;
	cout<<"================================================================================================"<<endl;
	cout<<"RND		-3ln(RND)	Arrival		CLOCK		RND		 Service Type"<<endl;
	cout<<"================================================================================================"<<endl;
		for(int i = 0; i<=49;i++){
		if(i<49){
		interArrivalTime[i]=-3*(log(R[i]));
		arrivalTime[i+1]=  interArrivalTime[i]+arrivalTime[i];
		serviceTypeRND[i] = R[i+9];
		if(R[i+9]<0.6){
			typep = "Cut";
		}else{
			typep = "Wash and Cut";
		}
		cout<<R[i]<<"		"<<interArrivalTime[i]<<"		"<<(i+1)<<"		"<<arrivalTime[i]<<"		"<<serviceTypeRND[i]<<"		"<<typep<<endl;
		}else{
		arrivalTime[i+1]=  interArrivalTime[i]+arrivalTime[i];
		if(R[i+9]<0.6){
			typep = "Cut";
		}else{
			typep = "Wash and Cut";
		}
		cout<<"				"<<(i+1)<<"		"<<arrivalTime[i]<<"		"<<R[i+9]<<"		"<<typep<<endl;
		}

	}
	cout<<"================================================================================================"<<endl;
}


void generateTraceTable(){
	CLOCK = arrivalTime[0];
	Q = 0;
	startA = -1;
	endA = -1;
	startB = -1;
	endB = -1;
	isBusyA = false;
	isBusyB = false;
	aWorkedLast = false;
	arrival = 0;
	next = findNextEvent(arrivalTime[arrival],endA,endB,arrival);
	cout<<"TRACE TABLE"<<endl;
	cout<<"================================================================================================================"<<endl;
	cout<<"CLOCK		NEXT EVENT		Q	START A		END A		START B			END B"<<endl;
	cout<<"================================================================================================================="<<endl;
	while(arrival<=50){
		if (next==1){
			arrival++;
			if(arrival>49){
				break;
			}
			CLOCK = arrivalTime[arrival-1];
			if(isBusyA){
				if (!isBusyB){
					startServiceB();
				}else{
					Q=Q+1;
				}

			}else{
				if (!aWorkedLast){
					startServiceA();
				}else{
					startServiceB();
				}
			}
		}else if(next==2){
			endServiceA();
		}else if(next==3){
			endServiceB();
		}

		next = findNextEvent(arrivalTime[arrival],endA,endB,arrival);
		if((startA<0) & (startB<0)){
		cout<<CLOCK<<"		"<<nextevent<<"	"<<Q<<"	"<<"-"<<"		"<<"-"<<"		"<<"-"<<"		"<<"-"<<endl;
		}else if(startA<0){
		cout<<CLOCK<<"		"<<nextevent<<"	"<<Q<<"	"<<"-"<<"		"<<"-"<<"		"<<startB<<"		"<<endB<<endl;
		}else if(startB<0){
		cout<<CLOCK<<"		"<<nextevent<<"	"<<Q<<"	"<<startA<<"		"<<endA<<"		"<<"-"<<"		"<<"-"<<endl;
		}else{
		cout<<CLOCK<<"		"<<nextevent<<"	"<<Q<<"	"<<startA<<"		"<<endA<<"		"<<startB<<"		"<<endB<<endl;
		}

	}
	cout<<"================================================================================================================="<<endl;
}

int findNextEvent(float aa, float bb, float cc, int dd){
	float arr[3] = {aa, bb, cc};
	float min = arr[0];
	int n = 1;
	for(int i = 1; i < 3; i++){
		if((arr[i]<min) & (arr[i]>=0)){
			n=i+1;
		}
	}
	if(n==1){
		ss<<setprecision(2)<<fixed<<"Arr " <<dd+1<<" at "<<arr[n-1]<<"	";
		string str = ss.str();
		nextevent = str;
	}else if(n==2){
		ss<<setprecision(2)<<fixed<<"EOS A at "<<arr[n-1]<<"	";
		string str = ss.str();
		nextevent = str;
	}else if(n==3){
		ss<<setprecision(2)<<fixed<<"EOS B at "<<arr[n-1]<<"	";
		string str = ss.str();
		nextevent = str;
	}
	ss.str("");
	return n;
}


void startServiceA(){
	startA = CLOCK;
	if (serviceTypeRND[arrival]<0.6){
		endA = startA + 5.0;
	}else{
		endA = startA + 8.0;
	}
	isBusyA = true;
	aWorkedLast = true;
}


void startServiceB(){
	startB = CLOCK;
	if (serviceTypeRND[arrival-1]<0.6){
		endB = startB + 5.0;
	}else{
		endB = startB + 8.0;
	}
	isBusyB = true;
	aWorkedLast = false;
}


void endServiceA(){
	CLOCK = endA;
	startA = -1;
	endA = -1;
	isBusyA = false;
	if (Q>0){
		Q = Q - 1;
		startServiceA();
	}
}


void endServiceB(){
	CLOCK = endB;
	startB = -1;
	endB = -1;
	isBusyB = false;
	if (Q>0){
		Q = Q - 1;
		startServiceB();
	}
}
xed<<"Arr " <<dd+1<<" at "<<arr[n-1]<<"	";
		string str = ss.str();
		nextevent = str;
	}else if(n==2){
		ss<<setprecision(2)<<fixed<<"EOS A at "<<arr[n-1]<<"	";
		string str = ss.str();
		nextevent = str;
	}else if(n==3){
		ss<<setprecision(2)<<fixed<<"EOS B at "<<arr[n-1]<<"	";
		string str = ss.str();
		nextevent = str;
	}
	ss.str("");
	return n;
}


void startServiceA(){
	startA = CLOCK;
	if (serviceTypeRND[arrival]<0.6){
		endA = startA + 5.0;
	}else{
		endA = startA + 8.0;
	}
	isBusyA = true;
	aWorkedLast = true;
}


void startServiceB(){
	startB = CLOCK;
	if (serviceTypeRND[arrival-1]<0.6){
		endB = startB + 5.0;
	}else{
		endB = startB + 8.0;
	}
	isBu