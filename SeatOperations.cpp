/*
Student Name:Muhammet Çavuş
Student Number:2018400306
Project Number: 3
Compile Status: [SUCCESS/FAIL]
Running Status: [SUCCESS/FAIL]
Notes: Anything you want to say about your code that will be helpful in the grading process.
*/
#include "SeatOperations.h"

using namespace std;


SeatOperations::SeatOperations(int N, int M){
    this->N=N;
    this->M=M;
    lines[0]=* new vector<Person> (N);
    lines[1]=* new vector<Person> (M);
    // IMPLEMENT ME!
}

void SeatOperations::addNewPerson(int personType, const string& ticketInfo){

    Person p;
    int lineType=ticketInfo[0]=='A' ? 0:1;
    int seatNumber=atoi(&ticketInfo[1]);
    p.line=lineType;
    p.seatNumber=seatNumber;
    p.type=personType;
    locate(p);


    // IMPLEMENT ME!
}

void SeatOperations::printAllSeats(ofstream& outFile){

    for(int i=0; i<N; i++) {
        if(lines[0][i].type!=0) {
            string s=lines[0][i].line==0 ? "A" : "B";
            outFile<<lines[0][i].type<<" "<<s<<lines[0][i].seatNumber<<endl;
        }else {
            outFile<<0<<endl;
        }

    }

    for(int i=0; i<M; i++) {
        if(lines[1][i].type!=0) {
            string s=lines[1][i].line==0 ? "A" : "B";
            outFile<<lines[1][i].type<<" "<<s<<lines[1][i].seatNumber<<endl;
        }else {
            outFile<<0<<endl;
        }
    }
    // IMPLEMENT ME!
}
void SeatOperations::locate(Person &p){
    Person p2;
    int seatNo;
    if(p.type==1) {
        if(p.lastOperation%2==0) {
            seatNo=p.line==0 ? (p.seatNumber-1)%N : (p.seatNumber-1)%M ;
            p2=lines[p.line][seatNo];
            p.lastOperation++;
            lines[p.line][seatNo]=p;
            if(p2.type!=0) {
                locate(p2);
            }

        } else {
            seatNo=p.line==0 ?  (p.seatNumber-1)%M : (p.seatNumber-1)%N ;
            p2=lines[1-p.line][seatNo];
            p.lastOperation++;
            lines[1-p.line][seatNo]=p;
            if(p2.type!=0) {
                locate(p2);
            }
        }

    } else if(p.type==2) {
        if(p.lastOperation==0) {
            seatNo=p.seatNumber-1;
            int lineSeat=p.line==0 ? N:M;
            seatNo=seatNo%lineSeat;
            p2=lines[p.line][seatNo];
            p.lastOperation++;
            p.lastSeatNumber=seatNo;
            p.lastLine=p.line;
            lines[p.line][seatNo]=p;
            if(p2.type!=0) {
                locate(p2);
            }

        } else {
            int lineSeat=p.lastLine==0 ? N:M;
            int seatNo=p.lastSeatNumber+1;
            if(seatNo==lines[p.lastLine].size()) {
                p2=lines[1-p.lastLine][0];
                p.lastOperation++;
                p.lastSeatNumber=0;
                p.lastLine=1-p.line;
                lines[p.lastLine][0]=p;
                if(p2.type!=0) {
                    locate(p2);
                }
            }
            else {
                p2=lines[p.lastLine][seatNo];
                p.lastOperation++;
                p.lastSeatNumber=seatNo;
                lines[p.lastLine][p.lastSeatNumber]=p;
                if(p2.type!=0) {
                    locate(p2);
                }
            }
        }

    } else if (p.type==3) {
        if(p.lastOperation==0) {
            seatNo=p.seatNumber-1;
            int lineSeat=p.line==0 ? N:M;
            seatNo=seatNo%lineSeat;
            p2=lines[p.line][seatNo];
            p.lastOperation=1;
            p.lastSeatNumber=seatNo;
            p.lastLine=p.line;
            lines[p.lastLine][seatNo]=p;
            if(p2.type!=0) {
                locate(p2);
            }
        } else {
            seatNo=p.lastSeatNumber+((2*p.lastOperation-1)%(M+N));
            if(seatNo<lines[p.lastLine].size()) {
                p2=lines[p.lastLine][seatNo];
                p.lastOperation++;
                p.lastSeatNumber=seatNo;
                lines[p.lastLine][seatNo]=p;
                if(p2.type!=0) {
                    locate(p2);
                }
            } else if(seatNo<M+N) {
                p2=lines[1-p.lastLine][seatNo-lines[p.lastLine].size()];
                p.lastOperation++;
                p.lastSeatNumber=seatNo-lines[p.lastLine].size();
                p.lastLine=1-p.lastLine;
                lines[p.lastLine][p.lastSeatNumber]=p;
                if(p2.type!=0) {
                    locate(p2);
                }
            } else {
                p2=lines[p.lastLine][seatNo-M-N];
                p.lastOperation++;
                p.lastSeatNumber=seatNo-N-M;
                lines[p.lastLine][p.lastSeatNumber]=p;
                if(p2.type!=0) {
                    locate(p2);
                }

            }
        }

    } else {
        return;
    }

}




// YOU CAN ADD YOUR HELPER FUNCTIONS